#include "ICodeGen.h"
#include <sstream>
#include <iomanip>
#include <list>

ICodeOprand* 
ICodeGenMgr::genICodeOprd(IRValue* irv) {
    if (irv->isReg() && !spilled(irv)) {
        return reg(getPhyRegNum(irv->regNum()), irv->isFloatReg());
    } else if (irv->isStrConst()) {
        return new ICodeOprand(ICodeOprand::STRING, irv->sval());
    } else if (irv->isIntConst()) {
        return new ICodeOprand(irv->ival());
    } else if (irv->isFloatConst()) {
        return new ICodeOprand(irv->fval());
    } else if (irv->isLabel()) {
        return new ICodeOprand(ICodeOprand::LABEL, irv->sval());
    } else {
        return nullptr;
    }
}


ICodeOprand*
ICodeGenMgr::reg(int id, bool isFloat) {
    auto & regs = isFloat?fregs_:iregs_;
    ICodeOprand::Type t = isFloat?ICodeOprand::FREG:ICodeOprand::IREG;
    if (!regs.count(id)) {
        regs[id] = new ICodeOprand(t, id);
    } 
    return regs[id];
}

ICodeOprand* 
ICodeGenMgr::loadSpilledVar(int spillOffset, int tmpRID, bool isFloat, vector<ICode*> &icode) {
    ICodeOprand* tmpReg;
    // special case hacking , handle store @a,b,c  a,b,c all spilled
    if (tmpRID == 3) {
        tmpReg = &raddr;
    } else {
        tmpReg = isFloat?&fspills[tmpRID]:&rspills[tmpRID];
    }
    ICode::OpCode opc = isFloat?ICode::LDF:ICode::LDI;
    ICode* getAddr = new ICode(ICode::ADD, {&bp, constInt(-spillOffset), &raddr});
    ICode* load = new ICode(opc, {&raddr, tmpReg});
    icode.push_back(getAddr);
    icode.push_back(load);
    return tmpReg;
}

void
ICodeGenMgr::storeSpilledVar(int spillOffset, int tmpRID, bool isFloat, vector<ICode*> &icode) {
    ICodeOprand* tmpReg = isFloat?&fspills[tmpRID]:&rspills[tmpRID];
    ICode::OpCode opc = isFloat?ICode::STF:ICode::STI;
    ICode* getAddr = new ICode(ICode::ADD, {&bp, constInt(-spillOffset), &raddr});
    ICode* store = new ICode(opc, {tmpReg, &raddr});
    icode.push_back(getAddr);
    icode.push_back(store);
}

void 
ICodeGenMgr::pushReg(int rid, bool isFloat, vector<ICode*> & icode) {
    ICode::OpCode opc = isFloat?ICode::STF:ICode::STI;
    ICode* subSP = new ICode(ICode::SUB, {&sp, constInt(1), &sp});
    ICode* store = new ICode{opc, {reg(rid, isFloat), &sp}};
    icode.push_back(subSP);
    icode.push_back(store);
}

void 
ICodeGenMgr::popReg(int rid, bool isFloat, vector<ICode*> & icode) {
    ICode::OpCode opc = isFloat?ICode::LDF:ICode::LDI;
    ICode* load = new ICode{opc, {&sp, reg(rid, isFloat)}};
    icode.push_back(load);
    incSP(icode);
}

void
ICodeGenMgr::pushLabelOrStr(const string & sval, bool isString, vector<ICode*> & icode) {
    auto movOp = isString?ICode::MOVS:ICode::MOVL;
    ICodeOprand* moved = isString?constStr(sval):label(sval);
    ICode* mov = new ICode(movOp, {moved, &rspills[0]});
    ICode* subSP = new ICode(ICode::SUB, {&sp, constInt(1), &sp});
    ICode* store = new ICode{ICode::STI, {&rspills[0], &sp}};
    icode.push_back(mov); icode.push_back(subSP); icode.push_back(store);
}
void 
ICodeGenMgr::pushValue(IRValue* irv, vector<ICode*> & icode) {
    ICode::OpCode opc = irv->isFloatVal()?ICode::STF:ICode::STI;
    ICodeOprand* pushed = genICodeOprd(irv);
    if (irv->isAddr()) {
        VariableEntry* var = (VariableEntry*)irv->sym();
        // constant sized array, global or local.
        if (var->nSubscripts()) {
            if (var->isStatic()) {
                pushed = constInt(var->heapOffset());
            } else {
                icode.push_back(new ICode(ICode::ADD, {&bp, constInt(-var->stkOffset()), &rspills[0]}));
                pushed = &rspills[0];
            }
        }
    }
    if (!pushed) {
        // spilled value
        pushed = loadSpilledVar(spillOffset(irv), 0, irv->isFloatConst(), icode);
    } else if (pushed->isConst() || pushed->isLabel()) {
        pushed = movConst2TmpReg(pushed, icode);
    } 
    decSP(icode, 1);
    ICode* store = new ICode{opc, {pushed, &sp}};
    icode.push_back(store);

}

ICodeOprand* 
ICodeGenMgr::movConst2TmpReg(ICodeOprand* constVal, vector<ICode*> & icode, int tmpRegID) {
    ICode::OpCode movOp;
    ICodeOprand* tmpReg = &rspills[tmpRegID];
    if (constVal->type() == ICodeOprand::STRING) {
        movOp = ICode::MOVS;
    } else if (constVal->type() == ICodeOprand::INT) {
        movOp = ICode::MOVI;
    } else if (constVal->type() == ICodeOprand::FLOAT) {
        movOp = ICode::MOVF;
        tmpReg = &fspills[tmpRegID];
    } else if (constVal->type() == ICodeOprand::LABEL) {
        movOp = ICode::MOVL;
    } else {
        return nullptr;
    }
    ICode* mov = new ICode(movOp, {constVal, tmpReg});
    icode.push_back(mov);
    return tmpReg;
}

void ICodeGenMgr::decSP(vector<ICode*> & icode, int len) {
    icode.push_back(new ICode(ICode::SUB, {&sp, constInt(len), &sp}));
}
void ICodeGenMgr::incSP(vector<ICode*> & icode, int len) {
    icode.push_back(new ICode(ICode::ADD, {&sp, constInt(len), &sp}));
}

void 
ICodeGenMgr::loadFromStk(int dstRID, int offset, bool isFloat, vector<ICode*> & icode) {
    auto ldOp = isFloat?ICode::LDF:ICode::LDI;
    auto dst = reg(dstRID, isFloat);
    ICode* getAddr = new ICode(ICode::ADD, {&bp, constInt(-offset), &raddr});
    ICode* load = new ICode(ldOp, {&raddr, dst});
    icode.push_back(getAddr); icode.push_back(load);
}

void 
ICodeGenMgr::storeInStk(IRValue* irv, int stkOffset, vector<ICode*> & icode) {
    ICode::OpCode opc = irv->isFloatVal()?ICode::STF:ICode::STI;
    ICodeOprand* stored = genICodeOprd(irv);
    if (!stored) {
        // spilled value
        stored = loadSpilledVar(spillOffset(irv), 0, irv->isFloatConst(), icode);
    } else if (stored->isConst() || stored->isLabel()) {
        stored = movConst2TmpReg(stored, icode);
    }
    ICode* getAddr = new ICode(ICode::ADD, {&bp, constInt(-stkOffset), &raddr});
    ICode* store = new ICode{opc, {stored, &raddr}};
    icode.push_back(getAddr); icode.push_back(store);
}



ICodeOprand* 
ICodeGenMgr::evalAddr(vector<IRValue*> &oprands, vector<ICode*> & icode, bool rspill0Used) {
    VariableEntry* ve = (VariableEntry*)oprands[0]->sym();
    int spillRegID = rspill0Used?1:0;
    // global variable or paramter
    if (oprands.size() == 1) {
        if (ve->varKind() == GLOBAL_VAR) {
            return constInt(ve->heapOffset());
        } else {
            // on stack, function paramter
            icode.push_back(new ICode(ICode::ADD, {&bp, constInt(ve->stkOffset()), &raddr}));
            return &raddr;
        }
    }
    IRValue* indexVal = oprands[1];
    ICodeOprand* idxOprd = genICodeOprd(indexVal);
    if (!idxOprd) {
        idxOprd = loadSpilledVar(spillOffset(indexVal), spillRegID, false, icode);
        spillRegID += 1;
    }
    
    if (ve->isStatic()) {
        int base = ve->heapOffset();
        if (idxOprd->isConst()) {
            return constInt(idxOprd->ival() + base);
        }
        icode.push_back(new ICode(ICode::ADD, {constInt(base), idxOprd, &raddr}));
    } else if (!ve->isVLA()) {
        int base = -ve->stkOffset();
        if (idxOprd->isConst()) {
            base += idxOprd->ival();
            icode.push_back(new ICode(ICode::ADD, {&bp, constInt(base), &raddr}));
        } else {
            icode.push_back(new ICode(ICode::ADD, {constInt(base), idxOprd, &raddr}));
            icode.push_back(new ICode(ICode::ADD, {&bp, &raddr, &raddr}));
        }

    } else {
        ICodeOprand* base = genICodeOprd(oprands[0]);
        if (!base) {
            base = loadSpilledVar(spillOffset(oprands[0]), spillRegID, false, icode);
        }
        icode.push_back(new ICode(ICode::ADD, {base, idxOprd, &raddr}));
    }
    return &raddr;
}

static const string opCode2Str[] = {
    "MOVL", "MOVS", "MOVI", "MOVF",
    "MOVIF", "MOVFI",
    "LDI", "LDF",
    "STI", "STF",
    "JMP", "JMPC", "JMPI", "JMPCI",
    "ADD", "SUB", "DIV", "MUL", "MOD", "NEG", "AND", "OR", "XOR",
    "FADD", "FSUB", "FDIV", "FMUL", "FNEG",
    "GT", "GE", "UGT", "UGE", "EQ", "NE",
    "FGT", "FGE", "FEQ", "FNE",
    "PRTI", "PRTS", "PRTF",
    "IN", "INI", "INF",
    "LABEL",
};


string 
ICodeOprand::str() {
    string name;
    if (type_==FREG || type_ == IREG) {
        stringstream ss;
        ss << setw(3) << setfill('0') << regID_;
        ss >> name;
        return (type_ == IREG)?("R"+name):("F"+name);
    } else if (type_ == STRING) {
        return "\"" + sval_ + "\"";
    } else if (type_ == INT) {
        return to_string(ival_);
    } else if (type_ == FLOAT) {
        return to_string(fval_);
    } else if (type_ == LABEL) {
        return sval_;
    }
    return "";
}

string 
ICode::str() {
    string code;
    if (opcode_ == JMPC) {
        code += opCode2Str[opcode_] + " ";
        code += cond_->str() + " ";
        code += getOprand(0)->str();
    } else if (opcode_ == LABEL) {
        code += label_ + ":";
    } else {
        code += opCode2Str[opcode_];
        for (auto opr: oprands_) {
            code += " " + opr->str();
        }
    }
    return code;
}

ICodeOprand ICodeGenMgr::sp(ICodeOprand::IREG , SP_ID);
ICodeOprand ICodeGenMgr::bp(ICodeOprand::IREG , BP_ID);
ICodeOprand ICodeGenMgr::raddr(ICodeOprand::IREG , RADDR_ID);
ICodeOprand ICodeGenMgr::rspills[2] = {{ICodeOprand::IREG , RSPILL_1_ID}, {ICodeOprand::IREG , RSPILL_2_ID}};
ICodeOprand ICodeGenMgr::fspills[2] = {{ICodeOprand::FREG , FSPILL_1_ID}, {ICodeOprand::FREG , FSPILL_2_ID}};
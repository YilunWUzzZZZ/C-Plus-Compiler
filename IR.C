#include "IR.h"
#include <assert.h>
#include <sstream>
#include <iomanip>
#include "STEClasses.h"
#include "RegAlloc.h"
#include "Error.h"
#include "IRGen.h"

IRValue::ValueType 
Instruction::instType2ValType(Instruction::OpCode opcode) {
    if (opcode==MOVIF||opcode==MOVF||opcode==LDF|| (opcode>=FADD && opcode<=FNEG) || opcode == INF) {
        return IRValue::ValueType::FREG;
    } else if (opcode==MOVI || opcode==MOVFI || opcode==LDI || opcode==MOVS || (opcode>=ADD && opcode<=XOR)) {
        return IRValue::ValueType::IREG;
    } else if (opcode >= GT && opcode <= FNE) {
       return IRValue::ValueType::VOID; 
    } else if (opcode == ALLOCA || opcode == IN || opcode == INI) {
        return IRValue::IREG;  
    }  else {
       return IRValue::ValueType::VOID;
    }
}

Instruction::Instruction(OpCode opcode, IRValue* op1, IRValue* op2, int regN): opcode_(opcode) {
    oprands_.push_back(op1); if (op2) oprands_.push_back(op2);
    type(instType2ValType(opcode));
    regNum(regN);
}

Instruction::Instruction(OpCode opcode, const vector<IRValue*> & vals, int regN): opcode_(opcode) {
    for (auto v: vals) {
        oprands_.push_back(v);
    }
    type(instType2ValType(opcode));
    regNum(regN);
}

const string opCode2Name[] = {
    "movl", "movs", "movi", "movf",
    "movif", "movfi",
    "loadi", "loadf",
    "storei", "storef",
    "jmp", "jmpc", "jmpi", "jmpci", "call", "return",// (ONLY for IR)
    "+", "-", "/", "*", "%", "-", "&", "|", "xor",
    "FADD", "FMINUS", "FDIV", "FMUL", "FNEG",
    "GT", "GE", "UGT", "UGE", "EQ", "NE",
    "FGT", "FGE", "FEQ", "FNE",
    "prti", "prts", "prtf",
    "in", "ini", "inf",
    "label", "alloca",
};


string IRValue::name() {
    switch (type_)
    {
    case IREG:
        if (sym_) {
            return sym_->name() + "(r" + to_string(regNum_) + ")";
        } else {
            return "r"+to_string(regNum_);
        }
        break;
    case FREG:
        if (sym_) return sym_->name() + "(f" + to_string(regNum_) + ")";
        return "f" + to_string(regNum_);
    case IVALUE:
        return to_string(ival_);
    case FVALUE:
        return to_string(fval_);
    case SVALUE:
    case LABEL:
        return sval_;
    case VOID:
        return "void";
    case ADDR:
        return sym_->name();
    default:
        break;
    }
    return "err_case";
}


string Instruction::str() {
    std::string s;
    if (opcode_==LABEL) {
        s += label() + ":";
    } else if (opcode_ == OpCode::NEG || opcode_ == OpCode::FNEG || (opcode_ >= OpCode::MOVL && opcode_ <= OpCode::MOVFI)) {
        s += name() + " := " + opCode2Name[opcode_] + " " + oprands_[0]->name();
    } else if (opcode_ >= OpCode::ADD && opcode_ <= OpCode::FNEG) {
        s += name() + " := " + oprands_[0]->name() + " " + opCode2Name[opcode_] + " " + oprands_[1]->name();
    } else if (opcode_>= OpCode::GT && opcode_ <= OpCode::FNE) {
        s += opCode2Name[opcode_] + " " + oprands_[0]->name() + " " + oprands_[1]->name();
    } else if (opcode_ == OpCode::JMPI || opcode_ == OpCode::JMP) {
        s += opCode2Name[opcode_] + " " + oprands_[0]->name();
    } else if (opcode_ == OpCode::JMPC || opcode_ == OpCode::JMPCI) {
        s += opCode2Name[opcode_] + " " + ((Instruction*)oprands_[0])->str() + " " + oprands_[1]->name() + " " + oprands_[2]->name();
    } else if (opcode_ == OpCode::CALL) {
        if (regNum() != -1) {
            s += name() + " := ";
        }
        s += "call @" + oprands_[0]->sym()->name() + "(";
        for (size_t i=1; i<oprands_.size(); i++) {
            s += oprands_[i]->name();
            if (i < oprands_.size()-1) {
                s += ", ";
            }
        }
        s += ")";
    } else if (opcode_ == OpCode::RETURN) {
        s += "return ";
        if (oprands_[0]) {
            s += oprands_[0]->name();
        }
    } else if (opcode_ >= PRTI && opcode_  <= PRTF) {
        s += opCode2Name[opcode_] + " " + oprands_[0]->name();
    } else if (isLoadInst() || isStoreInst()) {
        s += isLoadInst()? (name()+" := "):"";
        s += opCode2Name[opcode_] + " @";
        for (auto opr: oprands_) {
            s += opr->name() + " ";
        }
    }  else if (opcode_ == ALLOCA) {
        s += name() + " := " + opCode2Name[opcode_] + "[ " + oprands_[0]->name() + " ]";
    } else if (opcode_ ==  INF || opcode_ == IN || opcode_ == INI ) {
        s += name() + " := " + opCode2Name[opcode_] + "()";
    }
    return s;
}


void
BasicBlock::print(ostream& os) {
    os << label_ << ": ";
    for (BlockIterator it=begin(); it != end(); ++it) {
        Instruction* inst = *it;
        os << inst->str() << "\n";
    }
    os << "successors: ";
    for (auto succ: succs_) {
        os << succ->label() << " ";
    }
    os << "\n";
    
}

void 
BasicBlock::deleteInst(CodeIterator instIter) {
    auto code = function_->code();
    bool belong = false;
    for (auto it=begin(); it != end(); ++it) {
        if (it == instIter) {
            belong = true;
        }
    }
    if (!belong) {
        internalErr("BasicBlock::deleteInst: instruction doesn't belong to the basicblock\n");
        return;
    }
    if (instIter == begin()) {
        auto deleted = instIter++;
        firstInst(instIter);
        
        // reset the anotherBlock's endInst
        for (auto bb: function_->basicBlocks()) {
            if (bb->end() == deleted) {
                bb->endInst(begin());
                break;
            } 
        }
        code->erase(deleted);
        // delete inst;
    } else {
        code->erase(instIter);
        // delete inst;
    }
}

void 
Function::deleteEmptyBlock(BasicBlock* bb) {
    if (!bb->empty()) {
        internalErr("Trying to delete non-empty block");
        return;
    }
    // all basic blocks (except the entry) must start with a label
    if (bb->begin() == code_->begin()) {
        internalErr("Trying to delete entry block");
        return;
    }
    auto labelIter = --bb->begin();
    Instruction* labelInst = *(labelIter);
    string blockLabelName = labelInst->label();
    auto bbEnd = bb->end();
    if (bbEnd != code_->end() && (*bbEnd)->isLabel()) {
        auto nextLabel = *bbEnd;
        // rename label
        string nbrBlockLabelName = nextLabel->label();
        renameTargetLabel(blockLabelName, nbrBlockLabelName, *code_);
        // delete from predessor's successor list
        for (auto predBB: bb->preds()) {
            auto succs = predBB->succs();
            for (auto it=succs.begin(); it != succs.end(); ) {
                auto curIter = it++;
                if (*curIter == bb) {
                    succs.erase(curIter);
                    break;
                }
            }
        }
        // delete from bblist
        for (auto it=basicBlocks_.begin(); it != basicBlocks_.end(); ) {
            auto curIter = it++;
            if (*curIter == bb) {
                basicBlocks_.erase(curIter);
                break;
            }
        }
        // reset other basicBlocks' end Inst
        for (auto otherBB: basicBlocks()) {
            if (otherBB->end() == labelIter) {
                otherBB->endInst(bbEnd);
                break;
            }
        }
        // delete the label from code
        code_->erase(labelIter);

    } else {
        internalErr("error in deleting basic block, impossible CFG");
    }
}

void 
Function::printCFG(ostream& os) {
    for (auto bb: basicBlocks_) {
        bb->print(os);
        os << "Live variables: ";
        if (bb->liveOut()) {
            for (auto v : *bb->liveOut()) {
                IRValue* irv = (*rid2IRValue_)[v];
                if (irv->sym()) {
                    os << irv->sym()->name() << "(r" << v <<") ";  
                } else {
                    os << "r" << v << " ";
                }
            }
        }
        os << "\n\n";
    }

}

static void
fillUseSet(const vector<IRValue*> & ops, set<int>& def, set<int>& use) {
    for (IRValue* op: ops) {
        if (op && op->isReg() && !def.count(op->regNum())) {
            use.insert(op->regNum());
        }
    }
}

static void
getDefUseSet(BasicBlock* bb, set<int>& def, set<int>& use) {
    for (BlockIterator it=bb->begin(); it != bb->end(); ++it) {
        Instruction* inst = *it;
        if (inst->isArithInst()) {
            IRValue* op1= inst->getOprand(0), *op2=inst->getOprand(1);
            // use before any defintion of this value
            fillUseSet({op1,op2}, def, use);
            def.insert(inst->regNum());
        } else if (inst->opcode() == Instruction::JMPC) {
            Instruction* cmp = (Instruction*)(inst->getOprand(0));
            IRValue* op1= cmp->getOprand(0), *op2=cmp->getOprand(1);
            fillUseSet({op1,op2}, def, use);
        } else if (inst->isCallInst()) {
            vector<IRValue*> oprands = inst->getAllOprands();
            oprands.erase(oprands.begin());
            fillUseSet(oprands, def, use);
            if (inst->regNum() >= 0) {
                def.insert(inst->regNum());
            }
        } else if (inst->isMovInst()) {
            IRValue* op1 = inst->getOprand(0);
            fillUseSet({op1}, def, use);
            def.insert(inst->regNum());
        } else if (inst->isLoadInst()) {
            auto oprands = inst->getAllOprands();
            fillUseSet(oprands, def, use);
            def.insert(inst->regNum());
        } else if (inst->isStoreInst()) {
            auto oprands = inst->getAllOprands();
            fillUseSet(oprands, def, use);
        } else if (inst->isReturnInst() || inst->isPrtInst()) {
            fillUseSet({inst->getOprand(0)}, def, use);
        } else if (inst->opcode() == Instruction::ALLOCA) {
            fillUseSet(inst->getAllOprands(), def, use);
            def.insert(inst->regNum());
        } else if (inst->isInInst()) {
            if (inst->regNum() >= 0) {
                def.insert(inst->regNum());
            }
        }
    }
}

void
Function::livenessAnalysis() {
    unordered_map<BasicBlock*, set<int>> bb2UseSet, bb2InSet, bb2DefSet;
    list<BasicBlock*> workList;
    for (auto bb: basicBlocks_) {
        bb2DefSet[bb] = set<int>();
        bb2InSet[bb] = set<int>();
        bb2UseSet[bb] = set<int>();
        delete bb->liveOut();
        bb->liveOut(new set<int>());
        getDefUseSet(bb, bb2DefSet[bb], bb2UseSet[bb]);
        workList.push_back(bb);
    }
    // fix point algorithm
    // In(bb) = Use(bb) U (Out(bb) - Def(bb))
    // Out(bb) = U In(bb') where bb' is a succsessor of bb 
    while (workList.size()) {
        BasicBlock* bb = workList.front();
        workList.pop_front();
        // calculate In(bb)
        set<int> & outSet = *bb->liveOut();
        set<int> & defSet = bb2DefSet[bb], &useSet=bb2UseSet[bb], &inSet = bb2InSet[bb];
        size_t oldInSize = inSet.size();
        for (auto succBB: bb->succs()) {
            for (auto v: bb2InSet[succBB]) {
                outSet.insert(v);
            }
        }
        for (auto v: outSet) {
            if (!defSet.count(v)) {
                inSet.insert(v);
            }
        }
        for (auto v: useSet) {
            inSet.insert(v);
        }
        if (inSet.size() != oldInSize) {
            for (auto predBB: bb->preds()) {
                workList.push_back(predBB);
            }
        }
    }

}

static void
addInterference(set<int> & liveSet, int assignReg, unordered_map<int, IRValue*> & m, RegAllocator* ra, IRValue::ValueType t) {
    for (auto rid: liveSet) {
        if (!m.count(rid)) {
            cout << "non-existent rid: " << rid << "\n";
        }
        IRValue::ValueType rType = m[rid]->type();
        assert(rType == IRValue::IREG || rType==IRValue::FREG);
        if (rType == t && rid != assignReg) {
            ra->addInterference(rid, assignReg);
        }
    }
}

void
Function::buildInterGraph(RegAllocator* iregAlloc, RegAllocator* fregAlloc) {
    // add all the nodes into the graph
    for (auto vreg: *rid2IRValue_) {
        if (vreg.second->isIntReg()) {
            iregAlloc->addNode(vreg.first);
        } else {
            fregAlloc->addNode(vreg.first);
        }
    }
    for (auto bb: basicBlocks()) {
        if (bb->begin() == bb->end()) {
            internalErr("Empty Block in buildInterGraph");
            continue;
        }
        set<int> liveNow = *bb->liveOut();
        BlockIterator bi = --(bb->end());
        bool quit = false;
        while (!quit) {
            if (bi == bb->begin())
                quit = true;
            Instruction* inst = *bi;
        
            if (inst->isArithInst()) {
                IRValue* op1= inst->getOprand(0), *op2=inst->getOprand(1);
                RegAllocator* ra = inst->type() == IRValue::IREG?iregAlloc:fregAlloc;
                if (inst->regNum() < 0) {
                    cout << "err inst " << inst->str() << "\n"; 
                }
                addInterference(liveNow, inst->regNum(), *rid2IRValue_, ra, inst->type());
                liveNow.erase(inst->regNum());
                if (op1 && op1->isReg()) {
                    liveNow.insert(op1->regNum());
                }
                if (op2 && op2->isReg()) {
                    liveNow.insert(op2->regNum());
                }
            } else if (inst->isCallInst()) {
                call2LiveOut_[inst] = liveNow;
                vector<IRValue*> oprands = inst->getAllOprands();
                if (inst->regNum() >= 0) {
                    RegAllocator* ra = inst->type() == IRValue::IREG?iregAlloc:fregAlloc;
                    addInterference(liveNow, inst->regNum(), *rid2IRValue_, ra, inst->type());
                    liveNow.erase(inst->regNum());
                    call2LiveOut_[inst].erase(inst->regNum());
                }
                oprands.erase(oprands.begin());
                for (auto v: oprands) {
                    if (v && v->isReg()) {
                        liveNow.insert(v->regNum());
                    }
                }
            } else if (inst->isMovInst()) {
                IRValue* op1 = inst->getOprand(0);
                RegAllocator* ra = inst->type() == IRValue::IREG?iregAlloc:fregAlloc;
                if (inst->regNum() < 0) {
                    cout << "err inst " << inst->str() << "\n"; 
                }
                addInterference(liveNow, inst->regNum(), *rid2IRValue_, ra, inst->type());
                liveNow.erase(inst->regNum());
                if (op1 && op1->isReg()) {
                    liveNow.insert(op1->regNum());
                }
            } else if (inst->opcode() == Instruction::JMPC) {
                Instruction* cmp = (Instruction*)(inst->getOprand(0));
                IRValue* op1= cmp->getOprand(0), *op2=cmp->getOprand(1);
                if (op1->isReg()) {
                    liveNow.insert(op1->regNum());
                }
                if (op2->isReg()) {
                    liveNow.insert(op2->regNum());
                }
            } else if (inst->isLoadInst()) {
                RegAllocator* ra = inst->type() == IRValue::IREG?iregAlloc:fregAlloc;
                if (inst->regNum() < 0) {
                    cout << "err inst " << inst->str() << "\n"; 
                }
                addInterference(liveNow, inst->regNum(), *rid2IRValue_, ra, inst->type());
                liveNow.erase(inst->regNum());
                auto oprands = inst->getAllOprands();
                for (auto v: oprands) {
                    if (v && v->isReg()) {
                        liveNow.insert(v->regNum());
                    }
                }
            } else if (inst->isStoreInst()) {
                auto oprands = inst->getAllOprands();
                for (auto v: oprands) {
                    if (v && v->isReg()) {
                        liveNow.insert(v->regNum());
                    }
                }
            } else if ( inst->isReturnInst() || inst->isPrtInst()) {
                IRValue* op1 = inst->getOprand(0);
                if (op1 && op1->isReg()) {
                    liveNow.insert(op1->regNum());
                }
            } else if (inst->opcode() == Instruction::ALLOCA) {
                IRValue* alen = inst->getOprand(0);
                addInterference(liveNow, inst->regNum(), *rid2IRValue_, iregAlloc, inst->type());
                liveNow.erase(inst->regNum());
                if (alen->isReg()) {
                    liveNow.insert(alen->regNum());
                }
            }  else if (inst->isInInst()) {
                RegAllocator* ra = inst->type()==IRValue::FREG?fregAlloc:iregAlloc;
                if (inst->regNum() >= 0) {
                    addInterference(liveNow, inst->regNum(), *rid2IRValue_, ra, inst->type());
                    liveNow.erase(inst->regNum());
                }
            }
            
            --bi;
        }
    }

}

#include "Optimization.h"
#include "IR.h"
#include "IRGen.h"
#include <list>
#include <iostream>
#include <assert.h>

extern int optLevel;

Optimizer optimizer;

Optimizer::Optimizer() {
    registerPass(new ConstantPropagation());
    registerPass(new DeadCodeElimination());
}

bool Optimizer::optimize(Function& f) {
    if (optLevel < 1) {
        return false;
    }
    for (auto fp: passes_) {
        fp->runOnFunction(f);
    }
    return true;
}

void ConstantPropagation::getReachingDef(Function & f) {
    unordered_map<BasicBlock*, set<IRValue*>>  &out = outDefs_, gen;
    unordered_map<BasicBlock*, set<IRValue*>> & in = inDefs_;
    unordered_map<BasicBlock*, unordered_map<int, IRValue*>> rid2Def;
    // caculate gen set
    for (auto bb: f.basicBlocks()) {
        for (auto it = bb->begin(); it != bb->end(); ++it) {
            Instruction* inst = *it;
            
            if (inst->isReg() && inst->regNum() >= 0) {
                int rid = inst->regNum();
                if (!rid2Def[bb].count(rid)) {
                    rid2Def[bb][rid] =  inst;
                    gen[bb].insert(inst);
                } else {
                    // reassigned
                    auto oldAssign = rid2Def[bb][rid];
                    gen[bb].erase(oldAssign);
                    rid2Def[bb][rid] = inst;
                    gen[bb].insert(inst);
                }
            }
        }
    }

    // fix point algorithm: Compute reaching definitions
    // in(bb) = U out(bb') where bb' is a predecessor of bb 
    // out(bb) = gen(bb) U (in(bb) - kill(bb)) 
    list<BasicBlock*> worklist;
    for (auto bb: f.basicBlocks()) {
        worklist.push_back(bb);
    }
    while (worklist.size()) {
        auto bb = worklist.front();
        worklist.pop_front();
        // get in(bb)
        for (auto predBB: bb->preds()) {
            for (auto def: out[predBB]) {
                in[bb].insert(def);
            }
        }
        size_t oldOutSize = out[bb].size();
        for (auto def: gen[bb]) {
            out[bb].insert(def);
        }
        for (auto def: in[bb]) {
            int rid = def->regNum();
            if (!rid2Def[bb].count(rid)) {
                out[bb].insert(def);
            }
        }
        if (out[bb].size() != oldOutSize) {
            for (auto succBB: bb->succs()) {
                worklist.push_back(succBB);
            }
        }
    }
#if 0
    for (auto bb: f.basicBlocks()) {
        cout << bb->label() << " Reaching Defs: ";
        for (auto def: in[bb]) {
            cout << ((Instruction*)def)->str() << "\n";
        }
        cout << "\n";
    }
#endif

}

bool isIRVEqual(IRValue* v1, IRValue* v2) {
    if (v1->isIntConst() && v2->isIntConst()) {
        return v1->ival() == v2->ival();
    } else if (v1->isFloatConst() && v2->isFloatConst()) {
        return v1->fval() == v2->fval();
    } else if (v1->isStrConst() || v2->isStrConst()) {
        return v1->sval() == v2->sval();
    } else {
        return false;
    }
}

bool ConstantPropagation::isDefConst(BasicBlock* bb, set<IRValue*> & defs, set<int>& overideDefs) {
    if (!defs.size()) 
        return false;
    bool sameConstantVal=false;
    IRValue* prev = nullptr;
    int rid = (*defs.begin())->regNum();
    // if not redefined in the current block
    // check whether this def is coming from all the possible paths
    // if not, return false. if true, check whether they all all the same constant value
    if (!overideDefs.count(rid)) {
        for (auto predBB: bb->preds()) {
            auto out = outDefs_[predBB];
            bool defined = false;
            for (auto defVal: out) {
                if (defVal->regNum() == rid) {
                    defined = true;
                    break;
                }
            }
            if (!defined) {
                return false;
            }
        }
    }
    for (auto d: defs) {
        if (!def2Constant_.count(d)) {
            sameConstantVal = false;
            break;
        }
        IRValue* constVal = def2Constant_[d];
        if (!prev) {
            sameConstantVal = true;
        } else {
            sameConstantVal = isIRVEqual(prev, constVal);
        }
        prev = constVal;
        if (!sameConstantVal) {
            break;
        }
    }
    return sameConstantVal;
}

IRValue* evalConst(Instruction::OpCode opcode, IRValue* v1, IRValue* v2) {
    bool isFloatOp = opcode >= Instruction::FADD && opcode <= Instruction::FNEG;
    double fv1=isFloatOp?v1->fval():0;
    double fv2 = (v2&&isFloatOp)?v2->fval():0;
    long iv1= !isFloatOp?v1->ival():0;
    long iv2 = (v2&&!isFloatOp)?v2->ival():0;
    double fres=0; long ires=0;
    switch (opcode)
    {
    case Instruction::ADD: case Instruction::FADD:
        if (isFloatOp) fres = fv1+fv2; else ires = iv1+iv2; 
        break;
    case Instruction::SUB: case Instruction::FSUB:
        if (isFloatOp) fres = fv1-fv2; else ires = iv1-iv2; 
        break;
    case Instruction::MUL: case Instruction::FMUL:
        if (isFloatOp) fres = fv1*fv2; else ires = iv1*iv2; 
        break;
    case Instruction::DIV: case Instruction::FDIV:
        if (isFloatOp) fres = fv1/fv2; else ires = iv1/iv2; 
        break;
    case Instruction::NEG: case Instruction::FNEG:
        if (isFloatOp) fres = -fv1; else ires = -iv1; 
        break;
    case Instruction::MOD:
        ires = iv1 % iv2; break;
    case Instruction::AND:
        ires = iv1 & iv2; break;
    case Instruction::OR:
        ires = iv1 | iv2; break;
    case Instruction::XOR:
        ires = iv1 ^ iv2; break;
    default:
        cout << "default in evalConst()\n";
        break;
    }
    return isFloatOp?new IRValue(fres): new IRValue(ires);
}

bool ConstantPropagation::runOnFunction(Function& f) {
    getReachingDef(f);
    bool modified = true;
    // cout << "propogating...\n";
    while (modified) {
        modified = false;
        for (auto bb: f.basicBlocks()) {
            auto avalDefs = inDefs_[bb];
            unordered_map<int, set<IRValue*>> rid2Defs;
            for (IRValue*def: avalDefs) {
                rid2Defs[def->regNum()].insert(def);
            }
            set<int> overrided; 
            for (auto it=bb->begin(); it != bb->end(); ++it) {
                Instruction* inst = *it;
                if (inst->isMovInst()) {
                    IRValue* oprand = inst->getOprand(0);
                    if (oprand->isReg()){
                        auto & defs = rid2Defs[oprand->regNum()];
                        if (isDefConst(bb, defs, overrided)) {
                            IRValue* constant = def2Constant_[*defs.begin()];
                            inst->setOprand(0, constant);
                            oprand = constant;
                            modified = true;
                            // cout << "modified: " << inst->str() << "\n";
                        }
                    }
                    if (oprand->isConst() && !def2Constant_.count(inst)) {
                        IRValue* dstConstVal = oprand;
                        if (inst->opcode() == Instruction::MOVIF) {
                            dstConstVal = new IRValue((double)oprand->ival());
                        }
                        def2Constant_[inst] = dstConstVal;
                        modified = true;
                        // cout << "modified: " << inst->str() << "\n";
                    }
                } else  {
                    if (inst->opcode() == Instruction::JMPC) {
                        inst = (Instruction*)inst->getOprand(0);
                    }
                    vector<IRValue*> oprands = inst->getAllOprands();
                    for (size_t i=0; i<oprands.size(); i++) {
                        if (oprands[i] && oprands[i]->isReg() && oprands[i]->regNum() >= 0) {
                            auto & defs = rid2Defs[oprands[i]->regNum()];
                            if (isDefConst(bb, defs, overrided)) {
                                IRValue* constant = def2Constant_[*defs.begin()];
                                inst->setOprand(i, constant);
                                modified = true;
                                // cout << "modified: " << inst->str() << "\n";
                            }
                        }
                    }
                    if (inst->isArithInst()) {
                        auto oprand1=inst->getOprand(0), oprand2=inst->getOprand(1);
                        if (!def2Constant_.count(inst) && oprand1->isConst() && (!oprand2 || oprand2->isConst())) {
                            def2Constant_[inst] = evalConst(inst->opcode(), oprand1, oprand2);
                            modified = true;
                            // cout << "modified: " << inst->str() << "\n";
                            // optional
                            inst->opcode(inst->isFloatReg()?Instruction::MOVF:Instruction::MOVI);
                            inst->setOprand(0, def2Constant_[inst]);
                            if (inst->getOprand(1)) {
                                inst->popOprand();
                            }
                        }
                    }
                }
                if (inst->isReg() && inst->regNum() >=0) {
                    int rid = inst->regNum();
                    overrided.insert(rid);
                    for (auto def: rid2Defs[rid]) {
                        avalDefs.erase(def);
                    }
                    rid2Defs[rid].clear();
                    rid2Defs[rid].insert(inst);
                    avalDefs.insert(inst);
                } 
            }
        
        }
    }
   // cout << "propogating. OK\n";
    return true;
}

bool DeadCodeElimination::runOnFunction(Function& f) {
    bool modified = true;
    while (modified) {
        modified = false;
        f.livenessAnalysis();
        vector<BasicBlock*> toDel;
        for (auto bb: f.basicBlocks()) {
            set<int> liveNow = *bb->liveOut();
            BlockIterator bi = --(bb->end());
            bool quit = false;
            while (!quit) {
                if (bi == bb->begin())
                    quit = true;
                Instruction* inst = *bi;
                auto curIter = bi--;
                if (inst->opcode() == Instruction::JMPC) {
                    auto cmp = (Instruction*)inst->getOprand(0);
                    inst = cmp;
                }
                auto oprands = inst->getAllOprands();
                bool isDefAlive = true;
                if (inst->isReg() && inst->regNum() >= 0) {
                    isDefAlive = liveNow.count(inst->regNum());
                    liveNow.erase(inst->regNum());
                }
                if (isDefAlive) {
                    for (auto oprd: oprands) {
                        if (oprd && oprd->isReg() && oprd->regNum() >=0) {
                            liveNow.insert(oprd->regNum());
                        }
                    }
                } else {
                    //  cout << "deleted: " << inst->str() << "\n";
                    bb->deleteInst(curIter);
                    modified = true;
                    if (bb->empty()) {
                        toDel.push_back(bb);
                    }
                    
                }
                
            }
        }
        for (auto eb: toDel) {
            for (auto it=f.basicBlocks().begin(); it != f.basicBlocks().end(); ++it) {
                if (*it == eb) {
                    f.deleteEmptyBlock(eb);
                    break;
                }
            }
        }
    }

    // clean up consecutive jmps
    vector<BasicBlock*> toDel;
    for (auto bb: f.basicBlocks()) {
        auto inst = *(bb->begin());
        if (inst->opcode() == Instruction::JMP) {
            if ((bb->begin() != f.code()->begin())) {
                auto prev = *(--bb->begin());
                if (!prev->isJmpInst()) {
                    continue;
                }
            }
            auto tarName = inst->getOprand(0)->sval();
            IRValue* blockLabelVal = f.manager()->getLabel(bb->label());
            if (!blockLabelVal) {
                continue;
            }
            string blockLabelName = blockLabelVal->sval();
            bb->deleteInst(bb->begin());
            renameTargetLabel(blockLabelName, tarName, *f.code());
            toDel.push_back(bb);
            assert(bb->empty());
        } 
    }

    for (auto eb: toDel) {
        for (auto it=f.basicBlocks().begin(); it != f.basicBlocks().end(); ++it) {
            if (*it == eb) {
                f.deleteEmptyBlock(eb);
                break;
            }
        }
    }

    // delete wiped-out variables
    set<int> everUsed;
    for (auto inst: *f.code()) {
        if (inst->opcode() == Instruction::JMPC) {
            inst = (Instruction*)inst->getOprand(0);
        }
        auto oprands = inst->getAllOprands();
        for (auto oprd: oprands) {
            if (oprd && oprd->isReg() && oprd->regNum() >= 0) {
                everUsed.insert(oprd->regNum());
            }
        }
    }
    auto &rid2V = f.rid2IRValue();
    for (auto it=rid2V.begin(); it != rid2V.end(); ) {
        int rid = (*it).first;
        if (!everUsed.count(rid)) {
            it = rid2V.erase(it);
        } else {
            ++it;
        }
    }
    return true;
}
#include "IRGen.h"
#include "IR.h"

int IRGenManager::nextLabelID = 0;

void 
IRGenManager::checkAndSetSymReg(SymTabEntry* sym, IRValue* val) {
    if (!sym2VReg_.count(sym)) {
        sym2VReg_[sym] = val;
        val->regNum(nextTemp());
        rid2IRValue_[val->regNum()] = val;
    } else {
        val->regNum(sym2VReg_[sym]->regNum());
    }
}

IRValue* 
IRGenManager::nextLabel() { 
    string label = "L" + to_string(nextLabelID++);
    IRValue* lv = new IRValue(IRValue::LABEL, label);
    label2Val_[label] = lv;
    return lv;
}

void 
IRGenManager::setAsTemp(IRValue* v) {
    v->regNum(nextTemp());
    rid2IRValue_[v->regNum()] = v; 
}

void 
IRGenManager::setRegNum2Sym(int regNum, IRValue* v) {
    rid2IRValue_[regNum] = v;
}


void
renameTargetLabel(const string& oldName, const string& newName, list<Instruction*>&code) {
    for (auto inst: code) {
        if (inst->opcode() == Instruction::JMPC) {
            auto l1 = inst->getOprand(1), l2 = inst->getOprand(2);
            if (l1->sval() == oldName) {
                l1->sval(newName);
            } else if (l2->sval() == oldName) {
                l2->sval(newName);
            }
        } else if (inst->opcode() == Instruction::JMP) {
            auto l = inst->getOprand(0);
            if (l->sval() == oldName) {
                l->sval(newName); 
            }
        }
    }
}


void 
mergeLabels(IRGenManager* mgr, list<Instruction*>&code) {
    list<Instruction*>::iterator it = code.begin();
    IRValue* prevLabel = nullptr;
    while (it != code.end()) {
        auto curIt = it++;
        Instruction* inst = *curIt;
        if (inst->opcode() == Instruction::LABEL) {
            if (!prevLabel) {
                prevLabel = mgr->getLabel(inst->label());
            } else {
                // delete this label by renaming it
                IRValue* label = mgr->getLabel(inst->label());
                label->sval(prevLabel->sval());
                // delete label inst & the list elem holding it
                code.erase(curIt);
                delete inst;
            }
        } else if (prevLabel) {
            prevLabel = nullptr;
        }
    }
}

void
deleteUnreachable(list<Instruction*>&code) {
    auto it = code.begin();
    while (it != code.end()) {
        Instruction* inst = *it;
        if (inst->isReturnInst()) {
            ++it;
            while (it != code.end() &&
             !(*it)->isLabel()) {
                auto curIt = it++;
                code.erase(curIt);
            }
        } else {
            ++it;
        }
    }
    set<string> reachableLabels;
    Instruction* prev = nullptr;
    it = code.begin();
    // delete unreachable blocks
    while (it != code.end()) {
        Instruction* inst = *it;
        if (inst->opcode()==Instruction::JMPC) {
            auto l1 = inst->getOprand(1), l2 = inst->getOprand(2);
            reachableLabels.insert(l1->sval());
            reachableLabels.insert(l2->sval());
        } else if (inst->opcode()==Instruction::JMP) {
            reachableLabels.insert(inst->getOprand(0)->sval());
        } else if (inst->isLabel()) {
            bool reachable = !prev || (prev && !prev->isReturnInst() && !prev->isJmpInst()) || reachableLabels.count(inst->label());
            if (!reachable) {
                auto curLabel = it++;
                code.erase(curLabel);
                while (it != code.end() && !(*it)->isLabel()) {
                    auto curIt = it++;
                    code.erase(curIt);
                }
                continue;
            }
        }
        prev = inst;
        ++it;
    }
}

BasicBlock* 
CFGBuilder::getOrCreateBasicBlock(const string & label, Function* f) {
    if (!label2Block.count(label)) {
        BasicBlock* bb = new BasicBlock(f);
        label2Block[label] = bb;
        return bb;
    } else {
        return label2Block[label];
    }
}


/*
    build CFG for a given function
*/
BasicBlock* 
CFGBuilder::buildCFG(list<Instruction*> & code, Function* f) {
    if (!code.size()) return nullptr;
    BasicBlock* curBB = new BasicBlock(f);
    BasicBlock* entryBB = curBB;
    Instruction* prevInst = nullptr;
    CodeIterator entry = code.begin();
    if ((*entry)->isLabel()) {
        label2Block[(*entry)->label()] = curBB;
        curBB->label((*entry)->label());
        prevInst = *entry;
        ++entry;
    } else {
        curBB->firstInst(entry);
        curBB->label("%entry");
    }
    for(CodeIterator it=entry; it != code.end(); ++it) {
        Instruction* inst = *it;
        if (prevInst && prevInst->isLabel()) {
            curBB->firstInst(it);
            curBB->label(prevInst->label());
        }
        if (inst->opcode() == Instruction::LABEL) {
            string label = inst->label();
            BasicBlock* bb = getOrCreateBasicBlock(label, f);
            if (curBB && prevInst && !prevInst->isJmpInst() && !prevInst->isReturnInst()) {
                // fall through here
                curBB->succs().push_back(bb);
                bb->preds().push_back(curBB);
            }
            curBB->endInst(it);
            curBB = bb;
        } else if (inst->opcode() == Instruction::JMPC) {
            IRValue* l1 = inst->getOprand(1), *l2 = inst->getOprand(2);
            BasicBlock* tar1, *tar2;
            tar1 = getOrCreateBasicBlock(l1->sval(), f);
            tar2 = getOrCreateBasicBlock(l2->sval(), f);
            curBB->succs().push_back(tar1); curBB->succs().push_back(tar2);
            tar1->preds().push_back(curBB); tar2->preds().push_back(curBB);
        } else if (inst->opcode() == Instruction::JMP) {
            IRValue* l = inst->getOprand(0);
            BasicBlock* tar = getOrCreateBasicBlock(l->sval(), f);
            curBB->succs().push_back(tar);
            tar->preds().push_back(curBB);
        }
        prevInst = inst;
        
    }
    curBB->endInst(code.end());
    return entryBB;
}

Function* 
CFGBuilder::getFunctionCFG(list<Instruction*> & code, IRGenManager* mgr) {
    Function* f = new Function(&code, mgr);
    BasicBlock* entryBB =  buildCFG(code, f);
    if (!entryBB) return nullptr;
    
    // linearize the CFG for iteration use
    // broad first search
    list<BasicBlock*> workList;
    set<BasicBlock*> visited;
    workList.push_back(entryBB);
    visited.insert(entryBB);
    while (workList.size()) {
        BasicBlock* bb = workList.front();
        workList.pop_front();
        f->basicBlocks().push_back(bb);
        for (auto succBB: bb->succs()) {
            if (!visited.count(succBB)) {
                workList.push_back(succBB);
                visited.insert(succBB);
            }
        }
    }
    return f;
    
}
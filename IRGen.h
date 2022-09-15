#ifndef __IR_GEN_H__
#define __IR_GEN_H__

#include <string>
#include <unordered_map>
#include <stack>
#include <list>
using namespace std;

class Instruction;
class BasicBlock;
class Function;
class IRValue;
class SymTabEntry;

struct BranchInfo {
    IRValue* trueLabel;
    IRValue* falseLabel;
};

class IRGenManager {
private:
    int nextTempID_;
    unordered_map<SymTabEntry*, IRValue*> sym2VReg_; //map symbol entry to virtual register (x: r0)
    stack<BranchInfo> branchCtx_;
    unordered_map<string, IRValue*> label2Val_;
    unordered_map<int, IRValue*> rid2IRValue_;
    bool enableWarning_{false};
public:
    static int nextLabelID;
public:
    IRGenManager(bool enableWarning=true): nextTempID_(0), enableWarning_(enableWarning)  {}
    int nextTemp() { return nextTempID_++; }
    IRValue* nextLabel();
    IRValue* getLabel(string label) { 
        if (label2Val_.count(label)) return label2Val_[label];
        return nullptr;
    }
    void setSymReg(SymTabEntry* sym, IRValue* val) { sym2VReg_[sym]=val; }
    void setAsTemp(IRValue* v);
    void setRegNum2Sym(int regNum, IRValue* v);
    const unordered_map<int, IRValue*> & rid2Value() { return rid2IRValue_;}
    IRValue* getSymReg(SymTabEntry* sym) {
        if (!sym2VReg_.count(sym)) return nullptr;
        return sym2VReg_[sym]; 
    }
    BranchInfo& getBranchInfo() { return branchCtx_.top(); }
    void pushBranchInfo(const BranchInfo & binfo) { branchCtx_.push(binfo); }
    void popBranchInfo() { branchCtx_.pop(); }
    void checkAndSetSymReg(SymTabEntry* sym, IRValue* val);
    bool warnEnabled() const {return enableWarning_;}
};

void mergeLabels(IRGenManager* mgr, list<Instruction*>&code);
void deleteUnreachable(list<Instruction*>&code);
void renameTargetLabel(const string& oldName, const string& newName, list<Instruction*>&code);

class CFGBuilder {
public:
    CFGBuilder() {}
    ~CFGBuilder() {}
    BasicBlock* buildCFG(list<Instruction*> & code, Function* f);
    BasicBlock* getOrCreateBasicBlock(const string & label, Function* f);
    Function* getFunctionCFG(list<Instruction*> & code, IRGenManager* mgr);
    
private:
    unordered_map<string, BasicBlock*> label2Block;
};
#endif
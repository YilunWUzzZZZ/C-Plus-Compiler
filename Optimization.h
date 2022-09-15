#ifndef __OPTIMIZATION_H__
#define __OPTIMIZATION_H__
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;
class Function;
class BasicBlock;
class IRValue;
class Instruction;


class FunctionPass {
public:
    virtual bool runOnFunction(Function& f)=0;

};

class Optimizer {
public:
    Optimizer();
    ~Optimizer() {}
    bool optimize(Function& f);
    void registerPass(FunctionPass* p) {
        passes_.push_back(p);
    }
private:
    vector<FunctionPass*> passes_;
};


class ConstantPropagation: public FunctionPass {
public:
    ConstantPropagation() {}
    ~ConstantPropagation() {}
    bool runOnFunction(Function & f);
    void getReachingDef(Function & f);
    bool isDefConst(BasicBlock* bb, set<IRValue*> & defs, set<int>& overideDefs);

private:
    unordered_map<BasicBlock*, set<IRValue*>> inDefs_; // IRValue is the instruction defining that variable
    unordered_map<BasicBlock*, set<IRValue*>> outDefs_; // IRValue is the instruction defining that variable
    unordered_map<IRValue*, IRValue*> def2Constant_;
};


class DeadCodeElimination: public FunctionPass {
public:
    DeadCodeElimination() {}
    ~DeadCodeElimination() {}
    bool runOnFunction(Function&f);

    
};
#endif
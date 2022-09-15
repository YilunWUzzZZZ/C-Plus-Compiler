#ifndef __MEM_ALLOC_H__
#define __MEM_ALLOC_H__
#define RA_OFFSET 1 
#define RV_OFFSET 2
#define FIRST_PRAM_OFFSET 3
#include <stack>
#include <vector>
using namespace std;

class VariableEntry;

class MemAllocator {
public:
    MemAllocator(): nextHeapAddr_(0), nextStkOffset_(0) {}
    int allocOnStk(int size);
    int allocOnHeap(int size) { 
        int ret = nextHeapAddr_;
        nextHeapAddr_ += size;
        return ret; 
    }
    int maxDepth() { return maxDepth_; }
    vector<VariableEntry*>* arraysOnStk() { return &arrays_; }
    void leaveScope();
    void enterScope();
    void resetStk() { nextStkOffset_ = 0; maxDepth_=0; curDepth_=0; arrays_.clear();}

    
private:
    int nextHeapAddr_;
    int nextStkOffset_; // offset relative to BP, it's a negative number
    int maxDepth_{0};
    int curDepth_{0};
    std::stack<int> stkLenInScope_;
    vector<VariableEntry*> arrays_;
};


#endif
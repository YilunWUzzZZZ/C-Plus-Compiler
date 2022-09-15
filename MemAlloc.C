#include "MemAlloc.h"

int MemAllocator::allocOnStk(int size) {
    nextStkOffset_ += size;
    stkLenInScope_.top()+=size;
    curDepth_ += size;
    return nextStkOffset_;
}

void MemAllocator::leaveScope() {
    maxDepth_ = curDepth_ > maxDepth_ ? curDepth_:maxDepth_;
    curDepth_ -= stkLenInScope_.top();
    nextStkOffset_ -= stkLenInScope_.top();
    stkLenInScope_.pop();
}

void MemAllocator::enterScope() {
    stkLenInScope_.push(0);
}
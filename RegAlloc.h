#ifndef __REG_ALLOC_H__
#define __REG_ALLOC_H__
#include <unordered_map>
#include <vector>
#include <stack>
#include "IR.h"

using namespace std;


class InterGraph;
class IRValue;

class GraphNode {
    friend class InterGraph;
private:
    int nodeID_; // it's the same as virtual reg id
    int pRegID_; // allocated register id
    unordered_map<int, GraphNode*> neighbors_;
    
public:
    GraphNode(int vrid): nodeID_(vrid), pRegID_(-1) {}
    int degree() { return neighbors_.size(); }
    int nid() { return nodeID_; }
    unordered_map<int, GraphNode*> & neighbors() {return neighbors_;}
    void addNeighbor(GraphNode* n) {
        if (!neighbors_.count(n->nid()))
            neighbors_[n->nid()] = n;
    }
    void removeNeighbor(int nid) {
        neighbors_.erase(nid);
    }
    bool spilled() {return pRegID_ == -1;}
    int pRegID() { return pRegID_; }
    void pRegID(int id) { pRegID_=id; }
};

class InterGraph {
public:
    InterGraph() {}
    GraphNode* addNode(int nid);
    void addEdge(int n1, int n2);
    GraphNode* removeNode(int nid);
    void addNodeWithEdges(GraphNode* node);
    // degree >= k
    GraphNode* pickNode(int k);
    int size() {return nodes_.size();}
private:
    unordered_map<int, GraphNode*> nodes_;
};

class RegAllocator {
public:
    RegAllocator(int numRegs, int stkOff=1): numRegs_(numRegs), stkOff_(stkOff) {} 
    void addInterference(int r1, int r2);
    void addNode(int nid) { graph_.addNode(nid); }
    int stkOff() {return stkOff_;}
    void stkOff(int o) {stkOff_ = o;} 
    void allocate(unordered_map<int, IRValue*> &vreg2Val);
    unordered_map<int, int> & vReg2PReg() {return vReg2PReg_;}
    unordered_map<int, int> & vReg2StkOff() {return vReg2StkOff_;}
    bool spilled(int vregNum) { return vReg2PReg_[vregNum] == -1; }
    int  getStkOff(int vregNum) { return vReg2StkOff_.count(vregNum)?vReg2StkOff_[vregNum]:0; }
    int  getPhyRegNum(int vregNum) { return vReg2PReg_[vregNum]; }
private:
    InterGraph graph_;
    int numRegs_;
    int stkOff_;
    unordered_map<int, int> vReg2PReg_;
    unordered_map<int, int> vReg2StkOff_; // spilled
};


#endif
#include "RegAlloc.h"
#include "STEClasses.h"
#include <assert.h>
#include <set>
GraphNode*
InterGraph::addNode(int nid) {
    if (nodes_.count(nid)) {
        throw "duplicated nodes";
    }
    nodes_[nid] =  new GraphNode(nid);
    return nodes_[nid];
}

void 
InterGraph::addEdge(int n1, int n2) {
    if (n1 == n2) {
        cout << "can't add loop edge\n";
        return;
    }
    GraphNode* node1 = nodes_.count(n1)?nodes_[n1]:addNode(n1);
    GraphNode* node2 = nodes_.count(n2)?nodes_[n2]:addNode(n2);
    node1->addNeighbor(node2);
    node2->addNeighbor(node1);
}

GraphNode*
InterGraph::removeNode(int nid) {
    // remove node and all of its edges
    GraphNode* removed = nodes_[nid];
    for (auto n: removed->neighbors_) {
        n.second->removeNeighbor(removed->nid());
    }
    nodes_.erase(nid);
    return removed;
}

void 
InterGraph::addNodeWithEdges(GraphNode* node) {
    if (nodes_.count(node->nid())) {
        return;
    }
    nodes_[node->nid()] = node;
    for (auto n: node->neighbors_) {
        n.second->addNeighbor(node);
    }

}

GraphNode* 
InterGraph::pickNode(int k) {
    GraphNode* toRet=nullptr;
    for (auto n: nodes_) {
        if (n.second->degree() < k) {
            toRet = n.second;
            break;
        }
    }
    if (!toRet) {
        // pick one with degree >= k, and lowest priority, random for now
        for (auto n: nodes_) {
            if (n.second->degree() >= k) {
                toRet = n.second;
                break;
            }
        }
    }
    return toRet;
    
}

void
RegAllocator::addInterference(int n1, int n2) {
    graph_.addEdge(n1, n2);
}

void 
RegAllocator::allocate(unordered_map<int, IRValue*> &vreg2Val) {
    stack<GraphNode*> stk;
    int k = numRegs_;
    // k-coloring graph
    while (graph_.size()) {
        GraphNode* toRemove = graph_.pickNode(k);
        graph_.removeNode(toRemove->nid());
        stk.push(toRemove);
    }
    while (stk.size()) {
        GraphNode* n = stk.top();
        stk.pop();
        set<int> usedColor;
        for (auto p: n->neighbors()) {
             GraphNode* nbr = p.second;
             if (!nbr->spilled()) {
                 usedColor.insert(nbr->pRegID());
             } 
        }
        // color it
        int color = -1;
        for (int i=0; i<k; i++) {
            if (!usedColor.count(i)) {
                // free color
                color = i;
                break;
            }
        }
        n->pRegID(color);
        vReg2PReg_[n->nid()] = color; 
        // spill, allocate an offset for it, skip if it's a param
        IRValue* val = vreg2Val[n->nid()];
        if (color == -1) {
            if (!val->isTemprary()) {
                VariableEntry* var = (VariableEntry*)val->sym();
                if (var->varKind() == VarKind::FN_PARAM_VAR) {
                    vReg2StkOff_[n->nid()] = -var->stkOffset();
                    continue;
                }
            }
            vReg2StkOff_[n->nid()] = stkOff_++;
        } 
    }
}
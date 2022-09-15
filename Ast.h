#ifndef AST_H
#define AST_H

#include "all.h"
#include "Value.h"
#include "ProgramElem.h"
#include "ParserUtil.h"
#include <set>
#include <map>
#include <list>
#include <bitset>
#include <assert.h>
#include <sstream>

using namespace std;

class BlockEntry;
class FunctionEntry;
class OpNode;
class SymTabEntry;
class VariableEntry;
class ValueNode;
class IRGenManager;
class Instruction;
class MemAllocator;
class IRValue;
/*****************************************************************************
   Here is the class hierarchy:
                        ProgramElem
                             |
                          AstNode
                   +---------+-----------------------------------+
                   |                                             |
                  ExprNode                                   StmtNode
                   |                                             |
                   |                                             |
          +---------+----------+-----------+------------+        |
          |         |          |           |            |        |
      RefExprNode  OpNode  SizeOfNode  ValueNode  InvocationNode |
                                                                 |
                              +------------------------------------+------+
                              |                 |            |            |
                        ExprStmtNode   CompoundStmtNode   IfNode   ListForNode


******************************************************************************/

enum AstNodeType  {
   EXPR_NODE,
   STMT_NODE,
};


class AstNode: public ProgramElem {
 private:
  AstNodeType nodeType_;
  const AstNode* operator=(const AstNode& other); /* disable asg */

 public:
  AstNode(AstNodeType nt, int line=0, int column=0, string file="");
  virtual ~AstNode() {};


  AstNodeType nodeType() const { return nodeType_;}

  // Yan: 11/15
  virtual const Type* typeCheck() { return nullptr; }
  virtual void typePrint(ostream& os, int indent=0) const {};

  virtual void print(ostream& os, int indent=0) const=0;
  virtual IRValue* codeGen(IRGenManager* mgr, list<Instruction*>& code)=0;
  string prtString() const {
    stringstream s;
    print(s);
    return s.str();
  }
};

inline ostream& operator<<(ostream& os, const AstNode& an) {
  an.print(os);
  return os;
};

enum ExprNodeType {
   REF_EXPR_NODE,
   OP_NODE,
   SIZEOF_NODE,
   VALUE_NODE,
   INV_NODE
};

/****************************************************************/

class ExprNode: public AstNode {
 public:
 private:
  ExprNodeType exprType_;
  const Value *val_; // reference semantics for val_ and coercedType_
  const Type* coercedType_{nullptr};

 public:
  ExprNode(ExprNodeType et, const Value* val=0, int line=0, int col=0,
       string file=""); // val is saved, but not copied

  virtual ~ExprNode() {};

  ExprNodeType exprNodeType() const { return exprType_;};
  void exprNodeType(ExprNodeType t) { exprType_ = t; };

  const Value* value() const { return val_; }
  void value(const Value* v) { val_ = v; };

  // Yan 11/15 getter & setter for coercedType_ member
  const Type* getCoercedType() const { return coercedType_; }
  void setCoercedType(const Type* type) { coercedType_ = type; }

  virtual bool isConst() const { return false;};


};

/****************************************************************/
class RefExprNode: public ExprNode {
 private:
  RefExprNode* base_{nullptr};
  string ext_;
  vector<ExprNode*> *subscript_{nullptr};
  bitset<32> tupleSubs_; // @@@@ Max 32 subscripts!
  SymTabEntry* sym_;

 public:
  RefExprNode(RefExprNode* base, string ext, SymTabEntry* ste=nullptr,
        int line=0, int column=0, string file="");
  ~RefExprNode() {};


  const RefExprNode *base() const { return base_;};
  void base(RefExprNode* base) { base_ = base; };

  string ext() const { return ext_;};
  void ext(string str) { ext_ = str;};
  string fullName() const {
    if (base_ == nullptr) return ext_;
    else return base_->fullName() + "." + ext_;
  };

  const SymTabEntry* symTabEntry() const { return sym_;};
  SymTabEntry* symTabEntry() { return sym_;};
  void symTabEntry(SymTabEntry *ste)  { sym_ = ste;};

  // Yan: 11/15
  const Type* typeCheck();
  void typePrint(ostream& os, int indent=0) const;

  unsigned nsubs() const { return (subscript_? subscript_->size() : 0); };
  const ExprNode* subscript(unsigned int i) const
    { return (subscript_ != nullptr && i < subscript_->size())?
  (const ExprNode*)((*subscript_)[i]) : nullptr;  };
  ExprNode* subscript(unsigned int i)
    { return (subscript_ != nullptr && i < subscript_->size())?
       (*subscript_)[i] : nullptr;  };
  const vector<ExprNode*>* subscript() const { return subscript_; }
  vector<ExprNode*>* subscript() { return subscript_; };
  void addSubs(ExprNode* e);


  void print(ostream& os, int indent=0) const;
  IRValue* codeGen(IRGenManager* mgr, list<Instruction*>& code);
};

/****************************************************************/

class OpNode: public ExprNode {
 public:
  enum OpCode {
    UMINUS, PLUS, MINUS, MULT, DIV, MOD,
    EQ, NE, GT, LT, GE, LE,
    AND, OR, NOT,
    BITNOT, BITAND, BITOR, BITXOR,
    SHL, SHR,
    ASSIGN,
    EMPTY, CLEAR, LENGTH, APPEND, UNION, INS_SET,
    INS_VEC, ERASE, CONTAINS, REMOVE, CAT,
    TUPLE, VECTOR, SET, DICT,
    PRINT, PRINT_RAW,
    DUMMY_PROJECT,
    EQBIT,
    NEQBIT,
    INTERVAL,
    INVALID
  };


  static const int InverseOpCode[];

  enum OpPrintType {PREFIX, INFIX, POSTFIX};
  struct OpInfo {
    OpCode code_;
    const char* name_;
    int arity_;
  int needParen_;
    OpPrintType prtType_;
    Type::BaseTypeTag argType_[3]; // argType_[2] used for args 2..N
    Type::BaseTypeTag outType_;
    const char* typeConstraints;

  Type::BaseTypeTag argType(int i) const {
    if (i >= arity_) return Type::ERROR;
    if (i > 2) i = 2;

      for (; i >= 0; i--)
         if (argType_[i] > 0) return argType_[i];
      return Type::ERROR;
  }
  };

 private:
  unsigned int arity_;
  OpCode   opCode_;
  vector<ExprNode*> arg_;

 public:
  static const int VARIABLE = 100;

 public:
  OpNode(OpCode op, ExprNode *l, ExprNode *r=nullptr,
   int line=0, int column=0, string file="");
  OpNode(OpCode op, vector<ExprNode*>* args,
   int line =0, int column=0, string file="");
  ~OpNode() {};


  OpCode opCode() const { return opCode_;};
  const ExprNode* arg(unsigned int i) const
    { return (i < arg_.size())? arg_[i] : nullptr; };
  unsigned int arity() const { return arity_; }

  void opCode(OpCode a) { opCode_ = a; };
  ExprNode* arg(unsigned int i)
    { return (i < arg_.size())? arg_[i] : nullptr; };
  vector<ExprNode*>* args()
    { return &arg_; }

  // Yan: 11/15
  const Type* typeCheck();
  void typePrint(ostream& os, int indent=0) const;

  bool isConst() const {
     for (unsigned i=0; i < arg_.size(); i++)
        if (!arg_[i]->isConst()) return false;
     return true;
  };
  void print(ostream& os, int indent=0) const;
  IRValue* codeGen(IRGenManager* mgr, list<Instruction*>& code); 
};

extern const OpNode::OpInfo opInfo[];

/****************************************************************/

class SizeOfNode: public ExprNode {
 private:
  const SymTabEntry* ste_;

 public:
  SizeOfNode(const SymTabEntry* ste, int ln=0, int cl=0, string f="")
    : ExprNode(SIZEOF_NODE, 0,ln,cl, f) { ste_ = ste; }
  ~SizeOfNode() {};

  const SymTabEntry* symTabEntry() const { return ste_; };

  // Yan: 11/15
  const Type* typeCheck();
  void typePrint(ostream& os, int indent=0) const;

  bool isConst() const { return true;};

  void print(ostream& os, int indent=0) const;
  IRValue* codeGen(IRGenManager* mgr, list<Instruction*>& code) {return nullptr;}; 
};

/****************************************************************/

class ValueNode: public ExprNode {
 private:

 public:
  ValueNode(const Value* val=0, int line=0, int col=0, string file="")
    : ExprNode(VALUE_NODE, val, line, col, file) {
    if (val != nullptr) type((Type*)(val->type()));
  }
  ValueNode(const Value* val, AstNode* t)
    : ExprNode(VALUE_NODE, val, t->line(), t->column(), t->file()) {
    if (val != nullptr) type((Type*)(val->type()));
  }
  ~ValueNode() {};

  // Yan: 11/15
  const Type* typeCheck();
  void typePrint(ostream& os, int indent=0) const;

  bool isConst() const { return true;};

  void print(ostream& os, int indent=0) const;
  IRValue* codeGen(IRGenManager* mgr, list<Instruction*>& code); 

};


/****************************************************************/

class InvocationNode: public ExprNode {
  // Used to represent function invocation, module instantiation and
  // emitting of output events
 private:
  vector<ExprNode*>* params_;
  SymTabEntry *ste_;

 public:
  InvocationNode(SymTabEntry *ste, vector<ExprNode*>* param=0,
     int line=0, int column=0, string file="");
  ~InvocationNode() {};

  const SymTabEntry* symTabEntry() const { return ste_; };
  SymTabEntry* symTabEntry() { return ste_; };

  const vector<ExprNode*>* params() const { return params_;};
  vector<ExprNode*>* params() { return params_;}
  void params(vector<ExprNode*>* args){ params_ = args;};
  const ExprNode* param(unsigned int i) const
    { return (params_ != nullptr && i < params_->size())? (const ExprNode*)((*params_)[i]) : nullptr; };
  ExprNode* param(unsigned int i)
    { return (ExprNode*)(((const InvocationNode*)this)->param(i));}
  void param(ExprNode* arg, unsigned int i)
    { if (params_ != nullptr && i < params_->size()) (*params_)[i] = arg;};

  // Yan: 11/15
  const Type* typeCheck();
  void typePrint(ostream& os, int indent=0) const;

  void print(ostream& os, int indent=0) const;
  IRValue* codeGen(IRGenManager* mgr, list<Instruction*>& code);
};


/****************************************************************/

class StmtNode: public AstNode {
 public:
  enum StmtNodeKind { ILLEGAL=-1, EMPTY, EXPR, IF, COMPOUND, FORALL, WHILE, RETURN};

 private:
  StmtNodeKind skind_;

 public:
  StmtNode(StmtNodeKind skm, int line=0, int col=0, string file=""):
  AstNode(STMT_NODE, line,col,file) { skind_ = skm; };
  StmtNode( int line=0, int column=0, string file=""):
  AstNode(STMT_NODE, line,column,file) { skind_ = EMPTY; };
  ~StmtNode() {};

  StmtNodeKind stmtNodeKind() const { return skind_;}


  void print(ostream& os, int indent) const { os << ";" ;};
  virtual void memAlloc(MemAllocator* allocator) {}
  IRValue* codeGen(IRGenManager* mgr, list<Instruction*>& code) { return nullptr; }
};

/****************************************************************/

class ReturnStmtNode: public StmtNode {
 private:
  ExprNode* expr_;
  FunctionEntry* fun_;

 public:
  ReturnStmtNode(ExprNode *e, FunctionEntry* fe,
         int line=0, int column=0, string file=""):
    StmtNode(StmtNode::RETURN, line,column,file) { expr_ = e; fun_ = fe;};
  ~ReturnStmtNode() {};

  // Yan: 11/15
  const Type* typeCheck();
  void typePrint(ostream& os, int indent=0) const;

  void print(ostream& os, int indent) const;
  void memAlloc(MemAllocator* allocator) {}
  IRValue* codeGen(IRGenManager* mgr, list<Instruction*>& code);
};

/****************************************************************/
class ExprStmtNode: public StmtNode {
 private:
  ExprNode* expr_;

 public:
  ExprStmtNode(ExprNode* e,int line=0, int column=0, string file=""):
    StmtNode(StmtNode::EXPR, line,column,file) { expr_ = e; };
  ~ExprStmtNode() {};

  ExprNode* expr() { return expr_; };

  // Yan: 11/15
  const Type* typeCheck();
  void typePrint(ostream& os, int indent=0) const;

  void print(ostream& os, int indent) const;
  void memAlloc(MemAllocator* allocator) {}
  IRValue* codeGen(IRGenManager* mgr, list<Instruction*>& code);
};

/****************************************************************/
class CompoundStmtNode: public StmtNode {
 private:
  BlockEntry* decls_;
  list<StmtNode*>   *stmts_;

 public:
  CompoundStmtNode(BlockEntry* decls, list<StmtNode*> *s,
                   int l=0, int c=0, string f=""):
  StmtNode(StmtNode::COMPOUND, l, c, f) { decls_ = decls; stmts_ = s;};
  ~CompoundStmtNode() { };

  const BlockEntry* decls() const { return decls_; };
  const list<StmtNode*>* stmts() const { return stmts_;}

  BlockEntry* decls() { return decls_; };
  list<StmtNode*>* stmts() { return stmts_;}
  void add(StmtNode *s)
    { if(stmts_ != nullptr) stmts_->push_back(s); };

  void  emitWithoutBraces(ostream& os, int indent) const;

  // Yan: 11/15
  const Type* typeCheck();
  void typePrint(ostream& os, int indent=0) const;
  void typePrintWithoutBraces(ostream& os, int indent=0) const;

  void  print(ostream& os, int indent) const;
  void memAlloc(MemAllocator* allocator);
  IRValue* codeGen(IRGenManager* mgr, list<Instruction*>& code);
};

/****************************************************************/

class IfNode: public StmtNode {
 private:
  ExprNode *cond_;
  StmtNode *then_, *else_;

 public:
  IfNode(ExprNode* cond, StmtNode* thenStmt, StmtNode* elseStmt=nullptr,
         int line=0, int column=0, string file="");
  ~IfNode(){};

  const ExprNode* cond() const {return cond_;}
  const StmtNode* elseStmt() const { return else_;};
  const StmtNode* thenStmt() const  { return then_;};

  ExprNode* cond() {return cond_;}
  StmtNode* elseStmt() { return else_;};
  StmtNode* thenStmt() { return then_;};

  // Yan: 11/15
  const Type* typeCheck();
  void typePrint(ostream& os, int indent=0) const;

  void print(ostream& os, int indent) const;
  void memAlloc(MemAllocator* allocator);
  IRValue* codeGen(IRGenManager* mgr, list<Instruction*>& code);
};

/****************************************************************/

class ListForNode: public StmtNode {
 private:
  RefExprNode *indexVar_;
  ExprNode *list_;
  StmtNode *body_;

 public:
  ListForNode(RefExprNode* index, ExprNode* list, StmtNode* body=nullptr,
        int line=0, int column=0, string file=""):
  StmtNode(StmtNode::FORALL,line,column,file) {
  indexVar_ = index; list_ = list; body_ = body; }
  // ListForNode(const IfNode&); // @@@@ Inconsistent: default copy constructor
  ~ListForNode() {};

  const RefExprNode *indexVar() const { return indexVar_; };
  RefExprNode *indexVar() { return indexVar_; };

  const ExprNode *list() const { return list_; };
  ExprNode *list() { return list_; };

  const StmtNode* body() const { return body_; };
  StmtNode* body() { return body_; };
  void body(StmtNode* b) { body_ = b; };

  // Yan: 11/15
  const Type* typeCheck();
  void typePrint(ostream& os, int indent=0) const;
  void print(ostream& os, int indent) const;

  void memAlloc(MemAllocator* allocator);
  IRValue* codeGen(IRGenManager* mgr, std::list<Instruction*>& code);
};

/****************************************************************/

class WhileNode: public StmtNode {
 private:
  ExprNode *cond_;
  StmtNode *body_;

 public:
  WhileNode(ExprNode* cond, StmtNode* body=nullptr,
         int line=0, int column=0, string file=""):
  StmtNode(StmtNode::WHILE, line,column,file) {
  cond_ = cond; body_ = body; }
  ~WhileNode() {};

  const ExprNode *cond() const { return cond_; };
  ExprNode *cond() { return cond_; };

  const StmtNode* body() const { return body_; };
  StmtNode* body() { return body_; };
  void body(StmtNode* b) { body_ = b; };

  // Yan: 11/15
  const Type* typeCheck();
  void typePrint(ostream& os, int indent=0) const;

  void print(ostream& os, int indent) const;
  void memAlloc(MemAllocator* allocator);
  IRValue* codeGen(IRGenManager* mgr, list<Instruction*>& code);
};

/****************************************************************/

// utility functions

IRValue* evalConst(OpNode::OpCode op, IRValue* v1, IRValue*v2);
IRValue* checkTypeCoersion(IRValue* v, ExprNode* expr, IRGenManager* mgr, list<Instruction*> &code);
IRValue* inFuncCallCodeGen(string & fname, list<Instruction*>& code);
#endif

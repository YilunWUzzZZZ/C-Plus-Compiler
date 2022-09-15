#ifndef STE_CLASSES_H
#define STE_CLASSES_H

#include "SymTab.h"
#include "SymTabEntry.h"
#include "Ast.h"


class StmtNode;
class ExprNode;
class VariableEntry;
class OpNode;
class CompoundStmtNode;
class ICodeGenMgr;
class ICode;
class Function;
class RegAllocator;
class Instruction;
class MemAllocator;
class IRValue;

class GlobalEntry: public SymTabEntry {
 public:
  GlobalEntry(string name, int line=0, int column=0, string file=""):
    SymTabEntry(name, GLOBAL_KIND, line, column,file) {};
  ~GlobalEntry() {};
  void print(ostream&, int indent=0) const;
  void dbgPrint(ostream& os) const;
  // Functions for codeGen & memAlloc
  void memAlloc(MemAllocator* allocator);
  void emitICode(ostream & os);
  void codeGen();

  // Yan 11/16
  const Type* typeCheck();
  void typePrint(ostream& os, int indent=0) const;
};

class FunctionEntry: public SymTabEntry {
 private:
  int offset_;
  CompoundStmtNode* body_;
  string code_; // If code already emitted, the name of fn in generated code. 
  list<Instruction*> IR_;
  Function* cfg_{nullptr};
  vector<ICode*> ICode_;
 public:
  //for debug use
  RegAllocator* ira{nullptr}, *fra{nullptr};

 public:
  FunctionEntry(string name, Type* type=nullptr,
                int line=0, int column=0, string file=""):
    SymTabEntry(name, FUNCTION_KIND, line,column, file, type) {
    body_ = nullptr;
 };
  ~FunctionEntry() {};

  const CompoundStmtNode* body() const { return body_;};
  CompoundStmtNode* body() {return body_;};
  void body(CompoundStmtNode* n) { body_ = n;};

  void print(ostream& os, int indent) const;
  void dbgPrint(ostream& os) const;

  // Yan 11/16
  const Type* typeCheck();
  void typePrint(ostream& os, int indent=0) const;

  int offset() const { return offset_;}
  void offset(int o) { offset_ = o;}

  void memAlloc(MemAllocator* allocator);
  void emitICode();
  void ICodeGen(ICodeGenMgr* mgr);
  void codeGen();
  void cfg(Function* f) {cfg_=f;}
  Function* cfg() {return cfg_;}
  list<Instruction*>* IR() {return &IR_;}
  string code() {return code_;}
};

class EnumElemEntry: public SymTabEntry {
 private:
  int num_;

 public:
  EnumElemEntry(string nm, int n, Type*t=0,
                int ln=0, int col=0, string f=""):
    SymTabEntry(nm, ENUM_ELEM_KIND, ln, col, f, t), num_ (n) {};
  ~EnumElemEntry() {};

  int num() const { return num_;};
  void num(int i) {num_= i;};

  void print(ostream& os, int indent) const { os << name();};

  // Yan 11/16
  const Type* typeCheck() { return new Type(Type::UINT); }
  void typePrint(ostream& os, int indent=0) const { type()->print(os, indent); }

  //
  void memAlloc(MemAllocator* allocator) {}
};


class VariableEntry: public SymTabEntry {
 private:
  VarKind vkind_;
  ExprNode* offset_;
  ExprNode* initVal_;
  vector<ExprNode*> subscripts_;// used if variable is an array.

  union {
    int stkOffset_;
    int heapOffset_;
  };
  bool isStatic_{false};
  bool isVLA_{false};
  vector<IRValue*> dims_;
  vector<IRValue*> dimProducts_;
  IRValue* arraySize_;
 public:
  VariableEntry(string name, VarKind v, Type* type=nullptr, ExprNode* init=0,
                int ln=0, int col=0, string file=""):
    SymTabEntry(name, VARIABLE_KIND, ln, col, file, type) {
    vkind_ = v; offset_ = nullptr; initVal(init);
 };

  ~VariableEntry() {};

  VarKind varKind() const { return vkind_;};
  void varKind(VarKind v) { vkind_ = v;};

  const ExprNode* offset() const { return offset_;}
  ExprNode* offset() { return offset_;}
  void offset(ExprNode* offset) { offset_ = offset;};

  const ExprNode* initVal() const { return initVal_;}
  ExprNode* initVal() { return initVal_;};
  void initVal(ExprNode *init) { initVal_ = init;};

  unsigned int nSubscripts() const { return subscripts_.size();};
  const ExprNode* subscript(unsigned int i) const {
    if (subscripts_.size() > i) return subscripts_[i]; else return nullptr;
  }
  ExprNode* subscript(unsigned int i) {
    if (subscripts_.size() > i) return subscripts_[i]; else return nullptr;
  }
  void addSubscript(ExprNode* e) { subscripts_.push_back(e);}

  void print(ostream& os, int indent=0) const;

  // Yan 11/16
  const Type* typeCheck();
  void typePrint(ostream& os, int indent=0) const;

  int stkOffset() const { return stkOffset_; }
  void stkOffset(int offset) { stkOffset_=offset; }
  
  int heapOffset() const { return heapOffset_; }
  void heapOffset(int offset) { heapOffset_=offset; isStatic_=true; }

  bool isStatic() { return isStatic_;}
  bool isVLA() { return isVLA_;}
  void isVLA(bool is) { isVLA_=is; }
  vector<IRValue*> *dims() {return &dims_;}
  vector<IRValue*> *dimProducts() { return &dimProducts_; }
  IRValue* arraySize() { return arraySize_;}
  void arraySize(IRValue* sz) { arraySize_ = sz;}
  void memAlloc(MemAllocator* allocator) {}

};

class EnumEntry: public SymTabEntry {
 private:
  vector<EnumElemEntry*>* elems_;

 public:
  EnumEntry(string name, int ln=0, int column=0, string filename=""):
    SymTabEntry(name, ENUM_KIND, ln,column, filename) {
    elems_ = new vector<EnumElemEntry*>();
 }
  ~EnumEntry() {};

  const vector<EnumElemEntry*>* elems() const { return elems_;};
  int nelems() const { return elems_->size();}

  vector<EnumElemEntry*>* elems() {return elems_;};
  void addElem(EnumElemEntry* ste) {
    elems_->push_back(ste);
 };

  void print(ostream& os, int indent) const;

  // Yan 11/16
  const Type* typeCheck();
  void typePrint(ostream& os, int indent=0) const;

  void memAlloc(MemAllocator* allocator) {}

 private:
  EnumEntry& operator=(EnumEntry&);
};

class BlockEntry: public SymTabEntry {
 public:
  BlockEntry(string name, int ln=0, int col=0, string file=""):
    SymTabEntry(name, BLOCK_KIND, ln, col, file, (Type*)&Type::voidType) {};
  ~BlockEntry() {};
  void print(ostream& out, int indent=0) const;

  // Yan 11/16
  const Type* typeCheck();
  void typePrint(ostream& os, int indent=0) const;
  
  void memAlloc(MemAllocator* allocator);
};


#endif

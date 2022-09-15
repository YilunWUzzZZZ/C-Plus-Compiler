#ifndef STE_H
#define STE_H

#include "SymTab.h"
#include "Value.h"
#include "ProgramElem.h"
#include <set>

class SymTabEntry;
class ExprNode;

class SymTabEntry: public ProgramElem {
 public:
  static vector<SymTab*> symTabs_;
  enum SymKind {
   UNKNOWN_KIND,
   GLOBAL_KIND,FUNCTION_KIND,
   VARIABLE_KIND,
   ENUM_KIND, ENUM_ELEM_KIND,
   BLOCK_KIND,
   ERROR_KIND
  };

 private:
  string name_;
  SymTabEntry::SymKind kind_;
  SymTab* st_;
  SymTabEntry* next_;
  SymTabEntry* prev_;
  SymTab* parent_;

 public:
  /*****************************************************************
  The implementation of this class, as well its descendents.
  makes definite assumptions about the use of kind, name, prev, next
  and the symbol table fields. As such, methods operating on these
  fields are non-virtual. (Overriding them in subclasses is strongly
  discouraged.) All other operations are virtual, whether or not
  we can see any potential use of overriding them.
  ****************************************************************/

  SymTabEntry(string name, SymKind kind,
              int line, int column, string file, const Type* t=nullptr);
  virtual ~SymTabEntry() {};

  string name() const { return name_; }
  SymTabEntry::SymKind kind() const { return kind_; }
  const SymTab* symTab() const { return st_; };
  const SymTabEntry* prev()const { return prev_ ;};
  const SymTabEntry* next()const  { return next_ ;};

  void name(string str) { name_=str; };
  void kind(SymKind kind) { kind_ = kind; };
  SymTab* symTab() { return st_; };
  void prev(SymTabEntry *se) { prev_ = se; }
  SymTabEntry* prev() { return prev_ ;};
  void next(SymTabEntry *se) { next_ = se; }
  SymTabEntry* next()  { return next_ ;};
  void parent(SymTab *s) { parent_ = s; }
  SymTab* parent()  { return parent_ ;};

  ErrorST insert(SymTabEntry* ste) {
    if(st_ == nullptr) {
       st_ = new SymTab(this);
       symTabs_.push_back(st_);
    }
    return st_->insert(ste);
  }

  virtual ExprNode* storageAlloc();

  virtual bool operator==(const SymTabEntry&) const;
  virtual bool operator!=(const SymTabEntry& ste) const
  { return !operator==(ste); };

  virtual void print(ostream& os, int indent=0)  const = 0;

  // Yan: 11/16
  virtual const Type* typeCheck() { return nullptr; }
  virtual void typePrint(ostream& os, int indent=0) const {};

  virtual void emitST(ostream& os,int ind=0,char ldelim='{',char rdelim='}',
             bool linebreaks=true, int first=0, int last=0) const {
    if (symTab() != nullptr)
    symTab()->emitST(os, ind, ldelim, rdelim, linebreaks, first,last);
  }

 private:
  const SymTabEntry& operator=(const SymTabEntry&);
};

inline ostream& operator<<(ostream& out, const SymTabEntry* ste){
  ste->print(out, 0);
  return out;
}
#endif

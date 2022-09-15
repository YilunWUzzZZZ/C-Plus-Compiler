#ifndef  SymTabMgr_H
#define  SymTabMgr_H

#include "SymTabEntry.h"

const static int MAX_SCOPE_STACK_SIZE = 10000;

enum ErrorIT {EMPTY_STACK, NO_PROBLEM};

class SymTabMgr {
 public:
  SymTabMgr();
  virtual ~SymTabMgr();

  const SymTabEntry* lookUp(string name) const;
  const SymTabEntry* lookUpWithInheritance(string name) const;
  const SymTabEntry* lookUpInScope(string name, SymTabEntry::SymKind k) const;
  const SymTabEntry* currentScope() const;
  const SymTabEntry* currentScope(SymTabEntry::SymKind) const;

  SymTabEntry* lookUp(string name)
    {return (SymTabEntry*)(((const SymTabMgr*)this)->lookUp(name));}
  SymTabEntry* lookUpInScope(string name, SymTabEntry::SymKind k)
    {return (SymTabEntry*)(((const SymTabMgr*)this)->lookUpInScope(name,k));}
  SymTabEntry* lookUpWithInheritance(string name)  
    {return (SymTabEntry*)(((const SymTabMgr*)this)->lookUpWithInheritance(name)); }
  SymTabEntry* currentScope()
    {return (SymTabEntry*)(((const SymTabMgr*)this)->currentScope());}
  SymTabEntry* currentScope(SymTabEntry::SymKind k)
    {return (SymTabEntry*)(((const SymTabMgr*)this)->currentScope(k));}

  ErrorST enterScope(SymTabEntry *ste);
  ErrorST enterNameSpace(SymTabEntry* ste);
  ErrorST leaveScope();
  ErrorST leaveScope(SymTabEntry::SymKind k);
  ErrorST leaveToScope(SymTabEntry::SymKind k);
  ErrorST insert(SymTabEntry *ste);

 private:
  const SymTabMgr& operator=(const SymTabMgr&); 
  SymTabMgr(const SymTabMgr&);

 private: 
  int top_; 
  SymTabEntry* scopeStack_[MAX_SCOPE_STACK_SIZE];
  bool isNameSpace_[MAX_SCOPE_STACK_SIZE];
};

extern SymTabMgr stm;
#endif

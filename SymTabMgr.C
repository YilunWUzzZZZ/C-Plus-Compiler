#include "SymTabMgr.h"
#include "STEClasses.h"

SymTabMgr::SymTabMgr(){
  top_ = 0;
  scopeStack_[top_] = new GlobalEntry(string("GLOBAL")) ;
  isNameSpace_[top_] = false;
}

SymTabMgr::~SymTabMgr() { 
}

/* look up throughout the whole file */
const SymTabEntry* 
SymTabMgr::lookUp(string name) const {
  const SymTabEntry *ste = 0;
  for (int i = top_; i >= 0; i--) {
    const SymTab* st = scopeStack_[i]->symTab();
    if ((st != nullptr) && ((ste = st->lookUp(name)) != nullptr))
      break;
  }
  return ste;
}

/* Totally no use, super spicy chicken */
const SymTabEntry*
SymTabMgr::lookUpWithInheritance(string name) const {
  const SymTabEntry* ste = currentScope();
  return nullptr;
}

/* look in the current SymKind k scope */
const SymTabEntry* 
SymTabMgr::lookUpInScope(string name, SymTabEntry::SymKind k) const {
  const SymTabEntry *ste = currentScope(k);
  if ((ste != nullptr) && (ste->symTab() != nullptr)) {
    ste = ste->symTab()->lookUp(name);
    return ste;
  }
  else return nullptr;
}

/* current scope*/
const SymTabEntry* 
SymTabMgr::currentScope() const {
  for (int i = top_; i >= 0; i--) {
    if (!isNameSpace_[i]) 
      return scopeStack_[i];
  }
  return nullptr;
} 

/* find current scope of SymKind k*/
const SymTabEntry* 
SymTabMgr::currentScope(SymTabEntry::SymKind k) const {
  for (int i = top_; i >= 0; i--) {
    if (scopeStack_[i]->kind() == k) 
      return scopeStack_[i];
  }
  return nullptr;
} 

/* enter a scope identified by symtabentry ste */
ErrorST 
SymTabMgr::enterScope(SymTabEntry* ste){
  if (ste == nullptr)
    return INVALID_SCOPE;
  if (++top_ >= MAX_SCOPE_STACK_SIZE) {
    errMsg("Too many nested levels of scope, exiting");
    exit(-1);
  }
  scopeStack_[top_] = ste;
  isNameSpace_[top_] = false;
  return OK;
}

/* maybe no use, cuz we don't have namespace */
ErrorST 
SymTabMgr::enterNameSpace(SymTabEntry* ste){
  ErrorST rv = enterScope(ste);
  isNameSpace_[top_] = true;
  return rv;
}

/* leave current scope, and go to the outter scope */
ErrorST 
SymTabMgr::leaveScope() {
  if (top_ > 0) {
    top_--;
    return OK;
  }
  return INVALID_SCOPE;
}

/* keep leaving scopes untill go out of the nearest outter scope of SymKind kind */
// maybe no use
ErrorST 
SymTabMgr::leaveScope(SymTabEntry::SymKind kind) {
  ErrorST rv = leaveToScope(kind);
  if (rv == OK)  
  return leaveScope();
  else return rv;
    }

/* keep leaving scope untill go to the nearest outter scope of SymKind kind */
// maybe no use
ErrorST 
SymTabMgr::leaveToScope(SymTabEntry::SymKind kind) {
  ErrorST rv=OK;
  for (int i = top_; (i > 0) && (scopeStack_[i]->kind() != kind); i--)
  rv = leaveScope();
  return rv;
}

/* insert a symtabentry se in current scope, don't mind the isNameSpace */
// will return DUPLICATE_SYM, OK, or INVALID_SCOPE (refer to insert method in SymTab class)
ErrorST 
SymTabMgr::insert(SymTabEntry* se) { 
  for (int i=top_; i >= 0; i--) 
    if (scopeStack_[i] != nullptr && !isNameSpace_[i])
      return (scopeStack_[i]->insert(se));
  
  return INVALID_SCOPE;
}


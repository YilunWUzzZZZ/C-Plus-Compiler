#include "SymTabEntry.h"
#include "Ast.h"

vector<SymTab*> SymTabEntry::symTabs_;

static const char* const kindtag[] = {
  "UNKNOWN_KIND",
  "GLOBAL_KIND",
  "ENUM_KIND","FUNCTION_KIND", 
  "VARIABLE_KIND", 
  "BLOCK_KIND",
  "ERROR_KIND"
};

string kindTag(SymTabEntry::SymKind k) {
  if ((k >= 0) && (k < SymTabEntry::SymKind::ERROR_KIND))
    return kindtag[k];
  else return kindtag[SymTabEntry::SymKind::ERROR_KIND];
}

SymTabEntry::SymTabEntry(string name, SymTabEntry::SymKind k, 
       int lineno, int columnno, string filename, const Type *t) 
  : ProgramElem(t, lineno, columnno, filename) {
  name_ = name;
  kind_ = k;
  if (type() == nullptr)
    type(new Type(Type::voidType));
  st_ = nullptr;
  next_ = prev_ = nullptr;
}

bool 
SymTabEntry::operator==(const SymTabEntry& ste)const {
  return (&ste == this);
}

ExprNode *
SymTabEntry::storageAlloc() {
  SymTab *st = symTab();
  ExprNode *rv = nullptr;
  if (st != nullptr) {
    for (SymTab::iterator it = st->begin(); (it != st->end()); ++it) {
      ExprNode *s = (*it)->storageAlloc();
      if (s != nullptr) {
         if (rv == nullptr)
            rv = s;
         else rv = new OpNode(OpNode::PLUS, rv, s);
      }
    }
  }
  return rv;
}

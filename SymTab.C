#include "all.h"
#include "SymTab.h"
#include "SymTabEntry.h"
#include "STEClasses.h"

SymTab::SymTab(SymTabEntry* parent):map_() {
  first_ = last_ = nullptr;
  parent_ = parent;
}

const SymTabEntry* 
SymTab::lookUp(string name) const {
  auto it = map_.find(name);
  if (it != map_.end()) 
     return it->second; 
  else return nullptr;
}

ErrorST 
SymTab::insert(SymTabEntry* se) {
  if (map_.count(se->name()) > 0)
    return DUPLICATE_SYM;
  else {
    map_[se->name()] = se;
    se->parent(this);
    se->next(nullptr);
    se->prev(last_);
    if (map_.size() == 1)
      first_ = se;
	else last_->next(se);
   last_ = se;
    }
  return OK;
}

SymTab::iterator&
SymTab::iterator::operator++ () {
 if (current != nullptr)  
   current = current->next();
 return *this; 
}

SymTab::const_iterator&
SymTab::const_iterator::operator++ () {
  if (current != nullptr) 
    current = current->next();
  return *this; 
}

void
emitST1(const vector<SymTabEntry*>& stev, ostream& os, int indent, 
        char leftdelim, char rightdelim, bool linebreak, 
        int first, int last) {
  int i; auto it = stev.begin(); int n_printed=0;

   if ((first == 0) && (last == 0))
      last = 1000000;

   for (i=0; (it != stev.end()) && (i < last); i++, ++it)  {
      SymTabEntry *ste = *it;
      if (i >= first) {
         if (ste->kind() != SymTabEntry::SymKind::ENUM_ELEM_KIND) {
            n_printed++;
         }
      }
   }

   if (leftdelim != '\0') {
      os << leftdelim;
      if ((n_printed > 0) && (linebreak))
         prtln(os, indent+STEP_INDENT);
   }

   for (i=0, it=stev.begin();
        (it != stev.end()) && (i < last); i++, ++it)  {
      SymTabEntry *ste = *it;
      if (i >= first) {
		 if (ste->kind() != SymTabEntry::SymKind::ENUM_ELEM_KIND && (ste->kind()
					 != SymTabEntry::SymKind::BLOCK_KIND)) {
            ste->print(os,indent+STEP_INDENT);
            if ((leftdelim == '\0') && (rightdelim != '\0'))
               os << rightdelim;
            if (--n_printed > 0) {
               if (linebreak)
                  prtln(os,indent+STEP_INDENT);
               else os << ", ";
            }
            else if (linebreak)
               prtln(os,indent);
         }
      }
   }

   if (leftdelim != '\0') 
      os << rightdelim; 
}

void 
SymTab::emitST(ostream& os, int indent, char leftdelim, char rightdelim, 
				bool linebreak, int first, int last) const {
   SymTab::const_iterator it = begin();
   vector<SymTabEntry*> svec;
   for (; it != end(); ++it) 
      svec.push_back((SymTabEntry *)(*it));

   emitST1(svec, os, indent, leftdelim, rightdelim, linebreak, first, last);
}

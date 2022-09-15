#ifndef __PARSER_UTIL_H__
#define __PARSER_UTIL_H__

#include "SymTabEntry.h"
#include "SymTabMgr.h"
#include "STEClasses.h"

extern SymTabMgr stm;
ErrorST insertSymbolErrCheck(SymTabEntry* se);
void enterScopeErrCheck(SymTabEntry*);
void enterNameSpaceErrCheck(SymTabEntry*);

unsigned int atoui(const char *);
string itoa(int i);
string newName(string type);

#endif

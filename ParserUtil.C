#include "ParserUtil.h"
#include "Error.h"

static int variableCount = 1;
extern int yycolumnno;

static void 
errPrint(ErrorST code, const string& sym) {
  switch (code) {
  case DUPLICATE_SYM:
	errMsgLn("Redefinition of name " + sym);
	break;
  case SYM_NOT_PRESENT:
	errMsgLn("Undeclared symbol `" + sym + "'");
	break;
  case INVALID_SCOPE:
	errMsgLn("Definition of `" + sym +"' is invalid in " + 
		   stm.currentScope()->name());
	break;
  default:
	break;
  }
}

ErrorST insertSymbolErrCheck(SymTabEntry* se) {
  ErrorST err = stm.insert(se);
  errPrint(err, se->name());
  return err;
}

void enterScopeErrCheck(SymTabEntry* se) {
  errPrint(stm.enterScope(se), se->name());
}

void enterNameSpaceErrCheck(SymTabEntry* se) {
  errPrint(stm.enterNameSpace(se), se->name());
} 

void leaveScopeErrCheck() {
  if (stm.leaveScope() != OK)
    errMsg("Invalid leave scope");
} 

string itoa(int i) {
  char b[64];
  sprintf(b, "%d", i);
  return string(b);
}


string newName(string type) {
  string s("__");
  s +=type+"__"+ itoa(variableCount++);
  return s;
}


#include <iostream>
#include "ProgramElem.h"

using namespace std;

static int errorCount = 0;
static int warningCount = 0;

void msg(const string& type, const string& errorMsg, int line, int col, string file) {
	if (line == 0) {
    line = yylinenum;
    file = yyfilename;
  }
  cerr << file << ':' << line;
  if (col != 0)
    cerr << '.' << col;
  cerr << ':';
  cerr << type << errorMsg << endl;

}

void 
internalError(const string& s, int line, string file) {
  msg("Internal error: ", s, line, 0, file);
}

void errMsg(string errorMsg, int line, int col, string file) {
  msg("Error: ", errorMsg, line, col, file);
  errorCount++;
  if (errorCount > MAX_ERROR_BEFORE_QUIT) {
    cerr << endl << "Too many errors.  Exiting ... " << endl;
    exit(-1);
  }
}

void errMsg(string msg, const ProgramElem* p) {
  if (p == NULL)
    errMsg(msg);
  else errMsg(msg, p->line(), p->column(), p->file());
}

void warnMsg(string warningMsg, int line, int col, string file) {
  msg("Warning: ", warningMsg, line, col, file);
  warningCount++;
}

void warnMsg(string msg , const ProgramElem* p) {
  if (p == NULL)
    warnMsg(msg);
  else warnMsg(msg, p->line(), p->column(), p->file().c_str());
}

void resetErrs() {
  warningCount = errorCount = 0;
}

void resetWarns() {
  warningCount = 0;
}

int warnCount() {
  return warningCount;
}

int errCount() {
  return errorCount;
}

struct ErrInfo {
   char level;
   int col;
   int line;
   string file;
   string msg;
};

static vector<ErrInfo> bufErrs;

#define ERR 10
#define WARN 0

void bufErr(string s, const ProgramElem* pe) {
   bufErrs.push_back(ErrInfo{ERR, pe->column(), pe->line(), pe->file(), s});
}

void bufWarn(string s, const ProgramElem* pe) {
   bufErrs.push_back(ErrInfo{WARN, pe->column(), pe->line(), pe->file(), s});
}

void prtBufMsgs() {
  for (auto m: bufErrs) {
     if (m.level == ERR)
        errMsg(m.msg, m.line, m.col, m.file);
     else warnMsg(m.msg, m.line, m.col, m.file);
  }
  bufErrs.clear();
}

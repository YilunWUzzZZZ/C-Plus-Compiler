#include <libgen.h>
#include <unistd.h>

#include <iostream>
#include <fstream>
#include "all.h"
#include "Ast.h"
#include <stdio.h>
#include "SymTabMgr.h"
#include "STEClasses.h"
#include "SymTab.h"
#include "Value.h"
#include "MemAlloc.h"

using namespace std;

#include "C+_parser.H"

#define CPP_PROG_NAME "CPP" // Environment variable to specify location of cpp
#define DEFAULT_CPP_PROG_NAME "cpp"
#define CC_PROG_NAME "CC" // Environment variable to specify C compiler
#define DEFAULT_CC_PROG_NAME "gcc -g"
#define CC_PROG_OPTS "CFLAGS"

#define MAX_DEBUG_LEVEL 2

#ifdef DEBUG_LEXER
#ifdef LEXER_OUT
ofstream lexOutStr(LEXER_OUT);
ostream& lexOut = lexOutStr;
#else
ostream& lexOut = cout;
#endif
#endif

extern int yyparse();
extern int yylinenum;
extern const char* yyfilename;
extern YYSTYPE yylval;

void yyerror(const char *s)
{
  errMsg(s);
}

SymTabMgr stm;
string outputFile;
const char* inputFile = "";
string cppShellCmd, ccShellCmd;

int debugLevel;
int optLevel = 0;
bool genCCode;
bool genBinCode;
bool genSharedLib;
bool genDottyCode;
bool genPrologCode;
string outFileSuffix;
extern bool debugOn;
extern FILE* yyin;

void
printUsage(const char* cmd) {
  cerr << "Usage: " << cmd <<
	"[-I include_dir] [-L<library directory>]\n   [-l<library>]"
    "[-Dmacro[=defn]] [-Uname] "
    "[-o <output file>] <input file>\n"
    "Environment variable CPP can be used to override the default command\n"
    "for running cpp program. This variable can include the program name\n"
    "as well as command-line arguments to the command. Similarly, the\n"
    "environment variable CC can specify the command to be run for compiling\n"
    "C code produced by this compiler, but the options to the compiler can\n"
    "specified independently using the environment variable CFLAGS.\n";
}

int
parseOptions(int argc, char* argv[]) {
  opterr = 0; // Suppress printing of errors by getopt.

  if (getenv(CPP_PROG_NAME) == NULL)
	cppShellCmd = DEFAULT_CPP_PROG_NAME;  else cppShellCmd = getenv(CPP_PROG_NAME);
  cppShellCmd += " ";

  if (getenv(CC_PROG_NAME) == NULL)
	ccShellCmd = DEFAULT_CC_PROG_NAME;
  else ccShellCmd = getenv(CC_PROG_NAME);
  ccShellCmd += " ";
  if (getenv(CC_PROG_OPTS) != NULL) {
	ccShellCmd += getenv(CC_PROG_OPTS);
	ccShellCmd += " ";
  }

  while (1) {
	if (argc < 2) {
		cerr << "Please specify only a single input file\n";
		return -1;
	}
	else {
	  inputFile = argv[1];
    if (argc > 2) {
      for (int i=2; i<argc; i++) {
        if (strlen(argv[i]) >= 2 && argv[i][0] == '-' ) {
          if (argv[i][1]=='O') {
            optLevel = 1;
          } else if (argv[i][1] == 'o' && i+1 < argc) {
            outputFile= argv[i+1];
            outputFile += ".i";
            i++;
          }
        } 
      }
    }
	  return 0;
	}
  }

  genSharedLib = !(genCCode || genBinCode || genDottyCode || genPrologCode);
  if (genSharedLib)
	outFileSuffix = ".so";

  if (*inputFile == '\0')
    return -1;

  if (outputFile == "") {
	size_t pos;
	if (genSharedLib) {
	  string sinputFile(inputFile);
	  if ((pos = sinputFile.rfind('/')) == string::npos)
		outputFile = "lib" + sinputFile;
	  else outputFile =
			 sinputFile.substr(0, pos) + "/lib" + sinputFile.substr(pos+1);
	}
	else outputFile = inputFile;

	if ((pos = outputFile.rfind('.')) != outputFile.npos)
	  outputFile.replace(pos, outputFile.size(), outFileSuffix);
	else outputFile += outFileSuffix;
  }

  return 0;
}

int
main(int argc, char *argv[], char *envp[]) {

  string ccCmd;
  int optionsOK = parseOptions(argc, argv);
  if (optionsOK < 0)
	return -1;

  cppShellCmd += inputFile;
  cppShellCmd += " ";

  if ((yyin = popen(cppShellCmd.c_str(), "r")) == NULL) {
    cerr << "Unexpected error in reading input file\n";
    return 1;
  }

#ifdef TEST_LEXER
  int token;

  while (token = yylex()) {
	if (token == TOK_SYNTAX_ERROR) {
	  cout << yyfilename << ":" << yylinenum
		   << ": Error: Unrecognized token `" << yytext << "'\n";
	}
	else {
      cout << "Token: " << token << " ";
      switch(token)
        {
        case TOK_UINTNUM:
          cout << "Attribute: (int) " << yylval.uVal;
          break;

        case TOK_DOUBLENUM:
          cout << "Attribute: (float) " << yylval.dVal;
          break;

        case TOK_STRCONST:
          cout << "Attribute: (string) " << yylval.cVal;
          break;

        case TOK_ID:
          cout << "Attribute: (id) " << yylval.cVal;
          break;

        default:
          break;
        }
      cout << endl;
	}
  }

  return 0;
#else
  yyparse();
  stm.leaveToScope(SymTabEntry::GLOBAL_KIND);
  GlobalEntry *ge = (GlobalEntry*)(stm.currentScope());
  if (ge != nullptr && !errCount() ) {
    ge->typeCheck();
  } else {
    return 0;
  }
  if (!errCount()) {
	//cout << "Finished parsing, here is the AST\n";
	//ge->typePrint(cout, 0);
    MemAllocator gma;
    ge->memAlloc(&gma);
    ge->codeGen();
    if (debugOn) {
      cout << "Finished parsing, here is the IR\n";
      ge->dbgPrint(cout);
      cout << "\nGenerated Machine Code:\n\n";
    }
    ofstream ofs;
    if (outputFile.size()) {
      ofs.open(outputFile, ios::out|ios::trunc);
      if (!ofs.is_open())  {
        cout << "Can't open file " << outputFile << "\n";
        return 0;
      }
      ge->emitICode(ofs);
      ofs.close();
    } else {
      ge->emitICode(cout);
    }
    
  
  }
#endif
}

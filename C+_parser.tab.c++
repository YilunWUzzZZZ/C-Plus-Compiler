/* A Bison parser, made by GNU Bison 3.7.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "C+_parser.y++"

#include <iostream>
#include "Ast.h"
#include <string.h>
#include <assert.h>
#include <vector>
#include "ParserUtil.h"
#include "STEClasses.h"

#define prt(x) cout << x << endl;

extern int yylex();
extern void yyerror(const char *s);
using namespace std;


#line 88 "C+_parser.tab.c++"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOK_LEX_ERROR = 258,           /* TOK_LEX_ERROR  */
    TOK_COLON = 259,               /* TOK_COLON  */
    TOK_COMMA = 260,               /* TOK_COMMA  */
    TOK_DOT = 261,                 /* TOK_DOT  */
    TOK_SEMICOLON = 262,           /* TOK_SEMICOLON  */
    TOK_LBRACK = 263,              /* TOK_LBRACK  */
    TOK_RBRACK = 264,              /* TOK_RBRACK  */
    TOK_LPAREN = 265,              /* TOK_LPAREN  */
    TOK_RPAREN = 266,              /* TOK_RPAREN  */
    TOK_LBRACE = 267,              /* TOK_LBRACE  */
    TOK_RBRACE = 268,              /* TOK_RBRACE  */
    TOK_PLUS = 269,                /* TOK_PLUS  */
    TOK_MINUS = 270,               /* TOK_MINUS  */
    TOK_UMINUS = 271,              /* TOK_UMINUS  */
    TOK_MULT = 272,                /* TOK_MULT  */
    TOK_DIV = 273,                 /* TOK_DIV  */
    TOK_ASSIGN = 274,              /* TOK_ASSIGN  */
    TOK_AND = 275,                 /* TOK_AND  */
    TOK_OR = 276,                  /* TOK_OR  */
    TOK_NOT = 277,                 /* TOK_NOT  */
    TOK_GT = 278,                  /* TOK_GT  */
    TOK_LT = 279,                  /* TOK_LT  */
    TOK_EQ = 280,                  /* TOK_EQ  */
    TOK_NE = 281,                  /* TOK_NE  */
    TOK_GE = 282,                  /* TOK_GE  */
    TOK_LE = 283,                  /* TOK_LE  */
    TOK_MOD = 284,                 /* TOK_MOD  */
    TOK_ARROW = 285,               /* TOK_ARROW  */
    TOK_QMARK = 286,               /* TOK_QMARK  */
    TOK_BITAND = 287,              /* TOK_BITAND  */
    TOK_BITOR = 288,               /* TOK_BITOR  */
    TOK_BITNOT = 289,              /* TOK_BITNOT  */
    TOK_BITXOR = 290,              /* TOK_BITXOR  */
    TOK_SHL = 291,                 /* TOK_SHL  */
    TOK_SHR = 292,                 /* TOK_SHR  */
    TOK_CHAR = 293,                /* TOK_CHAR  */
    TOK_BIT = 294,                 /* TOK_BIT  */
    TOK_BOOL = 295,                /* TOK_BOOL  */
    TOK_SHORT = 296,               /* TOK_SHORT  */
    TOK_INT = 297,                 /* TOK_INT  */
    TOK_LONG = 298,                /* TOK_LONG  */
    TOK_UNSIGNED = 299,            /* TOK_UNSIGNED  */
    TOK_CONST = 300,               /* TOK_CONST  */
    TOK_DOUBLE = 301,              /* TOK_DOUBLE  */
    TOK_ELSE = 302,                /* TOK_ELSE  */
    TOK_ENUM = 303,                /* TOK_ENUM  */
    TOK_FALSE = 304,               /* TOK_FALSE  */
    TOK_IF = 305,                  /* TOK_IF  */
    TOK_IN = 306,                  /* TOK_IN  */
    TOK_PRINT = 307,               /* TOK_PRINT  */
    TOK_PRINTR = 308,              /* TOK_PRINTR  */
    TOK_RETURN = 309,              /* TOK_RETURN  */
    TOK_STRING = 310,              /* TOK_STRING  */
    TOK_TRUE = 311,                /* TOK_TRUE  */
    TOK_VOID = 312,                /* TOK_VOID  */
    TOK_LIST = 313,                /* TOK_LIST  */
    TOK_SET = 314,                 /* TOK_SET  */
    TOK_TUPLE = 315,               /* TOK_TUPLE  */
    TOK_DICT = 316,                /* TOK_DICT  */
    TOK_FOREACH = 317,             /* TOK_FOREACH  */
    TOK_WHILE = 318,               /* TOK_WHILE  */
    TOK_DO = 319,                  /* TOK_DO  */
    TOK_EMPTY = 320,               /* TOK_EMPTY  */
    TOK_CLEAR = 321,               /* TOK_CLEAR  */
    TOK_LENGTH = 322,              /* TOK_LENGTH  */
    TOK_APPEND = 323,              /* TOK_APPEND  */
    TOK_UNION = 324,               /* TOK_UNION  */
    TOK_INSERT = 325,              /* TOK_INSERT  */
    TOK_ERASE = 326,               /* TOK_ERASE  */
    TOK_CONTAINS = 327,            /* TOK_CONTAINS  */
    TOK_REMOVE = 328,              /* TOK_REMOVE  */
    TOK_IP = 329,                  /* TOK_IP  */
    TOK_UINTNUM = 330,             /* TOK_UINTNUM  */
    TOK_DOUBLENUM = 331,           /* TOK_DOUBLENUM  */
    TOK_STRCONST = 332,            /* TOK_STRCONST  */
    TOK_ID = 333,                  /* TOK_ID  */
    TOK_ULONGNUM = 334,            /* TOK_ULONGNUM  */
    NEG = 335                      /* NEG  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 18 "C+_parser.y++"

  unsigned int       uVal;
  unsigned long      lVal;
  double             dVal;
  char*              cVal;
  vector<string>*    strVector;
  Value*             valVal;

  ExprNode*          exprVal;
  vector<ExprNode*>* exprList;
  RefExprNode*       refexpVal;

  EnumEntry*         enumEntry;
  vector<EnumElemEntry*>* enumElemList;
  Type*              typeVal;
  vector<Type*>*     typeList;

  VariableEntry*     variableEntry;
  FunctionEntry*     functionEntry;
  BlockEntry*        blockEntry;

  StmtNode*          stmtVal;
  ListForNode*       listForVal;
  WhileNode*         whileVal;
  IfNode*	      ifval;
  list<StmtNode*>*   stmtList;
  CompoundStmtNode*  compoundStmtVal;

  //OnEntry*           onVal;

  vector<Type*>*     formalTypeVal;
  const OpNode::OpInfo*    funIval;

#line 249 "C+_parser.tab.c++"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);


/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOK_LEX_ERROR = 3,              /* TOK_LEX_ERROR  */
  YYSYMBOL_TOK_COLON = 4,                  /* TOK_COLON  */
  YYSYMBOL_TOK_COMMA = 5,                  /* TOK_COMMA  */
  YYSYMBOL_TOK_DOT = 6,                    /* TOK_DOT  */
  YYSYMBOL_TOK_SEMICOLON = 7,              /* TOK_SEMICOLON  */
  YYSYMBOL_TOK_LBRACK = 8,                 /* TOK_LBRACK  */
  YYSYMBOL_TOK_RBRACK = 9,                 /* TOK_RBRACK  */
  YYSYMBOL_TOK_LPAREN = 10,                /* TOK_LPAREN  */
  YYSYMBOL_TOK_RPAREN = 11,                /* TOK_RPAREN  */
  YYSYMBOL_TOK_LBRACE = 12,                /* TOK_LBRACE  */
  YYSYMBOL_TOK_RBRACE = 13,                /* TOK_RBRACE  */
  YYSYMBOL_TOK_PLUS = 14,                  /* TOK_PLUS  */
  YYSYMBOL_TOK_MINUS = 15,                 /* TOK_MINUS  */
  YYSYMBOL_TOK_UMINUS = 16,                /* TOK_UMINUS  */
  YYSYMBOL_TOK_MULT = 17,                  /* TOK_MULT  */
  YYSYMBOL_TOK_DIV = 18,                   /* TOK_DIV  */
  YYSYMBOL_TOK_ASSIGN = 19,                /* TOK_ASSIGN  */
  YYSYMBOL_TOK_AND = 20,                   /* TOK_AND  */
  YYSYMBOL_TOK_OR = 21,                    /* TOK_OR  */
  YYSYMBOL_TOK_NOT = 22,                   /* TOK_NOT  */
  YYSYMBOL_TOK_GT = 23,                    /* TOK_GT  */
  YYSYMBOL_TOK_LT = 24,                    /* TOK_LT  */
  YYSYMBOL_TOK_EQ = 25,                    /* TOK_EQ  */
  YYSYMBOL_TOK_NE = 26,                    /* TOK_NE  */
  YYSYMBOL_TOK_GE = 27,                    /* TOK_GE  */
  YYSYMBOL_TOK_LE = 28,                    /* TOK_LE  */
  YYSYMBOL_TOK_MOD = 29,                   /* TOK_MOD  */
  YYSYMBOL_TOK_ARROW = 30,                 /* TOK_ARROW  */
  YYSYMBOL_TOK_QMARK = 31,                 /* TOK_QMARK  */
  YYSYMBOL_TOK_BITAND = 32,                /* TOK_BITAND  */
  YYSYMBOL_TOK_BITOR = 33,                 /* TOK_BITOR  */
  YYSYMBOL_TOK_BITNOT = 34,                /* TOK_BITNOT  */
  YYSYMBOL_TOK_BITXOR = 35,                /* TOK_BITXOR  */
  YYSYMBOL_TOK_SHL = 36,                   /* TOK_SHL  */
  YYSYMBOL_TOK_SHR = 37,                   /* TOK_SHR  */
  YYSYMBOL_TOK_CHAR = 38,                  /* TOK_CHAR  */
  YYSYMBOL_TOK_BIT = 39,                   /* TOK_BIT  */
  YYSYMBOL_TOK_BOOL = 40,                  /* TOK_BOOL  */
  YYSYMBOL_TOK_SHORT = 41,                 /* TOK_SHORT  */
  YYSYMBOL_TOK_INT = 42,                   /* TOK_INT  */
  YYSYMBOL_TOK_LONG = 43,                  /* TOK_LONG  */
  YYSYMBOL_TOK_UNSIGNED = 44,              /* TOK_UNSIGNED  */
  YYSYMBOL_TOK_CONST = 45,                 /* TOK_CONST  */
  YYSYMBOL_TOK_DOUBLE = 46,                /* TOK_DOUBLE  */
  YYSYMBOL_TOK_ELSE = 47,                  /* TOK_ELSE  */
  YYSYMBOL_TOK_ENUM = 48,                  /* TOK_ENUM  */
  YYSYMBOL_TOK_FALSE = 49,                 /* TOK_FALSE  */
  YYSYMBOL_TOK_IF = 50,                    /* TOK_IF  */
  YYSYMBOL_TOK_IN = 51,                    /* TOK_IN  */
  YYSYMBOL_TOK_PRINT = 52,                 /* TOK_PRINT  */
  YYSYMBOL_TOK_PRINTR = 53,                /* TOK_PRINTR  */
  YYSYMBOL_TOK_RETURN = 54,                /* TOK_RETURN  */
  YYSYMBOL_TOK_STRING = 55,                /* TOK_STRING  */
  YYSYMBOL_TOK_TRUE = 56,                  /* TOK_TRUE  */
  YYSYMBOL_TOK_VOID = 57,                  /* TOK_VOID  */
  YYSYMBOL_TOK_LIST = 58,                  /* TOK_LIST  */
  YYSYMBOL_TOK_SET = 59,                   /* TOK_SET  */
  YYSYMBOL_TOK_TUPLE = 60,                 /* TOK_TUPLE  */
  YYSYMBOL_TOK_DICT = 61,                  /* TOK_DICT  */
  YYSYMBOL_TOK_FOREACH = 62,               /* TOK_FOREACH  */
  YYSYMBOL_TOK_WHILE = 63,                 /* TOK_WHILE  */
  YYSYMBOL_TOK_DO = 64,                    /* TOK_DO  */
  YYSYMBOL_TOK_EMPTY = 65,                 /* TOK_EMPTY  */
  YYSYMBOL_TOK_CLEAR = 66,                 /* TOK_CLEAR  */
  YYSYMBOL_TOK_LENGTH = 67,                /* TOK_LENGTH  */
  YYSYMBOL_TOK_APPEND = 68,                /* TOK_APPEND  */
  YYSYMBOL_TOK_UNION = 69,                 /* TOK_UNION  */
  YYSYMBOL_TOK_INSERT = 70,                /* TOK_INSERT  */
  YYSYMBOL_TOK_ERASE = 71,                 /* TOK_ERASE  */
  YYSYMBOL_TOK_CONTAINS = 72,              /* TOK_CONTAINS  */
  YYSYMBOL_TOK_REMOVE = 73,                /* TOK_REMOVE  */
  YYSYMBOL_TOK_IP = 74,                    /* TOK_IP  */
  YYSYMBOL_TOK_UINTNUM = 75,               /* TOK_UINTNUM  */
  YYSYMBOL_TOK_DOUBLENUM = 76,             /* TOK_DOUBLENUM  */
  YYSYMBOL_TOK_STRCONST = 77,              /* TOK_STRCONST  */
  YYSYMBOL_TOK_ID = 78,                    /* TOK_ID  */
  YYSYMBOL_TOK_ULONGNUM = 79,              /* TOK_ULONGNUM  */
  YYSYMBOL_NEG = 80,                       /* NEG  */
  YYSYMBOL_81_chooseStmt_ = 81,            /* "chooseStmt"  */
  YYSYMBOL_YYACCEPT = 82,                  /* $accept  */
  YYSYMBOL_specification = 83,             /* specification  */
  YYSYMBOL_global_decl_star = 84,          /* global_decl_star  */
  YYSYMBOL_global_decl = 85,               /* global_decl  */
  YYSYMBOL_enum = 86,                      /* enum  */
  YYSYMBOL_enum_elem_list = 87,            /* enum_elem_list  */
  YYSYMBOL_type = 88,                      /* type  */
  YYSYMBOL_known_type = 89,                /* known_type  */
  YYSYMBOL_unknown_type = 90,              /* unknown_type  */
  YYSYMBOL_primary_type = 91,              /* primary_type  */
  YYSYMBOL_builtin_type = 92,              /* builtin_type  */
  YYSYMBOL_list_type = 93,                 /* list_type  */
  YYSYMBOL_set_type = 94,                  /* set_type  */
  YYSYMBOL_tuple_type = 95,                /* tuple_type  */
  YYSYMBOL_type_sequence = 96,             /* type_sequence  */
  YYSYMBOL_dict_type = 97,                 /* dict_type  */
  YYSYMBOL_var_decl = 98,                  /* var_decl  */
  YYSYMBOL_single_var = 99,                /* single_var  */
  YYSYMBOL_var_sequence = 100,             /* var_sequence  */
  YYSYMBOL_expr_literal = 101,             /* expr_literal  */
  YYSYMBOL_expr_ref = 102,                 /* expr_ref  */
  YYSYMBOL_single_ref = 103,               /* single_ref  */
  YYSYMBOL_expr_index = 104,               /* expr_index  */
  YYSYMBOL_expr_assignment = 105,          /* expr_assignment  */
  YYSYMBOL_expr_func = 106,                /* expr_func  */
  YYSYMBOL_expr_param = 107,               /* expr_param  */
  YYSYMBOL_expr_plus = 108,                /* expr_plus  */
  YYSYMBOL_expr_set = 109,                 /* expr_set  */
  YYSYMBOL_expr_list = 110,                /* expr_list  */
  YYSYMBOL_expr_dict = 111,                /* expr_dict  */
  YYSYMBOL_expr_tuple = 112,               /* expr_tuple  */
  YYSYMBOL_expr = 113,                     /* expr  */
  YYSYMBOL_builtin_func = 114,             /* builtin_func  */
  YYSYMBOL_stat = 115,                     /* stat  */
  YYSYMBOL_stat_if = 116,                  /* stat_if  */
  YYSYMBOL_stat_empty = 117,               /* stat_empty  */
  YYSYMBOL_stat_func = 118,                /* stat_func  */
  YYSYMBOL_stat_assign = 119,              /* stat_assign  */
  YYSYMBOL_stat_return = 120,              /* stat_return  */
  YYSYMBOL_stat_for = 121,                 /* stat_for  */
  YYSYMBOL_stat_while = 122,               /* stat_while  */
  YYSYMBOL_stat_comp = 123,                /* stat_comp  */
  YYSYMBOL_block_enter = 124,              /* block_enter  */
  YYSYMBOL_block_leave = 125,              /* block_leave  */
  YYSYMBOL_var_decl_list = 126,            /* var_decl_list  */
  YYSYMBOL_var_decl_list_2 = 127,          /* var_decl_list_2  */
  YYSYMBOL_stat_comp_body = 128,           /* stat_comp_body  */
  YYSYMBOL_stat_bad_body = 129,            /* stat_bad_body  */
  YYSYMBOL_bad_body = 130,                 /* bad_body  */
  YYSYMBOL_bad_body_star = 131,            /* bad_body_star  */
  YYSYMBOL_stat_sequence = 132,            /* stat_sequence  */
  YYSYMBOL_func = 133,                     /* func  */
  YYSYMBOL_func_head = 134,                /* func_head  */
  YYSYMBOL_func_decl = 135,                /* func_decl  */
  YYSYMBOL_func_const_decl = 136,          /* func_const_decl  */
  YYSYMBOL_func_body = 137,                /* func_body  */
  YYSYMBOL_func_param = 138,               /* func_param  */
  YYSYMBOL_formal_param = 139              /* formal_param  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1231

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  82
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  187
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  340

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   336


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   120,   120,   122,   123,   126,   127,   128,   129,   135,
     145,   146,   147,   148,   151,   161,   174,   175,   178,   179,
     182,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   200,   201,   202,   203,   206,   209,
     212,   213,   216,   217,   220,   225,   232,   240,   241,   242,
     245,   279,   315,   316,   320,   321,   322,   323,   324,   325,
     328,   329,   332,   343,   346,   347,   350,   361,   362,   365,
     366,   369,   372,   375,   378,   381,   382,   383,   384,   385,
     386,   387,   388,   389,   390,   391,   392,   393,   394,   395,
     396,   397,   398,   399,   400,   401,   402,   403,   404,   405,
     406,   407,   408,   409,   410,   411,   414,   422,   430,   438,
     446,   454,   464,   472,   480,   488,   489,   495,   496,   497,
     498,   499,   500,   501,   502,   503,   506,   507,   508,   509,
     512,   515,   516,   519,   528,   532,   536,   539,   540,   541,
     544,   545,   549,   555,   556,   559,   566,   567,   570,   571,
     574,   575,   578,   581,   590,   593,   594,   603,   609,   620,
     623,   626,   630,   636,   645,   656,   657,   659,   660,   661,
     662,   663,   664,   665,   668,   669,   671,   672,   673,   674,
     675,   676,   677,   680,   683,   684,   687,   697
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TOK_LEX_ERROR",
  "TOK_COLON", "TOK_COMMA", "TOK_DOT", "TOK_SEMICOLON", "TOK_LBRACK",
  "TOK_RBRACK", "TOK_LPAREN", "TOK_RPAREN", "TOK_LBRACE", "TOK_RBRACE",
  "TOK_PLUS", "TOK_MINUS", "TOK_UMINUS", "TOK_MULT", "TOK_DIV",
  "TOK_ASSIGN", "TOK_AND", "TOK_OR", "TOK_NOT", "TOK_GT", "TOK_LT",
  "TOK_EQ", "TOK_NE", "TOK_GE", "TOK_LE", "TOK_MOD", "TOK_ARROW",
  "TOK_QMARK", "TOK_BITAND", "TOK_BITOR", "TOK_BITNOT", "TOK_BITXOR",
  "TOK_SHL", "TOK_SHR", "TOK_CHAR", "TOK_BIT", "TOK_BOOL", "TOK_SHORT",
  "TOK_INT", "TOK_LONG", "TOK_UNSIGNED", "TOK_CONST", "TOK_DOUBLE",
  "TOK_ELSE", "TOK_ENUM", "TOK_FALSE", "TOK_IF", "TOK_IN", "TOK_PRINT",
  "TOK_PRINTR", "TOK_RETURN", "TOK_STRING", "TOK_TRUE", "TOK_VOID",
  "TOK_LIST", "TOK_SET", "TOK_TUPLE", "TOK_DICT", "TOK_FOREACH",
  "TOK_WHILE", "TOK_DO", "TOK_EMPTY", "TOK_CLEAR", "TOK_LENGTH",
  "TOK_APPEND", "TOK_UNION", "TOK_INSERT", "TOK_ERASE", "TOK_CONTAINS",
  "TOK_REMOVE", "TOK_IP", "TOK_UINTNUM", "TOK_DOUBLENUM", "TOK_STRCONST",
  "TOK_ID", "TOK_ULONGNUM", "NEG", "\"chooseStmt\"", "$accept",
  "specification", "global_decl_star", "global_decl", "enum",
  "enum_elem_list", "type", "known_type", "unknown_type", "primary_type",
  "builtin_type", "list_type", "set_type", "tuple_type", "type_sequence",
  "dict_type", "var_decl", "single_var", "var_sequence", "expr_literal",
  "expr_ref", "single_ref", "expr_index", "expr_assignment", "expr_func",
  "expr_param", "expr_plus", "expr_set", "expr_list", "expr_dict",
  "expr_tuple", "expr", "builtin_func", "stat", "stat_if", "stat_empty",
  "stat_func", "stat_assign", "stat_return", "stat_for", "stat_while",
  "stat_comp", "block_enter", "block_leave", "var_decl_list",
  "var_decl_list_2", "stat_comp_body", "stat_bad_body", "bad_body",
  "bad_body_star", "stat_sequence", "func", "func_head", "func_decl",
  "func_const_decl", "func_body", "func_param", "formal_param", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336
};
#endif

#define YYPACT_NINF (-142)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-146)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -142,    15,   791,  -142,  -142,  -142,  -142,  -142,  -142,  -142,
    -142,   189,   947,  -142,     9,  -142,  -142,    19,    49,    27,
    -142,  -142,    67,    89,  -142,  -142,  -142,  -142,  -142,  -142,
    -142,  -142,  -142,   380,   178,   191,  -142,  -142,  -142,  -142,
    -142,   -39,  -142,    53,  -142,    30,   441,   947,    17,    93,
    -142,  -142,    11,  -142,   101,   834,    -5,    84,   947,   -33,
     137,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,    24,
     158,  -142,    59,    12,   130,   -23,   125,    69,  -142,   875,
     171,  -142,  -142,   832,   177,   110,  -142,   150,   145,   168,
    -142,  -142,   -21,  -142,   169,   899,   174,   706,   208,   208,
    -142,  -142,  -142,    56,  -142,    88,  -142,   947,  -142,   947,
    -142,   149,   213,   832,   832,   832,   832,   832,   832,  -142,
     216,   218,  -142,   223,   226,   231,   233,   234,   236,   240,
     241,   245,  -142,  -142,  -142,  -142,   247,  -142,    25,  -142,
    -142,  -142,  -142,  -142,  -142,  -142,  -142,  1122,  -142,  -142,
     239,  -142,  -142,   214,  -142,  -142,  -142,  -142,  -142,  -142,
      10,   947,   832,   300,    13,   378,   325,   121,  -142,    25,
     253,   254,   255,  -142,  -142,  -142,  -142,  -142,  -142,  -142,
    -142,  -142,   706,   256,  -142,  -142,   186,  -142,  -142,   -23,
      73,   220,   221,   258,   263,  1122,  1024,   259,   995,  -142,
    1170,   314,   832,   832,   832,   832,   832,   832,   832,   832,
     832,   832,   832,   832,   832,   456,   832,   832,   832,   832,
     832,   832,   832,   832,   832,   832,   832,   832,   832,   832,
     832,   832,   832,   832,  -142,   260,    75,   662,   262,  -142,
    1048,  -142,  -142,   243,   238,   528,   288,  -142,  -142,  -142,
    -142,  -142,   706,  -142,   923,  -142,  -142,  -142,  -142,  -142,
    -142,   832,   832,  -142,  -142,   832,   287,   292,   293,   294,
     295,   298,   302,   305,   306,   309,   312,   313,  1073,  -142,
    1122,   106,   106,  -142,  -142,  1170,  1146,  1194,  1194,  1194,
    1194,  1194,  1194,  -142,   314,   282,   282,   154,   154,  -142,
     280,  -142,  -142,   832,   318,   318,  -142,  -142,   750,   138,
    -142,  1122,   326,  1098,  -142,  -142,  -142,  -142,  -142,  -142,
    -142,  -142,  -142,  -142,  -142,  -142,  -142,   139,   595,  -142,
    -142,  -142,  -142,   323,  -142,   750,  -142,   331,  -142,  -142
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     2,     1,     8,    26,    27,    21,    23,    25,
      24,     0,     0,    28,     0,    22,    29,     0,     0,     0,
       4,     5,     0,    16,    17,    18,    19,    34,    35,    36,
      37,     7,     6,     0,     0,     0,    31,    33,    30,    32,
      20,     0,    16,     0,    11,     0,     0,     0,     0,     0,
      38,    39,    50,    52,     0,     0,   169,   166,     0,     0,
       0,   184,   159,   145,   183,   148,   161,   160,   162,    50,
       0,    13,     0,     0,     0,    42,     0,     0,    47,     0,
       0,    49,   163,     0,     0,     0,    45,   171,     0,   167,
     178,   175,     0,   186,   168,     0,   165,     0,     0,     0,
     164,    46,    14,     0,    12,     0,    41,     0,    40,     0,
     173,     0,     0,    67,     0,    67,     0,     0,     0,    59,
       0,     0,    58,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    55,    54,    56,    57,    62,    97,    98,    60,
      61,    99,   100,   101,   102,   103,   104,    51,   105,    48,
      50,    53,   180,   170,   176,   187,   177,   185,   174,   130,
       0,     0,     0,     0,     0,     0,     0,     0,   149,     0,
       0,     0,     0,   157,   117,   118,   119,   120,   121,   123,
     124,   122,   152,   146,   143,   144,     0,    10,     9,    43,
       0,   172,     0,     0,    68,    69,     0,     0,    69,    76,
      77,    75,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   179,     0,     0,     0,     0,   135,
       0,   139,    62,     0,     0,     0,     0,   133,   131,   132,
     150,   158,     0,   155,   153,   147,    15,    44,   181,   182,
      72,     0,    67,    78,    71,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    65,
      64,    96,    89,    92,    91,    94,    87,    86,    82,    83,
      90,    84,    81,    95,    93,    88,    79,    80,    85,   125,
     126,   136,   134,     0,     0,     0,   141,   151,   154,     0,
     156,    70,     0,     0,   115,   116,   106,   107,   108,   109,
     110,   111,   112,   113,   114,    66,    63,     0,     0,   142,
     140,    74,    73,     0,   127,     0,   138,   129,   137,   128
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -142,  -142,  -142,  -142,  -142,   266,     0,   338,  -142,  -142,
    -142,  -142,  -142,  -142,  -142,  -142,     1,   257,   -36,  -142,
     -93,   181,  -142,   -90,   -88,   -92,  -142,  -142,  -142,  -142,
    -142,    60,   -79,  -141,  -142,  -142,  -142,  -142,  -142,  -142,
    -142,   -34,  -142,   242,  -142,  -142,  -142,  -142,    92,  -142,
      95,  -142,  -142,  -142,  -142,   319,   -47,   264
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    20,    21,   103,    59,    42,    24,    25,
      26,    27,    28,    29,    76,    30,   250,    53,    54,   137,
     138,   139,   140,   141,   142,   193,   194,   143,   144,   145,
     146,   195,   148,   173,   174,   175,   176,   177,   178,   179,
     180,   181,    65,   184,    97,   252,    98,    99,   253,   254,
     182,    32,    33,    34,    35,    66,    60,    61
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      64,    64,    22,    31,   169,    70,    89,   170,    88,   171,
      43,   235,    41,   104,   241,     3,    44,  -145,   172,    50,
      51,    82,  -145,   197,    78,    50,    51,    79,    48,    46,
      83,    72,   111,   214,   100,    50,    51,    50,    51,    69,
      90,   251,    73,    83,   215,    93,    75,    77,  -145,  -145,
    -145,  -145,  -145,  -145,  -145,  -145,  -145,   155,    92,    47,
    -145,   186,  -145,  -145,  -145,  -145,    71,  -145,    49,   187,
    -145,  -145,  -145,  -145,   109,  -145,  -145,  -145,  -145,  -145,
    -145,  -145,  -145,  -145,   257,   -20,   -20,    45,  -145,   169,
     102,   242,   170,   186,   171,    80,   300,   167,   168,    55,
      81,   188,    84,   172,   306,   -20,    85,   189,    86,   190,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,    49,   218,   219,    50,    51,    50,    51,    91,
     107,    50,    51,    50,    51,   228,   108,   102,    94,   246,
     333,   106,    95,   147,   169,    52,   159,   170,    96,   171,
      95,   160,   169,   150,    95,   170,   153,   171,   172,   169,
     191,   236,   170,    85,   171,   101,   172,   251,   216,   217,
     312,   218,   219,   172,   196,   198,   199,   200,   201,    50,
      51,   112,   167,   228,   149,    62,   334,   336,   150,   162,
      63,   120,   121,   163,   338,   152,   -20,   -20,    67,   150,
      70,   164,   165,    63,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   154,   156,   169,   -20,   136,   170,   158,
     171,   183,   237,   240,   192,   245,   202,    36,   203,   172,
      37,    38,    39,   204,   169,   169,   205,   170,   170,   171,
     171,   206,   169,   207,   208,   170,   209,   171,   172,   172,
     210,   211,   167,   307,   167,   212,   172,   213,    83,   234,
     247,   248,   249,   255,   256,   258,   259,   260,   261,   301,
     329,   330,   264,   299,   278,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   303,    78,   216,   217,   314,   218,
     219,   238,   304,   315,   316,   317,   318,   239,   113,   319,
     114,   228,   115,   320,   229,   116,   321,   322,   232,   233,
     323,   311,   117,   324,   325,   313,   246,   327,   216,   217,
      63,   218,   219,   -62,   118,   213,   337,   331,   339,   105,
      23,   185,   151,   228,   -62,   243,   310,   308,     0,   119,
     232,   233,   120,   121,    68,     0,   122,     0,     0,   157,
       0,     0,     0,   328,     0,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   244,
       0,    56,     0,   -20,   -20,     0,   113,     0,   114,     0,
     115,    57,     0,   116,     0,     0,     0,     0,     0,     0,
     117,     0,     0,   -20,     0,     0,     0,     0,     0,     0,
       0,     0,   118,     0,     0,     0,     0,     0,     5,     6,
       7,     8,     9,    10,    11,    58,    13,   119,     0,     0,
     120,   121,     0,     0,   122,    15,     0,    16,     0,     0,
      17,    18,    74,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   279,    40,     0,
       0,     0,     0,     0,   113,     0,   114,     0,   115,     0,
       0,   116,     0,     0,     0,     0,     0,     0,   117,     5,
       6,     7,     8,     9,    10,    11,     0,    13,     0,     0,
     118,     0,     0,     0,     0,     0,    15,     0,    16,     0,
       0,    17,    18,     0,     0,   119,     0,     0,   120,   121,
       0,     0,   122,     0,     0,     0,     0,     0,     0,    40,
       0,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   159,     0,     0,     0,     0,
     160,     0,   216,   217,     0,   218,   219,     0,   220,   221,
       0,   222,   223,   224,   225,   226,   227,   228,     0,     0,
     229,   230,     0,   231,   232,   233,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   162,     0,
     120,   121,   163,     0,     0,     0,     0,     0,     0,     0,
     164,   165,   305,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   159,     0,     0,     0,   136,   160,     0,   216,
     217,     0,   218,   219,     0,   220,   221,     0,   222,   223,
     224,   225,   226,   227,   228,     0,     0,   229,   230,     0,
     231,   232,   233,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   162,     0,   120,   121,   163,
       0,     0,     0,     0,     0,     0,     0,   164,   165,   335,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   159,
       0,     0,     0,   136,   160,     0,   216,   217,     0,   218,
     219,     0,   220,   221,     0,   222,   223,   224,   225,   226,
     227,   228,     0,     0,   229,   230,     0,   231,   232,   233,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   162,   159,   120,   121,   163,     0,   160,     0,
       0,     0,     0,     0,   164,   165,     0,   123,   124,   125,
     126,   127,   128,   129,   130,   131,     0,     0,     0,     0,
     136,     0,     0,     0,     5,     6,     7,     8,     9,    10,
      11,   161,    13,     0,     0,     0,   162,   159,   120,   121,
     163,    15,   160,    16,     0,     0,    17,    18,   164,   165,
       0,   123,   124,   125,   126,   127,   128,   129,   130,   131,
       0,     0,     0,     0,   166,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     4,     0,
     162,     0,   120,   121,   163,     0,     0,     0,     0,     0,
       0,     0,   164,   165,     0,   123,   124,   125,   126,   127,
     128,   129,   130,   131,     0,     0,     0,     0,   136,     5,
       6,     7,     8,     9,    10,    11,    12,    13,     0,    14,
     113,     0,   114,     0,   115,    87,    15,   116,    16,     0,
       0,    17,    18,     0,   117,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   118,     0,     0,    19,
       0,     0,     5,     6,     7,     8,     9,    10,    11,    58,
      13,   119,     0,     0,   120,   121,   110,     0,   122,    15,
       0,    16,     0,     0,    17,    18,     0,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,     0,    40,     5,     6,     7,     8,     9,    10,    11,
      58,    13,     0,     0,     0,     0,     0,     0,     0,     0,
      15,     0,    16,     0,     0,    17,    18,     5,     6,     7,
       8,     9,    10,    11,    58,    13,     0,     0,     0,     0,
       0,     0,     0,    40,    15,     0,    16,     0,     0,    17,
      18,     5,     6,     7,     8,     9,    10,    11,   161,    13,
       0,     0,     0,     0,     0,     0,     0,    40,    15,     0,
      16,     0,     0,    17,    18,     5,     6,     7,     8,     9,
      10,    11,     0,    13,     0,     0,     0,     0,     0,   265,
       0,   309,    15,     0,    16,     0,     0,    17,    18,   216,
     217,     0,   218,   219,     0,   220,   221,     0,   222,   223,
     224,   225,   226,   227,   228,    40,     0,   229,   230,   262,
     231,   232,   233,     0,     0,   263,     0,     0,   216,   217,
       0,   218,   219,     0,   220,   221,     0,   222,   223,   224,
     225,   226,   227,   228,     0,   302,   229,   230,     0,   231,
     232,   233,   216,   217,     0,   218,   219,     0,   220,   221,
       0,   222,   223,   224,   225,   226,   227,   228,     0,     0,
     229,   230,   326,   231,   232,   233,     0,   216,   217,     0,
     218,   219,     0,   220,   221,     0,   222,   223,   224,   225,
     226,   227,   228,     0,     0,   229,   230,     0,   231,   232,
     233,   332,   216,   217,     0,   218,   219,     0,   220,   221,
       0,   222,   223,   224,   225,   226,   227,   228,     0,     0,
     229,   230,     0,   231,   232,   233,   216,   217,     0,   218,
     219,     0,   220,   221,     0,   222,   223,   224,   225,   226,
     227,   228,     0,     0,   229,   230,     0,   231,   232,   233,
     216,   217,     0,   218,   219,     0,   220,     0,     0,   222,
     223,   224,   225,   226,   227,   228,     0,     0,   229,   230,
       0,   231,   232,   233,   216,   217,     0,   218,   219,     0,
       0,     0,     0,   222,   223,   224,   225,   226,   227,   228,
       0,     0,   229,   230,     0,   231,   232,   233,   216,   217,
       0,   218,   219,     0,     0,     0,     0,  -146,  -146,  -146,
    -146,  -146,  -146,   228,     0,     0,   229,   230,     0,   231,
     232,   233
};

static const yytype_int16 yycheck[] =
{
      34,    35,     2,     2,    97,    41,    11,    97,    55,    97,
       1,     1,    12,     1,     1,     0,     7,     7,    97,    58,
      59,    10,    12,   115,     7,    58,    59,    10,     1,    10,
      19,     1,    79,     8,    10,    58,    59,    58,    59,    78,
      45,   182,    12,    19,    19,    78,    46,    47,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    78,    58,    10,
      50,     5,    52,    53,    54,    55,    13,    57,     1,    13,
      60,    61,    62,    63,     5,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    11,    58,    59,    78,    78,   182,
      78,    78,   182,     5,   182,    78,   237,    97,    97,    10,
       7,    13,     1,   182,   245,    78,     5,   107,     7,   109,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,     1,    17,    18,    58,    59,    58,    59,    45,
       5,    58,    59,    58,    59,    29,    11,    78,     1,     1,
       1,    11,     5,    83,   237,    78,     7,   237,    11,   237,
       5,    12,   245,    78,     5,   245,    11,   245,   237,   252,
      11,   161,   252,     5,   252,     7,   245,   308,    14,    15,
     262,    17,    18,   252,   114,   115,   116,   117,   118,    58,
      59,    10,   182,    29,     7,     7,   327,   328,    78,    50,
      12,    52,    53,    54,   335,    45,    58,    59,     7,    78,
     236,    62,    63,    12,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    45,    45,   308,    78,    78,   308,    45,
     308,    13,   162,   163,    11,   165,    10,    38,    10,   308,
      41,    42,    43,    10,   327,   328,    10,   327,   328,   327,
     328,    10,   335,    10,    10,   335,    10,   335,   327,   328,
      10,    10,   252,   252,   254,    10,   335,    10,    19,    45,
       7,     7,     7,     7,    78,    45,    45,     9,     5,     7,
     304,   305,    13,    13,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,    51,     7,    14,    15,    11,    17,
      18,     1,    64,    11,    11,    11,    11,     7,     8,    11,
      10,    29,    12,    11,    32,    15,    11,    11,    36,    37,
      11,   261,    22,    11,    11,   265,     1,    47,    14,    15,
      12,    17,    18,     8,    34,    10,    13,    11,     7,    73,
       2,    99,    85,    29,    19,   164,   254,   252,    -1,    49,
      36,    37,    52,    53,    35,    -1,    56,    -1,    -1,    95,
      -1,    -1,    -1,   303,    -1,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,     1,
      -1,     1,    -1,    58,    59,    -1,     8,    -1,    10,    -1,
      12,    11,    -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,
      22,    -1,    -1,    78,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    49,    -1,    -1,
      52,    53,    -1,    -1,    56,    55,    -1,    57,    -1,    -1,
      60,    61,     1,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,     1,    78,    -1,
      -1,    -1,    -1,    -1,     8,    -1,    10,    -1,    12,    -1,
      -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,    22,    38,
      39,    40,    41,    42,    43,    44,    -1,    46,    -1,    -1,
      34,    -1,    -1,    -1,    -1,    -1,    55,    -1,    57,    -1,
      -1,    60,    61,    -1,    -1,    49,    -1,    -1,    52,    53,
      -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    78,
      -1,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,     7,    -1,    -1,    -1,    -1,
      12,    -1,    14,    15,    -1,    17,    18,    -1,    20,    21,
      -1,    23,    24,    25,    26,    27,    28,    29,    -1,    -1,
      32,    33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,
      52,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,     7,    -1,    -1,    -1,    78,    12,    -1,    14,
      15,    -1,    17,    18,    -1,    20,    21,    -1,    23,    24,
      25,    26,    27,    28,    29,    -1,    -1,    32,    33,    -1,
      35,    36,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    -1,    52,    53,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,     7,
      -1,    -1,    -1,    78,    12,    -1,    14,    15,    -1,    17,
      18,    -1,    20,    21,    -1,    23,    24,    25,    26,    27,
      28,    29,    -1,    -1,    32,    33,    -1,    35,    36,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    50,     7,    52,    53,    54,    -1,    12,    -1,
      -1,    -1,    -1,    -1,    62,    63,    -1,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,
      78,    -1,    -1,    -1,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    -1,    -1,    50,     7,    52,    53,
      54,    55,    12,    57,    -1,    -1,    60,    61,    62,    63,
      -1,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     7,    -1,
      50,    -1,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    62,    63,    -1,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    -1,    -1,    -1,    -1,    78,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    48,
       8,    -1,    10,    -1,    12,    11,    55,    15,    57,    -1,
      -1,    60,    61,    -1,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    78,
      -1,    -1,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    49,    -1,    -1,    52,    53,    11,    -1,    56,    55,
      -1,    57,    -1,    -1,    60,    61,    -1,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    -1,    78,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      55,    -1,    57,    -1,    -1,    60,    61,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    78,    55,    -1,    57,    -1,    -1,    60,
      61,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    55,    -1,
      57,    -1,    -1,    60,    61,    38,    39,    40,    41,    42,
      43,    44,    -1,    46,    -1,    -1,    -1,    -1,    -1,     4,
      -1,    78,    55,    -1,    57,    -1,    -1,    60,    61,    14,
      15,    -1,    17,    18,    -1,    20,    21,    -1,    23,    24,
      25,    26,    27,    28,    29,    78,    -1,    32,    33,     5,
      35,    36,    37,    -1,    -1,    11,    -1,    -1,    14,    15,
      -1,    17,    18,    -1,    20,    21,    -1,    23,    24,    25,
      26,    27,    28,    29,    -1,     7,    32,    33,    -1,    35,
      36,    37,    14,    15,    -1,    17,    18,    -1,    20,    21,
      -1,    23,    24,    25,    26,    27,    28,    29,    -1,    -1,
      32,    33,     9,    35,    36,    37,    -1,    14,    15,    -1,
      17,    18,    -1,    20,    21,    -1,    23,    24,    25,    26,
      27,    28,    29,    -1,    -1,    32,    33,    -1,    35,    36,
      37,    13,    14,    15,    -1,    17,    18,    -1,    20,    21,
      -1,    23,    24,    25,    26,    27,    28,    29,    -1,    -1,
      32,    33,    -1,    35,    36,    37,    14,    15,    -1,    17,
      18,    -1,    20,    21,    -1,    23,    24,    25,    26,    27,
      28,    29,    -1,    -1,    32,    33,    -1,    35,    36,    37,
      14,    15,    -1,    17,    18,    -1,    20,    -1,    -1,    23,
      24,    25,    26,    27,    28,    29,    -1,    -1,    32,    33,
      -1,    35,    36,    37,    14,    15,    -1,    17,    18,    -1,
      -1,    -1,    -1,    23,    24,    25,    26,    27,    28,    29,
      -1,    -1,    32,    33,    -1,    35,    36,    37,    14,    15,
      -1,    17,    18,    -1,    -1,    -1,    -1,    23,    24,    25,
      26,    27,    28,    29,    -1,    -1,    32,    33,    -1,    35,
      36,    37
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    83,    84,     0,     7,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    48,    55,    57,    60,    61,    78,
      85,    86,    88,    89,    90,    91,    92,    93,    94,    95,
      97,    98,   133,   134,   135,   136,    38,    41,    42,    43,
      78,    88,    89,     1,     7,    78,    10,    10,     1,     1,
      58,    59,    78,    99,   100,    10,     1,    11,    45,    88,
     138,   139,     7,    12,   123,   124,   137,     7,   137,    78,
     100,    13,     1,    12,     1,    88,    96,    88,     7,    10,
      78,     7,    10,    19,     1,     5,     7,    11,   138,    11,
      45,    45,    88,    78,     1,     5,    11,   126,   128,   129,
      10,     7,    78,    87,     1,    87,    11,     5,    11,     5,
      11,   138,    10,     8,    10,    12,    15,    22,    34,    49,
      52,    53,    56,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,   101,   102,   103,
     104,   105,   106,   109,   110,   111,   112,   113,   114,     7,
      78,    99,    45,    11,    45,    78,    45,   139,    45,     7,
      12,    45,    50,    54,    62,    63,    78,    88,    98,   102,
     105,   106,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   132,    13,   125,   125,     5,    13,    13,    88,
      88,    11,    11,   107,   108,   113,   113,   107,   113,   113,
     113,   113,    10,    10,    10,    10,    10,    10,    10,    10,
      10,    10,    10,    10,     8,    19,    14,    15,    17,    18,
      20,    21,    23,    24,    25,    26,    27,    28,    29,    32,
      33,    35,    36,    37,    45,     1,    88,   113,     1,     7,
     113,     1,    78,   103,     1,   113,     1,     7,     7,     7,
      98,   115,   127,   130,   131,     7,    78,    11,    45,    45,
       9,     5,     5,    11,    13,     4,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   113,     1,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,    13,
     115,     7,     7,    51,    64,    64,   115,    98,   132,    78,
     130,   113,   107,   113,    11,    11,    11,    11,    11,    11,
      11,    11,    11,    11,    11,    11,     9,    47,   113,   123,
     123,    11,    13,     1,   115,    64,   115,    13,   115,     7
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    82,    83,    84,    84,    85,    85,    85,    85,    86,
      86,    86,    86,    86,    87,    87,    88,    88,    89,    89,
      90,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    92,    92,    92,    92,    93,    94,
      95,    95,    96,    96,    97,    98,    98,    98,    98,    98,
      99,    99,   100,   100,   101,   101,   101,   101,   101,   101,
     102,   102,   103,   104,   105,   105,   106,   107,   107,   108,
     108,   109,   110,   111,   112,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   116,   116,   116,   116,
     117,   118,   118,   119,   120,   120,   120,   121,   121,   121,
     122,   122,   122,   123,   123,   124,   125,   125,   126,   126,
     127,   127,   128,   129,   130,   131,   131,   132,   132,   133,
     133,   133,   133,   134,   134,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   137,   138,   138,   139,   139
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     1,     1,     5,
       5,     2,     4,     3,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     2,     2,     1,     1,     1,     1,     2,     2,
       4,     4,     1,     3,     6,     3,     4,     3,     4,     3,
       1,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     4,     3,     3,     4,     0,     1,     1,
       3,     3,     3,     5,     5,     2,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     5,     7,     6,
       1,     2,     2,     2,     3,     2,     3,     6,     5,     2,
       4,     3,     4,     3,     3,     1,     1,     2,     0,     2,
       1,     2,     2,     3,     2,     1,     2,     1,     2,     2,
       2,     2,     2,     3,     4,     3,     2,     3,     3,     2,
       4,     3,     5,     4,     4,     3,     4,     4,     3,     5,
       4,     6,     6,     1,     1,     3,     2,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 9: /* enum: TOK_ENUM TOK_ID TOK_LBRACE enum_elem_list TOK_RBRACE  */
#line 135 "C+_parser.y++"
                                                           {
	(yyval.enumEntry) =  new EnumEntry((yyvsp[-3].cVal), yylinenum, 0, yyfilename);
	for (int i = 0; i < (yyvsp[-1].enumElemList)->size(); i++ )
		(yyval.enumEntry)->addElem((yyvsp[-1].enumElemList)->at(i));
	ErrorST state = stm.insert( (yyval.enumEntry) );
	if ( state == DUPLICATE_SYM )
		errMsg("Redefinition of name " + string((yyvsp[-3].cVal)));
	else if ( state == INVALID_SCOPE )
		errMsg("Invalid Scope");
}
#line 1806 "C+_parser.tab.c++"
    break;

  case 10: /* enum: TOK_ENUM TOK_ID error enum_elem_list TOK_RBRACE  */
#line 145 "C+_parser.y++"
                                                  { errMsg("Expecting \"{\" following enum name"); }
#line 1812 "C+_parser.tab.c++"
    break;

  case 11: /* enum: TOK_ENUM TOK_SEMICOLON  */
#line 146 "C+_parser.y++"
                         { errMsg("parse error: expecting enum name and element list"); }
#line 1818 "C+_parser.tab.c++"
    break;

  case 12: /* enum: TOK_ENUM TOK_ID TOK_LBRACE error  */
#line 147 "C+_parser.y++"
                                   { errMsg("Syntax error in enum element list, Expected \",\" or \"}\""); }
#line 1824 "C+_parser.tab.c++"
    break;

  case 13: /* enum: TOK_ENUM error TOK_RBRACE  */
#line 148 "C+_parser.y++"
                            { errMsg("Syntax error while parsing enum declaration"); }
#line 1830 "C+_parser.tab.c++"
    break;

  case 14: /* enum_elem_list: TOK_ID  */
#line 151 "C+_parser.y++"
                       { 
	(yyval.enumElemList) = new vector<EnumElemEntry*>();
	EnumElemEntry *elem = new EnumElemEntry((yyvsp[0].cVal), (yyval.enumElemList)->size(), nullptr, yylinenum, 0, yyfilename);
	(yyval.enumElemList)->push_back(elem);
	ErrorST state = stm.insert( elem );
	if ( state == DUPLICATE_SYM )
		errMsg("Redefinition of name " + string((yyvsp[0].cVal)));
	else if ( state == INVALID_SCOPE )
		errMsg("Invalid Scope");
}
#line 1845 "C+_parser.tab.c++"
    break;

  case 15: /* enum_elem_list: enum_elem_list TOK_COMMA TOK_ID  */
#line 161 "C+_parser.y++"
                                  {
	EnumElemEntry *elem = new EnumElemEntry((yyvsp[0].cVal), (yyval.enumElemList)->size(), nullptr, yylinenum, 0, yyfilename);
	(yyval.enumElemList)->push_back(elem);
	ErrorST state = stm.insert( elem );
	if ( state == DUPLICATE_SYM )
		errMsg("Redefinition of name " + string((yyvsp[0].cVal)));
	else if ( state == INVALID_SCOPE )
		errMsg("Invalid Scope");
}
#line 1859 "C+_parser.tab.c++"
    break;

  case 16: /* type: known_type  */
#line 174 "C+_parser.y++"
                 { (yyval.typeVal) = (yyvsp[0].typeVal); }
#line 1865 "C+_parser.tab.c++"
    break;

  case 17: /* type: unknown_type  */
#line 175 "C+_parser.y++"
               { (yyval.typeVal) = (yyvsp[0].typeVal); }
#line 1871 "C+_parser.tab.c++"
    break;

  case 18: /* known_type: primary_type  */
#line 178 "C+_parser.y++"
                         { (yyval.typeVal) = (yyvsp[0].typeVal); }
#line 1877 "C+_parser.tab.c++"
    break;

  case 19: /* known_type: builtin_type  */
#line 179 "C+_parser.y++"
               { (yyval.typeVal) = (yyvsp[0].typeVal); }
#line 1883 "C+_parser.tab.c++"
    break;

  case 20: /* unknown_type: TOK_ID  */
#line 182 "C+_parser.y++"
                     { (yyval.typeVal) = new Type(Type::UNKNOWN); }
#line 1889 "C+_parser.tab.c++"
    break;

  case 21: /* primary_type: TOK_BOOL  */
#line 185 "C+_parser.y++"
                       { (yyval.typeVal) = new Type(Type::BOOL); }
#line 1895 "C+_parser.tab.c++"
    break;

  case 22: /* primary_type: TOK_STRING  */
#line 186 "C+_parser.y++"
             { (yyval.typeVal) = new Type(Type::STRING); }
#line 1901 "C+_parser.tab.c++"
    break;

  case 23: /* primary_type: TOK_SHORT  */
#line 187 "C+_parser.y++"
            { (yyval.typeVal) = new Type(Type::SHORT); }
#line 1907 "C+_parser.tab.c++"
    break;

  case 24: /* primary_type: TOK_LONG  */
#line 188 "C+_parser.y++"
           { (yyval.typeVal) = new Type(Type::LONG); }
#line 1913 "C+_parser.tab.c++"
    break;

  case 25: /* primary_type: TOK_INT  */
#line 189 "C+_parser.y++"
          { (yyval.typeVal) = new Type(Type::INT); }
#line 1919 "C+_parser.tab.c++"
    break;

  case 26: /* primary_type: TOK_CHAR  */
#line 190 "C+_parser.y++"
           { (yyval.typeVal) = new Type(Type::CHAR); }
#line 1925 "C+_parser.tab.c++"
    break;

  case 27: /* primary_type: TOK_BIT  */
#line 191 "C+_parser.y++"
          { (yyval.typeVal) = new Type(Type::BIT); }
#line 1931 "C+_parser.tab.c++"
    break;

  case 28: /* primary_type: TOK_DOUBLE  */
#line 192 "C+_parser.y++"
             { (yyval.typeVal) = new Type(Type::DOUBLE); }
#line 1937 "C+_parser.tab.c++"
    break;

  case 29: /* primary_type: TOK_VOID  */
#line 193 "C+_parser.y++"
           { (yyval.typeVal) = new Type(Type::VOID); }
#line 1943 "C+_parser.tab.c++"
    break;

  case 30: /* primary_type: TOK_UNSIGNED TOK_INT  */
#line 194 "C+_parser.y++"
                       { (yyval.typeVal) = new Type(Type::UINT); }
#line 1949 "C+_parser.tab.c++"
    break;

  case 31: /* primary_type: TOK_UNSIGNED TOK_CHAR  */
#line 195 "C+_parser.y++"
                        { (yyval.typeVal) = new Type(Type::UCHAR); }
#line 1955 "C+_parser.tab.c++"
    break;

  case 32: /* primary_type: TOK_UNSIGNED TOK_LONG  */
#line 196 "C+_parser.y++"
                        { (yyval.typeVal) = new Type(Type::ULONG); }
#line 1961 "C+_parser.tab.c++"
    break;

  case 33: /* primary_type: TOK_UNSIGNED TOK_SHORT  */
#line 197 "C+_parser.y++"
                         { (yyval.typeVal) = new Type(Type::USHORT); }
#line 1967 "C+_parser.tab.c++"
    break;

  case 34: /* builtin_type: list_type  */
#line 200 "C+_parser.y++"
                        { (yyval.typeVal) = (yyvsp[0].typeVal); }
#line 1973 "C+_parser.tab.c++"
    break;

  case 35: /* builtin_type: set_type  */
#line 201 "C+_parser.y++"
           { (yyval.typeVal) = (yyvsp[0].typeVal); }
#line 1979 "C+_parser.tab.c++"
    break;

  case 36: /* builtin_type: tuple_type  */
#line 202 "C+_parser.y++"
             { (yyval.typeVal) = (yyvsp[0].typeVal); }
#line 1985 "C+_parser.tab.c++"
    break;

  case 37: /* builtin_type: dict_type  */
#line 203 "C+_parser.y++"
            { (yyval.typeVal) = (yyvsp[0].typeVal); }
#line 1991 "C+_parser.tab.c++"
    break;

  case 38: /* list_type: type TOK_LIST  */
#line 206 "C+_parser.y++"
                         { (yyval.typeVal) = new Type( (yyvsp[-1].typeVal), Type::VECTOR); }
#line 1997 "C+_parser.tab.c++"
    break;

  case 39: /* set_type: type TOK_SET  */
#line 209 "C+_parser.y++"
                       { (yyval.typeVal) = new Type( (yyvsp[-1].typeVal), Type::SET); }
#line 2003 "C+_parser.tab.c++"
    break;

  case 40: /* tuple_type: TOK_TUPLE TOK_LPAREN type_sequence TOK_RPAREN  */
#line 212 "C+_parser.y++"
                                                          { (yyval.typeVal) = new Type((yyvsp[-1].typeList), Type::TUPLE); }
#line 2009 "C+_parser.tab.c++"
    break;

  case 41: /* tuple_type: TOK_TUPLE TOK_LPAREN error TOK_RPAREN  */
#line 213 "C+_parser.y++"
                                        { errMsg("Invalid Tuple Type declaration"); }
#line 2015 "C+_parser.tab.c++"
    break;

  case 42: /* type_sequence: type  */
#line 216 "C+_parser.y++"
                    { (yyval.typeList) = new vector<Type*>(); (yyval.typeList)->push_back((yyvsp[0].typeVal)); }
#line 2021 "C+_parser.tab.c++"
    break;

  case 43: /* type_sequence: type_sequence TOK_COMMA type  */
#line 217 "C+_parser.y++"
                               { (yyval.typeList)->push_back((yyvsp[0].typeVal)); }
#line 2027 "C+_parser.tab.c++"
    break;

  case 44: /* dict_type: TOK_DICT TOK_LPAREN type TOK_COMMA type TOK_RPAREN  */
#line 220 "C+_parser.y++"
                                                              { (yyval.typeVal) = new Type((yyvsp[-3].typeVal), (yyvsp[-1].typeVal)); }
#line 2033 "C+_parser.tab.c++"
    break;

  case 45: /* var_decl: type var_sequence TOK_SEMICOLON  */
#line 225 "C+_parser.y++"
                                          {
	for ( size_t i = 0; i < (yyvsp[-1].strVector)->size(); i++ ) {
		if ( !(yyvsp[-1].strVector)->at(i).empty() ) {
			(stm.lookUpInScope((yyvsp[-1].strVector)->at(i), stm.currentScope()->kind()))->type((yyvsp[-2].typeVal));
		}
	}
}
#line 2045 "C+_parser.tab.c++"
    break;

  case 46: /* var_decl: TOK_CONST type var_sequence TOK_SEMICOLON  */
#line 232 "C+_parser.y++"
                                            {
	(yyvsp[-2].typeVal)->constType(true);
	for ( size_t i = 0; i < (yyvsp[-1].strVector)->size(); i++ ) {
		if ( !(yyvsp[-1].strVector)->at(i).empty() ) {
			(stm.lookUpInScope((yyvsp[-1].strVector)->at(i), stm.currentScope()->kind()))->type((yyvsp[-2].typeVal));
		}
	}
}
#line 2058 "C+_parser.tab.c++"
    break;

  case 47: /* var_decl: TOK_ID error TOK_SEMICOLON  */
#line 240 "C+_parser.y++"
                             { errMsg("Error in variable declaration, may be a missing type name or identifier"); }
#line 2064 "C+_parser.tab.c++"
    break;

  case 48: /* var_decl: type var_sequence error TOK_SEMICOLON  */
#line 241 "C+_parser.y++"
                                        { errMsg("Error in variable declaration, may be a missing \",\" or identifier"); }
#line 2070 "C+_parser.tab.c++"
    break;

  case 49: /* var_decl: type error TOK_SEMICOLON  */
#line 242 "C+_parser.y++"
                           { errMsg("Error in variable declaration, may be a missing identifier"); }
#line 2076 "C+_parser.tab.c++"
    break;

  case 50: /* single_var: TOK_ID  */
#line 245 "C+_parser.y++"
                   { 
	(yyval.cVal) = (yyvsp[0].cVal);
	VariableEntry *var;
	if (!stm.currentScope())
		var = new VariableEntry((yyvsp[0].cVal), UNDEFINED, nullptr, 0, yylinenum, 0, yyfilename);
	else {
		switch ( stm.currentScope()->kind() ){
			case SymTabEntry::GLOBAL_KIND:
				var = new VariableEntry((yyvsp[0].cVal), GLOBAL_VAR, nullptr, 0, yylinenum, 0, yyfilename);
				break;
			case SymTabEntry::FUNCTION_KIND:
				var = new VariableEntry((yyvsp[0].cVal), FN_PARAM_VAR, nullptr, 0, yylinenum, 0, yyfilename);
				break;
			case SymTabEntry::BLOCK_KIND:
				var = new VariableEntry((yyvsp[0].cVal), LOCAL_VAR, nullptr, 0, yylinenum, 0, yyfilename);
				break;
			case SymTabEntry::ERROR_KIND:
				var = new VariableEntry((yyvsp[0].cVal), COMPILER_GENERATED_VAR, nullptr, 0, yylinenum, 0, yyfilename);
				break;
			default:
				var = new VariableEntry((yyvsp[0].cVal), UNDEFINED, nullptr, 0, yylinenum, 0, yyfilename);
				break;
		}
	}
	ErrorST state = stm.insert(var);
	if ( state == DUPLICATE_SYM ) {
		errMsg("Redefinition of name " + string((yyvsp[0].cVal)));
		(yyval.cVal) = (char*)"";
	}
	else if ( state == INVALID_SCOPE ) {
		errMsg("Invalid Scope");
		(yyval.cVal) = (char*)"";
	}
}
#line 2115 "C+_parser.tab.c++"
    break;

  case 51: /* single_var: TOK_ID TOK_ASSIGN expr  */
#line 279 "C+_parser.y++"
                         { 
	(yyval.cVal) = (yyvsp[-2].cVal);
	VariableEntry *var;
	if (!stm.currentScope())
		var = new VariableEntry((yyvsp[-2].cVal), UNDEFINED, nullptr, (yyvsp[0].exprVal), yylinenum, 0, yyfilename);
	else {
		switch ( stm.currentScope()->kind() ){
			case SymTabEntry::GLOBAL_KIND:
				var = new VariableEntry((yyvsp[-2].cVal), GLOBAL_VAR, nullptr, (yyvsp[0].exprVal), yylinenum, 0, yyfilename);
				break;
			case SymTabEntry::FUNCTION_KIND:
				var = new VariableEntry((yyvsp[-2].cVal), FN_PARAM_VAR, nullptr, (yyvsp[0].exprVal), yylinenum, 0, yyfilename);
				break;
			case SymTabEntry::BLOCK_KIND:
				var = new VariableEntry((yyvsp[-2].cVal), LOCAL_VAR, nullptr, (yyvsp[0].exprVal), yylinenum, 0, yyfilename);
				break;
			case SymTabEntry::ERROR_KIND:
				var = new VariableEntry((yyvsp[-2].cVal), COMPILER_GENERATED_VAR, nullptr, (yyvsp[0].exprVal), yylinenum, 0, yyfilename);
				break;
			default:
				var = new VariableEntry((yyvsp[-2].cVal), UNDEFINED, nullptr, (yyvsp[0].exprVal), yylinenum, 0, yyfilename);
				break;
		}
	}
	ErrorST state = stm.insert(var);
	if ( state == DUPLICATE_SYM ) {
		errMsg("Redefinition of name " + string((yyvsp[-2].cVal)));
		(yyval.cVal) = (char*)"";
	}
	else if ( state == INVALID_SCOPE ) {
		errMsg("Invalid Scope");
		(yyval.cVal) = (char*)"";
	}
}
#line 2154 "C+_parser.tab.c++"
    break;

  case 52: /* var_sequence: single_var  */
#line 315 "C+_parser.y++"
                         { (yyval.strVector) = new vector<string>(); (yyval.strVector)->push_back(string((yyvsp[0].cVal))); }
#line 2160 "C+_parser.tab.c++"
    break;

  case 53: /* var_sequence: var_sequence TOK_COMMA single_var  */
#line 316 "C+_parser.y++"
                                    { (yyval.strVector)->push_back(string((yyvsp[0].cVal))); }
#line 2166 "C+_parser.tab.c++"
    break;

  case 54: /* expr_literal: TOK_UINTNUM  */
#line 320 "C+_parser.y++"
                          { (yyval.valVal) = new Value((yyvsp[0].uVal)); }
#line 2172 "C+_parser.tab.c++"
    break;

  case 55: /* expr_literal: TOK_IP  */
#line 321 "C+_parser.y++"
         {  }
#line 2178 "C+_parser.tab.c++"
    break;

  case 56: /* expr_literal: TOK_DOUBLENUM  */
#line 322 "C+_parser.y++"
                { (yyval.valVal) = new Value((yyvsp[0].dVal)); }
#line 2184 "C+_parser.tab.c++"
    break;

  case 57: /* expr_literal: TOK_STRCONST  */
#line 323 "C+_parser.y++"
               { (yyval.valVal) = new Value((yyvsp[0].cVal)); }
#line 2190 "C+_parser.tab.c++"
    break;

  case 58: /* expr_literal: TOK_TRUE  */
#line 324 "C+_parser.y++"
           { (yyval.valVal) =  new Value(Type::BaseTypeTag::BOOL, true); }
#line 2196 "C+_parser.tab.c++"
    break;

  case 59: /* expr_literal: TOK_FALSE  */
#line 325 "C+_parser.y++"
            { (yyval.valVal) =  new Value(Type::BaseTypeTag::BOOL, false); }
#line 2202 "C+_parser.tab.c++"
    break;

  case 60: /* expr_ref: single_ref  */
#line 328 "C+_parser.y++"
                     { (yyval.refexpVal) = (yyvsp[0].refexpVal); }
#line 2208 "C+_parser.tab.c++"
    break;

  case 61: /* expr_ref: expr_index  */
#line 329 "C+_parser.y++"
             { (yyval.refexpVal) = (yyvsp[0].refexpVal); }
#line 2214 "C+_parser.tab.c++"
    break;

  case 62: /* single_ref: TOK_ID  */
#line 332 "C+_parser.y++"
                   { 
	SymTabEntry *ste = stm.lookUp((yyvsp[0].cVal));
	if(ste == nullptr || (ste->kind() != SymTabEntry::SymKind::VARIABLE_KIND && ste->kind() != SymTabEntry::SymKind::ENUM_ELEM_KIND)) {
		(yyval.refexpVal) = nullptr;
		errMsg("Undeclared identifier \"" + string((yyvsp[0].cVal)) + "\"");
	} else {
		(yyval.refexpVal) = new RefExprNode(nullptr, (yyvsp[0].cVal), ste); 
	}
  }
#line 2228 "C+_parser.tab.c++"
    break;

  case 63: /* expr_index: expr_ref TOK_LBRACK expr TOK_RBRACK  */
#line 343 "C+_parser.y++"
                                                { (yyvsp[-3].refexpVal)->addSubs((yyvsp[-1].exprVal)); (yyval.refexpVal) = (yyvsp[-3].refexpVal); }
#line 2234 "C+_parser.tab.c++"
    break;

  case 64: /* expr_assignment: expr_ref TOK_ASSIGN expr  */
#line 346 "C+_parser.y++"
                                          { if((yyvsp[-2].refexpVal) != nullptr && (yyvsp[0].exprVal) != nullptr) (yyval.exprVal) = new OpNode(OpNode::ASSIGN, (yyvsp[-2].refexpVal), (yyvsp[0].exprVal)); else (yyval.exprVal) = nullptr; }
#line 2240 "C+_parser.tab.c++"
    break;

  case 65: /* expr_assignment: expr_ref TOK_ASSIGN error  */
#line 347 "C+_parser.y++"
                            { errMsg("Syntax error in assignment"); }
#line 2246 "C+_parser.tab.c++"
    break;

  case 66: /* expr_func: TOK_ID TOK_LPAREN expr_param TOK_RPAREN  */
#line 350 "C+_parser.y++"
                                                   {	
	SymTabEntry *ste = stm.lookUp((yyvsp[-3].cVal));
	if(ste == nullptr || ste->kind() != SymTabEntry::SymKind::FUNCTION_KIND) {
		(yyval.exprVal) = new InvocationNode(nullptr, (yyvsp[-1].exprList));
		errMsg("\"" + string((yyvsp[-3].cVal)) + "\" is not a function or module name");
	} else {
		(yyval.exprVal) = new InvocationNode(ste, (yyvsp[-1].exprList));
	}
}
#line 2260 "C+_parser.tab.c++"
    break;

  case 67: /* expr_param: %empty  */
#line 361 "C+_parser.y++"
             { (yyval.exprList) = new vector<ExprNode*>(); }
#line 2266 "C+_parser.tab.c++"
    break;

  case 68: /* expr_param: expr_plus  */
#line 362 "C+_parser.y++"
            { (yyval.exprList) = (yyvsp[0].exprList); }
#line 2272 "C+_parser.tab.c++"
    break;

  case 69: /* expr_plus: expr  */
#line 365 "C+_parser.y++"
                { (yyval.exprList) = new vector<ExprNode*>(); (yyval.exprList)->push_back((yyvsp[0].exprVal)); }
#line 2278 "C+_parser.tab.c++"
    break;

  case 70: /* expr_plus: expr_plus TOK_COMMA expr  */
#line 366 "C+_parser.y++"
                           { (yyval.exprList)->push_back((yyvsp[0].exprVal)); }
#line 2284 "C+_parser.tab.c++"
    break;

  case 71: /* expr_set: TOK_LBRACE expr_param TOK_RBRACE  */
#line 369 "C+_parser.y++"
                                           { (yyval.exprVal) = new OpNode(OpNode::SET, (yyvsp[-1].exprList)); }
#line 2290 "C+_parser.tab.c++"
    break;

  case 72: /* expr_list: TOK_LBRACK expr_param TOK_RBRACK  */
#line 372 "C+_parser.y++"
                                            { (yyval.exprVal) = new OpNode(OpNode::VECTOR, (yyvsp[-1].exprList)); }
#line 2296 "C+_parser.tab.c++"
    break;

  case 73: /* expr_dict: TOK_LBRACE expr TOK_COLON expr TOK_RBRACE  */
#line 375 "C+_parser.y++"
                                                     { (yyval.exprVal) = new OpNode(OpNode::DICT, new OpNode(OpNode::TUPLE, (yyvsp[-3].exprVal), (yyvsp[-1].exprVal))); }
#line 2302 "C+_parser.tab.c++"
    break;

  case 74: /* expr_tuple: TOK_LPAREN expr TOK_COMMA expr_param TOK_RPAREN  */
#line 378 "C+_parser.y++"
                                                            { (yyvsp[-1].exprList)->insert((yyvsp[-1].exprList)->begin(), (yyvsp[-3].exprVal)); (yyval.exprVal) = new OpNode(OpNode::TUPLE, (yyvsp[-1].exprList)); }
#line 2308 "C+_parser.tab.c++"
    break;

  case 75: /* expr: TOK_BITNOT expr  */
#line 381 "C+_parser.y++"
                      { if ((yyvsp[0].exprVal) != nullptr) (yyval.exprVal) = new OpNode(OpNode::BITNOT, (yyvsp[0].exprVal)); else (yyval.exprVal) = nullptr; }
#line 2314 "C+_parser.tab.c++"
    break;

  case 76: /* expr: TOK_MINUS expr  */
#line 382 "C+_parser.y++"
                           { if ((yyvsp[0].exprVal) != nullptr) (yyval.exprVal) = new OpNode(OpNode::UMINUS, (yyvsp[0].exprVal)); else (yyval.exprVal) = nullptr; }
#line 2320 "C+_parser.tab.c++"
    break;

  case 77: /* expr: TOK_NOT expr  */
#line 383 "C+_parser.y++"
               { if ((yyvsp[0].exprVal) != nullptr) (yyval.exprVal) = new OpNode(OpNode::NOT, (yyvsp[0].exprVal)); else (yyval.exprVal) = nullptr; }
#line 2326 "C+_parser.tab.c++"
    break;

  case 78: /* expr: TOK_LPAREN expr TOK_RPAREN  */
#line 384 "C+_parser.y++"
                             { if ((yyvsp[-1].exprVal) != nullptr) (yyval.exprVal) = (yyvsp[-1].exprVal); else (yyval.exprVal) = nullptr; }
#line 2332 "C+_parser.tab.c++"
    break;

  case 79: /* expr: expr TOK_BITXOR expr  */
#line 385 "C+_parser.y++"
                       { if((yyvsp[-2].exprVal) != nullptr && (yyvsp[0].exprVal) != nullptr) (yyval.exprVal) = new OpNode(OpNode::BITXOR, (yyvsp[-2].exprVal), (yyvsp[0].exprVal)); else (yyval.exprVal) = nullptr; }
#line 2338 "C+_parser.tab.c++"
    break;

  case 80: /* expr: expr TOK_SHL expr  */
#line 386 "C+_parser.y++"
                    { if((yyvsp[-2].exprVal) != nullptr && (yyvsp[0].exprVal) != nullptr) (yyval.exprVal) = new OpNode(OpNode::SHL, (yyvsp[-2].exprVal), (yyvsp[0].exprVal)); else (yyval.exprVal) = nullptr; }
#line 2344 "C+_parser.tab.c++"
    break;

  case 81: /* expr: expr TOK_LE expr  */
#line 387 "C+_parser.y++"
                   { if((yyvsp[-2].exprVal) != nullptr && (yyvsp[0].exprVal) != nullptr) (yyval.exprVal) = new OpNode(OpNode::LE, (yyvsp[-2].exprVal), (yyvsp[0].exprVal)); else (yyval.exprVal) = nullptr; }
#line 2350 "C+_parser.tab.c++"
    break;

  case 82: /* expr: expr TOK_LT expr  */
#line 388 "C+_parser.y++"
                   { if((yyvsp[-2].exprVal) != nullptr && (yyvsp[0].exprVal) != nullptr) (yyval.exprVal) = new OpNode(OpNode::LT, (yyvsp[-2].exprVal), (yyvsp[0].exprVal)); else (yyval.exprVal) = nullptr; }
#line 2356 "C+_parser.tab.c++"
    break;

  case 83: /* expr: expr TOK_EQ expr  */
#line 389 "C+_parser.y++"
                   { if((yyvsp[-2].exprVal) != nullptr && (yyvsp[0].exprVal) != nullptr) (yyval.exprVal) = new OpNode(OpNode::EQ, (yyvsp[-2].exprVal), (yyvsp[0].exprVal)); else (yyval.exprVal) = nullptr; }
#line 2362 "C+_parser.tab.c++"
    break;

  case 84: /* expr: expr TOK_GE expr  */
#line 390 "C+_parser.y++"
                   { if((yyvsp[-2].exprVal) != nullptr && (yyvsp[0].exprVal) != nullptr) (yyval.exprVal) = new OpNode(OpNode::GE, (yyvsp[-2].exprVal), (yyvsp[0].exprVal)); else (yyval.exprVal) = nullptr; }
#line 2368 "C+_parser.tab.c++"
    break;

  case 85: /* expr: expr TOK_SHR expr  */
#line 391 "C+_parser.y++"
                    { if((yyvsp[-2].exprVal) != nullptr && (yyvsp[0].exprVal) != nullptr) (yyval.exprVal) = new OpNode(OpNode::SHR, (yyvsp[-2].exprVal), (yyvsp[0].exprVal)); else (yyval.exprVal) = nullptr; }
#line 2374 "C+_parser.tab.c++"
    break;

  case 86: /* expr: expr TOK_GT expr  */
#line 392 "C+_parser.y++"
                   { if((yyvsp[-2].exprVal) != nullptr && (yyvsp[0].exprVal) != nullptr) (yyval.exprVal) = new OpNode(OpNode::GT, (yyvsp[-2].exprVal), (yyvsp[0].exprVal)); else (yyval.exprVal) = nullptr; }
#line 2380 "C+_parser.tab.c++"
    break;

  case 87: /* expr: expr TOK_OR expr  */
#line 393 "C+_parser.y++"
                   { if((yyvsp[-2].exprVal) != nullptr && (yyvsp[0].exprVal) != nullptr) (yyval.exprVal) = new OpNode(OpNode::OR, (yyvsp[-2].exprVal), (yyvsp[0].exprVal)); else (yyval.exprVal) = nullptr; }
#line 2386 "C+_parser.tab.c++"
    break;

  case 88: /* expr: expr TOK_BITOR expr  */
#line 394 "C+_parser.y++"
                      { if((yyvsp[-2].exprVal) != nullptr && (yyvsp[0].exprVal) != nullptr) (yyval.exprVal) = new OpNode(OpNode::BITOR, (yyvsp[-2].exprVal), (yyvsp[0].exprVal)); else (yyval.exprVal) = nullptr; }
#line 2392 "C+_parser.tab.c++"
    break;

  case 89: /* expr: expr TOK_MINUS expr  */
#line 395 "C+_parser.y++"
                      { if((yyvsp[-2].exprVal) != nullptr && (yyvsp[0].exprVal) != nullptr) (yyval.exprVal) = new OpNode(OpNode::MINUS, (yyvsp[-2].exprVal), (yyvsp[0].exprVal)); else (yyval.exprVal) = nullptr; }
#line 2398 "C+_parser.tab.c++"
    break;

  case 90: /* expr: expr TOK_NE expr  */
#line 396 "C+_parser.y++"
                   { if((yyvsp[-2].exprVal) != nullptr && (yyvsp[0].exprVal) != nullptr) (yyval.exprVal) = new OpNode(OpNode::NE, (yyvsp[-2].exprVal), (yyvsp[0].exprVal)); else (yyval.exprVal) = nullptr; }
#line 2404 "C+_parser.tab.c++"
    break;

  case 91: /* expr: expr TOK_DIV expr  */
#line 397 "C+_parser.y++"
                    { if((yyvsp[-2].exprVal) != nullptr && (yyvsp[0].exprVal) != nullptr) (yyval.exprVal) = new OpNode(OpNode::DIV, (yyvsp[-2].exprVal), (yyvsp[0].exprVal)); else (yyval.exprVal) = nullptr; }
#line 2410 "C+_parser.tab.c++"
    break;

  case 92: /* expr: expr TOK_MULT expr  */
#line 398 "C+_parser.y++"
                     { if((yyvsp[-2].exprVal) != nullptr && (yyvsp[0].exprVal) != nullptr) (yyval.exprVal) = new OpNode(OpNode::MULT, (yyvsp[-2].exprVal), (yyvsp[0].exprVal)); else (yyval.exprVal) = nullptr; }
#line 2416 "C+_parser.tab.c++"
    break;

  case 93: /* expr: expr TOK_BITAND expr  */
#line 399 "C+_parser.y++"
                       { if((yyvsp[-2].exprVal) != nullptr && (yyvsp[0].exprVal) != nullptr) (yyval.exprVal) = new OpNode(OpNode::BITAND, (yyvsp[-2].exprVal), (yyvsp[0].exprVal)); else (yyval.exprVal) = nullptr; }
#line 2422 "C+_parser.tab.c++"
    break;

  case 94: /* expr: expr TOK_AND expr  */
#line 400 "C+_parser.y++"
                    { if((yyvsp[-2].exprVal) != nullptr && (yyvsp[0].exprVal) != nullptr) (yyval.exprVal) = new OpNode(OpNode::AND, (yyvsp[-2].exprVal), (yyvsp[0].exprVal)); else (yyval.exprVal) = nullptr; }
#line 2428 "C+_parser.tab.c++"
    break;

  case 95: /* expr: expr TOK_MOD expr  */
#line 401 "C+_parser.y++"
                    { if((yyvsp[-2].exprVal) != nullptr && (yyvsp[0].exprVal) != nullptr) (yyval.exprVal) = new OpNode(OpNode::MOD, (yyvsp[-2].exprVal), (yyvsp[0].exprVal)); else (yyval.exprVal) = nullptr; }
#line 2434 "C+_parser.tab.c++"
    break;

  case 96: /* expr: expr TOK_PLUS expr  */
#line 402 "C+_parser.y++"
                     { if((yyvsp[-2].exprVal) != nullptr && (yyvsp[0].exprVal) != nullptr) (yyval.exprVal) = new OpNode(OpNode::PLUS, (yyvsp[-2].exprVal), (yyvsp[0].exprVal)); else (yyval.exprVal) = nullptr; }
#line 2440 "C+_parser.tab.c++"
    break;

  case 97: /* expr: expr_literal  */
#line 403 "C+_parser.y++"
               { (yyval.exprVal) = new ValueNode((yyvsp[0].valVal)); }
#line 2446 "C+_parser.tab.c++"
    break;

  case 98: /* expr: expr_ref  */
#line 404 "C+_parser.y++"
           { (yyval.exprVal) = (yyvsp[0].refexpVal); }
#line 2452 "C+_parser.tab.c++"
    break;

  case 99: /* expr: expr_assignment  */
#line 405 "C+_parser.y++"
                  { (yyval.exprVal) = (yyvsp[0].exprVal); }
#line 2458 "C+_parser.tab.c++"
    break;

  case 100: /* expr: expr_func  */
#line 406 "C+_parser.y++"
            { (yyval.exprVal) = (yyvsp[0].exprVal); }
#line 2464 "C+_parser.tab.c++"
    break;

  case 101: /* expr: expr_set  */
#line 407 "C+_parser.y++"
           { (yyval.exprVal) = (yyvsp[0].exprVal); }
#line 2470 "C+_parser.tab.c++"
    break;

  case 102: /* expr: expr_list  */
#line 408 "C+_parser.y++"
            { (yyval.exprVal) = (yyvsp[0].exprVal); }
#line 2476 "C+_parser.tab.c++"
    break;

  case 103: /* expr: expr_dict  */
#line 409 "C+_parser.y++"
            { (yyval.exprVal) = (yyvsp[0].exprVal); }
#line 2482 "C+_parser.tab.c++"
    break;

  case 104: /* expr: expr_tuple  */
#line 410 "C+_parser.y++"
             { (yyval.exprVal) = (yyvsp[0].exprVal); }
#line 2488 "C+_parser.tab.c++"
    break;

  case 105: /* expr: builtin_func  */
#line 411 "C+_parser.y++"
               { (yyval.exprVal) = (yyvsp[0].exprVal); }
#line 2494 "C+_parser.tab.c++"
    break;

  case 106: /* builtin_func: TOK_EMPTY TOK_LPAREN expr_param TOK_RPAREN  */
#line 414 "C+_parser.y++"
                                                         { 
	if((yyvsp[-1].exprList)->size() < 1){
		errMsg("Missing operand for \"empty\"");
		(yyval.exprVal) = nullptr; 
	}else{
		(yyval.exprVal) = new OpNode(OpNode::EMPTY, (yyvsp[-1].exprList)); 
	}
  }
#line 2507 "C+_parser.tab.c++"
    break;

  case 107: /* builtin_func: TOK_CLEAR TOK_LPAREN expr_param TOK_RPAREN  */
#line 422 "C+_parser.y++"
                                             {
	if((yyvsp[-1].exprList)->size() < 1){
		errMsg("Missing operand for \"clear\"");
		(yyval.exprVal) = nullptr; 
	}else{
		(yyval.exprVal) = new OpNode(OpNode::CLEAR, (yyvsp[-1].exprList)); 
	}
  }
#line 2520 "C+_parser.tab.c++"
    break;

  case 108: /* builtin_func: TOK_LENGTH TOK_LPAREN expr_param TOK_RPAREN  */
#line 430 "C+_parser.y++"
                                              { 
	if((yyvsp[-1].exprList)->size() < 1){
		errMsg("Missing operand(s) for \"length\"");
		(yyval.exprVal) = nullptr; 
	}else{
	        (yyval.exprVal) = new OpNode(OpNode::LENGTH, (yyvsp[-1].exprList)); 
	}
  }
#line 2533 "C+_parser.tab.c++"
    break;

  case 109: /* builtin_func: TOK_APPEND TOK_LPAREN expr_param TOK_RPAREN  */
#line 438 "C+_parser.y++"
                                              { 
	if((yyvsp[-1].exprList)->size() < 2){
		errMsg("Missing operand(s) for \"append\"");
		(yyval.exprVal) = nullptr; 
	}else{
		(yyval.exprVal) = new OpNode(OpNode::APPEND, (yyvsp[-1].exprList)); 
	}
  }
#line 2546 "C+_parser.tab.c++"
    break;

  case 110: /* builtin_func: TOK_UNION TOK_LPAREN expr_param TOK_RPAREN  */
#line 446 "C+_parser.y++"
                                             { 
	if((yyvsp[-1].exprList)->size() < 2){
		errMsg("Missing operand(s) for \"union_\"");
		(yyval.exprVal) = nullptr; 
	}else{
		(yyval.exprVal) = new OpNode(OpNode::UNION, (yyvsp[-1].exprList)); 
	}
  }
#line 2559 "C+_parser.tab.c++"
    break;

  case 111: /* builtin_func: TOK_INSERT TOK_LPAREN expr_param TOK_RPAREN  */
#line 454 "C+_parser.y++"
                                              { 
	if((yyvsp[-1].exprList)->size() == 2) {
		(yyval.exprVal) = new OpNode(OpNode::INS_SET, (yyvsp[-1].exprList));
	}else if((yyvsp[-1].exprList)->size() == 3){
		(yyval.exprVal) = new OpNode(OpNode::INS_VEC, (yyvsp[-1].exprList));
	}else if((yyvsp[-1].exprList)->size() < 2){
		errMsg("Missing operand(s) for \"insert\"");
		(yyval.exprVal) = nullptr; 
	}
  }
#line 2574 "C+_parser.tab.c++"
    break;

  case 112: /* builtin_func: TOK_ERASE TOK_LPAREN expr_param TOK_RPAREN  */
#line 464 "C+_parser.y++"
                                             { 
	if((yyvsp[-1].exprList)->size() < 2){
		errMsg("Missing operand(s) for \"erase\"");
		(yyval.exprVal) = nullptr;  
	}else{
		(yyval.exprVal) = new OpNode(OpNode::ERASE, (yyvsp[-1].exprList)); 
	}
  }
#line 2587 "C+_parser.tab.c++"
    break;

  case 113: /* builtin_func: TOK_CONTAINS TOK_LPAREN expr_param TOK_RPAREN  */
#line 472 "C+_parser.y++"
                                                { 
	if((yyvsp[-1].exprList)->size() < 2){
		errMsg("Missing operand(s) for \"contains\"");
		(yyval.exprVal) = nullptr; 
	}else{
		(yyval.exprVal) = new OpNode(OpNode::CONTAINS, (yyvsp[-1].exprList)); 
	}
  }
#line 2600 "C+_parser.tab.c++"
    break;

  case 114: /* builtin_func: TOK_REMOVE TOK_LPAREN expr_param TOK_RPAREN  */
#line 480 "C+_parser.y++"
                                              { 
	if((yyvsp[-1].exprList)->size() < 2){
		errMsg("Missing operand(s) for \"remove\"");
		(yyval.exprVal) = nullptr; 
	}else{
		(yyval.exprVal) = new OpNode(OpNode::REMOVE, (yyvsp[-1].exprList)); 
	}
   }
#line 2613 "C+_parser.tab.c++"
    break;

  case 115: /* builtin_func: TOK_PRINT TOK_LPAREN expr_param TOK_RPAREN  */
#line 488 "C+_parser.y++"
                                             { (yyval.exprVal) = new OpNode(OpNode::PRINT, (yyvsp[-1].exprList)); }
#line 2619 "C+_parser.tab.c++"
    break;

  case 116: /* builtin_func: TOK_PRINTR TOK_LPAREN expr_param TOK_RPAREN  */
#line 489 "C+_parser.y++"
                                              { (yyval.exprVal) = new OpNode(OpNode::PRINT_RAW, (yyvsp[-1].exprList)); }
#line 2625 "C+_parser.tab.c++"
    break;

  case 117: /* stat: stat_if  */
#line 495 "C+_parser.y++"
              { (yyval.stmtVal) = (yyvsp[0].ifval); }
#line 2631 "C+_parser.tab.c++"
    break;

  case 118: /* stat: stat_empty  */
#line 496 "C+_parser.y++"
             { (yyval.stmtVal) = (yyvsp[0].stmtVal); }
#line 2637 "C+_parser.tab.c++"
    break;

  case 119: /* stat: stat_func  */
#line 497 "C+_parser.y++"
            { (yyval.stmtVal) = (yyvsp[0].stmtVal); }
#line 2643 "C+_parser.tab.c++"
    break;

  case 120: /* stat: stat_assign  */
#line 498 "C+_parser.y++"
              { (yyval.stmtVal) = (yyvsp[0].stmtVal); }
#line 2649 "C+_parser.tab.c++"
    break;

  case 121: /* stat: stat_return  */
#line 499 "C+_parser.y++"
              { (yyval.stmtVal) = (yyvsp[0].stmtVal); }
#line 2655 "C+_parser.tab.c++"
    break;

  case 122: /* stat: stat_comp  */
#line 500 "C+_parser.y++"
            { (yyval.stmtVal) = (yyvsp[0].compoundStmtVal); }
#line 2661 "C+_parser.tab.c++"
    break;

  case 123: /* stat: stat_for  */
#line 501 "C+_parser.y++"
           { (yyval.stmtVal) = (yyvsp[0].listForVal); }
#line 2667 "C+_parser.tab.c++"
    break;

  case 124: /* stat: stat_while  */
#line 502 "C+_parser.y++"
             { (yyval.stmtVal) = (yyvsp[0].whileVal); }
#line 2673 "C+_parser.tab.c++"
    break;

  case 125: /* stat: TOK_LBRACE error TOK_RBRACE  */
#line 503 "C+_parser.y++"
                              { errMsg("Syntax error, expecting a statement"); }
#line 2679 "C+_parser.tab.c++"
    break;

  case 126: /* stat_if: TOK_IF expr stat  */
#line 506 "C+_parser.y++"
                          { (yyval.ifval) = new IfNode((yyvsp[-1].exprVal), (yyvsp[0].stmtVal), nullptr); }
#line 2685 "C+_parser.tab.c++"
    break;

  case 127: /* stat_if: TOK_IF expr stat TOK_ELSE stat  */
#line 507 "C+_parser.y++"
                                 { (yyval.ifval) = new IfNode((yyvsp[-3].exprVal), (yyvsp[-2].stmtVal), (yyvsp[0].stmtVal));  }
#line 2691 "C+_parser.tab.c++"
    break;

  case 128: /* stat_if: TOK_IF expr stat TOK_ELSE error TOK_RBRACE TOK_SEMICOLON  */
#line 508 "C+_parser.y++"
                                                           { errMsg("Syntax error in else statement"); }
#line 2697 "C+_parser.tab.c++"
    break;

  case 129: /* stat_if: TOK_IF expr stat TOK_ELSE error TOK_RBRACE  */
#line 509 "C+_parser.y++"
                                             { errMsg("Syntax error in else statement"); }
#line 2703 "C+_parser.tab.c++"
    break;

  case 130: /* stat_empty: TOK_SEMICOLON  */
#line 512 "C+_parser.y++"
                          { (yyval.stmtVal) = new StmtNode(StmtNode::EMPTY); }
#line 2709 "C+_parser.tab.c++"
    break;

  case 131: /* stat_func: expr_func TOK_SEMICOLON  */
#line 515 "C+_parser.y++"
                                   { (yyval.stmtVal) = new ExprStmtNode((yyvsp[-1].exprVal)); }
#line 2715 "C+_parser.tab.c++"
    break;

  case 132: /* stat_func: builtin_func TOK_SEMICOLON  */
#line 516 "C+_parser.y++"
                             { (yyval.stmtVal) = new ExprStmtNode((yyvsp[-1].exprVal)); }
#line 2721 "C+_parser.tab.c++"
    break;

  case 133: /* stat_assign: expr_assignment TOK_SEMICOLON  */
#line 519 "C+_parser.y++"
                                           { 
	if((yyvsp[-1].exprVal) == nullptr){
		(yyval.stmtVal) = nullptr;
	}else{
		(yyval.stmtVal) = new ExprStmtNode((yyvsp[-1].exprVal)); 
	}
  }
#line 2733 "C+_parser.tab.c++"
    break;

  case 134: /* stat_return: TOK_RETURN expr TOK_SEMICOLON  */
#line 528 "C+_parser.y++"
                                           { 
	FunctionEntry* fe = (FunctionEntry*) stm.currentScope(); 
	(yyval.stmtVal) = new ReturnStmtNode((yyvsp[-1].exprVal), fe);
  }
#line 2742 "C+_parser.tab.c++"
    break;

  case 135: /* stat_return: TOK_RETURN TOK_SEMICOLON  */
#line 532 "C+_parser.y++"
                           { 
	FunctionEntry* fe = (FunctionEntry*) stm.currentScope(); 
	(yyval.stmtVal) = new ReturnStmtNode(nullptr, fe);
  }
#line 2751 "C+_parser.tab.c++"
    break;

  case 136: /* stat_return: TOK_RETURN error TOK_SEMICOLON  */
#line 536 "C+_parser.y++"
                                 { errMsg("Syntax error in return expression"); }
#line 2757 "C+_parser.tab.c++"
    break;

  case 137: /* stat_for: TOK_FOREACH single_ref TOK_IN expr TOK_DO stat  */
#line 539 "C+_parser.y++"
                                                         { (yyval.listForVal) = new ListForNode((yyvsp[-4].refexpVal), (yyvsp[-2].exprVal), (yyvsp[0].stmtVal)); }
#line 2763 "C+_parser.tab.c++"
    break;

  case 138: /* stat_for: TOK_FOREACH single_ref TOK_IN expr stat  */
#line 540 "C+_parser.y++"
                                          { prt("For each statement"); errMsg("Expected keyword 'do'"); }
#line 2769 "C+_parser.tab.c++"
    break;

  case 139: /* stat_for: TOK_FOREACH error  */
#line 541 "C+_parser.y++"
                    { errMsg("Syntax error in for statement"); }
#line 2775 "C+_parser.tab.c++"
    break;

  case 140: /* stat_while: TOK_WHILE expr TOK_DO stat_comp  */
#line 544 "C+_parser.y++"
                                            { (yyval.whileVal) = new WhileNode((yyvsp[-2].exprVal), (yyvsp[0].compoundStmtVal)); }
#line 2781 "C+_parser.tab.c++"
    break;

  case 141: /* stat_while: TOK_WHILE expr stat  */
#line 545 "C+_parser.y++"
                      { 
	(yyval.whileVal) = new WhileNode((yyvsp[-1].exprVal), nullptr); 
	errMsg("Expected keyword 'do'");
}
#line 2790 "C+_parser.tab.c++"
    break;

  case 142: /* stat_while: TOK_WHILE error TOK_DO stat_comp  */
#line 549 "C+_parser.y++"
                                   { 
	//$$ = new WhileNode(nullptr, $4); 
	errMsg("Syntax error in while-statement condition");
}
#line 2799 "C+_parser.tab.c++"
    break;

  case 143: /* stat_comp: block_enter stat_comp_body block_leave  */
#line 555 "C+_parser.y++"
                                                  { (yyval.compoundStmtVal) = new CompoundStmtNode((yyvsp[-2].blockEntry), (yyvsp[-1].stmtList)); }
#line 2805 "C+_parser.tab.c++"
    break;

  case 144: /* stat_comp: block_enter stat_bad_body block_leave  */
#line 556 "C+_parser.y++"
                                        { (yyval.compoundStmtVal) = new CompoundStmtNode((yyvsp[-2].blockEntry), (yyvsp[-1].stmtList)); }
#line 2811 "C+_parser.tab.c++"
    break;

  case 145: /* block_enter: TOK_LBRACE  */
#line 559 "C+_parser.y++"
                        { 
	(yyval.blockEntry) = new BlockEntry("{", yylinenum, 0, yyfilename);
 	stm.enterScope((yyval.blockEntry));
	stm.insert((yyval.blockEntry));
}
#line 2821 "C+_parser.tab.c++"
    break;

  case 146: /* block_leave: TOK_RBRACE  */
#line 566 "C+_parser.y++"
                        { stm.leaveScope(); }
#line 2827 "C+_parser.tab.c++"
    break;

  case 147: /* block_leave: TOK_RBRACE TOK_SEMICOLON  */
#line 567 "C+_parser.y++"
                           { stm.leaveScope(); }
#line 2833 "C+_parser.tab.c++"
    break;

  case 150: /* var_decl_list_2: var_decl  */
#line 574 "C+_parser.y++"
                          { errMsg("Declarations should precede all statements"); }
#line 2839 "C+_parser.tab.c++"
    break;

  case 151: /* var_decl_list_2: var_decl_list_2 var_decl  */
#line 575 "C+_parser.y++"
                           { errMsg("Declarations should precede all statements"); }
#line 2845 "C+_parser.tab.c++"
    break;

  case 152: /* stat_comp_body: var_decl_list stat_sequence  */
#line 578 "C+_parser.y++"
                                            { (yyval.stmtList) = (yyvsp[0].stmtList); }
#line 2851 "C+_parser.tab.c++"
    break;

  case 153: /* stat_bad_body: var_decl_list stat_sequence bad_body_star  */
#line 581 "C+_parser.y++"
                                                         { 
	list<StmtNode*>::iterator it = (yyvsp[0].stmtList)->begin();
	for(; it != (yyvsp[0].stmtList)->end(); it ++){
		(yyvsp[-1].stmtList)->push_back(*it);
	}
	(yyval.stmtList) = (yyvsp[-1].stmtList);
  }
#line 2863 "C+_parser.tab.c++"
    break;

  case 154: /* bad_body: var_decl_list_2 stat_sequence  */
#line 590 "C+_parser.y++"
                                        { (yyval.stmtList) = (yyvsp[0].stmtList); }
#line 2869 "C+_parser.tab.c++"
    break;

  case 155: /* bad_body_star: bad_body  */
#line 593 "C+_parser.y++"
                         { (yyval.stmtList) = (yyvsp[0].stmtList); }
#line 2875 "C+_parser.tab.c++"
    break;

  case 156: /* bad_body_star: bad_body_star bad_body  */
#line 594 "C+_parser.y++"
                         { 
	list<StmtNode*>::iterator it = (yyvsp[0].stmtList)->begin();
	for(; it != (yyvsp[0].stmtList)->end(); it ++){
		(yyvsp[-1].stmtList)->push_back(*it);
	}
	(yyval.stmtList) = (yyvsp[-1].stmtList);
  }
#line 2887 "C+_parser.tab.c++"
    break;

  case 157: /* stat_sequence: stat  */
#line 603 "C+_parser.y++"
                    {
  	(yyval.stmtList) = new list<StmtNode*>();
  	if((yyvsp[0].stmtVal) != nullptr){
  		(yyval.stmtList)->push_back((yyvsp[0].stmtVal));
  	}
  }
#line 2898 "C+_parser.tab.c++"
    break;

  case 158: /* stat_sequence: stat_sequence stat  */
#line 609 "C+_parser.y++"
                     { 
	if((yyvsp[-1].stmtList) != nullptr && (yyvsp[0].stmtVal) != nullptr){
		(yyvsp[-1].stmtList)->push_back((yyvsp[0].stmtVal));
	}	
	(yyval.stmtList) = (yyvsp[-1].stmtList);
  }
#line 2909 "C+_parser.tab.c++"
    break;

  case 159: /* func: func_decl TOK_SEMICOLON  */
#line 620 "C+_parser.y++"
                              { 
	stm.leaveScope();
}
#line 2917 "C+_parser.tab.c++"
    break;

  case 160: /* func: func_const_decl TOK_SEMICOLON  */
#line 623 "C+_parser.y++"
                                {
	stm.leaveScope();
}
#line 2925 "C+_parser.tab.c++"
    break;

  case 161: /* func: func_decl func_body  */
#line 626 "C+_parser.y++"
                      { 
	(yyvsp[-1].functionEntry)->body((yyvsp[0].compoundStmtVal)); 
	stm.leaveScope();
}
#line 2934 "C+_parser.tab.c++"
    break;

  case 162: /* func: func_const_decl func_body  */
#line 630 "C+_parser.y++"
                            { 
	(yyvsp[-1].functionEntry)->body((yyvsp[0].compoundStmtVal)); 
	stm.leaveScope();
}
#line 2943 "C+_parser.tab.c++"
    break;

  case 163: /* func_head: type TOK_ID TOK_LPAREN  */
#line 636 "C+_parser.y++"
                                  {
	(yyval.functionEntry) = new FunctionEntry((yyvsp[-1].cVal), (yyvsp[-2].typeVal), yylinenum, 0, yyfilename);
	ErrorST state = stm.insert((yyval.functionEntry));
	if ( state == DUPLICATE_SYM )
		errMsg("Redefinition of name " + (yyval.functionEntry)->name());
	else if ( state == INVALID_SCOPE )
		errMsg("Invalid Scope");
	stm.enterScope((yyval.functionEntry));
}
#line 2957 "C+_parser.tab.c++"
    break;

  case 164: /* func_head: TOK_CONST type TOK_ID TOK_LPAREN  */
#line 645 "C+_parser.y++"
                                   {
	(yyvsp[-2].typeVal)->constType(true);
	(yyval.functionEntry) = new FunctionEntry((yyvsp[-1].cVal), (yyvsp[-2].typeVal), yylinenum, 0, yyfilename);
	ErrorST state = stm.insert((yyval.functionEntry));
	if ( state == DUPLICATE_SYM )
		errMsg("Redefinition of name " + (yyval.functionEntry)->name());
	else if ( state == INVALID_SCOPE )
		errMsg("Invalid Scope");
	stm.enterScope((yyval.functionEntry));
}
#line 2972 "C+_parser.tab.c++"
    break;

  case 165: /* func_decl: func_head func_param TOK_RPAREN  */
#line 656 "C+_parser.y++"
                                           { (yyval.functionEntry) = (yyvsp[-2].functionEntry); }
#line 2978 "C+_parser.tab.c++"
    break;

  case 166: /* func_decl: func_head TOK_RPAREN  */
#line 657 "C+_parser.y++"
                       { (yyval.functionEntry) = (yyvsp[-1].functionEntry); }
#line 2984 "C+_parser.tab.c++"
    break;

  case 167: /* func_decl: func_head error TOK_RPAREN  */
#line 659 "C+_parser.y++"
                             { errMsg("Syntax error in formal parameter declaration"); }
#line 2990 "C+_parser.tab.c++"
    break;

  case 168: /* func_decl: func_head func_param error  */
#line 660 "C+_parser.y++"
                             { errMsg("Error while parsing function formal parameters, missing closing parenthesis"); }
#line 2996 "C+_parser.tab.c++"
    break;

  case 169: /* func_decl: func_head error  */
#line 661 "C+_parser.y++"
                  { errMsg("Error while parsing function formal parameters, missing closing parenthesis"); }
#line 3002 "C+_parser.tab.c++"
    break;

  case 170: /* func_decl: known_type TOK_LPAREN func_param TOK_RPAREN  */
#line 662 "C+_parser.y++"
                                              { prt("FunctionDecl"); errMsg("Expecting a function declaration -- may be a missing function name"); }
#line 3008 "C+_parser.tab.c++"
    break;

  case 171: /* func_decl: known_type TOK_LPAREN TOK_RPAREN  */
#line 663 "C+_parser.y++"
                                   { prt("FunctionDecl"); errMsg("Expecting a function declaration -- may be a missing function name"); }
#line 3014 "C+_parser.tab.c++"
    break;

  case 172: /* func_decl: TOK_ID error TOK_LPAREN func_param TOK_RPAREN  */
#line 664 "C+_parser.y++"
                                                { prt("FunctionDecl"); errMsg("Expecting a function declaration -- may be a missing type or a function name"); }
#line 3020 "C+_parser.tab.c++"
    break;

  case 173: /* func_decl: TOK_ID error TOK_LPAREN TOK_RPAREN  */
#line 665 "C+_parser.y++"
                                     { prt("FunctionDecl"); errMsg("Expecting a function declaration -- may be a missing type or a function name"); }
#line 3026 "C+_parser.tab.c++"
    break;

  case 174: /* func_const_decl: func_head func_param TOK_RPAREN TOK_CONST  */
#line 668 "C+_parser.y++"
                                                           { (yyval.functionEntry) = (yyvsp[-3].functionEntry); }
#line 3032 "C+_parser.tab.c++"
    break;

  case 175: /* func_const_decl: func_head TOK_RPAREN TOK_CONST  */
#line 669 "C+_parser.y++"
                                 { (yyval.functionEntry) = (yyvsp[-2].functionEntry); }
#line 3038 "C+_parser.tab.c++"
    break;

  case 176: /* func_const_decl: func_head error TOK_RPAREN TOK_CONST  */
#line 671 "C+_parser.y++"
                                       { errMsg("Syntax error in formal parameter declaration"); }
#line 3044 "C+_parser.tab.c++"
    break;

  case 177: /* func_const_decl: func_head func_param error TOK_CONST  */
#line 672 "C+_parser.y++"
                                        { errMsg("Error while parsing function formal parameters, missing closing parenthesis"); }
#line 3050 "C+_parser.tab.c++"
    break;

  case 178: /* func_const_decl: func_head error TOK_CONST  */
#line 673 "C+_parser.y++"
                            { errMsg("Error while parsing function formal parameters, missing closing parenthesis"); }
#line 3056 "C+_parser.tab.c++"
    break;

  case 179: /* func_const_decl: known_type TOK_LPAREN func_param TOK_RPAREN TOK_CONST  */
#line 674 "C+_parser.y++"
                                                        { prt("Const FunctionDecl"); errMsg("Expecting a function declaration -- may be a missing function name"); }
#line 3062 "C+_parser.tab.c++"
    break;

  case 180: /* func_const_decl: known_type TOK_LPAREN TOK_RPAREN TOK_CONST  */
#line 675 "C+_parser.y++"
                                             { prt("Const FunctionDecl"); errMsg("Expecting a function declaration -- may be a missing function name"); }
#line 3068 "C+_parser.tab.c++"
    break;

  case 181: /* func_const_decl: TOK_ID error TOK_LPAREN func_param TOK_RPAREN TOK_CONST  */
#line 676 "C+_parser.y++"
                                                          { prt("Const FunctionDecl"); errMsg("Expecting a function declaration -- may be a missing type or a function name"); }
#line 3074 "C+_parser.tab.c++"
    break;

  case 182: /* func_const_decl: TOK_ID error TOK_ID TOK_LPAREN TOK_RPAREN TOK_CONST  */
#line 677 "C+_parser.y++"
                                                      { prt("Const FunctionDecl"); errMsg("Expecting a function declaration -- may be a missing type or a function name"); }
#line 3080 "C+_parser.tab.c++"
    break;

  case 183: /* func_body: stat_comp  */
#line 680 "C+_parser.y++"
                     { (yyval.compoundStmtVal) = (yyvsp[0].compoundStmtVal); }
#line 3086 "C+_parser.tab.c++"
    break;

  case 186: /* formal_param: type TOK_ID  */
#line 687 "C+_parser.y++"
                          { 
	(yyval.variableEntry) = new VariableEntry((yyvsp[0].cVal), FN_PARAM_VAR, (yyvsp[-1].typeVal), 0, yylinenum, 0, yyfilename);
	ErrorST state = stm.insert((yyval.variableEntry));
	if ( state == DUPLICATE_SYM ) {
		errMsg("Redefinition of name " + string((yyvsp[0].cVal)));
	}
	else if ( state == INVALID_SCOPE ) {
		errMsg("Invalid Scope");
	}
}
#line 3101 "C+_parser.tab.c++"
    break;

  case 187: /* formal_param: TOK_CONST type TOK_ID  */
#line 697 "C+_parser.y++"
                        {
	(yyvsp[-1].typeVal)->constType(true);
	(yyval.variableEntry) = new VariableEntry((yyvsp[0].cVal), FN_PARAM_VAR, (yyvsp[-1].typeVal), 0, yylinenum, 0, yyfilename);
	ErrorST state = stm.insert((yyval.variableEntry));
	if ( state == DUPLICATE_SYM ) {
		errMsg("Redefinition of name " + string((yyvsp[0].cVal)));
	}
	else if ( state == INVALID_SCOPE ) {
		errMsg("Invalid Scope");
	}
}
#line 3117 "C+_parser.tab.c++"
    break;


#line 3121 "C+_parser.tab.c++"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 722 "C+_parser.y++"


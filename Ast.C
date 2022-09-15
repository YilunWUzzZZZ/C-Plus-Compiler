#include "Ast.h"
#include "ParserUtil.h"
#include "MemAlloc.h"
#include "IRGen.h"
#include "IR.h"
#include "STEClasses.h"
#include "Type.h"


AstNode::AstNode(AstNodeType nt, int line, int column, string file):
  ProgramElem(nullptr, line, column, file) {
  nodeType_ = nt;
}

ExprNode::ExprNode(ExprNodeType et, const Value* val, int line, int col,
           string file):
  AstNode(EXPR_NODE, line, col, file) {
  exprType_ = et;
  val_ = val;
  coercedType_ = nullptr;
}

/******************************  IfNode  **********************************/
IfNode::IfNode(ExprNode* cond, StmtNode* thenStmt, StmtNode* elseStmt, int line, int column, string file):
  StmtNode(StmtNode::IF,line,column,file) {
	cond_ = cond;
	then_ = thenStmt;
	else_ = elseStmt;
}

void
IfNode::print(ostream& os, int indent) const{
	os << "if (";
	if (cond_ != nullptr){
		cond_->print(os, indent);
	}
	os << ") ";

	if(then_ != nullptr){
		then_->print(os, indent);
		if(then_->stmtNodeKind() == StmtNode::COMPOUND){
			endln(os, indent);
		}else{
			prtln(os, indent);
		}
	}
	if(else_ != nullptr){
		os << "else ";
		else_->print(os, indent);
		os << ";";

	}
	if(then_ != nullptr && else_ != nullptr){
		prtln(os, indent);
	}
}

// Yan 11/18
const Type*
IfNode::typeCheck(){
  if(cond_ != nullptr){
    const Type* cond_type = cond_->typeCheck();
    if(cond_type == nullptr){
      errMsg("Boolean argument expected", line(), column(), file().c_str());
    }else if(!Type::isBool(cond_type->tag())){
      errMsg("Boolean argument expected", line(), column(), file().c_str());
    }
  }

  if(then_ != nullptr && then_->stmtNodeKind() != StmtNode::EMPTY){
    then_->typeCheck();
  }

  if(else_ != nullptr){
    else_->typeCheck();
  }

  return nullptr;
}

void
IfNode::typePrint(ostream& os, int indent) const{
  os << "if (";
  if (cond_ != nullptr){
    cond_->typePrint(os, indent);
  }
  os << ") ";

  if(then_ != nullptr){
    then_->typePrint(os, indent);
    if(then_->stmtNodeKind() == StmtNode::COMPOUND){
      endln(os, indent);
    }else{
      prtln(os, indent);
    }
  }
  if(else_ != nullptr){
    os << "else ";
    else_->typePrint(os, indent);
    os << ";";
  }
  if(then_ != nullptr && else_ != nullptr){
    prtln(os, indent);
  }
}

/******************************  ListForNode  **********************************/
void
ListForNode::print(ostream& os, int indent) const{
	os << "foreach ";
	if(indexVar_ != nullptr){
		indexVar_->print(os, indent);
		os << " ";
	}
	os << "in ";
	if(list_ != nullptr){
		list_->print(os, indent);
		os << " ";
	}
	os << "do ";
	if(body_ != nullptr){
		body_->print(os, indent);
		if(body_->stmtNodeKind() == StmtNode::COMPOUND){
			endln(os, indent);
		}
	}
}

// Yan 11/18
const Type*
ListForNode::typeCheck(){
  if(indexVar_ != nullptr){
		indexVar_->typeCheck();
	}
	if(list_ != nullptr){
		list_->typeCheck();
	}
	if(body_ != nullptr){
		body_->typeCheck();
	}
  return nullptr;
}

void
ListForNode::typePrint(ostream& os, int indent) const{
  os << "foreach ";
  if(indexVar_ != nullptr){
    indexVar_->print(os, indent);
    os << " ";
  }
  os << "in ";
  if(list_ != nullptr){
    list_->print(os, indent);
    os << " ";
  }
  os << "do ";
  if(body_ != nullptr){
    body_->print(os, indent);
    if(body_->stmtNodeKind() == StmtNode::COMPOUND){
      endln(os, indent);
    }
  }
}

/******************************  WhileNode  **********************************/
void
WhileNode::print(ostream& os, int indent) const{
  os << "while";
	os << " (";
	if(cond_ != nullptr){
		cond_->print(os, indent);
	}
	os << ") ";

	if(body_ != nullptr){
		body_->print(os, indent);
		if(body_->stmtNodeKind() == StmtNode::COMPOUND){
			endln(os, indent);
		}
	}
}

// Yan 11/18
const Type*
WhileNode::typeCheck(){
  if(cond_ != nullptr){
		cond_->typeCheck();
	}

	if(body_ != nullptr){
		body_->typeCheck();
	}
  return nullptr;
}

void
WhileNode::typePrint(ostream& os, int indent) const{
  os << "while";
  os << " (";
  if(cond_ != nullptr){
    cond_->typePrint(os, indent);
  }
  os << ") ";

  if(body_ != nullptr){
    body_->typePrint(os, indent);
    if(body_->stmtNodeKind() == StmtNode::COMPOUND){
      endln(os, indent);
    }
  }
}

/******************************  CompoundStmtNode  **********************************/
void
CompoundStmtNode::print(ostream& os, int indent) const{
	os << "{\n";
	emitWithoutBraces(os, indent);
	bool flag = true;
	if(stmts_!= nullptr && stmts_->size() != 0){
		if(stmts_->back() != nullptr && stmts_->back()->stmtNodeKind() == StmtNode::EXPR){
			ExprStmtNode* esn = (ExprStmtNode*)stmts_->back();
			if(esn->expr() != nullptr && esn->expr()->exprNodeType() == INV_NODE){
				InvocationNode* in = (InvocationNode*)esn->expr();
				const SymTabEntry* in_ste = in->symTabEntry();
				if(in_ste == nullptr){
					flag = false;
				}
			}
		}

		if(flag){
			prtln(os, indent);
		}
	}

    	os << "}";
}

void
CompoundStmtNode::emitWithoutBraces(ostream& os, int indent) const{
	if(decls_ != nullptr){
		decls_->print(os, indent);
	}

	if(stmts_!= nullptr && stmts_->size() != 0){
		list<StmtNode*>::const_iterator it = stmts_->begin();
		for(; it != stmts_->end(); it ++){
			if((*it) != nullptr){
				(*it)->print(os, indent+STEP_INDENT);
			}
		}
	}
}

// Yan 11/18
const Type*
CompoundStmtNode::typeCheck(){

  if(decls_ != nullptr){
    decls_->typeCheck();
  }

  if(stmts_!= nullptr && stmts_->size() != 0){
    list<StmtNode*>::const_iterator it = stmts_->begin();
    for(; it != stmts_->end(); it ++){
      if((*it) != nullptr && (*it)->stmtNodeKind() != StmtNode::EMPTY){
        (*it)->typeCheck();
      }
    }
  }

  return nullptr;
}

void
CompoundStmtNode::typePrint(ostream& os, int indent) const{
  os << "{\n";
  typePrintWithoutBraces(os, indent);
  bool flag = true;
  if(stmts_!= nullptr && stmts_->size() != 0){
    if(stmts_->back() != nullptr && stmts_->back()->stmtNodeKind() == StmtNode::EXPR){
      ExprStmtNode* esn = (ExprStmtNode*)stmts_->back();
      if(esn->expr() != nullptr && esn->expr()->exprNodeType() == INV_NODE){
        InvocationNode* in = (InvocationNode*)esn->expr();
        const SymTabEntry* in_ste = in->symTabEntry();
        if(in_ste == nullptr){
          flag = false;
        }
      }
    }

    if(flag){
      prtln(os, indent);
    }
  }
  os << "}";
}

void
CompoundStmtNode::typePrintWithoutBraces(ostream& os, int indent) const{
  if(decls_ != nullptr){
    decls_->typePrint(os, indent);
  }

  if(stmts_!= nullptr && stmts_->size() != 0){
    list<StmtNode*>::const_iterator it = stmts_->begin();
    prtSpace(os, indent+STEP_INDENT);
    for(; it != stmts_->end(); it ++){
      if((*it) != nullptr){
        (*it)->typePrint(os, indent+STEP_INDENT);
      }
    }
  }
}

/******************************  ReturnStmtNode  **********************************/
void
ReturnStmtNode::print(ostream& os, int indent) const{
	os << "return ";
	if(expr_ != nullptr){
		expr_->print(os, indent);
	}else{
		os << "nullptr";
	}
	os << ";";
}

// Yan 11/15
const Type*
ReturnStmtNode::typeCheck(){
  Type voidType = Type();
  const Type* return_type = fun_->type()->retType();
  const Type* expr_type = expr_?expr_->typeCheck():&voidType;

  if(return_type == nullptr || expr_type == nullptr){
    errMsg("Return value incompatible with current function's type", line(), column(), file().c_str());
    return nullptr;
  }else{
    if(return_type->tag() != expr_type->tag()){
      if(expr_type->isSubType(return_type->tag())){
        expr_->setCoercedType(return_type);
      }else{
        errMsg("Return value incompatible with current function's type", line(), column(), file().c_str());
      }
    }
  }
  return nullptr;
}

void
ReturnStmtNode::typePrint(ostream& os, int indent) const{
  os << "return ";
	if(expr_ != nullptr){
		expr_->typePrint(os, indent);
	}else{
		os << "nullptr";
	}
	os << ";";
}

/******************************  ExprStmtNode  **********************************/
void
ExprStmtNode::print(ostream& os, int indent) const{
	if(expr_ != nullptr){
		expr_->print(os, indent);
		bool flag = true;
		if(expr_->exprNodeType() == INV_NODE){
			InvocationNode* in = (InvocationNode*)expr_;
			const SymTabEntry* in_ste = in->symTabEntry();
			if(in_ste == nullptr){
				flag = false;
			}
		}
		if(flag){
			endln(os, indent);
		}else{
			endln(os, indent-STEP_INDENT);
		}
	}else{
		os << ";";
	}

}

// Yan 11/17
const Type*
ExprStmtNode::typeCheck(){
  if(expr_ != nullptr){
    expr_->typeCheck();
  }
  return nullptr;
}

void
ExprStmtNode::typePrint(ostream& os, int indent) const{
  if(expr_ != nullptr){
		expr_->typePrint(os, indent);
		bool flag = true;
		if(expr_->exprNodeType() == INV_NODE){
			InvocationNode* in = (InvocationNode*)expr_;
			const SymTabEntry* in_ste = in->symTabEntry();
			if(in_ste == nullptr){
				flag = false;
			}
		}
		if(flag){
			endln(os, indent);
		}else{
			endln(os, indent-STEP_INDENT);
		}
	}else{
		os << ";";
	}
}

/******************************  InvocationNode  **********************************/
InvocationNode::InvocationNode(SymTabEntry *ste, vector<ExprNode*>* param, int line, int column, string file):
 ExprNode(INV_NODE, nullptr, line, column, file){
	params_ = param;
	ste_ = ste;
}

void
InvocationNode::print(ostream& os, int indent) const{
 	if(ste_ != nullptr){
 		FunctionEntry* fe = (FunctionEntry*) ste_;
 		os << fe->name() << "(";
 		if(params_!= nullptr && params_->size() != 0){
 	 		std::vector<ExprNode*>::const_iterator it = params_->begin();
 	 		if((*it) != nullptr){
 	 			(*it)->print(os, indent);
 	 		}
 			for(it ++; it != params_->end(); it ++){
 				if((*it) != nullptr){
 					os << ", ";
 					(*it)->print(os, indent);
 				}
 			}
 		}
 		os << ")";
 	}
}

// Yan 11/17 updated: Yan 11/18
const Type*
InvocationNode::typeCheck(){
  FunctionEntry* fe = (FunctionEntry*) symTabEntry();
  if(fe != nullptr && fe->type() != nullptr){
    vector<Type*>* formal_param_type = fe->type()->argTypes();
    const Type* return_type = fe->type()->retType();
    if(return_type != nullptr){
      type(new Type(return_type->tag()));
    }

    if(params_ != nullptr && formal_param_type != nullptr && formal_param_type->size() == params_->size()){

      for(size_t i = 0; i < params_->size(); i ++){
        const Type* param = params_->at(i)->typeCheck();
        const Type* formal = formal_param_type->at(i);

        if(param == nullptr || formal == nullptr){
          errMsg("Error in formal paramter type or in parameter type", line(), column(), file().c_str());
          return type();
        }
        if(param->tag() != formal->tag()){
          if(param->isSubType(formal->tag())){
            params_->at(i)->setCoercedType(formal);
          }else{
            errMsg(fe->name() + ": Type mismatch for argument " + to_string(i+1) + " (expected: " + formal->fullName() + ", got " + param->fullName() + ")", line(), column(), file().c_str());
          }
        }
      }
    }
  }

  return type();
}

void
InvocationNode::typePrint(ostream& os, int indent) const{
  FunctionEntry* fe = (FunctionEntry*) symTabEntry();
  if(fe != nullptr){
    os << fe->name() << "(";
    if(params_ != nullptr){
      vector<ExprNode*>::const_iterator it = params_->begin();
      if((*it) != nullptr){
          (*it)->typePrint(os, indent);
      }
      for(++it; it != params_->end(); ++it){
        if(*it != nullptr){
          os << ", ";
          (*it)->typePrint(os, indent);
        }
      }
    }
    os << ")";
  }
}

/******************************  ValueNode  **********************************/
void
ValueNode::print(ostream& os, int indent) const{
	if(value()){
		value()->print(os, indent);
	}
}

// Yan 11/15
const Type*
ValueNode::typeCheck(){
  return type();
}

void
ValueNode::typePrint(ostream& os, int indent) const{
  // valuenode is a subclass of exprnode, which contains a member named coercedType_
  if(getCoercedType() != nullptr){
    os << "(";
    getCoercedType()->print(os, indent);
    os << ") ";
  }
  type()->print(os, indent);
}

/******************************  RefExprNode  **********************************/
void
RefExprNode::addSubs(ExprNode* e){
	if (subscript_ == nullptr)
		subscript_ = new vector<ExprNode*>();
  subscript_->push_back(e);
}

RefExprNode::RefExprNode(RefExprNode* base, string ext, SymTabEntry* ste, int line, int columns, string file):
 ExprNode(REF_EXPR_NODE, nullptr, line, columns, file){
	base_ = base;
	ext_ = ext;
	sym_ = ste;
}

void
RefExprNode::print(ostream& os, int indent) const{
	os << ext_;
	if(subscript_ != nullptr && subscript_->size() != 0){
		vector<ExprNode*>::const_iterator it = subscript_->begin();
		for(; it != subscript_->end(); it ++){
			if((*it) != nullptr){
				os << "[";
			  (*it)->print(os, indent);
				os << "]";
			}
		}
	}
}

// Yan 11/16 Updated: Yan 11/17
const Type*
RefExprNode::typeCheck(){
  if(sym_ != nullptr){
    type(sym_->type());
    if (nsubs()) {
      for (size_t i=0; i<subscript_->size(); i++) {
        auto subscriptType = subscript_->at(i)->typeCheck();
        if (!subscriptType->isIntegral()) {
          errMsg("Invalid type for array subscript", this);
        }
      }
    }
    return sym_->type();
  }
  return nullptr;
}

void
RefExprNode::typePrint(ostream& os, int indent) const{
  if(getCoercedType() != nullptr){
    os << "(";
    getCoercedType()->print(os, indent);
    os << ") ";
  }

  if(sym_ != nullptr){
    sym_->typePrint(os, indent);
  }
}

/******************************  OpNode  **********************************/
const OpNode::OpInfo opInfo[] = {
  // print name, arity, paren_flag, fixity, arg types, out type, constraints
  //
  // Paren_flag -- opnode->print() outputs is surrounded by parenthesis if
  // this flag is set. As set below, the expression may not print correctly
  // in some rare cases, e.g., ~(b * c) will get printed as ~b * c,
  // which actually corresponds to (~b)*c. To ensure that things get printed
  // correctly all the time, more paren_flags should be set to 1, but this
  // will lead to more clutter in printed output. Basically, what we have done
  // here is to look are expressions by type -- arithmetic, relational,
  // boolean, bit operations, etc. Within each type, the highest priority
  // operator is printed without paren. This will work correctly, as long
  // as the language doesn't permit mixing of different types of expressions.
  // But this assumption doesn't always hold, as in the example above. Also,
  // there is an exception to this general approach in the case of unary minus
  // and * -- since (-a)*b and -(a*b) have the same meaning, we can exclude
  // paren for * without an error.
  //
  // Codes for constraints:
  // first character:
  //    a digit, indicating which of the first 3 arguments are modified
  //    by the operation. (All other arguments are assumed to be unmodified
  //    by the operation.) A value '0' indicates an operation that changes no
  //    no arguments, while '5' indicates that the first and third arguments
  //    are modified.
  //    A special value 's' indicates that the function has some global
  //    side-effect but does not modify any arguments.
  // second character:
  //    N: No additional constraint over what is given by argTypes
  //    S: one of the arguments must have a type that is a supertype of
  //        of all other arguments. All other arguments require a coercion
  //        operation to be introduced so as to convert their type to S.
  //    A: (assignment). Type of second argument must be a subtype of
  //       the first argument
  //    E: All arguments should have exact same type
  //    k: If the first argument is a collection type, second argument should
  //       be key type (elemtype, in case of non-key based collections)
  //
  // third character:
  //    N: No additional checks
  //    O: output type is the same as out type. (In the following cases,
  //        the output type need not be equal to out type, but a subtype
  //        of it.) Since a TypeTag provides complete type information only
  //        for primitive types, `O' is applicable only in this case.
  //    digit: (1..9) output type is the same as that of the digit'th argument
  //
  //    S: The output type is the same as that of the argument with the
  //        most general type. (Typically used with first character 'S')
  //
  // fourth character: (Used to control top-down propagation of coercions)
  //    N: No coercions needed.
  //    T: Coerce to the specified type of input
  //    M: Compute the most general type among all args, coerce all to this type
  //    C: Similar to M, but in addition, if argument is a constant and a
  //       subtype of int, then coerce to int type.
  //    n: If output is double and input integral, propagate long or unsigned
  //       long, depending on whether an input arg. is integral and/or signed.
  //    g: All arguments are coerced to the most general type among the arguments.
  //       If the output type is more general than arguments, then arguments are
  //       instead coerced to this type. An exception occurs when output is
  //       double but inputs are integral: in this case, inputs are generalized
  //       to long (or unsigned long, depending on signedness)


  {OpNode::UMINUS, "-",  1, 0, OpNode::PREFIX, {Type::NUMERIC}, Type::SIGNED,                    "0N1g"},
  {OpNode::PLUS, "+",  2, 1, OpNode::INFIX, {Type::NUMERIC, Type::NUMERIC}, Type::NUMERIC,       "0SSg"},
  {OpNode::MINUS, "-",  2, 1, OpNode::INFIX, {Type::NUMERIC, Type::NUMERIC}, Type::NUMERIC,      "0SSg"},
  {OpNode::MULT, "*",  2, 0, OpNode::INFIX, {Type::NUMERIC, Type::NUMERIC}, Type::NUMERIC,       "0SSg"},
  {OpNode::DIV, "/",  2, 1, OpNode::INFIX, {Type::NUMERIC, Type::NUMERIC}, Type::NUMERIC,        "0SSg"},

  {OpNode::MOD, "%",  2, 1, OpNode::INFIX, {Type::INTEGRAL, Type::INTEGRAL}, Type::INTEGRAL,     "0S2n"},

  {OpNode::EQ, "==", 2, 0, OpNode::INFIX, {Type::NATIVE, Type::NATIVE}, Type::BOOL,              "0SOC"},
  {OpNode::NE, "!=", 2, 0, OpNode::INFIX, {Type::NATIVE, Type::NATIVE}, Type::BOOL,              "0SOC"},
  {OpNode::GT, ">",  2, 0, OpNode::INFIX, {Type::PRIMITIVE, Type::PRIMITIVE}, Type::BOOL,        "0SOC"},
  {OpNode::LT, "<",  2, 0, OpNode::INFIX, {Type::PRIMITIVE, Type::PRIMITIVE}, Type::BOOL,        "0SOC"},
  {OpNode::GE, ">=", 2, 0, OpNode::INFIX, {Type::PRIMITIVE, Type::PRIMITIVE}, Type::BOOL,        "0SOC"},
  {OpNode::LE, "<=", 2, 0, OpNode::INFIX, {Type::PRIMITIVE, Type::PRIMITIVE}, Type::BOOL,        "0SOC"},


  {OpNode::AND, "&&",  2, 1, OpNode::INFIX, {Type::BOOL, Type::BOOL}, Type::BOOL,                "0NOO"},
  {OpNode::OR, "||",  2, 1, OpNode::INFIX, {Type::BOOL, Type::BOOL}, Type::BOOL,                 "0NOO"},
  {OpNode::NOT, "!",  1, 0, OpNode::PREFIX, {Type::BOOL}, Type::BOOL,                            "0NOO"},

  {OpNode::BITNOT, "~",  1, 0, OpNode::PREFIX, {Type::INTEGRAL}, Type::INTEGRAL,                 "0N1n"},
  {OpNode::BITAND, "&",  2, 1, OpNode::INFIX, {Type::INTEGRAL, Type::INTEGRAL}, Type::INTEGRAL,  "0SSn"},
  {OpNode::BITOR, "|",  2, 1, OpNode::INFIX, {Type::INTEGRAL, Type::INTEGRAL}, Type::INTEGRAL,   "0SSn"},
  {OpNode::BITXOR, "^",  2, 0, OpNode::INFIX, {Type::INTEGRAL, Type::INTEGRAL}, Type::INTEGRAL,  "0SSn"},

  {OpNode::SHL, "<<", 2, 1, OpNode::INFIX, {Type::INTEGRAL, Type::INTEGRAL}, Type::INTEGRAL,     "0N1g"},
  {OpNode::SHR, ">>", 2, 1, OpNode::INFIX, {Type::INTEGRAL, Type::INTEGRAL}, Type::INTEGRAL,     "0N1g"},

  {OpNode::ASSIGN, "=",  2, 0, OpNode::INFIX, {Type::NATIVE, Type::NATIVE}, Type::VOID,          "1ANN"},

  {OpNode::EMPTY, "empty", 1, 1, OpNode::PREFIX, {Type::CONTAINER}, Type::BOOL,                  "0NON"},
  {OpNode::CLEAR, "clear", 1, 1, OpNode::PREFIX, {Type::CONTAINER}, Type::VOID,                  "1NON"},
  {OpNode::LENGTH, "length", 1, 1, OpNode::PREFIX, {Type::CONTAINER_OR_STR}, Type::UINT,         "0NON"},
  {OpNode::APPEND, "append", 2, 1, OpNode::PREFIX, {Type::VECTOR, Type::VECTOR}, Type::VOID,     "1NON"},
  {OpNode::UNION, "union_", 2, 1, OpNode::PREFIX, {Type::SET, Type::SET}, Type::VOID,            "1NON"},
  {OpNode::INS_SET, "insert", 2, 1, OpNode::PREFIX, {Type::SET, Type::NATIVE}, Type::BOOL,       "1kON"},
  {OpNode::INS_VEC,"insert",3,1,OpNode::PREFIX,{Type::VECTOR,Type::NATIVE,Type::UINT},Type::VOID,"1kON"},
  {OpNode::ERASE, "erase", 2, 1, OpNode::PREFIX, {Type::VECTOR, Type::UINT}, Type::VOID,         "1NON"},
  {OpNode::CONTAINS, "contains", 2, 1,OpNode::PREFIX,{Type::DICTORSET,Type::NATIVE},Type::BOOL,  "0kON"},
  {OpNode::REMOVE, "remove", 2, 1, OpNode::PREFIX, {Type::CONTAINER, Type::NATIVE}, Type::UINT,  "1kON"},
  {OpNode::CAT, "+",  2, 1, OpNode::INFIX, {Type::STRING, Type::STRING}, Type::STRING,           "1NON"},

  {OpNode::TUPLE, "make_tuple", OpNode::VARIABLE, 1, OpNode::PREFIX, {Type::NATIVE}, Type::TUPLE,"0NNN"},
  {OpNode::VECTOR, "list", OpNode::VARIABLE, 1, OpNode::PREFIX, {Type::NATIVE}, Type::VECTOR,    "0NNN"},
  {OpNode::SET, "set", OpNode::VARIABLE, 1, OpNode::PREFIX, {Type::NATIVE}, Type::SET,           "0NNN"},
  {OpNode::DICT, "dict", OpNode::VARIABLE, 1, OpNode::PREFIX, {Type::NATIVE}, Type::VECTOR,      "0NNN"},

  {OpNode::PRINT, "print", OpNode::VARIABLE, 0, OpNode::PREFIX, {Type::NATIVE}, Type::VOID,      "sNON"},
  {OpNode::PRINT_RAW, "print", OpNode::VARIABLE, 0, OpNode::PREFIX, {Type::NATIVE}, Type::VOID,      "sNON"},
  {OpNode::DUMMY_PROJECT, ".", 2, 1, OpNode::INFIX, {Type::TUPLE, Type::INTEGRAL}, Type::NATIVE, "0NNN"},
  {OpNode::EQBIT, "eqbit", 3, 1, OpNode::PREFIX, {Type::INTEGRAL, Type::INTEGRAL, Type::INTEGRAL}, Type::INTEGRAL, "0NNN"},
  {OpNode::NEQBIT, "neqbit", 3, 1, OpNode::PREFIX, {Type::INTEGRAL, Type::INTEGRAL, Type::INTEGRAL}, Type::INTEGRAL, "0NNN"},
  {OpNode::INTERVAL, "interval", 3, 1, OpNode::PREFIX, {Type::NUMERIC, Type::NUMERIC, Type::NUMERIC}, Type::NUMERIC, "0NNN"},
  {OpNode::INVALID, "invalid",            0, 0, OpNode::PREFIX, {}, Type::ERROR,                 "nNON"}
};

OpNode::OpNode(OpCode op, ExprNode* a1, ExprNode* a2,
         int ln, int col, string file):
  ExprNode(OP_NODE, nullptr, ln,col,file) {
  opCode_ = op;
  if (a1 != nullptr) {
  arg_.push_back(a1);
  if (a2 != nullptr) {
    arg_.push_back(a2);
  }
  }
  arity_ = arg_.size();
}

OpNode::OpNode(OpCode op, vector<ExprNode*>* args, int line,
         int column, string file):
  ExprNode(OP_NODE, nullptr, line, column, file) {
  opCode_ = op;
  if (args != nullptr) {
    int n = args->size(), i = 0;
    while (i < n)
      arg_.push_back((*args)[i++]);
    arity_ = n;
  }
  arity_ = arg_.size();
}


void
OpNode::print(ostream& os, int indent) const {
  if (opInfo[opCode_].prtType_ == OpNode::PREFIX) {
  os << opInfo[opCode_].name_;
  if (arity_ > 0) {
    if (opInfo[opCode_].needParen_)
    os << '(';
    for (unsigned i=0; i < arity_-1; i++) {
    if (arg_[i])
      arg_[i]->print(os, indent);
      else os << "nullptr";
    os << ", ";
    }
      if (arg_[arity_-1])
    arg_[arity_-1]->print(os, indent);
    else os << "nullptr";
    if (opInfo[opCode_].needParen_)
    os << ")";
  }
  }
  else if ((opInfo[opCode_].prtType_ == OpNode::INFIX) && (arity_ == 2)) {
  if (opInfo[opCode_].needParen_)
    os << "(";
  if(arg_[0])
    arg_[0]->print(os, indent);
  else os << "nullptr";
  os << opInfo[opCode_].name_;
  if(arg_[1])
    arg_[1]->print(os, indent);
  else os << "nullptr";
  if (opInfo[opCode_].needParen_)
    os << ")";
  }
  else internalErr("Unhandled case in OpNode::print");
}

// Yan-11/16; updated:Yan 11/17 updated 1119
const Type*
OpNode::typeCheck(){
  // w/o list tuple dict set
  bool valid = false;
  const Type* t1 = nullptr;
  const Type* t2 = nullptr;
  const Type* t3 = nullptr;
  ExprNode* operand1 = nullptr;
  ExprNode* operand2 = nullptr;
  ExprNode* operand3 = nullptr;
  // FIXME: check init list: int a[5] = {1,2,3.4,6} (wrong?)
  // ignore it for now
  if (opCode_==SET) {
    return nullptr;
  }
  switch(arity_){
    case 1:
      operand1 = arg(0);

      if(operand1 != nullptr){
        t1 = operand1->typeCheck();
        if(t1 != nullptr){
          valid = true;
        }
      }

      if(opCode() == UMINUS && valid){
        // The unary minus operator takes either an integer or float argument. Its output type is the same as that of input type.
        if(Type::isNumeric(t1->tag())){
          type(new Type(t1->tag()));
        }else{
          errMsg("Expected type numeric for argument 1 of operator '"+ (std::string)opInfo[opCode_].name_ +"' but got " + t1->fullName(), line(), column(), file().c_str());
          type(nullptr);
        }
        return type();
      }else if(opCode() == NOT && valid){
        // ! takes a boolean argument and its output is boolean as well.
        if(Type::isBool(t1->tag())){
          type(new Type(t1->tag()));
        }else{
          errMsg("Expected type bool for argument 1 of operator '"+ (std::string)opInfo[opCode_].name_ +"' but got " + t1->fullName(), line(), column(), file().c_str());
          type(nullptr);
        }
        return type();
      }else if(opCode() == BITNOT && valid){
        // ! takes a boolean argument and its output is boolean as well.
        if(Type::isIntegral(t1->tag())){
          type(new Type(t1->tag()));
        }else{
          errMsg("Expected type integral for argument 1 of operator '"+ (std::string)opInfo[opCode_].name_ +"' but got " + t1->fullName(), line(), column(), file().c_str());
          type(nullptr);
        }
        return type();
      }/*else if(opCode() >= EMPTY && opCode() <= LENGTH && valid){
        if(Type::isContainer(t1->tag())){
        }
      }*/
      // EMPTY CLEAR LENGTH
      else if(opCode() == EMPTY && valid){
        if(t1->isSubType(Type::CONTAINER)){
          type(new Type(Type::BOOL));
        }
        else{
          errMsg("Expected type Vector for argument of operator '"+ (std::string)opInfo[opCode_].name_ +"' but got " + t1->fullName(), line(), column(), file().c_str());
          type(nullptr);
        }
        return type();
      }
      else if(opCode() == CLEAR && valid){
        if(t1->isSubType(Type::CONTAINER)){
          type(new Type(Type::VOID));
        }
        else{
          errMsg("Expected type Vector for argument of operator '"+ (std::string)opInfo[opCode_].name_ +"' but got " + t1->fullName(), line(), column(), file().c_str());
          type(nullptr);
        }
        return type();
      }
      else if(opCode() == LENGTH && valid){
        if(Type::isVector(t1->tag()) || Type::isString(t1->tag())){
          type(new Type(Type::UINT));
        }
        else{
          errMsg("Expected type Vector for argument of operator '"+ (std::string)opInfo[opCode_].name_ +"' but got " + t1->fullName(), line(), column(), file().c_str());
          type(nullptr);
        }
        return type();
      }

      break;

    case 2:
      operand1 = arg(0);
      operand2 = arg(1);
      if(operand1 != nullptr && operand2 != nullptr){
        t1 = operand1->typeCheck();
        t2 = operand2->typeCheck();
        if(t1 != nullptr && t2 != nullptr){
          valid = true;
        }
      }

      if(opCode() >= PLUS && opCode() <= DIV && valid){
        if(!Type::isNumeric(t1->tag())){
          errMsg("Expected type numeric for argument 1 of operator '"+ (std::string)opInfo[opCode_].name_ +"' but got " + t1->fullName(), line(), column(), file().c_str());
          type(nullptr);
          return type();
        }

        if(!Type::isNumeric(t2->tag())){
          errMsg("Expected type numeric for argument 2 of operator '"+ (std::string)opInfo[opCode_].name_ +"' but got " + t2->fullName(), line(), column(), file().c_str());
          type(nullptr);
          return type();
        }

        if(t1->isSubType(t2->tag())){
          operand1->setCoercedType(t2);
          type(new Type(t2->tag()));
          return type();
        }
        else if(t2->isSubType(t1->tag())){
          operand2->setCoercedType(t1);
          type(new Type(t1->tag()));
          return type();
        }
        else{
          errMsg(" Type " + t1->fullName() + " is uncompatible of type " + t2->fullName(), line(), column(), file().c_str());
          type(nullptr);
          return type();
        }
      }
      else if(opCode() >= EQ && opCode() <= LE && valid){
        if(opCode() >= EQ && opCode() <= NE){
          if(!Type::isNative(t1->tag())){
            errMsg("Expected type native for argument 1 of operator '"+ (std::string)opInfo[opCode_].name_ +"' but got " + t1->fullName(), line(), column(), file().c_str());
            type(nullptr);
            return type();
          }
          if(!Type::isNative(t2->tag())){
            errMsg("Expected type native for argument 2 of operator '"+ (std::string)opInfo[opCode_].name_ +"' but got " + t2->fullName(), line(), column(), file().c_str());
            type(nullptr);
            return type();
          }
        }
        else{
          if(!Type::isPrimitive(t1->tag())){
            errMsg("Expected type primitive for argument 1 of operator '"+ (std::string)opInfo[opCode_].name_ +"' but got " + t1->fullName(), line(), column(), file().c_str());
            type(nullptr);
            return type();

          if(!Type::isPrimitive(t2->tag())){
            errMsg("Expected type primitive for argument 2 of operator '"+ (std::string)opInfo[opCode_].name_ +"' but got " + t2->fullName(), line(), column(), file().c_str());
            type(nullptr);
            return type();
          }
        }
        }

        if(t1->isSubType(t2->tag())){
          operand1->setCoercedType(t2);
          type(new Type(Type::BOOL));
          return type();
        }
        else if(t2->isSubType(t1->tag())){
          operand2->setCoercedType(t1);
          type(new Type(Type::BOOL));
          return type();
        }
        else{
          errMsg(" Type " + t1->fullName() + " is uncompatible of type " + t2->fullName(), line(), column(), file().c_str());
          type(nullptr);
          return type();
        }
      }
      else if(opCode() >= AND && opCode() <= OR && valid){
        if(!Type::isBool(t1->tag())){
          errMsg("Expected type bool for argument 1 of operator '"+ (std::string)opInfo[opCode_].name_ +"' but got " + t1->fullName(), line(), column(), file().c_str());
          type(nullptr);
          return type();
        }

        if(!Type::isBool(t2->tag())){
          errMsg("Expected type bool for argument 2 of operator '"+ (std::string)opInfo[opCode_].name_ +"' but got " + t2->fullName(), line(), column(), file().c_str());
          type(nullptr);
          return type();
        }

        type(new Type(Type::BOOL));
        return type();
      }else if(opCode() >= BITAND && opCode() <= SHR && valid){
        if(!Type::isIntegral(t1->tag())){
          errMsg("Expected type integral for argument 1 of operator '"+ (std::string)opInfo[opCode_].name_ +"' but got " + t1->fullName(), line(), column(), file().c_str());
          type(nullptr);
          return type();
        }

        if(!Type::isIntegral(t2->tag())){
          errMsg("Expected type integral for argument 2 of operator '"+ (std::string)opInfo[opCode_].name_ +"' but got " + t2->fullName(), line(), column(), file().c_str());
          type(nullptr);
          return type();
        }

        if(t1->isSubType(t2->tag())){
          operand1->setCoercedType(t2);
          type(new Type(t2->tag()));
          return type();
        }else if(t2->isSubType(t1->tag())){
          operand2->setCoercedType(t1);
          type(new Type(t1->tag()));
          return type();
        }
        else{
          errMsg(" Type " + t1->fullName() + " is uncompatible of type " + t2->fullName(), line(), column(), file().c_str());
          type(nullptr);
          return type();
        }
      }else if(opCode() == ASSIGN && valid){
        bool flag = false;
        if(t1->tag() == t2->tag()){
          flag = true;
        }else if(t2->isSubType(t1->tag())){
          operand2->setCoercedType(t1); // should set oprand2's conerced type
          flag = true;
        }else if(Type::isIntegral(t1->tag()) && Type::isIntegral(t2->tag())){
  					cerr << file() << ":" << line() << "." << column() << ":Warning: Signedness or possible integer overflow in assignment" << endl;
        }else{
          	errMsg("Assigned type '" + t2->fullName() + "' not a subtype of target type '" + t1->fullName() + "'", line(), column(), file().c_str());
        }

        if(flag){
          type(new Type(Type::BOOL));
          return type();
        }
      }else if(opCode() == MOD){
        bool flag = true;
        if(!Type::isIntegral(t1->tag())){
          errMsg("Expected type integral for argument 1 of operator '"+ (std::string)opInfo[opCode_].name_ +"' but got " + t1->fullName(), line(), column(), file().c_str());
          flag = false;
        }

        if(!Type::isIntegral(t2->tag())){
          errMsg("Expected type integral for argument 2 of operator '"+ (std::string)opInfo[opCode_].name_ +"' but got " + t2->fullName(), line(), column(), file().c_str());
          flag = false;
        }

        if(flag){
          type(new Type(Type::INT));
          return type();
        }
      }
      // APPEND UNION (INS_SET) (ERASE) CONTAINS REMOVE CAT
      // {OpNode::APPEND, "append", 2, 1, OpNode::PREFIX, {Type::VECTOR, Type::VECTOR}, Type::VOID,     "1NON"}
      else if(opCode() == APPEND){
        if(!Type::isVector(t1->tag())){
          errMsg("Expected type Vector for argument 1 of operator '"+ (std::string)opInfo[opCode_].name_ +"' but got " + t1->fullName(), line(), column(), file().c_str());
          type(nullptr);
          return type();
        }
        if(!Type::isVector(t2->tag())){
          errMsg("Expected type Vector for argument 2 of operator '"+ (std::string)opInfo[opCode_].name_ +"' but got " + t2->fullName(), line(), column(), file().c_str());
          type(nullptr);
          return type();
        }
        if(t1->elemType()->isSubType(t2->elemType()->tag()) || t2->elemType()->isSubType(t1->elemType()->tag())){
          type(new Type(Type::VOID));
          return type();
        }
        else{
          errMsg("Element type " + t1->elemType()->fullName() + " is uncompatible of element type " + t2->elemType()->fullName(), line(), column(), file().c_str());
          type(nullptr);
          return type();
        }
      }

      // {OpNode::REMOVE, "remove", 2, 1, OpNode::PREFIX, {Type::CONTAINER, Type::NATIVE}, Type::UINT,  "1kON"},
      else if(opCode() == REMOVE){
        if(!t1->isSubType(Type::CONTAINER)){
          errMsg("Expected type CONTAINER for argument 1 of operator '"+ (std::string)opInfo[opCode_].name_ +"' but got " + t1->fullName(), line(), column(), file().c_str());
          type(nullptr);
          return type();
        }
        if(!t2->isSubType(Type::NATIVE)){
          errMsg("Expected type NATIVE for argument 2 of operator '"+ (std::string)opInfo[opCode_].name_ +"' but got " + t2->fullName(), line(), column(), file().c_str());
          type(nullptr);
          return type();
        }
        if(t1->elemType()->isSubType(t2->tag()) || t2->isSubType(t1->elemType()->tag())){
          type(new Type(Type::UINT));
          return type();
        }
        else{
          errMsg("Element type " + t1->elemType()->fullName() + " is uncompatible of type " + t2->fullName(), line(), column(), file().c_str());
          type(nullptr);
          return type();
        }
      }

      // {OpNode::ERASE, "erase", 2, 1, OpNode::PREFIX, {Type::VECTOR, Type::UINT}, Type::VOID,         "1NON"},
      else if(opCode() == ERASE){
        if(!Type::isVector(t1->tag())){
          errMsg("Expected type Vector for argument 1 of operator '"+ (std::string)opInfo[opCode_].name_ +"' but got " + t1->fullName(), line(), column(), file().c_str());
          type(nullptr);
          return type();
        }
        if(!t2->isSubType(Type::UINT)){
          errMsg("Expected type UINT for argument 2 of operator '"+ (std::string)opInfo[opCode_].name_ +"' but got " + t2->fullName(), line(), column(), file().c_str());
          type(nullptr);
          return type();
        }
        if(t1->elemType()->isSubType(t2->tag()) || t2->isSubType(t1->elemType()->tag())){
          type(new Type(Type::VOID));
          return type();
        }
      }

      break;

    case 3: // INS_VEC
      operand1 = arg(0);
      operand2 = arg(1);
      operand3 = arg(2);
      if(operand1 != nullptr && operand2 != nullptr && operand3 != nullptr){
        t1 = operand1->typeCheck();
        t2 = operand2->typeCheck();
        t3 = operand3->typeCheck();
        if(t1 != nullptr && t2 != nullptr && t3 != nullptr){
          valid = true;
        }
      }

      if(opCode() == INS_VEC && valid){
        if(!Type::isVector(t1->tag())){
          errMsg("Expected type Vector for argument 1 of operator '"+ (std::string)opInfo[opCode_].name_ +"' but got " + t1->fullName(), line(), column(), file().c_str());
          type(nullptr);
          return type();
        }
        if(!t3->isSubType(Type::NATIVE)){
          errMsg("Expected type NATIVE for argument 3 of operator '"+ (std::string)opInfo[opCode_].name_ +"' but got " + t2->fullName(), line(), column(), file().c_str());
          type(nullptr);
          return type();
        }
        if(!t3->isSubType(Type::UINT)){
          errMsg("Expected type UINT for argument 3 of operator '"+ (std::string)opInfo[opCode_].name_ +"' but got " + t3->fullName(), line(), column(), file().c_str());
          type(nullptr);
          return type();
        }
        if(t1->elemType()->isSubType(t2->tag()) || t2->isSubType(t1->elemType()->tag())){
          type(new Type(Type::VOID));
          return type();
        }
        else{
          errMsg("Element type " + t1->elemType()->fullName() + " is uncompatible of type " + t2->fullName(), line(), column(), file().c_str());
          type(nullptr);
          return type();
        }
      }


      break;
    default:
      cout << "default" << endl;
  }

  return nullptr;
}

void
OpNode::typePrint(ostream& os, int indent) const{
  // TO-DO: parenthesis? type for op expressions? coerced type? need discussion

  ExprNode* operand1 = nullptr;
  ExprNode* operand2 = nullptr;

  switch(arity_){
    case 1:
      operand1 = arg_[0];
      if(operand1 == nullptr){
        return;
      }
      os << opInfo[opCode_].name_;
      os << "(";
      operand1->typePrint(os, indent);
      os << ")";

      break;
    case 2:
      operand1 = arg_[0];
      operand2 = arg_[1];
      if(operand1 == nullptr || operand2 == nullptr){
        return;
      }
      os << "(";
      operand1->typePrint(os, indent);
      os << ")";
      os << " " << opInfo[opCode_].name_ << " ";
      os << "(";
      operand2->typePrint(os, indent);
      os << ")";

      break;
    case 3:
      break;
    default:
      if(opCode() == SET && arity_ >= 1){
        os << "{";
        int i = 0;
        for(; i < arity_ - 1; i ++){
          arg_[i]->typePrint(os, indent);
          os << ", ";
        }
        arg_[i]->typePrint(os, indent);
        os << "}";
      }
      else{
        cout << "default" << endl;
      }
  }
}

/*-------------------------------------------------Mem Alloc -------------------------------------------------------------*/

void
CompoundStmtNode::memAlloc(MemAllocator* allocator) {
  allocator->enterScope();
  decls_->memAlloc(allocator);
   for (auto stmt : *stmts()) {
     if (stmt)
      stmt->memAlloc(allocator);
  }
  allocator->leaveScope();
}

void
WhileNode::memAlloc(MemAllocator* allocator) {
  if ( body_ ) {
    body_->memAlloc(allocator);
  }
}

void
IfNode::memAlloc(MemAllocator* allocator) {
  if (then_) {
    then_->memAlloc(allocator);
  }
  if (else_) {
    else_->memAlloc(allocator);
  }
}

void
ListForNode::memAlloc(MemAllocator* allocator) {
  // allocate index var
  if (body_) {
    body_->memAlloc(allocator);
  }
}




/*-------------------------------------------------IR Gen -------------------------------------------------------------*/

IRValue*
RefExprNode::codeGen(IRGenManager* mgr, list<Instruction*>& code) {
  VariableEntry* ve = (VariableEntry*)sym_;
  if (nsubs()) {
    // load/store vector element here, use load here, caller may change the opcode to store
    auto opt = ve->type()->isDouble()?Instruction::LDF:Instruction::LDI;
    IRValue* arrayVar = mgr->getSymReg(sym_);
    // array passed as function paramter
    if (!arrayVar && ve->varKind() == VarKind::FN_PARAM_VAR) {
      Instruction* loadInst = new Instruction(Instruction::LDI, new IRValue(sym_));
      loadInst->sym(sym_);
      mgr->checkAndSetSymReg(sym_, loadInst);
      code.push_back(loadInst);
      arrayVar = loadInst;
    }
    IRValue* array = arrayVar?arrayVar:new IRValue(sym_);
    auto & subs = *subscript();
    auto & dimProducts = *(ve->dimProducts());
    vector<IRValue*> oprands = {array};

    IRValue* prevRes = nullptr;
    for (size_t i=0; i<subs.size()-1; i++) {
      IRValue* idx = subs[i]->codeGen(mgr, code);
      if (idx->isTemprary()) {
        mgr->setAsTemp(idx);
      }
       // idx * dimProduct
      IRValue* mulRes;
      if (dimProducts[i]->isIntConst() && idx->isIntConst()) {
        mulRes = new IRValue(dimProducts[i]->ival() * idx->ival());
      } else {
        mulRes = new Instruction(Instruction::MUL, dimProducts[i], idx);
        code.push_back((Instruction*)mulRes);
      }
      if (mulRes->isTemprary())
        mgr->setAsTemp(mulRes);
      // add
      if (prevRes) {
        if (mulRes->isIntConst() && prevRes->isIntConst()) {
          prevRes->ival(prevRes->ival() + mulRes->ival());
        } else {
          prevRes = new Instruction(Instruction::ADD, prevRes, mulRes);
          code.push_back((Instruction*)prevRes);
        }
        if (prevRes->isTemprary())
          mgr->setAsTemp(prevRes);
      } else {
        prevRes = mulRes;
      }
    }
    IRValue* idx0 = subs.back()->codeGen(mgr, code);
    IRValue* offset = idx0;
    if (idx0->isTemprary())
      mgr->setAsTemp(idx0);
    if (prevRes) {
       if (prevRes->isIntConst() && idx0->isIntConst()) {
         offset = new IRValue(prevRes->ival() + idx0->ival());
       } else {
         offset = new Instruction(Instruction::ADD, prevRes, idx0);
         code.push_back((Instruction*)offset);
       }
       if (offset->isTemprary()) {
         mgr->setAsTemp(offset);
       }
    }
    oprands.push_back(offset);
    Instruction * gelem = new Instruction(opt, oprands);
    code.push_back(gelem);
    return gelem;
  } else {
    IRValue* vreg =mgr->getSymReg(sym_);
    if (vreg) {
      return vreg;
    }
    auto opType = sym_->type()->isDouble()?Instruction::OpCode::LDF : Instruction::OpCode::LDI;
    if (ve->varKind() == VarKind::FN_PARAM_VAR) {
      auto src = new IRValue(sym_);
      Instruction* loadInst = new Instruction(opType, src);
      loadInst->regNum(mgr->nextTemp());
      loadInst->sym(sym_);
      mgr->setSymReg(sym_, loadInst);
      mgr->setRegNum2Sym(loadInst->regNum(), loadInst);
      code.push_back(loadInst);
      return loadInst;
    } else if (ve->nSubscripts()) {
      // passing constant sized global/local array
      return new IRValue(sym_);
    } else if (ve->varKind() == VarKind::GLOBAL_VAR) {
      // reference to global var
      Instruction * gvar = new Instruction(opType, new IRValue(sym_));
      code.push_back(gvar);
      return gvar;
    }  else {
      // use before assign
      if (mgr->warnEnabled())
        warnMsg("use of '"+sym_->name() + "' before assignment", this);
      IRValue::ValueType vt = sym_->type()->isDouble()?IRValue::FREG:IRValue::IREG;
      IRValue* var = new IRValue(vt, mgr->nextTemp(), sym_);
      mgr->setSymReg(sym_, var);
      mgr->setRegNum2Sym(var->regNum(), var);
      return var;
    }
  }
}

////////////////////////////
const map<int, int> opCode2IRIntOpCode = {
  {OpNode::OpCode::PLUS, Instruction::OpCode::ADD },
  {OpNode::OpCode::MINUS, Instruction::OpCode::SUB },
  {OpNode::OpCode::MULT, Instruction::OpCode::MUL },
  {OpNode::OpCode::DIV, Instruction::OpCode::DIV },
  {OpNode::OpCode::UMINUS, Instruction::OpCode::NEG },
  {OpNode::OpCode::MOD, Instruction::OpCode::MOD },
  {OpNode::OpCode::BITAND, Instruction::OpCode::AND },
  {OpNode::OpCode::BITOR, Instruction::OpCode::OR },
  {OpNode::OpCode::BITXOR, Instruction::OpCode::XOR },
  {OpNode::OpCode::GT, Instruction::OpCode::GT },
  {OpNode::OpCode::GE, Instruction::OpCode::GE },
  {OpNode::OpCode::LT, Instruction::OpCode::GT },
  {OpNode::OpCode::LE, Instruction::OpCode::GE },
  {OpNode::OpCode::EQ, Instruction::OpCode::EQ },
  {OpNode::OpCode::NE, Instruction::OpCode::NE },
  {OpNode::OpCode::SHL, Instruction::OpCode::MUL },
  {OpNode::OpCode::SHR, Instruction::OpCode::DIV },
};

const map<int, int> opCode2IRFtOpCode = {
  {OpNode::OpCode::PLUS, Instruction::OpCode::FADD },
  {OpNode::OpCode::MINUS, Instruction::OpCode::FSUB },
  {OpNode::OpCode::MULT, Instruction::OpCode::FMUL },
  {OpNode::OpCode::DIV, Instruction::OpCode::FDIV },
  {OpNode::OpCode::UMINUS, Instruction::OpCode::FNEG },
  {OpNode::OpCode::GT, Instruction::OpCode::FGT },
  {OpNode::OpCode::GE, Instruction::OpCode::FGE },
  {OpNode::OpCode::LT, Instruction::OpCode::FGT },
  {OpNode::OpCode::LE, Instruction::OpCode::FGE },
  {OpNode::OpCode::EQ, Instruction::OpCode::FEQ },
  {OpNode::OpCode::NE, Instruction::OpCode::FNE },
};

IRValue*
OpNode::codeGen(IRGenManager* mgr, list<Instruction*>& code) {
  switch (opCode_)
  {
  case OpCode::PLUS:
  case OpCode::MINUS:
  case OpCode::MULT:
  case OpCode::DIV:
  case OpCode::MOD:
  case OpCode::UMINUS:
  case OpCode::BITAND: case OpCode::BITOR: case OpCode::BITXOR:
  {
    Type* outType = type();
    Instruction::OpCode opc;
    if (!outType) {
      cout << "NO outType for expr: ";
      print(cout);
      cout << "\n";
      exit(0);
    }

    if (outType->isIntegral()) {
      opc = (Instruction::OpCode)opCode2IRIntOpCode.at(opCode_);
    } else {
      opc = (Instruction::OpCode)opCode2IRFtOpCode.at(opCode_);
    }
    // generate op1's && op2's code
    ExprNode *op1Expr = arg(0), *op2Expr = arg(1);
    IRValue* opr1 = op1Expr->codeGen(mgr, code);
    if (opr1->isTemprary()) {
      mgr->setAsTemp(opr1);
    }
    IRValue* opr2 = op2Expr?op2Expr->codeGen(mgr, code):nullptr;
    if (opr2 && opr2->isTemprary()) {
      mgr->setAsTemp(opr2);
    }
    if ((opr1->isConst() && opr2 && opr2->isConst()) || (opr1->isConst() && !opr2)) {
      return evalConst(opCode_, opr1, opr2);
    }
    // handle type conversion
    opr1 = checkTypeCoersion(opr1, op1Expr, mgr, code);
    opr2 = checkTypeCoersion(opr2, op2Expr, mgr, code);
    Instruction* inst = new Instruction(opc, opr1, opr2);
    code.push_back(inst);
    return inst;
    break;
  }
  case OpCode::SHL: case OpCode::SHR:
  {
    errMsg("shift operation not supported!", this);
    exit(0);
  }
  case OpCode::ASSIGN:
  {
    ExprNode* rhs = arg(1);
    IRValue *rhsRes = rhs->codeGen(mgr, code);
    // might need a store
    RefExprNode* lhs = (RefExprNode*)arg(0);
    auto lhsSym = (VariableEntry*)lhs->symTabEntry();
    if (!lhs->nsubs() && lhsSym->varKind() != GLOBAL_VAR) {
      if (rhsRes->isConst()) {
        Instruction::OpCode opCode = rhsRes->isIntConst()?Instruction::MOVI:(rhsRes->isStrConst()?Instruction::MOVS : Instruction::MOVF);
        Instruction* mov = new Instruction(opCode, rhsRes);
        mov->sym(lhsSym);
        mgr->checkAndSetSymReg(lhsSym, mov);
        code.push_back(mov);
        return mov;
      } else if (rhsRes->isTemprary()) {
        rhsRes->sym(lhsSym);
        mgr->checkAndSetSymReg(lhsSym, rhsRes);
        return rhsRes;
      } else {
        Instruction::OpCode opCode;
        auto lhsType = lhs->symTabEntry()->type();
        auto rhsCoercedType = rhs->getCoercedType();
        if (rhsCoercedType && rhsCoercedType->isDouble()) {
          opCode = Instruction::OpCode::MOVIF;
        } else {
          opCode = lhsType->isDouble()?Instruction::MOVF:Instruction::MOVI;
        }
        Instruction* mov = new Instruction(opCode, rhsRes);
        mov->sym(lhsSym);
        mgr->checkAndSetSymReg(lhsSym, mov);
        code.push_back(mov);
        return mov;
      }
    } else {
      Instruction* gelem = (Instruction*)lhs->codeGen(mgr, code);
      gelem->opcode(gelem->isFloatReg()?Instruction::STF:Instruction::STI);
      IRValue* stored = rhsRes;
      if (rhsRes->isTemprary()) {
        mgr->setAsTemp(rhsRes);
      }
      if (gelem->isFloatReg() && rhsRes->isIntVal()) {
        stored = new Instruction(Instruction::MOVIF, {rhsRes});
        mgr->setAsTemp(stored);
        code.pop_back();
        code.push_back((Instruction*)stored);
        code.push_back(gelem);
      } else if (gelem->isIntReg() && rhsRes->isFloatVal()) {
        stored = new Instruction(Instruction::MOVFI, {rhsRes});
        mgr->setAsTemp(stored);
        code.pop_back();
        code.push_back((Instruction*)stored);
        code.push_back(gelem);
      }
      gelem->addOprand(stored);

      return gelem;
    }
    break;
  }
  case OpCode::EQ: case OpCode::NE: case OpCode::GT:  case OpCode::GE:
  case OpCode::LT: case OpCode::LE:
  {
    ExprNode *lhs=arg(0), *rhs=arg(1);
    IRValue* lhsVal= lhs->codeGen(mgr, code);
    if (lhsVal->isTemprary())
      mgr->setAsTemp(lhsVal);
    IRValue* rhsVal = rhs->codeGen(mgr, code);
    if (rhsVal->isTemprary())
      mgr->setAsTemp(rhsVal);
    // TODO() handle type conversion
    bool isFloat = (lhsVal->isFloatVal() || rhsVal->isFloatVal());
    Instruction::OpCode opCode=isFloat?(Instruction::OpCode)opCode2IRFtOpCode.at(opCode_):(Instruction::OpCode)opCode2IRIntOpCode.at(opCode_);

    lhsVal = checkTypeCoersion(lhsVal, lhs, mgr, code);
    rhsVal = checkTypeCoersion(rhsVal, rhs, mgr, code);
    BranchInfo& bTargets = mgr->getBranchInfo();
    IRValue* trueT = bTargets.trueLabel, *falseT = bTargets.falseLabel;
    Instruction* jmpInst, *cmpInst;
    if (opCode_==OpCode::LT) {
      opCode = isFloat?Instruction::OpCode::FGE : Instruction::OpCode::GE;
      // swithc labels
      trueT = bTargets.falseLabel; falseT = bTargets.trueLabel;
    } else if (opCode_==OpCode::LE) {
      opCode = isFloat?Instruction::OpCode::FGT : Instruction::OpCode::GT;
      // swithc labels
      trueT = bTargets.falseLabel; falseT = bTargets.trueLabel;
    }
    cmpInst = new Instruction(opCode, lhsVal, rhsVal);
    jmpInst = new Instruction(Instruction::OpCode::JMPC, {cmpInst, trueT, falseT});
    code.push_back(jmpInst);
    return jmpInst;
  }
  case OpCode::AND:
  {
    ExprNode *l = arg(0), *r = arg(1);
    BranchInfo curBInfo = mgr->getBranchInfo();
    IRValue* contLabel = mgr->nextLabel();
    Instruction* contLabelInst = new Instruction(contLabel->sval());
    BranchInfo bleft = {contLabel, curBInfo.falseLabel};
    mgr->pushBranchInfo(bleft);
    l->codeGen(mgr, code);
    code.push_back(contLabelInst);
    mgr->popBranchInfo();
    BranchInfo bright = {curBInfo.trueLabel, curBInfo.falseLabel};
    mgr->pushBranchInfo(bright);
    r->codeGen(mgr, code);
    mgr->popBranchInfo();
    return nullptr;
  }
  case OpCode::OR:
  {
    ExprNode *l = arg(0), *r = arg(1);
    BranchInfo curBInfo = mgr->getBranchInfo();
    IRValue* contLabel = mgr->nextLabel();
    Instruction* contLabelInst = new Instruction(contLabel->sval());
    BranchInfo bleft = {curBInfo.trueLabel, contLabel};
    mgr->pushBranchInfo(bleft);
    l->codeGen(mgr, code);
    code.push_back(contLabelInst);
    mgr->popBranchInfo();
    BranchInfo bright = {curBInfo.trueLabel, curBInfo.falseLabel};
    mgr->pushBranchInfo(bright);
    r->codeGen(mgr, code);
    mgr->popBranchInfo();
    return nullptr;
  }
  case OpCode::NOT:
  {
    ExprNode *l = arg(0);
    BranchInfo curBInfo = mgr->getBranchInfo();
    BranchInfo bi = {curBInfo.falseLabel, curBInfo.trueLabel};
    mgr->pushBranchInfo(bi);
    l->codeGen(mgr, code);
    mgr->popBranchInfo();
    return nullptr;
  }
  case OpCode::PRINT:
  case OpCode::PRINT_RAW:
  {
    size_t i = 0;
    auto args = this->args();
    if (!args) return nullptr;
    for (auto expr: *args){
      IRValue* exprVal = expr->codeGen(mgr, code);
      if (exprVal->isTemprary()) {
        mgr->setAsTemp(exprVal);
      }
      // TODO() for string variables, simplify the predicate with the derived type info
      if (exprVal->isStrConst() || (expr->type() && expr->type()->isString())) {
        code.push_back(new Instruction(Instruction::PRTS, {exprVal}));
      } else if (exprVal->isFloatVal()) {
        code.push_back(new Instruction(Instruction::PRTF, {exprVal}));
      } else if (exprVal->isIntVal()) {
        code.push_back(new Instruction(Instruction::PRTI, {exprVal}));
      }
      if (i < args->size()-1 && opCode_==PRINT) {
        code.push_back(new Instruction(Instruction::PRTS, {new IRValue(IRValue::SVALUE, " ")}));
      }
      i++;
    }
    return nullptr;
  }

  default:
    break;
  }
  return nullptr;
}


IRValue*
ExprStmtNode::codeGen(IRGenManager* mgr, list<Instruction*>& code) {
  return expr_->codeGen(mgr, code);
}

IRValue*
ValueNode::codeGen(IRGenManager* mgr, list<Instruction*>& code) {
  if (value()->isDouble()) {
    return new IRValue(value()->dval());
  } else if (value()->isIntegral()) {
    return new IRValue(value()->lval());
  } else if (value()->isString()) {
    return new IRValue(IRValue::ValueType::SVALUE, value()->sval());
  } else if (value()->type()->tag() == Type::BaseTypeTag::BOOL) {
    return new IRValue((long)value()->bval());
  } else {
    return nullptr;
  }
}

IRValue*
CompoundStmtNode::codeGen(IRGenManager* mgr, list<Instruction*>& code) {
  const SymTab *st = decls_->symTab();
  if (st) {
    for (SymTab::const_iterator it=st->begin(); it != st->end(); ++it) {
        if ((*it)->kind() == SymTabEntry::VARIABLE_KIND) {
            VariableEntry* ve = (VariableEntry*)(*it);
            auto expr = ve->initVal();
            if (!expr && !ve->isVLA()) {
              continue;
            }
            int isArray = ve->nSubscripts();
            if (!isArray) {
              RefExprNode lhs(nullptr, "", ve);
              OpNode assignOp(OpNode::OpCode::ASSIGN, &lhs, expr);
              // cout << " ## " << ((ValueNode*)expr)->value()->lval() << " ## " << endl;
              assignOp.codeGen(mgr, code);
            } else {
              IRValue* arrayAddr=nullptr;
              if (ve->isVLA()) {
                int ndims = ve->nSubscripts();
                IRValue* arraySize{nullptr}, *dimProduct{nullptr};
                vector<IRValue*>  &dimProdVec = *ve->dimProducts();
                IRValue* dimSize{nullptr};
                for (int i=ndims-1; i>=0; i--) {
                    ExprNode* expr = ve->subscript(i);
                    dimSize = expr->codeGen(mgr, code);
                    if (dimSize->isTemprary()) {
                      mgr->setAsTemp(dimSize);
                    }
                    if (i == ndims-1) {
                      dimProduct = dimSize;
                      arraySize = dimSize;
                    } else if (i > 0) {
                      if (dimProduct->isIntConst() && dimSize->isIntConst()) {
                        dimProduct = new IRValue(dimProduct->ival() * dimSize->ival());
                      } else {
                        dimProduct = new Instruction(Instruction::MUL, dimProduct, dimSize);
                        mgr->setAsTemp(dimProduct);
                        code.push_back((Instruction*)dimProduct);
                      }
                    }
                    if (i > 0) {
                      dimProdVec.insert(dimProdVec.begin(), dimProduct);
                    }
                }
                if (ndims > 1) {
                  arraySize = new Instruction(Instruction::MUL, dimProduct, dimSize);
                  mgr->setAsTemp(arraySize);
                  code.push_back((Instruction*)arraySize);
                }
                Instruction* alloca = new Instruction(Instruction::ALLOCA, {arraySize});
                arrayAddr = alloca;
                alloca->sym(ve);
                mgr->checkAndSetSymReg(ve, alloca);
                code.push_back(alloca);
              } else {
                arrayAddr = new IRValue(ve);
              }
              if (expr) {
                int i=0;
                OpNode* initList = (OpNode*)expr;
                auto stOp = ve->type()->isDouble()?Instruction::STF:Instruction::STI;
                while ( ExprNode* initExpr = initList->arg(i)) {
                  IRValue* val = initExpr->codeGen(mgr, code);
                  auto store = new Instruction(stOp, {arrayAddr, new IRValue((long)i), val});
                  code.push_back(store);
                  i++;
                }
              }
            }
        }
    }
  }
  if (!stmts_) return nullptr;
  for (auto stmt : *stmts_) {
    if (stmt)
      stmt->codeGen(mgr, code);
  }

  return nullptr;
}

IRValue*
IfNode::codeGen(IRGenManager* mgr, list<Instruction*>& code) {
  IRValue *trueLabel=mgr->nextLabel(), *falseLabel=mgr->nextLabel();
  IRValue* outLabel=falseLabel;
  BranchInfo binfo = {trueLabel, falseLabel};
  mgr->pushBranchInfo(binfo);
  cond_->codeGen(mgr, code);
  mgr->popBranchInfo();
  Instruction* trueLabelInst = new Instruction(trueLabel->sval());
  Instruction* falseLabelInst = new Instruction(falseLabel->sval());
  code.push_back(trueLabelInst);
  then_->codeGen(mgr, code);
  // when else stmt exists, jump here
  if (else_) {
    outLabel = mgr->nextLabel();
    Instruction* jmpInst = new Instruction(Instruction::OpCode::JMP, outLabel);
    Instruction* outLabelInst = new Instruction(outLabel->sval());
    code.push_back(jmpInst);
    code.push_back(falseLabelInst);
    else_->codeGen(mgr, code);
    code.push_back(outLabelInst);
  } else {
    code.push_back(falseLabelInst);
  }

  return nullptr;
}

IRValue*
InvocationNode::codeGen(IRGenManager* mgr, list<Instruction*>& code) {
  // evaluate actual params
  vector<IRValue*> actualParams;
  FunctionEntry* callee = (FunctionEntry*)ste_;
  string calleeName = callee->name();
  // hacking to handle the read funcalls
  if (calleeName == "readc" || calleeName == "readi" || calleeName == "readf") {
    return inFuncCallCodeGen(calleeName, code);
  }
  auto retType = callee->type()->retType();
  IRValue* calleeVal = new IRValue(callee);
  actualParams.push_back(calleeVal);
  if (params_) {
    for (size_t i=0; i<params_->size(); i++) {
      IRValue* apVal =(*params_)[i]->codeGen(mgr, code);
      if (apVal->isTemprary()) {
        mgr->setAsTemp(apVal);
      }
      apVal = checkTypeCoersion(apVal, (*params_)[i], mgr, code);
      actualParams.push_back(apVal);
    }
  }
  Instruction* callInst = new Instruction(Instruction::OpCode::CALL, actualParams);
  // set type
  if (retType && retType->tag() != Type::BaseTypeTag::VOID) {
    if (retType->isDouble()) {
      callInst->type(IRValue::FREG);
    } else {
      callInst->type(IRValue::IREG);
    }
  }
  code.push_back(callInst);
  return callInst;
}

IRValue*
ReturnStmtNode::codeGen(IRGenManager* mgr, list<Instruction*>& code) {
  IRValue *returnVal = nullptr;
  if (expr_) {
    returnVal = expr_->codeGen(mgr, code);
  }
  if (returnVal && returnVal->isTemprary()) {
    mgr->setAsTemp(returnVal);
  }
  Instruction* returnInst = new Instruction(Instruction::OpCode::RETURN, returnVal);

  code.push_back(returnInst);
  return returnInst;
}
/*
   idx = 0
   while idx < arraySize {
     i = array[index]
     {
       for body
     }
     idx++;
   }

*/
IRValue*
ListForNode::codeGen(IRGenManager* mgr, std::list<Instruction*>& code) {
  RefExprNode * arrayExpr = dynamic_cast<RefExprNode*>(list_);
  if (!arrayExpr) {
    errMsg("Fatal Error compiling foreach", this);
  }
  VariableEntry* array = (VariableEntry*)arrayExpr->symTabEntry();
  long arraySize = 1;
  assert(array->dims()->size() > 0);
  // FixME array size may be a variable
  for (auto dim: *array->dims()) {
    arraySize *= dim->ival();
  }
  indexVar_->type(array->type());
  VariableEntry* index = new VariableEntry("__for_idx", FOREACH_VAR);
  RefExprNode* indexExpr = new RefExprNode(nullptr, "", index);
  OpNode* initIdx = new OpNode(OpNode::ASSIGN, new vector<ExprNode*>{indexExpr, new ValueNode(new Value(0L))});
  auto valNode = new ValueNode(new Value(arraySize));
  auto cmp = new vector<ExprNode*>{indexExpr, valNode};
  ExprNode* cond = new OpNode(OpNode::LT, cmp);
  RefExprNode* arrayElem = new RefExprNode(nullptr, "", array);
  arrayElem->addSubs(indexExpr);
  OpNode* assignIter = new OpNode(OpNode::ASSIGN, new vector<ExprNode*>{indexVar_, arrayElem});
  ExprStmtNode* assignIterStmt = new ExprStmtNode(assignIter);
  OpNode* incIdx = new OpNode(OpNode::PLUS, new vector<ExprNode*>{indexExpr, new ValueNode(new Value(1L))});
  incIdx->type((Type*)&Type::intType);
  OpNode* incAssign = new OpNode(OpNode::ASSIGN, new vector<ExprNode*>{indexExpr, incIdx});
  ExprStmtNode* incAssignStmt = new ExprStmtNode(incAssign);
  // init index
  initIdx->codeGen(mgr, code);
  CompoundStmtNode* loopBdy = (CompoundStmtNode*) body_;
  auto loopStmts = loopBdy->stmts();
  loopStmts->push_front(assignIterStmt);
  loopStmts->push_back(incAssignStmt);
  WhileNode* forloop = new WhileNode(cond, loopBdy);
  forloop->codeGen(mgr, code);
  return nullptr;
}

IRValue*
WhileNode::codeGen(IRGenManager* mgr, list<Instruction*>& code) {
  IRValue* condLabel = mgr->nextLabel();
  Instruction* condLabelInst = new Instruction(condLabel->sval());
  code.push_back(condLabelInst);

  IRValue* loopLabel = mgr->nextLabel(), *outLabel = mgr->nextLabel();
  Instruction* loopLabelInst = new Instruction(loopLabel->sval());
  Instruction* outLabelInst = new Instruction(outLabel->sval());
  mgr->pushBranchInfo({loopLabel, outLabel});
  cond_->codeGen(mgr, code);
  mgr->popBranchInfo();
  //setup loop label
  code.push_back(loopLabelInst);
  body_->codeGen(mgr, code);
  // jmp to cond eval codes
  Instruction* jmpInst = new Instruction(Instruction::OpCode::JMP, condLabel);
  code.push_back(jmpInst);
  code.push_back(outLabelInst);
  return nullptr;
}

/*
  if the type should be converted to double, generate conversion code and return the new value
  if it is a const integer value, just modify it in place.
*/

IRValue* checkTypeCoersion(IRValue* v, ExprNode* expr, IRGenManager* mgr, list<Instruction*>& code) {
  if (!v) return v;
  const Type* coercedType = expr->getCoercedType();
  if (!expr->type()) {
    expr->print(cout);
  }
  if (coercedType && coercedType->isDouble() && coercedType->tag() != expr->type()->tag()) {
    if (v->isConst()) {
      // just reset the value and type of this IRValue here
      long iv = v->ival();
      double fv = (double)iv;
      v->type(IRValue::FVALUE);
      v->fval(fv);
      return v;
    }
    Instruction* movif = new Instruction(Instruction::MOVIF, v);
    mgr->setAsTemp(movif);
    code.push_back(movif);
    return movif;
  }
  return v;
}

IRValue* evalConst(OpNode::OpCode op, IRValue* v1, IRValue*v2) {
  bool isOutFloat = false;
  if (v1->isFloatConst() || (v2 && v2->isFloatConst())) {
    isOutFloat=true;
  }
  double fcv1 =  v1->isFloatConst()?v1->fval():(double)(v1->ival());
  double fcv2 = v2?(v2->isFloatConst()?v2->fval():(double)(v2->ival())):0;
  long icv1 = v1->ival();
  long icv2 = v2?v2->ival():0;
  double fres=0; long ires=0;
  switch (op)
  {
  case OpNode::PLUS:
    if (isOutFloat) fres = fcv1+fcv2; else ires = icv1 + icv2;
    break;
  case OpNode::MINUS:
    if (isOutFloat) fres = fcv1-fcv2; else ires = icv1 - icv2;
    break;
  case OpNode::MULT:
    if (isOutFloat) fres = fcv1*fcv2; else ires = icv1 * icv2;
    break;
  case OpNode::DIV:
    if (isOutFloat) fres = fcv1/fcv2; else ires = icv1 / icv2;
    break;
  case OpNode::MOD:
    ires = icv1 % icv2;
    break;
  case OpNode::BITAND:
    ires = icv1 & icv2;
    break;
  case OpNode::BITNOT:
    ires = !icv1;
    break;
  case OpNode::BITOR:
    ires = icv1 | icv2;
    break;
  case OpNode::BITXOR:
    ires = icv1 ^ icv2;
    break;
  case OpNode::SHL:
    ires = icv1 << icv2;
    break;
  case OpNode::SHR:
    ires = icv1 >> icv2;
    break;
  case OpNode::UMINUS:
    if (isOutFloat) fres = -fcv1; else ires = -icv1;
  default:
    break;
  }
  // cerr << "res: " << ((outType==IRValue::FVALUE)?res:(long)res) << "\n";
  return (isOutFloat)?new IRValue(fres):new IRValue(ires);
}

IRValue* inFuncCallCodeGen(string & fname, list<Instruction*>& code) {
  Instruction* in = nullptr;
  if (fname == "readc") {
    in = new Instruction(Instruction::IN, {});
  } else if (fname == "readi") {
    in = new Instruction(Instruction::INI, {});
  } else if (fname == "readf") {
    in = new Instruction(Instruction::INF, {});
  }
  if (in) {
    code.push_back(in);
  }
  return in;
}

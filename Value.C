#include "Value.h"

#include <stdlib.h>
#include "STEClasses.h"

const int MININT = (int)(1 << 31);
const int MAXINT = ~(MININT);
const unsigned MAXUNSIGNEDINT = ~0;


extern long minVals[];
extern unsigned long maxVals[];

vector<Value*>*
copyValList(const vector<const Value*>& l) {
  vector<Value*>* vl = new vector<Value*>((vector<Value*>&)l);
  for (unsigned i= 0; i<l.size(); i++) {
	Value * v = (*vl)[i];
	(*vl)[i] = new Value(*v);
  }
  return vl;
}

Value::Value(Type::BaseTypeTag t, unsigned long ul) {
   if (!Type::isIntegral(t) && !Type::isBool(t))
      type_ = &Type::errorType;
   else {
      type_ = Type::type[t];
      lVal_ = (long)ul;
   }
}

Value::Value(long l) {
   lVal_ = l; type_ = &Type::errorType;
   for (unsigned i = Type::BIT; i <= Type::LONG; i++)
      if (i == Type::ENUM) continue;
      else if (!Type::isSigned((Type::BaseTypeTag)i) && l < 0) continue;
      else if (l >= minVals[i] && l <= (long)maxVals[i]) {
         type_ = Type::type[i];
         break;
      }
}

Value::Value(unsigned long ul) {
   lVal_ = (long)ul; type_ = &Type::errorType;
   for (unsigned i = Type::BIT; i <= Type::LONG; i++)
      if (i == Type::ENUM) continue;
      else if (ul <= maxVals[i]) {
         type_ = Type::type[i];
         break;
      }
}

Value::Value(unsigned ul) {
   lVal_ = (long)ul; type_ = &Type::errorType;
   for (unsigned i = Type::BIT; i <= Type::LONG; i++)
      if (i == Type::ENUM) continue;
      else if (ul <= maxVals[i]) {
         type_ = Type::type[i];
         break;
      }
}

Value::Value(int i, SymTabEntry* t) {
  if (t != nullptr && t->kind() == SymTabEntry::ENUM_ELEM_KIND) {
    type_ = t->type();
    lVal_ = i ;  
  } 
  else {
    internalErr("Value::Value: Expected enumerated type as argument");
    type_ = &Type::errorType ;
  }
}

Value::Value(const vector<Value*>* l, Type *t)   {
   if ((t) && (t->tag() == Type::VECTOR || t->tag() == Type::TUPLE)) {
      type_ = t; 
      listVal_ = copyValList(*(const vector<const Value*>*)l);
   }
   else {
      type_ = &Type::errorType ;
      internalErr("Value should be a list or tuple type");
   }
}

void
Value::releaseResources() {
   if (isString() && sVal_) {
      delete sVal_;
      sVal_ = nullptr;
   }
   else if (type_->tag() == Type::VECTOR || type_->tag() == Type::TUPLE) {
      if (listVal_) {
         for (auto v: *listVal_)
            if (v) delete v;
         delete listVal_;
         listVal_ = nullptr;
      }
   }
}

Value::~Value() {
  releaseResources();
}

void 
Value::print(ostream& os, int indent) const{
  if (!this) {
     os << "nullptr"; return;
  }
  Type::BaseTypeTag t;
  switch (t = type_->tag()) {
    case Type::ERROR: 
      os << "ErrorValue "; break;
    case Type::VOID: 
      os << "VoidValue"; break;
    case Type::BOOL: 
      os << ((lVal_ == false) ? "false" : "true"); 
      break;
    case Type::ENUM: 
       (*((EnumEntry*)(type_->typeDesc()))->elems())[lVal_]->print(os, indent);
      break;
    case Type::VECTOR:
    case Type::TUPLE:
      char c1, c2;
      unsigned int i, n ;
      n = (listVal_ != nullptr) ? listVal_->size() : 0;
	if (t == Type::VECTOR) {
	c1 = '{'; c2 = '}';
      }
      else {
	c1 = '('; c2 = ')'; 
      }
      os << c1;
      for (i=0 ; i < n ;i++) {
	(*listVal_)[i]->print(os, indent); 
	if (i < n-1)
	  os << ", ";
      }
      os << c2;
      break;
    default: 
	if (Type::isString(type_->tag()))
	  if (sVal_ == nullptr)
		os << "nullptr POINTER";
	  else os << "\"" << *sVal_ << "\""; 
	else if (Type::isIntegral(t))
	  if (Type::isSigned(t))
		os << lVal_; 
	  else os << (unsigned long)lVal_;
	else if (Type::isDouble(t)) 
	  os << dVal_;
	else internalErr("Value::print: unsupported value type");
  }
}

extern string newName(string type);

string 
Value::sval() const {
  if ((Type::isString(type_->tag())) && (sVal_ != nullptr))
      return *sVal_ ;
  else {
    internalErr("Value::sval: Incorrect Type ");
    return string();
  }
}


bool 
Value::bval() const {
  if (type_->tag() != Type::BOOL)
	internalErr("Value::bval: stored type is not bool");
  return lVal_;
}

long 
Value::lval() const {
  Type::BaseTypeTag tg = type_->tag();
  if (Type::isIntegral(tg))
     if (Type::isSigned(tg) || lVal_ <= ((long)maxVals[Type::LONG]))
        return lVal_;
  internalErr("Value::lval: Incorrect Type ");
  return 0;
}

unsigned long 
Value::ulval() const {
  Type::BaseTypeTag tg = type_->tag();
  if (Type::isIntegral(tg) && !Type::isSigned(tg))
     return (unsigned)lVal_;

  internalErr("Value::lval: Incorrect Type ");
  return 0;
}

double
Value::dval() const { 
  if (Type::isDouble(type_->tag()))
    return dVal_; 
  else if (Type::isIntegral(type_->tag()))
     return (double)lval();
  else {
    internalErr("Value::dval: Incorrect Type ");
	return 0.0;
  }
}

const vector<const Value*>* 
Value::listVal() const {
  if (type_->tag() == Type::VECTOR || type_->tag() == Type::TUPLE)
    return (const vector<const Value*>*)listVal_;
  else {
    internalErr("Value::listVal: Incorrect Type ");
  return nullptr;
  }
}

void
Value::sval(const string& s) { 
  if (Type::isString(type_->tag())) {
	if  (sVal_ != nullptr)
	   delete sVal_;
	sVal_ = new string(s);
  }
  else internalErr("Value::sval: Incorrect Type ");
}


void 
Value::dval(double d) {
  if (Type::isDouble(type_->tag()))
    dVal_ = d;
  else internalErr("Value::dval: Incorrect Type ");
}

void 
Value::listVal(const vector<Value*>* vl) {
  if (type_->tag() == Type::VECTOR || type_->tag() == Type::TUPLE)
    listVal_ = copyValList(*(const vector<const Value*>*)vl);
  else internalErr("Value::listVal: Incorrect Type ");
}

/*******************************/
 
bool
Value::operator==(const Value& v) const {
  if ((*type_ == *v.type_) || 
	  (Type::isIntegral(type_->tag()) && Type::isIntegral(v.type_->tag()))) {
	Type::BaseTypeTag t = type_->tag();
	switch (t) {
	case Type::ERROR:
	case Type::VOID:
	  return true;
	case Type::ENUM:
	  return (lVal_ == v.lVal_);
	case Type::VECTOR:
	case Type::TUPLE:
	  return ((listVal_ == v.listVal_) ||
			  ((listVal_ != nullptr) && (v.listVal_ != nullptr) && 
			   (*listVal_ == *v.listVal_)));

	default:
	  if (Type::isString(t))
		return((sVal_ == v.sVal_) || 
               ((sVal_!=nullptr) && (v.sVal_!=nullptr) && (*sVal_ == *v.sVal_)));
      else if (Type::isBool(t) || Type::isIntegral(t))
		return (lVal_ == v.lVal_);
	  else if (Type::isDouble(t))
		return (dVal_ == v.dVal_);
	}
  }
  return false;
}

bool
Value::operator<(const Value& v) const {
   Type::BaseTypeTag t = type_->tag(), vt = v.type_->tag();
   if (t != vt && (!isNumeric() || !v.isNumeric()))
      return (t < v.type_->tag());
   if (Type::isString(t))
      return (*sVal_ < *v.sVal_);
   else if (Type::isBool(t) || Type::isIntegral(t)) {
      if (Type::isSigned(t))
		return ((unsigned long)lVal_ < (unsigned long)v.lVal_);
      else return (lVal_ < v.lVal_);
   }
   else if (Type::isDouble(t))
      return (dVal_ < v.dVal_);
   else internalErr("Value::operator<: Invalid argument types");
  return false;
}

/********************************/

const Value&
Value::operator=(const Value& v) {
  releaseResources(); 
  type_ = v.type_; sVal_ = nullptr;
	Type::BaseTypeTag t = type_->tag();

	switch (t) {
	case Type::ERROR:
	case Type::VOID:
	  break;
	case Type::ENUM:
	  lVal_ = v.lVal_; break;
	case Type::VECTOR:
	case Type::TUPLE:
	  listVal_=copyValList(*(const vector<const Value*>*)(v.listVal_)); break;

	default:
	  if (Type::isString(t))
		sval(*v.sVal_);
	  else if (Type::isBool(t) || Type::isIntegral(t))
		lVal_ = v.lVal_;
	  else if (Type::isDouble(t))
		dVal_ = v.dVal_;
	  else internalErr("Value::operator=: Invalid argument types");
	}
  return (*this);
}

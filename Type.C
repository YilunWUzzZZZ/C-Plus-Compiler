#include "Type.h"
#include "SymTabEntry.h"
#include <climits>
#include <assert.h>
#include <stdlib.h>

const char* typeName[] = {
  "error", "unknown", "void", 
  "string",
  "bool", 
  "bit", 
  "unsigned char", "char", 
  "unsigned short", "short",
  "enum", 
  "unsigned int", "int", 
  "unsigned long", "long",
  "double",
  "vector", "set", "dict", "tuple", 
  "function",
  "numeric",
  "integral",
  "signed",
  "unsigned",
  "scalar",
  "primitive",
  "dict or set",
  "container",
  "container_or_str",
  "native",
  "data",
  "any"
};

const char* codename[] = {
  "ET_ERROR", "ET_UNKNOWN", "void", 
  "string", 
  "bool", 
  "bool", "unsigned char", "char", 
  "unsigned short", "short",
  "enum", 
  "unsigned", "int", 
  "unsigned long", "long",
  "double",
  "vector", "unordered_set", "unordered_map", "tuple", 
  "ET_FUNCTION",
  "ET_NUMERIC",
  "ET_INTEGRAL",
  "ET_SIGNED",
  "ET_UNSIGNED",
  "ET_SCALAR",
  "ET_PRIMITIVE",
  "ET_DICTORSET",
  "ET_CONTAINER",
  "ET_CONTAINER_OR_STR",
  "ET_NATIVE",
  "ET_DATA",
  "ET_ANY"
};

/* 
   sizes of various types in number bits 
   negative sizes indicate that the types size is undefined.
*/
const int Type::SIZE_UNDEF = -1;
int typeSize[] = {
  Type::SIZE_UNDEF, Type::SIZE_UNDEF, Type::SIZE_UNDEF,
  Type::SIZE_UNDEF,
  1,
  1,          
  8,          8,
  16,         16,
  32,
  32,         32,
  64,         64,
  64,
  Type::SIZE_UNDEF, Type::SIZE_UNDEF, Type::SIZE_UNDEF,
  Type::SIZE_UNDEF, Type::SIZE_UNDEF, Type::SIZE_UNDEF, 
  Type::SIZE_UNDEF, Type::SIZE_UNDEF, Type::SIZE_UNDEF,
  Type::SIZE_UNDEF, Type::SIZE_UNDEF, Type::SIZE_UNDEF,
  Type::SIZE_UNDEF, Type::SIZE_UNDEF, Type::SIZE_UNDEF,
  Type::SIZE_UNDEF, Type::SIZE_UNDEF
};

unsigned long maxVals[] = {
            0, 0, 0,
            0,
            1,         
            1,   
            UCHAR_MAX, CHAR_MAX,
            USHRT_MAX, SHRT_MAX,
            INT_MAX,
            UINT_MAX,  INT_MAX,
            ULONG_MAX, LONG_MAX,
            0,
            0, 0, 0, 0,
            0, 
            0, 0, 0,
            0, 0, 0,
            0, 0, 0,
            0, 0, 0
};

long minVals[] = {
            0, 0, 0,
            0,
            0,         
            0,
            0, CHAR_MIN,
            0, SHRT_MIN,
            0, 
            0, INT_MIN,
            0, LONG_MIN,
            0,
            0, 0, 0, 0,
            0,
            0, 0, 0,
            0, 0, 0,
            0, 0, 0,
            0, 0, 0
};

const string Type::name(TypeTag t) {
  if ((t >= ERROR) && (t <= ANY))
    return (t.isConst()? "const " : "") + string(typeName[t.tag()]);
  else return string();
}

const string Type::codeName(TypeTag t, bool inclConst) {
  if((t >= ERROR) && (t <= ANY))
    return (inclConst && t.isConst()? "const " : "") + string(codename[t.tag()]);
  else return string();
}

int Type::size(BaseTypeTag t) {
  if((t >= ERROR) && (t <= ANY))
    return (typeSize[t]);
  else return Type::SIZE_UNDEF;
}

const Type
  Type::errorType(ERROR), Type::unkType(UNKNOWN), Type::voidType(VOID),
  Type::stringType(STRING), Type::constStringType(TypeTag(STRING, true)), 
  Type::boolType(BOOL),
  Type::bitType(BIT), 
  Type::ucharType(UCHAR), Type::charType(CHAR), 
  Type::ushortType(USHORT), Type::shortType(SHORT), 
  Type::uintType(UINT), Type::intType(INT), 
  Type::ulongType(ULONG), Type::longType(LONG), 
  Type::doubleType(DOUBLE);

const Type
  Type::constUintType(Type::TypeTag(UINT, true));

const Type* Type::type[] = {
  &Type::errorType, &Type::unkType, &Type::voidType, 
  &Type::stringType,
  &Type::boolType,
  &Type::bitType, 
  &Type::ucharType, &Type::charType, 
  &Type::ushortType, &Type::shortType, 
  nullptr, 
  &Type::uintType, &Type::intType,
  &Type::ulongType,  &Type::longType,
  &Type::doubleType,
  nullptr, nullptr, nullptr, nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr
};

/****************************************************************
   Type Class 
****************************************************************/

Type::Type(TypeTag tag) {
  tag_ = tag; 
  argTypes_ = nullptr; 
  retType_ = nullptr;
};     

Type::Type(SymTabEntry* td, TypeTag t) {   
  tag_ = t; 
  typeDesc_ = td; 
};

Type::Type(Type* elemType, TypeTag t) { 
   assert(t == VECTOR || t == SET);
   tag_ = t;
   elemType_ = elemType; 
};

Type::Type(Type* keyType, Type* elemType) { 
   tag_ = DICT;
   keyType_ = keyType;
   elemType_ = elemType; 
};

Type::Type(vector<Type*>* tupleType, TypeTag t) {
  tag_ = t; 
  argTypes(tupleType); 
};

Type::Type(vector<Type*>* argt, Type* rt) {      
  tag_ = FUNCTION; 
  retType_ = rt; 
  argTypes_ = argt; 
};

string 
Type::fullName() const {
  if (!this) 
     return "nullptr";
  string info;
  if (isConst())
	info += "const ";
  switch (tag()) {
  case ENUM:
     
  case VECTOR:
     return info + elemType_->fullName() + " "+ name() ;

  case SET:
     return info + elemType_->fullName() + " "+ name() ;

  case DICT:
     return info + name() + "(" + keyType_->fullName() + ", " +
              elemType_->fullName() + ") ";

  case TUPLE:
  case FUNCTION:
     info += name(tag_) + " (";
     if (argTypes_ != nullptr) {
        for (unsigned int i=0; i< argTypes_->size(); i++) {
           if ((*argTypes_)[i] != nullptr)
              info += (*argTypes_)[i]->fullName() ;  
           if (i < argTypes_->size() - 1)
              info += ", ";
        }
     }
     if (tag_ == FUNCTION) {
		info += "): ";
		info += retType_->fullName() + " ";
     }
     else info += ") ";
     return info;

  default:
     if (info == "const " && name().find("const") < 2)
        info = "";
     break;
  }
  return info+name();
}

string 
Type::fullCodeName(bool inclConst) const {
  string info;
  switch (tag()) {
  case ENUM:
     
  case VECTOR:
     return codeName(inclConst)+ "<" +  elemType_->fullCodeName(inclConst)+ "> ";

  case SET:
     return codeName(inclConst)+ "<" +  elemType_->fullCodeName(inclConst)+ "> ";

  case DICT:
     return codeName(inclConst) + "<" +  keyType_->fullCodeName(inclConst) 
        + ", " + elemType_->fullCodeName() + "> ";

  case TUPLE: {
     info = codeName(inclConst) + "<";
     for (unsigned int i=0; i< argTypes_->size(); i++) {
        if ((*argTypes_)[i] != nullptr) 
           info += (*argTypes_)[i]->fullCodeName(inclConst);  
        if (i < argTypes_->size() - 1)
           info += ", ";
     }
     info += "> ";
     return info;
  }

  default:
     return codeName();
  }
}

const Type&
Type::operator=(const Type& t) {
  tag_ = t.tag_;
  switch (tag()) {
    case ENUM:

    case DICT:
      if (t.keyType_ != nullptr)
        keyType_ = new Type(*(t.keyType_));
	  else keyType_ = new Type(VOID);
    case SET:
    case VECTOR:
	  if (t.elemType_ != nullptr) 
		elemType_ = new Type(*(t.elemType_));
	  else elemType_ = new Type(VOID);
      break;

    case TUPLE:
    case FUNCTION: 
      if (t.argTypes_ != nullptr) {
	argTypes_ = new vector<Type*>(t.argTypes_->size());
	for (unsigned int i=0; i<t.argTypes_->size(); i++) 
	  (*argTypes_)[i] = new Type(*((*t.argTypes_)[i]));
      } 
	  else argTypes_ = nullptr;
	  if (tag_ == FUNCTION) {
		if (t.retType_ != nullptr)
		  retType_ = new Type(*(t.retType_));
		else retType_ = new Type(VOID);
      }
      break;

    default:
      break;
    }
  return *this;
}

void 
Type::print(ostream& os, int indent) const {
  os << fullName();
}

static bool
isSubType(vector<Type*>* l1, vector<Type*> *l2) { 
  unsigned int i=0;
  if ((l1 == nullptr) || (l2 == nullptr))
    return (l1 == l2);
  else if (l1->size() != l2->size())
    return false;
  else {
    for (i=0; (i < l1->size()); i++)
      if (!(*l1)[i]->isSubType(*(*l2)[i])) 
         return false;
	return true;
  }
}

bool 
Type::isSubType(const Type& t, bool relaxed) const {
  if (tag() <= BOOL)
    return (tag() == t.tag());
  else if (isNumeric(tag())) {
     if (!isNumeric(t.tag()))
        return false;
     if (tag() <= t.tag() && (isSigned(t.tag()) || !isSigned(tag())))
        return true;
     return (relaxed && (!isIntegral(t.tag()) || isIntegral(tag())));
  }
  else if (tag() != t.tag())
    return false;
  else {
    switch (tag()) {
    case ENUM:
    case SET:
    case VECTOR:
      return elemType_->isSubType(*t.elemType_) || elemType_->tag() == NATIVE;
    case DICT:
      return (elemType_->isSubType(*t.elemType_) && 
              keyType_->isSubType(*t.keyType_));

    case FUNCTION:
      return (retType_->isSubType(*t.retType_) && 
			  ::isSubType(t.argTypes_, argTypes_));

    case TUPLE:

    default:
      break;
    }
  }
  internalErr("Type::isSubType: unhandled case");
  return false;
}

bool
Type::isSubType(TypeTag t) const {
  if (Type::type[t.tag()] != nullptr) {
    return isSubType(*type[t.tag()]);
  }
  else if (tag() == t.tag())
     return true;
  else {
    switch (t.tag()) {
    case VECTOR:
      return isVector(tag());
    case SET:
      return isSet(tag());
    case DICT:
      return isDict(tag());
    case TUPLE:
      return isTuple(tag());

    case NUMERIC:
      return isNumeric(tag());
    case INTEGRAL:
      return isIntegral(tag());
    case SIGNED:
      return isSigned(tag());
    case UNSIGNED:
      return isUnsigned(tag());
    case SCALAR:
      return isScalar(tag());
    case PRIMITIVE:
      return isPrimitive(tag());
    case DICTORSET:
       return isDictOrSet(tag());
    case CONTAINER:
       return isContainer(tag());
    case CONTAINER_OR_STR:
       return isContainerOrStr(tag());
    case NATIVE:
      return isNative(tag());
    case DATA:
      return isData(tag());
    case ANY:
      return isValid(tag());
    default:
      cerr << name(tag()) << "  " << name(t) << endl ;
      internalErr("Unexpected case in Type::isSubType(TypeTag)");
      return false;
    }
  }
}

void Type::
unify(const Type* t, const ProgramElem* pe) {
   if (tag() == NATIVE) {
      *this = *t;
      return;
   }
   else if (t->tag() == NATIVE)
      return;

   if (isEquiv(*t))
      return;
   if (Type::isNumeric(tag()) && Type::isNumeric(t->tag())) {
      if (t->isSubType(*this))
         return;
      else if (isSubType(*t))
         *this = *t;
      else {
         for (BaseTypeTag tn = tag(); tn <= DOUBLE; tn = (BaseTypeTag)(tn+1)) {
            *this = Type(tn);
            if (t->isSubType(*this))
               return;
         }
         warnMsg("Possible type error: types " + name() +
                 " and " + t->name() + " are incompatible", pe);
         *this = errorType;
      }
      return;
   }

   if (tag() != t->tag()) {
      warnMsg(string("Possible type error: types ") + typeName[tag()] 
           + " and " + typeName[t->tag()] + " are incompatible", pe);
      *this = errorType;
      return;
   }

   switch (tag()) {
     case TUPLE:
        if (t->argTypes()->size() != argTypes()->size()) {
           warnMsg(string("Possible error: tuples of different sizes are ") +
                   "incompatible", pe);
           *this = errorType;
        }
        else {
           vector<Type*>* at = argTypes();
           for (unsigned i=0; i < at->size(); i++) {
              (*at)[i]->unify((*t->argTypes())[i], pe);
              if (*(*at)[i] == errorType) {
                 *this = errorType;
                 return;
              }
           }
        }
        break;

     case DICT:
        keyType()->unify(t->keyType(), pe);
     case VECTOR:
     case SET:
        elemType()->unify(t->elemType(), pe);
        break;

     default: 
        *this = errorType;
        break;
   }
}

bool 
Type::operator==(const Type& t) const {
  if (this == &t) 
    return true;
  else if (tag() != t.tag())
    return false;
  else if (isTagOnly(tag()))
    return true;
  else {
    switch (tag()) {
    case ENUM:

    case VECTOR:
    case SET:
      return (elemType_ == t.elemType_ ||
              (elemType_ && t.elemType_ && *elemType_ == *t.elemType_));

    case DICT:
      return ((elemType_ == t.elemType_ ||
               (elemType_ && t.elemType_ && *elemType_ == *t.elemType_)) &&
              (keyType_ == t.keyType_ ||
               (keyType_ && t.keyType_ && *keyType_ == *t.keyType_)));

    case FUNCTION: 
      if ((retType_ != t.retType_) &&
		  ((retType_ == nullptr) || (t.retType_==nullptr) ||
		   (*retType_ != *t.retType_)))
	return false;

    case TUPLE:
		return true;
    default:
      break;
    }
  }
  internalErr("Type::operator==: unhandled case");
  return false;
}


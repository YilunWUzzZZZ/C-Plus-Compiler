#ifndef VALUE_H
#define VALUE_H

#include "Type.h"


class Value;
class ProgramElem;
class SymTabEntry;

enum VarKind {FOREACH_VAR, FN_PARAM_VAR, LOCAL_VAR, GLOBAL_VAR,
              COMPILER_GENERATED_VAR, UNDEFINED};


class Value {
 private:
  const Type* type_;       
  union {            
    string* sVal_;
    long lVal_;
    double dVal_;
    vector<Value*>* listVal_;
  };

 public:
  Value() 
    { type_ = &Type::voidType;}
  Value(const char* s)
    { sVal_ = new string(s); type_ = &Type::stringType; }
  Value(const string& s)
    { sVal_ = new string(s); type_ = &Type::stringType; }
  Value(Type::BaseTypeTag t, unsigned long ul);
  Value(long l);
  Value(unsigned long ul);
  Value(unsigned u);
  Value(double d)
    { type_ = &Type::doubleType; dVal_ = d; }
  Value(int i, SymTabEntry* t); 
  Value(const vector<Value*>* l, Type *t) ;  
  Value(Type::BaseTypeTag t) 
   { type_ = Type::type[t];  sVal_ = nullptr;}
  Value(const Value& v): type_(v.type_) { sVal_ = nullptr; *this = v;}

  ~Value();

  const Type* type() const { return type_; } 
  
  bool isIntegral() const { return Type::isIntegral(type()->tag()); };
  bool isNumeric() const { return Type::isNumeric(type()->tag()); };
  bool isString() const { return Type::isString(type()->tag()); };
  bool isDouble() const {return Type::isDouble(type()->tag());}

  string sval() const;
  bool bval() const;
  int ival() const;
  long lval() const;
  unsigned long ulval() const;
  double dval() const;
  const vector<const Value*>* listVal() const;
  size_t hash() const;

  void sval(const string& s) ;
  void bval(bool b) { lVal_ = b ;} 
  void ival(int i) ;
  void lval(long l) ;
  void dval(double d) ;
  void listVal(const vector<Value*>* vl) ; 

  void print(ostream& os, int indent=0) const;

  bool operator==(const Value&) const;
  bool operator!=(const Value& v) const { return !operator==(v);};
  bool operator<(const Value& v) const;
  bool operator>(const Value& v) const { return v < *this; };
  bool operator<=(const Value& v) const
     { return (*this < v) || (*this == v); }
  bool operator>=(const Value& v) const {return v <= *this;};
  const Value& operator=(const Value&);

  static Value zero() {return Value(0l); };

 private:
  void releaseResources();
}
;

inline ostream& operator<< (ostream& os, const Value& tt) {
  tt.print(os);
  return os;
};

#endif

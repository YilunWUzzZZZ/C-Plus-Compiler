#ifndef ST_H
#define ST_H

#include <string>
#include <unordered_map>
#include <iostream>
#include "util/FastHash.h"
#include "Value.h"
  
using namespace std;

struct string_eq {
  bool operator()(const string s1, const string s2) const {
    return s1==s2;
  }
};

struct string_hash {
  size_t operator() (const string& s1) const {
    return fasthash64(s1.data());
  }
};

class SymTabEntry;
class Type;

typedef unordered_map<const string, SymTabEntry *, string_hash, string_eq> Hmap;
typedef unordered_map<const string, SymTabEntry *, string_hash, string_eq>::iterator HmapNCIt;
typedef unordered_map<const string, SymTabEntry *, string_hash, string_eq>::const_iterator HmapCIt;

enum ErrorST {OK, DUPLICATE_SYM, INVALID_SCOPE, SYM_NOT_PRESENT};

class SymTab {
 public:
  class const_iterator {
  private:
    const SymTabEntry* current;
  public:
    const_iterator(const SymTabEntry *c) { current = c; };
    const SymTabEntry* operator* () const { return current;};
    const_iterator & operator++ () ;
    bool operator==(const const_iterator& i) const {return (current == i.current);};
    bool operator!=(const const_iterator& i) const {return !(operator==(i));};
  };
  class iterator {
  private:
    SymTabEntry* current;
  public:
    iterator(SymTabEntry *c) { current = c; };
    SymTabEntry* operator* () { return current;};
    iterator & operator++ ();
    bool operator==(const iterator& i) const {return (current == i.current);};
    bool operator!=(const iterator& i) const {return !operator==(i);};
  };

 private:
  Hmap map_;
  SymTabEntry* parent_;
  SymTabEntry* first_;
  SymTabEntry* last_;

 public:
  SymTab(SymTabEntry* parent);
  ~SymTab() {};

  int size() const {return map_.size();};

  SymTabEntry* parent() { return parent_; };
  const SymTabEntry* parent() const { return parent_; };
  const SymTabEntry* lookUp(string name) const;
  SymTabEntry* lookUp(string name) {
    return (SymTabEntry*)(((const SymTab*)this)->lookUp(name));
  }

  ErrorST insert(SymTabEntry*); 
  void print(ostream& os=cout,int indent=0) const {emitST(os, indent);};

  virtual void emitST(ostream& os,int ind=0,char ldelim='{',char rdelim='}',
                      bool linebreaks=true, int first=0, int last=0) const;

  const_iterator begin() const { return const_iterator(first_); };
  iterator begin() { return iterator(first_); };
  const_iterator end() const { return const_iterator(nullptr); };
  iterator end() { return iterator(nullptr); };
    
 private:
  SymTab(const SymTab&);
  SymTab operator=(const SymTab &);
};

#endif


#ifndef __ICODE_GEN_H__
#define __ICODE_GEN_H__
#include <string>
#include <vector>
#include <unordered_map>
#include "IR.h"
#include "STEClasses.h"
#define FREG_NUM 1000
#define IREG_NUM 1000
#define SP_ID 900
#define BP_ID 910
#define RADDR_ID 920
#define RSPILL_1_ID 950
#define RSPILL_2_ID 960
#define FSPILL_1_ID 950
#define FSPILL_2_ID 960
using namespace std;

class ICodeOprand;
class IRValue;
class VariableEntry;

class ICode {
public:
    enum OpCode {
        MOVL, MOVS, MOVI, MOVF,
        MOVIF, MOVFI,
        LDI, LDF,
        STI, STF,
        JMP, JMPC, JMPI, JMPCI,
        ADD, SUB, DIV, MUL, MOD, NEG, AND, OR, XOR,
        FADD, FSUB, FDIV, FMUL, FNEG,
        GT, GE, UGT, UGE, EQ, NE,
        FGT, FGE, FEQ, FNE,
        PRTI, PRTS, PRTF,
        IN, INI, INF,
        LABEL
    };
    ICode(OpCode opcode, const vector<ICodeOprand*> & oprands): opcode_(opcode) {
        for (auto & opr: oprands) {
            oprands_.push_back(opr);
        }
    }
    ICode(const string & l):opcode_(LABEL) {label_=l;}
    ~ICode(){}
    void label(const string & str) {label_=str;}
    string label() {return label_;}
    void cond(ICode* c) {cond_=c;}
    ICode* cond() {return cond_;}
    void setOprand(unsigned int i, ICodeOprand * opr) {
        if (i < oprands_.size()) {
            oprands_[i] = opr;
        } else if (i == oprands_.size()) {
            oprands_.push_back(opr);
        }
    }
    ICodeOprand* getOprand(unsigned int i) {return i<oprands_.size()?oprands_[i]:nullptr;}
    OpCode opcode() {return opcode_;}
    string str();
private:
    OpCode opcode_;
    vector<ICodeOprand*> oprands_;
    string label_;
    ICode* cond_{nullptr};
};

class ICodeOprand {
public:
    enum Type {
        FREG, IREG, 
        FLOAT, INT, STRING, 
        LABEL,
    };
    ICodeOprand(){}
    ~ICodeOprand(){}
    ICodeOprand(Type t, int rid): type_(t), regID_(rid){}
    ICodeOprand(double fval): type_(FLOAT), fval_(fval) {}
    ICodeOprand(Type t, string str): type_(t), sval_(str) {}
    ICodeOprand(long ival): type_(INT), ival_(ival) {}
    long ival() { return ival_;}
    void ival(long i) { ival_=i; }
    bool isConst() const {return type_ >= FLOAT && type_ <= STRING;}
    bool isLabel() const { return type_==LABEL; }
    Type type() { return type_; }
    string str();
private:
    Type type_;
    union 
    {
        int regID_;
        double fval_;
        long ival_;
        string sval_;
    };

};

class ICodeGenMgr {
public:
    ICodeGenMgr(unordered_map<int, int>* vreg2PhyReg, unordered_map<int, int>* spillOffsets) {
        vreg2PhyReg_=vreg2PhyReg; vreg2SpillLoc_=spillOffsets;
    }
    ~ICodeGenMgr(){}
    ICodeOprand* reg(int id, bool isFloat);
    ICodeOprand* constInt(long ival) { return new ICodeOprand(ival); }
    ICodeOprand* constFloat(long fval) { return new ICodeOprand(fval); }
    ICodeOprand* constStr(const string & s) { return new ICodeOprand(ICodeOprand::STRING, s);}
    ICodeOprand* label(const string & l) { return new ICodeOprand(ICodeOprand::LABEL, l);}
    ICodeOprand* loadSpilledVar(int spillOffset, int tmpRID, bool isFloat, vector<ICode*> & icode);
    void storeSpilledVar(int spillOffset, int tmpRID, bool isFloat, vector<ICode*> & icode);
    void pushReg(int rid, bool isFloat, vector<ICode*> & icode);
    void popReg(int rid, bool isFloat, vector<ICode*> & icode);
    void pushLabelOrStr(const string & sval, bool isString, vector<ICode*> & icode);
    void pushValue(IRValue* irv, vector<ICode*> & icode);
    ICodeOprand* movConst2TmpReg(ICodeOprand *constVal, vector<ICode*> & icode, int tmpRegID=0);
    void decSP(vector<ICode*> & icode, int len=1);
    void incSP(vector<ICode*> & icode, int len=1);
    void loadFromStk(int dstRID, int offset, bool isFloat, vector<ICode*> & icode );
    void storeInStk(IRValue* irv, int stkOffset, vector<ICode*> & icode);
    ICodeOprand* evalAddr(vector<IRValue*> &oprands, vector<ICode*> & icode, bool rspill0Used);
    ICodeOprand* genICodeOprd(IRValue* irv);
    bool spilled(IRValue* irv) { return irv->isReg() && (*vreg2PhyReg_)[irv->regNum()] == -1;}
    int spillOffset(IRValue* irv) { 
        return  spilled(irv)?(*vreg2SpillLoc_)[irv->regNum()]:0;
    }
    int getPhyRegNum(int vrid) { return (*vreg2PhyReg_)[vrid]; }
    string genRetLabelName(const string & prefix) {return prefix + "_call_ret_" + to_string(retLabelCnt_++);}
    
private:
    unordered_map<int, ICodeOprand*> iregs_, fregs_;
    unordered_map<int, int> *vreg2PhyReg_;
    unordered_map<int, int> *vreg2SpillLoc_;
    int retLabelCnt_{0};
public:
    static ICodeOprand sp, bp, raddr, rspills[2], fspills[2];
};


#endif
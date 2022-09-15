#ifndef __IR_H__
#define __IR_H__
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <set>
using namespace std;

class IRValue;
class Instruction;
class Function;
class BasicBlock;
class Use;
class IRGenManager;
class RegAllocator;
class VariableEntry;
class SymTabEntry;

typedef list<Instruction*>::iterator CodeIterator;
typedef CodeIterator BlockIterator;
typedef vector<BasicBlock*>::iterator FunctionIterator;


class IRValue {
public:
    enum ValueType {
        FREG, IREG,
        FVALUE, IVALUE, SVALUE, 
        LABEL,
        ADDR,
        VOID,
    };
    IRValue(): type_(VOID), sym_(nullptr)  {}
    IRValue(ValueType t): type_(t), sym_(nullptr)  {}
    IRValue(SymTabEntry* sym): type_(ADDR), regNum_(-2), sym_(sym)  {}
    IRValue(long ival): type_(IVALUE), ival_(ival), sym_(nullptr) {}
    IRValue(double fval): type_(FVALUE), fval_(fval), sym_(nullptr)  {}
    IRValue(ValueType t, int regNum, SymTabEntry* sym=nullptr): type_(t), regNum_(regNum), sym_(sym)  {}
    IRValue(ValueType t, std::string strOrLabel): type_(t), sval_(strOrLabel), sym_(nullptr)  {}
    virtual ~IRValue() {};
    bool isTemprary() const {return (type_ == ValueType::FREG || type_ == ValueType::IREG) && sym_ == nullptr;}
    bool isConst() const { return type_==FVALUE || type_==IVALUE || type_==SVALUE; }
    bool isFloatConst() const { return type_==FVALUE; }
    bool isIntConst() const { return type_==IVALUE; }
    bool isStrConst() const { return type_==SVALUE; }
    bool isFloatReg() const {return type_==FREG; }
    bool isIntReg() const {return type_==IREG; }
    bool isFloatVal() const {return (isFloatReg() || isFloatConst());}
    bool isIntVal() const {return isIntConst() || isIntReg();}
    bool isLabel() const {return type_==LABEL;}
    bool isReg() const {return (isIntReg() || isFloatReg());}
    bool isAddr() const { return type_==ADDR; }
    void type(ValueType t) {type_=t;}
    ValueType type() const {return type_;}
    void regNum(int id) {regNum_=id;}
    int regNum() { return regNum_; }
    SymTabEntry* sym() const { return sym_; }
    void sym( SymTabEntry* sym) { sym_=sym; }
    string sval() const { return sval_; }
    void sval(const string & s) { sval_=s; }
    long ival() {return ival_;}
    void ival(long i) { ival_=i; }
    double fval() {return fval_;}
    void fval(double fv) { fval_=fv; }
    //vector<Use*>* uses() {return &uses_;}
    string name();
    string codeName(int pRegID=-1);
    static IRValue* typeConvert(IRValue* v); 
private:
    ValueType type_;
    union {
        int regNum_;
        double fval_;
        long ival_;
        std::string sval_;   //string or lable
    };
    SymTabEntry* sym_;
    
    //vector<Use*> uses_;
};


class Instruction: public IRValue {
public:
    enum OpCode {
        MOVL, MOVS, MOVI, MOVF,
        MOVIF, MOVFI,
        LDI, LDF,
        STI, STF,
        JMP, JMPC, JMPI, JMPCI, CALL, RETURN,// (ONLY for IR)
        ADD, SUB, DIV, MUL, MOD, NEG, AND, OR, XOR,
        FADD, FSUB, FDIV, FMUL, FNEG,
        GT, GE, UGT, UGE, EQ, NE,
        FGT, FGE, FEQ, FNE,
        PRTI, PRTS, PRTF,
        IN, INI, INF,
        LABEL,
        ALLOCA, 
    };
    Instruction(OpCode opcode, IRValue* op1, IRValue* op2=nullptr, int regN=-1);
    Instruction(OpCode opcode, IRValue::ValueType t, IRValue * op1, IRValue* op2=nullptr)
        :IRValue(t), opcode_(opcode)  {
            oprands_.push_back(op1); if (op2) oprands_.push_back(op2); regNum(-1);
    }
    Instruction(OpCode opcode, const vector<IRValue*> & vals, int regN=-1);
    Instruction(const string & label): IRValue(IRValue::ValueType::LABEL, label), opcode_(LABEL) {}
    ~Instruction() {}
    void label(const std::string & str) { sval(str); } 
    string label() const { return sval(); }
    bool isLabel() const { return opcode_ == LABEL; }
    IRValue* getOprand(unsigned int nth) const { 
        if (nth < oprands_.size()) return oprands_[nth];
        return nullptr;
    }
    void setOprand(unsigned int nth, IRValue* newOp) { if (nth < oprands_.size() ) oprands_[nth]=newOp; }
    void addOprand(IRValue* newOp) { oprands_.push_back(newOp); }
    void popOprand() { oprands_.pop_back(); }
    vector<IRValue*> getAllOprands() {return oprands_;}
    IRValue::ValueType instType2ValType(Instruction::OpCode opcode);
    string str();
    OpCode opcode() const { return opcode_; }
    void opcode(OpCode op) { opcode_ = op; }
    bool isJmpInst() const { return opcode_>=JMP && opcode_ <= JMPCI; }
    bool isCallInst() const { return opcode_==CALL; }
    bool isReturnInst() const { return opcode_==RETURN; }
    bool isArithInst() const { return opcode_ >= ADD && opcode_ <= FNEG; }
    bool isMovInst() const { return opcode_>=MOVL && opcode_<=MOVFI; }
    bool isLoadInst() const { return opcode_==LDI || opcode_ == LDF; }
    bool isStoreInst() const {return opcode_ == STI || opcode_ == STF; }
    bool isCmpInst() const { return opcode_ >=GT && opcode_ <= FNE; }
    bool isPrtInst() const { return opcode_ >= PRTI && opcode_ <= PRTF; }
    bool isInInst() const { return opcode_ >= IN && opcode_ <= INF;}
    bool isAlloca() const { return opcode_ == ALLOCA; }
private:
    OpCode opcode_;
    vector<IRValue*> oprands_;
};


class Use {
private:
    Instruction* user_;
    int nthOprand_;
    
public:
    Use(Instruction* user, int nthOprand): user_(user), nthOprand_(nthOprand) {}
    ~Use() {}
    Instruction* user() {return user_;}
    int nthOprand() {return nthOprand_;} 
};

class BasicBlock {
private:
    vector<BasicBlock*> preds_;
    vector<BasicBlock*> succs_;
    CodeIterator firstInst_;
    CodeIterator endInst_; // not included in the block
    string label_;
    set<int>* liveOut_{nullptr};
    Function* function_;

public:
    BasicBlock(Function* f): function_(f) { }
    BasicBlock(const CodeIterator & firstInst):firstInst_(firstInst) {}
    void firstInst(const CodeIterator & first) { firstInst_=first; }
    void endInst(const CodeIterator & end) { endInst_=end; }
    BlockIterator begin() { return firstInst_; }
    BlockIterator end() { return endInst_; }
    vector<BasicBlock*>& preds() {return preds_;}
    vector<BasicBlock*>& succs() {return succs_;}
    void label(const string & label) { label_=label; }
    string label() { return label_; }
    set<int>* liveOut() {return liveOut_;}
    void liveOut(set<int>* liveOut) { liveOut_ = liveOut; }
    void deleteInst(CodeIterator instIter);
    bool empty() {return begin()==end(); }
    void print(ostream& os);
};

class Function {
public:
    Function(list<Instruction*>* code, IRGenManager*mgr): code_(code), mgr_(mgr) {}
    ~Function() {}
    vector<BasicBlock*> & basicBlocks() {return basicBlocks_;}
    BasicBlock* entryBlock() { return basicBlocks_.size()?basicBlocks_[0]:nullptr; }
    void livenessAnalysis();
    void printCFG(ostream& os);
    void buildInterGraph(RegAllocator* iregAlloc, RegAllocator* fregAlloc);
    unordered_map<int, IRValue*>& rid2IRValue() {return *rid2IRValue_;}
    void rid2IRValue(unordered_map<int, IRValue*>* m) { rid2IRValue_=m; }
    unordered_map<Instruction*, set<int>> & call2LiveOut() {return call2LiveOut_;}
    list<Instruction*>* code() {return code_;}
    IRGenManager* manager() {return mgr_;}
    void deleteEmptyBlock(BasicBlock* bb);
private:
    vector<BasicBlock*> basicBlocks_;
    unordered_map<int, IRValue*> *rid2IRValue_{nullptr};
    unordered_map<int, int> *vReg2PhyReg_{nullptr};
    unordered_map<Instruction*, set<int>> call2LiveOut_;
    list<Instruction*> *code_;
    IRGenManager *mgr_;
};

#endif
#include "STEClasses.h"
#include "Value.h"
#include "ParserUtil.h"
#include "RegAlloc.h"
#include "MemAlloc.h"
#include "IR.h"
#include "IRGen.h"
#include "ICodeGen.h"
#include "Optimization.h"
#define NUM_REGS 3

extern Type voidType;
extern Optimizer optimizer;
bool doLookUpBeforeTypeCheking = false;
bool copySym = false;
bool skipSemiColon = false;
bool debugOn = false;

/****************** global entry ******************/
void
GlobalEntry::print(ostream& os, int indent) const {
	emitST(os, indent-STEP_INDENT, '\0', '\0', true);
}

// Yan 11/16
const Type*
GlobalEntry::typeCheck(){
	// not sure what to return for global entry... dont think the return value is important, simply call type check for everything would be enough
	SymTab* st = symTab();
	if(st != nullptr && st->size() != 0){
		SymTab::iterator it = st->begin();
		for(; it != st->end(); ++it){
			if((*it) != nullptr){
				(*it)->typeCheck();
			}
		}
	}
	return nullptr;
}

void
GlobalEntry::typePrint(ostream& os, int indent) const{
	const SymTab* st = symTab();
	if(st != nullptr && st->size() != 0){
		SymTab::const_iterator it = st->begin();
		for(; it != st->end(); ++it){
			if((*it) != nullptr){
				(*it)->typePrint(os, indent);
				os << ";\n";
			}
		}
	}
}

/****************** function entry ******************/
void
FunctionEntry::print(ostream& os, int indent) const {
	if(type() != nullptr){
		type()->print(os, indent);
	}
	os << " " << name() << "(";
	const SymTab* st = symTab();
	if (st != nullptr && st->size() != 0){
		int num_params = 0;
		SymTab::const_iterator it = st->begin();
		for(; it != st->end(); ++it){
			if((*it) != nullptr){
				if(((SymTabEntry*)(*it))->kind() == SymTabEntry::VARIABLE_KIND){
					if(((VariableEntry*)(*it))->varKind() == FN_PARAM_VAR){
						num_params ++;
					}else{
						break;
					}
				}else{
					break;
				}
			}
		}
		if(num_params){
			emitST(os, indent, '\0', '\0', false, 0, num_params);
		}
	}

	if(body_ != nullptr){
		os << ") ";
		body_->print(os, indent);
	}else{
		os << ")";
		os << ";";
	}
}

// Yan 11/16
const Type*
FunctionEntry::typeCheck(){
	SymTab* st = symTab();
	vector<Type*>* argTypes = new vector<Type*>();
	if (st != nullptr && st->size() != 0){
		SymTab::iterator it = st->begin();
		for(; it != st->end(); ++it){
			if((*it) != nullptr){
				argTypes->push_back((Type*)(*it)->typeCheck());
			}
		}
	}
	Type* ret_Type = type();
	type(new Type(argTypes, ret_Type));

	if(body_ != nullptr){
		body_->typeCheck();
	}

	return nullptr;
}

void
FunctionEntry::typePrint(ostream& os, int indent) const{
	if(type() != nullptr){
		type()->print(os, indent);
	}
	os << " " << name() << "(";
	const SymTab* st = symTab();
	if (st != nullptr && st->size() != 0){
		SymTab::const_iterator it = st->begin();

		for(; it != st->end();){
			if((*it) != nullptr){
				if(((SymTabEntry*)(*it))->kind() == SymTabEntry::VARIABLE_KIND){
					if(((VariableEntry*)(*it))->varKind() == FN_PARAM_VAR){
						((VariableEntry*)(*it))->typePrint(os, indent);
					}else{
						break;
					}
					if(++it != st->end()){
						os << ", ";
					}
				}else{
					break;
				}
			}
		}
	}

	os << ")";
	if(body_ != nullptr){
		body_->typePrint(os, indent);
	}
}

/****************** variable entry ******************/
void
VariableEntry::print(ostream& os, int indent) const {
	// type is in ProgramElem class, which is the parent of VariableEntry's parent (SymTabEntry)
	// name is in SymTabEntry
	if(type() != nullptr){
		type()->print(os, indent);
	}
	os << " " << name();
	if(offset()){
		os << "[";
		offset()->print(os, indent);
		os << "]";

	}
	if(initVal()){
		os << " = ";
		initVal()->print(os, indent);
   	}
   	if(varKind() == LOCAL_VAR){
   		os << ";";
   	}
}

//Yan : 11/19
const Type*
VariableEntry::typeCheck(){
	// offset for array? TO-DO: offset
	if(type()->tag() == Type::UNKNOWN){
		// TO-DO: need to add a text field in type?
		errMsg("Undeclared type \"" + type()->fullName() + "\"", line(), column(), file().c_str());
	}
    // check array subscripts
    if (nSubscripts()) {
        for (unsigned int i=0; i<nSubscripts(); i++) {
            if (!subscript(i)) {
                continue;
            }
            auto t = subscript(i)->typeCheck();
            if (!t->isIntegral()) {
                errMsg("Invalid type for array subscript", this);
            }
        }
    }
	if(initVal() != nullptr) {
		ExprNode* init_val = initVal();
		if(init_val->exprNodeType() == OP_NODE && ((OpNode*)init_val)->opCode() == OpNode::SET){
			vector<ExprNode*>* init_args = ((OpNode*)init_val)->args();
			Type* array_type = type();
			if(array_type == nullptr){
				errMsg("Array declaration type error.");
			}else{
				vector<ExprNode*>::iterator it = init_args->begin();
				for(; it != init_args->end(); it ++){
					if((*it) != nullptr){
						Type* arg_type = (*it)->type();
						if(arg_type != nullptr){
							if(arg_type->fullName() != array_type->fullName() && !(arg_type->isSubType(array_type->tag()))){
								if(Type::isIntegral(arg_type->tag()) && Type::isIntegral(array_type->tag())){
									cerr << file() << ":" << line() << "." << column() << ":Warning: Signedness or possible integer overflow in assignment" << endl;
								}else{
									errMsg("Assigned type '" + arg_type->fullName() + "' not a subtype of target type '" + array_type->fullName() + "' in array initialization", line(), column(), file().c_str());
								}
							}
						}
					}
				}
			}
		}else{
			const Type* init_type = initVal()->typeCheck();
			if(init_type != nullptr && type() != nullptr){
				if(init_type->fullName() != type()->fullName() && !(init_type->isSubType(type()->tag()))){
					if(Type::isIntegral(init_type->tag()) && Type::isIntegral(type()->tag())){
						cerr << file() << ":" << line() << "." << column() << ":Warning: Signedness or possible integer overflow in assignment" << endl;
					}else{
						errMsg("Assigned type '" + init_type->fullName() + "' not a subtype of target type '" + type()->fullName() + "'", line(), column(), file().c_str());
					}
				}
			}
		}
	}
	return type();
}


void
VariableEntry::typePrint(ostream& os, int indent) const{
	// TO-DO: offset
	if(type() != nullptr){
		type()->print(os, indent);
	}
	if (nSubscripts()) {
			for (unsigned int i=0; i<nSubscripts(); i++) {
					if (!subscript(i)) {
							continue;
					}
					os << "[";
					subscript(i)->typePrint(os, indent);
					os << "]";
			}
	}
	os << " " << name();
	if(initVal() != nullptr){
		os << " = ";
		initVal()->typePrint(os, indent);
	}
}

/****************** enum entry ******************/
void
EnumEntry::print(ostream& os, int indent) const {
	os << "enum " << name() << " {";

	if(elems_ != nullptr && elems_->size() != 0){
		vector<EnumElemEntry*>::const_iterator it = elems_->begin();
		if((*it) != nullptr){
			(*it)->print(os, indent);
		}
		for(it ++; it != elems_->end(); it ++){
			if((*it) != nullptr){
				os << ", ";
				(*it)->print(os, indent);
			}
		}
	}
	os << "};";
}

// Yan 11/16
const Type*
EnumEntry::typeCheck(){
	if(elems_ != nullptr && elems_->size() != 0){
		vector<EnumElemEntry*>::const_iterator it = elems_->begin();
		for(; it != elems_->end(); it ++){
			if((*it) != nullptr){
				(*it)->typeCheck();
			}
		}
	}
	return nullptr;
}

void
EnumEntry::typePrint(ostream& os, int indent) const{
	os << "enum " << name() << " {";

	if(elems_ != nullptr && elems_->size() != 0){
		vector<EnumElemEntry*>::const_iterator it = elems_->begin();
		if((*it) != nullptr){
			(*it)->typePrint(os, indent);
		}
		for(it ++; it != elems_->end(); it ++){
			if((*it) != nullptr){
				os << ", ";
				(*it)->typePrint(os, indent);
			}
		}
	}
	os << "};";
}

/****************** block entry ******************/
void
BlockEntry::print(ostream& os, int indent) const {
	prtSpace(os, indent+STEP_INDENT);
	emitST(os, indent, '\0', '\0', true);
}

// Yan 11/16 updated: Yan 11/18
const Type*
BlockEntry::typeCheck(){
	SymTab* st = symTab();
	if(st != nullptr && st->size() != 0){
		SymTab::iterator it = st->begin();
		for(++it; it != st->end(); ++it){
			if((*it) != nullptr){
				(*it)->typeCheck();
			}
		}
	}

	return nullptr;
}

void
BlockEntry::typePrint(ostream& os, int indent) const{
	const SymTab* st = symTab();
	if(st != nullptr && st->size() != 0){
		SymTab::const_iterator it = st->begin();
		for(++it; it != st->end(); ++it){
			// first element is itself
			if((*it) != nullptr){
				prtSpace(os, indent+STEP_INDENT);
				(*it)->typePrint(os, indent);
				os << ";\n";
			}
		}
	}
}

/*------------------------------------------------------------------------------------------------------------------------*/

void
GlobalEntry::codeGen() {
    const SymTab *st = symTab();
     if (!st) return;
     for (SymTab::const_iterator it=st->begin(); it != st->end(); ++it) {
         if ((*it)->kind() == FUNCTION_KIND) {
             FunctionEntry* fe = (FunctionEntry*)(*it);
             fe->codeGen();
             // cout << "Finished IRGen for Function " << fe->name() << "\n";
         }
     }
}

void
GlobalEntry::dbgPrint(ostream& os) const {
    if (!debugOn) {
        return;
    }
     const SymTab *st = symTab();
     if (!st) return;
     for (SymTab::const_iterator it=st->begin(); it != st->end(); ++it) {
         if ((*it)->kind() == FUNCTION_KIND) {
             FunctionEntry* fe = (FunctionEntry*)(*it);
             fe->dbgPrint(os);
         }
     }
}

void
FunctionEntry::dbgPrint(ostream& os) const {
    if (!IR_.size() || !debugOn ) {
        return;
    }
    os << "\nCompilation Debug Info for Func " << name() << "\n";
    os << "--------IR---------\n";
    os << name() << ":\n";
    for (auto inst: IR_) {
        cout << inst->str() << "\n";
    }
    cout << "\n";
    os << "--------CFG---------\n";
    if (cfg_) {
        cfg_->printCFG(os);
    }
    if (!ira || !fra) return;
    auto rid2irv = cfg_->rid2IRValue();
    os << "====IntRegAlloc Result====\n";
    for (auto res: ira->vReg2PReg()) {
        int vrid = res.first, prid = res.second;
        string s = prid >= 0?("R"+to_string(prid)):("spilled at " + to_string(ira->vReg2StkOff()[vrid]));
        os << rid2irv[vrid]->name() << " : " << s << "\n";
    }
    os << "====FtRegAlloc Result====\n";
    for (auto res: fra->vReg2PReg()) {
        int vrid = res.first, prid = res.second;
        string s = prid >= 0?("F"+to_string(prid)):("spilled at " + to_string(fra->vReg2StkOff()[vrid]));
        os << rid2irv[vrid]->name() << " : " << s << "\n";
    }
}

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void
GlobalEntry::memAlloc(MemAllocator* allocator) {
    const SymTab *st = symTab();
     if (!st) return;
     for (SymTab::const_iterator it=st->begin(); it != st->end(); ++it) {
         auto symKind =  (*it)->kind();
         if ( symKind == VARIABLE_KIND) {
             auto ste = (VariableEntry*)(*it);
             int ndims = ste->nSubscripts();
             if (!ndims) {
                int newAddr = allocator->allocOnHeap(1);
                ste->heapOffset(newAddr);
             } else {
                int arraySize = 1, dimProduct=1;
                vector<IRValue*> & dimProdVec = *(ste->dimProducts());
                vector<IRValue*> & dimVec = *(ste->dims());
                list<Instruction*> code;
                IRGenManager mgr(false);
                for (int i=ndims-1; i>=0; i--) {
                    ExprNode* expr = ste->subscript(i);
                    IRValue* res = expr->codeGen(&mgr, code);
                    if (!res->isIntConst()) {
                        errMsg("The size of global array must be a constant integer!", ste);
                        exit(0);
                    }
                    int dimSize = (int)res->ival();
                    if (i != 0) {
                        dimProduct *= dimSize;
                        dimProdVec.insert(dimProdVec.begin(), new IRValue((long)dimProduct));
                    }
                    dimVec.insert(dimVec.begin(), new IRValue((long)dimSize));
                    arraySize *= dimSize;
                }
                ste->heapOffset(allocator->allocOnHeap(arraySize));
             }

         }
     }
}

void
FunctionEntry::memAlloc(MemAllocator* allocator) {
    // first, allocate space for function parameters
    // i.e. determine their offsets(positive) to the BP
    // array paramter must have constant dim sizes, highest dim is ignored  e.g int a[] int a[][5] int a[1][5]
    const SymTab *st = symTab();
    SymTab::const_iterator it = nullptr;

    int nparams = type()->arity();
    if (st) {
        it = st->begin();
        for (int i=0; i<nparams; ++i, ++it) {
            VariableEntry* varEntry =  (VariableEntry*)(*it);
            varEntry->stkOffset(FIRST_PRAM_OFFSET + i);
            if (varEntry->nSubscripts()) {
                int  dimProduct=1, ndims = varEntry->nSubscripts();
                auto & dimProdVec = *varEntry->dimProducts();
                list<Instruction*> code;
                IRGenManager mgr(false);
                for (int i=ndims-1; i>0; i--) {
                    ExprNode* expr = varEntry->subscript(i);
                    if (!expr) {
                        errMsg("missing subscript for array", expr);
                        exit(0);
                    }
                    IRValue* res = expr->codeGen(&mgr, code);
                    if (!res->isIntConst()) {
                        errMsg("Subscript for array paramters must be constant int", expr);
                        exit(0);
                    }
                    int dimSize = (int)res->ival();
                    dimProduct *= dimSize;
                    dimProdVec.insert(dimProdVec.begin(), new IRValue((long)dimProduct));
                }
                varEntry->isVLA(true);
            }
        }
    }
    if (body_)
        body_->memAlloc(allocator);

}

void
BlockEntry::memAlloc(MemAllocator* allocator) {
    const SymTab *st = symTab();
    if (!st) return;
    for (SymTab::const_iterator it=st->begin(); it != st->end(); ++it) {
        if ((*it)->kind() == VARIABLE_KIND) {
            auto ste = (VariableEntry*)(*it);
            int ndims = ste->nSubscripts();
            if (!ndims) {
                continue;
            }
            int arraySize = 1, dimProduct=1;
            vector<IRValue*>  dimProdVec;
            vector<IRValue*>  dimVec;
            list<Instruction*> code;
            IRGenManager mgr(false);
            bool skipVLA = false;
            for (int i=ndims-1; i>=0; i--) {
                ExprNode* expr = ste->subscript(i);
                IRValue* res = expr->codeGen(&mgr, code);
                if (!res->isIntConst()) {
                    ste->isVLA(true);
                    skipVLA = true;
                    break;
                }
                int dimSize = (int)res->ival();
                if (i != 0) {
                    dimProduct *= dimSize;
                    dimProdVec.insert(dimProdVec.begin(), new IRValue((long)dimProduct));
                }
                dimVec.insert(dimVec.begin(), new IRValue((long)dimSize));
                arraySize *= dimSize;
            }
            if (skipVLA) {
                continue;
            }
            *ste->dims() = dimVec;
            *ste->dimProducts() = dimProdVec;
            ste->stkOffset(allocator->allocOnStk(arraySize));
            allocator->arraysOnStk()->push_back(ste);
        }
    }
}

void
FunctionEntry::codeGen() {
    if (!body_) return;
    MemAllocator ma;
    memAlloc(&ma);
    SymTab* st = symTab();
#if 0
    cout << "MemAlloc Result for Function " << name() << " max stk depth: " << ma.maxDepth() << "\n";
    for (auto a: *ma.arraysOnStk()) {
        cout << "array offset for " << a->name() << " " << a->stkOffset() << "\n";
    }
#endif
    IRGenManager mgr;
    // load function paramter
    if (st) {
        for (auto it=st->begin(); it != st->end(); ++it) {
            VariableEntry* ve = (VariableEntry*)(*it);
            if (ve->varKind() == VarKind::FN_PARAM_VAR) {
                Instruction* loadInst = new Instruction(Instruction::LDI, new IRValue(ve));
                loadInst->sym(ve);
                mgr.checkAndSetSymReg(ve, loadInst);
                IR_.push_back(loadInst);
            }
        }
    }
    // Gen IR
    body_->codeGen(&mgr, IR_);
    mergeLabels(&mgr, IR_);
    deleteUnreachable(IR_);
    // check return stmt at the end of the function
    if ((IR_.size() && !IR_.back()->isReturnInst()) || !IR_.size()) {
        cerr << "Warning: Missing return at the end of function " << name() << "\n";
        IR_.push_back(new Instruction(Instruction::RETURN, {nullptr}));
    }
#if 0
    cout << "\nBefore OPT: \n"; 
    for (auto inst: IR_) {
        cout << inst->str() << "\n";
    }
#endif
    
    // build CFG
    CFGBuilder builder;
    cfg_ = builder.getFunctionCFG(IR_, &mgr);
    cfg_->rid2IRValue(new unordered_map<int, IRValue*>(mgr.rid2Value()));
    

    // OPT
    optimizer.optimize(*cfg_);
#if 0
    cout << "\nAfter OPT: \n"; 
    for (auto inst: IR_) {
        cout << inst->str() << "\n";
    }
#endif
    // Date flow analysis
    cfg_->livenessAnalysis();
    
    // Register Allocation
    ira = new RegAllocator(NUM_REGS); fra = new RegAllocator(NUM_REGS);
    RegAllocator & iregAlloc = *ira, &fregAlloc = *fra;
    cfg_->buildInterGraph(&iregAlloc, &fregAlloc);
    iregAlloc.allocate(cfg_->rid2IRValue());
    fregAlloc.stkOff(iregAlloc.stkOff());
    fregAlloc.allocate(cfg_->rid2IRValue());

    offset_ = fregAlloc.stkOff() - 1;
    // adjust array offsets
    for (auto a : *ma.arraysOnStk()) {
        a->stkOffset(offset_ + a->stkOffset());
        if (debugOn)
            cout << "adjusted array offset for " << a->name() << " " << a->stkOffset() << "\n";
    }
    offset_ += ma.maxDepth();

    auto vreg2PhyReg = new unordered_map<int, int>(), vreg2SpillOffset = new unordered_map<int, int>();
    unordered_map<int, int> & iregSpillLoc = iregAlloc.vReg2StkOff(), & fregSpillLoc = fregAlloc.vReg2StkOff();
    for (auto p:  iregAlloc.vReg2PReg()) {
        if (p.second == -1) {
            (*vreg2SpillOffset)[p.first] = iregSpillLoc[p.first];
            (*vreg2PhyReg)[p.first]  = -1;
        } else {
            (*vreg2PhyReg)[p.first] = p.second;
        }
    }
     for (auto p:  fregAlloc.vReg2PReg()) {
        if (p.second == -1) {
            (*vreg2SpillOffset)[p.first] = fregSpillLoc[p.first];
             (*vreg2PhyReg)[p.first]  = -1;
        } else {
            (*vreg2PhyReg)[p.first] = p.second;
        }
    }
    assert((vreg2PhyReg->size() == (iregAlloc.vReg2PReg().size() + fregAlloc.vReg2PReg().size())));
    ICodeGenMgr icodeMgr(vreg2PhyReg, vreg2SpillOffset);
    ICodeGen(&icodeMgr);

    // print some results

}

const ICode::OpCode opCode2ICodeOp[] = {
    ICode::MOVL, ICode::MOVS, ICode::MOVI, ICode::MOVF,
    ICode::MOVIF, ICode::MOVFI,
    ICode::LDI, ICode::LDF,
    ICode::STI, ICode::STF,
    ICode::JMP, ICode::JMPC, ICode::JMPI, ICode::JMPCI, ICode::JMPCI, ICode::JMPCI,// (padding 2)
    ICode::ADD, ICode::SUB, ICode::DIV, ICode::MUL, ICode::MOD, ICode::NEG, ICode::AND, ICode::OR, ICode::XOR,
    ICode::FADD, ICode::FSUB, ICode::FDIV, ICode::FMUL, ICode::FNEG,
    ICode::GT, ICode::GE, ICode::UGT, ICode::UGE, ICode::EQ, ICode::NE,
    ICode::FGT, ICode::FGE, ICode::FEQ, ICode::FNE,
    ICode::PRTI, ICode::PRTS, ICode::PRTF,
    ICode::IN, ICode::INI, ICode::INF,
    ICode::LABEL, // (ONLY for IR)
};


void
FunctionEntry::ICodeGen(ICodeGenMgr* mgr) {
    unordered_map<int, IRValue*> & rid2Val = cfg_->rid2IRValue();
    auto & call2LiveOut = cfg_->call2LiveOut();
    string funcRetLabelNm = "_" + name() + "_ret";
    // push old bp
    ICode_.push_back(new ICode(name()));
    mgr->pushReg(BP_ID, false, ICode_);
    // mov sp to bp
    ICode_.push_back(new ICode(ICode::MOVI, {&mgr->sp, &mgr->bp}));
    // allocate space for spilled vars
    if (offset_ > 0)
        mgr->decSP(ICode_, offset_);
    for (auto inst: IR_) {
        auto opc = opCode2ICodeOp[inst->opcode()];
        if (inst->isArithInst() || inst->isMovInst()) {
            vector<ICodeOprand*> ioprands;
            int i=0;
            for (auto irv: inst->getAllOprands()) {
                if (!irv) {
                    continue;
                }
                ICodeOprand* iopr = mgr->genICodeOprd(irv);
                if (!iopr) {
                    iopr = mgr->loadSpilledVar(mgr->spillOffset(irv), i++, irv->isFloatReg(), ICode_);
                }
                ioprands.push_back(iopr);
            }
            ICodeOprand* dst = mgr->genICodeOprd(inst);
            bool dstIsFLoat = inst->isFloatReg(), spilled = false;
            if (!dst) {
                dst = inst->isFloatReg()?&mgr->fspills[0]:&mgr->rspills[0];
                spilled = true;
            }
            ioprands.push_back(dst);
            ICode_.push_back(new ICode(opc, ioprands));
            if (spilled) {
                mgr->storeSpilledVar(mgr->spillOffset(inst), 0, dstIsFLoat, ICode_);
            }
        } else if (inst->opcode() == Instruction::JMPC) {
            Instruction* cmp = (Instruction*)inst->getOprand(0);
            vector<ICodeOprand*> ioprands;
            int i=0;
            for (auto irv: cmp->getAllOprands()) {
                ICodeOprand* iopr = mgr->genICodeOprd(irv);
                if (!iopr) {
                    iopr = mgr->loadSpilledVar(mgr->spillOffset(irv), i++, irv->isFloatReg(), ICode_);
                }
                ioprands.push_back(iopr);
            }
            ICode* icmp = new ICode(opCode2ICodeOp[cmp->opcode()],  ioprands);
            ICode* ijmpc = new ICode(opc, {mgr->genICodeOprd(inst->getOprand(1))});
            ijmpc->cond(icmp);
            ICode_.push_back(ijmpc);
            ICode_.push_back(new ICode(ICode::JMP, {mgr->genICodeOprd(inst->getOprand(2))}));
        } else if (inst->opcode() == Instruction::JMP) {
            ICode_.push_back(new ICode(opc, {mgr->genICodeOprd(inst->getOprand(0))}));
        } else if (inst->isCallInst()) {
            // push 2save value
            auto & liveVars = call2LiveOut[inst];
            stack<int> pushedRegs;
            for (auto vrid: liveVars) {
                IRValue* irv = rid2Val[vrid];
                if (!mgr->spilled(irv)) {
                    int prid = mgr->getPhyRegNum(vrid);
                    mgr->pushReg(prid, irv->isFloatReg(), ICode_);
                    pushedRegs.push(vrid);
                }
            }
            // push arguments, from right to left
            auto args = inst->getAllOprands();
            FunctionEntry* callee = (FunctionEntry*) args[0]->sym();
            args.erase(args.begin());
            for (int i=args.size()-1; i >=0; i--) {
                mgr->pushValue(args[i], ICode_);
            }
            mgr->decSP(ICode_); // skip RV
            string retLabelNm = mgr->genRetLabelName(name());
            mgr->pushLabelOrStr(retLabelNm, false, ICode_);
            ICode_.push_back(new ICode(ICode::JMP, {mgr->label(callee->name())} ));
            ICode_.push_back(new ICode(retLabelNm));
            // post call sequence
            if (inst->regNum() >= 0) {
                bool rvIsFloat = inst->isFloatReg();
                auto ldOp = rvIsFloat?ICode::LDF:ICode::LDI;
                if (mgr->spilled(inst)) {
                    ICodeOprand* tmp = rvIsFloat?&mgr->fspills[0]:&mgr->rspills[0];
                    ICode_.push_back(new ICode(ldOp, {&mgr->sp, tmp}));
                    mgr->storeSpilledVar(mgr->spillOffset(inst), 0, rvIsFloat, ICode_);
                } else {
                    ICode_.push_back(new ICode(ldOp, {&mgr->sp, mgr->reg(mgr->getPhyRegNum(inst->regNum()), rvIsFloat)}));
                }
            }
            // pop out rv & all the argments
            mgr->incSP(ICode_, args.size() + 1);
            //pop out all the saved regs
            while(pushedRegs.size()) {
                int vrid = pushedRegs.top();
                pushedRegs.pop();
                IRValue* irv = rid2Val[vrid];
                mgr->popReg(mgr->getPhyRegNum(vrid), irv->isFloatReg(), ICode_);
            }

        } else if (inst->isReturnInst()) {
            // store return value
            IRValue* rv = inst->getOprand(0);
            if (rv) {
                mgr->storeInStk(rv, -RV_OFFSET, ICode_);
            }
            ICode_.push_back(new ICode(ICode::JMP, {mgr->label(funcRetLabelNm)}));
        } else if (inst->isLoadInst()) {
            bool dstIsFloat = inst->isFloatReg();
            VariableEntry* sym = (VariableEntry*)inst->getOprand(0)->sym();
            if (sym->varKind() == FN_PARAM_VAR && mgr->spilled(inst)) {
                continue;
            }
            auto oprands = inst->getAllOprands();
            ICodeOprand* addr = mgr->evalAddr(oprands, ICode_, false);
            ICodeOprand* dst = mgr->genICodeOprd(inst);
            if(!dst) {
                ICodeOprand* spillDst = dstIsFloat?&mgr->fspills[0]:&mgr->rspills[0];
                ICode_.push_back(new ICode(opc, {addr, spillDst}));
                mgr->storeSpilledVar(mgr->spillOffset(inst), 0, dstIsFloat, ICode_);
            } else {
                ICode_.push_back(new ICode(opc, {addr, dst }));
            }
        } else if (inst->isStoreInst()) {
            // store,  array global vars
            auto oprands = inst->getAllOprands();
            IRValue* stored = oprands.back();
            ICodeOprand* stSrc = mgr->genICodeOprd(stored);
            bool stIsFloat = stored->isFloatVal();
            bool rspill0Used=false;
            if(!stSrc) {
                stSrc = mgr->loadSpilledVar(mgr->spillOffset(stored), 0, stIsFloat, ICode_);
                if (!stIsFloat) {
                    rspill0Used=true;
                }
            } else if (stSrc->isConst() || stSrc->isLabel()) {
                stSrc = mgr->movConst2TmpReg(stSrc, ICode_);
                if (!stIsFloat) {
                    rspill0Used=true;
                }
            }
            oprands.pop_back();
            ICodeOprand* addr = mgr->evalAddr(oprands, ICode_, rspill0Used);
            ICode_.push_back(new ICode(opc, {stSrc, addr }));
        } else if (inst->isLabel()) {
            ICode_.push_back(new ICode(inst->label()));
        } else if (inst->isPrtInst()) {
            IRValue* arg = inst->getOprand(0);
            ICodeOprand* opr = mgr->genICodeOprd(arg);
            if (!opr) {
                opr = mgr->loadSpilledVar(mgr->spillOffset(arg), 0, arg->isFloatVal(), ICode_);
            }
            ICode_.push_back(new ICode(opc, {opr}));
        } else if (inst->opcode() == Instruction::ALLOCA) {
            IRValue* alen = inst->getOprand(0);
            ICodeOprand* alenOprd = mgr->genICodeOprd(alen);
            ICodeOprand* arrayOprd = mgr->genICodeOprd(inst);
            if (!alenOprd) {
                alenOprd = mgr->loadSpilledVar(mgr->spillOffset(alen), 0, false, ICode_);
            }
            ICode_.push_back(new ICode(ICode::SUB, {&mgr->sp, alenOprd, &mgr->sp}));
            if (arrayOprd) {
                ICode_.push_back(new ICode(ICode::MOVI, {&mgr->sp, arrayOprd}));
            } else {
                ICode_.push_back(new ICode(ICode::ADD, {&mgr->bp, mgr->constInt(-mgr->spillOffset(inst)), &mgr->raddr}));
                ICode_.push_back(new ICode(ICode::STI, {&mgr->sp, &mgr->raddr} ));
            }
        } else if (inst->isInInst() && inst->regNum() >= 0) {
            ICodeOprand* inReg = mgr->genICodeOprd(inst);
            if (!inReg) {
                inReg = mgr->loadSpilledVar(mgr->spillOffset(inst), 0, inst->isFloatReg(), ICode_);
            }
            ICode_.push_back(new ICode(opc, {inReg}));
        }
    }
    // return seqeuence
    ICode_.push_back(new ICode(funcRetLabelNm));
    // mov sp to the bp's position
    ICode_.push_back(new ICode(ICode::MOVI, {&mgr->bp, &mgr->sp}));
    // restore caller's bp
    ICode_.push_back(new ICode(ICode::LDI, {&mgr->sp, &mgr->bp}));
    mgr->incSP(ICode_);
    // pop out return address
    ICode_.push_back(new ICode(ICode::LDI, {&mgr->sp, &mgr->raddr}));
    mgr->incSP(ICode_);
    ICode_.push_back(new ICode(ICode::JMPI, {&mgr->raddr}));
}

void
FunctionEntry::emitICode() {
    for (auto icode: ICode_) {
        string s = icode->str();
        if (icode->opcode() == ICode::LABEL) {
            code_ += "\n" + s + " ";
        } else {
            code_ += s + "\n";
        }
    }
}

void
GlobalEntry::emitICode(ostream & os) {
    const SymTab *st = symTab();
    if (!st) return;
    os << "MOVI 10000 R900\n"; // init rsp
    os << "MOVI 10000 R910\n"; // init rbp
    os << "SUB R900 2 R900\nMOVL __exit R950\nSTI R950 R900\n" ;

    os << "JMP main\n";
    for (SymTab::const_iterator it=st->begin(); it != st->end(); ++it) {
        if ((*it)->kind() == FUNCTION_KIND) {
            FunctionEntry* fe = (FunctionEntry*)(*it);
            fe->emitICode();
            if (fe->code().size()) {
                os << fe->code() << "\n";
            }
        }
    }

    os << "\n__exit: ADD R000 0 R000\n";
}

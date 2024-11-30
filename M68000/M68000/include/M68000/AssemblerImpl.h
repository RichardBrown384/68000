#pragma once

#include <cstdint>
#include <vector>
#include <functional>

namespace rbrown::m68000 {

enum class InstructionMnemonics {
    UNKNOWN,
    ABCD,
    ADDA,
    ADDI,
    ADDQ,
    ADDX,
    ADD,
    ANDI,
    ANDI_CCR,
    ANDI_SR,
    AND,
    ASL_REGISTER,
    ASL_IMMEDIATE,
    ASL_MEMORY,
    ASR_REGISTER,
    ASR_IMMEDIATE,
    ASR_MEMORY,
    Bcc,
    BCHG_DYNAMIC_REGISTER,
    BCHG_DYNAMIC_MEMORY,
    BCHG_STATIC_REGISTER,
    BCHG_STATIC_MEMORY,
    BCLR_DYNAMIC_REGISTER,
    BCLR_DYNAMIC_MEMORY,
    BCLR_STATIC_REGISTER,
    BCLR_STATIC_MEMORY,
    BRA,
    BSET_DYNAMIC_REGISTER,
    BSET_DYNAMIC_MEMORY,
    BSET_STATIC_REGISTER,
    BSET_STATIC_MEMORY,
    BSR,
    BTST_DYNAMIC_REGISTER,
    BTST_STATIC_REGISTER,
    BTST_DYNAMIC_MEMORY,
    BTST_STATIC_MEMORY,
    CHK,
    CLR,
    CMPA,
    CMPI,
    CMPM,
    CMP,
    DBcc,
    DIVS,
    DIVU,
    EORI,
    EORI_CCR,
    EORI_SR,
    EOR,
    EXG,
    EXT,
    ILLEGAL,
    JMP,
    JSR,
    LEA,
    LINK,
    LSL_REGISTER,
    LSL_IMMEDIATE,
    LSL_MEMORY,
    LSR_REGISTER,
    LSR_IMMEDIATE,
    LSR_MEMORY,
    MOVEA,
    MOVE_CCR,
    MOVEM_REGISTER,
    MOVEM_MEMORY,
    MOVEP,
    MOVEQ,
    MOVE_SR_SR,
    MOVE_SR_MEMORY,
    MOVE_USP_USP,
    MOVE_USP_REGISTER,
    MOVE,
    MULS,
    MULU,
    NBCD,
    NEGX,
    NEG,
    NOP,
    NOT,
    ORI,
    ORI_CCR,
    ORI_SR,
    OR,
    PEA,
    RESET,
    ROL_REGISTER,
    ROL_IMMEDIATE,
    ROL_MEMORY,
    ROR_REGISTER,
    ROR_IMMEDIATE,
    ROR_MEMORY,
    ROXL_REGISTER,
    ROXL_IMMEDIATE,
    ROXL_MEMORY,
    ROXR_REGISTER,
    ROXR_IMMEDIATE,
    ROXR_MEMORY,
    RTE,
    RTR,
    RTS,
    SBCD,
    Scc,
    STOP,
    SUBA,
    SUBI,
    SUBQ,
    SUBX,
    SUB,
    SWAP,
    TAS,
    TRAP,
    TRAPV,
    TST,
    UNLK
};

enum class OperandSizes {
    UNKNOWN,
    UNSIZED,
    BYTE,
    WORD,
    LONG
};

enum class ConditionCodes {
    UNKNOWN,
    TRUE,
    FALSE,
    HI,
    LS,
    CC,
    CS,
    NE,
    EQ,
    VC,
    VS,
    PL,
    MI,
    GE,
    LT,
    GT,
    LE
};

enum class AddressModes {
    UNKNOWN,
    DATA_DIRECT,
    ADDRESS_DIRECT,
    ADDRESS_INDIRECT,
    ADDRESS_INCREMENT,
    ADDRESS_DECREMENT,
    ADDRESS_DISPLACEMENT,
    ADDRESS_INDEX,
    ABSOLUTE_SHORT,
    ABSOLUTE_LONG,
    PROGRAM_COUNTER_DISPLACEMENT,
    PROGRAM_COUNTER_INDEX,
    IMMEDIATE,
    CONDITION_CODE_REGISTER,
    STATUS_REGISTER,
    USER_STACK_POINTER
};

enum class IndexRegisterTypes {
    UNKNOWN,
    DATA,
    ADDRESS
};

enum class IndexRegisterSizes {
    UNKNOWN,
    WORD,
    LONG,
};

class AddressModeData {
public:
    AddressModeData() : mode{},
                        registerNumber{},
                        indexRegisterType{ IndexRegisterTypes::UNKNOWN },
                        indexRegisterSize{ IndexRegisterSizes::UNKNOWN },
                        indexRegisterNumber{},
                        index{},
                        displacement{},
                        absoluteAddress{},
                        immediate{} {}

    void SetMode(AddressModes v) { mode = v; }
    void SetRegisterNumber(int64_t v) { registerNumber = v; }
    void SetIndexRegister(IndexRegisterTypes type, IndexRegisterSizes size, int64_t indexRegister) {
        indexRegisterType = type;
        indexRegisterSize = size;
        indexRegisterNumber = indexRegister;
    }
    void SetIndex(int64_t v) { index = v; }
    void SetDisplacement(int64_t v) { displacement = v; }
    void SetAbsoluteAddress(int64_t v) { absoluteAddress = v; }
    void SetImmediate(int64_t v) { immediate = v; }

    [[nodiscard]] auto& GetMode() const { return mode; }
    [[nodiscard]] auto& GetRegisterNumber() const { return registerNumber; }
    [[nodiscard]] auto& GetIndexRegisterType() const { return indexRegisterType; }
    [[nodiscard]] auto& GetIndexRegisterSize() const { return indexRegisterSize; }
    [[nodiscard]] auto& GetIndexRegisterNumber() const { return indexRegisterNumber; }
    [[nodiscard]] auto& GetIndex() const { return index; }
    [[nodiscard]] auto& GetDisplacement() const { return displacement; }
    [[nodiscard]] auto& GetAbsoluteAddress() const { return absoluteAddress; }
    [[nodiscard]] auto& GetImmediate() const { return immediate; }

private:
    AddressModes mode;
    int64_t registerNumber;

    IndexRegisterTypes indexRegisterType;
    IndexRegisterSizes indexRegisterSize;
    int64_t indexRegisterNumber;
    int64_t index;
    int64_t displacement;

    int64_t absoluteAddress;
    int64_t immediate;
};

class BranchCondition {
public:
    BranchCondition() : code{ ConditionCodes::UNKNOWN }, displacement{} {}
    void SetCode(ConditionCodes v) { code = v; }
    void SetDisplacement(int64_t v) { displacement = v; }
    [[nodiscard]] const auto& GetCode() const { return code; }
    [[nodiscard]] const auto& GetDisplacement() const { return displacement; }
private:
    ConditionCodes code;
    int64_t displacement;
};

class RegisterList {
public:
    RegisterList() : registers{} {}

    [[nodiscard]] auto GetRegisterList() const { return registers; }

    auto Accumulate(uint32_t start, uint32_t end) {
        if (start > end) {
            std::swap(start, end);
        }
        registers |= (1u << end) + ((1u << end) - (1u << start));
    }

private:
    uint16_t registers;
};

class InstructionData {
public:
    InstructionData() : mnemonic{ InstructionMnemonics::UNKNOWN },
                      size{ OperandSizes::UNKNOWN },
                      source{},
                      destination{},
                      branchCondition{},
                      registerList{} {}

    void SetMnemonic(InstructionMnemonics v) { mnemonic = v; }
    void SetSize(OperandSizes v) { size = v; }

    [[nodiscard]] const auto& GetMnemonic() const { return mnemonic; }
    [[nodiscard]] const auto& GetSize() const { return size; }
    [[nodiscard]] const auto& GetSourceData() const { return source; }
    [[nodiscard]] const auto& GetDestinationData() const { return destination; }
    [[nodiscard]] const auto& GetBranchCondition() const { return branchCondition; }
    [[nodiscard]] const auto& GetRegisterList() const { return registerList; }

    auto& GetSourceData() { return source; }
    auto& GetDestinationData() { return destination; }
    auto& GetBranchCondition() { return branchCondition; }
    auto& GetRegisterList() { return registerList; }

private:
    InstructionMnemonics mnemonic;
    OperandSizes size;
    AddressModeData source;
    AddressModeData destination;
    BranchCondition branchCondition;
    RegisterList registerList;
};

using Emitter = std::function<void(uint16_t)>;

bool CheckABCD(const InstructionData&);
bool CheckADDA(const InstructionData&);
bool CheckADDI(const InstructionData&);
bool CheckADDQ(const InstructionData&);
bool CheckADDX(const InstructionData&);
bool CheckADD(const InstructionData&);
bool CheckANDI(const InstructionData&);
bool CheckANDI_CCR(const InstructionData&);
bool CheckANDI_SR(const InstructionData&);
bool CheckAND(const InstructionData&);
bool CheckASL_Register(const InstructionData&);
bool CheckASL_Immediate(const InstructionData&);
bool CheckASL_Memory(const InstructionData&);
bool CheckASR_Register(const InstructionData&);
bool CheckASR_Immediate(const InstructionData&);
bool CheckASR_Memory(const InstructionData&);

bool CheckBcc(const InstructionData&);
bool CheckBCHG_Dynamic_Register(const InstructionData&);
bool CheckBCHG_Static_Register(const InstructionData&);
bool CheckBCHG_Dynamic_Memory(const InstructionData&);
bool CheckBCHG_Static_Memory(const InstructionData&);
bool CheckBCLR_Dynamic_Register(const InstructionData&);
bool CheckBCLR_Static_Register(const InstructionData&);
bool CheckBCLR_Dynamic_Memory(const InstructionData&);
bool CheckBCLR_Static_Memory(const InstructionData&);
bool CheckBRA(const InstructionData&);
bool CheckBSET_Dynamic_Register(const InstructionData&);
bool CheckBSET_Static_Register(const InstructionData&);
bool CheckBSET_Dynamic_Memory(const InstructionData&);
bool CheckBSET_Static_Memory(const InstructionData&);
bool CheckBSR(const InstructionData&);
bool CheckBTST_Dynamic_Register(const InstructionData&);
bool CheckBTST_Static_Register(const InstructionData&);
bool CheckBTST_Dynamic_Memory(const InstructionData&);
bool CheckBTST_Static_Memory(const InstructionData&);

bool CheckCHK(const InstructionData&);
bool CheckCLR(const InstructionData&);
bool CheckCMPA(const InstructionData&);
bool CheckCMPI(const InstructionData&);
bool CheckCMPM(const InstructionData&);
bool CheckCMP(const InstructionData&);

bool CheckDBcc(const InstructionData&);
bool CheckDIVS(const InstructionData&);
bool CheckDIVU(const InstructionData&);

bool CheckEORI(const InstructionData&);
bool CheckEORI_CCR(const InstructionData&);
bool CheckEORI_SR(const InstructionData&);
bool CheckEOR(const InstructionData&);
bool CheckEXG(const InstructionData&);
bool CheckEXT(const InstructionData&);

bool CheckILLEGAL(const InstructionData&);

bool CheckJMP(const InstructionData&);
bool CheckJSR(const InstructionData&);

bool CheckLEA(const InstructionData&);
bool CheckLINK(const InstructionData&);
bool CheckLSL_Register(const InstructionData&);
bool CheckLSL_Immediate(const InstructionData&);
bool CheckLSL_Memory(const InstructionData&);
bool CheckLSR_Register(const InstructionData&);
bool CheckLSR_Immediate(const InstructionData&);
bool CheckLSR_Memory(const InstructionData&);

bool CheckMOVEA(const InstructionData&);
bool CheckMOVE_CCR(const InstructionData&);
bool CheckMOVEM_Register(const InstructionData&);
bool CheckMOVEM_Memory(const InstructionData&);
bool CheckMOVEP(const InstructionData&);
bool CheckMOVEQ(const InstructionData&);
bool CheckMOVE_SR_SR(const InstructionData&);
bool CheckMOVE_SR_Memory(const InstructionData&);
bool CheckMOVE_USP_USP(const InstructionData&);
bool CheckMOVE_USP_Register(const InstructionData&);
bool CheckMOVE(const InstructionData&);
bool CheckMULS(const InstructionData&);
bool CheckMULU(const InstructionData&);

bool CheckNBCD(const InstructionData&);
bool CheckNEGX(const InstructionData&);
bool CheckNEG(const InstructionData&);
bool CheckNOP(const InstructionData&);
bool CheckNOT(const InstructionData&);

bool CheckORI(const InstructionData&);
bool CheckORI_CCR(const InstructionData&);
bool CheckORI_SR(const InstructionData&);
bool CheckOR(const InstructionData&);

bool CheckPEA(const InstructionData&);

bool CheckRESET(const InstructionData&);
bool CheckROL_Register(const InstructionData&);
bool CheckROL_Immediate(const InstructionData&);
bool CheckROL_Memory(const InstructionData&);
bool CheckROR_Register(const InstructionData&);
bool CheckROR_Immediate(const InstructionData&);
bool CheckROR_Memory(const InstructionData&);
bool CheckROXL_Register(const InstructionData&);
bool CheckROXL_Immediate(const InstructionData&);
bool CheckROXL_Memory(const InstructionData&);
bool CheckROXR_Register(const InstructionData&);
bool CheckROXR_Immediate(const InstructionData&);
bool CheckROXR_Memory(const InstructionData&);
bool CheckRTE(const InstructionData&);
bool CheckRTR(const InstructionData&);
bool CheckRTS(const InstructionData&);

bool CheckSBCD(const InstructionData&);
bool CheckScc(const InstructionData&);
bool CheckSTOP(const InstructionData&);
bool CheckSUBA(const InstructionData&);
bool CheckSUBI(const InstructionData&);
bool CheckSUBQ(const InstructionData&);
bool CheckSUBX(const InstructionData&);
bool CheckSUB(const InstructionData&);
bool CheckSWAP(const InstructionData&);

bool CheckTAS(const InstructionData&);
bool CheckTRAPV(const InstructionData&);
bool CheckTRAP(const InstructionData&);
bool CheckTST(const InstructionData&);

bool CheckUNLK(const InstructionData&);

bool EmitABCD(InstructionData&, Emitter&);
bool EmitADDA(InstructionData&, Emitter&);
bool EmitADDI(InstructionData&, Emitter&);
bool EmitADDQ(InstructionData&, Emitter&);
bool EmitADDX(InstructionData&, Emitter&);
bool EmitADD(InstructionData&, Emitter&);
bool EmitANDI(InstructionData&, Emitter&);
bool EmitANDI_CCR(InstructionData&, Emitter&);
bool EmitANDI_SR(InstructionData&, Emitter&);
bool EmitAND(InstructionData&, Emitter&);
bool EmitASL_Register(InstructionData&, Emitter&);
bool EmitASL_Immediate(InstructionData&, Emitter&);
bool EmitASL_Memory(InstructionData&, Emitter&);
bool EmitASR_Register(InstructionData&, Emitter&);
bool EmitASR_Immediate(InstructionData&, Emitter&);
bool EmitASR_Memory(InstructionData&, Emitter&);

bool EmitBcc(InstructionData&, Emitter&);
bool EmitBCHG_Dynamic_Register(InstructionData&, Emitter&);
bool EmitBCHG_Static_Register(InstructionData&, Emitter&);
bool EmitBCHG_Dynamic_Memory(InstructionData&, Emitter&);
bool EmitBCHG_Static_Memory(InstructionData&, Emitter&);
bool EmitBCLR_Dynamic_Register(InstructionData&, Emitter&);
bool EmitBCLR_Static_Register(InstructionData&, Emitter&);
bool EmitBCLR_Dynamic_Memory(InstructionData&, Emitter&);
bool EmitBCLR_Static_Memory(InstructionData&, Emitter&);
bool EmitBRA(InstructionData&, Emitter&);
bool EmitBSET_Dynamic_Register(InstructionData&, Emitter&);
bool EmitBSET_Static_Register(InstructionData&, Emitter&);
bool EmitBSET_Dynamic_Memory(InstructionData&, Emitter&);
bool EmitBSET_Static_Memory(InstructionData&, Emitter&);
bool EmitBSR(InstructionData&, Emitter&);
bool EmitBTST_Dynamic_Register(InstructionData&, Emitter&);
bool EmitBTST_Static_Register(InstructionData&, Emitter&);
bool EmitBTST_Dynamic_Memory(InstructionData&, Emitter&);
bool EmitBTST_Static_Memory(InstructionData&, Emitter&);

bool EmitCHK(InstructionData&, Emitter&);
bool EmitCLR(InstructionData&, Emitter&);
bool EmitCMPA(InstructionData&, Emitter&);
bool EmitCMPI(InstructionData&, Emitter&);
bool EmitCMPM(InstructionData&, Emitter&);
bool EmitCMP(InstructionData&, Emitter&);

bool EmitDBcc(InstructionData&, Emitter&);
bool EmitDIVS(InstructionData&, Emitter&);
bool EmitDIVU(InstructionData&, Emitter&);

bool EmitEORI(InstructionData&, Emitter&);
bool EmitEORI_CCR(InstructionData&, Emitter&);
bool EmitEORI_SR(InstructionData&, Emitter&);
bool EmitEOR(InstructionData&, Emitter&);
bool EmitEXG(InstructionData&, Emitter&);
bool EmitEXT(InstructionData&, Emitter&);

bool EmitILLEGAL(InstructionData&, Emitter&);

bool EmitJMP(InstructionData&, Emitter&);
bool EmitJSR(InstructionData&, Emitter&);

bool EmitLEA(InstructionData&, Emitter&);
bool EmitLINK(InstructionData&, Emitter&);
bool EmitLSL_Register(InstructionData&, Emitter&);
bool EmitLSL_Immediate(InstructionData&, Emitter&);
bool EmitLSL_Memory(InstructionData&, Emitter&);
bool EmitLSR_Register(InstructionData&, Emitter&);
bool EmitLSR_Immediate(InstructionData&, Emitter&);
bool EmitLSR_Memory(InstructionData&, Emitter&);

bool EmitMOVEA(InstructionData&, Emitter&);
bool EmitMOVE_CCR(InstructionData&, Emitter&);
bool EmitMOVEM_Register(InstructionData&, Emitter&);
bool EmitMOVEM_Memory(InstructionData&, Emitter&);
bool EmitMOVEP(InstructionData&, Emitter&);
bool EmitMOVEQ(InstructionData&, Emitter&);
bool EmitMOVE_SR_SR(InstructionData&, Emitter&);
bool EmitMOVE_SR_Memory(InstructionData&, Emitter&);
bool EmitMOVE_USP_USP(InstructionData&, Emitter&);
bool EmitMOVE_USP_Register(InstructionData&, Emitter&);
bool EmitMOVE(InstructionData&, Emitter&);
bool EmitMULS(InstructionData&, Emitter&);
bool EmitMULU(InstructionData&, Emitter&);

bool EmitNBCD(InstructionData&, Emitter&);
bool EmitNEGX(InstructionData&, Emitter&);
bool EmitNEG(InstructionData&, Emitter&);
bool EmitNOP(InstructionData&, Emitter&);
bool EmitNOT(InstructionData&, Emitter&);

bool EmitORI(InstructionData&, Emitter&);
bool EmitORI_CCR(InstructionData&, Emitter&);
bool EmitORI_SR(InstructionData&, Emitter&);
bool EmitOR(InstructionData&, Emitter&);

bool EmitPEA(InstructionData&, Emitter&);

bool EmitRESET(InstructionData&, Emitter&);
bool EmitROL_Register(InstructionData&, Emitter&);
bool EmitROL_Immediate(InstructionData&, Emitter&);
bool EmitROL_Memory(InstructionData&, Emitter&);
bool EmitROR_Register(InstructionData&, Emitter&);
bool EmitROR_Immediate(InstructionData&, Emitter&);
bool EmitROR_Memory(InstructionData&, Emitter&);
bool EmitROXL_Register(InstructionData&, Emitter&);
bool EmitROXL_Immediate(InstructionData&, Emitter&);
bool EmitROXL_Memory(InstructionData&, Emitter&);
bool EmitROXR_Register(InstructionData&, Emitter&);
bool EmitROXR_Immediate(InstructionData&, Emitter&);
bool EmitROXR_Memory(InstructionData&, Emitter&);
bool EmitRTE(InstructionData&, Emitter&);
bool EmitRTR(InstructionData&, Emitter&);
bool EmitRTS(InstructionData&, Emitter&);

bool EmitSBCD(InstructionData&, Emitter&);
bool EmitScc(InstructionData&, Emitter&);
bool EmitSTOP(InstructionData&, Emitter&);
bool EmitSUBA(InstructionData&, Emitter&);
bool EmitSUBI(InstructionData&, Emitter&);
bool EmitSUBQ(InstructionData&, Emitter&);
bool EmitSUBX(InstructionData&, Emitter&);
bool EmitSUB(InstructionData&, Emitter&);
bool EmitSWAP(InstructionData&, Emitter&);

bool EmitTAS(InstructionData&, Emitter&);
bool EmitTRAP(InstructionData&, Emitter&);
bool EmitTRAPV(InstructionData&, Emitter&);
bool EmitTST(InstructionData&, Emitter&);

bool EmitUNLK(InstructionData&, Emitter&);

}
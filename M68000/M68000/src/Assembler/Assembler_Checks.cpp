#include "M68000/AssemblerImpl.h"

using namespace rbrown::m68000;

namespace {

constexpr auto CheckMnemonic(const InstructionData& data, InstructionMnemonics mnemonic) {
    return data.GetMnemonic() == mnemonic;
}

constexpr auto CheckSizes(const InstructionData& data, OperandSizes size) {
    return data.GetSize() == size;
}

template<typename T, typename... Types>
constexpr auto CheckSizes(const InstructionData& data, T first, Types... rest) {
    return CheckSizes(data, first) || CheckSizes(data, rest...);
}

constexpr auto CheckSources(const InstructionData& data, AddressModes mode) {
    return data.GetSourceData().GetMode() == mode;
}

template<typename T, typename... Types>
constexpr auto CheckSources(const InstructionData& data, T first, Types... rest) {
    return CheckSources(data, first) || CheckSources(data, rest...);
}

constexpr auto CheckDestinations(const InstructionData& data, AddressModes mode) {
    return data.GetDestinationData().GetMode() == mode;
}

template<typename T, typename... Types>
constexpr auto CheckDestinations(const InstructionData& data, T first, Types... rest) {
    return CheckDestinations(data, first) || CheckDestinations(data, rest...);
}

constexpr auto CheckModesEqual(const InstructionData& data) {
    return CheckSources(data, data.GetDestinationData().GetMode());
}

constexpr auto CheckModesNotEqual(const InstructionData& data) {
    return !CheckModesEqual(data);
}

constexpr auto CheckSourceOrDestinationIs(const InstructionData& data, AddressModes mode) {
    return CheckSources(data, mode) || CheckDestinations(data, mode);
}

constexpr auto CheckSourcesForSize(const InstructionData& data) {
    if (CheckSources(data, AddressModes::ADDRESS_DIRECT)) {
        return CheckSizes(data, OperandSizes::WORD, OperandSizes::LONG);
    }
    return true;
}

constexpr auto CheckDestinationsForSize(const InstructionData& data) {
    if (CheckDestinations(data, AddressModes::ADDRESS_DIRECT)) {
        return CheckSizes(data, OperandSizes::WORD, OperandSizes::LONG);
    }
    return true;
}

constexpr auto CheckRangeInclusive(int64_t v, int64_t min, int64_t max) { return v >= min && v <= max; }

constexpr auto CheckRangeExclusive(int64_t v, int64_t min, int64_t max) { return v >= min && v < max; }

constexpr auto CheckImmediateRangeForSize(int64_t v, OperandSizes size) {
    switch (size) {
        case OperandSizes::BYTE: return CheckRangeInclusive(v, -0x80ll, 0xFFll);
        case OperandSizes::WORD: return CheckRangeInclusive(v, -0x8000ll, 0xFFFFll);
        case OperandSizes::LONG: return CheckRangeInclusive(v, -0x80000000ll, 0xFFFFFFFFll);
        default: return false;
    }
}

constexpr auto CheckSourceImmediateRange(const InstructionData& data, int64_t min, int64_t max) {
    return CheckRangeInclusive(data.GetSourceData().GetImmediate(), min, max);
}

constexpr auto CheckDestinationImmediateRange(const InstructionData& data, int64_t min, int64_t max) {
    return CheckRangeInclusive(data.GetDestinationData().GetImmediate(), min, max);
}

constexpr auto CheckSourceImmediateRangeForSize(const InstructionData& data) {
    if (CheckSources(data, AddressModes::IMMEDIATE)) {
        return CheckImmediateRangeForSize(data.GetSourceData().GetImmediate(), data.GetSize());
    }
    return true;
}

constexpr auto CheckDestinationImmediateRangeForSize(const InstructionData& data) {
    if (CheckSources(data, AddressModes::IMMEDIATE)) {
        return CheckImmediateRangeForSize(data.GetDestinationData().GetImmediate(), data.GetSize());
    }
    return true;
}

constexpr auto CheckBranchConditionCodes(const InstructionData& data, ConditionCodes code) {
    return data.GetBranchCondition().GetCode() == code;
}

template<typename T, typename... Types>
constexpr auto CheckBranchConditionCodes(const InstructionData& data, T first, Types... rest) {
    return CheckBranchConditionCodes(data, first) || CheckBranchConditionCodes(data, rest...);
}

constexpr auto CheckBranchDisplacement(const InstructionData& data) {
    const auto size = data.GetSize();
    const auto displacement = data.GetBranchCondition().GetDisplacement();
    switch (size) {
        case OperandSizes::BYTE: return CheckRangeExclusive(displacement, -0x80, 0x80);
        case OperandSizes::WORD: return CheckRangeExclusive(displacement, -0x8000, 0x8000);
        default: return false;
    }
}

constexpr auto CheckRegisterList(const InstructionData& data) {
    return data.GetRegisterList().GetRegisterList() != 0u;
}

}

namespace rbrown::m68000 {

bool CheckABCD(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ABCD) &&
           CheckSizes(data, OperandSizes::BYTE) &&
           CheckSources(data, AddressModes::DATA_DIRECT,
                        AddressModes::ADDRESS_DECREMENT) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT,
                             AddressModes::ADDRESS_DECREMENT) &&
           CheckModesEqual(data);
}

bool CheckADDA(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ADDA) &&
           CheckSizes(data, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::DATA_DIRECT,
                        AddressModes::ADDRESS_DIRECT,
                        AddressModes::ADDRESS_INDIRECT,
                        AddressModes::ADDRESS_INCREMENT,
                        AddressModes::ADDRESS_DECREMENT,
                        AddressModes::ADDRESS_DISPLACEMENT,
                        AddressModes::ADDRESS_INDEX,
                        AddressModes::ABSOLUTE_SHORT,
                        AddressModes::ABSOLUTE_LONG,
                        AddressModes::PROGRAM_COUNTER_DISPLACEMENT,
                        AddressModes::PROGRAM_COUNTER_INDEX,
                        AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRangeForSize(data) &&
           CheckDestinations(data, AddressModes::ADDRESS_DIRECT);
}

bool CheckADDI(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ADDI) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRangeForSize(data) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT,
                             AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckADDQ(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ADDQ) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRange(data, 1, 8) &&
           CheckDestinations(data, AddressModes::ADDRESS_DIRECT,
                             AddressModes::DATA_DIRECT,
                             AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG) &&
           CheckDestinationsForSize(data);
}

bool CheckADDX(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ADDX) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::DATA_DIRECT,
                        AddressModes::ADDRESS_DECREMENT) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT,
                             AddressModes::ADDRESS_DECREMENT) &&
           CheckModesEqual(data);
}

bool CheckADD(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ADD) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSourceOrDestinationIs(data, AddressModes::DATA_DIRECT) &&
           CheckSources(data, AddressModes::DATA_DIRECT,
                        AddressModes::ADDRESS_DIRECT,
                        AddressModes::ADDRESS_INDIRECT,
                        AddressModes::ADDRESS_INCREMENT,
                        AddressModes::ADDRESS_DECREMENT,
                        AddressModes::ADDRESS_DISPLACEMENT,
                        AddressModes::ADDRESS_INDEX,
                        AddressModes::ABSOLUTE_SHORT,
                        AddressModes::ABSOLUTE_LONG,
                        AddressModes::PROGRAM_COUNTER_DISPLACEMENT,
                        AddressModes::PROGRAM_COUNTER_INDEX,
                        AddressModes::IMMEDIATE) &&
           CheckSourcesForSize(data) &&
           CheckSourceImmediateRangeForSize(data) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT,
                             AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckANDI(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ANDI) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRangeForSize(data) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT,
                             AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckANDI_CCR(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ANDI_CCR) &&
           CheckSizes(data, OperandSizes::BYTE) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRangeForSize(data) &&
           CheckDestinations(data, AddressModes::CONDITION_CODE_REGISTER);
}

bool CheckANDI_SR(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ANDI_SR) &&
           CheckSizes(data, OperandSizes::WORD) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRangeForSize(data) &&
           CheckDestinations(data, AddressModes::STATUS_REGISTER);
}

bool CheckAND(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::AND) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSourceOrDestinationIs(data, AddressModes::DATA_DIRECT) &&
           CheckSources(data, AddressModes::DATA_DIRECT,
                        AddressModes::ADDRESS_INDIRECT,
                        AddressModes::ADDRESS_INCREMENT,
                        AddressModes::ADDRESS_DECREMENT,
                        AddressModes::ADDRESS_DISPLACEMENT,
                        AddressModes::ADDRESS_INDEX,
                        AddressModes::ABSOLUTE_SHORT,
                        AddressModes::ABSOLUTE_LONG,
                        AddressModes::PROGRAM_COUNTER_DISPLACEMENT,
                        AddressModes::PROGRAM_COUNTER_INDEX,
                        AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRangeForSize(data) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT,
                             AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckASL_Register(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ASL_REGISTER) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::DATA_DIRECT) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckASL_Immediate(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ASL_IMMEDIATE) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRange(data, 1, 8) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckASL_Memory(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ASL_MEMORY) &&
           CheckSizes(data, OperandSizes::WORD) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckASR_Register(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ASR_REGISTER) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::DATA_DIRECT) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckASR_Immediate(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ASR_IMMEDIATE) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRange(data, 1, 8) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckASR_Memory(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ASR_MEMORY) &&
           CheckSizes(data, OperandSizes::WORD) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckBcc(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::Bcc) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::UNKNOWN) &&
           CheckBranchConditionCodes(data, ConditionCodes::HI, ConditionCodes::LS, ConditionCodes::CC,
                                     ConditionCodes::CS, ConditionCodes::NE, ConditionCodes::EQ, ConditionCodes::VC,
                                     ConditionCodes::VS, ConditionCodes::PL, ConditionCodes::MI, ConditionCodes::GE,
                                     ConditionCodes::LT, ConditionCodes::GT, ConditionCodes::LE) &&
           CheckBranchDisplacement(data);
}

bool CheckBCHG_Dynamic_Register(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::BCHG_DYNAMIC_REGISTER) &&
           CheckSizes(data, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::DATA_DIRECT) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckBCHG_Static_Register(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::BCHG_STATIC_REGISTER) &&
           CheckSizes(data, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRange(data, 0, 255) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckBCHG_Dynamic_Memory(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::BCHG_DYNAMIC_MEMORY) &&
           CheckSizes(data, OperandSizes::BYTE) &&
           CheckSources(data, AddressModes::DATA_DIRECT) &&
           CheckDestinations(data, AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckBCHG_Static_Memory(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::BCHG_STATIC_MEMORY) &&
           CheckSizes(data, OperandSizes::BYTE) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRange(data, 0, 255) &&
           CheckDestinations(data, AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckBCLR_Dynamic_Register(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::BCLR_DYNAMIC_REGISTER) &&
           CheckSizes(data, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::DATA_DIRECT) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckBCLR_Static_Register(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::BCLR_STATIC_REGISTER) &&
           CheckSizes(data, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRange(data, 0, 255) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckBCLR_Dynamic_Memory(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::BCLR_DYNAMIC_MEMORY) &&
           CheckSizes(data, OperandSizes::BYTE) &&
           CheckSources(data, AddressModes::DATA_DIRECT) &&
           CheckDestinations(data, AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckBCLR_Static_Memory(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::BCLR_STATIC_MEMORY) &&
           CheckSizes(data, OperandSizes::BYTE) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRange(data, 0, 255) &&
           CheckDestinations(data, AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckBRA(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::BRA) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::UNKNOWN) &&
           CheckBranchConditionCodes(data, ConditionCodes::TRUE) &&
           CheckBranchDisplacement(data);
}

bool CheckBSET_Dynamic_Register(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::BSET_DYNAMIC_REGISTER) &&
           CheckSizes(data, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::DATA_DIRECT) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckBSET_Static_Register(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::BSET_STATIC_REGISTER) &&
           CheckSizes(data, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRange(data, 0, 255) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckBSET_Dynamic_Memory(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::BSET_DYNAMIC_MEMORY) &&
           CheckSizes(data, OperandSizes::BYTE) &&
           CheckSources(data, AddressModes::DATA_DIRECT) &&
           CheckDestinations(data, AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckBSET_Static_Memory(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::BSET_STATIC_MEMORY) &&
           CheckSizes(data, OperandSizes::BYTE) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRange(data, 0, 255) &&
           CheckDestinations(data, AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckBSR(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::BSR) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::UNKNOWN) &&
           CheckBranchConditionCodes(data, ConditionCodes::FALSE) &&
           CheckBranchDisplacement(data);
}

bool CheckBTST_Dynamic_Register(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::BTST_DYNAMIC_REGISTER) &&
           CheckSizes(data, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::DATA_DIRECT) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckBTST_Static_Register(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::BTST_STATIC_REGISTER) &&
           CheckSizes(data, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRange(data, 0, 255) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckBTST_Dynamic_Memory(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::BTST_DYNAMIC_MEMORY) &&
           CheckSizes(data, OperandSizes::BYTE) &&
           CheckSources(data, AddressModes::DATA_DIRECT) &&
           CheckDestinations(data, AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG,
                             AddressModes::PROGRAM_COUNTER_DISPLACEMENT,
                             AddressModes::PROGRAM_COUNTER_INDEX,
                             AddressModes::IMMEDIATE) &&
           CheckDestinationImmediateRangeForSize(data);
}

bool CheckBTST_Static_Memory(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::BTST_STATIC_MEMORY) &&
           CheckSizes(data, OperandSizes::BYTE) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRange(data, 0, 255) &&
           CheckDestinations(data, AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG,
                             AddressModes::PROGRAM_COUNTER_DISPLACEMENT,
                             AddressModes::PROGRAM_COUNTER_INDEX);
}

bool CheckCHK(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::CHK) &&
           CheckSizes(data, OperandSizes::WORD) &&
           CheckSources(data, AddressModes::DATA_DIRECT,
                        AddressModes::ADDRESS_INDIRECT,
                        AddressModes::ADDRESS_INCREMENT,
                        AddressModes::ADDRESS_DECREMENT,
                        AddressModes::ADDRESS_DISPLACEMENT,
                        AddressModes::ADDRESS_INDEX,
                        AddressModes::ABSOLUTE_SHORT,
                        AddressModes::ABSOLUTE_LONG,
                        AddressModes::PROGRAM_COUNTER_DISPLACEMENT,
                        AddressModes::PROGRAM_COUNTER_INDEX,
                        AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRangeForSize(data) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckCLR(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::CLR) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT,
                             AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckCMPA(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::CMPA) &&
           CheckSizes(data, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::DATA_DIRECT,
                        AddressModes::ADDRESS_DIRECT,
                        AddressModes::ADDRESS_INDIRECT,
                        AddressModes::ADDRESS_INCREMENT,
                        AddressModes::ADDRESS_DECREMENT,
                        AddressModes::ADDRESS_DISPLACEMENT,
                        AddressModes::ADDRESS_INDEX,
                        AddressModes::ABSOLUTE_SHORT,
                        AddressModes::ABSOLUTE_LONG,
                        AddressModes::PROGRAM_COUNTER_DISPLACEMENT,
                        AddressModes::PROGRAM_COUNTER_INDEX,
                        AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRangeForSize(data) &&
           CheckDestinations(data, AddressModes::ADDRESS_DIRECT);
}

bool CheckCMPI(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::CMPI) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRangeForSize(data) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT,
                             AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckCMPM(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::CMPM) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::ADDRESS_INCREMENT) &&
           CheckDestinations(data, AddressModes::ADDRESS_INCREMENT);
}

bool CheckCMP(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::CMP) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::DATA_DIRECT,
                        AddressModes::ADDRESS_DIRECT,
                        AddressModes::ADDRESS_INDIRECT,
                        AddressModes::ADDRESS_INCREMENT,
                        AddressModes::ADDRESS_DECREMENT,
                        AddressModes::ADDRESS_DISPLACEMENT,
                        AddressModes::ADDRESS_INDEX,
                        AddressModes::ABSOLUTE_SHORT,
                        AddressModes::ABSOLUTE_LONG,
                        AddressModes::PROGRAM_COUNTER_DISPLACEMENT,
                        AddressModes::PROGRAM_COUNTER_INDEX,
                        AddressModes::IMMEDIATE) &&
           CheckSourcesForSize(data) &&
           CheckSourceImmediateRangeForSize(data) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckDBcc(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::DBcc) &&
           CheckSizes(data, OperandSizes::WORD) &&
           CheckSources(data, AddressModes::DATA_DIRECT) &&
           CheckDestinations(data, AddressModes::UNKNOWN) &&
           CheckBranchConditionCodes(data, ConditionCodes::TRUE, ConditionCodes::FALSE, ConditionCodes::HI,
                                     ConditionCodes::LS, ConditionCodes::CC, ConditionCodes::CS, ConditionCodes::NE,
                                     ConditionCodes::EQ, ConditionCodes::VC, ConditionCodes::VS, ConditionCodes::PL,
                                     ConditionCodes::MI, ConditionCodes::GE, ConditionCodes::LT, ConditionCodes::GT,
                                     ConditionCodes::LE) &&
           CheckBranchDisplacement(data);
}

bool CheckDIVS(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::DIVS) &&
           CheckSizes(data, OperandSizes::WORD) &&
           CheckSources(data, AddressModes::DATA_DIRECT,
                        AddressModes::ADDRESS_INDIRECT,
                        AddressModes::ADDRESS_INCREMENT,
                        AddressModes::ADDRESS_DECREMENT,
                        AddressModes::ADDRESS_DISPLACEMENT,
                        AddressModes::ADDRESS_INDEX,
                        AddressModes::ABSOLUTE_SHORT,
                        AddressModes::ABSOLUTE_LONG,
                        AddressModes::PROGRAM_COUNTER_DISPLACEMENT,
                        AddressModes::PROGRAM_COUNTER_INDEX,
                        AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRangeForSize(data) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckDIVU(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::DIVU) &&
           CheckSizes(data, OperandSizes::WORD) &&
           CheckSources(data, AddressModes::DATA_DIRECT,
                        AddressModes::ADDRESS_INDIRECT,
                        AddressModes::ADDRESS_INCREMENT,
                        AddressModes::ADDRESS_DECREMENT,
                        AddressModes::ADDRESS_DISPLACEMENT,
                        AddressModes::ADDRESS_INDEX,
                        AddressModes::ABSOLUTE_SHORT,
                        AddressModes::ABSOLUTE_LONG,
                        AddressModes::PROGRAM_COUNTER_DISPLACEMENT,
                        AddressModes::PROGRAM_COUNTER_INDEX,
                        AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRangeForSize(data) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckEORI(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::EORI) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRangeForSize(data) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT,
                             AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckEORI_CCR(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::EORI_CCR) &&
           CheckSizes(data, OperandSizes::BYTE) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRangeForSize(data) &&
           CheckDestinations(data, AddressModes::CONDITION_CODE_REGISTER);
}

bool CheckEORI_SR(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::EORI_SR) &&
           CheckSizes(data, OperandSizes::WORD) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRangeForSize(data) &&
           CheckDestinations(data, AddressModes::STATUS_REGISTER);
}

bool CheckEOR(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::EOR) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::DATA_DIRECT) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT,
                             AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckEXG(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::EXG) &&
           CheckSizes(data, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::DATA_DIRECT,
                        AddressModes::ADDRESS_DIRECT) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT,
                             AddressModes::ADDRESS_DIRECT);
}

bool CheckEXT(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::EXT) &&
           CheckSizes(data, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckILLEGAL(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ILLEGAL) &&
           CheckSizes(data, OperandSizes::UNSIZED) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::UNKNOWN);
}

bool CheckJMP(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::JMP) &&
           CheckSizes(data, OperandSizes::UNSIZED) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::PROGRAM_COUNTER_DISPLACEMENT,
                             AddressModes::PROGRAM_COUNTER_INDEX,
                             AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckJSR(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::JSR) &&
           CheckSizes(data, OperandSizes::UNSIZED) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::PROGRAM_COUNTER_DISPLACEMENT,
                             AddressModes::PROGRAM_COUNTER_INDEX,
                             AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckLEA(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::LEA) &&
           CheckSizes(data, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::PROGRAM_COUNTER_DISPLACEMENT,
                        AddressModes::PROGRAM_COUNTER_INDEX,
                        AddressModes::ADDRESS_INDIRECT,
                        AddressModes::ADDRESS_DISPLACEMENT,
                        AddressModes::ADDRESS_INDEX,
                        AddressModes::ABSOLUTE_SHORT,
                        AddressModes::ABSOLUTE_LONG) &&
           CheckDestinations(data, AddressModes::ADDRESS_DIRECT);
}

bool CheckLINK(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::LINK) &&
           CheckSizes(data, OperandSizes::WORD) &&
           CheckSources(data, AddressModes::ADDRESS_DIRECT) &&
           CheckDestinations(data, AddressModes::IMMEDIATE) &&
           CheckDestinationImmediateRangeForSize(data);
}

bool CheckLSL_Register(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::LSL_REGISTER) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::DATA_DIRECT) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckLSL_Immediate(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::LSL_IMMEDIATE) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRange(data, 1, 8) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckLSL_Memory(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::LSL_MEMORY) &&
           CheckSizes(data, OperandSizes::WORD) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckLSR_Register(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::LSR_REGISTER) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::DATA_DIRECT) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckLSR_Immediate(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::LSR_IMMEDIATE) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRange(data, 1, 8) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckLSR_Memory(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::LSR_MEMORY) &&
           CheckSizes(data, OperandSizes::WORD) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckMOVEA(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::MOVEA) &&
           CheckSizes(data, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::DATA_DIRECT,
                        AddressModes::ADDRESS_DIRECT,
                        AddressModes::ADDRESS_INDIRECT,
                        AddressModes::ADDRESS_INCREMENT,
                        AddressModes::ADDRESS_DECREMENT,
                        AddressModes::ADDRESS_DISPLACEMENT,
                        AddressModes::ADDRESS_INDEX,
                        AddressModes::ABSOLUTE_SHORT,
                        AddressModes::ABSOLUTE_LONG,
                        AddressModes::PROGRAM_COUNTER_DISPLACEMENT,
                        AddressModes::PROGRAM_COUNTER_INDEX,
                        AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRangeForSize(data) &&
           CheckDestinations(data, AddressModes::ADDRESS_DIRECT);
}

bool CheckMOVE_CCR(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::MOVE_CCR) &&
           CheckSizes(data, OperandSizes::WORD) &&
           CheckSources(data, AddressModes::DATA_DIRECT,
                        AddressModes::ADDRESS_INDIRECT,
                        AddressModes::ADDRESS_INCREMENT,
                        AddressModes::ADDRESS_DECREMENT,
                        AddressModes::ADDRESS_DISPLACEMENT,
                        AddressModes::ADDRESS_INDEX,
                        AddressModes::ABSOLUTE_SHORT,
                        AddressModes::ABSOLUTE_LONG,
                        AddressModes::PROGRAM_COUNTER_DISPLACEMENT,
                        AddressModes::PROGRAM_COUNTER_INDEX,
                        AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRangeForSize(data) &&
           CheckDestinations(data, AddressModes::CONDITION_CODE_REGISTER);
}

bool CheckMOVEM_Register(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::MOVEM_REGISTER) &&
           CheckSizes(data, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::ADDRESS_INCREMENT,
                        AddressModes::PROGRAM_COUNTER_DISPLACEMENT,
                        AddressModes::PROGRAM_COUNTER_INDEX,
                        AddressModes::ADDRESS_INDIRECT,
                        AddressModes::ADDRESS_DISPLACEMENT,
                        AddressModes::ADDRESS_INDEX,
                        AddressModes::ABSOLUTE_SHORT,
                        AddressModes::ABSOLUTE_LONG) &&
           CheckDestinations(data, AddressModes::UNKNOWN) &&
           CheckRegisterList(data);
}

bool CheckMOVEM_Memory(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::MOVEM_MEMORY) &&
           CheckSizes(data, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG) &&
           CheckRegisterList(data);
}

bool CheckMOVEP(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::MOVEP) &&
           CheckSizes(data, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::DATA_DIRECT,
                        AddressModes::ADDRESS_DISPLACEMENT) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT,
                             AddressModes::ADDRESS_DISPLACEMENT) &&
           CheckModesNotEqual(data);
}

bool CheckMOVEQ(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::MOVEQ) &&
           CheckSizes(data, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRange(data, -0x80, 0xFF) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckMOVE_SR_SR(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::MOVE_SR_SR) &&
           CheckSizes(data, OperandSizes::WORD) &&
           CheckSources(data, AddressModes::DATA_DIRECT,
                        AddressModes::ADDRESS_INDIRECT,
                        AddressModes::ADDRESS_INCREMENT,
                        AddressModes::ADDRESS_DECREMENT,
                        AddressModes::ADDRESS_DISPLACEMENT,
                        AddressModes::ADDRESS_INDEX,
                        AddressModes::ABSOLUTE_SHORT,
                        AddressModes::ABSOLUTE_LONG,
                        AddressModes::PROGRAM_COUNTER_DISPLACEMENT,
                        AddressModes::PROGRAM_COUNTER_INDEX,
                        AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRangeForSize(data) &&
           CheckDestinations(data, AddressModes::STATUS_REGISTER);
}

bool CheckMOVE_SR_Memory(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::MOVE_SR_MEMORY) &&
           CheckSizes(data, OperandSizes::WORD) &&
           CheckSources(data, AddressModes::STATUS_REGISTER) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT,
                             AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckMOVE_USP_USP(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::MOVE_USP_USP) &&
           CheckSizes(data, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::ADDRESS_DIRECT) &&
           CheckDestinations(data, AddressModes::USER_STACK_POINTER);
}

bool CheckMOVE_USP_Register(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::MOVE_USP_REGISTER) &&
           CheckSizes(data, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::USER_STACK_POINTER) &&
           CheckDestinations(data, AddressModes::ADDRESS_DIRECT);
}

bool CheckMOVE(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::MOVE) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::DATA_DIRECT,
                        AddressModes::ADDRESS_DIRECT,
                        AddressModes::ADDRESS_INDIRECT,
                        AddressModes::ADDRESS_INCREMENT,
                        AddressModes::ADDRESS_DECREMENT,
                        AddressModes::ADDRESS_DISPLACEMENT,
                        AddressModes::ADDRESS_INDEX,
                        AddressModes::ABSOLUTE_SHORT,
                        AddressModes::ABSOLUTE_LONG,
                        AddressModes::PROGRAM_COUNTER_DISPLACEMENT,
                        AddressModes::PROGRAM_COUNTER_INDEX,
                        AddressModes::IMMEDIATE) &&
           CheckSourcesForSize(data) &&
           CheckSourceImmediateRangeForSize(data) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT,
                             AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckMULS(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::MULS) &&
           CheckSizes(data, OperandSizes::WORD) &&
           CheckSources(data, AddressModes::DATA_DIRECT,
                        AddressModes::ADDRESS_INDIRECT,
                        AddressModes::ADDRESS_INCREMENT,
                        AddressModes::ADDRESS_DECREMENT,
                        AddressModes::ADDRESS_DISPLACEMENT,
                        AddressModes::ADDRESS_INDEX,
                        AddressModes::ABSOLUTE_SHORT,
                        AddressModes::ABSOLUTE_LONG,
                        AddressModes::PROGRAM_COUNTER_DISPLACEMENT,
                        AddressModes::PROGRAM_COUNTER_INDEX,
                        AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRangeForSize(data) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckMULU(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::MULU) &&
           CheckSizes(data, OperandSizes::WORD) &&
           CheckSources(data, AddressModes::DATA_DIRECT,
                        AddressModes::ADDRESS_INDIRECT,
                        AddressModes::ADDRESS_INCREMENT,
                        AddressModes::ADDRESS_DECREMENT,
                        AddressModes::ADDRESS_DISPLACEMENT,
                        AddressModes::ADDRESS_INDEX,
                        AddressModes::ABSOLUTE_SHORT,
                        AddressModes::ABSOLUTE_LONG,
                        AddressModes::PROGRAM_COUNTER_DISPLACEMENT,
                        AddressModes::PROGRAM_COUNTER_INDEX,
                        AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRangeForSize(data) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckNBCD(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::NBCD) &&
           CheckSizes(data, OperandSizes::BYTE) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT,
                             AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckNEGX(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::NEGX) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT,
                             AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckNEG(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::NEG) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT,
                             AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckNOP(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::NOP) &&
           CheckSizes(data, OperandSizes::UNSIZED) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::UNKNOWN);
}

bool CheckNOT(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::NOT) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT,
                             AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckORI(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ORI) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRangeForSize(data) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT,
                             AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckORI_CCR(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ORI_CCR) &&
           CheckSizes(data, OperandSizes::BYTE) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRangeForSize(data) &&
           CheckDestinations(data, AddressModes::CONDITION_CODE_REGISTER);
}

bool CheckORI_SR(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ORI_SR) &&
           CheckSizes(data, OperandSizes::WORD) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRangeForSize(data) &&
           CheckDestinations(data, AddressModes::STATUS_REGISTER);
}

bool CheckOR(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::OR) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSourceOrDestinationIs(data, AddressModes::DATA_DIRECT) &&
           CheckSources(data, AddressModes::DATA_DIRECT,
                        AddressModes::ADDRESS_INDIRECT,
                        AddressModes::ADDRESS_INCREMENT,
                        AddressModes::ADDRESS_DECREMENT,
                        AddressModes::ADDRESS_DISPLACEMENT,
                        AddressModes::ADDRESS_INDEX,
                        AddressModes::ABSOLUTE_SHORT,
                        AddressModes::ABSOLUTE_LONG,
                        AddressModes::PROGRAM_COUNTER_DISPLACEMENT,
                        AddressModes::PROGRAM_COUNTER_INDEX,
                        AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRangeForSize(data) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT,
                             AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckPEA(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::PEA) &&
           CheckSizes(data, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::PROGRAM_COUNTER_DISPLACEMENT,
                             AddressModes::PROGRAM_COUNTER_INDEX,
                             AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckRESET(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::RESET) &&
           CheckSizes(data, OperandSizes::UNSIZED) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::UNKNOWN);
}

bool CheckROL_Register(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ROL_REGISTER) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::DATA_DIRECT) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckROL_Immediate(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ROL_IMMEDIATE) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRange(data, 1, 8) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckROL_Memory(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ROL_MEMORY) &&
           CheckSizes(data, OperandSizes::WORD) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckROR_Register(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ROR_REGISTER) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::DATA_DIRECT) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckROR_Immediate(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ROR_IMMEDIATE) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRange(data, 1, 8) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckROR_Memory(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ROR_MEMORY) &&
           CheckSizes(data, OperandSizes::WORD) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckROXL_Register(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ROXL_REGISTER) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::DATA_DIRECT) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckROXL_Immediate(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ROXL_IMMEDIATE) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRange(data, 1, 8) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckROXL_Memory(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ROXL_MEMORY) &&
           CheckSizes(data, OperandSizes::WORD) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckROXR_Register(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ROXR_REGISTER) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::DATA_DIRECT) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckROXR_Immediate(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ROXR_IMMEDIATE) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRange(data, 1, 8) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckROXR_Memory(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::ROXR_MEMORY) &&
           CheckSizes(data, OperandSizes::WORD) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckRTE(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::RTE) &&
           CheckSizes(data, OperandSizes::UNSIZED) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::UNKNOWN);
}

bool CheckRTR(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::RTR) &&
           CheckSizes(data, OperandSizes::UNSIZED) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::UNKNOWN);
}

bool CheckRTS(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::RTS) &&
           CheckSizes(data, OperandSizes::UNSIZED) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::UNKNOWN);
}

bool CheckSBCD(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::SBCD) &&
           CheckSizes(data, OperandSizes::BYTE) &&
           CheckSources(data, AddressModes::DATA_DIRECT,
                        AddressModes::ADDRESS_DECREMENT) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT,
                             AddressModes::ADDRESS_DECREMENT) &&
           CheckModesEqual(data);
}

bool CheckScc(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::Scc) &&
           CheckSizes(data, OperandSizes::BYTE) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT,
                             AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG) &&
           CheckBranchConditionCodes(data, ConditionCodes::TRUE, ConditionCodes::FALSE, ConditionCodes::HI,
                                     ConditionCodes::LS, ConditionCodes::CC, ConditionCodes::CS, ConditionCodes::NE,
                                     ConditionCodes::EQ, ConditionCodes::VC, ConditionCodes::VS, ConditionCodes::PL,
                                     ConditionCodes::MI, ConditionCodes::GE, ConditionCodes::LT, ConditionCodes::GT,
                                     ConditionCodes::LE);
}

bool CheckSTOP(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::STOP) &&
           CheckSizes(data, OperandSizes::UNSIZED) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::IMMEDIATE) &&
           CheckDestinationImmediateRange(data, 0, 0xFFFF);
}

bool CheckSUBA(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::SUBA) &&
           CheckSizes(data, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::DATA_DIRECT,
                        AddressModes::ADDRESS_DIRECT,
                        AddressModes::ADDRESS_INDIRECT,
                        AddressModes::ADDRESS_INCREMENT,
                        AddressModes::ADDRESS_DECREMENT,
                        AddressModes::ADDRESS_DISPLACEMENT,
                        AddressModes::ADDRESS_INDEX,
                        AddressModes::ABSOLUTE_SHORT,
                        AddressModes::ABSOLUTE_LONG,
                        AddressModes::PROGRAM_COUNTER_DISPLACEMENT,
                        AddressModes::PROGRAM_COUNTER_INDEX,
                        AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRangeForSize(data) &&
           CheckDestinations(data, AddressModes::ADDRESS_DIRECT);
}

bool CheckSUBI(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::SUBI) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRangeForSize(data) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT,
                             AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckSUBQ(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::SUBQ) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::IMMEDIATE) &&
           CheckSourceImmediateRange(data, 1, 8) &&
           CheckDestinations(data, AddressModes::ADDRESS_DIRECT,
                             AddressModes::DATA_DIRECT,
                             AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG) &&
           CheckDestinationsForSize(data);
}

bool CheckSUBX(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::SUBX) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::DATA_DIRECT,
                        AddressModes::ADDRESS_DECREMENT) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT,
                             AddressModes::ADDRESS_DECREMENT) &&
           CheckModesEqual(data);
}

bool CheckSUB(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::SUB) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSourceOrDestinationIs(data, AddressModes::DATA_DIRECT) &&
           CheckSources(data, AddressModes::DATA_DIRECT,
                        AddressModes::ADDRESS_DIRECT,
                        AddressModes::ADDRESS_INDIRECT,
                        AddressModes::ADDRESS_INCREMENT,
                        AddressModes::ADDRESS_DECREMENT,
                        AddressModes::ADDRESS_DISPLACEMENT,
                        AddressModes::ADDRESS_INDEX,
                        AddressModes::ABSOLUTE_SHORT,
                        AddressModes::ABSOLUTE_LONG,
                        AddressModes::PROGRAM_COUNTER_DISPLACEMENT,
                        AddressModes::PROGRAM_COUNTER_INDEX,
                        AddressModes::IMMEDIATE) &&
           CheckSourcesForSize(data) &&
           CheckSourceImmediateRangeForSize(data) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT,
                             AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckSWAP(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::SWAP) &&
           CheckSizes(data, OperandSizes::WORD) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT);
}

bool CheckTAS(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::TAS) &&
           CheckSizes(data, OperandSizes::BYTE) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT,
                             AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckTRAPV(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::TRAPV) &&
           CheckSizes(data, OperandSizes::UNSIZED) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::UNKNOWN);
}

bool CheckTRAP(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::TRAP) &&
           CheckSizes(data, OperandSizes::UNSIZED) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::IMMEDIATE) &&
           CheckDestinationImmediateRange(data, 0, 15);
}

bool CheckTST(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::TST) &&
           CheckSizes(data, OperandSizes::BYTE, OperandSizes::WORD, OperandSizes::LONG) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::DATA_DIRECT,
                             AddressModes::ADDRESS_INDIRECT,
                             AddressModes::ADDRESS_INCREMENT,
                             AddressModes::ADDRESS_DECREMENT,
                             AddressModes::ADDRESS_DISPLACEMENT,
                             AddressModes::ADDRESS_INDEX,
                             AddressModes::ABSOLUTE_SHORT,
                             AddressModes::ABSOLUTE_LONG);
}

bool CheckUNLK(const InstructionData& data) {
    return CheckMnemonic(data, InstructionMnemonics::UNLK) &&
           CheckSizes(data, OperandSizes::UNSIZED) &&
           CheckSources(data, AddressModes::UNKNOWN) &&
           CheckDestinations(data, AddressModes::ADDRESS_DIRECT);
}

}
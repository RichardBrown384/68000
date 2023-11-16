#include <cstdint>

#include "M68000/AssemblerImpl.h"

namespace rbrown::m68000 {

namespace {

constexpr auto SIZE_BYTE = 0u;
constexpr auto SIZE_WORD = 1u;
constexpr auto SIZE_LONG = 2u;

constexpr auto CODE_TRUE = 0u;
constexpr auto CODE_FALSE = 1u;
constexpr auto CODE_HI = 2u;
constexpr auto CODE_LS = 3u;
constexpr auto CODE_CC = 4u;
constexpr auto CODE_CS = 5u;
constexpr auto CODE_NE = 6u;
constexpr auto CODE_EQ = 7u;
constexpr auto CODE_VC = 8u;
constexpr auto CODE_VS = 9u;
constexpr auto CODE_PL = 10u;
constexpr auto CODE_MI = 11u;
constexpr auto CODE_GE = 12u;
constexpr auto CODE_LT = 13u;
constexpr auto CODE_GT = 14u;
constexpr auto CODE_LE = 15u;

constexpr auto MODE_DATA_DIRECT = 0u;
constexpr auto MODE_ADDRESS_DIRECT = 1u;
constexpr auto MODE_ADDRESS_INDIRECT = 2u;
constexpr auto MODE_ADDRESS_INCREMENT = 3u;
constexpr auto MODE_ADDRESS_DECREMENT = 4u;
constexpr auto MODE_ADDRESS_DISPLACEMENT = 5u;
constexpr auto MODE_ADDRESS_INDEX = 6u;
constexpr auto MODE_OTHER = 7u;
constexpr auto MODE_SHORT = 0u;
constexpr auto MODE_LONG = 1u;
constexpr auto MODE_PC_DISPLACEMENT = 2u;
constexpr auto MODE_PC_INDEX = 3u;
constexpr auto MODE_IMMEDIATE = 4u;

constexpr auto INDEX_DATA = 0u;
constexpr auto INDEX_ADDRESS = 1u;

constexpr auto INDEX_WORD = 0u;
constexpr auto INDEX_LONG = 1u;

constexpr auto MapOperandSize(const OperandSizes& size) {
    switch (size) {
        case OperandSizes::BYTE: return SIZE_BYTE;
        case OperandSizes::WORD: return SIZE_WORD;
        case OperandSizes::LONG: return SIZE_LONG;
        default:return 0u;
    }
}

constexpr auto MapConditionCode(const ConditionCodes& code) {
    switch (code) {
        case ConditionCodes::TRUE: return CODE_TRUE;
        case ConditionCodes::FALSE: return CODE_FALSE;
        case ConditionCodes::HI: return CODE_HI;
        case ConditionCodes::LS: return CODE_LS;
        case ConditionCodes::CC: return CODE_CC;
        case ConditionCodes::CS: return CODE_CS;
        case ConditionCodes::NE: return CODE_NE;
        case ConditionCodes::EQ: return CODE_EQ;
        case ConditionCodes::VC: return CODE_VC;
        case ConditionCodes::VS: return CODE_VS;
        case ConditionCodes::PL: return CODE_PL;
        case ConditionCodes::MI: return CODE_MI;
        case ConditionCodes::GE: return CODE_GE;
        case ConditionCodes::LT: return CODE_LT;
        case ConditionCodes::GT: return CODE_GT;
        case ConditionCodes::LE: return CODE_LE;
        default:return 0u;
    }
}

constexpr auto MapAddressModeAndRegister(const AddressModes mode, int64_t r) -> std::tuple<uint32_t, int64_t> {
    switch (mode) {
        case AddressModes::DATA_DIRECT: return { MODE_DATA_DIRECT, r };
        case AddressModes::ADDRESS_DIRECT: return { MODE_ADDRESS_DIRECT, r };
        case AddressModes::ADDRESS_INDIRECT: return { MODE_ADDRESS_INDIRECT, r };
        case AddressModes::ADDRESS_INCREMENT: return { MODE_ADDRESS_INCREMENT, r };
        case AddressModes::ADDRESS_DECREMENT: return { MODE_ADDRESS_DECREMENT, r };
        case AddressModes::ADDRESS_DISPLACEMENT: return { MODE_ADDRESS_DISPLACEMENT, r };
        case AddressModes::ADDRESS_INDEX: return { MODE_ADDRESS_INDEX, r };
        case AddressModes::ABSOLUTE_SHORT: return { MODE_OTHER, MODE_SHORT };
        case AddressModes::ABSOLUTE_LONG: return { MODE_OTHER, MODE_LONG };
        case AddressModes::IMMEDIATE: return { MODE_OTHER, MODE_IMMEDIATE };
        case AddressModes::PROGRAM_COUNTER_DISPLACEMENT: return { MODE_OTHER, MODE_PC_DISPLACEMENT };
        case AddressModes::PROGRAM_COUNTER_INDEX: return { MODE_OTHER, MODE_PC_INDEX };
        default: return { 0, 0 };
    }
}

constexpr auto MapIndexRegisterSize(const IndexRegisterSizes& size) {
    switch (size) {
        case IndexRegisterSizes::WORD: return INDEX_WORD;
        case IndexRegisterSizes::LONG: return INDEX_LONG;
        default:return 0u;
    }
}

constexpr auto MapIndexRegisterType(const IndexRegisterTypes& type) {
    switch (type) {
        case IndexRegisterTypes::DATA: return INDEX_DATA;
        case IndexRegisterTypes::ADDRESS: return INDEX_ADDRESS;
        default:return 0u;
    }
}

auto EmitWord(Emitter& emitter, uint16_t w) {
    emitter(w);
}

auto EmitLong(Emitter& emitter, uint32_t l) {
    emitter(l >> 16u);
    emitter(l);
}

constexpr auto EncodeInstruction(uint32_t oc, uint32_t rx, uint32_t mx, uint32_t my, uint32_t ry) {
    return ((oc & 0xFu) << 12u)
           + ((rx & 0x7u) << 9u)
           + ((mx & 0x7u) << 6u)
           + ((my & 0x7u) << 3u)
           + (ry & 0x7u);
}

auto EmitInstructionWord(Emitter& emitter, uint32_t oc, uint32_t rx, uint32_t mx, uint32_t my, uint32_t ry) {
    EmitWord(emitter, EncodeInstruction(oc, rx, mx, my, ry));
}

constexpr auto EncodeBriefExtensionWord(uint32_t index, uint32_t wl, uint32_t r, uint32_t da) {
    return ((da & 0x1u) << 15u)
           + ((r & 0x7u) << 12u)
           + ((wl & 0x1u) << 11u)
           + (index & 0xFFu);
}

auto EmitBriefExtensionWord(
    Emitter& emitter,
    uint32_t index,
    uint32_t wl,
    uint32_t r,
    uint32_t da) {
    EmitWord(emitter, EncodeBriefExtensionWord(index, wl, r, da));
}

auto EmitDisplacement(Emitter& emitter, const AddressModeData& mode) {
    EmitWord(emitter, mode.GetDisplacement());
}

auto EmitIndex(Emitter& emitter, const AddressModeData& mode) {
    const auto index = mode.GetIndex();
    const auto wl = MapIndexRegisterSize(mode.GetIndexRegisterSize());
    const auto r = mode.GetIndexRegisterNumber();
    const auto da = MapIndexRegisterType(mode.GetIndexRegisterType());
    return EmitBriefExtensionWord(emitter, index, wl, r, da);
}

auto EmitShortAddress(Emitter& emitter, const AddressModeData& mode) {
    EmitWord(emitter, mode.GetAbsoluteAddress());
}

auto EmitLongAddress(Emitter& emitter, const AddressModeData& mode) {
    EmitLong(emitter, mode.GetAbsoluteAddress());
}

auto EmitImmediate(Emitter& emitter, const InstructionData& data, const AddressModeData& mode) {
    const auto immediate = mode.GetImmediate();
    switch (data.GetSize()) {
        case OperandSizes::BYTE: return EmitWord(emitter, immediate & 0xFFu);
        case OperandSizes::WORD: return EmitWord(emitter, immediate);
        case OperandSizes::LONG: return EmitLong(emitter, immediate);
        default:return;
    }
}

auto EmitExtensionWords(Emitter& emitter, const InstructionData& data, const AddressModeData& mode) {
    switch (mode.GetMode()) {
        case AddressModes::ADDRESS_DISPLACEMENT: return EmitDisplacement(emitter, mode);
        case AddressModes::ADDRESS_INDEX: return EmitIndex(emitter, mode);
        case AddressModes::ABSOLUTE_SHORT: return EmitShortAddress(emitter, mode);
        case AddressModes::ABSOLUTE_LONG: return EmitLongAddress(emitter, mode);
        case AddressModes::PROGRAM_COUNTER_DISPLACEMENT: return EmitDisplacement(emitter, mode);
        case AddressModes::PROGRAM_COUNTER_INDEX: return EmitIndex(emitter, mode);
        case AddressModes::IMMEDIATE: return EmitImmediate(emitter, data, mode);
        default:return;
    }
}

auto EmitSourceExtensionWords(Emitter& emitter, const InstructionData& data) {
    EmitExtensionWords(emitter, data, data.GetSourceData());
}

auto EmitDestinationExtensionWords(Emitter& emitter, const InstructionData& data) {
    EmitExtensionWords(emitter, data, data.GetDestinationData());
}

auto EmitSourceStaticWord(Emitter& emitter, const InstructionData& data) {
    const auto& mode = data.GetSourceData();
    switch (mode.GetMode()) {
        case AddressModes::IMMEDIATE: {
            const auto immediate = mode.GetImmediate();
            EmitWord(emitter, immediate & 0xFFu);
        }
        default:return;
    }
}

auto EmitDestinationStopWord(Emitter& emitter, const InstructionData& data) {
    const auto& mode = data.GetDestinationData();
    switch (mode.GetMode()) {
        case AddressModes::IMMEDIATE: {
            const auto immediate = mode.GetImmediate();
            return EmitWord(emitter, immediate);
        }
        default:return;
    }
}

constexpr auto EncodeBranch(uint32_t operationCode, uint32_t conditionCode, uint32_t displacement) {
    return ((operationCode & 0xFu) << 12u)
           + ((conditionCode & 0xFu) << 8u)
           + (displacement & 0xFFu);
}

auto EmitBranch(Emitter& emitter,
                uint32_t operationCode,
                uint32_t size,
                uint32_t conditionCode,
                uint32_t displacement) {
    if (size == SIZE_BYTE) {
        EmitWord(emitter, EncodeBranch(operationCode, conditionCode, displacement));
    } else if (size == SIZE_WORD) {
        EmitWord(emitter, EncodeBranch(operationCode, conditionCode, 0u));
        EmitWord(emitter, displacement);
    }
}

auto EmitDecrementBranch(
    Emitter& emitter,
    uint32_t operationCode,
    uint32_t conditionCode,
    uint32_t registerCode,
    uint32_t displacement) {
    EmitWord(emitter, EncodeBranch(operationCode, conditionCode, registerCode));
    EmitWord(emitter, displacement);
}

constexpr auto BitReverse16(uint16_t v) {
    v = ((v & 0x00FFu) << 8u) + ((v & 0xFF00u) >> 8u);
    v = ((v & 0x0F0Fu) << 4u) + ((v & 0xF0F0u) >> 4u);
    v = ((v & 0x3333u) << 2u) + ((v & 0xCCCCu) >> 2u);
    v = ((v & 0x5555u) << 1u) + ((v & 0xAAAAu) >> 1u);
    return v;
}

auto EmitRegisterList(Emitter& emitter, const InstructionData& data) {
    const auto mode = data.GetDestinationData().GetMode();
    const auto list = data.GetRegisterList().GetRegisterList();
    if (mode == AddressModes::ADDRESS_DECREMENT) {
        EmitWord(emitter, BitReverse16(list));
        return;
    }
    EmitWord(emitter, list);
}

auto GetEmittableOperandSize(const InstructionData& data) {
    return MapOperandSize(data.GetSize());
}

auto GetEmittableSourceRegister(const InstructionData& data) {
    return data.GetSourceData().GetRegisterNumber();
}

auto GetEmittableDestinationRegister(const InstructionData& data) {
    return data.GetDestinationData().GetRegisterNumber();
}

auto GetEmittableModeAndRegister(const AddressModeData& mode) {
    return MapAddressModeAndRegister(mode.GetMode(), mode.GetRegisterNumber());
}

auto GetEmittableSourceModeAndRegister(const InstructionData& data) {
    return GetEmittableModeAndRegister(data.GetSourceData());
}

auto GetEmittableDestinationModeAndRegister(const InstructionData& data) {
    return GetEmittableModeAndRegister(data.GetDestinationData());
}

auto GetEmittableSourceQuick(const InstructionData& data) {
    return data.GetSourceData().GetImmediate() & 0x7u;
}

auto GetEmittableSourceQuickByte(const InstructionData& data) {
    return data.GetSourceData().GetImmediate();
}

auto GetEmittableDestinationTrapVector(const InstructionData& data) {
    return data.GetDestinationData().GetImmediate();
}

auto GetEmittableBranchConditionCode(const InstructionData& data) {
    return MapConditionCode(data.GetBranchCondition().GetCode());
}

auto GetEmittableBranchDisplacement(const InstructionData& data) {
    return data.GetBranchCondition().GetDisplacement() - 2u;
}

auto EmitDyadicInstruction(Emitter& emitter, uint32_t operationCode, const InstructionData& data) {
    const auto size = GetEmittableOperandSize(data);
    if (data.GetDestinationData().GetMode() == AddressModes::DATA_DIRECT) {
        const auto rx = GetEmittableDestinationRegister(data);
        const auto&[m, ry] = GetEmittableSourceModeAndRegister(data);
        EmitInstructionWord(emitter, operationCode, rx, size, m, ry);
        EmitSourceExtensionWords(emitter, data);
        return true;
    } else if (data.GetSourceData().GetMode() == AddressModes::DATA_DIRECT) {
        const auto rx = GetEmittableSourceRegister(data);
        const auto&[m, ry] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, operationCode, rx, 4u + size, m, ry);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

}

bool EmitABCD(InstructionData& data, Emitter& emitter) {
    if (CheckABCD(data)) {
        const auto& [m, y] = GetEmittableSourceModeAndRegister(data);
        const auto x = GetEmittableDestinationRegister(data);
        const auto rm = (m == MODE_ADDRESS_DECREMENT) ? 1u : 0u;
        EmitInstructionWord(emitter, 0xCu, x, 0x4u, rm, y);
        return true;
    }
    return false;
}

bool EmitADDA(InstructionData& data, Emitter& emitter) {
    if (CheckADDA(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto& [m, r] = GetEmittableSourceModeAndRegister(data);
        const auto x = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0xDu, x, (size << 2u) - 1u, m, r);
        EmitSourceExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitADDI(InstructionData& data, Emitter& emitter) {
    if (CheckADDI(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto& [m, r] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0x0u, 0x3u, size, m, r);
        EmitSourceExtensionWords(emitter, data);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitADDQ(InstructionData& data, Emitter& emitter) {
    if (CheckADDQ(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto quick = GetEmittableSourceQuick(data);
        const auto& [m, r] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0x5u, quick, size, m, r);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitADDX(InstructionData& data, Emitter& emitter) {
    if (CheckADDX(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto& [m, y] = GetEmittableSourceModeAndRegister(data);
        const auto x = GetEmittableDestinationRegister(data);
        const auto rm = (m == MODE_ADDRESS_DECREMENT) ? 1u : 0u;
        EmitInstructionWord(emitter, 0xDu, x, 0x4u + size, rm, y);
        return true;
    }
    return false;
}

bool EmitADD(InstructionData& data, Emitter& emitter) {
    if (CheckADD(data)) {
        return EmitDyadicInstruction(emitter, 0xDu, data);
    }
    return false;
}

bool EmitANDI(InstructionData& data, Emitter& emitter) {
    if (CheckANDI(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto& [m, r] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0x0u, 0x1u, size, m, r);
        EmitSourceExtensionWords(emitter, data);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitANDI_CCR(InstructionData& data, Emitter& emitter) {
    if (CheckANDI_CCR(data)) {
        EmitInstructionWord(emitter, 0x0u, 0x1u, 0x0u, MODE_OTHER, MODE_IMMEDIATE);
        EmitSourceExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitANDI_SR(InstructionData& data, Emitter& emitter) {
    if (CheckANDI_SR(data)) {
        EmitInstructionWord(emitter, 0x0u, 0x1u, 0x1u, MODE_OTHER, MODE_IMMEDIATE);
        EmitSourceExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitAND(InstructionData& data, Emitter& emitter) {
    if (CheckAND(data)) {
        return EmitDyadicInstruction(emitter, 0xCu, data);
    }
    return false;
}

bool EmitASL_Register(InstructionData& data, Emitter& emitter) {
    if (CheckASL_Register(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto rx = GetEmittableSourceRegister(data);
        const auto ry = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0xEu, rx, 0x4u + size, 0x4u, ry);
        return true;
    }
    return false;
}

bool EmitASL_Immediate(InstructionData& data, Emitter& emitter) {
    if (CheckASL_Immediate(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto quick = GetEmittableSourceQuick(data);
        const auto ry = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0xEu, quick, 0x4u + size, 0x0u, ry);
        return true;
    }
    return false;
}

bool EmitASL_Memory(InstructionData& data, Emitter& emitter) {
    if (CheckASL_Memory(data)) {
        const auto& [m, r] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0xEu, 0x0u, 0x7u, m, r);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitASR_Register(InstructionData& data, Emitter& emitter) {
    if (CheckASR_Register(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto rx = GetEmittableSourceRegister(data);
        const auto ry = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0xEu, rx, size, 0x4u, ry);
        return true;
    }
    return false;
}

bool EmitASR_Immediate(InstructionData& data, Emitter& emitter) {
    if (CheckASR_Immediate(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto quick = GetEmittableSourceQuick(data);
        const auto ry = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0xEu, quick, size, 0x0u, ry);
        return true;
    }
    return false;
}

bool EmitASR_Memory(InstructionData& data, Emitter& emitter) {
    if (CheckASR_Memory(data)) {
        const auto& [m, r] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0xEu, 0x0u, 0x3u, m, r);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitBcc(InstructionData& data, Emitter& emitter) {
    if (CheckBcc(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto code = GetEmittableBranchConditionCode(data);
        const auto displacement = GetEmittableBranchDisplacement(data);
        EmitBranch(emitter, 0x6u, size, code, displacement);
        return true;
    }
    return false;
}

bool EmitBCHG_Dynamic_Register(InstructionData& data, Emitter& emitter) {
    if (CheckBCHG_Dynamic_Register(data)) {
        const auto rx = GetEmittableSourceRegister(data);
        const auto ry = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0x0u, rx, 0x5u, MODE_DATA_DIRECT, ry);
        return true;
    }
    return false;
}

bool EmitBCHG_Static_Register(InstructionData& data, Emitter& emitter) {
    if (CheckBCHG_Static_Register(data)) {
        const auto ry = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0x0u, 0x4u, 0x1u, MODE_DATA_DIRECT, ry);
        EmitSourceStaticWord(emitter, data);
        return true;
    }
    return false;
}

bool EmitBCHG_Dynamic_Memory(InstructionData& data, Emitter& emitter) {
    if (CheckBCHG_Dynamic_Memory(data)) {
        const auto rx = GetEmittableSourceRegister(data);
        const auto& [my, ry] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0x0u, rx, 0x5u, my, ry);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitBCHG_Static_Memory(InstructionData& data, Emitter& emitter) {
    if (CheckBCHG_Static_Memory(data)) {
        const auto& [my, ry] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0x0u, 0x4u, 0x1u, my, ry);
        EmitSourceStaticWord(emitter, data);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitBCLR_Dynamic_Register(InstructionData& data, Emitter& emitter) {
    if (CheckBCLR_Dynamic_Register(data)) {
        const auto rx = GetEmittableSourceRegister(data);
        const auto ry = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0x0u, rx, 0x6u, MODE_DATA_DIRECT, ry);
        return true;
    }
    return false;
}

bool EmitBCLR_Static_Register(InstructionData& data, Emitter& emitter) {
    if (CheckBCLR_Static_Register(data)) {
        const auto ry = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0x0u, 0x4u, 0x2u, MODE_DATA_DIRECT, ry);
        EmitSourceStaticWord(emitter, data);
        return true;
    }
    return false;
}

bool EmitBCLR_Dynamic_Memory(InstructionData& data, Emitter& emitter) {
    if (CheckBCLR_Dynamic_Memory(data)) {
        const auto rx = GetEmittableSourceRegister(data);
        const auto& [my, ry] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0x0u, rx, 0x6u, my, ry);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitBCLR_Static_Memory(InstructionData& data, Emitter& emitter) {
    if (CheckBCLR_Static_Memory(data)) {
        const auto& [my, ry] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0x0u, 0x4u, 0x2u, my, ry);
        EmitSourceStaticWord(emitter, data);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitBRA(InstructionData& data, Emitter& emitter) {
    if (CheckBRA(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto code = GetEmittableBranchConditionCode(data);
        const auto displacement = GetEmittableBranchDisplacement(data);
        EmitBranch(emitter, 0x6u, size, code, displacement);
        return true;
    }
    return false;
}

bool EmitBSET_Dynamic_Register(InstructionData& data, Emitter& emitter) {
    if (CheckBSET_Dynamic_Register(data)) {
        const auto rx = GetEmittableSourceRegister(data);
        const auto ry = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0x0u, rx, 0x7u, MODE_DATA_DIRECT, ry);
        return true;
    }
    return false;
}

bool EmitBSET_Static_Register(InstructionData& data, Emitter& emitter) {
    if (CheckBSET_Static_Register(data)) {
        const auto ry = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0x0u, 0x4u, 0x3u, MODE_DATA_DIRECT, ry);
        EmitSourceStaticWord(emitter, data);
        return true;
    }
    return false;
}

bool EmitBSET_Dynamic_Memory(InstructionData& data, Emitter& emitter) {
    if (CheckBSET_Dynamic_Memory(data)) {
        const auto rx = GetEmittableSourceRegister(data);
        const auto& [my, ry] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0x0u, rx, 0x7u, my, ry);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitBSET_Static_Memory(InstructionData& data, Emitter& emitter) {
    if (CheckBSET_Static_Memory(data)) {
        const auto& [my, ry] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0x0u, 0x4u, 0x3u, my, ry);
        EmitSourceStaticWord(emitter, data);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitBSR(InstructionData& data, Emitter& emitter) {
    if (CheckBSR(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto code = GetEmittableBranchConditionCode(data);
        const auto displacement = GetEmittableBranchDisplacement(data);
        EmitBranch(emitter, 0x6u, size, code, displacement);
        return true;
    }
    return false;
}

bool EmitBTST_Dynamic_Register(InstructionData& data, Emitter& emitter) {
    if (CheckBTST_Dynamic_Register(data)) {
        const auto rx = GetEmittableSourceRegister(data);
        const auto ry = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0x0u, rx, 0x4u, MODE_DATA_DIRECT, ry);
        return true;
    }
    return false;
}

bool EmitBTST_Static_Register(InstructionData& data, Emitter& emitter) {
    if (CheckBTST_Static_Register(data)) {
        const auto ry = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0x0u, 0x4u, 0x0u, MODE_DATA_DIRECT, ry);
        EmitSourceStaticWord(emitter, data);
        return true;
    }
    return false;
}

bool EmitBTST_Dynamic_Memory(InstructionData& data, Emitter& emitter) {
    if (CheckBTST_Dynamic_Memory(data)) {
        const auto rx = GetEmittableSourceRegister(data);
        const auto& [my, ry] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0x0u, rx, 0x4u, my, ry);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitBTST_Static_Memory(InstructionData& data, Emitter& emitter) {
    if (CheckBTST_Static_Memory(data)) {
        const auto& [my, ry] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0x0u, 0x4u, 0x0u, my, ry);
        EmitSourceStaticWord(emitter, data);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitCHK(InstructionData& data, Emitter& emitter) {
    if (CheckCHK(data)) {
        const auto& [sm, sr] = GetEmittableSourceModeAndRegister(data);
        const auto dr = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0x4u, dr, 0x6u, sm, sr);
        EmitSourceExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitCLR(InstructionData& data, Emitter& emitter) {
    if (CheckCLR(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto& [m, r] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0x4u, 0x1u, size, m, r);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitCMPA(InstructionData& data, Emitter& emitter) {
    if (CheckCMPA(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto& [m, r] = GetEmittableSourceModeAndRegister(data);
        const auto x = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0xBu, x, (size << 2u) - 1u, m, r);
        EmitSourceExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitCMPI(InstructionData& data, Emitter& emitter) {
    if (CheckCMPI(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto& [m, r] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0x0u, 0x6u, size, m, r);
        EmitSourceExtensionWords(emitter, data);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitCMPM(InstructionData& data, Emitter& emitter) {
    if (CheckCMPM(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto y = GetEmittableSourceRegister(data);
        const auto x = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0xBu, x, 0x4u + size, 0x1u, y);
        return true;
    }
    return false;
}

bool EmitCMP(InstructionData& data, Emitter& emitter) {
    if (CheckCMP(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto& [m, ry] = GetEmittableSourceModeAndRegister(data);
        const auto rx = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0xBu, rx, size, m, ry);
        EmitSourceExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitDBcc(InstructionData& data, Emitter& emitter) {
    if (CheckDBcc(data)) {
        const auto r = GetEmittableSourceRegister(data);
        const auto code = GetEmittableBranchConditionCode(data);
        const auto displacement = GetEmittableBranchDisplacement(data);
        EmitDecrementBranch(emitter, 0x5u, code, 0xC8u + (r & 0x7u), displacement);
        return true;
    }
    return false;
}

bool EmitDIVS(InstructionData& data, Emitter& emitter) {
    if (CheckDIVS(data)) {
        const auto& [m, r] = GetEmittableSourceModeAndRegister(data);
        const auto x = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0x8u, x, 0x7u, m, r);
        EmitSourceExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitDIVU(InstructionData& data, Emitter& emitter) {
    if (CheckDIVU(data)) {
        const auto& [m, r] = GetEmittableSourceModeAndRegister(data);
        const auto x = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0x8u, x, 0x3u, m, r);
        EmitSourceExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitEORI(InstructionData& data, Emitter& emitter) {
    if (CheckEORI(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto& [m, r] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0x0u, 0x5u, size, m, r);
        EmitSourceExtensionWords(emitter, data);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitEORI_CCR(InstructionData& data, Emitter& emitter) {
    if (CheckEORI_CCR(data)) {
        EmitInstructionWord(emitter, 0x0u, 0x5u, 0x0u, MODE_OTHER, MODE_IMMEDIATE);
        EmitSourceExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitEORI_SR(InstructionData& data, Emitter& emitter) {
    if (CheckEORI_SR(data)) {
        EmitInstructionWord(emitter, 0x0u, 0x5u, 0x1u, MODE_OTHER, MODE_IMMEDIATE);
        EmitSourceExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitEOR(InstructionData& data, Emitter& emitter) {
    if (CheckEOR(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto rx = GetEmittableSourceRegister(data);
        const auto& [m, ry] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0xBu, rx, 0x4u + size, m, ry);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitEXG(InstructionData& data, Emitter& emitter) {
    if (CheckEXG(data)) {
        auto [mx, rx] = GetEmittableSourceModeAndRegister(data);
        auto [my, ry] = GetEmittableDestinationModeAndRegister(data);
        if (mx != my && mx == MODE_ADDRESS_DIRECT) {
            std::swap(rx, ry);
        }
        const auto s = (mx != my) ? 1u : 0u;
        const auto t = (mx != my || mx == MODE_ADDRESS_DIRECT) ? 1u : 0u;
        EmitInstructionWord(emitter, 0xCu, rx, 0x5u + s, t, ry);
        return true;
    }
    return false;
}

bool EmitEXT(InstructionData& data, Emitter& emitter) {
    if (CheckEXT(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto r = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0x4u, 0x4u, 0x1u + size, 0x0u, r);
        return true;
    }
    return false;
}

bool EmitILLEGAL(InstructionData& data, Emitter& emitter) {
    if (CheckILLEGAL(data)) {
        EmitInstructionWord(emitter, 0x4u, 0x5u, 0x3u, 0x7u, 0x4u);
        return true;
    }
    return false;
}

bool EmitJMP(InstructionData& data, Emitter& emitter) {
    if (CheckJMP(data)) {
        const auto& [m, r] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0x4u, 0x7u, 0x3u, m, r);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitJSR(InstructionData& data, Emitter& emitter) {
    if (CheckJSR(data)) {
        const auto& [m, r] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0x4u, 0x7u, 0x2u, m, r);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitLEA(InstructionData& data, Emitter& emitter) {
    if (CheckLEA(data)) {
        const auto& [m, y] = GetEmittableSourceModeAndRegister(data);
        const auto x = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0x4u, x, 0x7u, m, y);
        EmitSourceExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitLINK(InstructionData& data, Emitter& emitter) {
    if (CheckLINK(data)) {
        const auto r = GetEmittableSourceRegister(data);
        EmitInstructionWord(emitter, 0x4u, 0x7u, 0x1u, 0x2u, r);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitLSL_Register(InstructionData& data, Emitter& emitter) {
    if (CheckLSL_Register(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto rx = GetEmittableSourceRegister(data);
        const auto ry = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0xEu, rx, 0x4u + size, 0x5u, ry);
        return true;
    }
    return false;
}

bool EmitLSL_Immediate(InstructionData& data, Emitter& emitter) {
    if (CheckLSL_Immediate(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto quick = GetEmittableSourceQuick(data);
        const auto ry = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0xEu, quick, 0x4u + size, 0x1u, ry);
        return true;
    }
    return false;
}

bool EmitLSL_Memory(InstructionData& data, Emitter& emitter) {
    if (CheckLSL_Memory(data)) {
        const auto& [m, r] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0xEu, 0x1u, 0x7u, m, r);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitLSR_Register(InstructionData& data, Emitter& emitter) {
    if (CheckLSR_Register(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto rx = GetEmittableSourceRegister(data);
        const auto ry = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0xEu, rx, size, 0x5u, ry);
        return true;
    }
    return false;
}

bool EmitLSR_Immediate(InstructionData& data, Emitter& emitter) {
    if (CheckLSR_Immediate(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto quick = GetEmittableSourceQuick(data);
        const auto ry = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0xEu, quick, size, 0x1u, ry);
        return true;
    }
    return false;
}

bool EmitLSR_Memory(InstructionData& data, Emitter& emitter) {
    if (CheckLSR_Memory(data)) {
        const auto& [m, r] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0xEu, 0x1u, 0x3u, m, r);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitMOVEA(InstructionData& data, Emitter& emitter) {
    if (CheckMOVEA(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto& [sm, sr] = GetEmittableSourceModeAndRegister(data);
        const auto dr = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 1u + ((size ^ 3u) % 3u), dr, MODE_ADDRESS_DIRECT, sm, sr);
        EmitSourceExtensionWords(emitter, data);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitMOVE_CCR(InstructionData& data, Emitter& emitter) {
    if (CheckMOVE_CCR(data)) {
        const auto& [m, r] = GetEmittableSourceModeAndRegister(data);
        EmitInstructionWord(emitter, 0x4u, 0x2u, 0x3u, m, r);
        EmitSourceExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitMOVEM_Register(InstructionData& data, Emitter& emitter) {
    if (CheckMOVEM_Register(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto& [m, r] = GetEmittableSourceModeAndRegister(data);
        EmitInstructionWord(emitter, 0x4u, 0x6u, 2u + (size - 1u), m, r);
        EmitRegisterList(emitter, data);
        EmitSourceExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitMOVEM_Memory(InstructionData& data, Emitter& emitter) {
    if (CheckMOVEM_Memory(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto& [m, r] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0x4u, 0x4u, 2u + (size - 1u), m, r);
        EmitRegisterList(emitter, data);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitMOVEP(InstructionData& data, Emitter& emitter) {
    if (CheckMOVEP(data)) {
        const auto size = GetEmittableOperandSize(data);
        auto [my, ry] = GetEmittableSourceModeAndRegister(data);
        auto rx = GetEmittableDestinationRegister(data);
        if (my == MODE_DATA_DIRECT) {
            std::swap(rx, ry);
        }
        const auto d = (my == MODE_DATA_DIRECT) ? 2u : 0u;
        EmitInstructionWord(emitter, 0x0u, rx, 0x4u + d + (size - 0x1u), 0x1u, ry);
        EmitSourceExtensionWords(emitter, data);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitMOVEQ(InstructionData& data, Emitter& emitter) {
    if (CheckMOVEQ(data)) {
        const auto quick = GetEmittableSourceQuickByte(data);
        const auto r = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0x7u, r, ((quick & 0xC0u) >> 6u), ((quick & 0x38u) >> 3u), (quick & 0x7u));
        return true;
    }
    return false;
}

bool EmitMOVE_SR_SR(InstructionData& data, Emitter& emitter) {
    if (CheckMOVE_SR_SR(data)) {
        const auto& [m, r] = GetEmittableSourceModeAndRegister(data);
        EmitInstructionWord(emitter, 0x4u, 0x3u, 0x3u, m, r);
        EmitSourceExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitMOVE_SR_Memory(InstructionData& data, Emitter& emitter) {
    if (CheckMOVE_SR_Memory(data)) {
        const auto& [m, r] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0x4u, 0x0u, 0x3u, m, r);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitMOVE_USP_USP(InstructionData& data, Emitter& emitter) {
    if (CheckMOVE_USP_USP(data)) {
        const auto r = GetEmittableSourceRegister(data);
        EmitInstructionWord(emitter, 0x4u, 0x7u, 0x1u, 0x4u, r);
        return true;
    }
    return false;
}

bool EmitMOVE_USP_Register(InstructionData& data, Emitter& emitter) {
    if (CheckMOVE_USP_Register(data)) {
        const auto r = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0x4u, 0x7u, 0x1u, 0x5u, r);
        return true;
    }
    return false;
}

bool EmitMOVE(InstructionData& data, Emitter& emitter) {
    if (CheckMOVE(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto& [sm, sr] = GetEmittableSourceModeAndRegister(data);
        const auto& [dm, dr] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 1u + ((size ^ 3u) % 3u), dr, dm, sm, sr);
        EmitSourceExtensionWords(emitter, data);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitMULS(InstructionData& data, Emitter& emitter) {
    if (CheckMULS(data)) {
        const auto& [m, r] = GetEmittableSourceModeAndRegister(data);
        const auto x = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0xCu, x, 0x7u, m, r);
        EmitSourceExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitMULU(InstructionData& data, Emitter& emitter) {
    if (CheckMULU(data)) {
        const auto& [m, r] = GetEmittableSourceModeAndRegister(data);
        const auto x = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0xCu, x, 0x3u, m, r);
        EmitSourceExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitNBCD(InstructionData& data, Emitter& emitter) {
    if (CheckNBCD(data)) {
        const auto& [m, r] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0x4u, 0x4u, 0x0u, m, r);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitNEGX(InstructionData& data, Emitter& emitter) {
    if (CheckNEGX(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto& [m, r] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0x4u, 0x0u, size, m, r);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitNEG(InstructionData& data, Emitter& emitter) {
    if (CheckNEG(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto& [m, r] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0x4u, 0x2u, size, m, r);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitNOP(InstructionData& data, Emitter& emitter) {
    if (CheckNOP(data)) {
        EmitInstructionWord(emitter, 0x4u, 0x7u, 0x1u, 0x6u, 0x1u);
        return true;
    }
    return false;
}

bool EmitNOT(InstructionData& data, Emitter& emitter) {
    if (CheckNOT(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto& [m, r] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0x4u, 0x3u, size, m, r);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitORI(InstructionData& data, Emitter& emitter) {
    if (CheckORI(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto& [m, r] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0x0u, 0x0u, size, m, r);
        EmitSourceExtensionWords(emitter, data);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitORI_CCR(InstructionData& data, Emitter& emitter) {
    if (CheckORI_CCR(data)) {
        EmitInstructionWord(emitter, 0x0u, 0x0u, 0x0u, MODE_OTHER, MODE_IMMEDIATE);
        EmitSourceExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitORI_SR(InstructionData& data, Emitter& emitter) {
    if (CheckORI_SR(data)) {
        EmitInstructionWord(emitter, 0x0u, 0x0u, 0x1u, MODE_OTHER, MODE_IMMEDIATE);
        EmitSourceExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitOR(InstructionData& data, Emitter& emitter) {
    if (CheckOR(data)) {
        return EmitDyadicInstruction(emitter, 0x8u, data);
    }
    return false;
}

bool EmitPEA(InstructionData& data, Emitter& emitter) {
    if (CheckPEA(data)) {
        const auto& [m, r] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0x4u, 0x4u, 0x1u, m, r);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitRESET(InstructionData& data, Emitter& emitter) {
    if (CheckRESET(data)) {
        EmitInstructionWord(emitter, 0x4u, 0x7u, 0x1u, 0x6u, 0x0u);
        return true;
    }
    return false;
}

bool EmitROL_Register(InstructionData& data, Emitter& emitter) {
    if (CheckROL_Register(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto rx = GetEmittableSourceRegister(data);
        const auto ry = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0xEu, rx, 0x4u + size, 0x7u, ry);
        return true;
    }
    return false;
}

bool EmitROL_Immediate(InstructionData& data, Emitter& emitter) {
    if (CheckROL_Immediate(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto quick = GetEmittableSourceQuick(data);
        const auto ry = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0xEu, quick, 0x4u + size, 0x3u, ry);
        return true;
    }
    return false;
}

bool EmitROL_Memory(InstructionData& data, Emitter& emitter) {
    if (CheckROL_Memory(data)) {
        const auto& [m, r] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0xEu, 0x3u, 0x7u, m, r);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitROR_Register(InstructionData& data, Emitter& emitter) {
    if (CheckROR_Register(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto rx = GetEmittableSourceRegister(data);
        const auto ry = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0xEu, rx, size, 0x7u, ry);
        return true;
    }
    return false;
}

bool EmitROR_Immediate(InstructionData& data, Emitter& emitter) {
    if (CheckROR_Immediate(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto quick = GetEmittableSourceQuick(data);
        const auto ry = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0xEu, quick, size, 0x3u, ry);
        return true;
    }
    return false;
}

bool EmitROR_Memory(InstructionData& data, Emitter& emitter) {
    if (CheckROR_Memory(data)) {
        const auto& [m, r] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0xEu, 0x3u, 0x3u, m, r);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitROXL_Register(InstructionData& data, Emitter& emitter) {
    if (CheckROXL_Register(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto rx = GetEmittableSourceRegister(data);
        const auto ry = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0xEu, rx, 0x4u + size, 0x6u, ry);
        return true;
    }
    return false;
}

bool EmitROXL_Immediate(InstructionData& data, Emitter& emitter) {
    if (CheckROXL_Immediate(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto quick = GetEmittableSourceQuick(data);
        const auto ry = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0xEu, quick, 0x4u + size, 0x2u, ry);
        return true;
    }
    return false;
}

bool EmitROXL_Memory(InstructionData& data, Emitter& emitter) {
    if (CheckROXL_Memory(data)) {
        const auto& [m, r] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0xEu, 0x2u, 0x7u, m, r);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitROXR_Register(InstructionData& data, Emitter& emitter) {
    if (CheckROXR_Register(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto rx = GetEmittableSourceRegister(data);
        const auto ry = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0xEu, rx, size, 0x6u, ry);
        return true;
    }
    return false;
}

bool EmitROXR_Immediate(InstructionData& data, Emitter& emitter) {
    if (CheckROXR_Immediate(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto quick = GetEmittableSourceQuick(data);
        const auto ry = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0xEu, quick, size, 0x2u, ry);
        return true;
    }
    return false;
}

bool EmitROXR_Memory(InstructionData& data, Emitter& emitter) {
    if (CheckROXR_Memory(data)) {
        const auto& [m, r] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0xEu, 0x2u, 0x3u, m, r);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitRTE(InstructionData& data, Emitter& emitter) {
    if (CheckRTE(data)) {
        EmitInstructionWord(emitter, 0x4u, 0x7u, 0x1u, 0x6u, 0x3u);
        return true;
    }
    return false;
}

bool EmitRTR(InstructionData& data, Emitter& emitter) {
    if (CheckRTR(data)) {
        EmitInstructionWord(emitter, 0x4u, 0x7u, 0x1u, 0x6u, 0x7u);
        return true;
    }
    return false;
}

bool EmitRTS(InstructionData& data, Emitter& emitter) {
    if (CheckRTS(data)) {
        EmitInstructionWord(emitter, 0x4u, 0x7u, 0x1u, 0x6u, 0x5u);
        return true;
    }
    return false;
}

bool EmitSBCD(InstructionData& data, Emitter& emitter) {
    if (CheckSBCD(data)) {
        const auto& [m, y] = GetEmittableSourceModeAndRegister(data);
        const auto x = GetEmittableDestinationRegister(data);
        const auto rm = (m == MODE_ADDRESS_DECREMENT) ? 1u : 0u;
        EmitInstructionWord(emitter, 0x8u, x, 0x4u, rm, y);
        return true;
    }
    return false;
}

bool EmitScc(InstructionData& data, Emitter& emitter) {
    if (CheckScc(data)) {
        const auto& [m, r] = GetEmittableDestinationModeAndRegister(data);
        const auto code = GetEmittableBranchConditionCode(data);
        EmitInstructionWord(emitter, 0x5u, (code & 0xEu) >> 1u, 0x3u + ((code & 0x1u) << 2u), m, r);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitSTOP(InstructionData& data, Emitter& emitter) {
    if (CheckSTOP(data)) {
        EmitInstructionWord(emitter, 0x4u, 0x7u, 0x1u, 0x6u, 0x2u);
        EmitDestinationStopWord(emitter, data);
        return true;
    }
    return false;
}

bool EmitSUBA(InstructionData& data, Emitter& emitter) {
    if (CheckSUBA(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto& [m, r] = GetEmittableSourceModeAndRegister(data);
        const auto x = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0x9u, x, (size << 2u) - 1u, m, r);
        EmitSourceExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitSUBI(InstructionData& data, Emitter& emitter) {
    if (CheckSUBI(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto& [m, r] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0x0u, 0x2u, size, m, r);
        EmitSourceExtensionWords(emitter, data);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitSUBQ(InstructionData& data, Emitter& emitter) {
    if (CheckSUBQ(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto quick = GetEmittableSourceQuick(data);
        const auto& [m, r] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0x5u, quick, 4u + size, m, r);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitSUBX(InstructionData& data, Emitter& emitter) {
    if (CheckSUBX(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto& [m, y] = GetEmittableSourceModeAndRegister(data);
        const auto x = GetEmittableDestinationRegister(data);
        const auto rm = (m == MODE_ADDRESS_DECREMENT) ? 1u : 0u;
        EmitInstructionWord(emitter, 0x9u, x, 0x4u + size, rm, y);
        return true;
    }
    return false;
}

bool EmitSUB(InstructionData& data, Emitter& emitter) {
    if (CheckSUB(data)) {
        return EmitDyadicInstruction(emitter, 0x9u, data);
    }
    return false;
}

bool EmitSWAP(InstructionData& data, Emitter& emitter) {
    if (CheckSWAP(data)) {
        const auto r = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0x4u, 0x4u, 0x1u, 0x0u, r);
        return true;
    }
    return false;
}

bool EmitTAS(InstructionData& data, Emitter& emitter) {
    if (CheckTAS(data)) {
        const auto& [m, r] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0x4u, 0x5u, 0x3u, m, r);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitTRAP(InstructionData& data, Emitter& emitter) {
    if (CheckTRAP(data)) {
        const auto vector = GetEmittableDestinationTrapVector(data);
        EmitInstructionWord(emitter, 0x4u, 0x7u, 0x1u, (vector & 0x8u) >> 3u, (vector & 0x7u));
        return true;
    }
    return false;
}

bool EmitTRAPV(InstructionData& data, Emitter& emitter) {
    if (CheckTRAPV(data)) {
        EmitInstructionWord(emitter, 0x4u, 0x7u, 0x1u, 0x6u, 0x6u);
        return true;
    }
    return false;
}

bool EmitTST(InstructionData& data, Emitter& emitter) {
    if (CheckTST(data)) {
        const auto size = GetEmittableOperandSize(data);
        const auto& [m, r] = GetEmittableDestinationModeAndRegister(data);
        EmitInstructionWord(emitter, 0x4u, 0x5u, size, m, r);
        EmitDestinationExtensionWords(emitter, data);
        return true;
    }
    return false;
}

bool EmitUNLK(InstructionData& data, Emitter& emitter) {
    if (CheckUNLK(data)) {
        const auto r = GetEmittableDestinationRegister(data);
        EmitInstructionWord(emitter, 0x4u, 0x7u, 0x1u, 0x3u, r);
        return true;
    }
    return false;
}

}
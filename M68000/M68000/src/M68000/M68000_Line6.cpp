#include "M68000/M68000.h"
#include "M68000/M68000_Constants.h"
#include "M68000/M68000_Int.h"
#include "M68000/M68000_Opcode.h"

using namespace rbrown::m68000;

auto M68000::ExecuteLine6(uint32_t opcode) -> void {
    ExecuteBcc(opcode);
}

auto M68000::ExecuteBcc(uint32_t opcode) -> void {
    const auto condition = OpcodeConditionCode(opcode);
    if (condition == CONDITION_CODE_F) {
        ExecuteBsr(opcode);
        return;
    }
    if (TestCondition(condition)) {
        ExecuteBccBranchTaken(opcode);
        return;
    }
    ExecuteBccBranchNotTaken(opcode);
}

auto M68000::ExecuteBccBranchTaken(uint32_t opcode) -> void {
    InternalCycle();
    uint32_t displacement, size;
    BccDisplacementAndSize(opcode, displacement, size);
    const auto baseAddress = ReadPC();
    WritePC(baseAddress + displacement - 2u);
    if (!ExecutePrefetchCycle()) [[unlikely]] {
        return;
    }
    ExecuteFinalPrefetchCycle();
}

auto M68000::ExecuteBccBranchNotTaken(uint32_t opcode) -> void {
    InternalCycle();
    InternalCycle();
    const auto byteDisplacement = OpcodeBranchDisplacement(opcode);
    // Bcc.B
    if (byteDisplacement != 0u) {
        ExecuteFinalPrefetchCycle();
        return;
    }
    // Bcc.W
    if (!ExecutePrefetchCycle()) [[unlikely]] {
        return;
    }
    ExecuteFinalPrefetchCycle();
}

auto M68000::ExecuteBsr(uint32_t opcode) -> void {
    InternalCycle();
    uint32_t displacement, size;
    BccDisplacementAndSize(opcode, displacement, size);
    const auto baseAddress = ReadPC();
    if (!PushLong(baseAddress + size)) [[unlikely]] {
        return;
    }
    WritePC(pc + displacement - 2u);
    if (!ExecutePrefetchCycle()) [[unlikely]] {
        return;
    }
    ExecuteFinalPrefetchCycle();
}

auto M68000::BccDisplacementAndSize(uint32_t opcode, uint32_t& displacement, uint32_t& size) const -> void {
    const auto byteDisplacement = OpcodeBranchDisplacement(opcode);
    if (byteDisplacement != 0u) {
        displacement = byteDisplacement;
        size = 2u;
        return;
    }
    const auto displacementWord = ReadIRC();
    displacement = SignExtend16(displacementWord);
    size = 4u;
}
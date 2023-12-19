#include "M68000/M68000.h"
#include "M68000/M68000_Opcode.h"

using namespace rbrown::m68000;

auto M68000::ExecuteLine7(uint32_t opcode) -> void {
    if (opcode & 0x0100u) [[unlikely]] {
        ExecuteIllegal();
        return;
    }
    ExecuteMoveqDataRegister(opcode);
}

// MOVEQ #imm, Dx

auto M68000::ExecuteMoveqDataRegister(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto result = Moveq(opcode);
    WriteDataRegisterLong(rx, result);
    ExecuteFinalPrefetchCycle();
}


#include "M68000/DisassemblerImpl.h"
#include "M68000/M68000_Opcode.h"

using namespace rbrown::m68000;

auto Disassembler::Line7(uint32_t opcode) -> std::string {
    if (opcode & 0x0100u) {
        return {};
    }
    const auto rx = OpcodeRegisterX(opcode);
    const auto quick = QuickByte(opcode);
    return BinaryInstruction("MOVEQ", quick, Dn(rx));
}
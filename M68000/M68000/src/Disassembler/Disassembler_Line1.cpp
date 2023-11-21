#include "M68000/DisassemblerImpl.h"
#include "M68000/M68000_Opcode.h"

using namespace rbrown::m68000;

auto Disassembler::Line1(uint32_t opcode) -> std::string {
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return Line1(Dn(ry), opcode);
        case 2u: return Line1(AnIndirect(ry), opcode);
        case 3u: return Line1(AnIncrement(ry), opcode);
        case 4u: return Line1(AnDecrement(ry), opcode);
        case 5u: return Line1(AnDisplacement(ry), opcode);
        case 6u: return Line1(AnIndex(ry), opcode);
        case 7u:
            switch (ry) {
                case 0u: return Line1(Short(), opcode);
                case 1u: return Line1(Long(), opcode);
                case 2u: return Line1(PCDisplacement(), opcode);
                case 3u: return Line1(PCIndex(), opcode);
                case 4u: return Line1(ImmediateByte(), opcode);
                default: return {};
            }
        default: return {};
    }
}

auto Disassembler::Line1(const std::string& source, uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "MOVE.B";
    const auto rx = OpcodeRegisterX(opcode);
    switch (OpcodeModeX(opcode)) {
        case 0u: return BinaryInstruction(mnemonic, source, Dn(rx));
        case 2u: return BinaryInstruction(mnemonic, source, AnIndirect(rx));
        case 3u: return BinaryInstruction(mnemonic, source, AnIncrement(rx));
        case 4u: return BinaryInstruction(mnemonic, source, AnDecrement(rx));
        case 5u: return BinaryInstruction(mnemonic, source, AnDisplacement(rx));
        case 6u: return BinaryInstruction(mnemonic, source, AnIndex(rx));
        case 7u:
            switch (rx) {
                case 0u: return BinaryInstruction(mnemonic, source, Short());
                case 1u: return BinaryInstruction(mnemonic, source, Long());
                default: return {};
            }
        default: return {};
    }
}
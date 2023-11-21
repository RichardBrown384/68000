#include "M68000/DisassemblerImpl.h"
#include "M68000/M68000_Opcode.h"

using namespace rbrown::m68000;

auto Disassembler::LineC(uint32_t opcode) -> std::string {
    switch (OpcodeModeX(opcode)) {
        case 0u: return Line8Size0("AND.B", opcode);
        case 1u: return Line8Size1("AND.W", opcode);
        case 2u: return Line8Size2("AND.L", opcode);
        case 3u: return Line8Size1("MULU", opcode);
        case 4u: return LineCSize4(opcode);
        case 5u: return LineCSize5(opcode);
        case 6u: return LineCSize6(opcode);
        case 7u: return Line8Size1("MULS", opcode);
        default:return {};
    }
}

auto Disassembler::LineCSize4(uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "AND.B";
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction("ABCD", Dn(ry), Dn(rx));
        case 1u: return BinaryInstruction("ABCD", AnDecrement(ry), AnDecrement(rx));
        case 2u: return BinaryInstruction(mnemonic, Dn(rx), AnIndirect(ry));
        case 3u: return BinaryInstruction(mnemonic, Dn(rx), AnIncrement(ry));
        case 4u: return BinaryInstruction(mnemonic, Dn(rx), AnDecrement(ry));
        case 5u: return BinaryInstruction(mnemonic, Dn(rx), AnDisplacement(ry));
        case 6u: return BinaryInstruction(mnemonic, Dn(rx), AnIndex(ry));
        case 7u:
            switch (ry) {
                case 0u: return BinaryInstruction(mnemonic, Dn(rx), Short());
                case 1u: return BinaryInstruction(mnemonic, Dn(rx), Long());
                default:return {};
            }
        default:return {};
    }
}

auto Disassembler::LineCSize5(uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "AND.W";
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction("EXG", Dn(rx), Dn(ry));
        case 1u: return BinaryInstruction("EXG", An(rx), An(ry));
        case 2u: return BinaryInstruction(mnemonic, Dn(rx), AnIndirect(ry));
        case 3u: return BinaryInstruction(mnemonic, Dn(rx), AnIncrement(ry));
        case 4u: return BinaryInstruction(mnemonic, Dn(rx), AnDecrement(ry));
        case 5u: return BinaryInstruction(mnemonic, Dn(rx), AnDisplacement(ry));
        case 6u: return BinaryInstruction(mnemonic, Dn(rx), AnIndex(ry));
        case 7u:
            switch (ry) {
                case 0u: return BinaryInstruction(mnemonic, Dn(rx), Short());
                case 1u: return BinaryInstruction(mnemonic, Dn(rx), Long());
                default:return {};
            }
        default:return {};
    }
}

auto Disassembler::LineCSize6(uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "AND.L";
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 1u: return BinaryInstruction("EXG", Dn(rx), An(ry));
        case 2u: return BinaryInstruction(mnemonic, Dn(rx), AnIndirect(ry));
        case 3u: return BinaryInstruction(mnemonic, Dn(rx), AnIncrement(ry));
        case 4u: return BinaryInstruction(mnemonic, Dn(rx), AnDecrement(ry));
        case 5u: return BinaryInstruction(mnemonic, Dn(rx), AnDisplacement(ry));
        case 6u: return BinaryInstruction(mnemonic, Dn(rx), AnIndex(ry));
        case 7u:
            switch (ry) {
                case 0u: return BinaryInstruction(mnemonic, Dn(rx), Short());
                case 1u: return BinaryInstruction(mnemonic, Dn(rx), Long());
                default:return {};
            }
        default:return {};
    }
}

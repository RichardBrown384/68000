#include "M68000/DisassemblerImpl.h"
#include "M68000/M68000_Opcode.h"

using namespace rbrown::m68000;

auto Disassembler::LineD(uint32_t opcode) -> std::string {
    switch (OpcodeModeX(opcode)) {
        case 0u: return Line8Size0("ADD.B", opcode);
        case 1u: return Line9Size1("ADD.W", opcode);
        case 2u: return Line9Size2("ADD.L", opcode);
        case 3u: return Line9Size3("ADDA.W", opcode);
        case 4u: return LineDSize4(opcode);
        case 5u: return LineDSize5(opcode);
        case 6u: return LineDSize6(opcode);
        case 7u: return Line9Size7("ADDA.L", opcode);
        default:return {};
    }
}

auto Disassembler::LineDSize4(uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "ADD.B";
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction("ADDX.B", Dn(ry), Dn(rx));
        case 1u: return BinaryInstruction("ADDX.B", AnDecrement(ry), AnDecrement(rx));
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

auto Disassembler::LineDSize5(uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "ADD.W";
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction("ADDX.W", Dn(ry), Dn(rx));
        case 1u: return BinaryInstruction("ADDX.W", AnDecrement(ry), AnDecrement(rx));
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

auto Disassembler::LineDSize6(uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "ADD.L";
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction("ADDX.L", Dn(ry), Dn(rx));
        case 1u: return BinaryInstruction("ADDX.L", AnDecrement(ry), AnDecrement(rx));
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
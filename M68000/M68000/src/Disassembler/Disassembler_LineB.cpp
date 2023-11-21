#include "M68000/DisassemblerImpl.h"
#include "M68000/M68000_Opcode.h"

using namespace rbrown::m68000;

auto Disassembler::LineB(uint32_t opcode) -> std::string {
    switch (OpcodeModeX(opcode)) {
        case 0u: return Line8Size0("CMP.B", opcode);
        case 1u: return Line9Size1("CMP.W", opcode);
        case 2u: return Line9Size2("CMP.L", opcode);
        case 3u: return Line9Size3("CMPA.W", opcode);
        case 4u: return LineBSize4(opcode);
        case 5u: return LineBSize5(opcode);
        case 6u: return LineBSize6(opcode);
        case 7u: return Line9Size7("CMPA.L", opcode);
        default:return {};
    }
}

auto Disassembler::LineBSize4(uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "EOR.B";
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction(mnemonic, Dn(rx), Dn(ry));
        case 1u: return BinaryInstruction("CMPM.B", AnIncrement(ry), AnIncrement(rx));
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

auto Disassembler::LineBSize5(uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "EOR.W";
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction(mnemonic, Dn(rx), Dn(ry));
        case 1u: return BinaryInstruction("CMPM.W", AnIncrement(ry), AnIncrement(rx));
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

auto Disassembler::LineBSize6(uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "EOR.L";
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction(mnemonic, Dn(rx), Dn(ry));
        case 1u: return BinaryInstruction("CMPM.L", AnIncrement(ry), AnIncrement(rx));
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

#include "M68000/DisassemblerImpl.h"
#include "M68000/M68000_Opcode.h"

using namespace rbrown::m68000;

auto Disassembler::Line8(uint32_t opcode) -> std::string {
    switch (OpcodeModeX(opcode)) {
        case 0u: return Line8Size0("OR.B", opcode);
        case 1u: return Line8Size1("OR.W", opcode);
        case 2u: return Line8Size2("OR.L", opcode);
        case 3u: return Line8Size1("DIVU", opcode);
        case 4u: return Line8Size4(opcode);
        case 5u: return Line8Size5("OR.W", opcode);
        case 6u: return Line8Size5("OR.L", opcode);
        case 7u: return Line8Size1("DIVS", opcode);
        default:return {};
    }
}

auto Disassembler::Line8Size0(const std::string& mnemonic, uint32_t opcode) -> std::string {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction(mnemonic, Dn(ry), Dn(rx));
        case 2u: return BinaryInstruction(mnemonic, AnIndirect(ry), Dn(rx));
        case 3u: return BinaryInstruction(mnemonic, AnIncrement(ry), Dn(rx));
        case 4u: return BinaryInstruction(mnemonic, AnDecrement(ry), Dn(rx));
        case 5u: return BinaryInstruction(mnemonic, AnDisplacement(ry), Dn(rx));
        case 6u: return BinaryInstruction(mnemonic, AnIndex(ry), Dn(rx));
        case 7u:
            switch (ry) {
                case 0u: return BinaryInstruction(mnemonic, Short(), Dn(rx));
                case 1u: return BinaryInstruction(mnemonic, Long(), Dn(rx));
                case 2u: return BinaryInstruction(mnemonic, PCDisplacement(), Dn(rx));
                case 3u: return BinaryInstruction(mnemonic, PCIndex(), Dn(rx));
                case 4u: return BinaryInstruction(mnemonic, ImmediateByte(), Dn(rx));
                default:return {};
            }
        default:return {};
    }
}

auto Disassembler::Line8Size1(const std::string& mnemonic, uint32_t opcode) -> std::string {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction(mnemonic, Dn(ry), Dn(rx));
        case 2u: return BinaryInstruction(mnemonic, AnIndirect(ry), Dn(rx));
        case 3u: return BinaryInstruction(mnemonic, AnIncrement(ry), Dn(rx));
        case 4u: return BinaryInstruction(mnemonic, AnDecrement(ry), Dn(rx));
        case 5u: return BinaryInstruction(mnemonic, AnDisplacement(ry), Dn(rx));
        case 6u: return BinaryInstruction(mnemonic, AnIndex(ry), Dn(rx));
        case 7u:
            switch (ry) {
                case 0u: return BinaryInstruction(mnemonic, Short(), Dn(rx));
                case 1u: return BinaryInstruction(mnemonic, Long(), Dn(rx));
                case 2u: return BinaryInstruction(mnemonic, PCDisplacement(), Dn(rx));
                case 3u: return BinaryInstruction(mnemonic, PCIndex(), Dn(rx));
                case 4u: return BinaryInstruction(mnemonic, ImmediateWord(), Dn(rx));
                default:return {};
            }
        default:return {};
    }
}

auto Disassembler::Line8Size2(const std::string& mnemonic, uint32_t opcode) -> std::string {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction(mnemonic, Dn(ry), Dn(rx));
        case 2u: return BinaryInstruction(mnemonic, AnIndirect(ry), Dn(rx));
        case 3u: return BinaryInstruction(mnemonic, AnIncrement(ry), Dn(rx));
        case 4u: return BinaryInstruction(mnemonic, AnDecrement(ry), Dn(rx));
        case 5u: return BinaryInstruction(mnemonic, AnDisplacement(ry), Dn(rx));
        case 6u: return BinaryInstruction(mnemonic, AnIndex(ry), Dn(rx));
        case 7u:
            switch (ry) {
                case 0u: return BinaryInstruction(mnemonic, Short(), Dn(rx));
                case 1u: return BinaryInstruction(mnemonic, Long(), Dn(rx));
                case 2u: return BinaryInstruction(mnemonic, PCDisplacement(), Dn(rx));
                case 3u: return BinaryInstruction(mnemonic, PCIndex(), Dn(rx));
                case 4u: return BinaryInstruction(mnemonic, ImmediateLong(), Dn(rx));
                default:return {};
            }
        default:return {};
    }
}

auto Disassembler::Line8Size4(uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "OR.B";
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction("SBCD", Dn(ry), Dn(rx));
        case 1u: return BinaryInstruction("SBCD", AnDecrement(ry), AnDecrement(rx));
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

auto Disassembler::Line8Size5(const std::string& mnemonic, uint32_t opcode) -> std::string {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
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
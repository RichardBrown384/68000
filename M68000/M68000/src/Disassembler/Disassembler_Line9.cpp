#include "M68000/DisassemblerImpl.h"
#include "M68000/M68000_Opcode.h"

using namespace rbrown::m68000;

auto Disassembler::Line9(uint32_t opcode) -> std::string {
    switch (OpcodeModeX(opcode)) {
        case 0u: return Line8Size0("SUB.B", opcode);
        case 1u: return Line9Size1("SUB.W", opcode);
        case 2u: return Line9Size2("SUB.L", opcode);
        case 3u: return Line9Size3("SUBA.W", opcode);
        case 4u: return Line9Size4(opcode);
        case 5u: return Line9Size5(opcode);
        case 6u: return Line9Size6(opcode);
        case 7u: return Line9Size7("SUBA.L", opcode);
        default:return {};
    }
}

auto Disassembler::Line9Size1(const std::string& mnemonic, uint32_t opcode) -> std::string {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction(mnemonic, Dn(ry), Dn(rx));
        case 1u: return BinaryInstruction(mnemonic, An(ry), Dn(rx));
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

auto Disassembler::Line9Size2(const std::string& mnemonic, uint32_t opcode) -> std::string {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction(mnemonic, Dn(ry), Dn(rx));
        case 1u: return BinaryInstruction(mnemonic, An(ry), Dn(rx));
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

auto Disassembler::Line9Size3(const std::string& mnemonic, uint32_t opcode) -> std::string {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction(mnemonic, Dn(ry), An(rx));
        case 1u: return BinaryInstruction(mnemonic, An(ry), An(rx));
        case 2u: return BinaryInstruction(mnemonic, AnIndirect(ry), An(rx));
        case 3u: return BinaryInstruction(mnemonic, AnIncrement(ry), An(rx));
        case 4u: return BinaryInstruction(mnemonic, AnDecrement(ry), An(rx));
        case 5u: return BinaryInstruction(mnemonic, AnDisplacement(ry), An(rx));
        case 6u: return BinaryInstruction(mnemonic, AnIndex(ry), An(rx));
        case 7u:
            switch (ry) {
                case 0u: return BinaryInstruction(mnemonic, Short(), An(rx));
                case 1u: return BinaryInstruction(mnemonic, Long(), An(rx));
                case 2u: return BinaryInstruction(mnemonic, PCDisplacement(), An(rx));
                case 3u: return BinaryInstruction(mnemonic, PCIndex(), An(rx));
                case 4u: return BinaryInstruction(mnemonic, ImmediateWord(), An(rx));
                default:return {};
            }
        default:return {};
    }
}

auto Disassembler::Line9Size4(uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "SUB.B";
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction("SUBX.B", Dn(ry), Dn(rx));
        case 1u: return BinaryInstruction("SUBX.B", AnDecrement(ry), AnDecrement(rx));
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

auto Disassembler::Line9Size5(uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "SUB.W";
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction("SUBX.W", Dn(ry), Dn(rx));
        case 1u: return BinaryInstruction("SUBX.W", AnDecrement(ry), AnDecrement(rx));
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

auto Disassembler::Line9Size6(uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "SUB.L";
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction("SUBX.L", Dn(ry), Dn(rx));
        case 1u: return BinaryInstruction("SUBX.L", AnDecrement(ry), AnDecrement(rx));
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

auto Disassembler::Line9Size7(const std::string& mnemonic, uint32_t opcode) -> std::string {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction(mnemonic, Dn(ry), An(rx));
        case 1u: return BinaryInstruction(mnemonic, An(ry), An(rx));
        case 2u: return BinaryInstruction(mnemonic, AnIndirect(ry), An(rx));
        case 3u: return BinaryInstruction(mnemonic, AnIncrement(ry), An(rx));
        case 4u: return BinaryInstruction(mnemonic, AnDecrement(ry), An(rx));
        case 5u: return BinaryInstruction(mnemonic, AnDisplacement(ry), An(rx));
        case 6u: return BinaryInstruction(mnemonic, AnIndex(ry), An(rx));
        case 7u:
            switch (ry) {
                case 0u: return BinaryInstruction(mnemonic, Short(), An(rx));
                case 1u: return BinaryInstruction(mnemonic, Long(), An(rx));
                case 2u: return BinaryInstruction(mnemonic, PCDisplacement(), An(rx));
                case 3u: return BinaryInstruction(mnemonic, PCIndex(), An(rx));
                case 4u: return BinaryInstruction(mnemonic, ImmediateLong(), An(rx));
                default:return {};
            }
        default:return {};
    }
}
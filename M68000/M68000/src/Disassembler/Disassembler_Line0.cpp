#include "M68000/DisassemblerImpl.h"
#include "M68000/M68000_Opcode.h"

using namespace rbrown::m68000;

auto Disassembler::Line0(uint32_t opcode) -> std::string {
    switch (OpcodeModeX(opcode)) {
        case 0u: return Line0Size0(opcode);
        case 1u: return Line0Size1(opcode);
        case 2u: return Line0Size2(opcode);
        case 3u: return Line0Size3(opcode);
        case 4u: return Line0Size4(opcode);
        case 5u: return Line0Size5(opcode);
        case 6u: return Line0Size6(opcode);
        case 7u: return Line0Size7(opcode);
        default:return {};
    }
}

auto Disassembler::Line0Size0(uint32_t opcode) -> std::string {
    switch (OpcodeRegisterX(opcode)) {
        case 0u: return Line0Size0Rx0("ORI.B",  opcode);
        case 1u: return Line0Size0Rx0("ANDI.B", opcode);
        case 2u: return Line0Size0Rx2("SUBI.B", opcode);
        case 3u: return Line0Size0Rx2("ADDI.B", opcode);
        case 4u: return Line0Size0Rx4(opcode); // BTST
        case 5u: return Line0Size0Rx0("EORI.B", opcode);
        case 6u: return Line0Size0Rx2("CMPI.B", opcode);
        default: return {};
    }
}

auto Disassembler::Line0Size0Rx0(const std::string& mnemonic, uint32_t opcode) -> std::string {
    const auto ry = OpcodeRegisterY(opcode);
    const auto immediate = ImmediateByte();
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction(mnemonic, immediate, Dn(ry));
        case 2u: return BinaryInstruction(mnemonic, immediate, AnIndirect(ry));
        case 3u: return BinaryInstruction(mnemonic, immediate, AnIncrement(ry));
        case 4u: return BinaryInstruction(mnemonic, immediate, AnDecrement(ry));
        case 5u: return BinaryInstruction(mnemonic, immediate, AnDisplacement(ry));
        case 6u: return BinaryInstruction(mnemonic, immediate, AnIndex(ry));
        case 7u:
            switch (ry) {
                case 0u: return BinaryInstruction(mnemonic, immediate, Short());
                case 1u: return BinaryInstruction(mnemonic, immediate, Long());
                case 4u: return BinaryInstruction(mnemonic, immediate, CONDITION_CODE_REGISTER);
                default:return {};
            }
        default:return {};
    }
}

auto Disassembler::Line0Size0Rx2(const std::string& mnemonic, uint32_t opcode) -> std::string {
    const auto ry = OpcodeRegisterY(opcode);
    const auto immediate = ImmediateByte();
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction(mnemonic, immediate, Dn(ry));
        case 2u: return BinaryInstruction(mnemonic, immediate, AnIndirect(ry));
        case 3u: return BinaryInstruction(mnemonic, immediate, AnIncrement(ry));
        case 4u: return BinaryInstruction(mnemonic, immediate, AnDecrement(ry));
        case 5u: return BinaryInstruction(mnemonic, immediate, AnDisplacement(ry));
        case 6u: return BinaryInstruction(mnemonic, immediate, AnIndex(ry));
        case 7u:
            switch (ry) {
                case 0u: return BinaryInstruction(mnemonic, immediate, Short());
                case 1u: return BinaryInstruction(mnemonic, immediate, Long());
                default:return {};
            }
        default:return {};
    }
}

auto Disassembler::Line0Size0Rx4(uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "BTST.B";
    const auto ry = OpcodeRegisterY(opcode);
    const auto immediate = ImmediateByte();
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction("BTST.L", immediate, Dn(ry));
        case 2u: return BinaryInstruction(mnemonic, immediate, AnIndirect(ry));
        case 3u: return BinaryInstruction(mnemonic, immediate, AnIncrement(ry));
        case 4u: return BinaryInstruction(mnemonic, immediate, AnDecrement(ry));
        case 5u: return BinaryInstruction(mnemonic, immediate, AnDisplacement(ry));
        case 6u: return BinaryInstruction(mnemonic, immediate, AnIndex(ry));
        case 7u:
            switch (ry) {
                case 0u: return BinaryInstruction(mnemonic, immediate, Short());
                case 1u: return BinaryInstruction(mnemonic, immediate, Long());
                case 2u: return BinaryInstruction(mnemonic, immediate, PCDisplacement());
                case 3u: return BinaryInstruction(mnemonic, immediate, PCIndex());
                default:return {};
            }
        default:return {};
    }
}

auto Disassembler::Line0Size1(uint32_t opcode) -> std::string {
    switch (OpcodeRegisterX(opcode)) {
        case 0u: return Line0Size1Rx0("ORI.W",  opcode);
        case 1u: return Line0Size1Rx0("ANDI.W", opcode);
        case 2u: return Line0Size1Rx2("SUBI.W", opcode);
        case 3u: return Line0Size1Rx2("ADDI.W", opcode);
        case 4u: return Line0Size1Rx4(opcode); // BCHG
        case 5u: return Line0Size1Rx0("EORI.W", opcode);
        case 6u: return Line0Size1Rx2("CMPI.W", opcode);
        default: return {};
    }
}

auto Disassembler::Line0Size1Rx0(const std::string& mnemonic, uint32_t opcode) -> std::string {
    const auto ry = OpcodeRegisterY(opcode);
    const auto immediate = ImmediateWord();
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction(mnemonic, immediate, Dn(ry));
        case 2u: return BinaryInstruction(mnemonic, immediate, AnIndirect(ry));
        case 3u: return BinaryInstruction(mnemonic, immediate, AnIncrement(ry));
        case 4u: return BinaryInstruction(mnemonic, immediate, AnDecrement(ry));
        case 5u: return BinaryInstruction(mnemonic, immediate, AnDisplacement(ry));
        case 6u: return BinaryInstruction(mnemonic, immediate, AnIndex(ry));
        case 7u:
            switch (ry) {
                case 0u: return BinaryInstruction(mnemonic, immediate, Short());
                case 1u: return BinaryInstruction(mnemonic, immediate, Long());
                case 4u: return BinaryInstruction(mnemonic, immediate, STATUS_REGISTER);
                default:return {};
            }
        default:return {};
    }
}

auto Disassembler::Line0Size1Rx2(const std::string& mnemonic, uint32_t opcode) -> std::string {
    const auto ry = OpcodeRegisterY(opcode);
    const auto immediate = ImmediateWord();
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction(mnemonic, immediate, Dn(ry));
        case 2u: return BinaryInstruction(mnemonic, immediate, AnIndirect(ry));
        case 3u: return BinaryInstruction(mnemonic, immediate, AnIncrement(ry));
        case 4u: return BinaryInstruction(mnemonic, immediate, AnDecrement(ry));
        case 5u: return BinaryInstruction(mnemonic, immediate, AnDisplacement(ry));
        case 6u: return BinaryInstruction(mnemonic, immediate, AnIndex(ry));
        case 7u:
            switch (ry) {
                case 0u: return BinaryInstruction(mnemonic, immediate, Short());
                case 1u: return BinaryInstruction(mnemonic, immediate, Long());
                default:return {};
            }
        default:return {};
    }
}

auto Disassembler::Line0Size1Rx4(uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "BCHG.B";
    const auto ry = OpcodeRegisterY(opcode);
    const auto immediate = ImmediateByte();
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction("BCHG.L", immediate, Dn(ry));
        case 2u: return BinaryInstruction(mnemonic, immediate, AnIndirect(ry));
        case 3u: return BinaryInstruction(mnemonic, immediate, AnIncrement(ry));
        case 4u: return BinaryInstruction(mnemonic, immediate, AnDecrement(ry));
        case 5u: return BinaryInstruction(mnemonic, immediate, AnDisplacement(ry));
        case 6u: return BinaryInstruction(mnemonic, immediate, AnIndex(ry));
        case 7u:
            switch (ry) {
                case 0u: return BinaryInstruction(mnemonic, immediate, Short());
                case 1u: return BinaryInstruction(mnemonic, immediate, Long());
                default:return {};
            }
        default:return {};
    }
}

auto Disassembler::Line0Size2(uint32_t opcode) -> std::string {
    switch (OpcodeRegisterX(opcode)) {
        case 0u: return Line0Size2Rx0("ORI.L",  opcode);
        case 1u: return Line0Size2Rx0("ANDI.L", opcode);
        case 2u: return Line0Size2Rx0("SUBI.L", opcode);
        case 3u: return Line0Size2Rx0("ADDI.L", opcode);
        case 4u: return Line0Size2Rx4(opcode); // BCLR
        case 5u: return Line0Size2Rx0("EORI.L", opcode);
        case 6u: return Line0Size2Rx0("CMPI.L", opcode);
        default: return {};
    }
}

auto Disassembler::Line0Size2Rx0(const std::string& mnemonic, uint32_t opcode) -> std::string {
    const auto ry = OpcodeRegisterY(opcode);
    const auto immediate = ImmediateLong();
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction(mnemonic, immediate, Dn(ry));
        case 2u: return BinaryInstruction(mnemonic, immediate, AnIndirect(ry));
        case 3u: return BinaryInstruction(mnemonic, immediate, AnIncrement(ry));
        case 4u: return BinaryInstruction(mnemonic, immediate, AnDecrement(ry));
        case 5u: return BinaryInstruction(mnemonic, immediate, AnDisplacement(ry));
        case 6u: return BinaryInstruction(mnemonic, immediate, AnIndex(ry));
        case 7u:
            switch (ry) {
                case 0u: return BinaryInstruction(mnemonic, immediate, Short());
                case 1u: return BinaryInstruction(mnemonic, immediate, Long());
                default:return {};
            }
        default:return {};
    }
}

auto Disassembler::Line0Size2Rx4(uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "BCLR.B";
    const auto ry = OpcodeRegisterY(opcode);
    const auto immediate = ImmediateByte();
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction("BCLR.L", immediate, Dn(ry));
        case 2u: return BinaryInstruction(mnemonic, immediate, AnIndirect(ry));
        case 3u: return BinaryInstruction(mnemonic, immediate, AnIncrement(ry));
        case 4u: return BinaryInstruction(mnemonic, immediate, AnDecrement(ry));
        case 5u: return BinaryInstruction(mnemonic, immediate, AnDisplacement(ry));
        case 6u: return BinaryInstruction(mnemonic, immediate, AnIndex(ry));
        case 7u:
            switch (ry) {
                case 0u: return BinaryInstruction(mnemonic, immediate, Short());
                case 1u: return BinaryInstruction(mnemonic, immediate, Long());
                default:return {};
            }
        default:return {};
    }
}

auto Disassembler::Line0Size3(uint32_t opcode) -> std::string {
    if (OpcodeRegisterX(opcode) == 4u) {
        return Line0Size3Rx4(opcode); // BSET
    }
    return {};
}

auto Disassembler::Line0Size3Rx4(uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "BSET.B";
    const auto ry = OpcodeRegisterY(opcode);
    const auto immediate = ImmediateByte();
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction("BSET.L", immediate, Dn(ry));
        case 2u: return BinaryInstruction(mnemonic, immediate, AnIndirect(ry));
        case 3u: return BinaryInstruction(mnemonic, immediate, AnIncrement(ry));
        case 4u: return BinaryInstruction(mnemonic, immediate, AnDecrement(ry));
        case 5u: return BinaryInstruction(mnemonic, immediate, AnDisplacement(ry));
        case 6u: return BinaryInstruction(mnemonic, immediate, AnIndex(ry));
        case 7u:
            switch (ry) {
                case 0u: return BinaryInstruction(mnemonic, immediate, Short());
                case 1u: return BinaryInstruction(mnemonic, immediate, Long());
                default:return {};
            }
        default:return {};
    }
}

auto Disassembler::Line0Size4(uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "BTST.B";
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction("BTST.L", Dn(rx), Dn(ry));
        case 1u: return BinaryInstruction("MOVEP.W", AnDisplacement(ry), Dn(rx));
        case 2u: return BinaryInstruction(mnemonic, Dn(rx), AnIndirect(ry));
        case 3u: return BinaryInstruction(mnemonic, Dn(rx), AnIncrement(ry));
        case 4u: return BinaryInstruction(mnemonic, Dn(rx), AnDecrement(ry));
        case 5u: return BinaryInstruction(mnemonic, Dn(rx), AnDisplacement(ry));
        case 6u: return BinaryInstruction(mnemonic, Dn(rx), AnIndex(ry));
        case 7u:
            switch (ry) {
                case 0u: return BinaryInstruction(mnemonic, Dn(rx), Short());
                case 1u: return BinaryInstruction(mnemonic, Dn(rx), Long());
                case 2u: return BinaryInstruction(mnemonic, Dn(rx), PCDisplacement());
                case 3u: return BinaryInstruction(mnemonic, Dn(rx), PCIndex());
                case 4u: return BinaryInstruction(mnemonic, Dn(rx), ImmediateByte());
                default:return {};
            }
        default:return {};
    }
}

auto Disassembler::Line0Size5(uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "BCHG.B";
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction("BCHG.L", Dn(rx), Dn(ry));
        case 1u: return BinaryInstruction("MOVEP.L", AnDisplacement(ry), Dn(rx));
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

auto Disassembler::Line0Size6(uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "BCLR.B";
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction("BCLR.L", Dn(rx), Dn(ry));
        case 1u: return BinaryInstruction("MOVEP.W", Dn(rx), AnDisplacement(ry));
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

auto Disassembler::Line0Size7(uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "BSET.B";
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction("BSET.L", Dn(rx), Dn(ry));
        case 1u: return BinaryInstruction("MOVEP.L", Dn(rx), AnDisplacement(ry));
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
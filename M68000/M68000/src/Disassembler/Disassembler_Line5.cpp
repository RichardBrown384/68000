#include "M68000/DisassemblerImpl.h"
#include "M68000/M68000_Opcode.h"

#include <array>

using namespace rbrown::m68000;

constexpr std::array SCC_CONDITION_MNEMONICS = {
    "T", "F", "HI", "LS",
    "CC", "CS", "NE", "EQ",
    "VC", "VS", "PL", "MI",
    "GE", "LT", "GT", "LE"
};

constexpr std::array DBCC_CONDITION_MNEMONICS = {
    "T", "RA", "HI", "LS",
    "CC", "CS", "NE", "EQ",
    "VC", "VS", "PL", "MI",
    "GE", "LT", "GT", "LE"
};

auto Disassembler::Line5(uint32_t opcode) -> std::string {
    switch (OpcodeModeX(opcode)) {
        case 0u: return Line5Size0("ADDQ.B", opcode);
        case 1u: return Line5Size1("ADDQ.W", opcode);
        case 2u: return Line5Size1("ADDQ.L", opcode);
        case 3u: return Line5Size3(opcode);
        case 4u: return Line5Size0("SUBQ.B", opcode);
        case 5u: return Line5Size1("SUBQ.W", opcode);
        case 6u: return Line5Size1("SUBQ.L", opcode);
        case 7u: return Line5Size3(opcode);
        default:return {};
    }
}

auto Disassembler::Line5Size0(const std::string& mnemonic, uint32_t opcode) -> std::string {
    const auto quick = OpcodeQuick(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction(mnemonic, Quick(quick), Dn(ry));
        case 2u: return BinaryInstruction(mnemonic, Quick(quick), AnIndirect(ry));
        case 3u: return BinaryInstruction(mnemonic, Quick(quick), AnIncrement(ry));
        case 4u: return BinaryInstruction(mnemonic, Quick(quick), AnDecrement(ry));
        case 5u: return BinaryInstruction(mnemonic, Quick(quick), AnDisplacement(ry));
        case 6u: return BinaryInstruction(mnemonic, Quick(quick), AnIndex(ry));
        case 7u:
            switch (ry) {
                case 0u: return BinaryInstruction(mnemonic, Quick(quick), Short());
                case 1u: return BinaryInstruction(mnemonic, Quick(quick), Long());
                default:return {};
            }
        default:return {};
    }
}

auto Disassembler::Line5Size1(const std::string& mnemonic, uint32_t opcode) -> std::string {
    const auto quick = OpcodeQuick(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction(mnemonic, Quick(quick), Dn(ry));
        case 1u: return BinaryInstruction(mnemonic, Quick(quick), An(ry));
        case 2u: return BinaryInstruction(mnemonic, Quick(quick), AnIndirect(ry));
        case 3u: return BinaryInstruction(mnemonic, Quick(quick), AnIncrement(ry));
        case 4u: return BinaryInstruction(mnemonic, Quick(quick), AnDecrement(ry));
        case 5u: return BinaryInstruction(mnemonic, Quick(quick), AnDisplacement(ry));
        case 6u: return BinaryInstruction(mnemonic, Quick(quick), AnIndex(ry));
        case 7u:
            switch (ry) {
                case 0u: return BinaryInstruction(mnemonic, Quick(quick), Short());
                case 1u: return BinaryInstruction(mnemonic, Quick(quick), Long());
                default:return {};
            }
        default:return {};
    }
}

auto Disassembler::Line5Size3(uint32_t opcode) -> std::string {
    const auto cc = SCC_CONDITION_MNEMONICS[OpcodeConditionCode(opcode)];
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return SetConditionInstruction(cc, Dn(ry));
        case 1u: return DecrementBranchInstruction(
            DBCC_CONDITION_MNEMONICS[OpcodeConditionCode(opcode)],
            Dn(ry),
            ReadNextWord());
        case 2u: return SetConditionInstruction(cc, AnIndirect(ry));
        case 3u: return SetConditionInstruction(cc, AnIncrement(ry));
        case 4u: return SetConditionInstruction(cc, AnDecrement(ry));
        case 5u: return SetConditionInstruction(cc, AnDisplacement(ry));
        case 6u: return SetConditionInstruction(cc, AnIndex(ry));
        case 7u:
            switch (ry) {
                case 0u: return SetConditionInstruction(cc, Short());
                case 1u: return SetConditionInstruction(cc, Long());
                default:return {};
            }
        default:return {};
    }
}
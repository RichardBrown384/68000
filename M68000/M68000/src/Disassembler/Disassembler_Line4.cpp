#include "M68000/DisassemblerImpl.h"
#include "M68000/M68000_Opcode.h"
#include "M68000/M68000_Int.h"

using namespace rbrown::m68000;

auto Disassembler::Line4(uint32_t opcode) -> std::string {
    switch (OpcodeModeX(opcode)) {
        case 0u: return Line4Size0(opcode);
        case 1u: return Line4Size1(opcode);
        case 2u: return Line4Size2(opcode);
        case 3u: return Line4Size3(opcode);
        case 6u: return Line4Size6(opcode);
        case 7u: return Line4Size7(opcode);
        default:return {};
    }
}

auto Disassembler::Line4Size0(uint32_t opcode) -> std::string {
    switch (OpcodeRegisterX(opcode)) {
        case 0u: return Line4Size0("NEGX.B", opcode);
        case 1u: return Line4Size0("CLR.B", opcode);
        case 2u: return Line4Size0("NEG.B", opcode);
        case 3u: return Line4Size0("NOT.B", opcode);
        case 4u: return Line4Size0("NBCD", opcode);
        case 5u: return Line4Size0("TST.B", opcode);
        default: return {};
    }
}

auto Disassembler::Line4Size0(const std::string& mnemonic, uint32_t opcode) -> std::string {
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return SingleInstruction(mnemonic, Dn(ry));
        case 2u: return SingleInstruction(mnemonic, AnIndirect(ry));
        case 3u: return SingleInstruction(mnemonic, AnIncrement(ry));
        case 4u: return SingleInstruction(mnemonic, AnDecrement(ry));
        case 5u: return SingleInstruction(mnemonic, AnDisplacement(ry));
        case 6u: return SingleInstruction(mnemonic, AnIndex(ry));
        case 7u:
            switch (ry) {
                case 0u: return SingleInstruction(mnemonic, Short());
                case 1u: return SingleInstruction(mnemonic, Long());
                default:return {};
            }
        default:return {};
    }
}

auto Disassembler::Line4Size1(uint32_t opcode) -> std::string {
    switch (OpcodeRegisterX(opcode)) {
        case 0u: return Line4Size0("NEGX.W", opcode);
        case 1u: return Line4Size0("CLR.W", opcode);
        case 2u: return Line4Size0("NEG.W", opcode);
        case 3u: return Line4Size0("NOT.W", opcode);
        case 4u: return Line4Size1Rx4(opcode); // PEA / SWAP
        case 5u: return Line4Size0("TST.W", opcode);
        case 7u: return Line4Size1Rx7(opcode); // TRAP / LINK / etc
        default: return {};
    }
}

auto Disassembler::Line4Size1Rx4(uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "PEA";
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return SingleInstruction("SWAP", Dn(ry));
        case 2u: return SingleInstruction(mnemonic, AnIndirect(ry));
        case 5u: return SingleInstruction(mnemonic, AnDisplacement(ry));
        case 6u: return SingleInstruction(mnemonic, AnIndex(ry));
        case 7u:
            switch (ry) {
                case 0u: return SingleInstruction(mnemonic, Short());
                case 1u: return SingleInstruction(mnemonic, Long());
                case 2u: return SingleInstruction(mnemonic, PCDisplacement());
                case 3u: return SingleInstruction(mnemonic, PCIndex());
                default:return {};
            }
        default:return {};
    }
}

auto Disassembler::Line4Size1Rx7(uint32_t opcode) -> std::string {
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u:
        case 1u: return SingleInstruction("TRAP", TrapVector(opcode));
        case 2u: return BinaryInstruction("LINK", An(ry), ImmediateWord());
        case 3u: return SingleInstruction("UNLK", An(ry));
        case 4u: return BinaryInstruction("MOVE.L", An(ry), "USP");
        case 5u: return BinaryInstruction("MOVE.L", "USP", An(ry));
        case 6u:
            switch (ry) {
                case 0u: return { "RESET" };
                case 1u: return { "NOP" };
                case 2u: return SingleInstruction("STOP", ImmediateWord());
                case 3u: return { "RTE" };
                case 5u: return { "RTS" };
                case 6u: return { "TRAPV" };
                case 7u: return { "RTR" };
                default: return {};
            }
        default:return {};
    }
}

auto Disassembler::Line4Size2(uint32_t opcode) -> std::string {
    switch (OpcodeRegisterX(opcode)) {
        case 0u: return Line4Size0("NEGX.L", opcode);
        case 1u: return Line4Size0("CLR.L", opcode);
        case 2u: return Line4Size0("NEG.L", opcode);
        case 3u: return Line4Size0("NOT.L", opcode);
        case 4u: return Line4Size2Rx4(opcode); // MOVEM.W <list>, <ea>
        case 5u: return Line4Size0("TST.L", opcode);
        case 6u: return Line4Size2Rx6(opcode); // MOVEM.W <ea>, <list>
        case 7u: return Line4Size2Rx7("JSR", opcode);
        default: return {};
    }
}

auto Disassembler::Line4Size2Rx4(uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "MOVEM.W";
    const auto my = OpcodeModeY(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    if (my == 0u) {
        return SingleInstruction("EXT.W", Dn(ry));
    }
    const auto word = ReadNextWord();
    const auto list = RegisterList((my == 4u) ? Reverse16(word) : word);
    switch (my) {
        case 2u: return BinaryInstruction(mnemonic, list, AnIndirect(ry));
        case 4u: return BinaryInstruction(mnemonic, list, AnDecrement(ry));
        case 5u: return BinaryInstruction(mnemonic, list, AnDisplacement(ry));
        case 6u: return BinaryInstruction(mnemonic, list, AnIndex(ry));
        case 7u:
            switch (ry) {
                case 0u: return BinaryInstruction(mnemonic, list, Short());
                case 1u: return BinaryInstruction(mnemonic, list, Long());
                default:return {};
            }
        default:return {};
    }
}

auto Disassembler::Line4Size2Rx6(uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "MOVEM.W";
    const auto my = OpcodeModeY(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto list = RegisterList(ReadNextWord());
    switch (my) {
        case 2u: return BinaryInstruction(mnemonic, AnIndirect(ry), list);
        case 3u: return BinaryInstruction(mnemonic, AnIncrement(ry), list);
        case 5u: return BinaryInstruction(mnemonic, AnDisplacement(ry), list);
        case 6u: return BinaryInstruction(mnemonic, AnIndex(ry), list);
        case 7u:
            switch (ry) {
                case 0u: return BinaryInstruction(mnemonic, Short(), list);
                case 1u: return BinaryInstruction(mnemonic, Long(), list);
                case 2u: return BinaryInstruction(mnemonic, PCDisplacement(), list);
                case 3u: return BinaryInstruction(mnemonic, PCIndex(), list);
                default:return {};
            }
        default:return {};
    }
}

auto Disassembler::Line4Size2Rx7(const std::string& mnemonic, uint32_t opcode) -> std::string {
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 2u: return SingleInstruction(mnemonic, AnIndirect(ry));
        case 5u: return SingleInstruction(mnemonic, AnDisplacement(ry));
        case 6u: return SingleInstruction(mnemonic, AnIndex(ry));
        case 7u:
            switch (ry) {
                case 0u: return SingleInstruction(mnemonic, Short());
                case 1u: return SingleInstruction(mnemonic, Long());
                case 2u: return SingleInstruction(mnemonic, PCDisplacement());
                case 3u: return SingleInstruction(mnemonic, PCIndex());
                default:return {};
            }
        default:return {};
    }
}

auto Disassembler::Line4Size3(uint32_t opcode) -> std::string {
    switch (OpcodeRegisterX(opcode)) {
        case 0u: return Line4Size3Rx0(opcode); // MOVE.W SR, <ea>
        case 2u: return Line4Size3Rx2(CONDITION_CODE_REGISTER, opcode); // MOVE.W <ea>, CCR
        case 3u: return Line4Size3Rx2(STATUS_REGISTER, opcode); // MOVE.W <ea>, SR
        case 4u: return Line4Size3Rx4(opcode); // MOVEM.L <list>, <ea>
        case 5u: return Line4Size3Rx5(opcode); // TAS
        case 6u: return Line4Size3Rx6(opcode); // MOVEM.L <ea>, <list>
        case 7u: return Line4Size2Rx7("JMP", opcode);
        default: return {};
    }
}

auto Disassembler::Line4Size3Rx0(const uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "MOVE.W";
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction(mnemonic, STATUS_REGISTER, Dn(ry));
        case 2u: return BinaryInstruction(mnemonic, STATUS_REGISTER, AnIndirect(ry));
        case 3u: return BinaryInstruction(mnemonic, STATUS_REGISTER, AnIncrement(ry));
        case 4u: return BinaryInstruction(mnemonic, STATUS_REGISTER, AnDecrement(ry));
        case 5u: return BinaryInstruction(mnemonic, STATUS_REGISTER, AnDisplacement(ry));
        case 6u: return BinaryInstruction(mnemonic, STATUS_REGISTER, AnIndex(ry));
        case 7u:
            switch (ry) {
                case 0u: return BinaryInstruction(mnemonic, STATUS_REGISTER, Short());
                case 1u: return BinaryInstruction(mnemonic, STATUS_REGISTER, Long());
                default: return {};
            }
        default: return {};
    }
}

auto Disassembler::Line4Size3Rx2(const std::string& d, uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "MOVE.W";
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction(mnemonic, Dn(ry), d);
        case 2u: return BinaryInstruction(mnemonic, AnIndirect(ry), d);
        case 3u: return BinaryInstruction(mnemonic, AnIncrement(ry), d);
        case 4u: return BinaryInstruction(mnemonic, AnDecrement(ry), d);
        case 5u: return BinaryInstruction(mnemonic, AnDisplacement(ry), d);
        case 6u: return BinaryInstruction(mnemonic, AnIndex(ry), d);
        case 7u:
            switch (ry) {
                case 0u: return BinaryInstruction(mnemonic, Short(), d);
                case 1u: return BinaryInstruction(mnemonic, Long(), d);
                case 2u: return BinaryInstruction(mnemonic, PCDisplacement(), d);
                case 3u: return BinaryInstruction(mnemonic, PCIndex(), d);
                case 4u: return BinaryInstruction(mnemonic, ImmediateWord(), d);
                default: return {};
            }
        default: return {};
    }
}

auto Disassembler::Line4Size3Rx4(uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "MOVEM.L";
    const auto my = OpcodeModeY(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    if (my == 0u) {
        return SingleInstruction("EXT.L", Dn(ry));
    }
    const auto word = ReadNextWord();
    const auto list = RegisterList((my == 4u) ? Reverse16(word) : word);
    switch (OpcodeModeY(opcode)) {
        case 2u: return BinaryInstruction(mnemonic, list, AnIndirect(ry));
        case 4u: return BinaryInstruction(mnemonic, list, AnDecrement(ry));
        case 5u: return BinaryInstruction(mnemonic, list, AnDisplacement(ry));
        case 6u: return BinaryInstruction(mnemonic, list, AnIndex(ry));
        case 7u:
            switch (ry) {
                case 0u: return BinaryInstruction(mnemonic, list, Short());
                case 1u: return BinaryInstruction(mnemonic, list, Long());
                default: return {};
            }
        default: return {};
    }
}

auto Disassembler::Line4Size3Rx5(uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "TAS";
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return SingleInstruction(mnemonic, Dn(ry));
        case 2u: return SingleInstruction(mnemonic, AnIndirect(ry));
        case 3u: return SingleInstruction(mnemonic, AnIncrement(ry));
        case 4u: return SingleInstruction(mnemonic, AnDecrement(ry));
        case 5u: return SingleInstruction(mnemonic, AnDisplacement(ry));
        case 6u: return SingleInstruction(mnemonic, AnIndex(ry));
        case 7u:
            switch (ry) {
                case 0u: return SingleInstruction(mnemonic, Short());
                case 1u: return SingleInstruction(mnemonic, Long());
                case 4u: return { "ILLEGAL" };
                default:return {};
            }
        default:return {};
    }
}

auto Disassembler::Line4Size3Rx6(uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "MOVEM.L";
    const auto my = OpcodeModeY(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto list = RegisterList(ReadNextWord());
    switch (my) {
        case 2u: return BinaryInstruction(mnemonic, AnIndirect(ry), list);
        case 3u: return BinaryInstruction(mnemonic, AnIncrement(ry), list);
        case 5u: return BinaryInstruction(mnemonic, AnDisplacement(ry), list);
        case 6u: return BinaryInstruction(mnemonic, AnIndex(ry), list);
        case 7u:
            switch (ry) {
                case 0u: return BinaryInstruction(mnemonic, Short(), list);
                case 1u: return BinaryInstruction(mnemonic, Long(), list);
                case 2u: return BinaryInstruction(mnemonic, PCDisplacement(), list);
                case 3u: return BinaryInstruction(mnemonic, PCIndex(), list);
                default:return {};
            }
        default:return {};
    }
}

auto Disassembler::Line4Size6(uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "CHK";
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

auto Disassembler::Line4Size7(uint32_t opcode) -> std::string {
    static constexpr auto mnemonic = "LEA";
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 2u: return BinaryInstruction(mnemonic, AnIndirect(ry), An(rx));
        case 5u: return BinaryInstruction(mnemonic, AnDisplacement(ry), An(rx));
        case 6u: return BinaryInstruction(mnemonic, AnIndex(ry), An(rx));
        case 7u:
            switch (ry) {
                case 0u: return BinaryInstruction(mnemonic, Short(), An(rx));
                case 1u: return BinaryInstruction(mnemonic, Long(), An(rx));
                case 2u: return BinaryInstruction(mnemonic, PCDisplacement(), An(rx));
                case 3u: return BinaryInstruction(mnemonic, PCIndex(), An(rx));
                default:return {};
            }
        default:return {};
    }
}
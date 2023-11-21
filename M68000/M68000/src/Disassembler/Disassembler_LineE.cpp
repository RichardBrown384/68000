#include "M68000/DisassemblerImpl.h"
#include "M68000/M68000_Opcode.h"

using namespace rbrown::m68000;

auto Disassembler::LineE(uint32_t opcode) -> std::string {
    switch (OpcodeModeX(opcode)) {
        case 0u: return LineESize0(opcode);
        case 1u: return LineESize1(opcode);
        case 2u: return LineESize2(opcode);
        case 3u: return LineESize3(opcode);
        case 4u: return LineESize4(opcode);
        case 5u: return LineESize5(opcode);
        case 6u: return LineESize6(opcode);
        case 7u: return LineESize7(opcode);
        default: return {};
    }
}

auto Disassembler::LineESize0(uint32_t opcode) -> std::string {
    const auto quick = OpcodeQuick(opcode);
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction("ASR.B", Quick(quick), Dn(ry));
        case 1u: return BinaryInstruction("LSR.B", Quick(quick), Dn(ry));
        case 2u: return BinaryInstruction("ROXR.B", Quick(quick), Dn(ry));
        case 3u: return BinaryInstruction("ROR.B", Quick(quick), Dn(ry));
        case 4u: return BinaryInstruction("ASR.B", Dn(rx), Dn(ry));
        case 5u: return BinaryInstruction("LSR.B", Dn(rx), Dn(ry));
        case 6u: return BinaryInstruction("ROXR.B", Dn(rx), Dn(ry));
        case 7u: return BinaryInstruction("ROR.B", Dn(rx), Dn(ry));
        default: return {};
    }
}

auto Disassembler::LineESize1(uint32_t opcode) -> std::string {
    const auto quick = OpcodeQuick(opcode);
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction("ASR.W", Quick(quick), Dn(ry));
        case 1u: return BinaryInstruction("LSR.W", Quick(quick), Dn(ry));
        case 2u: return BinaryInstruction("ROXR.W", Quick(quick), Dn(ry));
        case 3u: return BinaryInstruction("ROR.W", Quick(quick), Dn(ry));
        case 4u: return BinaryInstruction("ASR.W", Dn(rx), Dn(ry));
        case 5u: return BinaryInstruction("LSR.W", Dn(rx), Dn(ry));
        case 6u: return BinaryInstruction("ROXR.W", Dn(rx), Dn(ry));
        case 7u: return BinaryInstruction("ROR.W", Dn(rx), Dn(ry));
        default: return {};
    }
}

auto Disassembler::LineESize2(uint32_t opcode) -> std::string {
    const auto quick = OpcodeQuick(opcode);
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction("ASR.L", Quick(quick), Dn(ry));
        case 1u: return BinaryInstruction("LSR.L", Quick(quick), Dn(ry));
        case 2u: return BinaryInstruction("ROXR.L", Quick(quick), Dn(ry));
        case 3u: return BinaryInstruction("ROR.L", Quick(quick), Dn(ry));
        case 4u: return BinaryInstruction("ASR.L", Dn(rx), Dn(ry));
        case 5u: return BinaryInstruction("LSR.L", Dn(rx), Dn(ry));
        case 6u: return BinaryInstruction("ROXR.L", Dn(rx), Dn(ry));
        case 7u: return BinaryInstruction("ROR.L", Dn(rx), Dn(ry));
        default: return {};
    }
}

auto Disassembler::LineESize3(uint32_t opcode) -> std::string {
    switch (OpcodeRegisterX(opcode)) {
        case 0u: return LineESize3("ASR.W", opcode);
        case 1u: return LineESize3("LSR.W", opcode);
        case 2u: return LineESize3("ROXR.W", opcode);
        case 3u: return LineESize3("ROR.W", opcode);
        default: return {};
    }
}

auto Disassembler::LineESize3(const std::string& mnemonic, uint32_t opcode) -> std::string {
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 2u: return SingleInstruction(mnemonic, AnIndirect(ry));
        case 3u: return SingleInstruction(mnemonic, AnIncrement(ry));
        case 4u: return SingleInstruction(mnemonic, AnDecrement(ry));
        case 5u: return SingleInstruction(mnemonic, AnDisplacement(ry));
        case 6u: return SingleInstruction(mnemonic, AnIndex(ry));
        case 7u: switch (ry) {
            case 0u: return SingleInstruction(mnemonic, Short());
            case 1u: return SingleInstruction(mnemonic, Long());
            default: return {};
        }
        default: return {};
    }
}

auto Disassembler::LineESize4(uint32_t opcode) -> std::string {
    const auto quick = OpcodeQuick(opcode);
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction("ASL.B", Quick(quick), Dn(ry));
        case 1u: return BinaryInstruction("LSL.B", Quick(quick), Dn(ry));
        case 2u: return BinaryInstruction("ROXL.B", Quick(quick), Dn(ry));
        case 3u: return BinaryInstruction("ROL.B", Quick(quick), Dn(ry));
        case 4u: return BinaryInstruction("ASL.B", Dn(rx), Dn(ry));
        case 5u: return BinaryInstruction("LSL.B", Dn(rx), Dn(ry));
        case 6u: return BinaryInstruction("ROXL.B", Dn(rx), Dn(ry));
        case 7u: return BinaryInstruction("ROL.B", Dn(rx), Dn(ry));
        default: return {};
    }
}

auto Disassembler::LineESize5(uint32_t opcode) -> std::string {
    const auto quick = OpcodeQuick(opcode);
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction("ASL.W", Quick(quick), Dn(ry));
        case 1u: return BinaryInstruction("LSL.W", Quick(quick), Dn(ry));
        case 2u: return BinaryInstruction("ROXL.W", Quick(quick), Dn(ry));
        case 3u: return BinaryInstruction("ROL.W", Quick(quick), Dn(ry));
        case 4u: return BinaryInstruction("ASL.W", Dn(rx), Dn(ry));
        case 5u: return BinaryInstruction("LSL.W", Dn(rx), Dn(ry));
        case 6u: return BinaryInstruction("ROXL.W", Dn(rx), Dn(ry));
        case 7u: return BinaryInstruction("ROL.W", Dn(rx), Dn(ry));
        default: return {};
    }
}

auto Disassembler::LineESize6(uint32_t opcode) -> std::string {
    const auto quick = OpcodeQuick(opcode);
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    switch (OpcodeModeY(opcode)) {
        case 0u: return BinaryInstruction("ASL.L", Quick(quick), Dn(ry));
        case 1u: return BinaryInstruction("LSL.L", Quick(quick), Dn(ry));
        case 2u: return BinaryInstruction("ROXL.L", Quick(quick), Dn(ry));
        case 3u: return BinaryInstruction("ROL.L", Quick(quick), Dn(ry));
        case 4u: return BinaryInstruction("ASL.L", Dn(rx), Dn(ry));
        case 5u: return BinaryInstruction("LSL.L", Dn(rx), Dn(ry));
        case 6u: return BinaryInstruction("ROXL.L", Dn(rx), Dn(ry));
        case 7u: return BinaryInstruction("ROL.L", Dn(rx), Dn(ry));
        default: return {};
    }
}

auto Disassembler::LineESize7(uint32_t opcode) -> std::string {
    switch (OpcodeRegisterX(opcode)) {
        case 0u: return LineESize3("ASL.W", opcode);
        case 1u: return LineESize3("LSL.W", opcode);
        case 2u: return LineESize3("ROXL.W", opcode);
        case 3u: return LineESize3("ROL.W", opcode);
        default: return {};
    }
}

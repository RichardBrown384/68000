#include "M68000/DisassemblerImpl.h"
#include "M68000/M68000_Opcode.h"

#include <array>

using namespace rbrown::m68000;

constexpr std::array BCC_CONDITION_MNEMONICS = {
    "RA", "SR", "HI", "LS",
    "CC", "CS", "NE", "EQ",
    "VC", "VS", "PL", "MI",
    "GE", "LT", "GT", "LE"
};

auto Disassembler::Line6(uint32_t opcode) -> std::string {
    const auto cc = BCC_CONDITION_MNEMONICS[OpcodeConditionCode(opcode)];
    const auto displacement = OpcodeBranchDisplacement(opcode);
    const auto size = displacement ? "B": "W";
    const auto disp = displacement ? displacement : ReadNextWord();
    return BranchInstruction(cc, size, disp);
}
#pragma once

#include <cstdint>

namespace rbrown::m68000 {

constexpr auto OpcodeLine(uint32_t opcode) {
    return (opcode >> 12u) & 0xFu;
}

constexpr auto OpcodeRegisterX(uint32_t opcode) {
    return (opcode >> 9u) & 0x7u;
}

constexpr auto OpcodeModeX(uint32_t opcode) {
    return (opcode >> 6u) & 0x7u;
}

constexpr auto OpcodeModeY(uint32_t opcode) {
    return (opcode >> 3u) & 0x7u;
}

constexpr auto OpcodeRegisterY(uint32_t opcode) {
    return opcode & 0x7u;
}

constexpr auto OpcodeConditionCode(uint32_t opcode) {
    return (opcode >> 8u) & 0xFu;
}

constexpr auto OpcodeQuick(uint32_t opcode) {
    return 1u + (((opcode >> 9u) + 7u) & 7u);
}

constexpr auto OpcodeBranchDisplacement(uint32_t opcode) {
    return ((opcode & 0xFFu) ^ 0x80u) - 0x80u;
}

constexpr auto OpcodeTrapVector(uint32_t opcode) {
    return opcode & 0xFu;
}

constexpr auto ExtensionWordAddress(uint32_t word) {
    return (word >> 15u) & 0x1u;
}

constexpr auto ExtensionWordRegister(uint32_t word) {
    return (word >> 12u) & 0x7u;
}

constexpr auto ExtensionWordLong(uint32_t word) {
    return (word >> 11u) & 0x1u;
}

constexpr auto ExtensionWordDisplacement(uint32_t word) {
    return word & 0xFFu;
}

}
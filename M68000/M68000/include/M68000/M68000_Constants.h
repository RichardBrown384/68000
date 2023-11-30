#pragma once

// Status register fields

constexpr auto FLAG_T = 0x8000u;
constexpr auto FLAG_S = 0x2000u;
constexpr auto FLAG_X = 0x0010u;
constexpr auto FLAG_N = 0x0008u;
constexpr auto FLAG_Z = 0x0004u;
constexpr auto FLAG_V = 0x0002u;
constexpr auto FLAG_C = 0x0001u;

// Condition codes

constexpr auto CONDITION_CODE_T = 0x0u;
constexpr auto CONDITION_CODE_F = 0x1u;
constexpr auto CONDITION_CODE_HI = 0x2u;
constexpr auto CONDITION_CODE_LS = 0x3u;
constexpr auto CONDITION_CODE_CC = 0x4u;
constexpr auto CONDITION_CODE_CS = 0x5u;
constexpr auto CONDITION_CODE_NE = 0x6u;
constexpr auto CONDITION_CODE_EQ = 0x7u;
constexpr auto CONDITION_CODE_VC = 0x8u;
constexpr auto CONDITION_CODE_VS = 0x9u;
constexpr auto CONDITION_CODE_PL = 0xAu;
constexpr auto CONDITION_CODE_MI = 0xBu;
constexpr auto CONDITION_CODE_GE = 0xCu;
constexpr auto CONDITION_CODE_LT = 0xDu;
constexpr auto CONDITION_CODE_GT = 0xEu;
constexpr auto CONDITION_CODE_LE = 0xFu;

// Exception vectors
constexpr auto VECTOR_RESET_STACK_POINTER = 0x000u;
constexpr auto VECTOR_RESET_PROGRAM_COUNTER = 0x004u;
constexpr auto VECTOR_BUS_ERROR = 0x008u;
constexpr auto VECTOR_ADDRESS_ERROR = 0x00C;
constexpr auto VECTOR_ILLEGAL_INSTRUCTION = 0x010u;
constexpr auto VECTOR_ZERO_DIVIDE = 0x014u;
constexpr auto VECTOR_CHK_INSTRUCTION = 0x018u;
constexpr auto VECTOR_TRAPV_INSTRUCTION = 0x01Cu;
constexpr auto VECTOR_PRIVILEGE_VIOLATION = 0x020u;
constexpr auto VECTOR_TRACE = 0x024u;
constexpr auto VECTOR_LINE_1010_EMULATOR = 0x028u;
constexpr auto VECTOR_LINE_1111_EMULATOR = 0x02Cu;

constexpr auto VECTOR_TRAP_BASE = 0x0080u;
#include "M68000/Fixtures/M68000Test.h"

constexpr auto Encode(uint32_t op, uint32_t rx, uint32_t mx, uint32_t my, uint32_t ry) {
    return (op << 12u) + (rx << 9u) + (mx << 6u) + (my << 3u) + (ry);
}

constexpr auto VALUES = {

    Encode(0xEu, 0u, 3u, 0u, 4u), // ASR D4
    Encode(0xEu, 0u, 3u, 1u, 4u), // ASR A4
    Encode(0xEu, 0u, 3u, 7u, 2u), // ASR <>
    Encode(0xEu, 0u, 3u, 7u, 3u), // ASR <>
    Encode(0xEu, 0u, 3u, 7u, 4u), // ASR <>
    Encode(0xEu, 0u, 3u, 7u, 5u), // ASR <>
    Encode(0xEu, 0u, 3u, 7u, 6u), // ASR <>
    Encode(0xEu, 0u, 3u, 7u, 7u), // ASR <>

    Encode(0xEu, 1u, 3u, 0u, 4u), // LSR D4
    Encode(0xEu, 1u, 3u, 1u, 4u), // LSR A4
    Encode(0xEu, 1u, 3u, 7u, 2u), // LSR <>
    Encode(0xEu, 1u, 3u, 7u, 3u), // LSR <>
    Encode(0xEu, 1u, 3u, 7u, 4u), // LSR <>
    Encode(0xEu, 1u, 3u, 7u, 5u), // LSR <>
    Encode(0xEu, 1u, 3u, 7u, 6u), // LSR <>
    Encode(0xEu, 1u, 3u, 7u, 7u), // LSR <>

    Encode(0xEu, 2u, 3u, 0u, 4u), // ROXR D4
    Encode(0xEu, 2u, 3u, 1u, 4u), // ROXR A4
    Encode(0xEu, 2u, 3u, 7u, 2u), // ROXR <>
    Encode(0xEu, 2u, 3u, 7u, 3u), // ROXR <>
    Encode(0xEu, 2u, 3u, 7u, 4u), // ROXR <>
    Encode(0xEu, 2u, 3u, 7u, 5u), // ROXR <>
    Encode(0xEu, 2u, 3u, 7u, 6u), // ROXR <>
    Encode(0xEu, 2u, 3u, 7u, 7u), // ROXR <>

    Encode(0xEu, 3u, 3u, 0u, 4u), // ROR D4
    Encode(0xEu, 3u, 3u, 1u, 4u), // ROR A4
    Encode(0xEu, 3u, 3u, 7u, 2u), // ROR <>
    Encode(0xEu, 3u, 3u, 7u, 3u), // ROR <>
    Encode(0xEu, 3u, 3u, 7u, 4u), // ROR <>
    Encode(0xEu, 3u, 3u, 7u, 5u), // ROR <>
    Encode(0xEu, 3u, 3u, 7u, 6u), // ROR <>
    Encode(0xEu, 3u, 3u, 7u, 7u), // ROR <>

    Encode(0xEu, 4u, 3u, 0u, 4u), // Undef D4
    Encode(0xEu, 4u, 3u, 1u, 4u), // Undef A4
    Encode(0xEu, 4u, 3u, 2u, 4u), // Undef (A4)
    Encode(0xEu, 4u, 3u, 3u, 4u), // Undef (A4)+
    Encode(0xEu, 4u, 3u, 4u, 4u), // Undef -(A4)
    Encode(0xEu, 4u, 3u, 5u, 4u), // Undef (d16, A4)
    Encode(0xEu, 4u, 3u, 5u, 4u), // Undef (d8, A4, Xn)
    Encode(0xEu, 4u, 3u, 7u, 0u), // Undef (XXX).W
    Encode(0xEu, 4u, 3u, 7u, 1u), // Undef (XXX).L
    Encode(0xEu, 4u, 3u, 7u, 2u), // Undef (d16, PC)
    Encode(0xEu, 4u, 3u, 7u, 3u), // Undef (d8, PC, Xn)
    Encode(0xEu, 4u, 3u, 7u, 4u), // Undef #imm
    Encode(0xEu, 4u, 3u, 7u, 5u), // Undef <>
    Encode(0xEu, 4u, 3u, 7u, 6u), // Undef <>
    Encode(0xEu, 4u, 3u, 7u, 7u), // Undef <>

    Encode(0xEu, 5u, 3u, 0u, 4u), // Undef D4
    Encode(0xEu, 5u, 3u, 1u, 4u), // Undef A4
    Encode(0xEu, 5u, 3u, 2u, 4u), // Undef (A4)
    Encode(0xEu, 5u, 3u, 3u, 4u), // Undef (A4)+
    Encode(0xEu, 5u, 3u, 4u, 4u), // Undef -(A4)
    Encode(0xEu, 5u, 3u, 5u, 4u), // Undef (d16, A4)
    Encode(0xEu, 5u, 3u, 5u, 4u), // Undef (d8, A4, Xn)
    Encode(0xEu, 5u, 3u, 7u, 0u), // Undef (XXX).W
    Encode(0xEu, 5u, 3u, 7u, 1u), // Undef (XXX).L
    Encode(0xEu, 5u, 3u, 7u, 2u), // Undef (d16, PC)
    Encode(0xEu, 5u, 3u, 7u, 3u), // Undef (d8, PC, Xn)
    Encode(0xEu, 5u, 3u, 7u, 4u), // Undef #imm
    Encode(0xEu, 5u, 3u, 7u, 5u), // Undef <>
    Encode(0xEu, 5u, 3u, 7u, 6u), // Undef <>
    Encode(0xEu, 5u, 3u, 7u, 7u), // Undef <>

    Encode(0xEu, 6u, 3u, 0u, 4u), // Undef D4
    Encode(0xEu, 6u, 3u, 1u, 4u), // Undef A4
    Encode(0xEu, 6u, 3u, 2u, 4u), // Undef (A4)
    Encode(0xEu, 6u, 3u, 3u, 4u), // Undef (A4)+
    Encode(0xEu, 6u, 3u, 4u, 4u), // Undef -(A4)
    Encode(0xEu, 6u, 3u, 5u, 4u), // Undef (d16, A4)
    Encode(0xEu, 6u, 3u, 5u, 4u), // Undef (d8, A4, Xn)
    Encode(0xEu, 6u, 3u, 7u, 0u), // Undef (XXX).W
    Encode(0xEu, 6u, 3u, 7u, 1u), // Undef (XXX).L
    Encode(0xEu, 6u, 3u, 7u, 2u), // Undef (d16, PC)
    Encode(0xEu, 6u, 3u, 7u, 3u), // Undef (d8, PC, Xn)
    Encode(0xEu, 6u, 3u, 7u, 4u), // Undef #imm
    Encode(0xEu, 6u, 3u, 7u, 5u), // Undef <>
    Encode(0xEu, 6u, 3u, 7u, 6u), // Undef <>
    Encode(0xEu, 6u, 3u, 7u, 7u), // Undef <>

    Encode(0xEu, 7u, 3u, 0u, 4u), // Undef D4
    Encode(0xEu, 7u, 3u, 1u, 4u), // Undef A4
    Encode(0xEu, 7u, 3u, 2u, 4u), // Undef (A4)
    Encode(0xEu, 7u, 3u, 3u, 4u), // Undef (A4)+
    Encode(0xEu, 7u, 3u, 4u, 4u), // Undef -(A4)
    Encode(0xEu, 7u, 3u, 5u, 4u), // Undef (d16, A4)
    Encode(0xEu, 7u, 3u, 5u, 4u), // Undef (d8, A4, Xn)
    Encode(0xEu, 7u, 3u, 7u, 0u), // Undef (XXX).W
    Encode(0xEu, 7u, 3u, 7u, 1u), // Undef (XXX).L
    Encode(0xEu, 7u, 3u, 7u, 2u), // Undef (d16, PC)
    Encode(0xEu, 7u, 3u, 7u, 3u), // Undef (d8, PC, Xn)
    Encode(0xEu, 7u, 3u, 7u, 4u), // Undef #imm
    Encode(0xEu, 7u, 3u, 7u, 5u), // Undef <>
    Encode(0xEu, 7u, 3u, 7u, 6u), // Undef <>
    Encode(0xEu, 7u, 3u, 7u, 7u), // Undef <>

    Encode(0xEu, 0u, 7u, 0u, 4u), // ASL D4
    Encode(0xEu, 0u, 7u, 1u, 4u), // ASL A4
    Encode(0xEu, 0u, 7u, 7u, 2u), // ASL <>
    Encode(0xEu, 0u, 7u, 7u, 3u), // ASL <>
    Encode(0xEu, 0u, 7u, 7u, 4u), // ASL <>
    Encode(0xEu, 0u, 7u, 7u, 5u), // ASL <>
    Encode(0xEu, 0u, 7u, 7u, 6u), // ASL <>
    Encode(0xEu, 0u, 7u, 7u, 7u), // ASL <>

    Encode(0xEu, 1u, 7u, 0u, 4u), // LSL D4
    Encode(0xEu, 1u, 7u, 1u, 4u), // LSL A4
    Encode(0xEu, 1u, 7u, 7u, 2u), // LSL <>
    Encode(0xEu, 1u, 7u, 7u, 3u), // LSL <>
    Encode(0xEu, 1u, 7u, 7u, 4u), // LSL <>
    Encode(0xEu, 1u, 7u, 7u, 5u), // LSL <>
    Encode(0xEu, 1u, 7u, 7u, 6u), // LSL <>
    Encode(0xEu, 1u, 7u, 7u, 7u), // LSL <>

    Encode(0xEu, 2u, 7u, 0u, 4u), // ROLR D4
    Encode(0xEu, 2u, 7u, 1u, 4u), // ROLR A4
    Encode(0xEu, 2u, 7u, 7u, 2u), // ROLR <>
    Encode(0xEu, 2u, 7u, 7u, 3u), // ROLR <>
    Encode(0xEu, 2u, 7u, 7u, 4u), // ROLR <>
    Encode(0xEu, 2u, 7u, 7u, 5u), // ROLR <>
    Encode(0xEu, 2u, 7u, 7u, 6u), // ROLR <>
    Encode(0xEu, 2u, 7u, 7u, 7u), // ROLR <>

    Encode(0xEu, 3u, 7u, 0u, 4u), // ROL D4
    Encode(0xEu, 3u, 7u, 1u, 4u), // ROL A4
    Encode(0xEu, 3u, 7u, 7u, 2u), // ROL <>
    Encode(0xEu, 3u, 7u, 7u, 3u), // ROL <>
    Encode(0xEu, 3u, 7u, 7u, 4u), // ROL <>
    Encode(0xEu, 3u, 7u, 7u, 5u), // ROL <>
    Encode(0xEu, 3u, 7u, 7u, 6u), // ROL <>
    Encode(0xEu, 3u, 7u, 7u, 7u), // ROL <>

    Encode(0xEu, 4u, 7u, 0u, 4u), // Undef D4
    Encode(0xEu, 4u, 7u, 1u, 4u), // Undef A4
    Encode(0xEu, 4u, 7u, 2u, 4u), // Undef (A4)
    Encode(0xEu, 4u, 7u, 3u, 4u), // Undef (A4)+
    Encode(0xEu, 4u, 7u, 4u, 4u), // Undef -(A4)
    Encode(0xEu, 4u, 7u, 5u, 4u), // Undef (d16, A4)
    Encode(0xEu, 4u, 7u, 5u, 4u), // Undef (d8, A4, Xn)
    Encode(0xEu, 4u, 7u, 7u, 0u), // Undef (XXX).W
    Encode(0xEu, 4u, 7u, 7u, 1u), // Undef (XXX).L
    Encode(0xEu, 4u, 7u, 7u, 2u), // Undef (d16, PC)
    Encode(0xEu, 4u, 7u, 7u, 3u), // Undef (d8, PC, Xn)
    Encode(0xEu, 4u, 7u, 7u, 4u), // Undef #imm
    Encode(0xEu, 4u, 7u, 7u, 5u), // Undef <>
    Encode(0xEu, 4u, 7u, 7u, 6u), // Undef <>
    Encode(0xEu, 4u, 7u, 7u, 7u), // Undef <>

    Encode(0xEu, 5u, 7u, 0u, 4u), // Undef D4
    Encode(0xEu, 5u, 7u, 1u, 4u), // Undef A4
    Encode(0xEu, 5u, 7u, 2u, 4u), // Undef (A4)
    Encode(0xEu, 5u, 7u, 3u, 4u), // Undef (A4)+
    Encode(0xEu, 5u, 7u, 4u, 4u), // Undef -(A4)
    Encode(0xEu, 5u, 7u, 5u, 4u), // Undef (d16, A4)
    Encode(0xEu, 5u, 7u, 5u, 4u), // Undef (d8, A4, Xn)
    Encode(0xEu, 5u, 7u, 7u, 0u), // Undef (XXX).W
    Encode(0xEu, 5u, 7u, 7u, 1u), // Undef (XXX).L
    Encode(0xEu, 5u, 7u, 7u, 2u), // Undef (d16, PC)
    Encode(0xEu, 5u, 7u, 7u, 3u), // Undef (d8, PC, Xn)
    Encode(0xEu, 5u, 7u, 7u, 4u), // Undef #imm
    Encode(0xEu, 5u, 7u, 7u, 5u), // Undef <>
    Encode(0xEu, 5u, 7u, 7u, 6u), // Undef <>
    Encode(0xEu, 5u, 7u, 7u, 7u), // Undef <>

    Encode(0xEu, 6u, 7u, 0u, 4u), // Undef D4
    Encode(0xEu, 6u, 7u, 1u, 4u), // Undef A4
    Encode(0xEu, 6u, 7u, 2u, 4u), // Undef (A4)
    Encode(0xEu, 6u, 7u, 3u, 4u), // Undef (A4)+
    Encode(0xEu, 6u, 7u, 4u, 4u), // Undef -(A4)
    Encode(0xEu, 6u, 7u, 5u, 4u), // Undef (d16, A4)
    Encode(0xEu, 6u, 7u, 5u, 4u), // Undef (d8, A4, Xn)
    Encode(0xEu, 6u, 7u, 7u, 0u), // Undef (XXX).W
    Encode(0xEu, 6u, 7u, 7u, 1u), // Undef (XXX).L
    Encode(0xEu, 6u, 7u, 7u, 2u), // Undef (d16, PC)
    Encode(0xEu, 6u, 7u, 7u, 3u), // Undef (d8, PC, Xn)
    Encode(0xEu, 6u, 7u, 7u, 4u), // Undef #imm
    Encode(0xEu, 6u, 7u, 7u, 5u), // Undef <>
    Encode(0xEu, 6u, 7u, 7u, 6u), // Undef <>
    Encode(0xEu, 6u, 7u, 7u, 7u), // Undef <>

    Encode(0xEu, 7u, 7u, 0u, 4u), // Undef D4
    Encode(0xEu, 7u, 7u, 1u, 4u), // Undef A4
    Encode(0xEu, 7u, 7u, 2u, 4u), // Undef (A4)
    Encode(0xEu, 7u, 7u, 3u, 4u), // Undef (A4)+
    Encode(0xEu, 7u, 7u, 4u, 4u), // Undef -(A4)
    Encode(0xEu, 7u, 7u, 5u, 4u), // Undef (d16, A4)
    Encode(0xEu, 7u, 7u, 5u, 4u), // Undef (d8, A4, Xn)
    Encode(0xEu, 7u, 7u, 7u, 0u), // Undef (XXX).W
    Encode(0xEu, 7u, 7u, 7u, 1u), // Undef (XXX).L
    Encode(0xEu, 7u, 7u, 7u, 2u), // Undef (d16, PC)
    Encode(0xEu, 7u, 7u, 7u, 3u), // Undef (d8, PC, Xn)
    Encode(0xEu, 7u, 7u, 7u, 4u), // Undef #imm
    Encode(0xEu, 7u, 7u, 7u, 5u), // Undef <>
    Encode(0xEu, 7u, 7u, 7u, 6u), // Undef <>
    Encode(0xEu, 7u, 7u, 7u, 7u), // Undef <>

};

class LineEIllegalInstructionTest: public M68000Test, public ::testing::WithParamInterface<uint32_t> {};

TEST_P(LineEIllegalInstructionTest, IllegalInstructionPattern) {
    const auto illegal = GetParam();
    Given({
        "SR is 0,0,XC",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "(0x10).L is 0x00ADBCBC",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        illegal
    });
    Then({
        "SR is S,0,XC",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "PC is 0x00ADBCBC",
        "(0x10).L is 0x00ADBCBC",
        "(0x00FFFFFA).W is 0x0011",
        "(0x00FFFFFC).L is 0x00001002",
        "CYCLES is 34"
    });
}

INSTANTIATE_TEST_SUITE_P(
   IllegalLineEInstructionPatterns,
   LineEIllegalInstructionTest,
   ::testing::ValuesIn(VALUES)
);

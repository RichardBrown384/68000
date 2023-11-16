#include "M68000/Fixtures/M68000Test.h"

constexpr auto Encode(uint32_t op, uint32_t rx, uint32_t mx, uint32_t my, uint32_t ry) {
    return (op << 12u) + (rx << 9u) + (mx << 6u) + (my << 3u) + (ry);
}

constexpr auto VALUES = {

    Encode(0xDu, 4u, 0u, 1u, 5u), // ADD.B A5, D4
    Encode(0xDu, 4u, 0u, 7u, 5u), // ADD.B <>, D4
    Encode(0xDu, 4u, 0u, 7u, 6u), // ADD.B <>, D4
    Encode(0xDu, 4u, 0u, 7u, 7u), // ADD.B <>, D4

    Encode(0xDu, 4u, 1u, 7u, 5u), // ADD.W <>, D4
    Encode(0xDu, 4u, 1u, 7u, 6u), // ADD.W <>, D4
    Encode(0xDu, 4u, 1u, 7u, 7u), // ADD.W <>, D4

    Encode(0xDu, 4u, 2u, 7u, 5u), // ADD.L <>, D4
    Encode(0xDu, 4u, 2u, 7u, 6u), // ADD.L <>, D4
    Encode(0xDu, 4u, 2u, 7u, 7u), // ADD.L <>, D4

    Encode(0xDu, 4u, 3u, 7u, 5u), // ADDA.W <>, A4
    Encode(0xDu, 4u, 3u, 7u, 6u), // ADDA.W <>, A4
    Encode(0xDu, 4u, 3u, 7u, 7u), // ADDA.W <>, A4

    Encode(0xDu, 4u, 4u, 7u, 2u), // ADD.B D4, <>
    Encode(0xDu, 4u, 4u, 7u, 3u), // ADD.B D4, <>
    Encode(0xDu, 4u, 4u, 7u, 4u), // ADD.B D4, <>
    Encode(0xDu, 4u, 4u, 7u, 5u), // ADD.B D4, <>
    Encode(0xDu, 4u, 4u, 7u, 6u), // ADD.B D4, <>
    Encode(0xDu, 4u, 4u, 7u, 7u), // ADD.B D4, <>

    Encode(0xDu, 4u, 5u, 7u, 2u), // ADD.W D4, <>
    Encode(0xDu, 4u, 5u, 7u, 3u), // ADD.W D4, <>
    Encode(0xDu, 4u, 5u, 7u, 4u), // ADD.W D4, <>
    Encode(0xDu, 4u, 5u, 7u, 5u), // ADD.W D4, <>
    Encode(0xDu, 4u, 5u, 7u, 6u), // ADD.W D4, <>
    Encode(0xDu, 4u, 5u, 7u, 7u), // ADD.W D4, <>

    Encode(0xDu, 4u, 6u, 7u, 2u), // ADD.L D4, <>
    Encode(0xDu, 4u, 6u, 7u, 3u), // ADD.L D4, <>
    Encode(0xDu, 4u, 6u, 7u, 4u), // ADD.L D4, <>
    Encode(0xDu, 4u, 6u, 7u, 5u), // ADD.L D4, <>
    Encode(0xDu, 4u, 6u, 7u, 6u), // ADD.L D4, <>
    Encode(0xDu, 4u, 6u, 7u, 7u), // ADD.L D4, <>

    Encode(0xDu, 4u, 7u, 7u, 5u), // ADDA.L <>, A4
    Encode(0xDu, 4u, 7u, 7u, 6u), // ADDA.L <>, A4
    Encode(0xDu, 4u, 7u, 7u, 7u), // ADDA.L <>, A4
};

class LineDIllegalInstructionTest: public M68000Test, public ::testing::WithParamInterface<uint32_t> {};

TEST_P(LineDIllegalInstructionTest, IllegalInstructionPattern) {
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
   IllegalLineDInstructionPatterns,
   LineDIllegalInstructionTest,
   ::testing::ValuesIn(VALUES)
);

#include "M68000/Fixtures/M68000Test.h"

constexpr auto Encode(uint32_t op, uint32_t rx, uint32_t mx, uint32_t my, uint32_t ry) {
    return (op << 12u) + (rx << 9u) + (mx << 6u) + (my << 3u) + (ry);
}

constexpr auto VALUES = {

    Encode(0xCu, 4u, 0u, 1u, 5u), // AND.B A5, D4
    Encode(0xCu, 4u, 0u, 7u, 5u), // AND.B <>, D4
    Encode(0xCu, 4u, 0u, 7u, 6u), // AND.B <>, D4
    Encode(0xCu, 4u, 0u, 7u, 7u), // AND.B <>, D4

    Encode(0xCu, 4u, 1u, 1u, 5u), // AND.W A5, D4
    Encode(0xCu, 4u, 1u, 7u, 5u), // AND.W <>, D4
    Encode(0xCu, 4u, 1u, 7u, 6u), // AND.W <>, D4
    Encode(0xCu, 4u, 1u, 7u, 7u), // AND.W <>, D4

    Encode(0xCu, 4u, 2u, 1u, 5u), // AND.L A5, D4
    Encode(0xCu, 4u, 2u, 7u, 5u), // AND.L <>, D4
    Encode(0xCu, 4u, 2u, 7u, 6u), // AND.L <>, D4
    Encode(0xCu, 4u, 2u, 7u, 7u), // AND.L <>, D4

    Encode(0xCu, 4u, 3u, 1u, 5u), // MULU A5, D4
    Encode(0xCu, 4u, 3u, 7u, 5u), // MULU <>, D4
    Encode(0xCu, 4u, 3u, 7u, 6u), // MULU <>, D4
    Encode(0xCu, 4u, 3u, 7u, 7u), // MULU <>, D4

    Encode(0xCu, 4u, 4u, 7u, 2u), // AND.B D4, <>
    Encode(0xCu, 4u, 4u, 7u, 3u), // AND.B D4, <>
    Encode(0xCu, 4u, 4u, 7u, 4u), // AND.B D4, <>
    Encode(0xCu, 4u, 4u, 7u, 5u), // AND.B D4, <>
    Encode(0xCu, 4u, 4u, 7u, 6u), // AND.B D4, <>
    Encode(0xCu, 4u, 4u, 7u, 7u), // AND.B D4, <>

    Encode(0xCu, 4u, 5u, 7u, 2u), // AND.W D4, <>
    Encode(0xCu, 4u, 5u, 7u, 3u), // AND.W D4, <>
    Encode(0xCu, 4u, 5u, 7u, 4u), // AND.W D4, <>
    Encode(0xCu, 4u, 5u, 7u, 5u), // AND.W D4, <>
    Encode(0xCu, 4u, 5u, 7u, 6u), // AND.W D4, <>
    Encode(0xCu, 4u, 5u, 7u, 7u), // AND.W D4, <>

    Encode(0xCu, 4u, 6u, 0u, 5u), // AND.L D4, <>
    Encode(0xCu, 4u, 6u, 7u, 2u), // AND.L D4, <>
    Encode(0xCu, 4u, 6u, 7u, 3u), // AND.L D4, <>
    Encode(0xCu, 4u, 6u, 7u, 4u), // AND.L D4, <>
    Encode(0xCu, 4u, 6u, 7u, 5u), // AND.L D4, <>
    Encode(0xCu, 4u, 6u, 7u, 6u), // AND.L D4, <>
    Encode(0xCu, 4u, 6u, 7u, 7u), // AND.L D4, <>

    Encode(0xCu, 4u, 7u, 1u, 5u), // MULS A5, D4
    Encode(0xCu, 4u, 7u, 7u, 5u), // MULS <>, D4
    Encode(0xCu, 4u, 7u, 7u, 6u), // MULS <>, D4
    Encode(0xCu, 4u, 7u, 7u, 7u), // MULS <>, D4

};

class LineCIllegalInstructionTest: public M68000Test, public ::testing::WithParamInterface<uint32_t> {};

TEST_P(LineCIllegalInstructionTest, IllegalInstructionPattern) {
    const auto illegal = GetParam();
    Given({
        "SR is 0,0,XC",
        "PC is 0x1000",
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
        "PC is 0x00ADBCBC",
        "CYCLES is 34",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "(0x10).L is 0x00ADBCBC",
        "(0x00FFFFFA).W is 0x0011",
        "(0x00FFFFFC).L is 0x00001002",
    });
}

INSTANTIATE_TEST_SUITE_P(
   IllegalLineCInstructionPatterns,
   LineCIllegalInstructionTest,
   ::testing::ValuesIn(VALUES)
);

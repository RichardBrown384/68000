#include "M68000/Fixtures/M68000Test.h"

constexpr auto Encode(uint32_t op, uint32_t rx, uint32_t mx, uint32_t my, uint32_t ry) {
    return (op << 12u) + (rx << 9u) + (mx << 6u) + (my << 3u) + (ry);
}

constexpr auto VALUES = {

    Encode(0x8u, 4u, 0u, 1u, 5u), // OR.B A5, D4
    Encode(0x8u, 4u, 0u, 7u, 5u), // OR.B <>, D4
    Encode(0x8u, 4u, 0u, 7u, 6u), // OR.B <>, D4
    Encode(0x8u, 4u, 0u, 7u, 7u), // OR.B <>, D4

    Encode(0x8u, 4u, 1u, 1u, 5u), // OR.W A5, D4
    Encode(0x8u, 4u, 1u, 7u, 5u), // OR.W <>, D4
    Encode(0x8u, 4u, 1u, 7u, 6u), // OR.W <>, D4
    Encode(0x8u, 4u, 1u, 7u, 7u), // OR.W <>, D4

    Encode(0x8u, 4u, 2u, 1u, 5u), // OR.L A5, D4
    Encode(0x8u, 4u, 2u, 7u, 5u), // OR.L <>, D4
    Encode(0x8u, 4u, 2u, 7u, 6u), // OR.L <>, D4
    Encode(0x8u, 4u, 2u, 7u, 7u), // OR.L <>, D4

    Encode(0x8u, 4u, 3u, 1u, 5u), // DIVU.L A5, D4
    Encode(0x8u, 4u, 3u, 7u, 5u), // DIVU.L <>, D4
    Encode(0x8u, 4u, 3u, 7u, 6u), // DIVU.L <>, D4
    Encode(0x8u, 4u, 3u, 7u, 7u), // DIVU.L <>, D4

    Encode(0x8u, 4u, 4u, 7u, 2u), // OR.B D4, <>
    Encode(0x8u, 4u, 4u, 7u, 3u), // OR.B D4, <>
    Encode(0x8u, 4u, 4u, 7u, 4u), // OR.B D4, <>
    Encode(0x8u, 4u, 4u, 7u, 5u), // OR.B D4, <>
    Encode(0x8u, 4u, 4u, 7u, 6u), // OR.B D4, <>
    Encode(0x8u, 4u, 4u, 7u, 7u), // OR.B D4, <>

    Encode(0x8u, 4u, 5u, 0u, 5u), // OR.W D4, <D5>
    Encode(0x8u, 4u, 5u, 1u, 5u), // OR.W D4, <A5>
    Encode(0x8u, 4u, 5u, 7u, 2u), // OR.W D4, <>
    Encode(0x8u, 4u, 5u, 7u, 3u), // OR.W D4, <>
    Encode(0x8u, 4u, 5u, 7u, 4u), // OR.W D4, <>
    Encode(0x8u, 4u, 5u, 7u, 5u), // OR.W D4, <>
    Encode(0x8u, 4u, 5u, 7u, 6u), // OR.W D4, <>
    Encode(0x8u, 4u, 5u, 7u, 7u), // OR.W D4, <>

    Encode(0x8u, 4u, 6u, 0u, 5u), // OR.L D4, <D5>
    Encode(0x8u, 4u, 6u, 1u, 5u), // OR.L D4, <A5>
    Encode(0x8u, 4u, 6u, 7u, 2u), // OR.L D4, <>
    Encode(0x8u, 4u, 6u, 7u, 3u), // OR.L D4, <>
    Encode(0x8u, 4u, 6u, 7u, 4u), // OR.L D4, <>
    Encode(0x8u, 4u, 6u, 7u, 5u), // OR.L D4, <>
    Encode(0x8u, 4u, 6u, 7u, 6u), // OR.L D4, <>
    Encode(0x8u, 4u, 6u, 7u, 7u), // OR.L D4, <>

    Encode(0x8u, 4u, 7u, 1u, 5u), // DIVS.L A5, D4
    Encode(0x8u, 4u, 7u, 7u, 5u), // DIVS.L <>, D4
    Encode(0x8u, 4u, 7u, 7u, 6u), // DIVS.L <>, D4
    Encode(0x8u, 4u, 7u, 7u, 7u), // DIVS.L <>, D4

};

class Line8IllegalInstructionTest: public M68000Test, public ::testing::WithParamInterface<uint32_t> {};

TEST_P(Line8IllegalInstructionTest, IllegalInstructionPattern) {
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
   IllegalLine8InstructionPatterns,
   Line8IllegalInstructionTest,
   ::testing::ValuesIn(VALUES)
);

#include "M68000/Fixtures/M68000Test.h"

constexpr auto Encode(uint32_t op, uint32_t rx, uint32_t mx, uint32_t my, uint32_t ry) {
    return (op << 12u) + (rx << 9u) + (mx << 6u) + (my << 3u) + (ry);
}

constexpr auto VALUES = {

    Encode(0x9u, 4u, 0u, 1u, 5u), // SUB.B A5, D4
    Encode(0x9u, 4u, 0u, 7u, 5u), // SUB.B <>, D4
    Encode(0x9u, 4u, 0u, 7u, 6u), // SUB.B <>, D4
    Encode(0x9u, 4u, 0u, 7u, 7u), // SUB.B <>, D4

    Encode(0x9u, 4u, 1u, 7u, 5u), // SUB.W <>, D4
    Encode(0x9u, 4u, 1u, 7u, 6u), // SUB.W <>, D4
    Encode(0x9u, 4u, 1u, 7u, 7u), // SUB.W <>, D4

    Encode(0x9u, 4u, 2u, 7u, 5u), // SUB.L <>, D4
    Encode(0x9u, 4u, 2u, 7u, 6u), // SUB.L <>, D4
    Encode(0x9u, 4u, 2u, 7u, 7u), // SUB.L <>, D4

    Encode(0x9u, 4u, 3u, 7u, 5u), // SUBA.W <>, A4
    Encode(0x9u, 4u, 3u, 7u, 6u), // SUBA.W <>, A4
    Encode(0x9u, 4u, 3u, 7u, 7u), // SUBA.W <>, A4

    Encode(0x9u, 4u, 4u, 7u, 2u), // SUB.B D4, <>
    Encode(0x9u, 4u, 4u, 7u, 3u), // SUB.B D4, <>
    Encode(0x9u, 4u, 4u, 7u, 4u), // SUB.B D4, <>
    Encode(0x9u, 4u, 4u, 7u, 5u), // SUB.B D4, <>
    Encode(0x9u, 4u, 4u, 7u, 6u), // SUB.B D4, <>
    Encode(0x9u, 4u, 4u, 7u, 7u), // SUB.B D4, <>

    Encode(0x9u, 4u, 5u, 7u, 2u), // SUB.W D4, <>
    Encode(0x9u, 4u, 5u, 7u, 3u), // SUB.W D4, <>
    Encode(0x9u, 4u, 5u, 7u, 4u), // SUB.W D4, <>
    Encode(0x9u, 4u, 5u, 7u, 5u), // SUB.W D4, <>
    Encode(0x9u, 4u, 5u, 7u, 6u), // SUB.W D4, <>
    Encode(0x9u, 4u, 5u, 7u, 7u), // SUB.W D4, <>

    Encode(0x9u, 4u, 6u, 7u, 2u), // SUB.L D4, <>
    Encode(0x9u, 4u, 6u, 7u, 3u), // SUB.L D4, <>
    Encode(0x9u, 4u, 6u, 7u, 4u), // SUB.L D4, <>
    Encode(0x9u, 4u, 6u, 7u, 5u), // SUB.L D4, <>
    Encode(0x9u, 4u, 6u, 7u, 6u), // SUB.L D4, <>
    Encode(0x9u, 4u, 6u, 7u, 7u), // SUB.L D4, <>

    Encode(0x9u, 4u, 7u, 7u, 5u), // SUBA.L <>, A4
    Encode(0x9u, 4u, 7u, 7u, 6u), // SUBA.L <>, A4
    Encode(0x9u, 4u, 7u, 7u, 7u), // SUBA.L <>, A4

};

class Line9IllegalInstructionTest: public M68000Test, public ::testing::WithParamInterface<uint32_t> {};

TEST_P(Line9IllegalInstructionTest, IllegalInstructionPattern) {
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
   IllegalLine9InstructionPatterns,
   Line9IllegalInstructionTest,
   ::testing::ValuesIn(VALUES)
);

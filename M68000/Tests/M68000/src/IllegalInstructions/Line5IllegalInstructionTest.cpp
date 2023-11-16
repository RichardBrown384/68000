#include "M68000/Fixtures/M68000Test.h"

constexpr auto Encode(uint32_t op, uint32_t rx, uint32_t mx, uint32_t my, uint32_t ry) {
    return (op << 12u) + (rx << 9u) + (mx << 6u) + (my << 3u) + (ry);
}

constexpr auto VALUES = {

    Encode(0x5u, 4u, 0u, 1u, 5u), // ADDQ.B #4, A5
    Encode(0x5u, 4u, 0u, 7u, 2u), // ADDQ.B #4, <>
    Encode(0x5u, 4u, 0u, 7u, 3u), // ADDQ.B #4, <>
    Encode(0x5u, 4u, 0u, 7u, 4u), // ADDQ.B #4, <>
    Encode(0x5u, 4u, 0u, 7u, 5u), // ADDQ.B #4, <>
    Encode(0x5u, 4u, 0u, 7u, 6u), // ADDQ.B #4, <>
    Encode(0x5u, 4u, 0u, 7u, 7u), // ADDQ.B #4, <>

    Encode(0x5u, 4u, 1u, 7u, 2u), // ADDQ.W #4, <>
    Encode(0x5u, 4u, 1u, 7u, 3u), // ADDQ.W #4, <>
    Encode(0x5u, 4u, 1u, 7u, 4u), // ADDQ.W #4, <>
    Encode(0x5u, 4u, 1u, 7u, 5u), // ADDQ.W #4, <>
    Encode(0x5u, 4u, 1u, 7u, 6u), // ADDQ.W #4, <>
    Encode(0x5u, 4u, 1u, 7u, 7u), // ADDQ.W #4, <>

    Encode(0x5u, 4u, 2u, 7u, 2u), // ADDQ.L #4, <>
    Encode(0x5u, 4u, 2u, 7u, 3u), // ADDQ.L #4, <>
    Encode(0x5u, 4u, 2u, 7u, 4u), // ADDQ.L #4, <>
    Encode(0x5u, 4u, 2u, 7u, 5u), // ADDQ.L #4, <>
    Encode(0x5u, 4u, 2u, 7u, 6u), // ADDQ.L #4, <>
    Encode(0x5u, 4u, 2u, 7u, 7u), // ADDQ.L #4, <>

    Encode(0x5u, 0u, 3u, 7u, 2u), // Scc <>
    Encode(0x5u, 0u, 3u, 7u, 3u), // Scc <>
    Encode(0x5u, 0u, 3u, 7u, 4u), // Scc <>
    Encode(0x5u, 0u, 3u, 7u, 5u), // Scc <>
    Encode(0x5u, 0u, 3u, 7u, 6u), // Scc <>
    Encode(0x5u, 0u, 3u, 7u, 7u), // Scc <>

    Encode(0x5u, 4u, 4u, 1u, 5u), // SUBQ.B #4, A5
    Encode(0x5u, 4u, 4u, 7u, 2u), // SUBQ.B #4, <>
    Encode(0x5u, 4u, 4u, 7u, 3u), // SUBQ.B #4, <>
    Encode(0x5u, 4u, 4u, 7u, 4u), // SUBQ.B #4, <>
    Encode(0x5u, 4u, 4u, 7u, 5u), // SUBQ.B #4, <>
    Encode(0x5u, 4u, 4u, 7u, 6u), // SUBQ.B #4, <>
    Encode(0x5u, 4u, 4u, 7u, 7u), // SUBQ.B #4, <>

    Encode(0x5u, 4u, 5u, 7u, 2u), // SUBQ.W #4, <>
    Encode(0x5u, 4u, 5u, 7u, 3u), // SUBQ.W #4, <>
    Encode(0x5u, 4u, 5u, 7u, 4u), // SUBQ.W #4, <>
    Encode(0x5u, 4u, 5u, 7u, 5u), // SUBQ.W #4, <>
    Encode(0x5u, 4u, 5u, 7u, 6u), // SUBQ.W #4, <>
    Encode(0x5u, 4u, 5u, 7u, 7u), // SUBQ.W #4, <>

    Encode(0x5u, 4u, 6u, 7u, 2u), // SUBQ.L #4, <>
    Encode(0x5u, 4u, 6u, 7u, 3u), // SUBQ.L #4, <>
    Encode(0x5u, 4u, 6u, 7u, 4u), // SUBQ.L #4, <>
    Encode(0x5u, 4u, 6u, 7u, 5u), // SUBQ.L #4, <>
    Encode(0x5u, 4u, 6u, 7u, 6u), // SUBQ.L #4, <>
    Encode(0x5u, 4u, 6u, 7u, 7u), // SUBQ.L #4, <>

    Encode(0x5u, 0u, 7u, 7u, 2u), // Scc <>
    Encode(0x5u, 0u, 7u, 7u, 3u), // Scc <>
    Encode(0x5u, 0u, 7u, 7u, 4u), // Scc <>
    Encode(0x5u, 0u, 7u, 7u, 5u), // Scc <>
    Encode(0x5u, 0u, 7u, 7u, 6u), // Scc <>
    Encode(0x5u, 0u, 7u, 7u, 7u), // Scc <>

};

class Line5IllegalInstructionTest: public M68000Test, public ::testing::WithParamInterface<uint32_t> {};

TEST_P(Line5IllegalInstructionTest, IllegalInstructionPattern) {
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
   IllegalLine5InstructionPatterns,
   Line5IllegalInstructionTest,
   ::testing::ValuesIn(VALUES)
);

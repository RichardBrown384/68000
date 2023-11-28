#include "M68000/Fixtures/M68000Test.h"

constexpr auto Encode(uint32_t op, uint32_t rx, uint32_t mx, uint32_t my, uint32_t ry) {
    return (op << 12u) + (rx << 9u) + (mx << 6u) + (my << 3u) + (ry);
}

constexpr auto VALUES = {

    Encode(0xBu, 4u, 0u, 1u, 5u), // CMP.B A5, D4
    Encode(0xBu, 4u, 0u, 7u, 5u), // CMP.B <>, D4
    Encode(0xBu, 4u, 0u, 7u, 6u), // CMP.B <>, D4
    Encode(0xBu, 4u, 0u, 7u, 7u), // CMP.B <>, D4

    Encode(0xBu, 4u, 1u, 7u, 5u), // CMP.W <>, D4
    Encode(0xBu, 4u, 1u, 7u, 6u), // CMP.W <>, D4
    Encode(0xBu, 4u, 1u, 7u, 7u), // CMP.W <>, D4

    Encode(0xBu, 4u, 2u, 7u, 5u), // CMP.L <>, D4
    Encode(0xBu, 4u, 2u, 7u, 6u), // CMP.L <>, D4
    Encode(0xBu, 4u, 2u, 7u, 7u), // CMP.L <>, D4

    Encode(0xBu, 4u, 3u, 7u, 5u), // CMPA.W <>, A4
    Encode(0xBu, 4u, 3u, 7u, 6u), // CMPA.W <>, A4
    Encode(0xBu, 4u, 3u, 7u, 7u), // CMPA.W <>, A4

    Encode(0xBu, 4u, 4u, 7u, 2u), // EOR.B D4, <>
    Encode(0xBu, 4u, 4u, 7u, 3u), // EOR.B D4, <>
    Encode(0xBu, 4u, 4u, 7u, 4u), // EOR.B D4, <>
    Encode(0xBu, 4u, 4u, 7u, 5u), // EOR.B D4, <>
    Encode(0xBu, 4u, 4u, 7u, 6u), // EOR.B D4, <>
    Encode(0xBu, 4u, 4u, 7u, 7u), // EOR.B D4, <>

    Encode(0xBu, 4u, 5u, 7u, 2u), // EOR.W D4, <>
    Encode(0xBu, 4u, 5u, 7u, 3u), // EOR.W D4, <>
    Encode(0xBu, 4u, 5u, 7u, 4u), // EOR.W D4, <>
    Encode(0xBu, 4u, 5u, 7u, 5u), // EOR.W D4, <>
    Encode(0xBu, 4u, 5u, 7u, 6u), // EOR.W D4, <>
    Encode(0xBu, 4u, 5u, 7u, 7u), // EOR.W D4, <>

    Encode(0xBu, 4u, 6u, 7u, 2u), // EOR.L D4, <>
    Encode(0xBu, 4u, 6u, 7u, 3u), // EOR.L D4, <>
    Encode(0xBu, 4u, 6u, 7u, 4u), // EOR.L D4, <>
    Encode(0xBu, 4u, 6u, 7u, 5u), // EOR.L D4, <>
    Encode(0xBu, 4u, 6u, 7u, 6u), // EOR.L D4, <>
    Encode(0xBu, 4u, 6u, 7u, 7u), // EOR.L D4, <>

    Encode(0xBu, 4u, 7u, 7u, 5u), // CMPA.L <>, A4
    Encode(0xBu, 4u, 7u, 7u, 6u), // CMPA.L <>, A4
    Encode(0xBu, 4u, 7u, 7u, 7u), // CMPA.L <>, A4

};

class LineBIllegalInstructionTest: public M68000Test, public ::testing::WithParamInterface<uint32_t> {};

TEST_P(LineBIllegalInstructionTest, IllegalInstructionPattern) {
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
   IllegalLineBInstructionPatterns,
   LineBIllegalInstructionTest,
   ::testing::ValuesIn(VALUES)
);

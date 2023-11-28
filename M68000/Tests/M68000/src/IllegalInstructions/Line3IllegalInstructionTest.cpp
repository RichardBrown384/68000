#include "M68000/Fixtures/M68000Test.h"

constexpr auto Encode(uint32_t op, uint32_t rx, uint32_t mx, uint32_t my, uint32_t ry) {
    return (op << 12u) + (rx << 9u) + (mx << 6u) + (my << 3u) + (ry);
}

constexpr auto VALUES = {
        
    Encode(0x3u, 2u, 7u, 0u, 4u), // MOVE.W D4, <>
    Encode(0x3u, 3u, 7u, 0u, 4u), // MOVE.W D4, <>
    Encode(0x3u, 4u, 7u, 0u, 4u), // MOVE.W D4, <>
    Encode(0x3u, 5u, 7u, 0u, 4u), // MOVE.W D4, <>
    Encode(0x3u, 6u, 7u, 0u, 4u), // MOVE.W D4, <>
    Encode(0x3u, 7u, 7u, 0u, 4u), // MOVE.W D4, <>
    
    Encode(0x3u, 2u, 7u, 1u, 5u), // MOVE.W A5, <>
    Encode(0x3u, 3u, 7u, 1u, 5u), // MOVE.W A5, <>
    Encode(0x3u, 4u, 7u, 1u, 5u), // MOVE.W A5, <>
    Encode(0x3u, 5u, 7u, 1u, 5u), // MOVE.W A5, <>
    Encode(0x3u, 6u, 7u, 1u, 5u), // MOVE.W A5, <>
    Encode(0x3u, 7u, 7u, 1u, 5u), // MOVE.W A5, <>
    
    Encode(0x3u, 2u, 7u, 2u, 4u), // MOVE.W (A4), <>
    Encode(0x3u, 3u, 7u, 2u, 4u), // MOVE.W (A4), <>
    Encode(0x3u, 4u, 7u, 2u, 4u), // MOVE.W (A4), <>
    Encode(0x3u, 5u, 7u, 2u, 4u), // MOVE.W (A4), <>
    Encode(0x3u, 6u, 7u, 2u, 4u), // MOVE.W (A4), <>
    Encode(0x3u, 7u, 7u, 2u, 4u), // MOVE.W (A4), <>
    
    Encode(0x3u, 2u, 7u, 3u, 4u), // MOVE.W (A4)+, <>
    Encode(0x3u, 3u, 7u, 3u, 4u), // MOVE.W (A4)+, <>
    Encode(0x3u, 4u, 7u, 3u, 4u), // MOVE.W (A4)+, <>
    Encode(0x3u, 5u, 7u, 3u, 4u), // MOVE.W (A4)+, <>
    Encode(0x3u, 6u, 7u, 3u, 4u), // MOVE.W (A4)+, <>
    Encode(0x3u, 7u, 7u, 3u, 4u), // MOVE.W (A4)+, <>
    
    Encode(0x3u, 2u, 7u, 4u, 4u), // MOVE.W -(A4), <>
    Encode(0x3u, 3u, 7u, 4u, 4u), // MOVE.W -(A4), <>
    Encode(0x3u, 4u, 7u, 4u, 4u), // MOVE.W -(A4), <>
    Encode(0x3u, 5u, 7u, 4u, 4u), // MOVE.W -(A4), <>
    Encode(0x3u, 6u, 7u, 4u, 4u), // MOVE.W -(A4), <>
    Encode(0x3u, 7u, 7u, 4u, 4u), // MOVE.W -(A4), <>

    Encode(0x3u, 2u, 7u, 5u, 4u), // MOVE.W (d16, A4), <>
    Encode(0x3u, 3u, 7u, 5u, 4u), // MOVE.W (d16, A4), <>
    Encode(0x3u, 4u, 7u, 5u, 4u), // MOVE.W (d16, A4), <>
    Encode(0x3u, 5u, 7u, 5u, 4u), // MOVE.W (d16, A4), <>
    Encode(0x3u, 6u, 7u, 5u, 4u), // MOVE.W (d16, A4), <>
    Encode(0x3u, 7u, 7u, 5u, 4u), // MOVE.W (d16, A4), <>

    Encode(0x3u, 2u, 7u, 6u, 4u), // MOVE.W (d8, A4, Xn), <>
    Encode(0x3u, 3u, 7u, 6u, 4u), // MOVE.W (d8, A4, Xn), <>
    Encode(0x3u, 4u, 7u, 6u, 4u), // MOVE.W (d8, A4, Xn), <>
    Encode(0x3u, 5u, 7u, 6u, 4u), // MOVE.W (d8, A4, Xn), <>
    Encode(0x3u, 6u, 7u, 6u, 4u), // MOVE.W (d8, A4, Xn), <>
    Encode(0x3u, 7u, 7u, 6u, 4u), // MOVE.W (d8, A4, Xn), <>

    Encode(0x3u, 2u, 7u, 7u, 0u), // MOVE.W (XXX).W, <>
    Encode(0x3u, 3u, 7u, 7u, 0u), // MOVE.W (XXX).W, <>
    Encode(0x3u, 4u, 7u, 7u, 0u), // MOVE.W (XXX).W, <>
    Encode(0x3u, 5u, 7u, 7u, 0u), // MOVE.W (XXX).W, <>
    Encode(0x3u, 6u, 7u, 7u, 0u), // MOVE.W (XXX).W, <>
    Encode(0x3u, 7u, 7u, 7u, 0u), // MOVE.W (XXX).W, <>

    Encode(0x3u, 2u, 7u, 7u, 1u), // MOVE.W (XXX).L, <>
    Encode(0x3u, 3u, 7u, 7u, 1u), // MOVE.W (XXX).L, <>
    Encode(0x3u, 4u, 7u, 7u, 1u), // MOVE.W (XXX).L, <>
    Encode(0x3u, 5u, 7u, 7u, 1u), // MOVE.W (XXX).L, <>
    Encode(0x3u, 6u, 7u, 7u, 1u), // MOVE.W (XXX).L, <>
    Encode(0x3u, 7u, 7u, 7u, 1u), // MOVE.W (XXX).L, <>

    Encode(0x3u, 2u, 7u, 7u, 2u), // MOVE.W (d16, PC), <>
    Encode(0x3u, 3u, 7u, 7u, 2u), // MOVE.W (d16, PC), <>
    Encode(0x3u, 4u, 7u, 7u, 2u), // MOVE.W (d16, PC), <>
    Encode(0x3u, 5u, 7u, 7u, 2u), // MOVE.W (d16, PC), <>
    Encode(0x3u, 6u, 7u, 7u, 2u), // MOVE.W (d16, PC), <>
    Encode(0x3u, 7u, 7u, 7u, 2u), // MOVE.W (d16, PC), <>

    Encode(0x3u, 2u, 7u, 7u, 3u), // MOVE.W (d8, PC, Xn), <>
    Encode(0x3u, 3u, 7u, 7u, 3u), // MOVE.W (d8, PC, Xn), <>
    Encode(0x3u, 4u, 7u, 7u, 3u), // MOVE.W (d8, PC, Xn), <>
    Encode(0x3u, 5u, 7u, 7u, 3u), // MOVE.W (d8, PC, Xn), <>
    Encode(0x3u, 6u, 7u, 7u, 3u), // MOVE.W (d8, PC, Xn), <>
    Encode(0x3u, 7u, 7u, 7u, 3u), // MOVE.W (d8, PC, Xn), <>

    Encode(0x3u, 2u, 7u, 7u, 4u), // MOVE.W #imm, <>
    Encode(0x3u, 3u, 7u, 7u, 4u), // MOVE.W #imm, <>
    Encode(0x3u, 4u, 7u, 7u, 4u), // MOVE.W #imm, <>
    Encode(0x3u, 5u, 7u, 7u, 4u), // MOVE.W #imm, <>
    Encode(0x3u, 6u, 7u, 7u, 4u), // MOVE.W #imm, <>
    Encode(0x3u, 7u, 7u, 7u, 4u), // MOVE.W #imm, <>

    Encode(0x3u, 4u, 0u, 7u, 5u), // MOVE.W <>, D4
    Encode(0x3u, 4u, 1u, 7u, 5u), // MOVE.W <>, A4
    Encode(0x3u, 4u, 2u, 7u, 5u), // MOVE.W <>, (A4)
    Encode(0x3u, 4u, 3u, 7u, 5u), // MOVE.W <>, (A4)+
    Encode(0x3u, 4u, 4u, 7u, 5u), // MOVE.W <>, -(A4)
    Encode(0x3u, 4u, 5u, 7u, 5u), // MOVE.W <>, (d16, A4)
    Encode(0x3u, 4u, 6u, 7u, 5u), // MOVE.W <>, (d8, A4, Xn)
    Encode(0x3u, 0u, 7u, 7u, 5u), // MOVE.W <>, (XXX).W
    Encode(0x3u, 1u, 7u, 7u, 5u), // MOVE.W <>, (XXX).L
    Encode(0x3u, 2u, 7u, 7u, 5u), // MOVE.W <>, <>
    Encode(0x3u, 3u, 7u, 7u, 5u), // MOVE.W <>, <>
    Encode(0x3u, 4u, 7u, 7u, 5u), // MOVE.W <>, <>
    Encode(0x3u, 5u, 7u, 7u, 5u), // MOVE.W <>, <>
    Encode(0x3u, 6u, 7u, 7u, 5u), // MOVE.W <>, <>
    Encode(0x3u, 7u, 7u, 7u, 5u), // MOVE.W <>, <>

    Encode(0x3u, 4u, 0u, 7u, 6u), // MOVE.W <>, D4
    Encode(0x3u, 4u, 1u, 7u, 6u), // MOVE.W <>, A4
    Encode(0x3u, 4u, 2u, 7u, 6u), // MOVE.W <>, (A4)
    Encode(0x3u, 4u, 3u, 7u, 6u), // MOVE.W <>, (A4)+
    Encode(0x3u, 4u, 4u, 7u, 6u), // MOVE.W <>, -(A4)
    Encode(0x3u, 4u, 5u, 7u, 6u), // MOVE.W <>, (d16, A4)
    Encode(0x3u, 4u, 6u, 7u, 6u), // MOVE.W <>, (d8, A4, Xn)
    Encode(0x3u, 0u, 7u, 7u, 6u), // MOVE.W <>, (XXX).W
    Encode(0x3u, 1u, 7u, 7u, 6u), // MOVE.W <>, (XXX).L
    Encode(0x3u, 2u, 7u, 7u, 6u), // MOVE.W <>, <>
    Encode(0x3u, 3u, 7u, 7u, 6u), // MOVE.W <>, <>
    Encode(0x3u, 4u, 7u, 7u, 6u), // MOVE.W <>, <>
    Encode(0x3u, 5u, 7u, 7u, 6u), // MOVE.W <>, <>
    Encode(0x3u, 6u, 7u, 7u, 6u), // MOVE.W <>, <>
    Encode(0x3u, 7u, 7u, 7u, 6u), // MOVE.W <>, <>

    Encode(0x3u, 4u, 0u, 7u, 7u), // MOVE.W <>, D4
    Encode(0x3u, 4u, 1u, 7u, 7u), // MOVE.W <>, A4
    Encode(0x3u, 4u, 2u, 7u, 7u), // MOVE.W <>, (A4)
    Encode(0x3u, 4u, 3u, 7u, 7u), // MOVE.W <>, (A4)+
    Encode(0x3u, 4u, 4u, 7u, 7u), // MOVE.W <>, -(A4)
    Encode(0x3u, 4u, 5u, 7u, 7u), // MOVE.W <>, (d16, A4)
    Encode(0x3u, 4u, 6u, 7u, 7u), // MOVE.W <>, (d8, A4, Xn)
    Encode(0x3u, 0u, 7u, 7u, 7u), // MOVE.W <>, (XXX).W
    Encode(0x3u, 1u, 7u, 7u, 7u), // MOVE.W <>, (XXX).L
    Encode(0x3u, 2u, 7u, 7u, 7u), // MOVE.W <>, <>
    Encode(0x3u, 3u, 7u, 7u, 7u), // MOVE.W <>, <>
    Encode(0x3u, 4u, 7u, 7u, 7u), // MOVE.W <>, <>
    Encode(0x3u, 5u, 7u, 7u, 7u), // MOVE.W <>, <>
    Encode(0x3u, 6u, 7u, 7u, 7u), // MOVE.W <>, <>
    Encode(0x3u, 7u, 7u, 7u, 7u), // MOVE.W <>, <>

};

class Line3IllegalInstructionTest: public M68000Test, public ::testing::WithParamInterface<uint32_t> {};

TEST_P(Line3IllegalInstructionTest, IllegalInstructionPattern) {
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
   IllegalLine3InstructionPatterns,
   Line3IllegalInstructionTest,
   ::testing::ValuesIn(VALUES)
);

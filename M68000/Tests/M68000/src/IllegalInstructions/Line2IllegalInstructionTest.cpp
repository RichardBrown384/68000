#include "M68000/Fixtures/M68000Test.h"

constexpr auto Encode(uint32_t op, uint32_t rx, uint32_t mx, uint32_t my, uint32_t ry) {
    return (op << 12u) + (rx << 9u) + (mx << 6u) + (my << 3u) + (ry);
}

constexpr auto VALUES = {
        
    Encode(0x2u, 2u, 7u, 0u, 4u), // MOVE.L D4, <>
    Encode(0x2u, 3u, 7u, 0u, 4u), // MOVE.L D4, <>
    Encode(0x2u, 4u, 7u, 0u, 4u), // MOVE.L D4, <>
    Encode(0x2u, 5u, 7u, 0u, 4u), // MOVE.L D4, <>
    Encode(0x2u, 6u, 7u, 0u, 4u), // MOVE.L D4, <>
    Encode(0x2u, 7u, 7u, 0u, 4u), // MOVE.L D4, <>
    
    Encode(0x2u, 2u, 7u, 1u, 5u), // MOVE.L A5, <>
    Encode(0x2u, 3u, 7u, 1u, 5u), // MOVE.L A5, <>
    Encode(0x2u, 4u, 7u, 1u, 5u), // MOVE.L A5, <>
    Encode(0x2u, 5u, 7u, 1u, 5u), // MOVE.L A5, <>
    Encode(0x2u, 6u, 7u, 1u, 5u), // MOVE.L A5, <>
    Encode(0x2u, 7u, 7u, 1u, 5u), // MOVE.L A5, <>
    
    Encode(0x2u, 2u, 7u, 2u, 4u), // MOVE.L (A4), <>
    Encode(0x2u, 3u, 7u, 2u, 4u), // MOVE.L (A4), <>
    Encode(0x2u, 4u, 7u, 2u, 4u), // MOVE.L (A4), <>
    Encode(0x2u, 5u, 7u, 2u, 4u), // MOVE.L (A4), <>
    Encode(0x2u, 6u, 7u, 2u, 4u), // MOVE.L (A4), <>
    Encode(0x2u, 7u, 7u, 2u, 4u), // MOVE.L (A4), <>
    
    Encode(0x2u, 2u, 7u, 3u, 4u), // MOVE.L (A4)+, <>
    Encode(0x2u, 3u, 7u, 3u, 4u), // MOVE.L (A4)+, <>
    Encode(0x2u, 4u, 7u, 3u, 4u), // MOVE.L (A4)+, <>
    Encode(0x2u, 5u, 7u, 3u, 4u), // MOVE.L (A4)+, <>
    Encode(0x2u, 6u, 7u, 3u, 4u), // MOVE.L (A4)+, <>
    Encode(0x2u, 7u, 7u, 3u, 4u), // MOVE.L (A4)+, <>
    
    Encode(0x2u, 2u, 7u, 4u, 4u), // MOVE.L -(A4), <>
    Encode(0x2u, 3u, 7u, 4u, 4u), // MOVE.L -(A4), <>
    Encode(0x2u, 4u, 7u, 4u, 4u), // MOVE.L -(A4), <>
    Encode(0x2u, 5u, 7u, 4u, 4u), // MOVE.L -(A4), <>
    Encode(0x2u, 6u, 7u, 4u, 4u), // MOVE.L -(A4), <>
    Encode(0x2u, 7u, 7u, 4u, 4u), // MOVE.L -(A4), <>

    Encode(0x2u, 2u, 7u, 5u, 4u), // MOVE.L (d16, A4), <>
    Encode(0x2u, 3u, 7u, 5u, 4u), // MOVE.L (d16, A4), <>
    Encode(0x2u, 4u, 7u, 5u, 4u), // MOVE.L (d16, A4), <>
    Encode(0x2u, 5u, 7u, 5u, 4u), // MOVE.L (d16, A4), <>
    Encode(0x2u, 6u, 7u, 5u, 4u), // MOVE.L (d16, A4), <>
    Encode(0x2u, 7u, 7u, 5u, 4u), // MOVE.L (d16, A4), <>

    Encode(0x2u, 2u, 7u, 6u, 4u), // MOVE.L (d8, A4, Xn), <>
    Encode(0x2u, 3u, 7u, 6u, 4u), // MOVE.L (d8, A4, Xn), <>
    Encode(0x2u, 4u, 7u, 6u, 4u), // MOVE.L (d8, A4, Xn), <>
    Encode(0x2u, 5u, 7u, 6u, 4u), // MOVE.L (d8, A4, Xn), <>
    Encode(0x2u, 6u, 7u, 6u, 4u), // MOVE.L (d8, A4, Xn), <>
    Encode(0x2u, 7u, 7u, 6u, 4u), // MOVE.L (d8, A4, Xn), <>

    Encode(0x2u, 2u, 7u, 7u, 0u), // MOVE.L (XXX).W, <>
    Encode(0x2u, 3u, 7u, 7u, 0u), // MOVE.L (XXX).W, <>
    Encode(0x2u, 4u, 7u, 7u, 0u), // MOVE.L (XXX).W, <>
    Encode(0x2u, 5u, 7u, 7u, 0u), // MOVE.L (XXX).W, <>
    Encode(0x2u, 6u, 7u, 7u, 0u), // MOVE.L (XXX).W, <>
    Encode(0x2u, 7u, 7u, 7u, 0u), // MOVE.L (XXX).W, <>

    Encode(0x2u, 2u, 7u, 7u, 1u), // MOVE.L (XXX).L, <>
    Encode(0x2u, 3u, 7u, 7u, 1u), // MOVE.L (XXX).L, <>
    Encode(0x2u, 4u, 7u, 7u, 1u), // MOVE.L (XXX).L, <>
    Encode(0x2u, 5u, 7u, 7u, 1u), // MOVE.L (XXX).L, <>
    Encode(0x2u, 6u, 7u, 7u, 1u), // MOVE.L (XXX).L, <>
    Encode(0x2u, 7u, 7u, 7u, 1u), // MOVE.L (XXX).L, <>

    Encode(0x2u, 2u, 7u, 7u, 2u), // MOVE.L (d16, PC), <>
    Encode(0x2u, 3u, 7u, 7u, 2u), // MOVE.L (d16, PC), <>
    Encode(0x2u, 4u, 7u, 7u, 2u), // MOVE.L (d16, PC), <>
    Encode(0x2u, 5u, 7u, 7u, 2u), // MOVE.L (d16, PC), <>
    Encode(0x2u, 6u, 7u, 7u, 2u), // MOVE.L (d16, PC), <>
    Encode(0x2u, 7u, 7u, 7u, 2u), // MOVE.L (d16, PC), <>

    Encode(0x2u, 2u, 7u, 7u, 3u), // MOVE.L (d8, PC, Xn), <>
    Encode(0x2u, 3u, 7u, 7u, 3u), // MOVE.L (d8, PC, Xn), <>
    Encode(0x2u, 4u, 7u, 7u, 3u), // MOVE.L (d8, PC, Xn), <>
    Encode(0x2u, 5u, 7u, 7u, 3u), // MOVE.L (d8, PC, Xn), <>
    Encode(0x2u, 6u, 7u, 7u, 3u), // MOVE.L (d8, PC, Xn), <>
    Encode(0x2u, 7u, 7u, 7u, 3u), // MOVE.L (d8, PC, Xn), <>

    Encode(0x2u, 2u, 7u, 7u, 4u), // MOVE.L #imm, <>
    Encode(0x2u, 3u, 7u, 7u, 4u), // MOVE.L #imm, <>
    Encode(0x2u, 4u, 7u, 7u, 4u), // MOVE.L #imm, <>
    Encode(0x2u, 5u, 7u, 7u, 4u), // MOVE.L #imm, <>
    Encode(0x2u, 6u, 7u, 7u, 4u), // MOVE.L #imm, <>
    Encode(0x2u, 7u, 7u, 7u, 4u), // MOVE.L #imm, <>

    Encode(0x2u, 4u, 0u, 7u, 5u), // MOVE.L <>, D4
    Encode(0x2u, 4u, 1u, 7u, 5u), // MOVE.L <>, A4
    Encode(0x2u, 4u, 2u, 7u, 5u), // MOVE.L <>, (A4)
    Encode(0x2u, 4u, 3u, 7u, 5u), // MOVE.L <>, (A4)+
    Encode(0x2u, 4u, 4u, 7u, 5u), // MOVE.L <>, -(A4)
    Encode(0x2u, 4u, 5u, 7u, 5u), // MOVE.L <>, (d16, A4)
    Encode(0x2u, 4u, 6u, 7u, 5u), // MOVE.L <>, (d8, A4, Xn)
    Encode(0x2u, 0u, 7u, 7u, 5u), // MOVE.L <>, (XXX).W
    Encode(0x2u, 1u, 7u, 7u, 5u), // MOVE.L <>, (XXX).L
    Encode(0x2u, 2u, 7u, 7u, 5u), // MOVE.L <>, <>
    Encode(0x2u, 3u, 7u, 7u, 5u), // MOVE.L <>, <>
    Encode(0x2u, 4u, 7u, 7u, 5u), // MOVE.L <>, <>
    Encode(0x2u, 5u, 7u, 7u, 5u), // MOVE.L <>, <>
    Encode(0x2u, 6u, 7u, 7u, 5u), // MOVE.L <>, <>
    Encode(0x2u, 7u, 7u, 7u, 5u), // MOVE.L <>, <>

    Encode(0x2u, 4u, 0u, 7u, 6u), // MOVE.L <>, D4
    Encode(0x2u, 4u, 1u, 7u, 6u), // MOVE.L <>, A4
    Encode(0x2u, 4u, 2u, 7u, 6u), // MOVE.L <>, (A4)
    Encode(0x2u, 4u, 3u, 7u, 6u), // MOVE.L <>, (A4)+
    Encode(0x2u, 4u, 4u, 7u, 6u), // MOVE.L <>, -(A4)
    Encode(0x2u, 4u, 5u, 7u, 6u), // MOVE.L <>, (d16, A4)
    Encode(0x2u, 4u, 6u, 7u, 6u), // MOVE.L <>, (d8, A4, Xn)
    Encode(0x2u, 0u, 7u, 7u, 6u), // MOVE.L <>, (XXX).W
    Encode(0x2u, 1u, 7u, 7u, 6u), // MOVE.L <>, (XXX).L
    Encode(0x2u, 2u, 7u, 7u, 6u), // MOVE.L <>, <>
    Encode(0x2u, 3u, 7u, 7u, 6u), // MOVE.L <>, <>
    Encode(0x2u, 4u, 7u, 7u, 6u), // MOVE.L <>, <>
    Encode(0x2u, 5u, 7u, 7u, 6u), // MOVE.L <>, <>
    Encode(0x2u, 6u, 7u, 7u, 6u), // MOVE.L <>, <>
    Encode(0x2u, 7u, 7u, 7u, 6u), // MOVE.L <>, <>

    Encode(0x2u, 4u, 0u, 7u, 7u), // MOVE.L <>, D4
    Encode(0x2u, 4u, 1u, 7u, 7u), // MOVE.L <>, A4
    Encode(0x2u, 4u, 2u, 7u, 7u), // MOVE.L <>, (A4)
    Encode(0x2u, 4u, 3u, 7u, 7u), // MOVE.L <>, (A4)+
    Encode(0x2u, 4u, 4u, 7u, 7u), // MOVE.L <>, -(A4)
    Encode(0x2u, 4u, 5u, 7u, 7u), // MOVE.L <>, (d16, A4)
    Encode(0x2u, 4u, 6u, 7u, 7u), // MOVE.L <>, (d8, A4, Xn)
    Encode(0x2u, 0u, 7u, 7u, 7u), // MOVE.L <>, (XXX).W
    Encode(0x2u, 1u, 7u, 7u, 7u), // MOVE.L <>, (XXX).L
    Encode(0x2u, 2u, 7u, 7u, 7u), // MOVE.L <>, <>
    Encode(0x2u, 3u, 7u, 7u, 7u), // MOVE.L <>, <>
    Encode(0x2u, 4u, 7u, 7u, 7u), // MOVE.L <>, <>
    Encode(0x2u, 5u, 7u, 7u, 7u), // MOVE.L <>, <>
    Encode(0x2u, 6u, 7u, 7u, 7u), // MOVE.L <>, <>
    Encode(0x2u, 7u, 7u, 7u, 7u), // MOVE.L <>, <>

};

class Line2IllegalInstructionTest: public M68000Test, public ::testing::WithParamInterface<uint32_t> {};

TEST_P(Line2IllegalInstructionTest, IllegalInstructionPattern) {
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
   IllegalLine2InstructionPatterns,
   Line2IllegalInstructionTest,
   ::testing::ValuesIn(VALUES)
);

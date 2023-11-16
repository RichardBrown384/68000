#include "M68000/Fixtures/M68000Test.h"

class MovemMemoryTestWord : public M68000Test {};

TEST_F(MovemMemoryTestWord, AddressIndirect) {
    Given({
        "D1 is 0xAABB",
        "D2 is 0xCCDD",
        "A4 is 0x2000",
        "A5 is 0x5000",
        "SR is S,0,0",
        "(0x2000).L is 0xFFFFFFFF",
        "(0x2004).L is 0xFFFFFFFF",
        "(0x2008).L is 0xFFFFFFFF",
        "(0x200C).L is 0xFFFFFFFF"
    });
    When({
        "MOVEM.W D1-D2/A4-A5, (A4)"
    });
    Then({
        "D1 is 0xAABB",
        "D2 is 0xCCDD",
        "A4 is 0x2000",
        "A5 is 0x5000",
        "SR is S,0,0",
        "(0x2000).L is 0xAABBCCDD",
        "(0x2004).L is 0x20005000",
        "(0x2008).L is 0xFFFFFFFF",
        "(0x200C).L is 0xFFFFFFFF",
        "CYCLES is 24"
    });
}

TEST_F(MovemMemoryTestWord, AddressDecrement) {
    Given({
        "D1 is 0xAABB",
        "D2 is 0xCCDD",
        "A4 is 0x2000",
        "A5 is 0x5000",
        "SR is S,0,0",
        "(0x1FF0).L is 0xFFFFFFFF",
        "(0x1FF4).L is 0xFFFFFFFF",
        "(0x1FF8).L is 0xFFFFFFFF",
        "(0x1FFC).L is 0xFFFFFFFF"
    });
    When({
        "MOVEM.W D1-D2/A4-A5, -(A4)"
    });
    Then({
        "D1 is 0xAABB",
        "D2 is 0xCCDD",
        "A4 is 0x1FF8",
        "A5 is 0x5000",
        "SR is S,0,0",
        "(0x1FF0).L is 0xFFFFFFFF",
        "(0x1FF4).L is 0xFFFFFFFF",
        "(0x1FF8).L is 0xAABBCCDD",
        "(0x1FFC).L is 0x20005000",
        "CYCLES is 24"
    });
}

TEST_F(MovemMemoryTestWord, AddressDisplacement) {
    Given({
        "D1 is 0xAABB",
        "D2 is 0xCCDD",
        "A4 is 0x2000",
        "A5 is 0x5000",
        "SR is S,0,0",
        "(0x4300).L is 0xFFFFFFFF",
        "(0x4304).L is 0xFFFFFFFF",
        "(0x4308).L is 0xFFFFFFFF",
        "(0x430C).L is 0xFFFFFFFF"
    });
    When({
        "MOVEM.W D1-D2/A4-A5, (0x2300, A4)"
    });
    Then({
        "D1 is 0xAABB",
        "D2 is 0xCCDD",
        "A4 is 0x2000",
        "A5 is 0x5000",
        "SR is S,0,0",
        "(0x4300).L is 0xAABBCCDD",
        "(0x4304).L is 0x20005000",
        "(0x4308).L is 0xFFFFFFFF",
        "(0x430C).L is 0xFFFFFFFF",
        "CYCLES is 28"
    });
}

TEST_F(MovemMemoryTestWord, AddressIndex) {
    Given({
        "D1 is 0xAABB",
        "D2 is 0xCCDD",
        "A4 is 0x2000",
        "A5 is 0x5000",
        "A6 is 0x0100",
        "SR is S,0,0",
        "(0x2110).L is 0xFFFFFFFF",
        "(0x2114).L is 0xFFFFFFFF",
        "(0x2118).L is 0xFFFFFFFF",
        "(0x211C).L is 0xFFFFFFFF"
    });
    When({
        "MOVEM.W D1-D2/A4-A5, (0x10, A4, A6.L)"
    });
    Then({
        "D1 is 0xAABB",
        "D2 is 0xCCDD",
        "A4 is 0x2000",
        "A5 is 0x5000",
        "A6 is 0x0100",
        "SR is S,0,0",
        "(0x2110).L is 0xAABBCCDD",
        "(0x2114).L is 0x20005000",
        "(0x2118).L is 0xFFFFFFFF",
        "(0x211C).L is 0xFFFFFFFF",
        "CYCLES is 30"
    });
}

TEST_F(MovemMemoryTestWord, AddressShort) {
    Given({
        "D1 is 0xAABB",
        "D2 is 0xCCDD",
        "A4 is 0x2000",
        "A5 is 0x5000",
        "SR is S,0,0",
        "(0x2310).L is 0xFFFFFFFF",
        "(0x2314).L is 0xFFFFFFFF",
        "(0x2318).L is 0xFFFFFFFF",
        "(0x231C).L is 0xFFFFFFFF"
    });
    When({
        "MOVEM.W D1-D2/A4-A5, (0x2310).W"
    });
    Then({
        "D1 is 0xAABB",
        "D2 is 0xCCDD",
        "A4 is 0x2000",
        "A5 is 0x5000",
        "SR is S,0,0",
        "(0x2310).L is 0xAABBCCDD",
        "(0x2314).L is 0x20005000",
        "(0x2318).L is 0xFFFFFFFF",
        "(0x231C).L is 0xFFFFFFFF",
        "CYCLES is 28"
    });
}

TEST_F(MovemMemoryTestWord, AddressLong) {
    Given({
        "D1 is 0xAABB",
        "D2 is 0xCCDD",
        "A4 is 0x2000",
        "A5 is 0x5000",
        "SR is S,0,0",
        "(0x00102310).L is 0xFFFFFFFF",
        "(0x00102314).L is 0xFFFFFFFF",
        "(0x00102318).L is 0xFFFFFFFF",
        "(0x0010231C).L is 0xFFFFFFFF"
    });
    When({
        "MOVEM.W D1-D2/A4-A5, (0x00102310).L"
    });
    Then({
        "D1 is 0xAABB",
        "D2 is 0xCCDD",
        "A4 is 0x2000",
        "A5 is 0x5000",
        "SR is S,0,0",
        "(0x00102310).L is 0xAABBCCDD",
        "(0x00102314).L is 0x20005000",
        "(0x00102318).L is 0xFFFFFFFF",
        "(0x0010231C).L is 0xFFFFFFFF",
        "CYCLES is 32"
    });
}
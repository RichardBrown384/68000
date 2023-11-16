#include "M68000/Fixtures/M68000Test.h"

class MovemMemoryTestLong : public M68000Test {};

TEST_F(MovemMemoryTestLong, AddressIndirect) {
    Given({
        "D1 is 0xAABBCCDD",
        "D2 is 0xEEFF8899",
        "A4 is 0x00002000",
        "A5 is 0xDEADBEEF",
        "SR is S,0,0",
        "(0x2000).L is 0xFFFFFFFF",
        "(0x2004).L is 0xFFFFFFFF",
        "(0x2008).L is 0xFFFFFFFF",
        "(0x200C).L is 0xFFFFFFFF"
    });
    When({
        "MOVEM.L D1-D2/A4-A5, (A4)"
    });
    Then({
        "D1 is 0xAABBCCDD",
        "D2 is 0xEEFF8899",
        "A4 is 0x00002000",
        "A5 is 0xDEADBEEF",
        "SR is S,0,0",
        "(0x2000).L is 0xAABBCCDD",
        "(0x2004).L is 0xEEFF8899",
        "(0x2008).L is 0x00002000",
        "(0x200C).L is 0xDEADBEEF",
        "CYCLES is 40"
    });
}

TEST_F(MovemMemoryTestLong, AddressDecrement) {
    Given({
        "D1 is 0xAABBCCDD",
        "D2 is 0xEEFF8899",
        "A4 is 0x00002000",
        "A5 is 0xDEADBEEF",
        "SR is S,0,0",
        "(0x1FF0).L is 0xFFFFFFFF",
        "(0x1FF4).L is 0xFFFFFFFF",
        "(0x1FF8).L is 0xFFFFFFFF",
        "(0x1FFC).L is 0xFFFFFFFF"
    });
    When({
        "MOVEM.L D1-D2/A4-A5, -(A4)"
    });
    Then({
        "D1 is 0xAABBCCDD",
        "D2 is 0xEEFF8899",
        "A4 is 0x00001FF0",
        "A5 is 0xDEADBEEF",
        "SR is S,0,0",
        "(0x1FF0).L is 0xAABBCCDD",
        "(0x1FF4).L is 0xEEFF8899",
        "(0x1FF8).L is 0x00002000",
        "(0x1FFC).L is 0xDEADBEEF",
        "CYCLES is 40"
    });
}

TEST_F(MovemMemoryTestLong, AddressDisplacement) {
    Given({
        "D1 is 0xAABBCCDD",
        "D2 is 0xEEFF8899",
        "A4 is 0x00002000",
        "A5 is 0xDEADBEEF",
        "SR is S,0,0",
        "(0x2100).L is 0xFFFFFFFF",
        "(0x2104).L is 0xFFFFFFFF",
        "(0x2108).L is 0xFFFFFFFF",
        "(0x210C).L is 0xFFFFFFFF"
    });
    When({
        "MOVEM.L D1-D2/A4-A5, (0x0100, A4)"
    });
    Then({
        "D1 is 0xAABBCCDD",
        "D2 is 0xEEFF8899",
        "A4 is 0x00002000",
        "A5 is 0xDEADBEEF",
        "SR is S,0,0",
        "(0x2100).L is 0xAABBCCDD",
        "(0x2104).L is 0xEEFF8899",
        "(0x2108).L is 0x00002000",
        "(0x210C).L is 0xDEADBEEF",
        "CYCLES is 44"
    });
}

TEST_F(MovemMemoryTestLong, AddressIndex) {
    Given({
        "D1 is 0xAABBCCDD",
        "D2 is 0xEEFF8899",
        "A4 is 0x00002000",
        "A5 is 0xDEADBEEF",
        "A6 is 0x00000100",
        "SR is S,0,0",
        "(0x2110).L is 0xFFFFFFFF",
        "(0x2114).L is 0xFFFFFFFF",
        "(0x2118).L is 0xFFFFFFFF",
        "(0x211C).L is 0xFFFFFFFF"
    });
    When({
        "MOVEM.L D1-D2/A4-A5, (0x10, A4, A6.L)"
    });
    Then({
        "D1 is 0xAABBCCDD",
        "D2 is 0xEEFF8899",
        "A4 is 0x00002000",
        "A5 is 0xDEADBEEF",
        "A6 is 0x00000100",
        "SR is S,0,0",
        "(0x2110).L is 0xAABBCCDD",
        "(0x2114).L is 0xEEFF8899",
        "(0x2118).L is 0x00002000",
        "(0x211C).L is 0xDEADBEEF",
        "CYCLES is 46"
    });
}

TEST_F(MovemMemoryTestLong, Short) {
    Given({
        "D1 is 0xAABBCCDD",
        "D2 is 0xEEFF8899",
        "A4 is 0x00002000",
        "A5 is 0xDEADBEEF",
        "SR is S,0,0",
        "(0x4300).L is 0xFFFFFFFF",
        "(0x4304).L is 0xFFFFFFFF",
        "(0x4308).L is 0xFFFFFFFF",
        "(0x430C).L is 0xFFFFFFFF"
    });
    When({
        "MOVEM.L D1-D2/A4-A5, (0x4300).W"
    });
    Then({
        "D1 is 0xAABBCCDD",
        "D2 is 0xEEFF8899",
        "A4 is 0x00002000",
        "A5 is 0xDEADBEEF",
        "SR is S,0,0",
        "(0x4300).L is 0xAABBCCDD",
        "(0x4304).L is 0xEEFF8899",
        "(0x4308).L is 0x00002000",
        "(0x430C).L is 0xDEADBEEF",
        "CYCLES is 44"
    });
}

TEST_F(MovemMemoryTestLong, Long) {
    Given({
        "D1 is 0xAABBCCDD",
        "D2 is 0xEEFF8899",
        "A4 is 0x00002000",
        "A5 is 0xDEADBEEF",
        "SR is S,0,0",
        "(0x00104300).L is 0xFFFFFFFF",
        "(0x00104304).L is 0xFFFFFFFF",
        "(0x00104308).L is 0xFFFFFFFF",
        "(0x0010430C).L is 0xFFFFFFFF"
    });
    When({
        "MOVEM.L D1-D2/A4-A5, (0x00104300).L"
    });
    Then({
        "D1 is 0xAABBCCDD",
        "D2 is 0xEEFF8899",
        "A4 is 0x00002000",
        "A5 is 0xDEADBEEF",
        "SR is S,0,0",
        "(0x00104300).L is 0xAABBCCDD",
        "(0x00104304).L is 0xEEFF8899",
        "(0x00104308).L is 0x00002000",
        "(0x0010430C).L is 0xDEADBEEF",
        "CYCLES is 48"
    });
}
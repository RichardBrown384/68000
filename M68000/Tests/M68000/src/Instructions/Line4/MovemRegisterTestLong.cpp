#include "M68000/Fixtures/M68000Test.h"

class MovemRegisterTestLong : public M68000Test {};

TEST_F(MovemRegisterTestLong, AddressIndirect) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0000",
        "D2 is 0x0000",
        "A4 is 0x2000",
        "A5 is 0x0000",
        "(0x2000).L is 0xDEADBEEF",
        "(0x2004).L is 0xAABBCCDD",
        "(0x2008).L is 0xBADC0FFE",
        "(0x200C).L is 0x0000CDCD",
    });
    When({
        "MOVEM.L (A4), D1-D2/A4-A5"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 44",
        "D1 is 0xDEADBEEF",
        "D2 is 0xAABBCCDD",
        "A4 is 0xBADC0FFE",
        "A5 is 0x0000CDCD",
        "(0x2000).L is 0xDEADBEEF",
        "(0x2004).L is 0xAABBCCDD",
        "(0x2008).L is 0xBADC0FFE",
        "(0x200C).L is 0x0000CDCD",
    });
}

TEST_F(MovemRegisterTestLong, AddressIncrement) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0000",
        "D2 is 0x0000",
        "A4 is 0x2000",
        "A5 is 0x0000",
        "(0x2000).L is 0xDEADBEEF",
        "(0x2004).L is 0xAABBCCDD",
        "(0x2008).L is 0xBADC0FFE",
        "(0x200C).L is 0xCDCDCDCD",
    });
    When({
        "MOVEM.L (A4)+, D1-D2/A4-A5"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 44",
        "D1 is 0xDEADBEEF",
        "D2 is 0xAABBCCDD",
        "A4 is 0x00002010",
        "A5 is 0xCDCDCDCD",
        "(0x2000).L is 0xDEADBEEF",
        "(0x2004).L is 0xAABBCCDD",
        "(0x2008).L is 0xBADC0FFE",
        "(0x200C).L is 0xCDCDCDCD",
    });
}

TEST_F(MovemRegisterTestLong, AddressDisplacement) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0000",
        "D2 is 0x0000",
        "A4 is 0x2000",
        "A5 is 0x0000",
        "(0x2020).L is 0xDEADBEEF",
        "(0x2024).L is 0xAABBCCDD",
        "(0x2028).L is 0xBADC0FFE",
        "(0x202C).L is 0x0000CDCD",
    });
    When({
        "MOVEM.L (0x20, A4), D1-D2/A4-A5"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 48",
        "D1 is 0xDEADBEEF",
        "D2 is 0xAABBCCDD",
        "A4 is 0xBADC0FFE",
        "A5 is 0x0000CDCD",
        "(0x2020).L is 0xDEADBEEF",
        "(0x2024).L is 0xAABBCCDD",
        "(0x2028).L is 0xBADC0FFE",
        "(0x202C).L is 0x0000CDCD",
    });
}

TEST_F(MovemRegisterTestLong, AddressIndex) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0000",
        "D2 is 0x0000",
        "A4 is 0x2000",
        "A5 is 0x0000",
        "A6 is 0x1000",
        "(0x3020).L is 0xDEADBEEF",
        "(0x3024).L is 0xAABBCCDD",
        "(0x3028).L is 0xBADC0FFE",
        "(0x302C).L is 0x0000CDCD",
    });
    When({
        "MOVEM.L (0x20, A4, A6.L), D1-D2/A4-A5"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 50",
        "D1 is 0xDEADBEEF",
        "D2 is 0xAABBCCDD",
        "A4 is 0xBADC0FFE",
        "A5 is 0x0000CDCD",
        "A6 is 0x00001000",
        "(0x3020).L is 0xDEADBEEF",
        "(0x3024).L is 0xAABBCCDD",
        "(0x3028).L is 0xBADC0FFE",
        "(0x302C).L is 0x0000CDCD",
    });
}

TEST_F(MovemRegisterTestLong, Short) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0000",
        "D2 is 0x0000",
        "A4 is 0x2000",
        "A5 is 0x0000",
        "(0x2020).L is 0xDEADBEEF",
        "(0x2024).L is 0xAABBCCDD",
        "(0x2028).L is 0xBADC0FFE",
        "(0x202C).L is 0x0000CDCD",
    });
    When({
        "MOVEM.L (0x2020).W, D1-D2/A4-A5"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 48",
        "D1 is 0xDEADBEEF",
        "D2 is 0xAABBCCDD",
        "A4 is 0xBADC0FFE",
        "A5 is 0x0000CDCD",
        "(0x2020).L is 0xDEADBEEF",
        "(0x2024).L is 0xAABBCCDD",
        "(0x2028).L is 0xBADC0FFE",
        "(0x202C).L is 0x0000CDCD",
    });
}

TEST_F(MovemRegisterTestLong, Long) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0000",
        "D2 is 0x0000",
        "A4 is 0x2000",
        "A5 is 0x0000",
        "(0x00102020).L is 0xDEADBEEF",
        "(0x00102024).L is 0xAABBCCDD",
        "(0x00102028).L is 0xBADC0FFE",
        "(0x0010202C).L is 0x0000CDCD",
    });
    When({
        "MOVEM.L (0x00102020).L, D1-D2/A4-A5"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1008",
        "CYCLES is 52",
        "D1 is 0xDEADBEEF",
        "D2 is 0xAABBCCDD",
        "A4 is 0xBADC0FFE",
        "A5 is 0x0000CDCD",
        "(0x00102020).L is 0xDEADBEEF",
        "(0x00102024).L is 0xAABBCCDD",
        "(0x00102028).L is 0xBADC0FFE",
        "(0x0010202C).L is 0x0000CDCD",
    });
}

TEST_F(MovemRegisterTestLong, PCDisplacement) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0000",
        "D2 is 0x0000",
        "A4 is 0x2000",
        "A5 is 0x0000",
        "(0x1020).L is 0xDEADBEEF",
        "(0x1024).L is 0xAABBCCDD",
        "(0x1028).L is 0xBADC0FFE",
        "(0x102C).L is 0x0000CDCD",
    });
    When({
        "MOVEM.L (0x1C, PC), D1-D2/A4-A5"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 48",
        "D1 is 0xDEADBEEF",
        "D2 is 0xAABBCCDD",
        "A4 is 0xBADC0FFE",
        "A5 is 0x0000CDCD",
        "(0x1020).L is 0xDEADBEEF",
        "(0x1024).L is 0xAABBCCDD",
        "(0x1028).L is 0xBADC0FFE",
        "(0x102C).L is 0x0000CDCD",
    });
}

TEST_F(MovemRegisterTestLong, PCIndex) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0000",
        "D2 is 0x0000",
        "A4 is 0x2000",
        "A5 is 0x0000",
        "A6 is 0x1000",
        "(0x2020).L is 0xDEADBEEF",
        "(0x2024).L is 0xAABBCCDD",
        "(0x2028).L is 0xBADC0FFE",
        "(0x202C).L is 0x0000CDCD",
    });
    When({
        "MOVEM.L (0x1C, PC, A6.L), D1-D2/A4-A5"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 50",
        "D1 is 0xDEADBEEF",
        "D2 is 0xAABBCCDD",
        "A4 is 0xBADC0FFE",
        "A5 is 0x0000CDCD",
        "A6 is 0x00001000",
        "(0x2020).L is 0xDEADBEEF",
        "(0x2024).L is 0xAABBCCDD",
        "(0x2028).L is 0xBADC0FFE",
        "(0x202C).L is 0x0000CDCD",
    });
}

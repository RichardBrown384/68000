#include "M68000/Fixtures/M68000Test.h"

class TSTTest : public M68000Test {};

TEST_F(TSTTest, TstNonZeroDataRegisterByteWorks) {
    Given({
        "SR is S,0,XVC",
        "PC is 0x1000",
        "D1 is 0x00000001",
    });
    When({
        "TST.B D1"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x00000001",
    });
}

TEST_F(TSTTest, TstNegativeDataRegisterByteWorks) {
    Given({
        "SR is S,0,XVC",
        "PC is 0x1000",
        "D1 is 0xFFFFFF81",
    });
    When({
        "TST.B D1"
    });
    Then({
        "SR is S,0,XN",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0xFFFFFF81",
    });
}

TEST_F(TSTTest, TstZeroRegisterByteWorks) {
    Given({
        "SR is S,0,XVC",
        "PC is 0x1000",
        "D1 is 0xFFFFFF00",
    });
    When({
        "TST.B D1"
    });
    Then({
        "SR is S,0,XZ",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0xFFFFFF00",
    });
}

TEST_F(TSTTest, TstNonZeroDataRegisterWordWorks) {
    Given({
        "SR is S,0,XVC",
        "PC is 0x1000",
        "D1 is 0x00000100",
    });
    When({
        "TST.W D1"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x00000100",
    });
}

TEST_F(TSTTest, TstNegativeDataRegisterWordWorks) {
    Given({
        "SR is S,0,XVC",
        "PC is 0x1000",
        "D1 is 0xFFFF8001",
    });
    When({
        "TST.W D1"
    });
    Then({
        "SR is S,0,XN",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0xFFFF8001",
    });
}

TEST_F(TSTTest, TstZeroRegisterWordWorks) {
    Given({
        "SR is S,0,XVC",
        "PC is 0x1000",
        "D1 is 0xFFFF0000",
    });
    When({
        "TST.W D1"
    });
    Then({
        "SR is S,0,XZ",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0xFFFF0000",
    });
}

TEST_F(TSTTest, TstNonZeroDataRegisterLongWorks) {
    Given({
        "SR is S,0,XVC",
        "PC is 0x1000",
        "D1 is 0x01000000",
    });
    When({
        "TST.L D1"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01000000",
    });
}

TEST_F(TSTTest, TstNegativeDataRegisterLongWorks) {
    Given({
        "SR is S,0,XVC",
        "PC is 0x1000",
        "D1 is 0x80000001",
    });
    When({
        "TST.L D1"
    });
    Then({
        "SR is S,0,XN",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x80000001",
    });
}

TEST_F(TSTTest, TstZeroRegisterLongWorks) {
    Given({
        "SR is S,0,XVC",
        "PC is 0x1000",
        "D1 is 0x00000000",
    });
    When({
        "TST.L D1"
    });
    Then({
        "SR is S,0,XZ",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x00000000",
    });
}

TEST_F(TSTTest, TstMemoryByteWorks) {
    Given({
        "SR is S,0,XVC",
        "PC is 0x1000",
        "A1 is 0x00003000",
        "(0x3000).B is 0x80",
    });
    When({
        "TST.B (A1)"
    });
    Then({
        "SR is S,0,XN",
        "PC is 0x1002",
        "CYCLES is 8",
        "A1 is 0x00003000",
        "(0x3000).B is 0x80",
    });
}

TEST_F(TSTTest, TstMemoryWordWorks) {
    Given({
        "SR is S,0,XVC",
        "PC is 0x1000",
        "A1 is 0x00003000",
        "(0x3000).W is 0x8000",
    });
    When({
        "TST.W (A1)"
    });
    Then({
        "SR is S,0,XN",
        "PC is 0x1002",
        "CYCLES is 8",
        "A1 is 0x00003000",
        "(0x3000).W is 0x8000",
    });
}

TEST_F(TSTTest, TstMemoryLongWorks) {
    Given({
        "SR is S,0,XVC",
        "PC is 0x1000",
        "A1 is 0x00003000",
        "(0x3000).L is 0x80000000",
    });
    When({
        "TST.L (A1)"
    });
    Then({
        "SR is S,0,XN",
        "PC is 0x1002",
        "CYCLES is 12",
        "A1 is 0x00003000",
        "(0x3000).L is 0x80000000",
    });
}

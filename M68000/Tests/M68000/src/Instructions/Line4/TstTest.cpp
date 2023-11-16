#include "M68000/Fixtures/M68000Test.h"

class TSTTest : public M68000Test {};

TEST_F(TSTTest, TstNonZeroDataRegisterByteWorks) {
    Given({
        "D1 is 0x00000001",
        "SR is S,0,XVC"
    });
    When({
        "TST.B D1"
    });
    Then({
        "D1 is 0x00000001",
        "SR is S,0,X"
    });
}

TEST_F(TSTTest, TstNegativeDataRegisterByteWorks) {
    Given({
        "D1 is 0xFFFFFF81",
        "SR is S,0,XVC"
    });
    When({
        "TST.B D1"
    });
    Then({
        "D1 is 0xFFFFFF81",
        "SR is S,0,XN"
    });
}

TEST_F(TSTTest, TstZeroRegisterByteWorks) {
    Given({
        "D1 is 0xFFFFFF00",
        "SR is S,0,XVC"
    });
    When({
        "TST.B D1"
    });
    Then({
        "D1 is 0xFFFFFF00",
        "SR is S,0,XZ"
    });
}

TEST_F(TSTTest, TstNonZeroDataRegisterWordWorks) {
    Given({
        "D1 is 0x00000100",
        "SR is S,0,XVC"
    });
    When({
        "TST.W D1"
    });
    Then({
        "D1 is 0x00000100",
        "SR is S,0,X"
    });
}

TEST_F(TSTTest, TstNegativeDataRegisterWordWorks) {
    Given({
        "D1 is 0xFFFF8001",
        "SR is S,0,XVC"
    });
    When({
        "TST.W D1"
    });
    Then({
        "D1 is 0xFFFF8001",
        "SR is S,0,XN"
    });
}

TEST_F(TSTTest, TstZeroRegisterWordWorks) {
    Given({
        "D1 is 0xFFFF0000",
        "SR is S,0,XVC"
    });
    When({
        "TST.W D1"
    });
    Then({
        "D1 is 0xFFFF0000",
        "SR is S,0,XZ"
    });
}

TEST_F(TSTTest, TstNonZeroDataRegisterLongWorks) {
    Given({
        "D1 is 0x01000000",
        "SR is S,0,XVC"
    });
    When({
        "TST.L D1"
    });
    Then({
        "D1 is 0x01000000",
        "SR is S,0,X"
    });
}

TEST_F(TSTTest, TstNegativeDataRegisterLongWorks) {
    Given({
        "D1 is 0x80000001",
        "SR is S,0,XVC"
    });
    When({
        "TST.L D1"
    });
    Then({
        "D1 is 0x80000001",
        "SR is S,0,XN"
    });
}

TEST_F(TSTTest, TstZeroRegisterLongWorks) {
    Given({
        "D1 is 0x00000000",
        "SR is S,0,XVC"
    });
    When({
        "TST.L D1"
    });
    Then({
        "D1 is 0x00000000",
        "SR is S,0,XZ"
    });
}

TEST_F(TSTTest, TstMemoryByteWorks) {
    Given({
        "A1 is 0x00003000",
        "(0x3000).B is 0x80",
        "SR is S,0,XVC"
    });
    When({
        "TST.B (A1)"
    });
    Then({
        "A1 is 0x00003000",
        "(0x3000).B is 0x80",
        "SR is S,0,XN"
    });
}

TEST_F(TSTTest, TstMemoryWordWorks) {
    Given({
        "A1 is 0x00003000",
        "(0x3000).W is 0x8000",
        "SR is S,0,XVC"
    });
    When({
        "TST.W (A1)"
    });
    Then({
        "A1 is 0x00003000",
        "(0x3000).W is 0x8000",
        "SR is S,0,XN"
    });
}

TEST_F(TSTTest, TstMemoryLongWorks) {
    Given({
        "A1 is 0x00003000",
        "(0x3000).L is 0x80000000",
        "SR is S,0,XVC"
    });
    When({
        "TST.L (A1)"
    });
    Then({
        "A1 is 0x00003000",
        "(0x3000).L is 0x80000000",
        "SR is S,0,XN"
    });
}

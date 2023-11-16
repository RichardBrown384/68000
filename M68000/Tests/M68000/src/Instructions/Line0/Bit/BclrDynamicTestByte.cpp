#include "M68000/Fixtures/M68000Test.h"

class BCLRDynamicTestByte : public M68000Test {};

TEST_F(BCLRDynamicTestByte, BitSetWorks) {
    Given({
        "D1 is 0x3",
        "A1 is 0x2000",
        "(0x2000).B is 0xFF",
        "SR is S,0,0"
    });
    When({
        "BCLR.B D1, (A1)"
    });
    Then({
        "D1 is 0x3",
        "A1 is 0x2000",
        "(0x2000).B is 0xF7",
        "SR is S,0,0"
    });
}

TEST_F(BCLRDynamicTestByte, BitClearWorks) {
    Given({
        "D1 is 0xB",
        "A1 is 0x2000",
        "(0x2000).B is 0xF7",
        "SR is S,0,0"
    });
    When({
        "BCLR.B D1, (A1)"
    });
    Then({
        "D1 is 0xB",
        "A1 is 0x2000",
        "(0x2000).B is 0xF7",
        "SR is S,0,Z"
    });
}

TEST_F(BCLRDynamicTestByte, AddressIndirectWorks) {
    Given({
        "D1 is 0x4",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFF",
        "SR is S,0,0"
    });
    When({
        "BCLR.B D1, (A4)"
    });
    Then({
        "D1 is 0x4",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
}

TEST_F(BCLRDynamicTestByte, AddressIncrementWorks) {
    Given({
        "D1 is 0x4",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFF",
        "SR is S,0,0"
    });
    When({
        "BCLR.B D1, (A4)+"
    });
    Then({
        "D1 is 0x4",
        "A4 is 0x00006001",
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
}

TEST_F(BCLRDynamicTestByte, AddressDecrementWorks) {
    Given({
        "D1 is 0x4",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xFF",
        "SR is S,0,0"
    });
    When({
        "BCLR.B D1, -(A4)"
    });
    Then({
        "D1 is 0x4",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xEF",
        "SR is S,0,0"
    });
}

TEST_F(BCLRDynamicTestByte, AddressDisplacementWorks) {
    Given({
        "D1 is 0x4",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xFF",
        "SR is S,0,0"
    });
    When({
        "BCLR.B D1, (0x004C, A4)"
    });
    Then({
        "D1 is 0x4",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
        "SR is S,0,0"
    });
}

TEST_F(BCLRDynamicTestByte, AddressIndexWorks) {
    Given({
        "D1 is 0x4",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xFF",
        "SR is S,0,0"
    });
    When({
        "BCLR.B D1, (0x6E, A4, A5.L)"
    });
    Then({
        "D1 is 0x4",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
        "SR is S,0,0"
    });
}

TEST_F(BCLRDynamicTestByte, ShortWorks) {
    Given({
        "D1 is 0x4",
        "(0x00006000).B is 0xFF",
        "SR is S,0,0"
    });
    When({
        "BCLR.B D1, (0x6000).W"
    });
    Then({
        "D1 is 0x4",
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
}

TEST_F(BCLRDynamicTestByte, LongWorks) {
    Given({
        "D1 is 0x4",
        "(0x00006000).B is 0xFF",
        "SR is S,0,0"
    });
    When({
        "BCLR.B D1, (0x00006000).L"
    });
    Then({
        "D1 is 0x4",
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
}

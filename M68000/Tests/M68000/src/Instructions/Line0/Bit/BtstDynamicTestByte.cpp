#include "M68000/Fixtures/M68000Test.h"

class BTSTDynamicTestByte : public M68000Test {};

TEST_F(BTSTDynamicTestByte, BitSetWorks) {
    Given({
        "D1 is 0x3",
        "A1 is 0x2000",
        "(0x2000).B is 0xFF",
        "SR is S,0,Z"
    });
    When({
        "BTST.B D1, (A1)"
    });
    Then({
        "D1 is 0x3",
        "A1 is 0x2000",
        "(0x2000).B is 0xFF",
        "SR is S,0,0"
    });
}

TEST_F(BTSTDynamicTestByte, BitClearWorks) {
    Given({
        "D1 is 0xB",
        "A1 is 0x2000",
        "(0x2000).B is 0xF7",
        "SR is S,0,0"
    });
    When({
        "BTST.B D1, (A1)"
    });
    Then({
        "D1 is 0xB",
        "A1 is 0x2000",
        "(0x2000).B is 0xF7",
        "SR is S,0,Z"
    });
}

TEST_F(BTSTDynamicTestByte, AddressIndirectWorks) {
    Given({
        "D1 is 0x4",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFF",
        "SR is S,0,Z"
    });
    When({
        "BTST.B D1, (A4)"
    });
    Then({
        "D1 is 0x4",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFF",
        "SR is S,0,0"
    });
}

TEST_F(BTSTDynamicTestByte, AddressIncrementWorks) {
    Given({
        "D1 is 0x4",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "BTST.B D1, (A4)+"
    });
    Then({
        "D1 is 0x4",
        "A4 is 0x00006001",
        "(0x00006000).B is 0xEF",
        "SR is S,0,Z"
    });
}

TEST_F(BTSTDynamicTestByte, AddressDecrementWorks) {
    Given({
        "D1 is 0x4",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xFF",
        "SR is S,0,0"
    });
    When({
        "BTST.B D1, -(A4)"
    });
    Then({
        "D1 is 0x4",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xFF",
        "SR is S,0,0"
    });
}

TEST_F(BTSTDynamicTestByte, AddressDisplacementWorks) {
    Given({
        "D1 is 0x4",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xFF",
        "SR is S,0,Z"
    });
    When({
        "BTST.B D1, (0x004C, A4)"
    });
    Then({
        "D1 is 0x4",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xFF",
        "SR is S,0,0"
    });
}

TEST_F(BTSTDynamicTestByte, AddressIndexWorks) {
    Given({
        "D1 is 0x4",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "BTST.B D1, (0x6E, A4, A5.L)"
    });
    Then({
        "D1 is 0x4",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
        "SR is S,0,Z"
    });
}

TEST_F(BTSTDynamicTestByte, ShortWorks) {
    Given({
        "D1 is 0x4",
        "(0x00006000).B is 0xFF",
        "SR is S,0,Z"
    });
    When({
        "BTST.B D1, (0x6000).W"
    });
    Then({
        "D1 is 0x4",
        "(0x00006000).B is 0xFF",
        "SR is S,0,0"
    });
}

TEST_F(BTSTDynamicTestByte, LongWorks) {
    Given({
        "D1 is 0x4",
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "BTST.B D1, (0x00006000).L"
    });
    Then({
        "D1 is 0x4",
        "(0x00006000).B is 0xEF",
        "SR is S,0,Z"
    });
}

TEST_F(BTSTDynamicTestByte, PCDisplacementWorks) {
    Given({
        "D1 is 0x0",
        "(0x0000103E).B is 0xEE",
        "SR is S,0,0"
    });
    When({
        "BTST.B D1, (0x003C, PC)"
    });
    Then({
        "D1 is 0x0",
        "(0x0000103E).B is 0xEE",
        "SR is S,0,Z"
    });
}

TEST_F(BTSTDynamicTestByte, PCIndexWorks) {
    Given({
        "D1 is 0x1",
        "A2 is 0x00000010",
        "(0x00001070).B is 0xEE",
        "SR is S,0,Z"
    });
    When({
        "BTST.B D1, (0x5E, PC, A2.L)"
    });
    Then({
        "D1 is 0x1",
        "A2 is 0x00000010",
        "(0x00001070).B is 0xEE",
        "SR is S,0,0"
    });
}

TEST_F(BTSTDynamicTestByte, ImmediateWorks) {
    Given({
        "D1 is 0x0",
        "SR is S,0,0"
    });
    When({
        "BTST.B D1, #0xEE"
    });
    Then({
        "D1 is 0x0",
        "SR is S,0,Z"
    });
}
#include "M68000/Fixtures/M68000Test.h"

class BTSTDynamicTestByte : public M68000Test {};

TEST_F(BTSTDynamicTestByte, BitSetWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0x3",
        "A1 is 0x2000",
        "(0x2000).B is 0xFF",
    });
    When({
        "BTST.B D1, (A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x3",
        "A1 is 0x2000",
        "(0x2000).B is 0xFF",
    });
}

TEST_F(BTSTDynamicTestByte, BitClearWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xB",
        "A1 is 0x2000",
        "(0x2000).B is 0xF7",
    });
    When({
        "BTST.B D1, (A1)"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0xB",
        "A1 is 0x2000",
        "(0x2000).B is 0xF7",
    });
}

TEST_F(BTSTDynamicTestByte, AddressIndirectWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0x4",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFF",
    });
    When({
        "BTST.B D1, (A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x4",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFF",
    });
}

TEST_F(BTSTDynamicTestByte, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x4",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "BTST.B D1, (A4)+"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x4",
        "A4 is 0x00006001",
        "(0x00006000).B is 0xEF",
    });
}

TEST_F(BTSTDynamicTestByte, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x4",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xFF",
    });
    When({
        "BTST.B D1, -(A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0x4",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xFF",
    });
}

TEST_F(BTSTDynamicTestByte, AddressDisplacementWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0x4",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xFF",
    });
    When({
        "BTST.B D1, (0x004C, A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x4",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xFF",
    });
}

TEST_F(BTSTDynamicTestByte, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x4",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
    });
    When({
        "BTST.B D1, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0x4",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
    });
}

TEST_F(BTSTDynamicTestByte, ShortWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0x4",
        "(0x00006000).B is 0xFF",
    });
    When({
        "BTST.B D1, (0x6000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x4",
        "(0x00006000).B is 0xFF",
    });
}

TEST_F(BTSTDynamicTestByte, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x4",
        "(0x00006000).B is 0xEF",
    });
    When({
        "BTST.B D1, (0x00006000).L"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1006",
        "CYCLES is 16",
        "D1 is 0x4",
        "(0x00006000).B is 0xEF",
    });
}

TEST_F(BTSTDynamicTestByte, PCDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0",
        "(0x0000103E).B is 0xEE",
    });
    When({
        "BTST.B D1, (0x003C, PC)"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x0",
        "(0x0000103E).B is 0xEE",
    });
}

TEST_F(BTSTDynamicTestByte, PCIndexWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0x1",
        "A2 is 0x00000010",
        "(0x00001070).B is 0xEE",
    });
    When({
        "BTST.B D1, (0x5E, PC, A2.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0x1",
        "A2 is 0x00000010",
        "(0x00001070).B is 0xEE",
    });
}

TEST_F(BTSTDynamicTestByte, ImmediateWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0",
    });
    When({
        "BTST.B D1, #0xEE"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 8",
        "D1 is 0x0",
    });
}

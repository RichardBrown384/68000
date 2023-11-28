#include "M68000/Fixtures/M68000Test.h"

class BCHGDynamicTestByte : public M68000Test {};

TEST_F(BCHGDynamicTestByte, BitSetWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x3",
        "A1 is 0x2000",
        "(0x2000).B is 0xFF",
    });
    When({
        "BCHG.B D1, (A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x3",
        "A1 is 0x2000",
        "(0x2000).B is 0xF7",
    });
}

TEST_F(BCHGDynamicTestByte, BitClearWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xB",
        "A1 is 0x2000",
        "(0x2000).B is 0xF7",
    });
    When({
        "BCHG.B D1, (A1)"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0xB",
        "A1 is 0x2000",
        "(0x2000).B is 0xFF",
    });
}

TEST_F(BCHGDynamicTestByte, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x4",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFF",
    });
    When({
        "BCHG.B D1, (A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x4",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
    });
}

TEST_F(BCHGDynamicTestByte, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x4",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFF",
    });
    When({
        "BCHG.B D1, (A4)+"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x4",
        "A4 is 0x00006001",
        "(0x00006000).B is 0xEF",
    });
}

TEST_F(BCHGDynamicTestByte, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x4",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xFF",
    });
    When({
        "BCHG.B D1, -(A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x4",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xEF",
    });
}

TEST_F(BCHGDynamicTestByte, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x4",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xFF",
    });
    When({
        "BCHG.B D1, (0x004C, A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "D1 is 0x4",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
    });
}

TEST_F(BCHGDynamicTestByte, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x4",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xFF",
    });
    When({
        "BCHG.B D1, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "D1 is 0x4",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
    });
}

TEST_F(BCHGDynamicTestByte, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x4",
        "(0x00006000).B is 0xFF",
    });
    When({
        "BCHG.B D1, (0x6000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "D1 is 0x4",
        "(0x00006000).B is 0xEF",
    });
}

TEST_F(BCHGDynamicTestByte, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x4",
        "(0x00006000).B is 0xFF",
    });
    When({
        "BCHG.B D1, (0x00006000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 20",
        "D1 is 0x4",
        "(0x00006000).B is 0xEF",
    });
}

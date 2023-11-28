#include "M68000/Fixtures/M68000Test.h"

class BCHGStaticTestByte : public M68000Test {};

TEST_F(BCHGStaticTestByte, BitSetWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x2000",
        "(0x2000).B is 0xFF",
    });
    When({
        "BCHG.B #0xB, (A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "A1 is 0x2000",
        "(0x2000).B is 0xF7",
    });
}

TEST_F(BCHGStaticTestByte, BitClearWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x2000",
        "(0x2000).B is 0xF7",
    });
    When({
        "BCHG.B #0x3, (A1)"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 16",
        "A1 is 0x2000",
        "(0x2000).B is 0xFF",
    });
}

TEST_F(BCHGStaticTestByte, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0x15",
    });
    When({
        "BCHG.B #0x44, (A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "A4 is 0x00006000",
        "(0x00006000).B is 0x05",
    });
}

TEST_F(BCHGStaticTestByte, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0x15",
    });
    When({
        "BCHG.B #0x44, (A4)+"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "A4 is 0x00006001",
        "(0x00006000).B is 0x05",
    });
}

TEST_F(BCHGStaticTestByte, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0x15",
    });
    When({
        "BCHG.B #0x44, -(A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x05",
    });
}

TEST_F(BCHGStaticTestByte, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x15",
    });
    When({
        "BCHG.B #0x44, (0x004C, A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 20",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x05",
    });
}

TEST_F(BCHGStaticTestByte, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x15",
    });
    When({
        "BCHG.B #0x44, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 22",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x05",
    });
}

TEST_F(BCHGStaticTestByte, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).B is 0x15",
    });
    When({
        "BCHG.B #0x44, (0x6000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 20",
        "(0x00006000).B is 0x05",
    });
}

TEST_F(BCHGStaticTestByte, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).B is 0x15",
    });
    When({
        "BCHG.B #0x44, (0x00006000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1008",
        "CYCLES is 24",
        "(0x00006000).B is 0x05",
    });
}

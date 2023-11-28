#include "M68000/Fixtures/M68000Test.h"

class BCLRStaticTestByte : public M68000Test {};

TEST_F(BCLRStaticTestByte, BitSetWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x2000",
        "(0x2000).B is 0xFF",
    });
    When({
        "BCLR.B #0xB, (A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "A1 is 0x2000",
        "(0x2000).B is 0xF7",
    });
}

TEST_F(BCLRStaticTestByte, BitClearWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x2000",
        "(0x2000).B is 0xF7",
    });
    When({
        "BCLR.B #0x3, (A1)"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 16",
        "A1 is 0x2000",
        "(0x2000).B is 0xF7",
    });
}

TEST_F(BCLRStaticTestByte, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0x15",
    });
    When({
        "BCLR.B #0x44, (A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "A4 is 0x00006000",
        "(0x00006000).B is 0x05",
    });
}

TEST_F(BCLRStaticTestByte, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0x15",
    });
    When({
        "BCLR.B #0x44, (A4)+"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "A4 is 0x00006001",
        "(0x00006000).B is 0x05",
    });
}

TEST_F(BCLRStaticTestByte, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0x15",
    });
    When({
        "BCLR.B #0x44, -(A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x05",
    });
}

TEST_F(BCLRStaticTestByte, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x15",
    });
    When({
        "BCLR.B #0x44, (0x004C, A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 20",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x05",
    });
}

TEST_F(BCLRStaticTestByte, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x15",
    });
    When({
        "BCLR.B #0x44, (0x6E, A4, A5.L)"
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

TEST_F(BCLRStaticTestByte, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).B is 0x15",
    });
    When({
        "BCLR.B #0x44, (0x6000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 20",
        "(0x00006000).B is 0x05",
    });
}

TEST_F(BCLRStaticTestByte, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).B is 0x15",
    });
    When({
        "BCLR.B #0x44, (0x00006000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1008",
        "CYCLES is 24",
        "(0x00006000).B is 0x05",
    });
}

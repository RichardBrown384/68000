#include "M68000/Fixtures/M68000Test.h"

class BTSTStaticTestByte : public M68000Test {};

TEST_F(BTSTStaticTestByte, BitSetWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "A1 is 0x2000",
        "(0x2000).B is 0xFF",
    });
    When({
        "BTST.B #0xB, (A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "A1 is 0x2000",
        "(0x2000).B is 0xFF",
    });
}

TEST_F(BTSTStaticTestByte, BitClearWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x2000",
        "(0x2000).B is 0xF7",
    });
    When({
        "BTST.B #0x3, (A1)"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 12",
        "A1 is 0x2000",
        "(0x2000).B is 0xF7",
    });
}

TEST_F(BTSTStaticTestByte, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0x05",
    });
    When({
        "BTST.B #0x44, (A4)"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 12",
        "A4 is 0x00006000",
        "(0x00006000).B is 0x05",
    });
}

TEST_F(BTSTStaticTestByte, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0x15",
    });
    When({
        "BTST.B #0x44, (A4)+"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "A4 is 0x00006001",
        "(0x00006000).B is 0x15",
    });
}

TEST_F(BTSTStaticTestByte, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0x05",
    });
    When({
        "BTST.B #0x44, -(A4)"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 14",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x05",
    });
}

TEST_F(BTSTStaticTestByte, AddressDisplacementWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x15",
    });
    When({
        "BTST.B #0x44, (0x004C, A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 16",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x15",
    });
}

TEST_F(BTSTStaticTestByte, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x05",
    });
    When({
        "BTST.B #0x44, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1006",
        "CYCLES is 18",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x05",
    });
}

TEST_F(BTSTStaticTestByte, ShortWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "(0x00006000).B is 0x15",
    });
    When({
        "BTST.B #0x44, (0x6000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 16",
        "(0x00006000).B is 0x15",
    });
}

TEST_F(BTSTStaticTestByte, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).B is 0x05",
    });
    When({
        "BTST.B #0x44, (0x00006000).L"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1008",
        "CYCLES is 20",
        "(0x00006000).B is 0x05",
    });
}

TEST_F(BTSTStaticTestByte, PCDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x0000103E).B is 0xEE",
    });
    When({
        "BTST.B #0x1, (0x003C, PC)"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1006",
        "CYCLES is 16",
        "(0x0000103E).B is 0xEE",
    });
}

TEST_F(BTSTStaticTestByte, PCIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A2 is 0x00000010",
        "(0x00001070).B is 0xEE",
    });
    When({
        "BTST.B #0x0, (0x5E, PC, A2.L)"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1006",
        "CYCLES is 18",
        "A2 is 0x00000010",
        "(0x00001070).B is 0xEE",
    });
}

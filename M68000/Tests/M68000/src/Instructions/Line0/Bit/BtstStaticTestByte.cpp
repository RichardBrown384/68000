#include "M68000/Fixtures/M68000Test.h"

class BTSTStaticTestByte : public M68000Test {};

TEST_F(BTSTStaticTestByte, BitSetWorks) {
    Given({
        "A1 is 0x2000",
        "(0x2000).B is 0xFF",
        "SR is S,0,Z"
    });
    When({
        "BTST.B #0xB, (A1)"
    });
    Then({
        "A1 is 0x2000",
        "(0x2000).B is 0xFF",
        "SR is S,0,0"
    });
}

TEST_F(BTSTStaticTestByte, BitClearWorks) {
    Given({
        "A1 is 0x2000",
        "(0x2000).B is 0xF7",
        "SR is S,0,0"
    });
    When({
        "BTST.B #0x3, (A1)"
    });
    Then({
        "A1 is 0x2000",
        "(0x2000).B is 0xF7",
        "SR is S,0,Z"
    });
}

TEST_F(BTSTStaticTestByte, AddressIndirectWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x05",
        "SR is S,0,0"
    });
    When({
        "BTST.B #0x44, (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x05",
        "SR is S,0,Z"
    });
}

TEST_F(BTSTStaticTestByte, AddressIncrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "BTST.B #0x44, (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0x15",
        "SR is S,0,0"
    });
}

TEST_F(BTSTStaticTestByte, AddressDecrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0x05",
        "SR is S,0,0"
    });
    When({
        "BTST.B #0x44, -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x05",
        "SR is S,0,Z"
    });
}

TEST_F(BTSTStaticTestByte, AddressDisplacementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x15",
        "SR is S,0,Z"
    });
    When({
        "BTST.B #0x44, (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x15",
        "SR is S,0,0"
    });
}

TEST_F(BTSTStaticTestByte, AddressIndexWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x05",
        "SR is S,0,0"
    });
    When({
        "BTST.B #0x44, (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x05",
        "SR is S,0,Z"
    });
}

TEST_F(BTSTStaticTestByte, ShortWorks) {
    Given({
        "(0x00006000).B is 0x15",
        "SR is S,0,Z"
    });
    When({
        "BTST.B #0x44, (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0x15",
        "SR is S,0,0"
    });
}

TEST_F(BTSTStaticTestByte, LongWorks) {
    Given({
        "(0x00006000).B is 0x05",
        "SR is S,0,0"
    });
    When({
        "BTST.B #0x44, (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0x05",
        "SR is S,0,Z"
    });
}

TEST_F(BTSTStaticTestByte, PCDisplacementWorks) {
    Given({
        "(0x0000103E).B is 0xEE",
        "SR is S,0,0"
    });
    When({
        "BTST.B #0x1, (0x003C, PC)"
    });
    Then({
        "(0x0000103E).B is 0xEE",
        "SR is S,0,Z"
    });
}

TEST_F(BTSTStaticTestByte, PCIndexWorks) {
    Given({
        "A2 is 0x00000010",
        "(0x00001070).B is 0xEE",
        "SR is S,0,0"
    });
    When({
        "BTST.B #0x0, (0x5E, PC, A2.L)"
    });
    Then({
        "A2 is 0x00000010",
        "(0x00001070).B is 0xEE",
        "SR is S,0,Z"
    });
}

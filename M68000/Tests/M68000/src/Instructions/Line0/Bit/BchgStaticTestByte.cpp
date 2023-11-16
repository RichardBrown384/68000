#include "M68000/Fixtures/M68000Test.h"

class BCHGStaticTestByte : public M68000Test {};

TEST_F(BCHGStaticTestByte, BitSetWorks) {
    Given({
        "A1 is 0x2000",
        "(0x2000).B is 0xFF",
        "SR is S,0,0"
    });
    When({
        "BCHG.B #0xB, (A1)"
    });
    Then({
        "A1 is 0x2000",
        "(0x2000).B is 0xF7",
        "SR is S,0,0"
    });
}

TEST_F(BCHGStaticTestByte, BitClearWorks) {
    Given({
        "A1 is 0x2000",
        "(0x2000).B is 0xF7",
        "SR is S,0,0"
    });
    When({
        "BCHG.B #0x3, (A1)"
    });
    Then({
        "A1 is 0x2000",
        "(0x2000).B is 0xFF",
        "SR is S,0,Z"
    });
}

TEST_F(BCHGStaticTestByte, AddressIndirectWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "BCHG.B #0x44, (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x05",
        "SR is S,0,0"
    });
}

TEST_F(BCHGStaticTestByte, AddressIncrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "BCHG.B #0x44, (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0x05",
        "SR is S,0,0"
    });
}

TEST_F(BCHGStaticTestByte, AddressDecrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "BCHG.B #0x44, -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x05",
        "SR is S,0,0"
    });
}

TEST_F(BCHGStaticTestByte, AddressDisplacementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "BCHG.B #0x44, (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x05",
        "SR is S,0,0"
    });
}

TEST_F(BCHGStaticTestByte, AddressIndexWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "BCHG.B #0x44, (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x05",
        "SR is S,0,0"
    });
}

TEST_F(BCHGStaticTestByte, ShortWorks) {
    Given({
        "(0x00006000).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "BCHG.B #0x44, (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0x05",
        "SR is S,0,0"
    });
}

TEST_F(BCHGStaticTestByte, LongWorks) {
    Given({
        "(0x00006000).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "BCHG.B #0x44, (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0x05",
        "SR is S,0,0"
    });
}

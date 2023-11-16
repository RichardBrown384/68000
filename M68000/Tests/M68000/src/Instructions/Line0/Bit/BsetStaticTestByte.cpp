#include "M68000/Fixtures/M68000Test.h"

class BSETStaticTestByte : public M68000Test {};

TEST_F(BSETStaticTestByte, BitSetWorks) {
    Given({
        "A1 is 0x2000",
        "(0x2000).B is 0xFF",
        "SR is S,0,0"
    });
    When({
        "BSET.B #0xB, (A1)"
    });
    Then({
        "A1 is 0x2000",
        "(0x2000).B is 0xFF",
        "SR is S,0,0"
    });
}

TEST_F(BSETStaticTestByte, BitClearWorks) {
    Given({
        "A1 is 0x2000",
        "(0x2000).B is 0xF7",
        "SR is S,0,0"
    });
    When({
        "BSET.B #0x3, (A1)"
    });
    Then({
        "A1 is 0x2000",
        "(0x2000).B is 0xFF",
        "SR is S,0,Z"
    });
}

TEST_F(BSETStaticTestByte, AddressIndirectWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x05",
        "SR is S,0,0"
    });
    When({
        "BSET.B #0x44, (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x15",
        "SR is S,0,Z"
    });
}

TEST_F(BSETStaticTestByte, AddressIncrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x05",
        "SR is S,0,0"
    });
    When({
        "BSET.B #0x44, (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0x15",
        "SR is S,0,Z"
    });
}

TEST_F(BSETStaticTestByte, AddressDecrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0x05",
        "SR is S,0,0"
    });
    When({
        "BSET.B #0x44, -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x15",
        "SR is S,0,Z"
    });
}

TEST_F(BSETStaticTestByte, AddressDisplacementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x05",
        "SR is S,0,0"
    });
    When({
        "BSET.B #0x44, (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x15",
        "SR is S,0,Z"
    });
}

TEST_F(BSETStaticTestByte, AddressIndexWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x05",
        "SR is S,0,0"
    });
    When({
        "BSET.B #0x44, (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x15",
        "SR is S,0,Z"
    });
}

TEST_F(BSETStaticTestByte, ShortWorks) {
    Given({
        "(0x00006000).B is 0x05",
        "SR is S,0,0"
    });
    When({
        "BSET.B #0x44, (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0x15",
        "SR is S,0,Z"
    });
}

TEST_F(BSETStaticTestByte, LongWorks) {
    Given({
        "(0x00006000).B is 0x05",
        "SR is S,0,0"
    });
    When({
        "BSET.B #0x44, (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0x15",
        "SR is S,0,Z"
    });
}

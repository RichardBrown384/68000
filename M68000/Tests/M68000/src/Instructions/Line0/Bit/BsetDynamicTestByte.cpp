#include "M68000/Fixtures/M68000Test.h"

class BSETDynamicTestByte : public M68000Test {};

TEST_F(BSETDynamicTestByte, BitSetWorks) {
    Given({
        "D1 is 0x3",
        "A1 is 0x2000",
        "(0x2000).B is 0xFF",
        "SR is S,0,Z"
    });
    When({
        "BSET.B D1, (A1)"
    });
    Then({
        "D1 is 0x3",
        "A1 is 0x2000",
        "(0x2000).B is 0xFF",
        "SR is S,0,0"
    });
}

TEST_F(BSETDynamicTestByte, BitClearWorks) {
    Given({
        "D1 is 0xB",
        "A1 is 0x2000",
        "(0x2000).B is 0xF7",
        "SR is S,0,0"
    });
    When({
        "BSET.B D1, (A1)"
    });
    Then({
        "D1 is 0xB",
        "A1 is 0x2000",
        "(0x2000).B is 0xFF",
        "SR is S,0,Z"
    });
}

TEST_F(BSETDynamicTestByte, AddressIndirectWorks) {
    Given({
        "D1 is 0x4",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "BSET.B D1, (A4)"
    });
    Then({
        "D1 is 0x4",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFF",
        "SR is S,0,Z"
    });
}

TEST_F(BSETDynamicTestByte, AddressIncrementWorks) {
    Given({
        "D1 is 0x4",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "BSET.B D1, (A4)+"
    });
    Then({
        "D1 is 0x4",
        "A4 is 0x00006001",
        "(0x00006000).B is 0xFF",
        "SR is S,0,Z"
    });
}

TEST_F(BSETDynamicTestByte, AddressDecrementWorks) {
    Given({
        "D1 is 0x4",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "BSET.B D1, -(A4)"
    });
    Then({
        "D1 is 0x4",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xFF",
        "SR is S,0,Z"
    });
}

TEST_F(BSETDynamicTestByte, AddressDisplacementWorks) {
    Given({
        "D1 is 0x4",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "BSET.B D1, (0x004C, A4)"
    });
    Then({
        "D1 is 0x4",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xFF",
        "SR is S,0,Z"
    });
}

TEST_F(BSETDynamicTestByte, AddressIndexWorks) {
    Given({
        "D1 is 0x4",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "BSET.B D1, (0x6E, A4, A5.L)"
    });
    Then({
        "D1 is 0x4",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xFF",
        "SR is S,0,Z"
    });
}

TEST_F(BSETDynamicTestByte, ShortWorks) {
    Given({
        "D1 is 0x4",
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "BSET.B D1, (0x6000).W"
    });
    Then({
        "D1 is 0x4",
        "(0x00006000).B is 0xFF",
        "SR is S,0,Z"
    });
}

TEST_F(BSETDynamicTestByte, LongWorks) {
    Given({
        "D1 is 0x4",
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "BSET.B D1, (0x00006000).L"
    });
    Then({
        "D1 is 0x4",
        "(0x00006000).B is 0xFF",
        "SR is S,0,Z"
    });
}

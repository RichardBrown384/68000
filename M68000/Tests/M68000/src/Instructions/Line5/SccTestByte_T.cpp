#include "M68000/Fixtures/M68000Test.h"

class SccTestByte_T : public M68000Test {};

TEST_F(SccTestByte_T, DataDirectTrueWorks) {
    Given({
        "D4 is 0xDEADBEEF",
        "SR is S,0,0"
    });
    When({
        "ST D4"
    });
    Then({
        "D4 is 0xDEADBEFF",
        "SR is S,0,0",
        "CYCLES is 6"
    });
}

TEST_F(SccTestByte_T, AddressIndirectTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "ST (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_T, AddressIncrementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "ST (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_T, AddressDecrementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "ST -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 14"
    });
}

TEST_F(SccTestByte_T, AddressDisplacementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "ST (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_T, AddressIndexTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "ST (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 18"
    });
}

TEST_F(SccTestByte_T, ShortTrueWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "ST (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_T, LongTrueWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "ST (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 20"
    });
}

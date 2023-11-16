#include "M68000/Fixtures/M68000Test.h"

class SccTestByte_F : public M68000Test {};

TEST_F(SccTestByte_F, DataDirectFalseWorks) {
    Given({
        "D4 is 0xDEADBEEF",
        "SR is S,0,0"
    });
    When({
        "SF D4"
    });
    Then({
        "D4 is 0xDEADBE00",
        "SR is S,0,0",
        "CYCLES is 4"
    });
}

TEST_F(SccTestByte_F, AddressIndirectFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SF (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_F, AddressIncrementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SF (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_F, AddressDecrementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SF -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 14"
    });
}

TEST_F(SccTestByte_F, AddressDisplacementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SF (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_F, AddressIndexFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SF (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 18"
    });
}

TEST_F(SccTestByte_F, ShortFalseWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SF (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_F, LongFalseWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SF (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 20"
    });
}

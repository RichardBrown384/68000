#include "M68000/Fixtures/M68000Test.h"

class SccTestByte_PL : public M68000Test {};

TEST_F(SccTestByte_PL, DataDirectTrueWorks) {
    Given({
        "D4 is 0xDEADBEEF",
        "SR is S,0,0"
    });
    When({
        "SPL D4"
    });
    Then({
        "D4 is 0xDEADBEFF",
        "SR is S,0,0",
        "CYCLES is 6"
    });
}

TEST_F(SccTestByte_PL, AddressIndirectTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SPL (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_PL, AddressIncrementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SPL (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_PL, AddressDecrementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SPL -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 14"
    });
}

TEST_F(SccTestByte_PL, AddressDisplacementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SPL (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_PL, AddressIndexTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SPL (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 18"
    });
}

TEST_F(SccTestByte_PL, ShortTrueWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SPL (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_PL, LongTrueWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SPL (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 20"
    });
}

TEST_F(SccTestByte_PL, DataDirectFalseWorks) {
    Given({
        "D4 is 0xDEADBEEF",
        "SR is S,0,N"
    });
    When({
        "SPL D4"
    });
    Then({
        "D4 is 0xDEADBE00",
        "SR is S,0,N",
        "CYCLES is 4"
    });
}

TEST_F(SccTestByte_PL, AddressIndirectFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,N"
    });
    When({
        "SPL (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x00",
        "SR is S,0,N",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_PL, AddressIncrementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,N"
    });
    When({
        "SPL (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0x00",
        "SR is S,0,N",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_PL, AddressDecrementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
        "SR is S,0,N"
    });
    When({
        "SPL -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x00",
        "SR is S,0,N",
        "CYCLES is 14"
    });
}

TEST_F(SccTestByte_PL, AddressDisplacementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
        "SR is S,0,N"
    });
    When({
        "SPL (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x00",
        "SR is S,0,N",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_PL, AddressIndexFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
        "SR is S,0,N"
    });
    When({
        "SPL (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x00",
        "SR is S,0,N",
        "CYCLES is 18"
    });
}

TEST_F(SccTestByte_PL, ShortFalseWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,N"
    });
    When({
        "SPL (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0x00",
        "SR is S,0,N",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_PL, LongFalseWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,N"
    });
    When({
        "SPL (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0x00",
        "SR is S,0,N",
        "CYCLES is 20"
    });
}

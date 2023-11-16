#include "M68000/Fixtures/M68000Test.h"

class SccTestByte_LS : public M68000Test {};

TEST_F(SccTestByte_LS, DataDirectTrueWorks) {
    Given({
        "D4 is 0xDEADBEEF",
        "SR is S,0,ZC"
    });
    When({
        "SLS D4"
    });
    Then({
        "D4 is 0xDEADBEFF",
        "SR is S,0,ZC",
        "CYCLES is 6"
    });
}

TEST_F(SccTestByte_LS, AddressIndirectTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,ZC"
    });
    When({
        "SLS (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFF",
        "SR is S,0,ZC",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_LS, AddressIncrementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,ZC"
    });
    When({
        "SLS (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0xFF",
        "SR is S,0,ZC",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_LS, AddressDecrementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
        "SR is S,0,ZC"
    });
    When({
        "SLS -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xFF",
        "SR is S,0,ZC",
        "CYCLES is 14"
    });
}

TEST_F(SccTestByte_LS, AddressDisplacementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
        "SR is S,0,ZC"
    });
    When({
        "SLS (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xFF",
        "SR is S,0,ZC",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_LS, AddressIndexTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
        "SR is S,0,ZC"
    });
    When({
        "SLS (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xFF",
        "SR is S,0,ZC",
        "CYCLES is 18"
    });
}

TEST_F(SccTestByte_LS, ShortTrueWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,ZC"
    });
    When({
        "SLS (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0xFF",
        "SR is S,0,ZC",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_LS, LongTrueWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,ZC"
    });
    When({
        "SLS (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0xFF",
        "SR is S,0,ZC",
        "CYCLES is 20"
    });
}

TEST_F(SccTestByte_LS, DataDirectFalseWorks) {
    Given({
        "D4 is 0xDEADBEEF",
        "SR is S,0,0"
    });
    When({
        "SLS D4"
    });
    Then({
        "D4 is 0xDEADBE00",
        "SR is S,0,0",
        "CYCLES is 4"
    });
}

TEST_F(SccTestByte_LS, AddressIndirectFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SLS (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_LS, AddressIncrementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SLS (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_LS, AddressDecrementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SLS -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 14"
    });
}

TEST_F(SccTestByte_LS, AddressDisplacementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SLS (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_LS, AddressIndexFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SLS (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 18"
    });
}

TEST_F(SccTestByte_LS, ShortFalseWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SLS (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_LS, LongFalseWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SLS (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 20"
    });
}

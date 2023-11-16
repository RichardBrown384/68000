#include "M68000/Fixtures/M68000Test.h"

class SccTestByte_HI : public M68000Test {};

TEST_F(SccTestByte_HI, DataDirectTrueWorks) {
    Given({
        "D4 is 0xDEADBEEF",
        "SR is S,0,0"
    });
    When({
        "SHI D4"
    });
    Then({
        "D4 is 0xDEADBEFF",
        "SR is S,0,0",
        "CYCLES is 6"
    });
}

TEST_F(SccTestByte_HI, AddressIndirectTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SHI (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_HI, AddressIncrementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SHI (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_HI, AddressDecrementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SHI -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 14"
    });
}

TEST_F(SccTestByte_HI, AddressDisplacementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SHI (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_HI, AddressIndexTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SHI (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 18"
    });
}

TEST_F(SccTestByte_HI, ShortTrueWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SHI (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_HI, LongTrueWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SHI (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 20"
    });
}

TEST_F(SccTestByte_HI, DataDirectFalseWorks) {
    Given({
        "D4 is 0xDEADBEEF",
        "SR is S,0,ZC"
    });
    When({
        "SHI D4"
    });
    Then({
        "D4 is 0xDEADBE00",
        "SR is S,0,ZC",
        "CYCLES is 4"
    });
}

TEST_F(SccTestByte_HI, AddressIndirectFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,ZC"
    });
    When({
        "SHI (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x00",
        "SR is S,0,ZC",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_HI, AddressIncrementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,ZC"
    });
    When({
        "SHI (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0x00",
        "SR is S,0,ZC",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_HI, AddressDecrementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
        "SR is S,0,ZC"
    });
    When({
        "SHI -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x00",
        "SR is S,0,ZC",
        "CYCLES is 14"
    });
}

TEST_F(SccTestByte_HI, AddressDisplacementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
        "SR is S,0,ZC"
    });
    When({
        "SHI (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x00",
        "SR is S,0,ZC",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_HI, AddressIndexFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
        "SR is S,0,ZC"
    });
    When({
        "SHI (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x00",
        "SR is S,0,ZC",
        "CYCLES is 18"
    });
}

TEST_F(SccTestByte_HI, ShortFalseWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,ZC"
    });
    When({
        "SHI (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0x00",
        "SR is S,0,ZC",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_HI, LongFalseWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,ZC"
    });
    When({
        "SHI (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0x00",
        "SR is S,0,ZC",
        "CYCLES is 20"
    });
}

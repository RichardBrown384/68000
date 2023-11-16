#include "M68000/Fixtures/M68000Test.h"

class SccTestByte_GE : public M68000Test {};

TEST_F(SccTestByte_GE, DataDirectTrueWorks) {
    Given({
        "D4 is 0xDEADBEEF",
        "SR is S,0,NV"
    });
    When({
        "SGE D4"
    });
    Then({
        "D4 is 0xDEADBEFF",
        "SR is S,0,NV",
        "CYCLES is 6"
    });
}

TEST_F(SccTestByte_GE, AddressIndirectTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,NV"
    });
    When({
        "SGE (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFF",
        "SR is S,0,NV",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_GE, AddressIncrementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,NV"
    });
    When({
        "SGE (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0xFF",
        "SR is S,0,NV",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_GE, AddressDecrementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
        "SR is S,0,NV"
    });
    When({
        "SGE -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xFF",
        "SR is S,0,NV",
        "CYCLES is 14"
    });
}

TEST_F(SccTestByte_GE, AddressDisplacementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
        "SR is S,0,NV"
    });
    When({
        "SGE (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xFF",
        "SR is S,0,NV",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_GE, AddressIndexTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
        "SR is S,0,NV"
    });
    When({
        "SGE (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xFF",
        "SR is S,0,NV",
        "CYCLES is 18"
    });
}

TEST_F(SccTestByte_GE, ShortTrueWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,NV"
    });
    When({
        "SGE (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0xFF",
        "SR is S,0,NV",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_GE, LongTrueWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,NV"
    });
    When({
        "SGE (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0xFF",
        "SR is S,0,NV",
        "CYCLES is 20"
    });
}

TEST_F(SccTestByte_GE, DataDirectFalseWorks) {
    Given({
        "D4 is 0xDEADBEEF",
        "SR is S,0,N"
    });
    When({
        "SGE D4"
    });
    Then({
        "D4 is 0xDEADBE00",
        "SR is S,0,N",
        "CYCLES is 4"
    });
}

TEST_F(SccTestByte_GE, AddressIndirectFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,N"
    });
    When({
        "SGE (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x00",
        "SR is S,0,N",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_GE, AddressIncrementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,N"
    });
    When({
        "SGE (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0x00",
        "SR is S,0,N",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_GE, AddressDecrementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
        "SR is S,0,N"
    });
    When({
        "SGE -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x00",
        "SR is S,0,N",
        "CYCLES is 14"
    });
}

TEST_F(SccTestByte_GE, AddressDisplacementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
        "SR is S,0,N"
    });
    When({
        "SGE (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x00",
        "SR is S,0,N",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_GE, AddressIndexFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
        "SR is S,0,N"
    });
    When({
        "SGE (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x00",
        "SR is S,0,N",
        "CYCLES is 18"
    });
}

TEST_F(SccTestByte_GE, ShortFalseWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,N"
    });
    When({
        "SGE (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0x00",
        "SR is S,0,N",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_GE, LongFalseWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,N"
    });
    When({
        "SGE (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0x00",
        "SR is S,0,N",
        "CYCLES is 20"
    });
}

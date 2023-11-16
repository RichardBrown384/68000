#include "M68000/Fixtures/M68000Test.h"

class SccTestByte_LT : public M68000Test {};

TEST_F(SccTestByte_LT, DataDirectTrueWorks) {
    Given({
        "D4 is 0xDEADBEEF",
        "SR is S,0,N"
    });
    When({
        "SLT D4"
    });
    Then({
        "D4 is 0xDEADBEFF",
        "SR is S,0,N",
        "CYCLES is 6"
    });
}

TEST_F(SccTestByte_LT, AddressIndirectTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,N"
    });
    When({
        "SLT (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFF",
        "SR is S,0,N",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_LT, AddressIncrementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,N"
    });
    When({
        "SLT (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0xFF",
        "SR is S,0,N",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_LT, AddressDecrementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
        "SR is S,0,N"
    });
    When({
        "SLT -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xFF",
        "SR is S,0,N",
        "CYCLES is 14"
    });
}

TEST_F(SccTestByte_LT, AddressDisplacementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
        "SR is S,0,N"
    });
    When({
        "SLT (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xFF",
        "SR is S,0,N",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_LT, AddressIndexTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
        "SR is S,0,N"
    });
    When({
        "SLT (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xFF",
        "SR is S,0,N",
        "CYCLES is 18"
    });
}

TEST_F(SccTestByte_LT, ShortTrueWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,N"
    });
    When({
        "SLT (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0xFF",
        "SR is S,0,N",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_LT, LongTrueWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,N"
    });
    When({
        "SLT (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0xFF",
        "SR is S,0,N",
        "CYCLES is 20"
    });
}

TEST_F(SccTestByte_LT, DataDirectFalseWorks) {
    Given({
        "D4 is 0xDEADBEEF",
        "SR is S,0,NV"
    });
    When({
        "SLT D4"
    });
    Then({
        "D4 is 0xDEADBE00",
        "SR is S,0,NV",
        "CYCLES is 4"
    });
}

TEST_F(SccTestByte_LT, AddressIndirectFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,NV"
    });
    When({
        "SLT (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x00",
        "SR is S,0,NV",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_LT, AddressIncrementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,NV"
    });
    When({
        "SLT (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0x00",
        "SR is S,0,NV",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_LT, AddressDecrementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
        "SR is S,0,NV"
    });
    When({
        "SLT -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x00",
        "SR is S,0,NV",
        "CYCLES is 14"
    });
}

TEST_F(SccTestByte_LT, AddressDisplacementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
        "SR is S,0,NV"
    });
    When({
        "SLT (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x00",
        "SR is S,0,NV",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_LT, AddressIndexFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
        "SR is S,0,NV"
    });
    When({
        "SLT (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x00",
        "SR is S,0,NV",
        "CYCLES is 18"
    });
}

TEST_F(SccTestByte_LT, ShortFalseWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,NV"
    });
    When({
        "SLT (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0x00",
        "SR is S,0,NV",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_LT, LongFalseWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,NV"
    });
    When({
        "SLT (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0x00",
        "SR is S,0,NV",
        "CYCLES is 20"
    });
}

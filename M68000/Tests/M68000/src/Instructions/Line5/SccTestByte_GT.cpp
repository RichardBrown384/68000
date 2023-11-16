#include "M68000/Fixtures/M68000Test.h"

class SccTestByte_GT : public M68000Test {};

TEST_F(SccTestByte_GT, DataDirectTrueWorks) {
    Given({
        "D4 is 0xDEADBEEF",
        "SR is S,0,NV"
    });
    When({
        "SGT D4"
    });
    Then({
        "D4 is 0xDEADBEFF",
        "SR is S,0,NV",
        "CYCLES is 6"
    });
}

TEST_F(SccTestByte_GT, AddressIndirectTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,NV"
    });
    When({
        "SGT (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFF",
        "SR is S,0,NV",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_GT, AddressIncrementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,NV"
    });
    When({
        "SGT (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0xFF",
        "SR is S,0,NV",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_GT, AddressDecrementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
        "SR is S,0,NV"
    });
    When({
        "SGT -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xFF",
        "SR is S,0,NV",
        "CYCLES is 14"
    });
}

TEST_F(SccTestByte_GT, AddressDisplacementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
        "SR is S,0,NV"
    });
    When({
        "SGT (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xFF",
        "SR is S,0,NV",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_GT, AddressIndexTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
        "SR is S,0,NV"
    });
    When({
        "SGT (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xFF",
        "SR is S,0,NV",
        "CYCLES is 18"
    });
}

TEST_F(SccTestByte_GT, ShortTrueWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,NV"
    });
    When({
        "SGT (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0xFF",
        "SR is S,0,NV",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_GT, LongTrueWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,NV"
    });
    When({
        "SGT (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0xFF",
        "SR is S,0,NV",
        "CYCLES is 20"
    });
}

TEST_F(SccTestByte_GT, DataDirectFalseWorks) {
    Given({
        "D4 is 0xDEADBEEF",
        "SR is S,0,NZ"
    });
    When({
        "SGT D4"
    });
    Then({
        "D4 is 0xDEADBE00",
        "SR is S,0,NZ",
        "CYCLES is 4"
    });
}

TEST_F(SccTestByte_GT, AddressIndirectFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,NZ"
    });
    When({
        "SGT (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x00",
        "SR is S,0,NZ",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_GT, AddressIncrementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,NZ"
    });
    When({
        "SGT (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0x00",
        "SR is S,0,NZ",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_GT, AddressDecrementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
        "SR is S,0,NZ"
    });
    When({
        "SGT -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x00",
        "SR is S,0,NZ",
        "CYCLES is 14"
    });
}

TEST_F(SccTestByte_GT, AddressDisplacementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
        "SR is S,0,NZ"
    });
    When({
        "SGT (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x00",
        "SR is S,0,NZ",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_GT, AddressIndexFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
        "SR is S,0,NZ"
    });
    When({
        "SGT (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x00",
        "SR is S,0,NZ",
        "CYCLES is 18"
    });
}

TEST_F(SccTestByte_GT, ShortFalseWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,NZ"
    });
    When({
        "SGT (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0x00",
        "SR is S,0,NZ",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_GT, LongFalseWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,NZ"
    });
    When({
        "SGT (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0x00",
        "SR is S,0,NZ",
        "CYCLES is 20"
    });
}

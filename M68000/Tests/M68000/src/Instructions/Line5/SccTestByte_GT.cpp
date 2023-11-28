#include "M68000/Fixtures/M68000Test.h"

class SccTestByte_GT : public M68000Test {};

TEST_F(SccTestByte_GT, DataDirectTrueWorks) {
    Given({
        "SR is S,0,NV",
        "PC is 0x1000",
        "D4 is 0xDEADBEEF",
    });
    When({
        "SGT D4"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1002",
        "CYCLES is 6",
        "D4 is 0xDEADBEFF",
    });
}

TEST_F(SccTestByte_GT, AddressIndirectTrueWorks) {
    Given({
        "SR is S,0,NV",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SGT (A4)"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1002",
        "CYCLES is 12",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFF",
    });
}

TEST_F(SccTestByte_GT, AddressIncrementTrueWorks) {
    Given({
        "SR is S,0,NV",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SGT (A4)+"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1002",
        "CYCLES is 12",
        "A4 is 0x00006001",
        "(0x00006000).B is 0xFF",
    });
}

TEST_F(SccTestByte_GT, AddressDecrementTrueWorks) {
    Given({
        "SR is S,0,NV",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
    });
    When({
        "SGT -(A4)"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1002",
        "CYCLES is 14",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xFF",
    });
}

TEST_F(SccTestByte_GT, AddressDisplacementTrueWorks) {
    Given({
        "SR is S,0,NV",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
    });
    When({
        "SGT (0x004C, A4)"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1004",
        "CYCLES is 16",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xFF",
    });
}

TEST_F(SccTestByte_GT, AddressIndexTrueWorks) {
    Given({
        "SR is S,0,NV",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
    });
    When({
        "SGT (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1004",
        "CYCLES is 18",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xFF",
    });
}

TEST_F(SccTestByte_GT, ShortTrueWorks) {
    Given({
        "SR is S,0,NV",
        "PC is 0x1000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SGT (0x6000).W"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1004",
        "CYCLES is 16",
        "(0x00006000).B is 0xFF",
    });
}

TEST_F(SccTestByte_GT, LongTrueWorks) {
    Given({
        "SR is S,0,NV",
        "PC is 0x1000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SGT (0x00006000).L"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1006",
        "CYCLES is 20",
        "(0x00006000).B is 0xFF",
    });
}

TEST_F(SccTestByte_GT, DataDirectFalseWorks) {
    Given({
        "SR is S,0,NZ",
        "PC is 0x1000",
        "D4 is 0xDEADBEEF",
    });
    When({
        "SGT D4"
    });
    Then({
        "SR is S,0,NZ",
        "PC is 0x1002",
        "CYCLES is 4",
        "D4 is 0xDEADBE00",
    });
}

TEST_F(SccTestByte_GT, AddressIndirectFalseWorks) {
    Given({
        "SR is S,0,NZ",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SGT (A4)"
    });
    Then({
        "SR is S,0,NZ",
        "PC is 0x1002",
        "CYCLES is 12",
        "A4 is 0x00006000",
        "(0x00006000).B is 0x00",
    });
}

TEST_F(SccTestByte_GT, AddressIncrementFalseWorks) {
    Given({
        "SR is S,0,NZ",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SGT (A4)+"
    });
    Then({
        "SR is S,0,NZ",
        "PC is 0x1002",
        "CYCLES is 12",
        "A4 is 0x00006001",
        "(0x00006000).B is 0x00",
    });
}

TEST_F(SccTestByte_GT, AddressDecrementFalseWorks) {
    Given({
        "SR is S,0,NZ",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
    });
    When({
        "SGT -(A4)"
    });
    Then({
        "SR is S,0,NZ",
        "PC is 0x1002",
        "CYCLES is 14",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x00",
    });
}

TEST_F(SccTestByte_GT, AddressDisplacementFalseWorks) {
    Given({
        "SR is S,0,NZ",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
    });
    When({
        "SGT (0x004C, A4)"
    });
    Then({
        "SR is S,0,NZ",
        "PC is 0x1004",
        "CYCLES is 16",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x00",
    });
}

TEST_F(SccTestByte_GT, AddressIndexFalseWorks) {
    Given({
        "SR is S,0,NZ",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
    });
    When({
        "SGT (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,NZ",
        "PC is 0x1004",
        "CYCLES is 18",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x00",
    });
}

TEST_F(SccTestByte_GT, ShortFalseWorks) {
    Given({
        "SR is S,0,NZ",
        "PC is 0x1000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SGT (0x6000).W"
    });
    Then({
        "SR is S,0,NZ",
        "PC is 0x1004",
        "CYCLES is 16",
        "(0x00006000).B is 0x00",
    });
}

TEST_F(SccTestByte_GT, LongFalseWorks) {
    Given({
        "SR is S,0,NZ",
        "PC is 0x1000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SGT (0x00006000).L"
    });
    Then({
        "SR is S,0,NZ",
        "PC is 0x1006",
        "CYCLES is 20",
        "(0x00006000).B is 0x00",
    });
}

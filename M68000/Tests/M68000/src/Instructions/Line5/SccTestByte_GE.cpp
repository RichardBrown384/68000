#include "M68000/Fixtures/M68000Test.h"

class SccTestByte_GE : public M68000Test {};

TEST_F(SccTestByte_GE, DataDirectTrueWorks) {
    Given({
        "SR is S,0,NV",
        "PC is 0x1000",
        "D4 is 0xDEADBEEF",
    });
    When({
        "SGE D4"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1002",
        "CYCLES is 6",
        "D4 is 0xDEADBEFF",
    });
}

TEST_F(SccTestByte_GE, AddressIndirectTrueWorks) {
    Given({
        "SR is S,0,NV",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SGE (A4)"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1002",
        "CYCLES is 12",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFF",
    });
}

TEST_F(SccTestByte_GE, AddressIncrementTrueWorks) {
    Given({
        "SR is S,0,NV",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SGE (A4)+"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1002",
        "CYCLES is 12",
        "A4 is 0x00006001",
        "(0x00006000).B is 0xFF",
    });
}

TEST_F(SccTestByte_GE, AddressDecrementTrueWorks) {
    Given({
        "SR is S,0,NV",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
    });
    When({
        "SGE -(A4)"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1002",
        "CYCLES is 14",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xFF",
    });
}

TEST_F(SccTestByte_GE, AddressDisplacementTrueWorks) {
    Given({
        "SR is S,0,NV",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
    });
    When({
        "SGE (0x004C, A4)"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1004",
        "CYCLES is 16",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xFF",
    });
}

TEST_F(SccTestByte_GE, AddressIndexTrueWorks) {
    Given({
        "SR is S,0,NV",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
    });
    When({
        "SGE (0x6E, A4, A5.L)"
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

TEST_F(SccTestByte_GE, ShortTrueWorks) {
    Given({
        "SR is S,0,NV",
        "PC is 0x1000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SGE (0x6000).W"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1004",
        "CYCLES is 16",
        "(0x00006000).B is 0xFF",
    });
}

TEST_F(SccTestByte_GE, LongTrueWorks) {
    Given({
        "SR is S,0,NV",
        "PC is 0x1000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SGE (0x00006000).L"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1006",
        "CYCLES is 20",
        "(0x00006000).B is 0xFF",
    });
}

TEST_F(SccTestByte_GE, DataDirectFalseWorks) {
    Given({
        "SR is S,0,N",
        "PC is 0x1000",
        "D4 is 0xDEADBEEF",
    });
    When({
        "SGE D4"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 4",
        "D4 is 0xDEADBE00",
    });
}

TEST_F(SccTestByte_GE, AddressIndirectFalseWorks) {
    Given({
        "SR is S,0,N",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SGE (A4)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 12",
        "A4 is 0x00006000",
        "(0x00006000).B is 0x00",
    });
}

TEST_F(SccTestByte_GE, AddressIncrementFalseWorks) {
    Given({
        "SR is S,0,N",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SGE (A4)+"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 12",
        "A4 is 0x00006001",
        "(0x00006000).B is 0x00",
    });
}

TEST_F(SccTestByte_GE, AddressDecrementFalseWorks) {
    Given({
        "SR is S,0,N",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
    });
    When({
        "SGE -(A4)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 14",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x00",
    });
}

TEST_F(SccTestByte_GE, AddressDisplacementFalseWorks) {
    Given({
        "SR is S,0,N",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
    });
    When({
        "SGE (0x004C, A4)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 16",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x00",
    });
}

TEST_F(SccTestByte_GE, AddressIndexFalseWorks) {
    Given({
        "SR is S,0,N",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
    });
    When({
        "SGE (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 18",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x00",
    });
}

TEST_F(SccTestByte_GE, ShortFalseWorks) {
    Given({
        "SR is S,0,N",
        "PC is 0x1000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SGE (0x6000).W"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 16",
        "(0x00006000).B is 0x00",
    });
}

TEST_F(SccTestByte_GE, LongFalseWorks) {
    Given({
        "SR is S,0,N",
        "PC is 0x1000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SGE (0x00006000).L"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 20",
        "(0x00006000).B is 0x00",
    });
}

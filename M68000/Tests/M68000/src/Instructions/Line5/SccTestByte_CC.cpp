#include "M68000/Fixtures/M68000Test.h"

class SccTestByte_CC : public M68000Test {};

TEST_F(SccTestByte_CC, DataDirectTrueWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xDEADBEEF",
    });
    When({
        "SCC D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 6",
        "D4 is 0xDEADBEFF",
    });
}

TEST_F(SccTestByte_CC, AddressIndirectTrueWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SCC (A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFF",
    });
}

TEST_F(SccTestByte_CC, AddressIncrementTrueWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SCC (A4)+"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "A4 is 0x00006001",
        "(0x00006000).B is 0xFF",
    });
}

TEST_F(SccTestByte_CC, AddressDecrementTrueWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
    });
    When({
        "SCC -(A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xFF",
    });
}

TEST_F(SccTestByte_CC, AddressDisplacementTrueWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
    });
    When({
        "SCC (0x004C, A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xFF",
    });
}

TEST_F(SccTestByte_CC, AddressIndexTrueWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
    });
    When({
        "SCC (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xFF",
    });
}

TEST_F(SccTestByte_CC, ShortTrueWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SCC (0x6000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "(0x00006000).B is 0xFF",
    });
}

TEST_F(SccTestByte_CC, LongTrueWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SCC (0x00006000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 20",
        "(0x00006000).B is 0xFF",
    });
}

TEST_F(SccTestByte_CC, DataDirectFalseWorks) {
    Given({
        "SR is S,0,C",
        "PC is 0x1000",
        "D4 is 0xDEADBEEF",
    });
    When({
        "SCC D4"
    });
    Then({
        "SR is S,0,C",
        "PC is 0x1002",
        "CYCLES is 4",
        "D4 is 0xDEADBE00",
    });
}

TEST_F(SccTestByte_CC, AddressIndirectFalseWorks) {
    Given({
        "SR is S,0,C",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SCC (A4)"
    });
    Then({
        "SR is S,0,C",
        "PC is 0x1002",
        "CYCLES is 12",
        "A4 is 0x00006000",
        "(0x00006000).B is 0x00",
    });
}

TEST_F(SccTestByte_CC, AddressIncrementFalseWorks) {
    Given({
        "SR is S,0,C",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SCC (A4)+"
    });
    Then({
        "SR is S,0,C",
        "PC is 0x1002",
        "CYCLES is 12",
        "A4 is 0x00006001",
        "(0x00006000).B is 0x00",
    });
}

TEST_F(SccTestByte_CC, AddressDecrementFalseWorks) {
    Given({
        "SR is S,0,C",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
    });
    When({
        "SCC -(A4)"
    });
    Then({
        "SR is S,0,C",
        "PC is 0x1002",
        "CYCLES is 14",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x00",
    });
}

TEST_F(SccTestByte_CC, AddressDisplacementFalseWorks) {
    Given({
        "SR is S,0,C",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
    });
    When({
        "SCC (0x004C, A4)"
    });
    Then({
        "SR is S,0,C",
        "PC is 0x1004",
        "CYCLES is 16",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x00",
    });
}

TEST_F(SccTestByte_CC, AddressIndexFalseWorks) {
    Given({
        "SR is S,0,C",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
    });
    When({
        "SCC (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,C",
        "PC is 0x1004",
        "CYCLES is 18",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x00",
    });
}

TEST_F(SccTestByte_CC, ShortFalseWorks) {
    Given({
        "SR is S,0,C",
        "PC is 0x1000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SCC (0x6000).W"
    });
    Then({
        "SR is S,0,C",
        "PC is 0x1004",
        "CYCLES is 16",
        "(0x00006000).B is 0x00",
    });
}

TEST_F(SccTestByte_CC, LongFalseWorks) {
    Given({
        "SR is S,0,C",
        "PC is 0x1000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SCC (0x00006000).L"
    });
    Then({
        "SR is S,0,C",
        "PC is 0x1006",
        "CYCLES is 20",
        "(0x00006000).B is 0x00",
    });
}

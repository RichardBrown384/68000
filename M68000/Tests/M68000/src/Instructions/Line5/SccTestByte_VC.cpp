#include "M68000/Fixtures/M68000Test.h"

class SccTestByte_VC : public M68000Test {};

TEST_F(SccTestByte_VC, DataDirectTrueWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xDEADBEEF",
    });
    When({
        "SVC D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 6",
        "D4 is 0xDEADBEFF",
    });
}

TEST_F(SccTestByte_VC, AddressIndirectTrueWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SVC (A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFF",
    });
}

TEST_F(SccTestByte_VC, AddressIncrementTrueWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SVC (A4)+"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "A4 is 0x00006001",
        "(0x00006000).B is 0xFF",
    });
}

TEST_F(SccTestByte_VC, AddressDecrementTrueWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
    });
    When({
        "SVC -(A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xFF",
    });
}

TEST_F(SccTestByte_VC, AddressDisplacementTrueWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
    });
    When({
        "SVC (0x004C, A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xFF",
    });
}

TEST_F(SccTestByte_VC, AddressIndexTrueWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
    });
    When({
        "SVC (0x6E, A4, A5.L)"
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

TEST_F(SccTestByte_VC, ShortTrueWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SVC (0x6000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "(0x00006000).B is 0xFF",
    });
}

TEST_F(SccTestByte_VC, LongTrueWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SVC (0x00006000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 20",
        "(0x00006000).B is 0xFF",
    });
}

TEST_F(SccTestByte_VC, DataDirectFalseWorks) {
    Given({
        "SR is S,0,V",
        "PC is 0x1000",
        "D4 is 0xDEADBEEF",
    });
    When({
        "SVC D4"
    });
    Then({
        "SR is S,0,V",
        "PC is 0x1002",
        "CYCLES is 4",
        "D4 is 0xDEADBE00",
    });
}

TEST_F(SccTestByte_VC, AddressIndirectFalseWorks) {
    Given({
        "SR is S,0,V",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SVC (A4)"
    });
    Then({
        "SR is S,0,V",
        "PC is 0x1002",
        "CYCLES is 12",
        "A4 is 0x00006000",
        "(0x00006000).B is 0x00",
    });
}

TEST_F(SccTestByte_VC, AddressIncrementFalseWorks) {
    Given({
        "SR is S,0,V",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SVC (A4)+"
    });
    Then({
        "SR is S,0,V",
        "PC is 0x1002",
        "CYCLES is 12",
        "A4 is 0x00006001",
        "(0x00006000).B is 0x00",
    });
}

TEST_F(SccTestByte_VC, AddressDecrementFalseWorks) {
    Given({
        "SR is S,0,V",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
    });
    When({
        "SVC -(A4)"
    });
    Then({
        "SR is S,0,V",
        "PC is 0x1002",
        "CYCLES is 14",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x00",
    });
}

TEST_F(SccTestByte_VC, AddressDisplacementFalseWorks) {
    Given({
        "SR is S,0,V",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
    });
    When({
        "SVC (0x004C, A4)"
    });
    Then({
        "SR is S,0,V",
        "PC is 0x1004",
        "CYCLES is 16",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x00",
    });
}

TEST_F(SccTestByte_VC, AddressIndexFalseWorks) {
    Given({
        "SR is S,0,V",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
    });
    When({
        "SVC (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,V",
        "PC is 0x1004",
        "CYCLES is 18",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x00",
    });
}

TEST_F(SccTestByte_VC, ShortFalseWorks) {
    Given({
        "SR is S,0,V",
        "PC is 0x1000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SVC (0x6000).W"
    });
    Then({
        "SR is S,0,V",
        "PC is 0x1004",
        "CYCLES is 16",
        "(0x00006000).B is 0x00",
    });
}

TEST_F(SccTestByte_VC, LongFalseWorks) {
    Given({
        "SR is S,0,V",
        "PC is 0x1000",
        "(0x00006000).B is 0xEF",
    });
    When({
        "SVC (0x00006000).L"
    });
    Then({
        "SR is S,0,V",
        "PC is 0x1006",
        "CYCLES is 20",
        "(0x00006000).B is 0x00",
    });
}

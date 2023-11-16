#include "M68000/Fixtures/M68000Test.h"

class SccTestByte_EQ : public M68000Test {};

TEST_F(SccTestByte_EQ, DataDirectTrueWorks) {
    Given({
        "D4 is 0xDEADBEEF",
        "SR is S,0,Z"
    });
    When({
        "SEQ D4"
    });
    Then({
        "D4 is 0xDEADBEFF",
        "SR is S,0,Z",
        "CYCLES is 6"
    });
}

TEST_F(SccTestByte_EQ, AddressIndirectTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,Z"
    });
    When({
        "SEQ (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFF",
        "SR is S,0,Z",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_EQ, AddressIncrementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,Z"
    });
    When({
        "SEQ (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0xFF",
        "SR is S,0,Z",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_EQ, AddressDecrementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
        "SR is S,0,Z"
    });
    When({
        "SEQ -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xFF",
        "SR is S,0,Z",
        "CYCLES is 14"
    });
}

TEST_F(SccTestByte_EQ, AddressDisplacementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
        "SR is S,0,Z"
    });
    When({
        "SEQ (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xFF",
        "SR is S,0,Z",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_EQ, AddressIndexTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
        "SR is S,0,Z"
    });
    When({
        "SEQ (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xFF",
        "SR is S,0,Z",
        "CYCLES is 18"
    });
}

TEST_F(SccTestByte_EQ, ShortTrueWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,Z"
    });
    When({
        "SEQ (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0xFF",
        "SR is S,0,Z",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_EQ, LongTrueWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,Z"
    });
    When({
        "SEQ (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0xFF",
        "SR is S,0,Z",
        "CYCLES is 20"
    });
}

TEST_F(SccTestByte_EQ, DataDirectFalseWorks) {
    Given({
        "D4 is 0xDEADBEEF",
        "SR is S,0,0"
    });
    When({
        "SEQ D4"
    });
    Then({
        "D4 is 0xDEADBE00",
        "SR is S,0,0",
        "CYCLES is 4"
    });
}

TEST_F(SccTestByte_EQ, AddressIndirectFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SEQ (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_EQ, AddressIncrementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SEQ (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_EQ, AddressDecrementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SEQ -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 14"
    });
}

TEST_F(SccTestByte_EQ, AddressDisplacementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SEQ (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_EQ, AddressIndexFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SEQ (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 18"
    });
}

TEST_F(SccTestByte_EQ, ShortFalseWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SEQ (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_EQ, LongFalseWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SEQ (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 20"
    });
}

#include "M68000/Fixtures/M68000Test.h"

class SccTestByte_NE : public M68000Test {};

TEST_F(SccTestByte_NE, DataDirectTrueWorks) {
    Given({
        "D4 is 0xDEADBEEF",
        "SR is S,0,0"
    });
    When({
        "SNE D4"
    });
    Then({
        "D4 is 0xDEADBEFF",
        "SR is S,0,0",
        "CYCLES is 6"
    });
}

TEST_F(SccTestByte_NE, AddressIndirectTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SNE (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_NE, AddressIncrementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SNE (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_NE, AddressDecrementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SNE -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 14"
    });
}

TEST_F(SccTestByte_NE, AddressDisplacementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SNE (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_NE, AddressIndexTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SNE (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 18"
    });
}

TEST_F(SccTestByte_NE, ShortTrueWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SNE (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_NE, LongTrueWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SNE (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 20"
    });
}

TEST_F(SccTestByte_NE, DataDirectFalseWorks) {
    Given({
        "D4 is 0xDEADBEEF",
        "SR is S,0,Z"
    });
    When({
        "SNE D4"
    });
    Then({
        "D4 is 0xDEADBE00",
        "SR is S,0,Z",
        "CYCLES is 4"
    });
}

TEST_F(SccTestByte_NE, AddressIndirectFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,Z"
    });
    When({
        "SNE (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x00",
        "SR is S,0,Z",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_NE, AddressIncrementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,Z"
    });
    When({
        "SNE (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0x00",
        "SR is S,0,Z",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_NE, AddressDecrementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
        "SR is S,0,Z"
    });
    When({
        "SNE -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x00",
        "SR is S,0,Z",
        "CYCLES is 14"
    });
}

TEST_F(SccTestByte_NE, AddressDisplacementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
        "SR is S,0,Z"
    });
    When({
        "SNE (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x00",
        "SR is S,0,Z",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_NE, AddressIndexFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
        "SR is S,0,Z"
    });
    When({
        "SNE (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x00",
        "SR is S,0,Z",
        "CYCLES is 18"
    });
}

TEST_F(SccTestByte_NE, ShortFalseWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,Z"
    });
    When({
        "SNE (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0x00",
        "SR is S,0,Z",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_NE, LongFalseWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,Z"
    });
    When({
        "SNE (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0x00",
        "SR is S,0,Z",
        "CYCLES is 20"
    });
}

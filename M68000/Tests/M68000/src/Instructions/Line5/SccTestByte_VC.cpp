#include "M68000/Fixtures/M68000Test.h"

class SccTestByte_VC : public M68000Test {};

TEST_F(SccTestByte_VC, DataDirectTrueWorks) {
    Given({
        "D4 is 0xDEADBEEF",
        "SR is S,0,0"
    });
    When({
        "SVC D4"
    });
    Then({
        "D4 is 0xDEADBEFF",
        "SR is S,0,0",
        "CYCLES is 6"
    });
}

TEST_F(SccTestByte_VC, AddressIndirectTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SVC (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_VC, AddressIncrementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SVC (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_VC, AddressDecrementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SVC -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 14"
    });
}

TEST_F(SccTestByte_VC, AddressDisplacementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SVC (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_VC, AddressIndexTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SVC (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 18"
    });
}

TEST_F(SccTestByte_VC, ShortTrueWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SVC (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_VC, LongTrueWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SVC (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0xFF",
        "SR is S,0,0",
        "CYCLES is 20"
    });
}

TEST_F(SccTestByte_VC, DataDirectFalseWorks) {
    Given({
        "D4 is 0xDEADBEEF",
        "SR is S,0,V"
    });
    When({
        "SVC D4"
    });
    Then({
        "D4 is 0xDEADBE00",
        "SR is S,0,V",
        "CYCLES is 4"
    });
}

TEST_F(SccTestByte_VC, AddressIndirectFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,V"
    });
    When({
        "SVC (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x00",
        "SR is S,0,V",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_VC, AddressIncrementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,V"
    });
    When({
        "SVC (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0x00",
        "SR is S,0,V",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_VC, AddressDecrementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
        "SR is S,0,V"
    });
    When({
        "SVC -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x00",
        "SR is S,0,V",
        "CYCLES is 14"
    });
}

TEST_F(SccTestByte_VC, AddressDisplacementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
        "SR is S,0,V"
    });
    When({
        "SVC (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x00",
        "SR is S,0,V",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_VC, AddressIndexFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
        "SR is S,0,V"
    });
    When({
        "SVC (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x00",
        "SR is S,0,V",
        "CYCLES is 18"
    });
}

TEST_F(SccTestByte_VC, ShortFalseWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,V"
    });
    When({
        "SVC (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0x00",
        "SR is S,0,V",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_VC, LongFalseWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,V"
    });
    When({
        "SVC (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0x00",
        "SR is S,0,V",
        "CYCLES is 20"
    });
}

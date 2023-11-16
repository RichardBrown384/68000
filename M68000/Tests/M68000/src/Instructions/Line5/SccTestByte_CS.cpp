#include "M68000/Fixtures/M68000Test.h"

class SccTestByte_CS : public M68000Test {};

TEST_F(SccTestByte_CS, DataDirectTrueWorks) {
    Given({
        "D4 is 0xDEADBEEF",
        "SR is S,0,C"
    });
    When({
        "SCS D4"
    });
    Then({
        "D4 is 0xDEADBEFF",
        "SR is S,0,C",
        "CYCLES is 6"
    });
}

TEST_F(SccTestByte_CS, AddressIndirectTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,C"
    });
    When({
        "SCS (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFF",
        "SR is S,0,C",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_CS, AddressIncrementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,C"
    });
    When({
        "SCS (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0xFF",
        "SR is S,0,C",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_CS, AddressDecrementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
        "SR is S,0,C"
    });
    When({
        "SCS -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xFF",
        "SR is S,0,C",
        "CYCLES is 14"
    });
}

TEST_F(SccTestByte_CS, AddressDisplacementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
        "SR is S,0,C"
    });
    When({
        "SCS (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xFF",
        "SR is S,0,C",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_CS, AddressIndexTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
        "SR is S,0,C"
    });
    When({
        "SCS (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xFF",
        "SR is S,0,C",
        "CYCLES is 18"
    });
}

TEST_F(SccTestByte_CS, ShortTrueWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,C"
    });
    When({
        "SCS (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0xFF",
        "SR is S,0,C",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_CS, LongTrueWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,C"
    });
    When({
        "SCS (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0xFF",
        "SR is S,0,C",
        "CYCLES is 20"
    });
}

TEST_F(SccTestByte_CS, DataDirectFalseWorks) {
    Given({
        "D4 is 0xDEADBEEF",
        "SR is S,0,0"
    });
    When({
        "SCS D4"
    });
    Then({
        "D4 is 0xDEADBE00",
        "SR is S,0,0",
        "CYCLES is 4"
    });
}

TEST_F(SccTestByte_CS, AddressIndirectFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SCS (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_CS, AddressIncrementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SCS (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_CS, AddressDecrementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SCS -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 14"
    });
}

TEST_F(SccTestByte_CS, AddressDisplacementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SCS (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_CS, AddressIndexFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SCS (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 18"
    });
}

TEST_F(SccTestByte_CS, ShortFalseWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SCS (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_CS, LongFalseWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SCS (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 20"
    });
}

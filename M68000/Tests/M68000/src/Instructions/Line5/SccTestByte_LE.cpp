#include "M68000/Fixtures/M68000Test.h"

class SccTestByte_LE : public M68000Test {};

TEST_F(SccTestByte_LE, DataDirectTrueWorks) {
    Given({
        "D4 is 0xDEADBEEF",
        "SR is S,0,NZ"
    });
    When({
        "SLE D4"
    });
    Then({
        "D4 is 0xDEADBEFF",
        "SR is S,0,NZ",
        "CYCLES is 6"
    });
}

TEST_F(SccTestByte_LE, AddressIndirectTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,NZ"
    });
    When({
        "SLE (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFF",
        "SR is S,0,NZ",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_LE, AddressIncrementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,NZ"
    });
    When({
        "SLE (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0xFF",
        "SR is S,0,NZ",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_LE, AddressDecrementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
        "SR is S,0,NZ"
    });
    When({
        "SLE -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xFF",
        "SR is S,0,NZ",
        "CYCLES is 14"
    });
}

TEST_F(SccTestByte_LE, AddressDisplacementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
        "SR is S,0,NZ"
    });
    When({
        "SLE (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xFF",
        "SR is S,0,NZ",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_LE, AddressIndexTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
        "SR is S,0,NZ"
    });
    When({
        "SLE (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xFF",
        "SR is S,0,NZ",
        "CYCLES is 18"
    });
}

TEST_F(SccTestByte_LE, ShortTrueWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,NZ"
    });
    When({
        "SLE (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0xFF",
        "SR is S,0,NZ",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_LE, LongTrueWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,NZ"
    });
    When({
        "SLE (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0xFF",
        "SR is S,0,NZ",
        "CYCLES is 20"
    });
}

TEST_F(SccTestByte_LE, DataDirectFalseWorks) {
    Given({
        "D4 is 0xDEADBEEF",
        "SR is S,0,NV"
    });
    When({
        "SLE D4"
    });
    Then({
        "D4 is 0xDEADBE00",
        "SR is S,0,NV",
        "CYCLES is 4"
    });
}

TEST_F(SccTestByte_LE, AddressIndirectFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,NV"
    });
    When({
        "SLE (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x00",
        "SR is S,0,NV",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_LE, AddressIncrementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,NV"
    });
    When({
        "SLE (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0x00",
        "SR is S,0,NV",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_LE, AddressDecrementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
        "SR is S,0,NV"
    });
    When({
        "SLE -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x00",
        "SR is S,0,NV",
        "CYCLES is 14"
    });
}

TEST_F(SccTestByte_LE, AddressDisplacementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
        "SR is S,0,NV"
    });
    When({
        "SLE (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x00",
        "SR is S,0,NV",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_LE, AddressIndexFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
        "SR is S,0,NV"
    });
    When({
        "SLE (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x00",
        "SR is S,0,NV",
        "CYCLES is 18"
    });
}

TEST_F(SccTestByte_LE, ShortFalseWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,NV"
    });
    When({
        "SLE (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0x00",
        "SR is S,0,NV",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_LE, LongFalseWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,NV"
    });
    When({
        "SLE (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0x00",
        "SR is S,0,NV",
        "CYCLES is 20"
    });
}

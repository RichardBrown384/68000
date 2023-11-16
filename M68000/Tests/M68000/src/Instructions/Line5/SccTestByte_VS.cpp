#include "M68000/Fixtures/M68000Test.h"

class SccTestByte_VS : public M68000Test {};

TEST_F(SccTestByte_VS, DataDirectTrueWorks) {
    Given({
        "D4 is 0xDEADBEEF",
        "SR is S,0,V"
    });
    When({
        "SVS D4"
    });
    Then({
        "D4 is 0xDEADBEFF",
        "SR is S,0,V",
        "CYCLES is 6"
    });
}

TEST_F(SccTestByte_VS, AddressIndirectTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,V"
    });
    When({
        "SVS (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFF",
        "SR is S,0,V",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_VS, AddressIncrementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,V"
    });
    When({
        "SVS (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0xFF",
        "SR is S,0,V",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_VS, AddressDecrementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
        "SR is S,0,V"
    });
    When({
        "SVS -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xFF",
        "SR is S,0,V",
        "CYCLES is 14"
    });
}

TEST_F(SccTestByte_VS, AddressDisplacementTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
        "SR is S,0,V"
    });
    When({
        "SVS (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xFF",
        "SR is S,0,V",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_VS, AddressIndexTrueWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
        "SR is S,0,V"
    });
    When({
        "SVS (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xFF",
        "SR is S,0,V",
        "CYCLES is 18"
    });
}

TEST_F(SccTestByte_VS, ShortTrueWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,V"
    });
    When({
        "SVS (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0xFF",
        "SR is S,0,V",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_VS, LongTrueWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,V"
    });
    When({
        "SVS (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0xFF",
        "SR is S,0,V",
        "CYCLES is 20"
    });
}

TEST_F(SccTestByte_VS, DataDirectFalseWorks) {
    Given({
        "D4 is 0xDEADBEEF",
        "SR is S,0,0"
    });
    When({
        "SVS D4"
    });
    Then({
        "D4 is 0xDEADBE00",
        "SR is S,0,0",
        "CYCLES is 4"
    });
}

TEST_F(SccTestByte_VS, AddressIndirectFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SVS (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_VS, AddressIncrementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SVS (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(SccTestByte_VS, AddressDecrementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SVS -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 14"
    });
}

TEST_F(SccTestByte_VS, AddressDisplacementFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SVS (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_VS, AddressIndexFalseWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SVS (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 18"
    });
}

TEST_F(SccTestByte_VS, ShortFalseWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SVS (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(SccTestByte_VS, LongFalseWorks) {
    Given({
        "(0x00006000).B is 0xEF",
        "SR is S,0,0"
    });
    When({
        "SVS (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0x00",
        "SR is S,0,0",
        "CYCLES is 20"
    });
}

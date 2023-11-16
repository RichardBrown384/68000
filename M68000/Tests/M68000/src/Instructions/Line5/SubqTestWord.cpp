#include "M68000/Fixtures/M68000Test.h"

class SUBQTestWord : public M68000Test {};

TEST_F(SUBQTestWord, DataDirectWorks) {
    Given({
        "D4 is 0x01000004",
        "SR is S,0,0"
    });
    When({
        "SUBQ.W #0x0006, D4"
    });
    Then({
        "D4 is 0x0100FFFE",
        "SR is S,0,XNC"
    });
}

TEST_F(SUBQTestWord, DataDirectSub8Works) {
    Given({
        "D4 is 0x700F0F07",
        "SR is S,0,0"
    });
    When({
        "SUBQ.W #0x08, D4"
    });
    Then({
        "D4 is 0x700F0EFF",
        "SR is S,0,0"
    });
}

TEST_F(SUBQTestWord, DataDirectFlagNWorks) {
    Given({
        "D4 is 0xFEEFF00E",
        "SR is S,0,0"
    });
    When({
        "SUBQ.W #0x01, D4"
    });
    Then({
        "D4 is 0xFEEFF00D",
        "SR is S,0,N"
    });
}

TEST_F(SUBQTestWord, DataDirectFlagZWorks) {
    Given({
        "D4 is 0xFEEF0001",
        "SR is S,0,0"
    });
    When({
        "SUBQ.W #0x01, D4"
    });
    Then({
        "D4 is 0xFEEF0000",
        "SR is S,0,Z"
    });
}

TEST_F(SUBQTestWord, DataDirectFlagVWorks) {
    Given({
        "D4 is 0xFEEF8000",
        "SR is S,0,0"
    });
    When({
        "SUBQ.W #0x01, D4"
    });
    Then({
        "D4 is 0xFEEF7FFF",
        "SR is S,0,V"
    });
}

TEST_F(SUBQTestWord, DataDirectFlagCWorks) {
    Given({
        "D4 is 0xFEEF0000",
        "SR is S,0,0"
    });
    When({
        "SUBQ.W #0x02, D4"
    });
    Then({
        "D4 is 0xFEEFFFFE",
        "SR is S,0,XNC"
    });
}

TEST_F(SUBQTestWord, AddressDirectWorks) {
    Given({
        "A4 is 0x01000004",
        "SR is S,0,0"
    });
    When({
        "SUBQ.W #0x0006, A4"
    });
    Then({
        "A4 is 0x00FFFFFE",
        "SR is S,0,0"
    });
}

TEST_F(SUBQTestWord, AddressIndirectWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).W is 0x0004",
        "SR is S,0,0"
    });
    When({
        "SUBQ.W #0x0006, (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).W is 0xFFFE",
        "SR is S,0,XNC"
    });
}

TEST_F(SUBQTestWord, AddressIncrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).W is 0x0004",
        "SR is S,0,0"
    });
    When({
        "SUBQ.W #0x0006, (A4)+"
    });
    Then({
        "A4 is 0x00006002",
        "(0x00006000).W is 0xFFFE",
        "SR is S,0,XNC"
    });
}

TEST_F(SUBQTestWord, AddressDecrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFE).W is 0x0004",
        "SR is S,0,0"
    });
    When({
        "SUBQ.W #0x0006, -(A4)"
    });
    Then({
        "A4 is 0x00005FFE",
        "(0x00005FFE).W is 0xFFFE",
        "SR is S,0,XNC"
    });
}

TEST_F(SUBQTestWord, AddressDisplacementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x0004",
        "SR is S,0,0"
    });
    When({
        "SUBQ.W #0x0006, (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).W is 0xFFFE",
        "SR is S,0,XNC"
    });
}

TEST_F(SUBQTestWord, AddressIndexWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x0004",
        "SR is S,0,0"
    });
    When({
        "SUBQ.W #0x0006, (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0xFFFE",
        "SR is S,0,XNC"
    });
}

TEST_F(SUBQTestWord, ShortWorks) {
    Given({
        "(0x00006000).W is 0x0004",
        "SR is S,0,0"
    });
    When({
        "SUBQ.W #0x0006, (0x6000).W"
    });
    Then({
        "(0x00006000).W is 0xFFFE",
        "SR is S,0,XNC"
    });
}

TEST_F(SUBQTestWord, LongWorks) {
    Given({
        "(0x00006000).W is 0x0004",
        "SR is S,0,0"
    });
    When({
        "SUBQ.W #0x0006, (0x00006000).L"
    });
    Then({
        "(0x00006000).W is 0xFFFE",
        "SR is S,0,XNC"
    });
}

#include "M68000/Fixtures/M68000Test.h"

class SUBQTestWord : public M68000Test {};

TEST_F(SUBQTestWord, DataDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x01000004",
    });
    When({
        "SUBQ.W #0x0006, D4"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 4",
        "D4 is 0x0100FFFE",
    });
}

TEST_F(SUBQTestWord, DataDirectSub8Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x700F0F07",
    });
    When({
        "SUBQ.W #0x08, D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D4 is 0x700F0EFF",
    });
}

TEST_F(SUBQTestWord, DataDirectFlagNWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xFEEFF00E",
    });
    When({
        "SUBQ.W #0x01, D4"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 4",
        "D4 is 0xFEEFF00D",
    });
}

TEST_F(SUBQTestWord, DataDirectFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xFEEF0001",
    });
    When({
        "SUBQ.W #0x01, D4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 4",
        "D4 is 0xFEEF0000",
    });
}

TEST_F(SUBQTestWord, DataDirectFlagVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xFEEF8000",
    });
    When({
        "SUBQ.W #0x01, D4"
    });
    Then({
        "SR is S,0,V",
        "PC is 0x1002",
        "CYCLES is 4",
        "D4 is 0xFEEF7FFF",
    });
}

TEST_F(SUBQTestWord, DataDirectFlagCWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xFEEF0000",
    });
    When({
        "SUBQ.W #0x02, D4"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 4",
        "D4 is 0xFEEFFFFE",
    });
}

TEST_F(SUBQTestWord, AddressDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x01000004",
    });
    When({
        "SUBQ.W #0x0006, A4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "A4 is 0x00FFFFFE",
    });
}

TEST_F(SUBQTestWord, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).W is 0x0004",
    });
    When({
        "SUBQ.W #0x0006, (A4)"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 12",
        "A4 is 0x00006000",
        "(0x00006000).W is 0xFFFE",
    });
}

TEST_F(SUBQTestWord, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).W is 0x0004",
    });
    When({
        "SUBQ.W #0x0006, (A4)+"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 12",
        "A4 is 0x00006002",
        "(0x00006000).W is 0xFFFE",
    });
}

TEST_F(SUBQTestWord, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005FFE).W is 0x0004",
    });
    When({
        "SUBQ.W #0x0006, -(A4)"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 14",
        "A4 is 0x00005FFE",
        "(0x00005FFE).W is 0xFFFE",
    });
}

TEST_F(SUBQTestWord, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x0004",
    });
    When({
        "SUBQ.W #0x0006, (0x004C, A4)"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1004",
        "CYCLES is 16",
        "A4 is 0x00006000",
        "(0x0000604C).W is 0xFFFE",
    });
}

TEST_F(SUBQTestWord, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x0004",
    });
    When({
        "SUBQ.W #0x0006, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1004",
        "CYCLES is 18",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0xFFFE",
    });
}

TEST_F(SUBQTestWord, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).W is 0x0004",
    });
    When({
        "SUBQ.W #0x0006, (0x6000).W"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1004",
        "CYCLES is 16",
        "(0x00006000).W is 0xFFFE",
    });
}

TEST_F(SUBQTestWord, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).W is 0x0004",
    });
    When({
        "SUBQ.W #0x0006, (0x00006000).L"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1006",
        "CYCLES is 20",
        "(0x00006000).W is 0xFFFE",
    });
}

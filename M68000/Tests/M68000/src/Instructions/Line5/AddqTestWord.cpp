#include "M68000/Fixtures/M68000Test.h"

class ADDQTestWord : public M68000Test {};

TEST_F(ADDQTestWord, DataDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xFEEFFFFE",
    });
    When({
        "ADDQ.W #0x0003, D4"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 4",
        "D4 is 0xFEEF0001",
    });
}

TEST_F(ADDQTestWord, DataDirectAdd8Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xFEEF40F9",
    });
    When({
        "ADDQ.W #0x08, D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D4 is 0xFEEF4101",
    });
}

TEST_F(ADDQTestWord, DataDirectFlagNWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xFEEFF00E",
    });
    When({
        "ADDQ.W #0x01, D4"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 4",
        "D4 is 0xFEEFF00F",
    });
}

TEST_F(ADDQTestWord, DataDirectFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xFEEFFFFF",
    });
    When({
        "ADDQ.W #0x01, D4"
    });
    Then({
        "SR is S,0,XZC",
        "PC is 0x1002",
        "CYCLES is 4",
        "D4 is 0xFEEF0000",
    });
}

TEST_F(ADDQTestWord, DataDirectFlagVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xFEEF7FFF",
    });
    When({
        "ADDQ.W #0x01, D4"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1002",
        "CYCLES is 4",
        "D4 is 0xFEEF8000",
    });
}

TEST_F(ADDQTestWord, DataDirectFlagCWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xFEEFFFFF",
    });
    When({
        "ADDQ.W #0x02, D4"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 4",
        "D4 is 0xFEEF0001",
    });
}

TEST_F(ADDQTestWord, AddressDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0xFEEFFFFE",
    });
    When({
        "ADDQ.W #0x0003, A4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "A4 is 0xFEF00001",
    });
}

TEST_F(ADDQTestWord, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).W is 0xFFFE",
    });
    When({
        "ADDQ.W #0x0003, (A4)"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 12",
        "A4 is 0x00006000",
        "(0x00006000).W is 0x0001",
    });
}

TEST_F(ADDQTestWord, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).W is 0xFFFE",
    });
    When({
        "ADDQ.W #0x0003, (A4)+"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 12",
        "A4 is 0x00006002",
        "(0x00006000).W is 0x0001",
    });
}

TEST_F(ADDQTestWord, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005FFE).W is 0xFFFE",
    });
    When({
        "ADDQ.W #0x0003, -(A4)"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 14",
        "A4 is 0x00005FFE",
        "(0x00005FFE).W is 0x0001",
    });
}

TEST_F(ADDQTestWord, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x0000604C).W is 0xFFFE",
    });
    When({
        "ADDQ.W #0x0003, (0x004C, A4)"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1004",
        "CYCLES is 16",
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x0001",
    });
}

TEST_F(ADDQTestWord, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0xFFFE",
    });
    When({
        "ADDQ.W #0x0003, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1004",
        "CYCLES is 18",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x0001",
    });
}

TEST_F(ADDQTestWord, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).W is 0xFFFE",
    });
    When({
        "ADDQ.W #0x0003, (0x6000).W"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1004",
        "CYCLES is 16",
        "(0x00006000).W is 0x0001",
    });
}

TEST_F(ADDQTestWord, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).W is 0xFFFE",
    });
    When({
        "ADDQ.W #0x0003, (0x00006000).L"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1006",
        "CYCLES is 20",
        "(0x00006000).W is 0x0001",
    });
}

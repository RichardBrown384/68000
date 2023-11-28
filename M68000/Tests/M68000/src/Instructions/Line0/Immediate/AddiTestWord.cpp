#include "M68000/Fixtures/M68000Test.h"

class ADDITestWord : public M68000Test {};

TEST_F(ADDITestWord, DataDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x768B3415",
    });
    When({
        "ADDI.W #0x1244, D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 8",
        "D4 is 0x768B4659",
    });
}

TEST_F(ADDITestWord, DataDirectFlagXWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x768BFFFF",
    });
    When({
        "ADDI.W #0x0002, D4"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1004",
        "CYCLES is 8",
        "D4 is 0x768B0001",
    });
}

TEST_F(ADDITestWord, DataDirectFlagNWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x768B9415",
    });
    When({
        "ADDI.W #0x1244, D4"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 8",
        "D4 is 0x768BA659",
    });
}

TEST_F(ADDITestWord, DataDirectFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x768B0000",
    });
    When({
        "ADDI.W #0x0000, D4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 8",
        "D4 is 0x768B0000",
    });
}

TEST_F(ADDITestWord, DataDirectFlagsVCWorks) {
    Given({
        "SR is S,0,VC",
        "PC is 0x1000",
        "D4 is 0x768B3415",
    });
    When({
        "ADDI.W #0x1244, D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 8",
        "D4 is 0x768B4659",
    });
}

TEST_F(ADDITestWord, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).W is 0x3415",
    });
    When({
        "ADDI.W #0x1244, (A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "A4 is 0x00006000",
        "(0x00006000).W is 0x4659",
    });
}

TEST_F(ADDITestWord, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).W is 0x3415",
    });
    When({
        "ADDI.W #0x1244, (A4)+"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "A4 is 0x00006002",
        "(0x00006000).W is 0x4659",
    });
}

TEST_F(ADDITestWord, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005FFE).W is 0x3415",
    });
    When({
        "ADDI.W #0x1244, -(A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "A4 is 0x00005FFE",
        "(0x00005FFE).W is 0x4659",
    });
}

TEST_F(ADDITestWord, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x3415",
    });
    When({
        "ADDI.W #0x1244, (0x004C, A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 20",
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x4659",
    });
}

TEST_F(ADDITestWord, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x3415",
    });
    When({
        "ADDI.W #0x1244, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 22",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x4659",
    });
}

TEST_F(ADDITestWord, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).W is 0x3415",
    });
    When({
        "ADDI.W #0x1244, (0x6000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 20",
        "(0x00006000).W is 0x4659",
    });
}

TEST_F(ADDITestWord, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).W is 0x3415",
    });
    When({
        "ADDI.W #0x1244, (0x00006000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1008",
        "CYCLES is 24",
        "(0x00006000).W is 0x4659",
    });
}

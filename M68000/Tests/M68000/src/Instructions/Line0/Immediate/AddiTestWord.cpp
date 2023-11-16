#include "M68000/Fixtures/M68000Test.h"

class ADDITestWord : public M68000Test {};

TEST_F(ADDITestWord, DataDirectWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "ADDI.W #0x1244, D4"
    });
    Then({
        "D4 is 0x768B4659",
        "SR is S,0,0"
    });
}

TEST_F(ADDITestWord, DataDirectFlagXWorks) {
    Given({
        "D4 is 0x768BFFFF",
        "SR is S,0,0"
    });
    When({
        "ADDI.W #0x0002, D4"
    });
    Then({
        "D4 is 0x768B0001",
        "SR is S,0,XC"
    });
}

TEST_F(ADDITestWord, DataDirectFlagNWorks) {
    Given({
        "D4 is 0x768B9415",
        "SR is S,0,0"
    });
    When({
        "ADDI.W #0x1244, D4"
    });
    Then({
        "D4 is 0x768BA659",
        "SR is S,0,N"
    });
}

TEST_F(ADDITestWord, DataDirectFlagZWorks) {
    Given({
        "D4 is 0x768B0000",
        "SR is S,0,0"
    });
    When({
        "ADDI.W #0x0000, D4"
    });
    Then({
        "D4 is 0x768B0000",
        "SR is S,0,Z"
    });
}

TEST_F(ADDITestWord, DataDirectFlagsVCWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,VC"
    });
    When({
        "ADDI.W #0x1244, D4"
    });
    Then({
        "D4 is 0x768B4659",
        "SR is S,0,0"
    });
}

TEST_F(ADDITestWord, AddressIndirectWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "ADDI.W #0x1244, (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).W is 0x4659",
        "SR is S,0,0"
    });
}

TEST_F(ADDITestWord, AddressIncrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "ADDI.W #0x1244, (A4)+"
    });
    Then({
        "A4 is 0x00006002",
        "(0x00006000).W is 0x4659",
        "SR is S,0,0"
    });
}

TEST_F(ADDITestWord, AddressDecrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFE).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "ADDI.W #0x1244, -(A4)"
    });
    Then({
        "A4 is 0x00005FFE",
        "(0x00005FFE).W is 0x4659",
        "SR is S,0,0"
    });
}

TEST_F(ADDITestWord, AddressDisplacementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "ADDI.W #0x1244, (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x4659",
        "SR is S,0,0"
    });
}

TEST_F(ADDITestWord, AddressIndexWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "ADDI.W #0x1244, (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x4659",
        "SR is S,0,0"
    });
}

TEST_F(ADDITestWord, ShortWorks) {
    Given({
        "(0x00006000).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "ADDI.W #0x1244, (0x6000).W"
    });
    Then({
        "(0x00006000).W is 0x4659",
        "SR is S,0,0"
    });
}

TEST_F(ADDITestWord, LongWorks) {
    Given({
        "(0x00006000).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "ADDI.W #0x1244, (0x00006000).L"
    });
    Then({
        "(0x00006000).W is 0x4659",
        "SR is S,0,0"
    });
}

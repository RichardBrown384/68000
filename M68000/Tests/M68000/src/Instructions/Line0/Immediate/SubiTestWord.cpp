#include "M68000/Fixtures/M68000Test.h"

class SUBITestWord : public M68000Test {};

TEST_F(SUBITestWord, DataDirectWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "SUBI.W #0x1244, D4"
    });
    Then({
        "D4 is 0x768B21D1",
        "SR is S,0,0"
    });
}

TEST_F(SUBITestWord, DataDirectFlagXWorks) {
    Given({
        "D4 is 0x768B8000",
        "SR is S,0,0"
    });
    When({
        "SUBI.W #0x8001, D4"
    });
    Then({
        "D4 is 0x768BFFFF",
        "SR is S,0,XNC"
    });
}

TEST_F(SUBITestWord, DataDirectFlagNWorks) {
    Given({
        "D4 is 0x768BFFFF",
        "SR is S,0,0"
    });
    When({
        "SUBI.W #0x0001, D4"
    });
    Then({
        "D4 is 0x768BFFFE",
        "SR is S,0,N"
    });
}

TEST_F(SUBITestWord, DataDirectFlagZWorks) {
    Given({
        "D4 is 0x768B0000",
        "SR is S,0,0"
    });
    When({
        "SUBI.W #0x0000, D4"
    });
    Then({
        "D4 is 0x768B0000",
        "SR is S,0,Z"
    });
}

TEST_F(SUBITestWord, DataDirectFlagsVCWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,VC"
    });
    When({
        "SUBI.W #0x1244, D4"
    });
    Then({
        "D4 is 0x768B21D1",
        "SR is S,0,0"
    });
}

TEST_F(SUBITestWord, AddressIndirectWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "SUBI.W #0x1244, (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).W is 0x21D1",
        "SR is S,0,0"
    });
}

TEST_F(SUBITestWord, AddressIncrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "SUBI.W #0x1244, (A4)+"
    });
    Then({
        "A4 is 0x00006002",
        "(0x00006000).W is 0x21D1",
        "SR is S,0,0"
    });
}

TEST_F(SUBITestWord, AddressDecrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFE).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "SUBI.W #0x1244, -(A4)"
    });
    Then({
        "A4 is 0x00005FFE",
        "(0x00005FFE).W is 0x21D1",
        "SR is S,0,0"
    });
}

TEST_F(SUBITestWord, AddressDisplacementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "SUBI.W #0x1244, (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x21D1",
        "SR is S,0,0"
    });
}

TEST_F(SUBITestWord, AddressIndexWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "SUBI.W #0x1244, (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x21D1",
        "SR is S,0,0"
    });
}

TEST_F(SUBITestWord, ShortWorks) {
    Given({
        "(0x00006000).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "SUBI.W #0x1244, (0x6000).W"
    });
    Then({
        "(0x00006000).W is 0x21D1",
        "SR is S,0,0"
    });
}

TEST_F(SUBITestWord, LongWorks) {
    Given({
        "(0x00006000).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "SUBI.W #0x1244, (0x00006000).L"
    });
    Then({
        "(0x00006000).W is 0x21D1",
        "SR is S,0,0"
    });
}

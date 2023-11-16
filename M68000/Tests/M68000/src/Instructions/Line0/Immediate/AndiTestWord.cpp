#include "M68000/Fixtures/M68000Test.h"

class ANDITestWord : public M68000Test {};

TEST_F(ANDITestWord, DataDirectWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "ANDI.W #0x1244, D4"
    });
    Then({
        "D4 is 0x768B1004",
        "SR is S,0,0"
    });
}

TEST_F(ANDITestWord, DataDirectFlagXWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,X"
    });
    When({
        "ANDI.W #0x1244, D4"
    });
    Then({
        "D4 is 0x768B1004",
        "SR is S,0,X"
    });
}

TEST_F(ANDITestWord, DataDirectFlagNWorks) {
    Given({
        "D4 is 0x768B8415",
        "SR is S,0,0"
    });
    When({
        "ANDI.W #0x8244, D4"
    });
    Then({
        "D4 is 0x768B8004",
        "SR is S,0,N"
    });
}

TEST_F(ANDITestWord, DataDirectFlagZWorks) {
    Given({
        "D4 is 0x768BF00F",
        "SR is S,0,0"
    });
    When({
        "ANDI.W #0x0FF0, D4"
    });
    Then({
        "D4 is 0x768B0000",
        "SR is S,0,Z"
    });
}

TEST_F(ANDITestWord, DataDirectFlagsVCWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,VC"
    });
    When({
        "ANDI.W #0x1244, D4"
    });
    Then({
        "D4 is 0x768B1004",
        "SR is S,0,0"
    });
}

TEST_F(ANDITestWord, AddressIndirectWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "ANDI.W #0x1244, (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).W is 0x1004",
        "SR is S,0,0"
    });
}

TEST_F(ANDITestWord, AddressIncrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "ANDI.W #0x1244, (A4)+"
    });
    Then({
        "A4 is 0x00006002",
        "(0x00006000).W is 0x1004",
        "SR is S,0,0"
    });
}

TEST_F(ANDITestWord, AddressDecrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFE).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "ANDI.W #0x1244, -(A4)"
    });
    Then({
        "A4 is 0x00005FFE",
        "(0x00005FFE).W is 0x1004",
        "SR is S,0,0"
    });
}

TEST_F(ANDITestWord, AddressDisplacementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "ANDI.W #0x1244, (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x1004",
        "SR is S,0,0"
    });
}

TEST_F(ANDITestWord, AddressIndexWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "ANDI.W #0x1244, (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x1004",
        "SR is S,0,0"
    });
}

TEST_F(ANDITestWord, ShortWorks) {
    Given({
        "(0x00006000).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "ANDI.W #0x1244, (0x6000).W"
    });
    Then({
        "(0x00006000).W is 0x1004",
        "SR is S,0,0"
    });
}

TEST_F(ANDITestWord, LongWorks) {
    Given({
        "(0x00006000).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "ANDI.W #0x1244, (0x00006000).L"
    });
    Then({
        "(0x00006000).W is 0x1004",
        "SR is S,0,0"
    });
}

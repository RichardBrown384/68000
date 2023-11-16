#include "M68000/Fixtures/M68000Test.h"

class ORITestWord : public M68000Test {};

TEST_F(ORITestWord, DataDirectWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "ORI.W #0x1244, D4"
    });
    Then({
        "D4 is 0x768B3655",
        "SR is S,0,0"
    });
}

TEST_F(ORITestWord, DataDirectFlagXWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,X"
    });
    When({
        "ORI.W #0x1244, D4"
    });
    Then({
        "D4 is 0x768B3655",
        "SR is S,0,X"
    });
}

TEST_F(ORITestWord, DataDirectFlagNWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "ORI.W #0xC244, D4"
    });
    Then({
        "D4 is 0x768BF655",
        "SR is S,0,N"
    });
}

TEST_F(ORITestWord, DataDirectFlagZWorks) {
    Given({
        "D4 is 0x768B0000",
        "SR is S,0,0"
    });
    When({
        "ORI.W #0x0000, D4"
    });
    Then({
        "D4 is 0x768B0000",
        "SR is S,0,Z"
    });
}

TEST_F(ORITestWord, DataDirectFlagsVCWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,VC"
    });
    When({
        "ORI.W #0x1244, D4"
    });
    Then({
        "D4 is 0x768B3655",
        "SR is S,0,0"
    });
}

TEST_F(ORITestWord, AddressIndirectWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "ORI.W #0x1244, (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).W is 0x3655",
        "SR is S,0,0"
    });
}

TEST_F(ORITestWord, AddressIncrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "ORI.W #0x1244, (A4)+"
    });
    Then({
        "A4 is 0x00006002",
        "(0x00006000).W is 0x3655",
        "SR is S,0,0"
    });
}

TEST_F(ORITestWord, AddressDecrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFE).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "ORI.W #0x1244, -(A4)"
    });
    Then({
        "A4 is 0x00005FFE",
        "(0x00005FFE).W is 0x3655",
        "SR is S,0,0"
    });
}

TEST_F(ORITestWord, AddressDisplacementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "ORI.W #0x1244, (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x3655",
        "SR is S,0,0"
    });
}

TEST_F(ORITestWord, AddressIndexWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "ORI.W #0x1244, (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x3655",
        "SR is S,0,0"
    });
}

TEST_F(ORITestWord, ShortWorks) {
    Given({
        "(0x00006000).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "ORI.W #0x1244, (0x6000).W"
    });
    Then({
        "(0x00006000).W is 0x3655",
        "SR is S,0,0"
    });
}

TEST_F(ORITestWord, LongWorks) {
    Given({
        "(0x00006000).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "ORI.W #0x1244, (0x00006000).L"
    });
    Then({
        "(0x00006000).W is 0x3655",
        "SR is S,0,0"
    });
}

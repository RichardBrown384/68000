#include "M68000/Fixtures/M68000Test.h"

class EORITestWord : public M68000Test {};

TEST_F(EORITestWord, DataDirectWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "EORI.W #0x1244, D4"
    });
    Then({
        "D4 is 0x768B2651",
        "SR is S,0,0"
    });
}

TEST_F(EORITestWord, DataDirectFlagXWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,X"
    });
    When({
        "EORI.W #0x1244, D4"
    });
    Then({
        "D4 is 0x768B2651",
        "SR is S,0,X"
    });
}

TEST_F(EORITestWord, DataDirectFlagNWorks) {
    Given({
        "D4 is 0x768B8415",
        "SR is S,0,0"
    });
    When({
        "EORI.W #0x1244, D4"
    });
    Then({
        "D4 is 0x768B9651",
        "SR is S,0,N"
    });
}

TEST_F(EORITestWord, DataDirectFlagZWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "EORI.W #0x3415, D4"
    });
    Then({
        "D4 is 0x768B0000",
        "SR is S,0,Z"
    });
}

TEST_F(EORITestWord, DataDirectFlagsVCWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,VC"
    });
    When({
        "EORI.W #0x1244, D4"
    });
    Then({
        "D4 is 0x768B2651",
        "SR is S,0,0"
    });
}

TEST_F(EORITestWord, AddressIndirectWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "EORI.W #0x1244, (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).W is 0x2651",
        "SR is S,0,0"
    });
}

TEST_F(EORITestWord, AddressIncrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "EORI.W #0x1244, (A4)+"
    });
    Then({
        "A4 is 0x00006002",
        "(0x00006000).W is 0x2651",
        "SR is S,0,0"
    });
}

TEST_F(EORITestWord, AddressDecrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFE).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "EORI.W #0x1244, -(A4)"
    });
    Then({
        "A4 is 0x00005FFE",
        "(0x00005FFE).W is 0x2651",
        "SR is S,0,0"
    });
}

TEST_F(EORITestWord, AddressDisplacementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "EORI.W #0x1244, (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x2651",
        "SR is S,0,0"
    });
}

TEST_F(EORITestWord, AddressIndexWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "EORI.W #0x1244, (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x2651",
        "SR is S,0,0"
    });
}

TEST_F(EORITestWord, ShortWorks) {
    Given({
        "(0x00006000).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "EORI.W #0x1244, (0x6000).W"
    });
    Then({
        "(0x00006000).W is 0x2651",
        "SR is S,0,0"
    });
}

TEST_F(EORITestWord, LongWorks) {
    Given({
        "(0x00006000).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "EORI.W #0x1244, (0x00006000).L"
    });
    Then({
        "(0x00006000).W is 0x2651",
        "SR is S,0,0"
    });
}

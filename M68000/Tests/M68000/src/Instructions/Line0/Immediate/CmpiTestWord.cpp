#include "M68000/Fixtures/M68000Test.h"

class CMPITestWord : public M68000Test {};

TEST_F(CMPITestWord, DataDirectWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "CMPI.W #0x4212, D4"
    });
    Then({
        "D4 is 0x768B3415",
        "SR is S,0,NC"
    });
}

TEST_F(CMPITestWord, DataDirectFlagXWorks) {
    Given({
        "D4 is 0x768B8000",
        "SR is S,0,X"
    });
    When({
        "CMPI.W #0x8001, D4"
    });
    Then({
        "D4 is 0x768B8000",
        "SR is S,0,XNC"
    });
}

TEST_F(CMPITestWord, DataDirectFlagNWorks) {
    Given({
        "D4 is 0x768BFFFF",
        "SR is S,0,0"
    });
    When({
        "CMPI.W #0x0001, D4"
    });
    Then({
        "D4 is 0x768BFFFF",
        "SR is S,0,N"
    });
}

TEST_F(CMPITestWord, DataDirectFlagZWorks) {
    Given({
        "D4 is 0x768B0000",
        "SR is S,0,0"
    });
    When({
        "CMPI.W #0x0000, D4"
    });
    Then({
        "D4 is 0x768B0000",
        "SR is S,0,Z"
    });
}

TEST_F(CMPITestWord, DataDirectFlagsVCWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,VC"
    });
    When({
        "CMPI.W #0x4244, D4"
    });
    Then({
        "D4 is 0x768B3415",
        "SR is S,0,NC"
    });
}

TEST_F(CMPITestWord, AddressIndirectWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "CMPI.W #0x4212, (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).W is 0x3415",
        "SR is S,0,NC"
    });
}

TEST_F(CMPITestWord, AddressIncrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "CMPI.W #0x4212, (A4)+"
    });
    Then({
        "A4 is 0x00006002",
        "(0x00006000).W is 0x3415",
        "SR is S,0,NC"
    });
}

TEST_F(CMPITestWord, AddressDecrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFE).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "CMPI.W #0x4212, -(A4)"
    });
    Then({
        "A4 is 0x00005FFE",
        "(0x00005FFE).W is 0x3415",
        "SR is S,0,NC"
    });
}

TEST_F(CMPITestWord, AddressDisplacementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "CMPI.W #0x4212, (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x3415",
        "SR is S,0,NC"
    });
}

TEST_F(CMPITestWord, AddressIndexWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "CMPI.W #0x4212, (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x3415",
        "SR is S,0,NC"
    });
}

TEST_F(CMPITestWord, ShortWorks) {
    Given({
        "(0x00006000).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "CMPI.W #0x4212, (0x6000).W"
    });
    Then({
        "(0x00006000).W is 0x3415",
        "SR is S,0,NC"
    });
}

TEST_F(CMPITestWord, LongWorks) {
    Given({
        "(0x00006000).W is 0x3415",
        "SR is S,0,0"
    });
    When({
        "CMPI.W #0x4212, (0x00006000).L"
    });
    Then({
        "(0x00006000).W is 0x3415",
        "SR is S,0,NC"
    });
}

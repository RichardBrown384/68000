#include "M68000/Fixtures/M68000Test.h"

class CMPITestWord : public M68000Test {};

TEST_F(CMPITestWord, DataDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x768B3415",
    });
    When({
        "CMPI.W #0x4212, D4"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1004",
        "CYCLES is 8",
        "D4 is 0x768B3415",
    });
}

TEST_F(CMPITestWord, DataDirectFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D4 is 0x768B8000",
    });
    When({
        "CMPI.W #0x8001, D4"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1004",
        "CYCLES is 8",
        "D4 is 0x768B8000",
    });
}

TEST_F(CMPITestWord, DataDirectFlagNWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x768BFFFF",
    });
    When({
        "CMPI.W #0x0001, D4"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 8",
        "D4 is 0x768BFFFF",
    });
}

TEST_F(CMPITestWord, DataDirectFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x768B0000",
    });
    When({
        "CMPI.W #0x0000, D4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 8",
        "D4 is 0x768B0000",
    });
}

TEST_F(CMPITestWord, DataDirectFlagsVCWorks) {
    Given({
        "SR is S,0,VC",
        "PC is 0x1000",
        "D4 is 0x768B3415",
    });
    When({
        "CMPI.W #0x4244, D4"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1004",
        "CYCLES is 8",
        "D4 is 0x768B3415",
    });
}

TEST_F(CMPITestWord, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).W is 0x3415",
    });
    When({
        "CMPI.W #0x4212, (A4)"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1004",
        "CYCLES is 12",
        "A4 is 0x00006000",
        "(0x00006000).W is 0x3415",
    });
}

TEST_F(CMPITestWord, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).W is 0x3415",
    });
    When({
        "CMPI.W #0x4212, (A4)+"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1004",
        "CYCLES is 12",
        "A4 is 0x00006002",
        "(0x00006000).W is 0x3415",
    });
}

TEST_F(CMPITestWord, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005FFE).W is 0x3415",
    });
    When({
        "CMPI.W #0x4212, -(A4)"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1004",
        "CYCLES is 14",
        "A4 is 0x00005FFE",
        "(0x00005FFE).W is 0x3415",
    });
}

TEST_F(CMPITestWord, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x3415",
    });
    When({
        "CMPI.W #0x4212, (0x004C, A4)"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1006",
        "CYCLES is 16",
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x3415",
    });
}

TEST_F(CMPITestWord, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x3415",
    });
    When({
        "CMPI.W #0x4212, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1006",
        "CYCLES is 18",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x3415",
    });
}

TEST_F(CMPITestWord, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).W is 0x3415",
    });
    When({
        "CMPI.W #0x4212, (0x6000).W"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1006",
        "CYCLES is 16",
        "(0x00006000).W is 0x3415",
    });
}

TEST_F(CMPITestWord, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).W is 0x3415",
    });
    When({
        "CMPI.W #0x4212, (0x00006000).L"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1008",
        "CYCLES is 20",
        "(0x00006000).W is 0x3415",
    });
}

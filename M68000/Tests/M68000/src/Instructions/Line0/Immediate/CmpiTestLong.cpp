#include "M68000/Fixtures/M68000Test.h"

class CMPITestLong : public M68000Test {};

TEST_F(CMPITestLong, DataDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x468B3415",
    });
    When({
        "CMPI.L #0x54761244, D4"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1006",
        "CYCLES is 14",
        "D4 is 0x468B3415",
    });
}

TEST_F(CMPITestLong, DataDirectFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D4 is 0x80000000",
    });
    When({
        "CMPI.L #0x80000001, D4"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1006",
        "CYCLES is 14",
        "D4 is 0x80000000",
    });
}

TEST_F(CMPITestLong, DataDirectFlagNWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xFFFFFFFF",
    });
    When({
        "CMPI.L #0x00000001, D4"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 14",
        "D4 is 0xFFFFFFFF",
    });
}

TEST_F(CMPITestLong, DataDirectFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x00000000",
    });
    When({
        "CMPI.L #0x00000000, D4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1006",
        "CYCLES is 14",
        "D4 is 0x00000000",
    });
}

TEST_F(CMPITestLong, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).L is 0x468B3415",
    });
    When({
        "CMPI.L #0x54761244, (A4)"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1006",
        "CYCLES is 20",
        "A4 is 0x00006000",
        "(0x00006000).L is 0x468B3415",
    });
}

TEST_F(CMPITestLong, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).L is 0x468B3415",
    });
    When({
        "CMPI.L #0x54761244, (A4)+"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1006",
        "CYCLES is 20",
        "A4 is 0x00006004",
        "(0x00006000).L is 0x468B3415",
    });
}

TEST_F(CMPITestLong, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005FFC).L is 0x468B3415",
    });
    When({
        "CMPI.L #0x54761244, -(A4)"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1006",
        "CYCLES is 22",
        "A4 is 0x00005FFC",
        "(0x00005FFC).L is 0x468B3415",
    });
}

TEST_F(CMPITestLong, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x468B3415",
    });
    When({
        "CMPI.L #0x54761244, (0x004C, A4)"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1008",
        "CYCLES is 24",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x468B3415",
    });
}

TEST_F(CMPITestLong, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0x468B3415",
    });
    When({
        "CMPI.L #0x54761244, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1008",
        "CYCLES is 26",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0x468B3415",
    });
}

TEST_F(CMPITestLong, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).L is 0x468B3415",
    });
    When({
        "CMPI.L #0x54761244, (0x6000).W"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1008",
        "CYCLES is 24",
        "(0x00006000).L is 0x468B3415",
    });
}

TEST_F(CMPITestLong, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).L is 0x468B3415",
    });
    When({
        "CMPI.L #0x54761244, (0x00006000).L"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x100A",
        "CYCLES is 28",
        "(0x00006000).L is 0x468B3415",
    });
}

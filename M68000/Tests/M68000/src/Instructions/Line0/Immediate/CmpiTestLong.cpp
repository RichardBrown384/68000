#include "M68000/Fixtures/M68000Test.h"

class CMPITestLong : public M68000Test {};

TEST_F(CMPITestLong, DataDirectWorks) {
    Given({
        "D4 is 0x468B3415",
        "SR is S,0,0"
    });
    When({
        "CMPI.L #0x54761244, D4"
    });
    Then({
        "D4 is 0x468B3415",
        "SR is S,0,NC"
    });
}

TEST_F(CMPITestLong, DataDirectFlagXWorks) {
    Given({
        "D4 is 0x80000000",
        "SR is S,0,X"
    });
    When({
        "CMPI.L #0x80000001, D4"
    });
    Then({
        "D4 is 0x80000000",
        "SR is S,0,XNC"
    });
}

TEST_F(CMPITestLong, DataDirectFlagNWorks) {
    Given({
        "D4 is 0xFFFFFFFF",
        "SR is S,0,0"
    });
    When({
        "CMPI.L #0x00000001, D4"
    });
    Then({
        "D4 is 0xFFFFFFFF",
        "SR is S,0,N"
    });
}

TEST_F(CMPITestLong, DataDirectFlagZWorks) {
    Given({
        "D4 is 0x00000000",
        "SR is S,0,0"
    });
    When({
        "CMPI.L #0x00000000, D4"
    });
    Then({
        "D4 is 0x00000000",
        "SR is S,0,Z"
    });
}

TEST_F(CMPITestLong, AddressIndirectWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).L is 0x468B3415",
        "SR is S,0,0"
    });
    When({
        "CMPI.L #0x54761244, (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).L is 0x468B3415",
        "SR is S,0,NC"
    });
}

TEST_F(CMPITestLong, AddressIncrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).L is 0x468B3415",
        "SR is S,0,0"
    });
    When({
        "CMPI.L #0x54761244, (A4)+"
    });
    Then({
        "A4 is 0x00006004",
        "(0x00006000).L is 0x468B3415",
        "SR is S,0,NC"
    });
}

TEST_F(CMPITestLong, AddressDecrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFC).L is 0x468B3415",
        "SR is S,0,0"
    });
    When({
        "CMPI.L #0x54761244, -(A4)"
    });
    Then({
        "A4 is 0x00005FFC",
        "(0x00005FFC).L is 0x468B3415",
        "SR is S,0,NC"
    });
}

TEST_F(CMPITestLong, AddressDisplacementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x468B3415",
        "SR is S,0,0"
    });
    When({
        "CMPI.L #0x54761244, (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x468B3415",
        "SR is S,0,NC"
    });
}

TEST_F(CMPITestLong, AddressIndexWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0x468B3415",
        "SR is S,0,0"
    });
    When({
        "CMPI.L #0x54761244, (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0x468B3415",
        "SR is S,0,NC"
    });
}

TEST_F(CMPITestLong, ShortWorks) {
    Given({
        "(0x00006000).L is 0x468B3415",
        "SR is S,0,0"
    });
    When({
        "CMPI.L #0x54761244, (0x6000).W"
    });
    Then({
        "(0x00006000).L is 0x468B3415",
        "SR is S,0,NC"
    });
}

TEST_F(CMPITestLong, LongWorks) {
    Given({
        "(0x00006000).L is 0x468B3415",
        "SR is S,0,0"
    });
    When({
        "CMPI.L #0x54761244, (0x00006000).L"
    });
    Then({
        "(0x00006000).L is 0x468B3415",
        "SR is S,0,NC"
    });
}

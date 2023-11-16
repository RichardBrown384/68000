#include "M68000/Fixtures/M68000Test.h"

class ANDITestLong : public M68000Test {};

TEST_F(ANDITestLong, DataDirectWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "ANDI.L #0x34761244, D4"
    });
    Then({
        "D4 is 0x34021004",
        "SR is S,0,0"
    });
}

TEST_F(ANDITestLong, DataDirectFlagXWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,X"
    });
    When({
        "ANDI.L #0x34761244, D4"
    });
    Then({
        "D4 is 0x34021004",
        "SR is S,0,X"
    });
}

TEST_F(ANDITestLong, DataDirectFlagNWorks) {
    Given({
        "D4 is 0x868B3415",
        "SR is S,0,0"
    });
    When({
        "ANDI.L #0xF4761244, D4"
    });
    Then({
        "D4 is 0x84021004",
        "SR is S,0,N"
    });
}

TEST_F(ANDITestLong, DataDirectFlagZWorks) {
    Given({
        "D4 is 0x0F0F0F0F",
        "SR is S,0,0"
    });
    When({
        "ANDI.L #0xF0F0F0F0, D4"
    });
    Then({
        "D4 is 0x00000000",
        "SR is S,0,Z"
    });
}

TEST_F(ANDITestLong, DataDirectFlagVCWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,VC"
    });
    When({
        "ANDI.L #0x34761244, D4"
    });
    Then({
        "D4 is 0x34021004",
        "SR is S,0,0"
    });
}

TEST_F(ANDITestLong, AddressIndirectWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).L is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "ANDI.L #0x34761244, (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).L is 0x34021004",
        "SR is S,0,0"
    });
}

TEST_F(ANDITestLong, AddressIncrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).L is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "ANDI.L #0x34761244, (A4)+"
    });
    Then({
        "A4 is 0x00006004",
        "(0x00006000).L is 0x34021004",
        "SR is S,0,0"
    });
}

TEST_F(ANDITestLong, AddressDecrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFC).L is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "ANDI.L #0x34761244, -(A4)"
    });
    Then({
        "A4 is 0x00005FFC",
        "(0x00005FFC).L is 0x34021004",
        "SR is S,0,0"
    });
}

TEST_F(ANDITestLong, AddressDisplacementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "ANDI.L #0x34761244, (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x34021004",
        "SR is S,0,0"
    });
}

TEST_F(ANDITestLong, AddressIndexWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "ANDI.L #0x34761244, (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0x34021004",
        "SR is S,0,0"
    });
}

TEST_F(ANDITestLong, ShortWorks) {
    Given({
        "(0x00006000).L is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "ANDI.L #0x34761244, (0x6000).W"
    });
    Then({
        "(0x00006000).L is 0x34021004",
        "SR is S,0,0"
    });
}

TEST_F(ANDITestLong, LongWorks) {
    Given({
        "(0x00006000).L is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "ANDI.L #0x34761244, (0x00006000).L"
    });
    Then({
        "(0x00006000).L is 0x34021004",
        "SR is S,0,0"
    });
}

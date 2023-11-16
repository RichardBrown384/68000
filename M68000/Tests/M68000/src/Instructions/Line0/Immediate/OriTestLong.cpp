#include "M68000/Fixtures/M68000Test.h"

class ORITestLong : public M68000Test {};

TEST_F(ORITestLong, DataDirectWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "ORI.L #0x34761244, D4"
    });
    Then({
        "D4 is 0x76FF3655",
        "SR is S,0,0"
    });
}

TEST_F(ORITestLong, DataDirectFlagXWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,X"
    });
    When({
        "ORI.L #0x34761244, D4"
    });
    Then({
        "D4 is 0x76FF3655",
        "SR is S,0,X"
    });
}

TEST_F(ORITestLong, DataDirectFlagNWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "ORI.L #0x84761244, D4"
    });
    Then({
        "D4 is 0xF6FF3655",
        "SR is S,0,N"
    });
}

TEST_F(ORITestLong, DataDirectFlagsVCWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,VC"
    });
    When({
        "ORI.L #0x34761244, D4"
    });
    Then({
        "D4 is 0x76FF3655",
        "SR is S,0,0"
    });
}

TEST_F(ORITestLong, DataDirectFlagZWorks) {
    Given({
        "D4 is 0x00000000",
        "SR is S,0,0"
    });
    When({
        "ORI.L #0x00000000, D4"
    });
    Then({
        "D4 is 0x00000000",
        "SR is S,0,Z"
    });
}

TEST_F(ORITestLong, AddressIndirectWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).L is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "ORI.L #0x34761244, (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).L is 0x76FF3655",
        "SR is S,0,0"
    });
}

TEST_F(ORITestLong, AddressIncrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).L is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "ORI.L #0x34761244, (A4)+"
    });
    Then({
        "A4 is 0x00006004",
        "(0x00006000).L is 0x76FF3655",
        "SR is S,0,0"
    });
}

TEST_F(ORITestLong, AddressDecrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFC).L is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "ORI.L #0x34761244, -(A4)"
    });
    Then({
        "A4 is 0x00005FFC",
        "(0x00005FFC).L is 0x76FF3655",
        "SR is S,0,0"
    });
}

TEST_F(ORITestLong, AddressDisplacementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "ORI.L #0x34761244, (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x76FF3655",
        "SR is S,0,0"
    });
}

TEST_F(ORITestLong, AddressIndexWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "ORI.L #0x34761244, (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0x76FF3655",
        "SR is S,0,0"
    });
}

TEST_F(ORITestLong, ShortWorks) {
    Given({
        "(0x00006000).L is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "ORI.L #0x34761244, (0x6000).W"
    });
    Then({
        "(0x00006000).L is 0x76FF3655",
        "SR is S,0,0"
    });
}

TEST_F(ORITestLong, LongWorks) {
    Given({
        "(0x00006000).L is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "ORI.L #0x34761244, (0x00006000).L"
    });
    Then({
        "(0x00006000).L is 0x76FF3655",
        "SR is S,0,0"
    });
}

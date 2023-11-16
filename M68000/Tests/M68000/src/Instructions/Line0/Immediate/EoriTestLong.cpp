#include "M68000/Fixtures/M68000Test.h"

class EORITestLong : public M68000Test {};

TEST_F(EORITestLong, DataDirectWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "EORI.L #0x34761244, D4"
    });
    Then({
        "D4 is 0x42FD2651",
        "SR is S,0,0"
    });
}

TEST_F(EORITestLong, DataDirectFlagXWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,X"
    });
    When({
        "EORI.L #0x34761244, D4"
    });
    Then({
        "D4 is 0x42FD2651",
        "SR is S,0,X"
    });
}

TEST_F(EORITestLong, DataDirectFlagNWorks) {
    Given({
        "D4 is 0x868B3415",
        "SR is S,0,0"
    });
    When({
        "EORI.L #0x34761244, D4"
    });
    Then({
        "D4 is 0xB2FD2651",
        "SR is S,0,N"
    });
}

TEST_F(EORITestLong, DataDirectFlagZWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "EORI.L #0x768B3415, D4"
    });
    Then({
        "D4 is 0x00000000",
        "SR is S,0,Z"
    });
}

TEST_F(EORITestLong, DataDirectFlagsVCWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,VC"
    });
    When({
        "EORI.L #0x34761244, D4"
    });
    Then({
        "D4 is 0x42FD2651",
        "SR is S,0,0"
    });
}

TEST_F(EORITestLong, AddressIndirectWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).L is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "EORI.L #0x34761244, (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).L is 0x42FD2651",
        "SR is S,0,0"
    });
}

TEST_F(EORITestLong, AddressIncrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).L is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "EORI.L #0x34761244, (A4)+"
    });
    Then({
        "A4 is 0x00006004",
        "(0x00006000).L is 0x42FD2651",
        "SR is S,0,0"
    });
}

TEST_F(EORITestLong, AddressDecrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFC).L is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "EORI.L #0x34761244, -(A4)"
    });
    Then({
        "A4 is 0x00005FFC",
        "(0x00005FFC).L is 0x42FD2651",
        "SR is S,0,0"
    });
}

TEST_F(EORITestLong, AddressDisplacementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "EORI.L #0x34761244, (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x42FD2651",
        "SR is S,0,0"
    });
}

TEST_F(EORITestLong, AddressIndexWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "EORI.L #0x34761244, (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0x42FD2651",
        "SR is S,0,0"
    });
}

TEST_F(EORITestLong, ShortWorks) {
    Given({
        "(0x00006000).L is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "EORI.L #0x34761244, (0x6000).W"
    });
    Then({
        "(0x00006000).L is 0x42FD2651",
        "SR is S,0,0"
    });
}

TEST_F(EORITestLong, LongWorks) {
    Given({
        "(0x00006000).L is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "EORI.L #0x34761244, (0x00006000).L"
    });
    Then({
        "(0x00006000).L is 0x42FD2651",
        "SR is S,0,0"
    });
}

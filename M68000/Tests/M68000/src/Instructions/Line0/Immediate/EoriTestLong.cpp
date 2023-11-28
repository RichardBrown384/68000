#include "M68000/Fixtures/M68000Test.h"

class EORITestLong : public M68000Test {};

TEST_F(EORITestLong, DataDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x768B3415",
    });
    When({
        "EORI.L #0x34761244, D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 16",
        "D4 is 0x42FD2651",
    });
}

TEST_F(EORITestLong, DataDirectFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D4 is 0x768B3415",
    });
    When({
        "EORI.L #0x34761244, D4"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1006",
        "CYCLES is 16",
        "D4 is 0x42FD2651",
    });
}

TEST_F(EORITestLong, DataDirectFlagNWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x868B3415",
    });
    When({
        "EORI.L #0x34761244, D4"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 16",
        "D4 is 0xB2FD2651",
    });
}

TEST_F(EORITestLong, DataDirectFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x768B3415",
    });
    When({
        "EORI.L #0x768B3415, D4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1006",
        "CYCLES is 16",
        "D4 is 0x00000000",
    });
}

TEST_F(EORITestLong, DataDirectFlagsVCWorks) {
    Given({
        "SR is S,0,VC",
        "PC is 0x1000",
        "D4 is 0x768B3415",
    });
    When({
        "EORI.L #0x34761244, D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 16",
        "D4 is 0x42FD2651",
    });
}

TEST_F(EORITestLong, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).L is 0x768B3415",
    });
    When({
        "EORI.L #0x34761244, (A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 28",
        "A4 is 0x00006000",
        "(0x00006000).L is 0x42FD2651",
    });
}

TEST_F(EORITestLong, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).L is 0x768B3415",
    });
    When({
        "EORI.L #0x34761244, (A4)+"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 28",
        "A4 is 0x00006004",
        "(0x00006000).L is 0x42FD2651",
    });
}

TEST_F(EORITestLong, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005FFC).L is 0x768B3415",
    });
    When({
        "EORI.L #0x34761244, -(A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 30",
        "A4 is 0x00005FFC",
        "(0x00005FFC).L is 0x42FD2651",
    });
}

TEST_F(EORITestLong, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x768B3415",
    });
    When({
        "EORI.L #0x34761244, (0x004C, A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1008",
        "CYCLES is 32",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x42FD2651",
    });
}

TEST_F(EORITestLong, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0x768B3415",
    });
    When({
        "EORI.L #0x34761244, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1008",
        "CYCLES is 34",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0x42FD2651",
    });
}

TEST_F(EORITestLong, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).L is 0x768B3415",
    });
    When({
        "EORI.L #0x34761244, (0x6000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1008",
        "CYCLES is 32",
        "(0x00006000).L is 0x42FD2651",
    });
}

TEST_F(EORITestLong, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).L is 0x768B3415",
    });
    When({
        "EORI.L #0x34761244, (0x00006000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x100A",
        "CYCLES is 36",
        "(0x00006000).L is 0x42FD2651",
    });
}

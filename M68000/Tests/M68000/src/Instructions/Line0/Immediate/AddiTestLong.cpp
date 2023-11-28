#include "M68000/Fixtures/M68000Test.h"

class ADDITestLong : public M68000Test {};

TEST_F(ADDITestLong, DataDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x468B3415",
    });
    When({
        "ADDI.L #0x14761244, D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 16",
        "D4 is 0x5B014659",
    });
}

TEST_F(ADDITestLong, DataDirectFlagXWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xFFFFFFFF",
    });
    When({
        "ADDI.L #0x00000002, D4"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1006",
        "CYCLES is 16",
        "D4 is 0x00000001",
    });
}

TEST_F(ADDITestLong, DataDirectFlagNWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x868B3415",
    });
    When({
        "ADDI.L #0x14761244, D4"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 16",
        "D4 is 0x9B014659",
    });
}

TEST_F(ADDITestLong, DataDirectFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x00000000",
    });
    When({
        "ADDI.L #0x00000000, D4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1006",
        "CYCLES is 16",
        "D4 is 0x00000000",
    });
}

TEST_F(ADDITestLong, DataDirectFlagVCWorks) {
    Given({
        "SR is S,0,VC",
        "PC is 0x1000",
        "D4 is 0x468B3415",
    });
    When({
        "ADDI.L #0x14761244, D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 16",
        "D4 is 0x5B014659",
    });
}

TEST_F(ADDITestLong, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).L is 0x468B3415",
    });
    When({
        "ADDI.L #0x14761244, (A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 28",
        "A4 is 0x00006000",
        "(0x00006000).L is 0x5B014659",
    });
}

TEST_F(ADDITestLong, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).L is 0x468B3415",
    });
    When({
        "ADDI.L #0x14761244, (A4)+"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 28",
        "A4 is 0x00006004",
        "(0x00006000).L is 0x5B014659",
    });
}

TEST_F(ADDITestLong, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005FFC).L is 0x468B3415",
    });
    When({
        "ADDI.L #0x14761244, -(A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 30",
        "A4 is 0x00005FFC",
        "(0x00005FFC).L is 0x5B014659",
    });
}

TEST_F(ADDITestLong, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x468B3415",
    });
    When({
        "ADDI.L #0x14761244, (0x004C, A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1008",
        "CYCLES is 32",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x5B014659",
    });
}

TEST_F(ADDITestLong, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0x468B3415",
    });
    When({
        "ADDI.L #0x14761244, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1008",
        "CYCLES is 34",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0x5B014659",
    });
}

TEST_F(ADDITestLong, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).L is 0x468B3415",
    });
    When({
        "ADDI.L #0x14761244, (0x6000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1008",
        "CYCLES is 32",
        "(0x00006000).L is 0x5B014659",
    });
}

TEST_F(ADDITestLong, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).L is 0x468B3415",
    });
    When({
        "ADDI.L #0x14761244, (0x00006000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x100A",
        "CYCLES is 36",
        "(0x00006000).L is 0x5B014659",
    });
}

#include "M68000/Fixtures/M68000Test.h"

class ADDITestLong : public M68000Test {};

TEST_F(ADDITestLong, DataDirectWorks) {
    Given({
        "D4 is 0x468B3415",
        "SR is S,0,0"
    });
    When({
        "ADDI.L #0x14761244, D4"
    });
    Then({
        "D4 is 0x5B014659",
        "SR is S,0,0"
    });
}

TEST_F(ADDITestLong, DataDirectFlagXWorks) {
    Given({
        "D4 is 0xFFFFFFFF",
        "SR is S,0,0"
    });
    When({
        "ADDI.L #0x00000002, D4"
    });
    Then({
        "D4 is 0x00000001",
        "SR is S,0,XC"
    });
}

TEST_F(ADDITestLong, DataDirectFlagNWorks) {
    Given({
        "D4 is 0x868B3415",
        "SR is S,0,0"
    });
    When({
        "ADDI.L #0x14761244, D4"
    });
    Then({
        "D4 is 0x9B014659",
        "SR is S,0,N"
    });
}

TEST_F(ADDITestLong, DataDirectFlagZWorks) {
    Given({
        "D4 is 0x00000000",
        "SR is S,0,0"
    });
    When({
        "ADDI.L #0x00000000, D4"
    });
    Then({
        "D4 is 0x00000000",
        "SR is S,0,Z"
    });
}

TEST_F(ADDITestLong, DataDirectFlagVCWorks) {
    Given({
        "D4 is 0x468B3415",
        "SR is S,0,VC"
    });
    When({
        "ADDI.L #0x14761244, D4"
    });
    Then({
        "D4 is 0x5B014659",
        "SR is S,0,0"
    });
}

TEST_F(ADDITestLong, AddressIndirectWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).L is 0x468B3415",
        "SR is S,0,0"
    });
    When({
        "ADDI.L #0x14761244, (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).L is 0x5B014659",
        "SR is S,0,0"
    });
}

TEST_F(ADDITestLong, AddressIncrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).L is 0x468B3415",
        "SR is S,0,0"
    });
    When({
        "ADDI.L #0x14761244, (A4)+"
    });
    Then({
        "A4 is 0x00006004",
        "(0x00006000).L is 0x5B014659",
        "SR is S,0,0"
    });
}

TEST_F(ADDITestLong, AddressDecrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFC).L is 0x468B3415",
        "SR is S,0,0"
    });
    When({
        "ADDI.L #0x14761244, -(A4)"
    });
    Then({
        "A4 is 0x00005FFC",
        "(0x00005FFC).L is 0x5B014659",
        "SR is S,0,0"
    });
}

TEST_F(ADDITestLong, AddressDisplacementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x468B3415",
        "SR is S,0,0"
    });
    When({
        "ADDI.L #0x14761244, (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x5B014659",
        "SR is S,0,0"
    });
}

TEST_F(ADDITestLong, AddressIndexWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0x468B3415",
        "SR is S,0,0"
    });
    When({
        "ADDI.L #0x14761244, (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0x5B014659",
        "SR is S,0,0"
    });
}

TEST_F(ADDITestLong, ShortWorks) {
    Given({
        "(0x00006000).L is 0x468B3415",
        "SR is S,0,0"
    });
    When({
        "ADDI.L #0x14761244, (0x6000).W"
    });
    Then({
        "(0x00006000).L is 0x5B014659",
        "SR is S,0,0"
    });
}

TEST_F(ADDITestLong, LongWorks) {
    Given({
        "(0x00006000).L is 0x468B3415",
        "SR is S,0,0"
    });
    When({
        "ADDI.L #0x14761244, (0x00006000).L"
    });
    Then({
        "(0x00006000).L is 0x5B014659",
        "SR is S,0,0"
    });
}

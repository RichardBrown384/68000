#include "M68000/Fixtures/M68000Test.h"

class SUBITestLong : public M68000Test {};

TEST_F(SUBITestLong, DataDirectWorks) {
    Given({
        "D4 is 0x468B3415",
        "SR is S,0,0"
    });
    When({
        "SUBI.L #0x14761244, D4"
    });
    Then({
        "D4 is 0x321521D1",
        "SR is S,0,0"
    });
}

TEST_F(SUBITestLong, DataDirectFlagXWorks) {
    Given({
        "D4 is 0x80000000",
        "SR is S,0,0"
    });
    When({
        "SUBI.L #0x80000001, D4"
    });
    Then({
        "D4 is 0xFFFFFFFF",
        "SR is S,0,XNC"
    });
}

TEST_F(SUBITestLong, DataDirectFlagNWorks) {
    Given({
        "D4 is 0xFFFFFFFF",
        "SR is S,0,0"
    });
    When({
        "SUBI.L #0x00000001, D4"
    });
    Then({
        "D4 is 0xFFFFFFFE",
        "SR is S,0,N"
    });
}

TEST_F(SUBITestLong, DataDirectFlagZWorks) {
    Given({
        "D4 is 0x00000000",
        "SR is S,0,0"
    });
    When({
        "SUBI.L #0x00000000, D4"
    });
    Then({
        "D4 is 0x00000000",
        "SR is S,0,Z"
    });
}

TEST_F(SUBITestLong, DataDirectFlagVCWorks) {
    Given({
        "D4 is 0x468B3415",
        "SR is S,0,VC"
    });
    When({
        "SUBI.L #0x14761244, D4"
    });
    Then({
        "D4 is 0x321521D1",
        "SR is S,0,0"
    });
}

TEST_F(SUBITestLong, AddressIndirectWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).L is 0x468B3415",
        "SR is S,0,0"
    });
    When({
        "SUBI.L #0x14761244, (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).L is 0x321521D1",
        "SR is S,0,0"
    });
}

TEST_F(SUBITestLong, AddressIncrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).L is 0x468B3415",
        "SR is S,0,0"
    });
    When({
        "SUBI.L #0x14761244, (A4)+"
    });
    Then({
        "A4 is 0x00006004",
        "(0x00006000).L is 0x321521D1",
        "SR is S,0,0"
    });
}

TEST_F(SUBITestLong, AddressDecrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFC).L is 0x468B3415",
        "SR is S,0,0"
    });
    When({
        "SUBI.L #0x14761244, -(A4)"
    });
    Then({
        "A4 is 0x00005FFC",
        "(0x00005FFC).L is 0x321521D1",
        "SR is S,0,0"
    });
}

TEST_F(SUBITestLong, AddressDisplacementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x468B3415",
        "SR is S,0,0"
    });
    When({
        "SUBI.L #0x14761244, (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x321521D1",
        "SR is S,0,0"
    });
}

TEST_F(SUBITestLong, AddressIndexWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0x468B3415",
        "SR is S,0,0"
    });
    When({
        "SUBI.L #0x14761244, (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0x321521D1",
        "SR is S,0,0"
    });
}

TEST_F(SUBITestLong, ShortWorks) {
    Given({
        "(0x00006000).L is 0x468B3415",
        "SR is S,0,0"
    });
    When({
        "SUBI.L #0x14761244, (0x6000).W"
    });
    Then({
        "(0x00006000).L is 0x321521D1",
        "SR is S,0,0"
    });
}

TEST_F(SUBITestLong, LongWorks) {
    Given({
        "(0x00006000).L is 0x468B3415",
        "SR is S,0,0"
    });
    When({
        "SUBI.L #0x14761244, (0x00006000).L"
    });
    Then({
        "(0x00006000).L is 0x321521D1",
        "SR is S,0,0"
    });
}

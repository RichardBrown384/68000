#include "M68000/Fixtures/M68000Test.h"

class SUBITestLong : public M68000Test {};

TEST_F(SUBITestLong, DataDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x468B3415",
    });
    When({
        "SUBI.L #0x14761244, D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 16",
        "D4 is 0x321521D1",
    });
}

TEST_F(SUBITestLong, DataDirectFlagXWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x80000000",
    });
    When({
        "SUBI.L #0x80000001, D4"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1006",
        "CYCLES is 16",
        "D4 is 0xFFFFFFFF",
    });
}

TEST_F(SUBITestLong, DataDirectFlagNWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xFFFFFFFF",
    });
    When({
        "SUBI.L #0x00000001, D4"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 16",
        "D4 is 0xFFFFFFFE",
    });
}

TEST_F(SUBITestLong, DataDirectFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x00000000",
    });
    When({
        "SUBI.L #0x00000000, D4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1006",
        "CYCLES is 16",
        "D4 is 0x00000000",
    });
}

TEST_F(SUBITestLong, DataDirectFlagVCWorks) {
    Given({
        "SR is S,0,VC",
        "PC is 0x1000",
        "D4 is 0x468B3415",
    });
    When({
        "SUBI.L #0x14761244, D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 16",
        "D4 is 0x321521D1",
    });
}

TEST_F(SUBITestLong, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).L is 0x468B3415",
    });
    When({
        "SUBI.L #0x14761244, (A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 28",
        "A4 is 0x00006000",
        "(0x00006000).L is 0x321521D1",
    });
}

TEST_F(SUBITestLong, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).L is 0x468B3415",
    });
    When({
        "SUBI.L #0x14761244, (A4)+"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 28",
        "A4 is 0x00006004",
        "(0x00006000).L is 0x321521D1",
    });
}

TEST_F(SUBITestLong, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005FFC).L is 0x468B3415",
    });
    When({
        "SUBI.L #0x14761244, -(A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 30",
        "A4 is 0x00005FFC",
        "(0x00005FFC).L is 0x321521D1",
    });
}

TEST_F(SUBITestLong, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x468B3415",
    });
    When({
        "SUBI.L #0x14761244, (0x004C, A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1008",
        "CYCLES is 32",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x321521D1",
    });
}

TEST_F(SUBITestLong, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0x468B3415",
    });
    When({
        "SUBI.L #0x14761244, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1008",
        "CYCLES is 34",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0x321521D1",
    });
}

TEST_F(SUBITestLong, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).L is 0x468B3415",
    });
    When({
        "SUBI.L #0x14761244, (0x6000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1008",
        "CYCLES is 32",
        "(0x00006000).L is 0x321521D1",
    });
}

TEST_F(SUBITestLong, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).L is 0x468B3415",
    });
    When({
        "SUBI.L #0x14761244, (0x00006000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x100A",
        "CYCLES is 36",
        "(0x00006000).L is 0x321521D1",
    });
}

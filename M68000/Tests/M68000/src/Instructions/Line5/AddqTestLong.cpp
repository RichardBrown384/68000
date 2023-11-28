#include "M68000/Fixtures/M68000Test.h"

class ADDQTestLong : public M68000Test {};

TEST_F(ADDQTestLong, DataDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xFEEFFFFE",
    });
    When({
        "ADDQ.L #0x00000003, D4"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 8",
        "D4 is 0xFEF00001",
    });
}

TEST_F(ADDQTestLong, DataDirectAdd8Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x700FFFF9",
    });
    When({
        "ADDQ.L #0x08, D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D4 is 0x70100001",
    });
}

TEST_F(ADDQTestLong, DataDirectFlagNWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xF000FFFF",
    });
    When({
        "ADDQ.L #0x01, D4"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 8",
        "D4 is 0xF0010000",
    });
}

TEST_F(ADDQTestLong, DataDirectFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xFFFFFFFF",
    });
    When({
        "ADDQ.L #0x01, D4"
    });
    Then({
        "SR is S,0,XZC",
        "PC is 0x1002",
        "CYCLES is 8",
        "D4 is 0x00000000",
    });
}

TEST_F(ADDQTestLong, DataDirectFlagVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x7FFFFFFF",
    });
    When({
        "ADDQ.L #0x01, D4"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1002",
        "CYCLES is 8",
        "D4 is 0x80000000",
    });
}

TEST_F(ADDQTestLong, DataDirectFlagCWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xFFFFFFFF",
    });
    When({
        "ADDQ.L #0x02, D4"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 8",
        "D4 is 0x00000001",
    });
}

TEST_F(ADDQTestLong, AddressDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0xFEEFFFFE",
    });
    When({
        "ADDQ.L #0x00000003, A4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "A4 is 0xFEF00001",
    });
}

TEST_F(ADDQTestLong, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).L is 0xFEEFFFFE",
    });
    When({
        "ADDQ.L #0x00000003, (A4)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 20",
        "A4 is 0x00006000",
        "(0x00006000).L is 0xFEF00001",
    });
}

TEST_F(ADDQTestLong, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).L is 0xFEEFFFFE",
    });
    When({
        "ADDQ.L #0x00000003, (A4)+"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 20",
        "A4 is 0x00006004",
        "(0x00006000).L is 0xFEF00001",
    });
}

TEST_F(ADDQTestLong, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005FFC).L is 0xFEEFFFFE",
    });
    When({
        "ADDQ.L #0x00000003, -(A4)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 22",
        "A4 is 0x00005FFC",
        "(0x00005FFC).L is 0xFEF00001",
    });
}

TEST_F(ADDQTestLong, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0xFEEFFFFE",
    });
    When({
        "ADDQ.L #0x00000003, (0x004C, A4)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 24",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0xFEF00001",
    });
}

TEST_F(ADDQTestLong, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0xFEEFFFFE",
    });
    When({
        "ADDQ.L #0x00000003, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 26",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0xFEF00001",
    });
}

TEST_F(ADDQTestLong, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).L is 0xFEEFFFFE",
    });
    When({
        "ADDQ.L #0x00000003, (0x6000).W"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 24",
        "(0x00006000).L is 0xFEF00001",
    });
}

TEST_F(ADDQTestLong, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).L is 0xFEEFFFFE",
    });
    When({
        "ADDQ.L #0x00000003, (0x00006000).L"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 28",
        "(0x00006000).L is 0xFEF00001",
    });
}

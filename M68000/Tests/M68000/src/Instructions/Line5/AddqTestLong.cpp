#include "M68000/Fixtures/M68000Test.h"

class ADDQTestLong : public M68000Test {};

TEST_F(ADDQTestLong, DataDirectWorks) {
    Given({
        "D4 is 0xFEEFFFFE",
        "SR is S,0,0"
    });
    When({
        "ADDQ.L #0x00000003, D4"
    });
    Then({
        "D4 is 0xFEF00001",
        "SR is S,0,N"
    });
}

TEST_F(ADDQTestLong, DataDirectAdd8Works) {
    Given({
        "D4 is 0x700FFFF9",
        "SR is S,0,0"
    });
    When({
        "ADDQ.L #0x08, D4"
    });
    Then({
        "D4 is 0x70100001",
        "SR is S,0,0"
    });
}

TEST_F(ADDQTestLong, DataDirectFlagNWorks) {
    Given({
        "D4 is 0xF000FFFF",
        "SR is S,0,0"
    });
    When({
        "ADDQ.L #0x01, D4"
    });
    Then({
        "D4 is 0xF0010000",
        "SR is S,0,N"
    });
}

TEST_F(ADDQTestLong, DataDirectFlagZWorks) {
    Given({
        "D4 is 0xFFFFFFFF",
        "SR is S,0,0"
    });
    When({
        "ADDQ.L #0x01, D4"
    });
    Then({
        "D4 is 0x00000000",
        "SR is S,0,XZC"
    });
}

TEST_F(ADDQTestLong, DataDirectFlagVWorks) {
    Given({
        "D4 is 0x7FFFFFFF",
        "SR is S,0,0"
    });
    When({
        "ADDQ.L #0x01, D4"
    });
    Then({
        "D4 is 0x80000000",
        "SR is S,0,NV"
    });
}

TEST_F(ADDQTestLong, DataDirectFlagCWorks) {
    Given({
        "D4 is 0xFFFFFFFF",
        "SR is S,0,0"
    });
    When({
        "ADDQ.L #0x02, D4"
    });
    Then({
        "D4 is 0x00000001",
        "SR is S,0,XC"
    });
}

TEST_F(ADDQTestLong, AddressDirectWorks) {
    Given({
        "A4 is 0xFEEFFFFE",
        "SR is S,0,0"
    });
    When({
        "ADDQ.L #0x00000003, A4"
    });
    Then({
        "A4 is 0xFEF00001",
        "SR is S,0,0"
    });
}

TEST_F(ADDQTestLong, AddressIndirectWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).L is 0xFEEFFFFE",
        "SR is S,0,0"
    });
    When({
        "ADDQ.L #0x00000003, (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).L is 0xFEF00001",
        "SR is S,0,N"
    });
}

TEST_F(ADDQTestLong, AddressIncrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).L is 0xFEEFFFFE",
        "SR is S,0,0"
    });
    When({
        "ADDQ.L #0x00000003, (A4)+"
    });
    Then({
        "A4 is 0x00006004",
        "(0x00006000).L is 0xFEF00001",
        "SR is S,0,N"
    });
}

TEST_F(ADDQTestLong, AddressDecrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFC).L is 0xFEEFFFFE",
        "SR is S,0,0"
    });
    When({
        "ADDQ.L #0x00000003, -(A4)"
    });
    Then({
        "A4 is 0x00005FFC",
        "(0x00005FFC).L is 0xFEF00001",
        "SR is S,0,N"
    });
}

TEST_F(ADDQTestLong, AddressDisplacementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).L is 0xFEEFFFFE",
        "SR is S,0,0"
    });
    When({
        "ADDQ.L #0x00000003, (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).L is 0xFEF00001",
        "SR is S,0,N"
    });
}

TEST_F(ADDQTestLong, AddressIndexWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0xFEEFFFFE",
        "SR is S,0,0"
    });
    When({
        "ADDQ.L #0x00000003, (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0xFEF00001",
        "SR is S,0,N"
    });
}

TEST_F(ADDQTestLong, ShortWorks) {
    Given({
        "(0x00006000).L is 0xFEEFFFFE",
        "SR is S,0,0"
    });
    When({
        "ADDQ.L #0x00000003, (0x6000).W"
    });
    Then({
        "(0x00006000).L is 0xFEF00001",
        "SR is S,0,N"
    });
}

TEST_F(ADDQTestLong, LongWorks) {
    Given({
        "(0x00006000).L is 0xFEEFFFFE",
        "SR is S,0,0"
    });
    When({
        "ADDQ.L #0x00000003, (0x00006000).L"
    });
    Then({
        "(0x00006000).L is 0xFEF00001",
        "SR is S,0,N"
    });
}

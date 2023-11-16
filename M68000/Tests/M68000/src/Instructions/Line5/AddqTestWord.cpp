#include "M68000/Fixtures/M68000Test.h"

class ADDQTestWord : public M68000Test {};

TEST_F(ADDQTestWord, DataDirectWorks) {
    Given({
        "D4 is 0xFEEFFFFE",
        "SR is S,0,0"
    });
    When({
        "ADDQ.W #0x0003, D4"
    });
    Then({
        "D4 is 0xFEEF0001",
        "SR is S,0,XC"
    });
}

TEST_F(ADDQTestWord, DataDirectAdd8Works) {
    Given({
        "D4 is 0xFEEF40F9",
        "SR is S,0,0"
    });
    When({
        "ADDQ.W #0x08, D4"
    });
    Then({
        "D4 is 0xFEEF4101",
        "SR is S,0,0"
    });
}

TEST_F(ADDQTestWord, DataDirectFlagNWorks) {
    Given({
        "D4 is 0xFEEFF00E",
        "SR is S,0,0"
    });
    When({
        "ADDQ.W #0x01, D4"
    });
    Then({
        "D4 is 0xFEEFF00F",
        "SR is S,0,N"
    });
}

TEST_F(ADDQTestWord, DataDirectFlagZWorks) {
    Given({
        "D4 is 0xFEEFFFFF",
        "SR is S,0,0"
    });
    When({
        "ADDQ.W #0x01, D4"
    });
    Then({
        "D4 is 0xFEEF0000",
        "SR is S,0,XZC"
    });
}

TEST_F(ADDQTestWord, DataDirectFlagVWorks) {
    Given({
        "D4 is 0xFEEF7FFF",
        "SR is S,0,0"
    });
    When({
        "ADDQ.W #0x01, D4"
    });
    Then({
        "D4 is 0xFEEF8000",
        "SR is S,0,NV"
    });
}

TEST_F(ADDQTestWord, DataDirectFlagCWorks) {
    Given({
        "D4 is 0xFEEFFFFF",
        "SR is S,0,0"
    });
    When({
        "ADDQ.W #0x02, D4"
    });
    Then({
        "D4 is 0xFEEF0001",
        "SR is S,0,XC"
    });
}

TEST_F(ADDQTestWord, AddressDirectWorks) {
    Given({
        "A4 is 0xFEEFFFFE",
        "SR is S,0,0"
    });
    When({
        "ADDQ.W #0x0003, A4"
    });
    Then({
        "A4 is 0xFEF00001",
        "SR is S,0,0"
    });
}

TEST_F(ADDQTestWord, AddressIndirectWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).W is 0xFFFE",
        "SR is S,0,0"
    });
    When({
        "ADDQ.W #0x0003, (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).W is 0x0001",
        "SR is S,0,XC"
    });
}

TEST_F(ADDQTestWord, AddressIncrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).W is 0xFFFE",
        "SR is S,0,0"
    });
    When({
        "ADDQ.W #0x0003, (A4)+"
    });
    Then({
        "A4 is 0x00006002",
        "(0x00006000).W is 0x0001",
        "SR is S,0,XC"
    });
}

TEST_F(ADDQTestWord, AddressDecrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFE).W is 0xFFFE",
        "SR is S,0,0"
    });
    When({
        "ADDQ.W #0x0003, -(A4)"
    });
    Then({
        "A4 is 0x00005FFE",
        "(0x00005FFE).W is 0x0001",
        "SR is S,0,XC"
    });
}

TEST_F(ADDQTestWord, AddressDisplacementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).W is 0xFFFE",
        "SR is S,0,0"
    });
    When({
        "ADDQ.W #0x0003, (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x0001",
        "SR is S,0,XC"
    });
}

TEST_F(ADDQTestWord, AddressIndexWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0xFFFE",
        "SR is S,0,0"
    });
    When({
        "ADDQ.W #0x0003, (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x0001",
        "SR is S,0,XC"
    });
}

TEST_F(ADDQTestWord, ShortWorks) {
    Given({
        "(0x00006000).W is 0xFFFE",
        "SR is S,0,0"
    });
    When({
        "ADDQ.W #0x0003, (0x6000).W"
    });
    Then({
        "(0x00006000).W is 0x0001",
        "SR is S,0,XC"
    });
}

TEST_F(ADDQTestWord, LongWorks) {
    Given({
        "(0x00006000).W is 0xFFFE",
        "SR is S,0,0"
    });
    When({
        "ADDQ.W #0x0003, (0x00006000).L"
    });
    Then({
        "(0x00006000).W is 0x0001",
        "SR is S,0,XC"
    });
}

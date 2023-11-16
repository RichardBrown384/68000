#include "M68000/Fixtures/M68000Test.h"

class ADDQTestByte : public M68000Test {};

TEST_F(ADDQTestByte, DataDirectWorks) {
    Given({
        "D4 is 0xFEEFFFFE",
        "SR is S,0,0"
    });
    When({
        "ADDQ.B #0x03, D4"
    });
    Then({
        "D4 is 0xFEEFFF01",
        "SR is S,0,XC"
    });
}

TEST_F(ADDQTestByte, DataDirectAdd8Works) {
    Given({
        "D4 is 0xFEEFFF03",
        "SR is S,0,0"
    });
    When({
        "ADDQ.B #0x08, D4"
    });
    Then({
        "D4 is 0xFEEFFF0B",
        "SR is S,0,0"
    });
}

TEST_F(ADDQTestByte, DataDirectFlagNWorks) {
    Given({
        "D4 is 0xFEEF00FE",
        "SR is S,0,0"
    });
    When({
        "ADDQ.B #0x01, D4"
    });
    Then({
        "D4 is 0xFEEF00FF",
        "SR is S,0,N"
    });
}

TEST_F(ADDQTestByte, DataDirectFlagZWorks) {
    Given({
        "D4 is 0xFEEFFFFF",
        "SR is S,0,0"
    });
    When({
        "ADDQ.B #0x01, D4"
    });
    Then({
        "D4 is 0xFEEFFF00",
        "SR is S,0,XZC"
    });
}

TEST_F(ADDQTestByte, DataDirectFlagVWorks) {
    Given({
        "D4 is 0xFEEFFF7F",
        "SR is S,0,0"
    });
    When({
        "ADDQ.B #0x01, D4"
    });
    Then({
        "D4 is 0xFEEFFF80",
        "SR is S,0,NV"
    });
}

TEST_F(ADDQTestByte, DataDirectFlagCWorks) {
    Given({
        "D4 is 0xFEEFFFFF",
        "SR is S,0,0"
    });
    When({
        "ADDQ.B #0x02, D4"
    });
    Then({
        "D4 is 0xFEEFFF01",
        "SR is S,0,XC"
    });
}

TEST_F(ADDQTestByte, AddressIndirectWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFE",
        "SR is S,0,0"
    });
    When({
        "ADDQ.B #0x03, (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x01",
        "SR is S,0,XC"
    });
}

TEST_F(ADDQTestByte, AddressIncrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFE",
        "SR is S,0,0"
    });
    When({
        "ADDQ.B #0x03, (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0x01",
        "SR is S,0,XC"
    });
}

TEST_F(ADDQTestByte, AddressDecrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xFE",
        "SR is S,0,0"
    });
    When({
        "ADDQ.B #0x03, -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x01",
        "SR is S,0,XC"
    });
}

TEST_F(ADDQTestByte, AddressDisplacementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xFE",
        "SR is S,0,0"
    });
    When({
        "ADDQ.B #0x03, (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x01",
        "SR is S,0,XC"
    });
}

TEST_F(ADDQTestByte, AddressIndexWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xFE",
        "SR is S,0,0"
    });
    When({
        "ADDQ.B #0x03, (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x01",
        "SR is S,0,XC"
    });
}

TEST_F(ADDQTestByte, ShortWorks) {
    Given({
        "(0x00006000).B is 0xFE",
        "SR is S,0,0"
    });
    When({
        "ADDQ.B #0x03, (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0x01",
        "SR is S,0,XC"
    });
}

TEST_F(ADDQTestByte, LongWorks) {
    Given({
        "(0x00006000).B is 0xFE",
        "SR is S,0,0"
    });
    When({
        "ADDQ.B #0x03, (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0x01",
        "SR is S,0,XC"
    });
}

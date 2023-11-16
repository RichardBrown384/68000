#include "M68000/Fixtures/M68000Test.h"

class SUBQTestByte : public M68000Test {};

TEST_F(SUBQTestByte, DataDirectWorks) {
    Given({
        "D4 is 0x01000004",
        "SR is S,0,0"
    });
    When({
        "SUBQ.B #0x06, D4"
    });
    Then({
        "D4 is 0x010000FE",
        "SR is S,0,XNC"
    });
}

TEST_F(SUBQTestByte, DataDirectSub8Works) {
    Given({
        "D4 is 0xFEEFFF74",
        "SR is S,0,0"
    });
    When({
        "SUBQ.B #0x08, D4"
    });
    Then({
        "D4 is 0xFEEFFF6C",
        "SR is S,0,0"
    });
}

TEST_F(SUBQTestByte, DataDirectFlagNWorks) {
    Given({
        "D4 is 0xFEEF00FE",
        "SR is S,0,0"
    });
    When({
        "SUBQ.B #0x01, D4"
    });
    Then({
        "D4 is 0xFEEF00FD",
        "SR is S,0,N"
    });
}

TEST_F(SUBQTestByte, DataDirectFlagZWorks) {
    Given({
        "D4 is 0xFEEFFF01",
        "SR is S,0,0"
    });
    When({
        "SUBQ.B #0x01, D4"
    });
    Then({
        "D4 is 0xFEEFFF00",
        "SR is S,0,Z"
    });
}

TEST_F(SUBQTestByte, DataDirectFlagVWorks) {
    Given({
        "D4 is 0xFEEFFF80",
        "SR is S,0,0"
    });
    When({
        "SUBQ.B #0x01, D4"
    });
    Then({
        "D4 is 0xFEEFFF7F",
        "SR is S,0,V"
    });
}

TEST_F(SUBQTestByte, DataDirectFlagCWorks) {
    Given({
        "D4 is 0xFEEFFF00",
        "SR is S,0,0"
    });
    When({
        "SUBQ.B #0x01, D4"
    });
    Then({
        "D4 is 0xFEEFFFFF",
        "SR is S,0,XNC"
    });
}

TEST_F(SUBQTestByte, AddressIndirectWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x04",
        "SR is S,0,0"
    });
    When({
        "SUBQ.B #0x06, (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFE",
        "SR is S,0,XNC"
    });
}

TEST_F(SUBQTestByte, AddressIncrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x04",
        "SR is S,0,0"
    });
    When({
        "SUBQ.B #0x06, (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0xFE",
        "SR is S,0,XNC"
    });
}

TEST_F(SUBQTestByte, AddressDecrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0x04",
        "SR is S,0,0"
    });
    When({
        "SUBQ.B #0x06, -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xFE",
        "SR is S,0,XNC"
    });
}

TEST_F(SUBQTestByte, AddressDisplacementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x04",
        "SR is S,0,0"
    });
    When({
        "SUBQ.B #0x06, (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xFE",
        "SR is S,0,XNC"
    });
}

TEST_F(SUBQTestByte, AddressIndexWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x04",
        "SR is S,0,0"
    });
    When({
        "SUBQ.B #0x06, (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xFE",
        "SR is S,0,XNC"
    });
}

TEST_F(SUBQTestByte, ShortWorks) {
    Given({
        "(0x00006000).B is 0x04",
        "SR is S,0,0"
    });
    When({
        "SUBQ.B #0x06, (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0xFE",
        "SR is S,0,XNC"
    });
}

TEST_F(SUBQTestByte, LongWorks) {
    Given({
        "(0x00006000).B is 0x04",
        "SR is S,0,0"
    });
    When({
        "SUBQ.B #0x06, (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0xFE",
        "SR is S,0,XNC"
    });
}

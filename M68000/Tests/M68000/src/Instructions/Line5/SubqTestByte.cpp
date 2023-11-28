#include "M68000/Fixtures/M68000Test.h"

class SUBQTestByte : public M68000Test {};

TEST_F(SUBQTestByte, DataDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x01000004",
    });
    When({
        "SUBQ.B #0x06, D4"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 4",
        "D4 is 0x010000FE",
    });
}

TEST_F(SUBQTestByte, DataDirectSub8Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xFEEFFF74",
    });
    When({
        "SUBQ.B #0x08, D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D4 is 0xFEEFFF6C",
    });
}

TEST_F(SUBQTestByte, DataDirectFlagNWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xFEEF00FE",
    });
    When({
        "SUBQ.B #0x01, D4"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 4",
        "D4 is 0xFEEF00FD",
    });
}

TEST_F(SUBQTestByte, DataDirectFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xFEEFFF01",
    });
    When({
        "SUBQ.B #0x01, D4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 4",
        "D4 is 0xFEEFFF00",
    });
}

TEST_F(SUBQTestByte, DataDirectFlagVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xFEEFFF80",
    });
    When({
        "SUBQ.B #0x01, D4"
    });
    Then({
        "SR is S,0,V",
        "PC is 0x1002",
        "CYCLES is 4",
        "D4 is 0xFEEFFF7F",
    });
}

TEST_F(SUBQTestByte, DataDirectFlagCWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xFEEFFF00",
    });
    When({
        "SUBQ.B #0x01, D4"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 4",
        "D4 is 0xFEEFFFFF",
    });
}

TEST_F(SUBQTestByte, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0x04",
    });
    When({
        "SUBQ.B #0x06, (A4)"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 12",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFE",
    });
}

TEST_F(SUBQTestByte, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0x04",
    });
    When({
        "SUBQ.B #0x06, (A4)+"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 12",
        "A4 is 0x00006001",
        "(0x00006000).B is 0xFE",
    });
}

TEST_F(SUBQTestByte, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0x04",
    });
    When({
        "SUBQ.B #0x06, -(A4)"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 14",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xFE",
    });
}

TEST_F(SUBQTestByte, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x04",
    });
    When({
        "SUBQ.B #0x06, (0x004C, A4)"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1004",
        "CYCLES is 16",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xFE",
    });
}

TEST_F(SUBQTestByte, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x04",
    });
    When({
        "SUBQ.B #0x06, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1004",
        "CYCLES is 18",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xFE",
    });
}

TEST_F(SUBQTestByte, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).B is 0x04",
    });
    When({
        "SUBQ.B #0x06, (0x6000).W"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1004",
        "CYCLES is 16",
        "(0x00006000).B is 0xFE",
    });
}

TEST_F(SUBQTestByte, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).B is 0x04",
    });
    When({
        "SUBQ.B #0x06, (0x00006000).L"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1006",
        "CYCLES is 20",
        "(0x00006000).B is 0xFE",
    });
}

#include "M68000/Fixtures/M68000Test.h"

class ADDQTestByte : public M68000Test {};

TEST_F(ADDQTestByte, DataDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xFEEFFFFE",
    });
    When({
        "ADDQ.B #0x03, D4"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 4",
        "D4 is 0xFEEFFF01",
    });
}

TEST_F(ADDQTestByte, DataDirectAdd8Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xFEEFFF03",
    });
    When({
        "ADDQ.B #0x08, D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D4 is 0xFEEFFF0B",
    });
}

TEST_F(ADDQTestByte, DataDirectFlagNWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xFEEF00FE",
    });
    When({
        "ADDQ.B #0x01, D4"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 4",
        "D4 is 0xFEEF00FF",
    });
}

TEST_F(ADDQTestByte, DataDirectFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xFEEFFFFF",
    });
    When({
        "ADDQ.B #0x01, D4"
    });
    Then({
        "SR is S,0,XZC",
        "PC is 0x1002",
        "CYCLES is 4",
        "D4 is 0xFEEFFF00",
    });
}

TEST_F(ADDQTestByte, DataDirectFlagVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xFEEFFF7F",
    });
    When({
        "ADDQ.B #0x01, D4"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1002",
        "CYCLES is 4",
        "D4 is 0xFEEFFF80",
    });
}

TEST_F(ADDQTestByte, DataDirectFlagCWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xFEEFFFFF",
    });
    When({
        "ADDQ.B #0x02, D4"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 4",
        "D4 is 0xFEEFFF01",
    });
}

TEST_F(ADDQTestByte, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFE",
    });
    When({
        "ADDQ.B #0x03, (A4)"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 12",
        "A4 is 0x00006000",
        "(0x00006000).B is 0x01",
    });
}

TEST_F(ADDQTestByte, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0xFE",
    });
    When({
        "ADDQ.B #0x03, (A4)+"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 12",
        "A4 is 0x00006001",
        "(0x00006000).B is 0x01",
    });
}

TEST_F(ADDQTestByte, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0xFE",
    });
    When({
        "ADDQ.B #0x03, -(A4)"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 14",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x01",
    });
}

TEST_F(ADDQTestByte, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xFE",
    });
    When({
        "ADDQ.B #0x03, (0x004C, A4)"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1004",
        "CYCLES is 16",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x01",
    });
}

TEST_F(ADDQTestByte, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0xFE",
    });
    When({
        "ADDQ.B #0x03, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1004",
        "CYCLES is 18",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x01",
    });
}

TEST_F(ADDQTestByte, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).B is 0xFE",
    });
    When({
        "ADDQ.B #0x03, (0x6000).W"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1004",
        "CYCLES is 16",
        "(0x00006000).B is 0x01",
    });
}

TEST_F(ADDQTestByte, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).B is 0xFE",
    });
    When({
        "ADDQ.B #0x03, (0x00006000).L"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1006",
        "CYCLES is 20",
        "(0x00006000).B is 0x01",
    });
}

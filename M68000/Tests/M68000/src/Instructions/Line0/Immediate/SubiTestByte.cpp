#include "M68000/Fixtures/M68000Test.h"

class SUBITestByte : public M68000Test {};

TEST_F(SUBITestByte, DataDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x768B3415",
    });
    When({
        "SUBI.B #0x14, D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 8",
        "D4 is 0x768B3401",
    });
}

TEST_F(SUBITestByte, DataDirectFlagNVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01010171",
    });
    When({
        "SUBI.B #0x80, D1"
    });
    Then({
        "SR is S,0,XNVC",
        "PC is 0x1004",
        "CYCLES is 8",
        "D1 is 0x010101F1",
    });
}

TEST_F(SUBITestByte, DataDirectFlagXWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D2 is 0x01010101",
    });
    When({
        "SUBI.B #0x02, D2"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1004",
        "CYCLES is 8",
        "D2 is 0x010101FF",
    });
}

TEST_F(SUBITestByte, DataDirectFlagNWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x768B3495",
    });
    When({
        "SUBI.B #0x01, D4"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 8",
        "D4 is 0x768B3494",
    });
}

TEST_F(SUBITestByte, DataDirectFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x768B3401",
    });
    When({
        "SUBI.B #0x01, D4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 8",
        "D4 is 0x768B3400",
    });
}

TEST_F(SUBITestByte, DataDirectFlagVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x768B3480",
    });
    When({
        "SUBI.B #0x03, D4"
    });
    Then({
        "SR is S,0,V",
        "PC is 0x1004",
        "CYCLES is 8",
        "D4 is 0x768B347D",
    });
}

TEST_F(SUBITestByte, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0x72",
    });
    When({
        "SUBI.B #0x14, (A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "A4 is 0x00006000",
        "(0x00006000).B is 0x5E",
    });
}

TEST_F(SUBITestByte, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0x72",
    });
    When({
        "SUBI.B #0x14, (A4)+"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "A4 is 0x00006001",
        "(0x00006000).B is 0x5E",
    });
}

TEST_F(SUBITestByte, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0x72",
    });
    When({
        "SUBI.B #0x14, -(A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x5E",
    });
}

TEST_F(SUBITestByte, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x72",
    });
    When({
        "SUBI.B #0x14, (0x004C, A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 20",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x5E",
    });
}

TEST_F(SUBITestByte, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x72",
    });
    When({
        "SUBI.B #0x14, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 22",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x5E",
    });
}

TEST_F(SUBITestByte, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).B is 0x72",
    });
    When({
        "SUBI.B #0x14, (0x6000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 20",
        "(0x00006000).B is 0x5E",
    });
}

TEST_F(SUBITestByte, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).B is 0x72",
    });
    When({
        "SUBI.B #0x14, (0x00006000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1008",
        "CYCLES is 24",
        "(0x00006000).B is 0x5E",
    });
}

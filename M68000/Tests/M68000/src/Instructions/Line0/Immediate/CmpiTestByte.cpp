#include "M68000/Fixtures/M68000Test.h"

class CMPITestByte : public M68000Test {};

TEST_F(CMPITestByte, DataDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x768B3415",
    });
    When({
        "CMPI.B #0x84, D4"
    });
    Then({
        "SR is S,0,NVC",
        "PC is 0x1004",
        "CYCLES is 8",
        "D4 is 0x768B3415",
    });
}

TEST_F(CMPITestByte, DataDirectFlagNVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01010171",
    });
    When({
        "CMPI.B #0x80, D1"
    });
    Then({
        "SR is S,0,NVC",
        "PC is 0x1004",
        "CYCLES is 8",
        "D1 is 0x01010171",
    });
}

TEST_F(CMPITestByte, DataDirectFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D2 is 0x01010101",
    });
    When({
        "CMPI.B #0x02, D2"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1004",
        "CYCLES is 8",
        "D2 is 0x01010101",
    });
}

TEST_F(CMPITestByte, DataDirectFlagNWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x768B3495",
    });
    When({
        "CMPI.B #0x01, D4"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 8",
        "D4 is 0x768B3495",
    });
}

TEST_F(CMPITestByte, DataDirectFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x768B3401",
    });
    When({
        "CMPI.B #0x01, D4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 8",
        "D4 is 0x768B3401",
    });
}

TEST_F(CMPITestByte, DataDirectFlagVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x768B3480",
    });
    When({
        "CMPI.B #0x03, D4"
    });
    Then({
        "SR is S,0,V",
        "PC is 0x1004",
        "CYCLES is 8",
        "D4 is 0x768B3480",
    });
}

TEST_F(CMPITestByte, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0x72",
    });
    When({
        "CMPI.B #0x84, (A4)"
    });
    Then({
        "SR is S,0,NVC",
        "PC is 0x1004",
        "CYCLES is 12",
        "A4 is 0x00006000",
        "(0x00006000).B is 0x72",
    });
}

TEST_F(CMPITestByte, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0x72",
    });
    When({
        "CMPI.B #0x84, (A4)+"
    });
    Then({
        "SR is S,0,NVC",
        "PC is 0x1004",
        "CYCLES is 12",
        "A4 is 0x00006001",
        "(0x00006000).B is 0x72",
    });
}

TEST_F(CMPITestByte, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0x72",
    });
    When({
        "CMPI.B #0x84, -(A4)"
    });
    Then({
        "SR is S,0,NVC",
        "PC is 0x1004",
        "CYCLES is 14",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x72",
    });
}

TEST_F(CMPITestByte, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x72",
    });
    When({
        "CMPI.B #0x84, (0x004C, A4)"
    });
    Then({
        "SR is S,0,NVC",
        "PC is 0x1006",
        "CYCLES is 16",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x72",
    });
}

TEST_F(CMPITestByte, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x72",
    });
    When({
        "CMPI.B #0x84, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,NVC",
        "PC is 0x1006",
        "CYCLES is 18",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x72",
    });
}

TEST_F(CMPITestByte, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).B is 0x72",
    });
    When({
        "CMPI.B #0x84, (0x6000).W"
    });
    Then({
        "SR is S,0,NVC",
        "PC is 0x1006",
        "CYCLES is 16",
        "(0x00006000).B is 0x72",
    });
}

TEST_F(CMPITestByte, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).B is 0x72",
    });
    When({
        "CMPI.B #0x84, (0x00006000).L"
    });
    Then({
        "SR is S,0,NVC",
        "PC is 0x1008",
        "CYCLES is 20",
        "(0x00006000).B is 0x72",
    });
}

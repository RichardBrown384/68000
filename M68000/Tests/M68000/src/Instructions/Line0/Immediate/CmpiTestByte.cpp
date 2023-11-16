#include "M68000/Fixtures/M68000Test.h"

class CMPITestByte : public M68000Test {};

TEST_F(CMPITestByte, DataDirectWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "CMPI.B #0x84, D4"
    });
    Then({
        "D4 is 0x768B3415",
        "SR is S,0,NVC"
    });
}

TEST_F(CMPITestByte, DataDirectFlagNVWorks) {
    Given({
        "D1 is 0x01010171",
        "SR is S,0,0"
    });
    When({
        "CMPI.B #0x80, D1"
    });
    Then({
        "D1 is 0x01010171",
        "SR is S,0,NVC"
    });
}

TEST_F(CMPITestByte, DataDirectFlagXWorks) {
    Given({
        "D2 is 0x01010101",
        "SR is S,0,X"
    });
    When({
        "CMPI.B #0x02, D2"
    });
    Then({
        "D2 is 0x01010101",
        "SR is S,0,XNC"
    });
}

TEST_F(CMPITestByte, DataDirectFlagNWorks) {
    Given({
        "D4 is 0x768B3495",
        "SR is S,0,0"
    });
    When({
        "CMPI.B #0x01, D4"
    });
    Then({
        "D4 is 0x768B3495",
        "SR is S,0,N"
    });
}

TEST_F(CMPITestByte, DataDirectFlagZWorks) {
    Given({
        "D4 is 0x768B3401",
        "SR is S,0,0"
    });
    When({
        "CMPI.B #0x01, D4"
    });
    Then({
        "D4 is 0x768B3401",
        "SR is S,0,Z"
    });
}

TEST_F(CMPITestByte, DataDirectFlagVWorks) {
    Given({
        "D4 is 0x768B3480",
        "SR is S,0,0"
    });
    When({
        "CMPI.B #0x03, D4"
    });
    Then({
        "D4 is 0x768B3480",
        "SR is S,0,V"
    });
}

TEST_F(CMPITestByte, AddressIndirectWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x72",
        "SR is S,0,0"
    });
    When({
        "CMPI.B #0x84, (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x72",
        "SR is S,0,NVC"
    });
}

TEST_F(CMPITestByte, AddressIncrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x72",
        "SR is S,0,0"
    });
    When({
        "CMPI.B #0x84, (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0x72",
        "SR is S,0,NVC"
    });
}

TEST_F(CMPITestByte, AddressDecrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0x72",
        "SR is S,0,0"
    });
    When({
        "CMPI.B #0x84, -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x72",
        "SR is S,0,NVC"
    });
}

TEST_F(CMPITestByte, AddressDisplacementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x72",
        "SR is S,0,0"
    });
    When({
        "CMPI.B #0x84, (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x72",
        "SR is S,0,NVC"
    });
}

TEST_F(CMPITestByte, AddressIndexWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x72",
        "SR is S,0,0"
    });
    When({
        "CMPI.B #0x84, (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x72",
        "SR is S,0,NVC"
    });
}

TEST_F(CMPITestByte, ShortWorks) {
    Given({
        "(0x00006000).B is 0x72",
        "SR is S,0,0"
    });
    When({
        "CMPI.B #0x84, (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0x72",
        "SR is S,0,NVC"
    });
}

TEST_F(CMPITestByte, LongWorks) {
    Given({
        "(0x00006000).B is 0x72",
        "SR is S,0,0"
    });
    When({
        "CMPI.B #0x84, (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0x72",
        "SR is S,0,NVC"
    });
}

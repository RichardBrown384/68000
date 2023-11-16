#include "M68000/Fixtures/M68000Test.h"

class ADDITestByte : public M68000Test {};

TEST_F(ADDITestByte, DataDirectWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "ADDI.B #0x44, D4"
    });
    Then({
        "D4 is 0x768B3459",
        "SR is S,0,0"
    });
}

TEST_F(ADDITestByte, DataDirectFlagNVWorks) {
    Given({
        "D1 is 0x01010110",
        "SR is S,0,0"
    });
    When({
        "ADDI.B #0x70, D1"
    });
    Then({
        "D1 is 0x01010180",
        "SR is S,0,NV"
    });
}

TEST_F(ADDITestByte, DataDirectFlagXWorks) {
    Given({
        "D2 is 0x010101FF",
        "SR is S,0,0"
    });
    When({
        "ADDI.B #0x02, D2"
    });
    Then({
        "D2 is 0x01010101",
        "SR is S,0,XC"
    });
}

TEST_F(ADDITestByte, DataDirectFlagNWorks) {
    Given({
        "D4 is 0x768B3495",
        "SR is S,0,0"
    });
    When({
        "ADDI.B #0x01, D4"
    });
    Then({
        "D4 is 0x768B3496",
        "SR is S,0,N"
    });
}

TEST_F(ADDITestByte, DataDirectFlagZWorks) {
    Given({
        "D4 is 0x768B3400",
        "SR is S,0,0"
    });
    When({
        "ADDI.B #0x00, D4"
    });
    Then({
        "D4 is 0x768B3400",
        "SR is S,0,Z"
    });
}

TEST_F(ADDITestByte, DataDirectFlagsVCWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,VC"
    });
    When({
        "ADDI.B #0x44, D4"
    });
    Then({
        "D4 is 0x768B3459",
        "SR is S,0,0"
    });
}

TEST_F(ADDITestByte, AddressIndirectWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "ADDI.B #0x44, (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x59",
        "SR is S,0,0"
    });
}

TEST_F(ADDITestByte, AddressIncrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "ADDI.B #0x44, (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0x59",
        "SR is S,0,0"
    });
}

TEST_F(ADDITestByte, AddressDecrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "ADDI.B #0x44, -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x59",
        "SR is S,0,0"
    });
}

TEST_F(ADDITestByte, AddressDisplacementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "ADDI.B #0x44, (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x59",
        "SR is S,0,0"
    });
}

TEST_F(ADDITestByte, AddressIndexWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "ADDI.B #0x44, (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x59",
        "SR is S,0,0"
    });
}

TEST_F(ADDITestByte, ShortWorks) {
    Given({
        "(0x00006000).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "ADDI.B #0x44, (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0x59",
        "SR is S,0,0"
    });
}

TEST_F(ADDITestByte, LongWorks) {
    Given({
        "(0x00006000).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "ADDI.B #0x44, (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0x59",
        "SR is S,0,0"
    });
}

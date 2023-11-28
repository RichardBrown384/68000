#include "M68000/Fixtures/M68000Test.h"

class ADDITestByte : public M68000Test {};

TEST_F(ADDITestByte, DataDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x768B3415",
    });
    When({
        "ADDI.B #0x44, D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 8",
        "D4 is 0x768B3459",
    });
}

TEST_F(ADDITestByte, DataDirectFlagNVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01010110",
    });
    When({
        "ADDI.B #0x70, D1"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1004",
        "CYCLES is 8",
        "D1 is 0x01010180",
    });
}

TEST_F(ADDITestByte, DataDirectFlagXWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D2 is 0x010101FF",
    });
    When({
        "ADDI.B #0x02, D2"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1004",
        "CYCLES is 8",
        "D2 is 0x01010101",
    });
}

TEST_F(ADDITestByte, DataDirectFlagNWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x768B3495",
    });
    When({
        "ADDI.B #0x01, D4"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 8",
        "D4 is 0x768B3496",
    });
}

TEST_F(ADDITestByte, DataDirectFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x768B3400",
    });
    When({
        "ADDI.B #0x00, D4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 8",
        "D4 is 0x768B3400",
    });
}

TEST_F(ADDITestByte, DataDirectFlagsVCWorks) {
    Given({
        "SR is S,0,VC",
        "PC is 0x1000",
        "D4 is 0x768B3415",
    });
    When({
        "ADDI.B #0x44, D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 8",
        "D4 is 0x768B3459",
    });
}

TEST_F(ADDITestByte, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0x15",
    });
    When({
        "ADDI.B #0x44, (A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "A4 is 0x00006000",
        "(0x00006000).B is 0x59",
    });
}

TEST_F(ADDITestByte, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).B is 0x15",
    });
    When({
        "ADDI.B #0x44, (A4)+"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "A4 is 0x00006001",
        "(0x00006000).B is 0x59",
    });
}

TEST_F(ADDITestByte, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0x15",
    });
    When({
        "ADDI.B #0x44, -(A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x59",
    });
}

TEST_F(ADDITestByte, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x15",
    });
    When({
        "ADDI.B #0x44, (0x004C, A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 20",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x59",
    });
}

TEST_F(ADDITestByte, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x15",
    });
    When({
        "ADDI.B #0x44, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 22",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x59",
    });
}

TEST_F(ADDITestByte, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).B is 0x15",
    });
    When({
        "ADDI.B #0x44, (0x6000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 20",
        "(0x00006000).B is 0x59",
    });
}

TEST_F(ADDITestByte, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).B is 0x15",
    });
    When({
        "ADDI.B #0x44, (0x00006000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1008",
        "CYCLES is 24",
        "(0x00006000).B is 0x59",
    });
}

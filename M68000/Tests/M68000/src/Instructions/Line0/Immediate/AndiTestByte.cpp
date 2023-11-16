#include "M68000/Fixtures/M68000Test.h"

class ANDITestByte : public M68000Test {};

TEST_F(ANDITestByte, DataDirectWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "ANDI.B #0x44, D4"
    });
    Then({
        "D4 is 0x768B3404",
        "SR is S,0,0"
    });
}

TEST_F(ANDITestByte, DataDirectFlagXWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,X"
    });
    When({
        "ANDI.B #0x44, D4"
    });
    Then({
        "D4 is 0x768B3404",
        "SR is S,0,X"
    });
}

TEST_F(ANDITestByte, DataDirectFlagNWorks) {
    Given({
        "D4 is 0x768B3495",
        "SR is S,0,0"
    });
    When({
        "ANDI.B #0x94, D4"
    });
    Then({
        "D4 is 0x768B3494",
        "SR is S,0,N"
    });
}

TEST_F(ANDITestByte, DataDirectFlagZWorks) {
    Given({
        "D4 is 0x768B3400",
        "SR is S,0,0"
    });
    When({
        "ANDI.B #0x44, D4"
    });
    Then({
        "D4 is 0x768B3400",
        "SR is S,0,Z"
    });
}

TEST_F(ANDITestByte, DataDirectFlagsVCWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,VC"
    });
    When({
        "ANDI.B #0x44, D4"
    });
    Then({
        "D4 is 0x768B3404",
        "SR is S,0,0"
    });
}

TEST_F(ANDITestByte, AddressIndirectWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "ANDI.B #0x44, (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x04",
        "SR is S,0,0"
    });
}

TEST_F(ANDITestByte, AddressIncrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "ANDI.B #0x44, (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0x04",
        "SR is S,0,0"
    });
}

TEST_F(ANDITestByte, AddressDecrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "ANDI.B #0x44, -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x04",
        "SR is S,0,0"
    });
}

TEST_F(ANDITestByte, AddressDisplacementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "ANDI.B #0x44, (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x04",
        "SR is S,0,0"
    });
}

TEST_F(ANDITestByte, AddressIndexWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "ANDI.B #0x44, (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x04",
        "SR is S,0,0"
    });
}

TEST_F(ANDITestByte, ShortWorks) {
    Given({
        "(0x00006000).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "ANDI.B #0x44, (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0x04",
        "SR is S,0,0"
    });
}

TEST_F(ANDITestByte, LongWorks) {
    Given({
        "(0x00006000).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "ANDI.B #0x44, (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0x04",
        "SR is S,0,0"
    });
}

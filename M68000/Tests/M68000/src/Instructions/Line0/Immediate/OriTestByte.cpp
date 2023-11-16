#include "M68000/Fixtures/M68000Test.h"

class ORITestByte : public M68000Test {};

TEST_F(ORITestByte, DataDirectWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "ORI.B #0x44, D4"
    });
    Then({
        "D4 is 0x768B3455",
        "SR is S,0,0"
    });
}

TEST_F(ORITestByte, DataDirectFlagXWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,X"
    });
    When({
        "ORI.B #0x44, D4"
    });
    Then({
        "D4 is 0x768B3455",
        "SR is S,0,X"
    });
}

TEST_F(ORITestByte, DataDirectFlagNWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "ORI.B #0x84, D4"
    });
    Then({
        "D4 is 0x768B3495",
        "SR is S,0,N"
    });
}

TEST_F(ORITestByte, DataDirectFlagZWorks) {
    Given({
        "D4 is 0x768B3400",
        "SR is S,0,0"
    });
    When({
        "ORI.B #0x00, D4"
    });
    Then({
        "D4 is 0x768B3400",
        "SR is S,0,Z"
    });
}

TEST_F(ORITestByte, DataDirectFlagsVCWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,VC"
    });
    When({
        "ORI.B #0x44, D4"
    });
    Then({
        "D4 is 0x768B3455",
        "SR is S,0,0"
    });
}

TEST_F(ORITestByte, AddressIndirectWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "ORI.B #0x44, (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x55",
        "SR is S,0,0"
    });
}

TEST_F(ORITestByte, AddressIncrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "ORI.B #0x44, (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0x55",
        "SR is S,0,0"
    });
}

TEST_F(ORITestByte, AddressDecrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "ORI.B #0x44, -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x55",
        "SR is S,0,0"
    });
}

TEST_F(ORITestByte, AddressDisplacementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "ORI.B #0x44, (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x55",
        "SR is S,0,0"
    });
}

TEST_F(ORITestByte, AddressIndexWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "ORI.B #0x44, (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x55",
        "SR is S,0,0"
    });
}

TEST_F(ORITestByte, ShortWorks) {
    Given({
        "(0x00006000).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "ORI.B #0x44, (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0x55",
        "SR is S,0,0"
    });
}

TEST_F(ORITestByte, LongWorks) {
    Given({
        "(0x00006000).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "ORI.B #0x44, (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0x55",
        "SR is S,0,0"
    });
}

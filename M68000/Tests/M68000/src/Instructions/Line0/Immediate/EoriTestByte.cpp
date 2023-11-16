#include "M68000/Fixtures/M68000Test.h"

class EORITestByte : public M68000Test {};

TEST_F(EORITestByte, DataDirectWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,0"
    });
    When({
        "EORI.B #0x44, D4"
    });
    Then({
        "D4 is 0x768B3451",
        "SR is S,0,0"
    });
}

TEST_F(EORITestByte, DataDirectFlagXWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,X"
    });
    When({
        "EORI.B #0x44, D4"
    });
    Then({
        "D4 is 0x768B3451",
        "SR is S,0,X"
    });
}

TEST_F(EORITestByte, DataDirectFlagNWorks) {
    Given({
        "D4 is 0x768B3485",
        "SR is S,0,0"
    });
    When({
        "EORI.B #0x44, D4"
    });
    Then({
        "D4 is 0x768B34C1",
        "SR is S,0,N"
    });
}

TEST_F(EORITestByte, DataDirectFlagZWorks) {
    Given({
        "D4 is 0x768B3444",
        "SR is S,0,0"
    });
    When({
        "EORI.B #0x44, D4"
    });
    Then({
        "D4 is 0x768B3400",
        "SR is S,0,Z"
    });
}

TEST_F(EORITestByte, DataDirectFlagsVCWorks) {
    Given({
        "D4 is 0x768B3415",
        "SR is S,0,VC"
    });
    When({
        "EORI.B #0x44, D4"
    });
    Then({
        "D4 is 0x768B3451",
        "SR is S,0,0"
    });
}

TEST_F(EORITestByte, AddressIndirectWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "EORI.B #0x44, (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x51",
        "SR is S,0,0"
    });
}

TEST_F(EORITestByte, AddressIncrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "EORI.B #0x44, (A4)+"
    });
    Then({
        "A4 is 0x00006001",
        "(0x00006000).B is 0x51",
        "SR is S,0,0"
    });
}

TEST_F(EORITestByte, AddressDecrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "EORI.B #0x44, -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0x51",
        "SR is S,0,0"
    });
}

TEST_F(EORITestByte, AddressDisplacementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "EORI.B #0x44, (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x51",
        "SR is S,0,0"
    });
}

TEST_F(EORITestByte, AddressIndexWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "EORI.B #0x44, (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).B is 0x51",
        "SR is S,0,0"
    });
}

TEST_F(EORITestByte, ShortWorks) {
    Given({
        "(0x00006000).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "EORI.B #0x44, (0x6000).W"
    });
    Then({
        "(0x00006000).B is 0x51",
        "SR is S,0,0"
    });
}

TEST_F(EORITestByte, LongWorks) {
    Given({
        "(0x00006000).B is 0x15",
        "SR is S,0,0"
    });
    When({
        "EORI.B #0x44, (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0x51",
        "SR is S,0,0"
    });
}

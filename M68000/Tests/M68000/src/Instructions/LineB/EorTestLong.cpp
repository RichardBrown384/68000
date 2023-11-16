#include "M68000/Fixtures/M68000Test.h"

class EORTestLong : public M68000Test {};

TEST_F(EORTestLong, DataRegisterDataRegisterWorks) {
    Given({
        "D1 is 0x55555555",
        "D2 is 0x5A4A1A0A",
        "SR is S,0,0"
    });
    When({
        "EOR.L D1, D2"
    });
    Then({
        "D1 is 0x55555555",
        "D2 is 0x0F1F4F5F",
        "SR is S,0,0"
    });
}

TEST_F(EORTestLong, DataRegisterDataRegisterFlagNWorks) {
    Given({
        "D1 is 0x55555555",
        "D2 is 0xAF0FAF0F",
        "SR is S,0,0"
    });
    When({
        "EOR.L D1, D2"
    });
    Then({
        "D1 is 0x55555555",
        "D2 is 0xFA5AFA5A",
        "SR is S,0,N"
    });
}

TEST_F(EORTestLong, DataRegisterDataRegisterFlagZWorks) {
    Given({
        "D1 is 0x04010309",
        "D2 is 0x04010309",
        "SR is S,0,0"
    });
    When({
        "EOR.L D1, D2"
    });
    Then({
        "D1 is 0x04010309",
        "D2 is 0x00000000",
        "SR is S,0,Z"
    });
}

TEST_F(EORTestLong, DataRegisterDataRegisterFlagXWorks) {
    Given({
        "D1 is 0x111111F3",
        "D2 is 0x010101F1",
        "SR is S,0,X"
    });
    When({
        "EOR.L D1, D2"
    });
    Then({
        "D1 is 0x111111F3",
        "D2 is 0x10101002",
        "SR is S,0,X"
    });
}

TEST_F(EORTestLong, DataRegisterDataRegisterFlagVCWorks) {
    Given({
        "D1 is 0x111111F3",
        "D2 is 0x010101F1",
        "SR is S,0,VC"
    });
    When({
        "EOR.L D1, D2"
    });
    Then({
        "D1 is 0x111111F3",
        "D2 is 0x10101002",
        "SR is S,0,0"
    });
}

TEST_F(EORTestLong, DataRegisterAddressIndirectWorks) {
    Given({
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x53AB7633",
        "SR is S,0,0"
    });
    When({
        "EOR.L D1, (A1)"
    });
    Then({
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x440824D2",
        "SR is S,0,0"
    });
}

TEST_F(EORTestLong, DataRegisterAddressIncrementWorks) {
    Given({
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x53AB7633",
        "SR is S,0,0"
    });
    When({
        "EOR.L D1, (A1)+"
    });
    Then({
        "D1 is 0x17A352E1",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x440824D2",
        "SR is S,0,0"
    });
}

TEST_F(EORTestLong, DataRegisterAddressDecrementWorks) {
    Given({
        "D1 is 0x17A352E1",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x53AB7633",
        "SR is S,0,0"
    });
    When({
        "EOR.L D1, -(A1)"
    });
    Then({
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x440824D2",
        "SR is S,0,0"
    });
}

TEST_F(EORTestLong, DataRegisterAddressIndexWorks) {
    Given({
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x53AB7633",
        "SR is S,0,0"
    });
    When({
        "EOR.L D1, (2, A1)"
    });
    Then({
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x440824D2",
        "SR is S,0,0"
    });
}

TEST_F(EORTestLong, DataRegisterAddressDisplacementWorks) {
    Given({
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x53AB7633",
        "SR is S,0,0"
    });
    When({
        "EOR.L D1, (2, A1, A2.L)"
    });
    Then({
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x440824D2",
        "SR is S,0,0"
    });
}

TEST_F(EORTestLong, DataRegisterAddressShortWorks) {
    Given({
        "D1 is 0x17A352E1",
        "(0x00004000).L is 0x53AB7633",
        "SR is S,0,0"
    });
    When({
        "EOR.L D1, (0x4000).W"
    });
    Then({
        "D1 is 0x17A352E1",
        "(0x00004000).L is 0x440824D2",
        "SR is S,0,0"
    });
}

TEST_F(EORTestLong, DataRegisterAddressLongWorks) {
    Given({
        "D1 is 0x17A352E1",
        "(0x00008000).L is 0x53AB7633",
        "SR is S,0,0"
    });
    When({
        "EOR.L D1, (0x8000).L"
    });
    Then({
        "D1 is 0x17A352E1",
        "(0x00008000).L is 0x440824D2",
        "SR is S,0,0"
    });
}
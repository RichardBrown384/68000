#include "M68000/Fixtures/M68000Test.h"

class ORTestLong : public M68000Test {};

TEST_F(ORTestLong, DataRegisterDataRegisterWorks) {
    Given({
        "D1 is 0x55555555",
        "D2 is 0x5A4A1A0A",
        "SR is S,0,0"
    });
    When({
        "OR.L D1, D2"
    });
    Then({
        "D1 is 0x55555555",
        "D2 is 0x5F5F5F5F",
        "SR is S,0,0"
    });
}

TEST_F(ORTestLong, DataRegisterDataRegisterFlagNWorks) {
    Given({
        "D1 is 0x55555555",
        "D2 is 0xAF0FAF0F",
        "SR is S,0,0"
    });
    When({
        "OR.L D1, D2"
    });
    Then({
        "D1 is 0x55555555",
        "D2 is 0xFF5FFF5F",
        "SR is S,0,N"
    });
}

TEST_F(ORTestLong, DataRegisterDataRegisterFlagZWorks) {
    Given({
        "D1 is 0x00000000",
        "D2 is 0x00000000",
        "SR is S,0,0"
    });
    When({
        "OR.L D1, D2"
    });
    Then({
        "D1 is 0x00000000",
        "D2 is 0x00000000",
        "SR is S,0,Z"
    });
}

TEST_F(ORTestLong, DataRegisterDataRegisterFlagXWorks) {
    Given({
        "D1 is 0x111111F3",
        "D2 is 0x010101F1",
        "SR is S,0,X"
    });
    When({
        "OR.L D1, D2"
    });
    Then({
        "D1 is 0x111111F3",
        "D2 is 0x111111F3",
        "SR is S,0,X"
    });
}

TEST_F(ORTestLong, DataRegisterDataRegisterFlagVCWorks) {
    Given({
        "D1 is 0x111111F3",
        "D2 is 0x010101F1",
        "SR is S,0,VC"
    });
    When({
        "OR.L D1, D2"
    });
    Then({
        "D1 is 0x111111F3",
        "D2 is 0x111111F3",
        "SR is S,0,0"
    });
}


TEST_F(ORTestLong, AddressIndirectDataRegisterWorks) {
    Given({
        "D1 is 0x53AB7633",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x17A352E1",
        "SR is S,0,0"
    });
    When({
        "OR.L (A1), D1"
    });
    Then({
        "D1 is 0x57AB76F3",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x17A352E1",
        "SR is S,0,0"
    });
}

TEST_F(ORTestLong, AddressIncrementDataRegisterWorks) {
    Given({
        "D1 is 0x53AB7633",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x17A352E1",
        "SR is S,0,0"
    });
    When({
        "OR.L (A1)+, D1"
    });
    Then({
        "D1 is 0x57AB76F3",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x17A352E1",
        "SR is S,0,0"
    });
}

TEST_F(ORTestLong, AddressDecrementDataRegisterWorks) {
    Given({
        "D1 is 0x53AB7633",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x17A352E1",
        "SR is S,0,0"
    });
    When({
        "OR.L -(A1), D1"
    });
    Then({
        "D1 is 0x57AB76F3",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x17A352E1",
        "SR is S,0,0"
    });
}

TEST_F(ORTestLong, AddressDisplacementDataRegisterWorks) {
    Given({
        "D1 is 0x53AB7633",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x17A352E1",
        "SR is S,0,0"
    });
    When({
        "OR.L (2, A1), D1"
    });
    Then({
        "D1 is 0x57AB76F3",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x17A352E1",
        "SR is S,0,0"
    });
}

TEST_F(ORTestLong, AddressIndexDataRegisterWorks) {
    Given({
        "D1 is 0x53AB7633",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x17A352E1",
        "SR is S,0,0"
    });
    When({
        "OR.L (2, A1, A2.L), D1"
    });
    Then({
        "D1 is 0x57AB76F3",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x17A352E1",
        "SR is S,0,0"
    });
}

TEST_F(ORTestLong, ShortDataRegisterWorks) {
    Given({
        "D1 is 0x53AB7633",
        "(0x00004000).L is 0x17A352E1",
        "SR is S,0,0"
    });
    When({
        "OR.L (0x4000).W, D1"
    });
    Then({
        "D1 is 0x57AB76F3",
        "(0x00004000).L is 0x17A352E1",
        "SR is S,0,0"
    });
}

TEST_F(ORTestLong, LongDataRegisterWorks) {
    Given({
        "D1 is 0x53AB7633",
        "(0x00008000).L is 0x17A352E1",
        "SR is S,0,0"
    });
    When({
        "OR.L (0x8000).L, D1"
    });
    Then({
        "D1 is 0x57AB76F3",
        "(0x00008000).L is 0x17A352E1",
        "SR is S,0,0"
    });
}

TEST_F(ORTestLong, PCDisplacementDataRegisterWorks) {
    Given({
        "D1 is 0x53AB7633",
        "(0x00001060).L is 0x17A352E1",
        "SR is S,0,0"
    });
    When({
        "OR.L (0x5E, PC), D1"
    });
    Then({
        "D1 is 0x57AB76F3",
        "(0x00001060).L is 0x17A352E1",
        "SR is S,0,0"
    });
}

TEST_F(ORTestLong, PCIndexDataRegisterWorks) {
    Given({
        "D1 is 0x53AB7633",
        "A1 is 0x00000010",
        "(0x00001070).L is 0x17A352E1",
        "SR is S,0,0"
    });
    When({
        "OR.L (0x5E, PC, A1.L), D1"
    });
    Then({
        "D1 is 0x57AB76F3",
        "A1 is 0x00000010",
        "(0x00001070).L is 0x17A352E1",
        "SR is S,0,0"
    });
}

TEST_F(ORTestLong, ImmediateDataRegisterWorks) {
    Given({
        "D1 is 0x53AB7633",
        "SR is S,0,0"
    });
    When({
        "OR.L #0x17A352E1, D1"
    });
    Then({
        "D1 is 0x57AB76F3",
        "SR is S,0,0"
    });
}

TEST_F(ORTestLong, DataRegisterAddressIndirectWorks) {
    Given({
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x53AB7633",
        "SR is S,0,0"
    });
    When({
        "OR.L D1, (A1)"
    });
    Then({
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x57AB76F3",
        "SR is S,0,0"
    });
}

TEST_F(ORTestLong, DataRegisterAddressIncrementWorks) {
    Given({
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x53AB7633",
        "SR is S,0,0"
    });
    When({
        "OR.L D1, (A1)+"
    });
    Then({
        "D1 is 0x17A352E1",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x57AB76F3",
        "SR is S,0,0"
    });
}

TEST_F(ORTestLong, DataRegisterAddressDecrementWorks) {
    Given({
        "D1 is 0x17A352E1",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x53AB7633",
        "SR is S,0,0"
    });
    When({
        "OR.L D1, -(A1)"
    });
    Then({
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x57AB76F3",
        "SR is S,0,0"
    });
}

TEST_F(ORTestLong, DataRegisterAddressIndexWorks) {
    Given({
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x53AB7633",
        "SR is S,0,0"
    });
    When({
        "OR.L D1, (2, A1)"
    });
    Then({
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x57AB76F3",
        "SR is S,0,0"
    });
}

TEST_F(ORTestLong, DataRegisterAddressDisplacementWorks) {
    Given({
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x53AB7633",
        "SR is S,0,0"
    });
    When({
        "OR.L D1, (2, A1, A2.L)"
    });
    Then({
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x57AB76F3",
        "SR is S,0,0"
    });
}

TEST_F(ORTestLong, DataRegisterAddressShortWorks) {
    Given({
        "D1 is 0x17A352E1",
        "(0x00004000).L is 0x53AB7633",
        "SR is S,0,0"
    });
    When({
        "OR.L D1, (0x4000).W"
    });
    Then({
        "D1 is 0x17A352E1",
        "(0x00004000).L is 0x57AB76F3",
        "SR is S,0,0"
    });
}

TEST_F(ORTestLong, DataRegisterAddressLongWorks) {
    Given({
        "D1 is 0x17A352E1",
        "(0x00008000).L is 0x53AB7633",
        "SR is S,0,0"
    });
    When({
        "OR.L D1, (0x8000).L"
    });
    Then({
        "D1 is 0x17A352E1",
        "(0x00008000).L is 0x57AB76F3",
        "SR is S,0,0"
    });
}
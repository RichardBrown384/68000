#include "M68000/Fixtures/M68000Test.h"

class ORTestLong : public M68000Test {};

TEST_F(ORTestLong, DataRegisterDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x55555555",
        "D2 is 0x5A4A1A0A",
    });
    When({
        "OR.L D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x55555555",
        "D2 is 0x5F5F5F5F",
    });
}

TEST_F(ORTestLong, DataRegisterDataRegisterFlagNWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x55555555",
        "D2 is 0xAF0FAF0F",
    });
    When({
        "OR.L D1, D2"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x55555555",
        "D2 is 0xFF5FFF5F",
    });
}

TEST_F(ORTestLong, DataRegisterDataRegisterFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000000",
        "D2 is 0x00000000",
    });
    When({
        "OR.L D1, D2"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x00000000",
        "D2 is 0x00000000",
    });
}

TEST_F(ORTestLong, DataRegisterDataRegisterFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0x111111F3",
        "D2 is 0x010101F1",
    });
    When({
        "OR.L D1, D2"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x111111F3",
        "D2 is 0x111111F3",
    });
}

TEST_F(ORTestLong, DataRegisterDataRegisterFlagVCWorks) {
    Given({
        "SR is S,0,VC",
        "PC is 0x1000",
        "D1 is 0x111111F3",
        "D2 is 0x010101F1",
    });
    When({
        "OR.L D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x111111F3",
        "D2 is 0x111111F3",
    });
}


TEST_F(ORTestLong, AddressIndirectDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x53AB7633",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x17A352E1",
    });
    When({
        "OR.L (A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x57AB76F3",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x17A352E1",
    });
}

TEST_F(ORTestLong, AddressIncrementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x53AB7633",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x17A352E1",
    });
    When({
        "OR.L (A1)+, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x57AB76F3",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x17A352E1",
    });
}

TEST_F(ORTestLong, AddressDecrementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x53AB7633",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x17A352E1",
    });
    When({
        "OR.L -(A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 16",
        "D1 is 0x57AB76F3",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x17A352E1",
    });
}

TEST_F(ORTestLong, AddressDisplacementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x53AB7633",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x17A352E1",
    });
    When({
        "OR.L (2, A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "D1 is 0x57AB76F3",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x17A352E1",
    });
}

TEST_F(ORTestLong, AddressIndexDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x53AB7633",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x17A352E1",
    });
    When({
        "OR.L (2, A1, A2.L), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 20",
        "D1 is 0x57AB76F3",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x17A352E1",
    });
}

TEST_F(ORTestLong, ShortDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x53AB7633",
        "(0x00004000).L is 0x17A352E1",
    });
    When({
        "OR.L (0x4000).W, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "D1 is 0x57AB76F3",
        "(0x00004000).L is 0x17A352E1",
    });
}

TEST_F(ORTestLong, LongDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x53AB7633",
        "(0x00008000).L is 0x17A352E1",
    });
    When({
        "OR.L (0x8000).L, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 22",
        "D1 is 0x57AB76F3",
        "(0x00008000).L is 0x17A352E1",
    });
}

TEST_F(ORTestLong, PCDisplacementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x53AB7633",
        "(0x00001060).L is 0x17A352E1",
    });
    When({
        "OR.L (0x5E, PC), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "D1 is 0x57AB76F3",
        "(0x00001060).L is 0x17A352E1",
    });
}

TEST_F(ORTestLong, PCIndexDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x53AB7633",
        "A1 is 0x00000010",
        "(0x00001070).L is 0x17A352E1",
    });
    When({
        "OR.L (0x5E, PC, A1.L), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 20",
        "D1 is 0x57AB76F3",
        "A1 is 0x00000010",
        "(0x00001070).L is 0x17A352E1",
    });
}

TEST_F(ORTestLong, ImmediateDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x53AB7633",
    });
    When({
        "OR.L #0x17A352E1, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 16",
        "D1 is 0x57AB76F3",
    });
}

TEST_F(ORTestLong, DataRegisterAddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x53AB7633",
    });
    When({
        "OR.L D1, (A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 20",
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x57AB76F3",
    });
}

TEST_F(ORTestLong, DataRegisterAddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x53AB7633",
    });
    When({
        "OR.L D1, (A1)+"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 20",
        "D1 is 0x17A352E1",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x57AB76F3",
    });
}

TEST_F(ORTestLong, DataRegisterAddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x17A352E1",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x53AB7633",
    });
    When({
        "OR.L D1, -(A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 22",
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x57AB76F3",
    });
}

TEST_F(ORTestLong, DataRegisterAddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x53AB7633",
    });
    When({
        "OR.L D1, (2, A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 24",
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x57AB76F3",
    });
}

TEST_F(ORTestLong, DataRegisterAddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x53AB7633",
    });
    When({
        "OR.L D1, (2, A1, A2.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 26",
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x57AB76F3",
    });
}

TEST_F(ORTestLong, DataRegisterAddressShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x17A352E1",
        "(0x00004000).L is 0x53AB7633",
    });
    When({
        "OR.L D1, (0x4000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 24",
        "D1 is 0x17A352E1",
        "(0x00004000).L is 0x57AB76F3",
    });
}

TEST_F(ORTestLong, DataRegisterAddressLongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x17A352E1",
        "(0x00008000).L is 0x53AB7633",
    });
    When({
        "OR.L D1, (0x8000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 28",
        "D1 is 0x17A352E1",
        "(0x00008000).L is 0x57AB76F3",
    });
}

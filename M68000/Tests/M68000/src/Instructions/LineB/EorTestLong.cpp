#include "M68000/Fixtures/M68000Test.h"

class EORTestLong : public M68000Test {};

TEST_F(EORTestLong, DataRegisterDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x55555555",
        "D2 is 0x5A4A1A0A",
    });
    When({
        "EOR.L D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x55555555",
        "D2 is 0x0F1F4F5F",
    });
}

TEST_F(EORTestLong, DataRegisterDataRegisterFlagNWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x55555555",
        "D2 is 0xAF0FAF0F",
    });
    When({
        "EOR.L D1, D2"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x55555555",
        "D2 is 0xFA5AFA5A",
    });
}

TEST_F(EORTestLong, DataRegisterDataRegisterFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x04010309",
        "D2 is 0x04010309",
    });
    When({
        "EOR.L D1, D2"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x04010309",
        "D2 is 0x00000000",
    });
}

TEST_F(EORTestLong, DataRegisterDataRegisterFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0x111111F3",
        "D2 is 0x010101F1",
    });
    When({
        "EOR.L D1, D2"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x111111F3",
        "D2 is 0x10101002",
    });
}

TEST_F(EORTestLong, DataRegisterDataRegisterFlagVCWorks) {
    Given({
        "SR is S,0,VC",
        "PC is 0x1000",
        "D1 is 0x111111F3",
        "D2 is 0x010101F1",
    });
    When({
        "EOR.L D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x111111F3",
        "D2 is 0x10101002",
    });
}

TEST_F(EORTestLong, DataRegisterAddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x53AB7633",
    });
    When({
        "EOR.L D1, (A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 20",
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x440824D2",
    });
}

TEST_F(EORTestLong, DataRegisterAddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x53AB7633",
    });
    When({
        "EOR.L D1, (A1)+"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 20",
        "D1 is 0x17A352E1",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x440824D2",
    });
}

TEST_F(EORTestLong, DataRegisterAddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x17A352E1",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x53AB7633",
    });
    When({
        "EOR.L D1, -(A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 22",
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x440824D2",
    });
}

TEST_F(EORTestLong, DataRegisterAddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x53AB7633",
    });
    When({
        "EOR.L D1, (2, A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 24",
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x440824D2",
    });
}

TEST_F(EORTestLong, DataRegisterAddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x53AB7633",
    });
    When({
        "EOR.L D1, (2, A1, A2.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 26",
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x440824D2",
    });
}

TEST_F(EORTestLong, DataRegisterAddressShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x17A352E1",
        "(0x00004000).L is 0x53AB7633",
    });
    When({
        "EOR.L D1, (0x4000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 24",
        "D1 is 0x17A352E1",
        "(0x00004000).L is 0x440824D2",
    });
}

TEST_F(EORTestLong, DataRegisterAddressLongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x17A352E1",
        "(0x00008000).L is 0x53AB7633",
    });
    When({
        "EOR.L D1, (0x8000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 28",
        "D1 is 0x17A352E1",
        "(0x00008000).L is 0x440824D2",
    });
}

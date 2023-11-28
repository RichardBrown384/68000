#include "M68000/Fixtures/M68000Test.h"

class ANDTestLong : public M68000Test {};

TEST_F(ANDTestLong, DataRegisterDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x20110101",
        "D2 is 0xE3010101",
    });
    When({
        "AND.L D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x20110101",
        "D2 is 0x20010101",
    });
}

TEST_F(ANDTestLong, DataRegisterDataRegisterFlagNWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x81010101",
        "D2 is 0x80010001",
    });
    When({
        "AND.L D1, D2"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x81010101",
        "D2 is 0x80010001",
    });
}

TEST_F(ANDTestLong, DataRegisterDataRegisterFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xAAAAAAAA",
        "D2 is 0x55555555",
    });
    When({
        "AND.L D1, D2"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0xAAAAAAAA",
        "D2 is 0x00000000",
    });
}

TEST_F(ANDTestLong, DataRegisterDataRegisterFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0x010101F1",
        "D2 is 0x111111F3",
    });
    When({
        "AND.L D1, D2"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x010101F1",
        "D2 is 0x010101F1",
    });
}

TEST_F(ANDTestLong, DataRegisterDataRegisterFlagVCWorks) {
    Given({
        "SR is S,0,VC",
        "PC is 0x1000",
        "D1 is 0x010101F1",
        "D2 is 0x111111F3",
    });
    When({
        "AND.L D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x010101F1",
        "D2 is 0x010101F1",
    });
}


TEST_F(ANDTestLong, AddressIndirectDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xD3AB7633",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x17A352E1",
    });
    When({
        "AND.L (A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x13A35221",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x17A352E1",
    });
}

TEST_F(ANDTestLong, AddressIncrementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xD3AB7633",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x17A352E1",
    });
    When({
        "AND.L (A1)+, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x13A35221",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x17A352E1",
    });
}

TEST_F(ANDTestLong, AddressDecrementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xD3AB7633",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x17A352E1",
    });
    When({
        "AND.L -(A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 16",
        "D1 is 0x13A35221",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x17A352E1",
    });
}

TEST_F(ANDTestLong, AddressDisplacementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xD3AB7633",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x17A352E1",
    });
    When({
        "AND.L (2, A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "D1 is 0x13A35221",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x17A352E1",
    });
}

TEST_F(ANDTestLong, AddressIndexDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xD3AB7633",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x17A352E1",
    });
    When({
        "AND.L (2, A1, A2.L), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 20",
        "D1 is 0x13A35221",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x17A352E1",
    });
}

TEST_F(ANDTestLong, ShortDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xD3AB7633",
        "(0x00004000).L is 0x17A352E1",
    });
    When({
        "AND.L (0x4000).W, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "D1 is 0x13A35221",
        "(0x00004000).L is 0x17A352E1",
    });
}

TEST_F(ANDTestLong, LongDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xD3AB7633",
        "(0x00008000).L is 0x17A352E1",
    });
    When({
        "AND.L (0x8000).L, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 22",
        "D1 is 0x13A35221",
        "(0x00008000).L is 0x17A352E1",
    });
}

TEST_F(ANDTestLong, PCDisplacementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xD3AB7633",
        "(0x00001060).L is 0x17A352E1",
    });
    When({
        "AND.L (0x5E, PC), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "D1 is 0x13A35221",
        "(0x00001060).L is 0x17A352E1",
    });
}

TEST_F(ANDTestLong, PCIndexDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xD3AB7633",
        "A1 is 0x00000010",
        "(0x00001070).L is 0x17A352E1",
    });
    When({
        "AND.L (0x5E, PC, A1.L), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 20",
        "D1 is 0x13A35221",
        "A1 is 0x00000010",
        "(0x00001070).L is 0x17A352E1",
    });
}

TEST_F(ANDTestLong, ImmediateDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xD3AB7633",
    });
    When({
        "AND.L #0x17A352E1, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 16",
        "D1 is 0x13A35221",
    });
}

TEST_F(ANDTestLong, DataRegisterAddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008000).L is 0xD3AB7633",
    });
    When({
        "AND.L D1, (A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 20",
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x13A35221",
    });
}

TEST_F(ANDTestLong, DataRegisterAddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008000).L is 0xD3AB7633",
    });
    When({
        "AND.L D1, (A1)+"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 20",
        "D1 is 0x17A352E1",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x13A35221",
    });
}

TEST_F(ANDTestLong, DataRegisterAddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x17A352E1",
        "A1 is 0x00008004",
        "(0x00008000).L is 0xD3AB7633",
    });
    When({
        "AND.L D1, -(A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 22",
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x13A35221",
    });
}

TEST_F(ANDTestLong, DataRegisterAddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008002).L is 0xD3AB7633",
    });
    When({
        "AND.L D1, (2, A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 24",
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x13A35221",
    });
}

TEST_F(ANDTestLong, DataRegisterAddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0xD3AB7633",
    });
    When({
        "AND.L D1, (2, A1, A2.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 26",
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x13A35221",
    });
}

TEST_F(ANDTestLong, DataRegisterAddressShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x17A352E1",
        "(0x00004000).L is 0xD3AB7633",
    });
    When({
        "AND.L D1, (0x4000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 24",
        "D1 is 0x17A352E1",
        "(0x00004000).L is 0x13A35221",
    });
}

TEST_F(ANDTestLong, DataRegisterAddressLongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x17A352E1",
        "(0x00008000).L is 0xD3AB7633",
    });
    When({
        "AND.L D1, (0x8000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 28",
        "D1 is 0x17A352E1",
        "(0x00008000).L is 0x13A35221",
    });
}

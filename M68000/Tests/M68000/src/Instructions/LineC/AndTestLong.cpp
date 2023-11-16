#include "M68000/Fixtures/M68000Test.h"

class ANDTestLong : public M68000Test {};

TEST_F(ANDTestLong, DataRegisterDataRegisterWorks) {
    Given({
        "D1 is 0x20110101",
        "D2 is 0xE3010101",
        "SR is S,0,0"
    });
    When({
        "AND.L D1, D2"
    });
    Then({
        "D1 is 0x20110101",
        "D2 is 0x20010101",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestLong, DataRegisterDataRegisterFlagNWorks) {
    Given({
        "D1 is 0x81010101",
        "D2 is 0x80010001",
        "SR is S,0,0"
    });
    When({
        "AND.L D1, D2"
    });
    Then({
        "D1 is 0x81010101",
        "D2 is 0x80010001",
        "SR is S,0,N"
    });
}

TEST_F(ANDTestLong, DataRegisterDataRegisterFlagZWorks) {
    Given({
        "D1 is 0xAAAAAAAA",
        "D2 is 0x55555555",
        "SR is S,0,0"
    });
    When({
        "AND.L D1, D2"
    });
    Then({
        "D1 is 0xAAAAAAAA",
        "D2 is 0x00000000",
        "SR is S,0,Z"
    });
}

TEST_F(ANDTestLong, DataRegisterDataRegisterFlagXWorks) {
    Given({
        "D1 is 0x010101F1",
        "D2 is 0x111111F3",
        "SR is S,0,X"
    });
    When({
        "AND.L D1, D2"
    });
    Then({
        "D1 is 0x010101F1",
        "D2 is 0x010101F1",
        "SR is S,0,X"
    });
}

TEST_F(ANDTestLong, DataRegisterDataRegisterFlagVCWorks) {
    Given({
        "D1 is 0x010101F1",
        "D2 is 0x111111F3",
        "SR is S,0,VC"
    });
    When({
        "AND.L D1, D2"
    });
    Then({
        "D1 is 0x010101F1",
        "D2 is 0x010101F1",
        "SR is S,0,0"
    });
}


TEST_F(ANDTestLong, AddressIndirectDataRegisterWorks) {
    Given({
        "D1 is 0xD3AB7633",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x17A352E1",
        "SR is S,0,0"
    });
    When({
        "AND.L (A1), D1"
    });
    Then({
        "D1 is 0x13A35221",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x17A352E1",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestLong, AddressIncrementDataRegisterWorks) {
    Given({
        "D1 is 0xD3AB7633",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x17A352E1",
        "SR is S,0,0"
    });
    When({
        "AND.L (A1)+, D1"
    });
    Then({
        "D1 is 0x13A35221",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x17A352E1",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestLong, AddressDecrementDataRegisterWorks) {
    Given({
        "D1 is 0xD3AB7633",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x17A352E1",
        "SR is S,0,0"
    });
    When({
        "AND.L -(A1), D1"
    });
    Then({
        "D1 is 0x13A35221",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x17A352E1",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestLong, AddressDisplacementDataRegisterWorks) {
    Given({
        "D1 is 0xD3AB7633",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x17A352E1",
        "SR is S,0,0"
    });
    When({
        "AND.L (2, A1), D1"
    });
    Then({
        "D1 is 0x13A35221",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x17A352E1",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestLong, AddressIndexDataRegisterWorks) {
    Given({
        "D1 is 0xD3AB7633",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x17A352E1",
        "SR is S,0,0"
    });
    When({
        "AND.L (2, A1, A2.L), D1"
    });
    Then({
        "D1 is 0x13A35221",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x17A352E1",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestLong, ShortDataRegisterWorks) {
    Given({
        "D1 is 0xD3AB7633",
        "(0x00004000).L is 0x17A352E1",
        "SR is S,0,0"
    });
    When({
        "AND.L (0x4000).W, D1"
    });
    Then({
        "D1 is 0x13A35221",
        "(0x00004000).L is 0x17A352E1",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestLong, LongDataRegisterWorks) {
    Given({
        "D1 is 0xD3AB7633",
        "(0x00008000).L is 0x17A352E1",
        "SR is S,0,0"
    });
    When({
        "AND.L (0x8000).L, D1"
    });
    Then({
        "D1 is 0x13A35221",
        "(0x00008000).L is 0x17A352E1",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestLong, PCDisplacementDataRegisterWorks) {
    Given({
        "D1 is 0xD3AB7633",
        "(0x00001060).L is 0x17A352E1",
        "SR is S,0,0"
    });
    When({
        "AND.L (0x5E, PC), D1"
    });
    Then({
        "D1 is 0x13A35221",
        "(0x00001060).L is 0x17A352E1",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestLong, PCIndexDataRegisterWorks) {
    Given({
        "D1 is 0xD3AB7633",
        "A1 is 0x00000010",
        "(0x00001070).L is 0x17A352E1",
        "SR is S,0,0"
    });
    When({
        "AND.L (0x5E, PC, A1.L), D1"
    });
    Then({
        "D1 is 0x13A35221",
        "A1 is 0x00000010",
        "(0x00001070).L is 0x17A352E1",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestLong, ImmediateDataRegisterWorks) {
    Given({
        "D1 is 0xD3AB7633",
        "SR is S,0,0"
    });
    When({
        "AND.L #0x17A352E1, D1"
    });
    Then({
        "D1 is 0x13A35221",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestLong, DataRegisterAddressIndirectWorks) {
    Given({
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008000).L is 0xD3AB7633",
        "SR is S,0,0"
    });
    When({
        "AND.L D1, (A1)"
    });
    Then({
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x13A35221",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestLong, DataRegisterAddressIncrementWorks) {
    Given({
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008000).L is 0xD3AB7633",
        "SR is S,0,0"
    });
    When({
        "AND.L D1, (A1)+"
    });
    Then({
        "D1 is 0x17A352E1",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x13A35221",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestLong, DataRegisterAddressDecrementWorks) {
    Given({
        "D1 is 0x17A352E1",
        "A1 is 0x00008004",
        "(0x00008000).L is 0xD3AB7633",
        "SR is S,0,0"
    });
    When({
        "AND.L D1, -(A1)"
    });
    Then({
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x13A35221",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestLong, DataRegisterAddressIndexWorks) {
    Given({
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008002).L is 0xD3AB7633",
        "SR is S,0,0"
    });
    When({
        "AND.L D1, (2, A1)"
    });
    Then({
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x13A35221",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestLong, DataRegisterAddressDisplacementWorks) {
    Given({
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0xD3AB7633",
        "SR is S,0,0"
    });
    When({
        "AND.L D1, (2, A1, A2.L)"
    });
    Then({
        "D1 is 0x17A352E1",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x13A35221",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestLong, DataRegisterAddressShortWorks) {
    Given({
        "D1 is 0x17A352E1",
        "(0x00004000).L is 0xD3AB7633",
        "SR is S,0,0"
    });
    When({
        "AND.L D1, (0x4000).W"
    });
    Then({
        "D1 is 0x17A352E1",
        "(0x00004000).L is 0x13A35221",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestLong, DataRegisterAddressLongWorks) {
    Given({
        "D1 is 0x17A352E1",
        "(0x00008000).L is 0xD3AB7633",
        "SR is S,0,0"
    });
    When({
        "AND.L D1, (0x8000).L"
    });
    Then({
        "D1 is 0x17A352E1",
        "(0x00008000).L is 0x13A35221",
        "SR is S,0,0"
    });
}
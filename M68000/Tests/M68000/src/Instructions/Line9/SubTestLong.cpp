#include "M68000/Fixtures/M68000Test.h"

class SUBTestLong : public M68000Test {};

TEST_F(SUBTestLong, DataRegisterDataRegisterWorks) {
    Given({
        "D1 is 0x20010101",
        "D2 is 0xE3010101",
        "SR is S,0,0"
    });
    When({
        "SUB.L D1, D2"
    });
    Then({
        "D1 is 0x20010101",
        "D2 is 0xC3000000",
        "SR is S,0,N"
    });
}

TEST_F(SUBTestLong, DataRegisterDataRegisterFlagNVWorks) {
    Given({
        "D1 is 0x80010001",
        "D2 is 0x32010001",
        "SR is S,0,0"
    });
    When({
        "SUB.L D1, D2"
    });
    Then({
        "D1 is 0x80010001",
        "D2 is 0xB2000000",
        "SR is S,0,XNVC"
    });
}

TEST_F(SUBTestLong, AddressRegisterDataRegisterWorks) {
    Given({
        "A2 is 0x07050301",
        "D2 is 0x09080706",
        "SR is S,0,0"
    });
    When({
        "SUB.L A2, D2"
    });
    Then({
        "A2 is 0x07050301",
        "D2 is 0x02030405",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestLong, AddressIndirectDataRegisterWorks) {
    Given({
        "D1 is 0x09080706",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x07050301",
        "SR is S,0,0"
    });
    When({
        "SUB.L (A1), D1"
    });
    Then({
        "D1 is 0x02030405",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x07050301",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestLong, AddressIncrementDataRegisterWorks) {
    Given({
        "D1 is 0x09080706",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x07050301",
        "SR is S,0,0"
    });
    When({
        "SUB.L (A1)+, D1"
    });
    Then({
        "D1 is 0x02030405",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x07050301",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestLong, AddressDecrementDataRegisterWorks) {
    Given({
        "D1 is 0x09080706",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x07050301",
        "SR is S,0,0"
    });
    When({
        "SUB.L -(A1), D1"
    });
    Then({
        "D1 is 0x02030405",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x07050301",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestLong, AddressDisplacementDataRegisterWorks) {
    Given({
        "D1 is 0x09080706",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x07050301",
        "SR is S,0,0"
    });
    When({
        "SUB.L (2, A1), D1"
    });
    Then({
        "D1 is 0x02030405",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x07050301",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestLong, AddressIndexDataRegisterWorks) {
    Given({
        "D1 is 0x09080706",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x07050301",
        "SR is S,0,0"
    });
    When({
        "SUB.L (2, A1, A2.L), D1"
    });
    Then({
        "D1 is 0x02030405",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x07050301",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestLong, ShortDataRegisterWorks) {
    Given({
        "D1 is 0x09080706",
        "(0x00004000).L is 0x07050301",
        "SR is S,0,0"
    });
    When({
        "SUB.L (0x4000).W, D1"
    });
    Then({
        "D1 is 0x02030405",
        "(0x00004000).L is 0x07050301",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestLong, LongDataRegisterWorks) {
    Given({
        "D1 is 0x09080706",
        "(0x00008000).L is 0x07050301",
        "SR is S,0,0"
    });
    When({
        "SUB.L (0x8000).L, D1"
    });
    Then({
        "D1 is 0x02030405",
        "(0x00008000).L is 0x07050301",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestLong, PCDisplacementDataRegisterWorks) {
    Given({
        "D1 is 0x09080706",
        "(0x00001060).L is 0x07050301",
        "SR is S,0,0"
    });
    When({
        "SUB.L (0x5E, PC), D1"
    });
    Then({
        "D1 is 0x02030405",
        "(0x00001060).L is 0x07050301",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestLong, PCIndexDataRegisterWorks) {
    Given({
        "D1 is 0x09080706",
        "A1 is 0x00000010",
        "(0x00001070).L is 0x07050301",
        "SR is S,0,0"
    });
    When({
        "SUB.L (0x5E, PC, A1.L), D1"
    });
    Then({
        "D1 is 0x02030405",
        "A1 is 0x00000010",
        "(0x00001070).L is 0x07050301",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestLong, ImmediateDataRegisterWorks) {
    Given({
        "D1 is 0x09080706",
        "SR is S,0,0"
    });
    When({
        "SUB.L #0x07050301, D1"
    });
    Then({
        "D1 is 0x02030405",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestLong, DataRegisterAddressIndirectWorks) {
    Given({
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x09080706",
        "SR is S,0,0"
    });
    When({
        "SUB.L D1, (A1)"
    });
    Then({
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x02030405",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestLong, DataRegisterAddressIncrementWorks) {
    Given({
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x09080706",
        "SR is S,0,0"
    });
    When({
        "SUB.L D1, (A1)+"
    });
    Then({
        "D1 is 0x07050301",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x02030405",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestLong, DataRegisterAddressDecrementWorks) {
    Given({
        "D1 is 0x07050301",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x09080706",
        "SR is S,0,0"
    });
    When({
        "SUB.L D1, -(A1)"
    });
    Then({
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x02030405",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestLong, DataRegisterAddressIndexWorks) {
    Given({
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x09080706",
        "SR is S,0,0"
    });
    When({
        "SUB.L D1, (2, A1)"
    });
    Then({
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x02030405",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestLong, DataRegisterAddressDisplacementWorks) {
    Given({
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x09080706",
        "SR is S,0,0"
    });
    When({
        "SUB.L D1, (2, A1, A2.L)"
    });
    Then({
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x02030405",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestLong, DataRegisterAddressShortWorks) {
    Given({
        "D1 is 0x07050301",
        "(0x00004000).L is 0x09080706",
        "SR is S,0,0"
    });
    When({
        "SUB.L D1, (0x4000).W"
    });
    Then({
        "D1 is 0x07050301",
        "(0x00004000).L is 0x02030405",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestLong, DataRegisterAddressLongWorks) {
    Given({
        "D1 is 0x07050301",
        "(0x00008000).L is 0x09080706",
        "SR is S,0,0"
    });
    When({
        "SUB.L D1, (0x8000).L"
    });
    Then({
        "D1 is 0x07050301",
        "(0x00008000).L is 0x02030405",
        "SR is S,0,0"
    });
}
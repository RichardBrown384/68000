#include "M68000/Fixtures/M68000Test.h"

class SUBTestLong : public M68000Test {};

TEST_F(SUBTestLong, DataRegisterDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x20010101",
        "D2 is 0xE3010101",
    });
    When({
        "SUB.L D1, D2"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x20010101",
        "D2 is 0xC3000000",
    });
}

TEST_F(SUBTestLong, DataRegisterDataRegisterFlagNVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x80010001",
        "D2 is 0x32010001",
    });
    When({
        "SUB.L D1, D2"
    });
    Then({
        "SR is S,0,XNVC",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x80010001",
        "D2 is 0xB2000000",
    });
}

TEST_F(SUBTestLong, AddressRegisterDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D2 is 0x09080706",
        "A2 is 0x07050301",
    });
    When({
        "SUB.L A2, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D2 is 0x02030405",
        "A2 is 0x07050301",
    });
}

TEST_F(SUBTestLong, AddressIndirectDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x09080706",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x07050301",
    });
    When({
        "SUB.L (A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x02030405",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x07050301",
    });
}

TEST_F(SUBTestLong, AddressIncrementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x09080706",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x07050301",
    });
    When({
        "SUB.L (A1)+, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x02030405",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x07050301",
    });
}

TEST_F(SUBTestLong, AddressDecrementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x09080706",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x07050301",
    });
    When({
        "SUB.L -(A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 16",
        "D1 is 0x02030405",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x07050301",
    });
}

TEST_F(SUBTestLong, AddressDisplacementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x09080706",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x07050301",
    });
    When({
        "SUB.L (2, A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "D1 is 0x02030405",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x07050301",
    });
}

TEST_F(SUBTestLong, AddressIndexDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x09080706",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x07050301",
    });
    When({
        "SUB.L (2, A1, A2.L), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 20",
        "D1 is 0x02030405",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x07050301",
    });
}

TEST_F(SUBTestLong, ShortDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x09080706",
        "(0x00004000).L is 0x07050301",
    });
    When({
        "SUB.L (0x4000).W, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "D1 is 0x02030405",
        "(0x00004000).L is 0x07050301",
    });
}

TEST_F(SUBTestLong, LongDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x09080706",
        "(0x00008000).L is 0x07050301",
    });
    When({
        "SUB.L (0x8000).L, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 22",
        "D1 is 0x02030405",
        "(0x00008000).L is 0x07050301",
    });
}

TEST_F(SUBTestLong, PCDisplacementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x09080706",
        "(0x00001060).L is 0x07050301",
    });
    When({
        "SUB.L (0x5E, PC), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "D1 is 0x02030405",
        "(0x00001060).L is 0x07050301",
    });
}

TEST_F(SUBTestLong, PCIndexDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x09080706",
        "A1 is 0x00000010",
        "(0x00001070).L is 0x07050301",
    });
    When({
        "SUB.L (0x5E, PC, A1.L), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 20",
        "D1 is 0x02030405",
        "A1 is 0x00000010",
        "(0x00001070).L is 0x07050301",
    });
}

TEST_F(SUBTestLong, ImmediateDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x09080706",
    });
    When({
        "SUB.L #0x07050301, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 16",
        "D1 is 0x02030405",
    });
}

TEST_F(SUBTestLong, DataRegisterAddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x09080706",
    });
    When({
        "SUB.L D1, (A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 20",
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x02030405",
    });
}

TEST_F(SUBTestLong, DataRegisterAddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x09080706",
    });
    When({
        "SUB.L D1, (A1)+"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 20",
        "D1 is 0x07050301",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x02030405",
    });
}

TEST_F(SUBTestLong, DataRegisterAddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x07050301",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x09080706",
    });
    When({
        "SUB.L D1, -(A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 22",
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x02030405",
    });
}

TEST_F(SUBTestLong, DataRegisterAddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x09080706",
    });
    When({
        "SUB.L D1, (2, A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 24",
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x02030405",
    });
}

TEST_F(SUBTestLong, DataRegisterAddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x09080706",
    });
    When({
        "SUB.L D1, (2, A1, A2.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 26",
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x02030405",
    });
}

TEST_F(SUBTestLong, DataRegisterAddressShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x07050301",
        "(0x00004000).L is 0x09080706",
    });
    When({
        "SUB.L D1, (0x4000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 24",
        "D1 is 0x07050301",
        "(0x00004000).L is 0x02030405",
    });
}

TEST_F(SUBTestLong, DataRegisterAddressLongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x07050301",
        "(0x00008000).L is 0x09080706",
    });
    When({
        "SUB.L D1, (0x8000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 28",
        "D1 is 0x07050301",
        "(0x00008000).L is 0x02030405",
    });
}

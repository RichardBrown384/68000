#include "M68000/Fixtures/M68000Test.h"

class ORTestWord : public M68000Test {};

TEST_F(ORTestWord, DataRegisterDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x03030503",
        "D2 is 0xF0F070F5",
    });
    When({
        "OR.W D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x03030503",
        "D2 is 0xF0F075F7",
    });
}

TEST_F(ORTestWord, DataRegisterDataRegisterFlagNWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x03038503",
        "D2 is 0xF0F070F5",
    });
    When({
        "OR.W D1, D2"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x03038503",
        "D2 is 0xF0F0F5F7",
    });
}

TEST_F(ORTestWord, DataRegisterDataRegisterFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x03030000",
        "D2 is 0xF0F00000",
    });
    When({
        "OR.W D1, D2"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x03030000",
        "D2 is 0xF0F00000",
    });
}

TEST_F(ORTestWord, DataRegisterDataRegisterFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0x010101F3",
        "D2 is 0x101011F1",
    });
    When({
        "OR.W D1, D2"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x010101F3",
        "D2 is 0x101011F3",
    });
}

TEST_F(ORTestWord, DataRegisterDataRegisterFlagVCWorks) {
    Given({
        "SR is S,0,VC",
        "PC is 0x1000",
        "D1 is 0x010101F3",
        "D2 is 0x101010F1",
    });
    When({
        "OR.W D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x010101F3",
        "D2 is 0x101011F3",
    });
}

TEST_F(ORTestWord, AddressIndirectDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5AA5",
    });
    When({
        "OR.W (A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x11115EA7",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5AA5",
    });
}

TEST_F(ORTestWord, AddressIncrementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5AA5",
    });
    When({
        "OR.W (A1)+, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x11115EA7",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x5AA5",
    });
}

TEST_F(ORTestWord, AddressDecrementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x5AA5",
    });
    When({
        "OR.W -(A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0x11115EA7",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5AA5",
    });
}

TEST_F(ORTestWord, AddressDisplacementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x5AA5",
    });
    When({
        "OR.W (2, A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x11115EA7",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x5AA5",
    });
}

TEST_F(ORTestWord, AddressIndexDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x5AA5",
    });
    When({
        "OR.W (2, A1, A2.L), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0x11115EA7",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x5AA5",
    });
}

TEST_F(ORTestWord, ShortDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "(0x00004000).W is 0x5AA5",
    });
    When({
        "OR.W (0x4000).W, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x11115EA7",
        "(0x00004000).W is 0x5AA5",
    });
}

TEST_F(ORTestWord, LongDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "(0x00008000).W is 0x5AA5",
    });
    When({
        "OR.W (0x8000).L, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 16",
        "D1 is 0x11115EA7",
        "(0x00008000).W is 0x5AA5",
    });
}

TEST_F(ORTestWord, PCDisplacementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "(0x00001060).W is 0x5AA5",
    });
    When({
        "OR.W (0x5E, PC), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x11115EA7",
        "(0x00001060).W is 0x5AA5",
    });
}

TEST_F(ORTestWord, PCIndexDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00000010",
        "(0x00001070).W is 0x5AA5",
    });
    When({
        "OR.W (0x5E, PC, A1.L), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0x11115EA7",
        "A1 is 0x00000010",
        "(0x00001070).W is 0x5AA5",
    });
}

TEST_F(ORTestWord, ImmediateDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
    });
    When({
        "OR.W #0x5AA5, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 8",
        "D1 is 0x11115EA7",
    });
}

TEST_F(ORTestWord, DataRegisterAddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5AA5",
    });
    When({
        "OR.W D1, (A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5EA7",
    });
}

TEST_F(ORTestWord, DataRegisterAddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5AA5",
    });
    When({
        "OR.W D1, (A1)+"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x11110607",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x5EA7",
    });
}

TEST_F(ORTestWord, DataRegisterAddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x5AA5",
    });
    When({
        "OR.W D1, -(A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5EA7",
    });
}

TEST_F(ORTestWord, DataRegisterAddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x5AA5",
    });
    When({
        "OR.W D1, (2, A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x5EA7",
    });
}

TEST_F(ORTestWord, DataRegisterAddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x5AA5",
    });
    When({
        "OR.W D1, (2, A1, A2.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x5EA7",
    });
}

TEST_F(ORTestWord, DataRegisterShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "(0x00004000).W is 0x5AA5",
    });
    When({
        "OR.W D1, (0x4000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "D1 is 0x11110607",
        "(0x00004000).W is 0x5EA7",
    });
}

TEST_F(ORTestWord, DataRegisterLongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "(0x00008000).W is 0x5AA5",
    });
    When({
        "OR.W D1, (0x8000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 20",
        "D1 is 0x11110607",
        "(0x00008000).W is 0x5EA7",
    });
}

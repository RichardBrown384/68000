#include "M68000/Fixtures/M68000Test.h"

class ORTestWord : public M68000Test {};

TEST_F(ORTestWord, DataRegisterDataRegisterWorks) {
    Given({
        "D1 is 0x03030503",
        "D2 is 0xF0F070F5",
        "SR is S,0,0"
    });
    When({
        "OR.W D1, D2"
    });
    Then({
        "D1 is 0x03030503",
        "D2 is 0xF0F075F7",
        "SR is S,0,0"
    });
}

TEST_F(ORTestWord, DataRegisterDataRegisterFlagNWorks) {
    Given({
        "D1 is 0x03038503",
        "D2 is 0xF0F070F5",
        "SR is S,0,0"
    });
    When({
        "OR.W D1, D2"
    });
    Then({
        "D1 is 0x03038503",
        "D2 is 0xF0F0F5F7",
        "SR is S,0,N"
    });
}

TEST_F(ORTestWord, DataRegisterDataRegisterFlagZWorks) {
    Given({
        "D1 is 0x03030000",
        "D2 is 0xF0F00000",
        "SR is S,0,0"
    });
    When({
        "OR.W D1, D2"
    });
    Then({
        "D1 is 0x03030000",
        "D2 is 0xF0F00000",
        "SR is S,0,Z"
    });
}

TEST_F(ORTestWord, DataRegisterDataRegisterFlagXWorks) {
    Given({
        "D1 is 0x010101F3",
        "D2 is 0x101011F1",
        "SR is S,0,X"
    });
    When({
        "OR.W D1, D2"
    });
    Then({
        "D1 is 0x010101F3",
        "D2 is 0x101011F3",
        "SR is S,0,X"
    });
}

TEST_F(ORTestWord, DataRegisterDataRegisterFlagVCWorks) {
    Given({
        "D1 is 0x010101F3",
        "D2 is 0x101010F1",
        "SR is S,0,VC"
    });
    When({
        "OR.W D1, D2"
    });
    Then({
        "D1 is 0x010101F3",
        "D2 is 0x101011F3",
        "SR is S,0,0"
    });
}

TEST_F(ORTestWord, AddressIndirectDataRegisterWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "OR.W (A1), D1"
    });
    Then({
        "D1 is 0x11115EA7",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5AA5",
        "SR is S,0,0"
    });
}

TEST_F(ORTestWord, AddressIncrementDataRegisterWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "OR.W (A1)+, D1"
    });
    Then({
        "D1 is 0x11115EA7",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x5AA5",
        "SR is S,0,0"
    });
}

TEST_F(ORTestWord, AddressDecrementDataRegisterWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "OR.W -(A1), D1"
    });
    Then({
        "D1 is 0x11115EA7",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5AA5",
        "SR is S,0,0"
    });
}

TEST_F(ORTestWord, AddressDisplacementDataRegisterWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "OR.W (2, A1), D1"
    });
    Then({
        "D1 is 0x11115EA7",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x5AA5",
        "SR is S,0,0"
    });
}

TEST_F(ORTestWord, AddressIndexDataRegisterWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "OR.W (2, A1, A2.L), D1"
    });
    Then({
        "D1 is 0x11115EA7",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x5AA5",
        "SR is S,0,0"
    });
}

TEST_F(ORTestWord, ShortDataRegisterWorks) {
    Given({
        "D1 is 0x11110607",
        "(0x00004000).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "OR.W (0x4000).W, D1"
    });
    Then({
        "D1 is 0x11115EA7",
        "(0x00004000).W is 0x5AA5",
        "SR is S,0,0"
    });
}

TEST_F(ORTestWord, LongDataRegisterWorks) {
    Given({
        "D1 is 0x11110607",
        "(0x00008000).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "OR.W (0x8000).L, D1"
    });
    Then({
        "D1 is 0x11115EA7",
        "(0x00008000).W is 0x5AA5",
        "SR is S,0,0"
    });
}

TEST_F(ORTestWord, PCDisplacementDataRegisterWorks) {
    Given({
        "D1 is 0x11110607",
        "(0x00001060).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "OR.W (0x5E, PC), D1"
    });
    Then({
        "D1 is 0x11115EA7",
        "(0x00001060).W is 0x5AA5",
        "SR is S,0,0"
    });
}

TEST_F(ORTestWord, PCIndexDataRegisterWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00000010",
        "(0x00001070).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "OR.W (0x5E, PC, A1.L), D1"
    });
    Then({
        "D1 is 0x11115EA7",
        "A1 is 0x00000010",
        "(0x00001070).W is 0x5AA5",
        "SR is S,0,0"
    });
}

TEST_F(ORTestWord, ImmediateDataRegisterWorks) {
    Given({
        "D1 is 0x11110607",
        "SR is S,0,0"
    });
    When({
        "OR.W #0x5AA5, D1"
    });
    Then({
        "D1 is 0x11115EA7",
        "SR is S,0,0"
    });
}

TEST_F(ORTestWord, DataRegisterAddressIndirectWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "OR.W D1, (A1)"
    });
    Then({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5EA7",
        "SR is S,0,0"
    });
}

TEST_F(ORTestWord, DataRegisterAddressIncrementWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "OR.W D1, (A1)+"
    });
    Then({
        "D1 is 0x11110607",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x5EA7",
        "SR is S,0,0"
    });
}

TEST_F(ORTestWord, DataRegisterAddressDecrementWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "OR.W D1, -(A1)"
    });
    Then({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5EA7",
        "SR is S,0,0"
    });
}

TEST_F(ORTestWord, DataRegisterAddressIndexWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "OR.W D1, (2, A1)"
    });
    Then({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x5EA7",
        "SR is S,0,0"
    });
}

TEST_F(ORTestWord, DataRegisterAddressDisplacementWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "OR.W D1, (2, A1, A2.L)"
    });
    Then({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x5EA7",
        "SR is S,0,0"
    });
}

TEST_F(ORTestWord, DataRegisterShortWorks) {
    Given({
        "D1 is 0x11110607",
        "(0x00004000).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "OR.W D1, (0x4000).W"
    });
    Then({
        "D1 is 0x11110607",
        "(0x00004000).W is 0x5EA7",
        "SR is S,0,0"
    });
}

TEST_F(ORTestWord, DataRegisterLongWorks) {
    Given({
        "D1 is 0x11110607",
        "(0x00008000).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "OR.W D1, (0x8000).L"
    });
    Then({
        "D1 is 0x11110607",
        "(0x00008000).W is 0x5EA7",
        "SR is S,0,0"
    });
}
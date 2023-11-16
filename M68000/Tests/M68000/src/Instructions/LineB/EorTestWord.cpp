#include "M68000/Fixtures/M68000Test.h"

class EORTestWord : public M68000Test {};

TEST_F(EORTestWord, DataRegisterDataRegisterWorks) {
    Given({
        "D1 is 0x03030503",
        "D2 is 0xF0F070F5",
        "SR is S,0,0"
    });
    When({
        "EOR.W D1, D2"
    });
    Then({
        "D1 is 0x03030503",
        "D2 is 0xF0F075F6",
        "SR is S,0,0"
    });
}

TEST_F(EORTestWord, DataRegisterDataRegisterFlagNWorks) {
    Given({
        "D1 is 0x03038503",
        "D2 is 0xF0F070F5",
        "SR is S,0,0"
    });
    When({
        "EOR.W D1, D2"
    });
    Then({
        "D1 is 0x03038503",
        "D2 is 0xF0F0F5F6",
        "SR is S,0,N"
    });
}

TEST_F(EORTestWord, DataRegisterDataRegisterFlagZWorks) {
    Given({
        "D1 is 0x03037060",
        "D2 is 0xF0F07060",
        "SR is S,0,0"
    });
    When({
        "EOR.W D1, D2"
    });
    Then({
        "D1 is 0x03037060",
        "D2 is 0xF0F00000",
        "SR is S,0,Z"
    });
}

TEST_F(EORTestWord, DataRegisterDataRegisterFlagXWorks) {
    Given({
        "D1 is 0x010101F3",
        "D2 is 0x101011F1",
        "SR is S,0,X"
    });
    When({
        "EOR.W D1, D2"
    });
    Then({
        "D1 is 0x010101F3",
        "D2 is 0x10101002",
        "SR is S,0,X"
    });
}

TEST_F(EORTestWord, DataRegisterDataRegisterFlagVCWorks) {
    Given({
        "D1 is 0x010101F3",
        "D2 is 0x101010F1",
        "SR is S,0,VC"
    });
    When({
        "EOR.W D1, D2"
    });
    Then({
        "D1 is 0x010101F3",
        "D2 is 0x10101102",
        "SR is S,0,0"
    });
}

TEST_F(EORTestWord, DataRegisterAddressIndirectWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "EOR.W D1, (A1)"
    });
    Then({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5CA2",
        "SR is S,0,0"
    });
}

TEST_F(EORTestWord, DataRegisterAddressIncrementWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "EOR.W D1, (A1)+"
    });
    Then({
        "D1 is 0x11110607",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x5CA2",
        "SR is S,0,0"
    });
}

TEST_F(EORTestWord, DataRegisterAddressDecrementWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "EOR.W D1, -(A1)"
    });
    Then({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5CA2",
        "SR is S,0,0"
    });
}

TEST_F(EORTestWord, DataRegisterAddressIndexWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "EOR.W D1, (2, A1)"
    });
    Then({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x5CA2",
        "SR is S,0,0"
    });
}

TEST_F(EORTestWord, DataRegisterAddressDisplacementWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "EOR.W D1, (2, A1, A2.L)"
    });
    Then({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x5CA2",
        "SR is S,0,0"
    });
}

TEST_F(EORTestWord, DataRegisterShortWorks) {
    Given({
        "D1 is 0x11110607",
        "(0x00004000).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "EOR.W D1, (0x4000).W"
    });
    Then({
        "D1 is 0x11110607",
        "(0x00004000).W is 0x5CA2",
        "SR is S,0,0"
    });
}

TEST_F(EORTestWord, DataRegisterLongWorks) {
    Given({
        "D1 is 0x11110607",
        "(0x00008000).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "EOR.W D1, (0x8000).L"
    });
    Then({
        "D1 is 0x11110607",
        "(0x00008000).W is 0x5CA2",
        "SR is S,0,0"
    });
}
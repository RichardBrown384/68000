#include "M68000/Fixtures/M68000Test.h"

class EORTestWord : public M68000Test {};

TEST_F(EORTestWord, DataRegisterDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x03030503",
        "D2 is 0xF0F070F5",
    });
    When({
        "EOR.W D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x03030503",
        "D2 is 0xF0F075F6",
    });
}

TEST_F(EORTestWord, DataRegisterDataRegisterFlagNWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x03038503",
        "D2 is 0xF0F070F5",
    });
    When({
        "EOR.W D1, D2"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x03038503",
        "D2 is 0xF0F0F5F6",
    });
}

TEST_F(EORTestWord, DataRegisterDataRegisterFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x03037060",
        "D2 is 0xF0F07060",
    });
    When({
        "EOR.W D1, D2"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x03037060",
        "D2 is 0xF0F00000",
    });
}

TEST_F(EORTestWord, DataRegisterDataRegisterFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0x010101F3",
        "D2 is 0x101011F1",
    });
    When({
        "EOR.W D1, D2"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x010101F3",
        "D2 is 0x10101002",
    });
}

TEST_F(EORTestWord, DataRegisterDataRegisterFlagVCWorks) {
    Given({
        "SR is S,0,VC",
        "PC is 0x1000",
        "D1 is 0x010101F3",
        "D2 is 0x101010F1",
    });
    When({
        "EOR.W D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x010101F3",
        "D2 is 0x10101102",
    });
}

TEST_F(EORTestWord, DataRegisterAddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5AA5",
    });
    When({
        "EOR.W D1, (A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5CA2",
    });
}

TEST_F(EORTestWord, DataRegisterAddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5AA5",
    });
    When({
        "EOR.W D1, (A1)+"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x11110607",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x5CA2",
    });
}

TEST_F(EORTestWord, DataRegisterAddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x5AA5",
    });
    When({
        "EOR.W D1, -(A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5CA2",
    });
}

TEST_F(EORTestWord, DataRegisterAddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x5AA5",
    });
    When({
        "EOR.W D1, (2, A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x5CA2",
    });
}

TEST_F(EORTestWord, DataRegisterAddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x5AA5",
    });
    When({
        "EOR.W D1, (2, A1, A2.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x5CA2",
    });
}

TEST_F(EORTestWord, DataRegisterShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "(0x00004000).W is 0x5AA5",
    });
    When({
        "EOR.W D1, (0x4000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "D1 is 0x11110607",
        "(0x00004000).W is 0x5CA2",
    });
}

TEST_F(EORTestWord, DataRegisterLongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "(0x00008000).W is 0x5AA5",
    });
    When({
        "EOR.W D1, (0x8000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 20",
        "D1 is 0x11110607",
        "(0x00008000).W is 0x5CA2",
    });
}

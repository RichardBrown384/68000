#include "M68000/Fixtures/M68000Test.h"

class MULUTestWord : public M68000Test {};

TEST_F(MULUTestWord, DataRegisterWorks) {
    Given({
        "D1 is 0x00000002",
        "D2 is 0x00000003",
        "SR is S,0,XVC"
    });
    When({
        "MULU D1, D2"
    });
    Then({
        "D1 is 0x00000002",
        "D2 is 0x00000006",
        "SR is S,0,X"
    });
}

TEST_F(MULUTestWord, DataRegisterMultiplicationIsUnsigned) {
    Given({
        "D1 is 0x0000FFFF",
        "D2 is 0x0000FFFF",
        "SR is S,0,XVC"
    });
    When({
        "MULU D1, D2"
    });
    Then({
        "D1 is 0x0000FFFF",
        "D2 is 0xFFFE0001",
        "SR is S,0,XN"
    });
}

TEST_F(MULUTestWord, DataRegisterFlagZWorks) {
    Given({
        "D1 is 0x00000000",
        "D2 is 0x0000FFFF",
        "SR is S,0,XVC"
    });
    When({
        "MULU D1, D2"
    });
    Then({
        "D1 is 0x00000000",
        "D2 is 0x00000000",
        "SR is S,0,XZ"
    });
}

TEST_F(MULUTestWord, AddressIndirectWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0xA55A",
        "SR is S,0,0"
    });
    When({
        "MULU (A1), D1"
    });
    Then({
        "D1 is 0x03E4A176",
        "A1 is 0x00008000",
        "(0x00008000).W is 0xA55A",
        "SR is S,0,0"
    });
}

TEST_F(MULUTestWord, AddressIncrementWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0xA55A",
        "SR is S,0,0"
    });
    When({
        "MULU (A1)+, D1"
    });
    Then({
        "D1 is 0x03E4A176",
        "A1 is 0x00008002",
        "(0x00008000).W is 0xA55A",
        "SR is S,0,0"
    });
}

TEST_F(MULUTestWord, AddressDecrementWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008002",
        "(0x00008000).W is 0xA55A",
        "SR is S,0,0"
    });
    When({
        "MULU -(A1), D1"
    });
    Then({
        "D1 is 0x03E4A176",
        "A1 is 0x00008000",
        "(0x00008000).W is 0xA55A",
        "SR is S,0,0"
    });
}

TEST_F(MULUTestWord, AddressDisplacementWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008002).W is 0xA55A",
        "SR is S,0,0"
    });
    When({
        "MULU (2, A1), D1"
    });
    Then({
        "D1 is 0x03E4A176",
        "A1 is 0x00008000",
        "(0x00008002).W is 0xA55A",
        "SR is S,0,0"
    });
}

TEST_F(MULUTestWord, AddressIndexWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0xA55A",
        "SR is S,0,0"
    });
    When({
        "MULU (2, A1, A2.L), D1"
    });
    Then({
        "D1 is 0x03E4A176",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0xA55A",
        "SR is S,0,0"
    });
}

TEST_F(MULUTestWord, ShortWorks) {
    Given({
        "D1 is 0x11110607",
        "(0x00004000).W is 0xA55A",
        "SR is S,0,0"
    });
    When({
        "MULU (0x4000).W, D1"
    });
    Then({
        "D1 is 0x03E4A176",
        "(0x00004000).W is 0xA55A",
        "SR is S,0,0"
    });
}

TEST_F(MULUTestWord, LongWorks) {
    Given({
        "D1 is 0x11110607",
        "(0x00008000).W is 0xA55A",
        "SR is S,0,0"
    });
    When({
        "MULU (0x8000).L, D1"
    });
    Then({
        "D1 is 0x03E4A176",
        "(0x00008000).W is 0xA55A",
        "SR is S,0,0"
    });
}

TEST_F(MULUTestWord, PCDisplacementWorks) {
    Given({
        "D1 is 0x11110607",
        "(0x00001060).W is 0xA55A",
        "SR is S,0,0"
    });
    When({
        "MULU (0x5E, PC), D1"
    });
    Then({
        "D1 is 0x03E4A176",
        "(0x00001060).W is 0xA55A",
        "SR is S,0,0"
    });
}

TEST_F(MULUTestWord, PCIndexWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00000010",
        "(0x00001070).W is 0xA55A",
        "SR is S,0,0"
    });
    When({
        "MULU (0x5E, PC, A1.L), D1"
    });
    Then({
        "D1 is 0x03E4A176",
        "A1 is 0x00000010",
        "(0x00001070).W is 0xA55A",
        "SR is S,0,0"
    });
}

TEST_F(MULUTestWord, ImmediateWorks) {
    Given({
        "D1 is 0x11110607",
        "SR is S,0,0"
    });
    When({
        "MULU #0xA55A, D1"
    });
    Then({
        "D1 is 0x03E4A176",
        "SR is S,0,0"
    });
}
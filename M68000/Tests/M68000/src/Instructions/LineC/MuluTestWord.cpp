#include "M68000/Fixtures/M68000Test.h"

class MULUTestWord : public M68000Test {};

TEST_F(MULUTestWord, DataRegisterWorks) {
    Given({
        "SR is S,0,XVC",
        "PC is 0x1000",
        "D1 is 0x00000002",
        "D2 is 0x00000003",
    });
    When({
        "MULU D1, D2"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 40",
        "D1 is 0x00000002",
        "D2 is 0x00000006",
    });
}

TEST_F(MULUTestWord, DataRegisterMultiplicationIsUnsigned) {
    Given({
        "SR is S,0,XVC",
        "PC is 0x1000",
        "D1 is 0x0000FFFF",
        "D2 is 0x0000FFFF",
    });
    When({
        "MULU D1, D2"
    });
    Then({
        "SR is S,0,XN",
        "PC is 0x1002",
        "CYCLES is 70",
        "D1 is 0x0000FFFF",
        "D2 is 0xFFFE0001",
    });
}

TEST_F(MULUTestWord, DataRegisterFlagZWorks) {
    Given({
        "SR is S,0,XVC",
        "PC is 0x1000",
        "D1 is 0x00000000",
        "D2 is 0x0000FFFF",
    });
    When({
        "MULU D1, D2"
    });
    Then({
        "SR is S,0,XZ",
        "PC is 0x1002",
        "CYCLES is 38",
        "D1 is 0x00000000",
        "D2 is 0x00000000",
    });
}

TEST_F(MULUTestWord, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0xA55A",
    });
    When({
        "MULU (A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 58",
        "D1 is 0x03E4A176",
        "A1 is 0x00008000",
        "(0x00008000).W is 0xA55A",
    });
}

TEST_F(MULUTestWord, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0xA55A",
    });
    When({
        "MULU (A1)+, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 58",
        "D1 is 0x03E4A176",
        "A1 is 0x00008002",
        "(0x00008000).W is 0xA55A",
    });
}

TEST_F(MULUTestWord, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008002",
        "(0x00008000).W is 0xA55A",
    });
    When({
        "MULU -(A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 60",
        "D1 is 0x03E4A176",
        "A1 is 0x00008000",
        "(0x00008000).W is 0xA55A",
    });
}

TEST_F(MULUTestWord, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008002).W is 0xA55A",
    });
    When({
        "MULU (2, A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 62",
        "D1 is 0x03E4A176",
        "A1 is 0x00008000",
        "(0x00008002).W is 0xA55A",
    });
}

TEST_F(MULUTestWord, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0xA55A",
    });
    When({
        "MULU (2, A1, A2.L), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 64",
        "D1 is 0x03E4A176",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0xA55A",
    });
}

TEST_F(MULUTestWord, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "(0x00004000).W is 0xA55A",
    });
    When({
        "MULU (0x4000).W, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 62",
        "D1 is 0x03E4A176",
        "(0x00004000).W is 0xA55A",
    });
}

TEST_F(MULUTestWord, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "(0x00008000).W is 0xA55A",
    });
    When({
        "MULU (0x8000).L, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 66",
        "D1 is 0x03E4A176",
        "(0x00008000).W is 0xA55A",
    });
}

TEST_F(MULUTestWord, PCDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "(0x00001060).W is 0xA55A",
    });
    When({
        "MULU (0x5E, PC), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 62",
        "D1 is 0x03E4A176",
        "(0x00001060).W is 0xA55A",
    });
}

TEST_F(MULUTestWord, PCIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00000010",
        "(0x00001070).W is 0xA55A",
    });
    When({
        "MULU (0x5E, PC, A1.L), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 64",
        "D1 is 0x03E4A176",
        "A1 is 0x00000010",
        "(0x00001070).W is 0xA55A",
    });
}

TEST_F(MULUTestWord, ImmediateWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
    });
    When({
        "MULU #0xA55A, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 58",
        "D1 is 0x03E4A176",
    });
}

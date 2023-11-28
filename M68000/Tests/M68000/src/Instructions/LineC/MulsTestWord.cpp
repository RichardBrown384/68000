#include "M68000/Fixtures/M68000Test.h"

class MULSTestWord : public M68000Test {};

TEST_F(MULSTestWord, DataRegisterWorks) {
    Given({
        "SR is S,0,XVC",
        "PC is 0x1000",
        "D1 is 0x00000002",
        "D2 is 0x00000003",
    });
    When({
        "MULS D1, D2"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 42",
        "D1 is 0x00000002",
        "D2 is 0x00000006",
    });
}

TEST_F(MULSTestWord, DataRegisterMultiplicationIsSigned) {
    Given({
        "SR is S,0,XVC",
        "PC is 0x1000",
        "D1 is 0x0000FFFF",
        "D2 is 0x0000FFFF",
    });
    When({
        "MULS D1, D2"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 40",
        "D1 is 0x0000FFFF",
        "D2 is 0x00000001",
    });
}

TEST_F(MULSTestWord, DataRegisterFlagZWorks) {
    Given({
        "SR is S,0,XVC",
        "PC is 0x1000",
        "D1 is 0x00000000",
        "D2 is 0x0000FFFF",
    });
    When({
        "MULS D1, D2"
    });
    Then({
        "SR is S,0,XZ",
        "PC is 0x1002",
        "CYCLES is 38",
        "D1 is 0x00000000",
        "D2 is 0x00000000",
    });
}

TEST_F(MULSTestWord, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0xA55A",
    });
    When({
        "MULS (A1), D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 68",
        "D1 is 0xFDDDA176",
        "A1 is 0x00008000",
        "(0x00008000).W is 0xA55A",
    });
}

TEST_F(MULSTestWord, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0xA55A",
    });
    When({
        "MULS (A1)+, D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 68",
        "D1 is 0xFDDDA176",
        "A1 is 0x00008002",
        "(0x00008000).W is 0xA55A",
    });
}

TEST_F(MULSTestWord, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008002",
        "(0x00008000).W is 0xA55A",
    });
    When({
        "MULS -(A1), D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 70",
        "D1 is 0xFDDDA176",
        "A1 is 0x00008000",
        "(0x00008000).W is 0xA55A",
    });
}

TEST_F(MULSTestWord, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008002).W is 0xA55A",
    });
    When({
        "MULS (2, A1), D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 72",
        "D1 is 0xFDDDA176",
        "A1 is 0x00008000",
        "(0x00008002).W is 0xA55A",
    });
}

TEST_F(MULSTestWord, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0xA55A",
    });
    When({
        "MULS (2, A1, A2.L), D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 74",
        "D1 is 0xFDDDA176",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0xA55A",
    });
}

TEST_F(MULSTestWord, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "(0x00004000).W is 0xA55A",
    });
    When({
        "MULS (0x4000).W, D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 72",
        "D1 is 0xFDDDA176",
        "(0x00004000).W is 0xA55A",
    });
}

TEST_F(MULSTestWord, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "(0x00008000).W is 0xA55A",
    });
    When({
        "MULS (0x8000).L, D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 76",
        "D1 is 0xFDDDA176",
        "(0x00008000).W is 0xA55A",
    });
}

TEST_F(MULSTestWord, PCDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "(0x00001060).W is 0xA55A",
    });
    When({
        "MULS (0x5E, PC), D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 72",
        "D1 is 0xFDDDA176",
        "(0x00001060).W is 0xA55A",
    });
}

TEST_F(MULSTestWord, PCIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00000010",
        "(0x00001070).W is 0xA55A",
    });
    When({
        "MULS (0x5E, PC, A1.L), D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 74",
        "D1 is 0xFDDDA176",
        "A1 is 0x00000010",
        "(0x00001070).W is 0xA55A",
    });
}

TEST_F(MULSTestWord, ImmediateWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
    });
    When({
        "MULS #0xA55A, D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 68",
        "D1 is 0xFDDDA176",
    });
}

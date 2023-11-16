#include "M68000/Fixtures/M68000Test.h"

class MULSTestWord : public M68000Test {};

TEST_F(MULSTestWord, DataRegisterWorks) {
    Given({
        "D1 is 0x00000002",
        "D2 is 0x00000003",
        "SR is S,0,XVC"
    });
    When({
        "MULS D1, D2"
    });
    Then({
        "D1 is 0x00000002",
        "D2 is 0x00000006",
        "SR is S,0,X"
    });
}

TEST_F(MULSTestWord, DataRegisterMultiplicationIsSigned) {
    Given({
        "D1 is 0x0000FFFF",
        "D2 is 0x0000FFFF",
        "SR is S,0,XVC"
    });
    When({
        "MULS D1, D2"
    });
    Then({
        "D1 is 0x0000FFFF",
        "D2 is 0x00000001",
        "SR is S,0,X"
    });
}

TEST_F(MULSTestWord, DataRegisterFlagZWorks) {
    Given({
        "D1 is 0x00000000",
        "D2 is 0x0000FFFF",
        "SR is S,0,XVC"
    });
    When({
        "MULS D1, D2"
    });
    Then({
        "D1 is 0x00000000",
        "D2 is 0x00000000",
        "SR is S,0,XZ"
    });
}

TEST_F(MULSTestWord, AddressIndirectWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0xA55A",
        "SR is S,0,0"
    });
    When({
        "MULS (A1), D1"
    });
    Then({
        "D1 is 0xFDDDA176",
        "A1 is 0x00008000",
        "(0x00008000).W is 0xA55A",
        "SR is S,0,N"
    });
}

TEST_F(MULSTestWord, AddressIncrementWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0xA55A",
        "SR is S,0,0"
    });
    When({
        "MULS (A1)+, D1"
    });
    Then({
        "D1 is 0xFDDDA176",
        "A1 is 0x00008002",
        "(0x00008000).W is 0xA55A",
        "SR is S,0,N"
    });
}

TEST_F(MULSTestWord, AddressDecrementWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008002",
        "(0x00008000).W is 0xA55A",
        "SR is S,0,0"
    });
    When({
        "MULS -(A1), D1"
    });
    Then({
        "D1 is 0xFDDDA176",
        "A1 is 0x00008000",
        "(0x00008000).W is 0xA55A",
        "SR is S,0,N"
    });
}

TEST_F(MULSTestWord, AddressDisplacementWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008002).W is 0xA55A",
        "SR is S,0,0"
    });
    When({
        "MULS (2, A1), D1"
    });
    Then({
        "D1 is 0xFDDDA176",
        "A1 is 0x00008000",
        "(0x00008002).W is 0xA55A",
        "SR is S,0,N"
    });
}

TEST_F(MULSTestWord, AddressIndexWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0xA55A",
        "SR is S,0,0"
    });
    When({
        "MULS (2, A1, A2.L), D1"
    });
    Then({
        "D1 is 0xFDDDA176",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0xA55A",
        "SR is S,0,N"
    });
}

TEST_F(MULSTestWord, ShortWorks) {
    Given({
        "D1 is 0x11110607",
        "(0x00004000).W is 0xA55A",
        "SR is S,0,0"
    });
    When({
        "MULS (0x4000).W, D1"
    });
    Then({
        "D1 is 0xFDDDA176",
        "(0x00004000).W is 0xA55A",
        "SR is S,0,N"
    });
}

TEST_F(MULSTestWord, LongWorks) {
    Given({
        "D1 is 0x11110607",
        "(0x00008000).W is 0xA55A",
        "SR is S,0,0"
    });
    When({
        "MULS (0x8000).L, D1"
    });
    Then({
        "D1 is 0xFDDDA176",
        "(0x00008000).W is 0xA55A",
        "SR is S,0,N"
    });
}

TEST_F(MULSTestWord, PCDisplacementWorks) {
    Given({
        "D1 is 0x11110607",
        "(0x00001060).W is 0xA55A",
        "SR is S,0,0"
    });
    When({
        "MULS (0x5E, PC), D1"
    });
    Then({
        "D1 is 0xFDDDA176",
        "(0x00001060).W is 0xA55A",
        "SR is S,0,N"
    });
}

TEST_F(MULSTestWord, PCIndexWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00000010",
        "(0x00001070).W is 0xA55A",
        "SR is S,0,0"
    });
    When({
        "MULS (0x5E, PC, A1.L), D1"
    });
    Then({
        "D1 is 0xFDDDA176",
        "A1 is 0x00000010",
        "(0x00001070).W is 0xA55A",
        "SR is S,0,N"
    });
}

TEST_F(MULSTestWord, ImmediateWorks) {
    Given({
        "D1 is 0x11110607",
        "SR is S,0,0"
    });
    When({
        "MULS #0xA55A, D1"
    });
    Then({
        "D1 is 0xFDDDA176",
        "SR is S,0,N"
    });
}
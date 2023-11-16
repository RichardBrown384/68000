#include "M68000/Fixtures/M68000Test.h"

class SUBATestWord : public M68000Test {};

TEST_F(SUBATestWord, DataRegisterWorks) {
    Given({
        "D1 is 0x01010201",
        "A2 is 0x01010305",
        "SR is S,0,0"
    });
    When({
        "SUBA.W D1, A2"
    });
    Then({
        "D1 is 0x01010201",
        "A2 is 0x01010104",
        "SR is S,0,0"
    });
}

TEST_F(SUBATestWord, DataRegisterSignExtend16Works) {
    Given({
        "D1 is 0x00008080",
        "A2 is 0x01000080",
        "SR is S,0,0"
    });
    When({
        "SUBA.W D1, A2"
    });
    Then({
        "D1 is 0x00008080",
        "A2 is 0x01008000",
        "SR is S,0,0"
    });
}

TEST_F(SUBATestWord, DataRegisterFlagNVWorks) {
    Given({
        "D1 is 0x0000FFFF",
        "A2 is 0x7FFFFFFF",
        "SR is S,0,0"
    });
    When({
        "SUBA.W D1, A2"
    });
    Then({
        "D1 is 0x0000FFFF",
        "A2 is 0x80000000",
        "SR is S,0,0"
    });
}

TEST_F(SUBATestWord, AddressRegisterWorks) {
    Given({
        "A1 is 0x01010301",
        "A2 is 0x01010908",
        "SR is S,0,0"
    });
    When({
        "SUBA.W A1, A2"
    });
    Then({
        "A1 is 0x01010301",
        "A2 is 0x01010607",
        "SR is S,0,0"
    });
}

TEST_F(SUBATestWord, AddressIndirectWorks) {
    Given({
        "A1 is 0x00008000",
        "A2 is 0x01030908",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "SUBA.W (A1), A2"
    });
    Then({
        "A1 is 0x00008000",
        "A2 is 0x01030304",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0"
    });
}

TEST_F(SUBATestWord, AddressIncrementWorks) {
    Given({
        "A1 is 0x00008000",
        "A2 is 0x01030908",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "SUBA.W (A1)+, A2"
    });
    Then({
        "A1 is 0x00008002",
        "A2 is 0x01030304",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0"
    });
}

TEST_F(SUBATestWord, AddressDecrementWorks) {
    Given({
        "A1 is 0x00008002",
        "A2 is 0x01030908",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "SUBA.W -(A1), A2"
    });
    Then({
        "A1 is 0x00008000",
        "A2 is 0x01030304",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0"
    });
}

TEST_F(SUBATestWord, AddressDisplacementWorks) {
    Given({
        "A1 is 0x00008000",
        "A2 is 0x01030908",
        "(0x00008002).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "SUBA.W (2, A1), A2"
    });
    Then({
        "A1 is 0x00008000",
        "A2 is 0x01030304",
        "(0x00008002).W is 0x0604",
        "SR is S,0,0"
    });
}

TEST_F(SUBATestWord, AddressIndexWorks) {
    Given({
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "A3 is 0x01030908",
        "(0x00008012).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "SUBA.W (2, A1, A2.L), A3"
    });
    Then({
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "A3 is 0x01030304",
        "(0x00008012).W is 0x0604",
        "SR is S,0,0"
    });
}

TEST_F(SUBATestWord, ShortWorks) {
    Given({
        "A1 is 0x01030908",
        "(0x00004000).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "SUBA.W (0x4000).W, A1"
    });
    Then({
        "A1 is 0x01030304",
        "(0x00004000).W is 0x0604",
        "SR is S,0,0"
    });
}

TEST_F(SUBATestWord, LongWorks) {
    Given({
        "A1 is 0x01030908",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "SUBA.W (0x8000).L, A1"
    });
    Then({
        "A1 is 0x01030304",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0"
    });
}

TEST_F(SUBATestWord, PCDisplacementWorks) {
    Given({
        "A1 is 0x01030908",
        "(0x00001060).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "SUBA.W (0x5E, PC), A1"
    });
    Then({
        "A1 is 0x01030304",
        "(0x00001060).W is 0x0604",
        "SR is S,0,0"
    });
}

TEST_F(SUBATestWord, PCIndexWorks) {
    Given({
        "A1 is 0x00000010",
        "A2 is 0x01030908",
        "(0x00001070).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "SUBA.W (0x5E, PC, A1.L), A2"
    });
    Then({
        "A1 is 0x00000010",
        "A2 is 0x01030304",
        "(0x00001070).W is 0x0604",
        "SR is S,0,0"
    });
}

TEST_F(SUBATestWord, ImmediateWorks) {
    Given({
        "A1 is 0x01030908",
        "SR is S,0,0"
    });
    When({
        "SUBA.W #0x0604, A1"
    });
    Then({
        "A1 is 0x01030304",
        "SR is S,0,0"
    });
}
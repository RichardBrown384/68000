#include "M68000/Fixtures/M68000Test.h"

class SUBATestWord : public M68000Test {};

TEST_F(SUBATestWord, DataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01010201",
        "A2 is 0x01010305",
    });
    When({
        "SUBA.W D1, A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x01010201",
        "A2 is 0x01010104",
    });
}

TEST_F(SUBATestWord, DataRegisterSignExtend16Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00008080",
        "A2 is 0x01000080",
    });
    When({
        "SUBA.W D1, A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x00008080",
        "A2 is 0x01008000",
    });
}

TEST_F(SUBATestWord, DataRegisterFlagNVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0000FFFF",
        "A2 is 0x7FFFFFFF",
    });
    When({
        "SUBA.W D1, A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x0000FFFF",
        "A2 is 0x80000000",
    });
}

TEST_F(SUBATestWord, AddressRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x01010301",
        "A2 is 0x01010908",
    });
    When({
        "SUBA.W A1, A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "A1 is 0x01010301",
        "A2 is 0x01010607",
    });
}

TEST_F(SUBATestWord, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00008000",
        "A2 is 0x01030908",
        "(0x00008000).W is 0x0604",
    });
    When({
        "SUBA.W (A1), A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "A1 is 0x00008000",
        "A2 is 0x01030304",
        "(0x00008000).W is 0x0604",
    });
}

TEST_F(SUBATestWord, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00008000",
        "A2 is 0x01030908",
        "(0x00008000).W is 0x0604",
    });
    When({
        "SUBA.W (A1)+, A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "A1 is 0x00008002",
        "A2 is 0x01030304",
        "(0x00008000).W is 0x0604",
    });
}

TEST_F(SUBATestWord, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00008002",
        "A2 is 0x01030908",
        "(0x00008000).W is 0x0604",
    });
    When({
        "SUBA.W -(A1), A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "A1 is 0x00008000",
        "A2 is 0x01030304",
        "(0x00008000).W is 0x0604",
    });
}

TEST_F(SUBATestWord, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00008000",
        "A2 is 0x01030908",
        "(0x00008002).W is 0x0604",
    });
    When({
        "SUBA.W (2, A1), A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "A1 is 0x00008000",
        "A2 is 0x01030304",
        "(0x00008002).W is 0x0604",
    });
}

TEST_F(SUBATestWord, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "A3 is 0x01030908",
        "(0x00008012).W is 0x0604",
    });
    When({
        "SUBA.W (2, A1, A2.L), A3"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "A3 is 0x01030304",
        "(0x00008012).W is 0x0604",
    });
}

TEST_F(SUBATestWord, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x01030908",
        "(0x00004000).W is 0x0604",
    });
    When({
        "SUBA.W (0x4000).W, A1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "A1 is 0x01030304",
        "(0x00004000).W is 0x0604",
    });
}

TEST_F(SUBATestWord, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x01030908",
        "(0x00008000).W is 0x0604",
    });
    When({
        "SUBA.W (0x8000).L, A1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 20",
        "A1 is 0x01030304",
        "(0x00008000).W is 0x0604",
    });
}

TEST_F(SUBATestWord, PCDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x01030908",
        "(0x00001060).W is 0x0604",
    });
    When({
        "SUBA.W (0x5E, PC), A1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "A1 is 0x01030304",
        "(0x00001060).W is 0x0604",
    });
}

TEST_F(SUBATestWord, PCIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00000010",
        "A2 is 0x01030908",
        "(0x00001070).W is 0x0604",
    });
    When({
        "SUBA.W (0x5E, PC, A1.L), A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "A1 is 0x00000010",
        "A2 is 0x01030304",
        "(0x00001070).W is 0x0604",
    });
}

TEST_F(SUBATestWord, ImmediateWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x01030908",
    });
    When({
        "SUBA.W #0x0604, A1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "A1 is 0x01030304",
    });
}

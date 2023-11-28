#include "M68000/Fixtures/M68000Test.h"

class SUBATestLong : public M68000Test {};

TEST_F(SUBATestLong, DataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01010101",
        "A2 is 0x0708090A",
    });
    When({
        "SUBA.L D1, A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x01010101",
        "A2 is 0x06070809",
    });
}

TEST_F(SUBATestLong, DataRegisterFlagNVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xFFFFFFFF",
        "A2 is 0x7FFFFFFF",
    });
    When({
        "SUBA.L D1, A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0xFFFFFFFF",
        "A2 is 0x80000000",
    });
}

TEST_F(SUBATestLong, AddressRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x04060604",
        "A2 is 0x05080907",
    });
    When({
        "SUBA.L A1, A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "A1 is 0x04060604",
        "A2 is 0x01020303",
    });
}

TEST_F(SUBATestLong, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00008000",
        "A2 is 0x05080907",
        "(0x00008000).L is 0x04060604",
    });
    When({
        "SUBA.L (A1), A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "A1 is 0x00008000",
        "A2 is 0x01020303",
        "(0x00008000).L is 0x04060604",
    });
}

TEST_F(SUBATestLong, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00008000",
        "A2 is 0x05080907",
        "(0x00008000).L is 0x04060604",
    });
    When({
        "SUBA.L (A1)+, A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "A1 is 0x00008004",
        "A2 is 0x01020303",
        "(0x00008000).L is 0x04060604",
    });
}

TEST_F(SUBATestLong, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00008004",
        "A2 is 0x05080907",
        "(0x00008000).L is 0x04060604",
    });
    When({
        "SUBA.L -(A1), A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 16",
        "A1 is 0x00008000",
        "A2 is 0x01020303",
        "(0x00008000).L is 0x04060604",
    });
}

TEST_F(SUBATestLong, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00008000",
        "A2 is 0x05080907",
        "(0x00008002).L is 0x04060604",
    });
    When({
        "SUBA.L (2, A1), A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "A1 is 0x00008000",
        "A2 is 0x01020303",
        "(0x00008002).L is 0x04060604",
    });
}

TEST_F(SUBATestLong, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "A3 is 0x05080907",
        "(0x00008012).L is 0x04060604",
    });
    When({
        "SUBA.L (2, A1, A2.L), A3"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 20",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "A3 is 0x01020303",
        "(0x00008012).L is 0x04060604",
    });
}

TEST_F(SUBATestLong, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x05080907",
        "(0x00004000).L is 0x04060604",
    });
    When({
        "SUBA.L (0x4000).W, A1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "A1 is 0x01020303",
        "(0x00004000).L is 0x04060604",
    });
}

TEST_F(SUBATestLong, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x05080907",
        "(0x00008000).L is 0x04060604",
    });
    When({
        "SUBA.L (0x8000).L, A1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 22",
        "A1 is 0x01020303",
        "(0x00008000).L is 0x04060604",
    });
}

TEST_F(SUBATestLong, PCDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x05080907",
        "(0x00001060).L is 0x04060604",
    });
    When({
        "SUBA.L (0x5E, PC), A1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "A1 is 0x01020303",
        "(0x00001060).L is 0x04060604",
    });
}

TEST_F(SUBATestLong, PCIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00000010",
        "A2 is 0x05080907",
        "(0x00001070).L is 0x04060604",
    });
    When({
        "SUBA.L (0x5E, PC, A1.L), A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 20",
        "A1 is 0x00000010",
        "A2 is 0x01020303",
        "(0x00001070).L is 0x04060604",
    });
}

TEST_F(SUBATestLong, ImmediateWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x05080907",
    });
    When({
        "SUBA.L #0x04060604, A1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 16",
        "A1 is 0x01020303",
    });
}

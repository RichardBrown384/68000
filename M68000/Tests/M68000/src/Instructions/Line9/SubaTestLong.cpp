#include "M68000/Fixtures/M68000Test.h"

class SUBATestLong : public M68000Test {};

TEST_F(SUBATestLong, DataRegisterWorks) {
    Given({
        "D1 is 0x01010101",
        "A2 is 0x0708090A",
        "SR is S,0,0"
    });
    When({
        "SUBA.L D1, A2"
    });
    Then({
        "D1 is 0x01010101",
        "A2 is 0x06070809",
        "SR is S,0,0"
    });
}

TEST_F(SUBATestLong, DataRegisterFlagNVWorks) {
    Given({
        "D1 is 0xFFFFFFFF",
        "A2 is 0x7FFFFFFF",
        "SR is S,0,0"
    });
    When({
        "SUBA.L D1, A2"
    });
    Then({
        "D1 is 0xFFFFFFFF",
        "A2 is 0x80000000",
        "SR is S,0,0"
    });
}

TEST_F(SUBATestLong, AddressRegisterWorks) {
    Given({
        "A1 is 0x04060604",
        "A2 is 0x05080907",
        "SR is S,0,0"
    });
    When({
        "SUBA.L A1, A2"
    });
    Then({
        "A1 is 0x04060604",
        "A2 is 0x01020303",
        "SR is S,0,0"
    });
}

TEST_F(SUBATestLong, AddressIndirectWorks) {
    Given({
        "A1 is 0x00008000",
        "A2 is 0x05080907",
        "(0x00008000).L is 0x04060604",
        "SR is S,0,0"
    });
    When({
        "SUBA.L (A1), A2"
    });
    Then({
        "A1 is 0x00008000",
        "A2 is 0x01020303",
        "(0x00008000).L is 0x04060604",
        "SR is S,0,0"
    });
}

TEST_F(SUBATestLong, AddressIncrementWorks) {
    Given({
        "A1 is 0x00008000",
        "A2 is 0x05080907",
        "(0x00008000).L is 0x04060604",
        "SR is S,0,0"
    });
    When({
        "SUBA.L (A1)+, A2"
    });
    Then({
        "A1 is 0x00008004",
        "A2 is 0x01020303",
        "(0x00008000).L is 0x04060604",
        "SR is S,0,0"
    });
}

TEST_F(SUBATestLong, AddressDecrementWorks) {
    Given({
        "A1 is 0x00008004",
        "A2 is 0x05080907",
        "(0x00008000).L is 0x04060604",
        "SR is S,0,0"
    });
    When({
        "SUBA.L -(A1), A2"
    });
    Then({
        "A1 is 0x00008000",
        "A2 is 0x01020303",
        "(0x00008000).L is 0x04060604",
        "SR is S,0,0"
    });
}

TEST_F(SUBATestLong, AddressDisplacementWorks) {
    Given({
        "A1 is 0x00008000",
        "A2 is 0x05080907",
        "(0x00008002).L is 0x04060604",
        "SR is S,0,0"
    });
    When({
        "SUBA.L (2, A1), A2"
    });
    Then({
        "A1 is 0x00008000",
        "A2 is 0x01020303",
        "(0x00008002).L is 0x04060604",
        "SR is S,0,0"
    });
}

TEST_F(SUBATestLong, AddressIndexWorks) {
    Given({
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "A3 is 0x05080907",
        "(0x00008012).L is 0x04060604",
        "SR is S,0,0"
    });
    When({
        "SUBA.L (2, A1, A2.L), A3"
    });
    Then({
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "A3 is 0x01020303",
        "(0x00008012).L is 0x04060604",
        "SR is S,0,0"
    });
}

TEST_F(SUBATestLong, ShortWorks) {
    Given({
        "A1 is 0x05080907",
        "(0x00004000).L is 0x04060604",
        "SR is S,0,0"
    });
    When({
        "SUBA.L (0x4000).W, A1"
    });
    Then({
        "A1 is 0x01020303",
        "(0x00004000).L is 0x04060604",
        "SR is S,0,0"
    });
}

TEST_F(SUBATestLong, LongWorks) {
    Given({
        "A1 is 0x05080907",
        "(0x00008000).L is 0x04060604",
        "SR is S,0,0"
    });
    When({
        "SUBA.L (0x8000).L, A1"
    });
    Then({
        "A1 is 0x01020303",
        "(0x00008000).L is 0x04060604",
        "SR is S,0,0"
    });
}

TEST_F(SUBATestLong, PCDisplacementWorks) {
    Given({
        "A1 is 0x05080907",
        "(0x00001060).L is 0x04060604",
        "SR is S,0,0"
    });
    When({
        "SUBA.L (0x5E, PC), A1"
    });
    Then({
        "A1 is 0x01020303",
        "(0x00001060).L is 0x04060604",
        "SR is S,0,0"
    });
}

TEST_F(SUBATestLong, PCIndexWorks) {
    Given({
        "A1 is 0x00000010",
        "A2 is 0x05080907",
        "(0x00001070).L is 0x04060604",
        "SR is S,0,0"
    });
    When({
        "SUBA.L (0x5E, PC, A1.L), A2"
    });
    Then({
        "A1 is 0x00000010",
        "A2 is 0x01020303",
        "(0x00001070).L is 0x04060604",
        "SR is S,0,0"
    });
}

TEST_F(SUBATestLong, ImmediateWorks) {
    Given({
        "A1 is 0x05080907",
        "SR is S,0,0"
    });
    When({
        "SUBA.L #0x04060604, A1"
    });
    Then({
        "A1 is 0x01020303",
        "SR is S,0,0"
    });
}
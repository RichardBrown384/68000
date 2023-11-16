#include "M68000/Fixtures/M68000Test.h"

class ADDATestWord : public M68000Test {};

TEST_F(ADDATestWord, DataRegisterWorks) {
    Given({
        "D1 is 0x01010101",
        "A2 is 0x01010101",
        "SR is S,0,0"
    });
    When({
        "ADDA.W D1, A2"
    });
    Then({
        "D1 is 0x01010101",
        "A2 is 0x01010202",
        "SR is S,0,0"
    });
}

TEST_F(ADDATestWord, DataRegisterSignExtend16Works) {
    Given({
        "D1 is 0x00008080",
        "A2 is 0x01000080",
        "SR is S,0,0"
    });
    When({
        "ADDA.W D1, A2"
    });
    Then({
        "D1 is 0x00008080",
        "A2 is 0x00FF8100",
        "SR is S,0,0"
    });
}

TEST_F(ADDATestWord, DataRegisterFlagNVWorks) {
    Given({
        "D1 is 0x00000001",
        "A2 is 0x7FFFFFFF",
        "SR is S,0,0"
    });
    When({
        "ADDA.W D1, A2"
    });
    Then({
        "D1 is 0x00000001",
        "A2 is 0x80000000",
        "SR is S,0,0"
    });
}

TEST_F(ADDATestWord, AddressRegisterWorks) {
    Given({
        "A1 is 0x01010101",
        "A2 is 0x01010101",
        "SR is S,0,0"
    });
    When({
        "ADDA.W A1, A2"
    });
    Then({
        "A1 is 0x01010101",
        "A2 is 0x01010202",
        "SR is S,0,0"
    });
}

TEST_F(ADDATestWord, AddressIndirectWorks) {
    Given({
        "A1 is 0x00008000",
        "A2 is 0x01030201",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "ADDA.W (A1), A2"
    });
    Then({
        "A1 is 0x00008000",
        "A2 is 0x01030805",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0"
    });
}

TEST_F(ADDATestWord, AddressIncrementWorks) {
    Given({
        "A1 is 0x00008000",
        "A2 is 0x01030201",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "ADDA.W (A1)+, A2"
    });
    Then({
        "A1 is 0x00008002",
        "A2 is 0x01030805",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0"
    });
}

TEST_F(ADDATestWord, AddressDecrementWorks) {
    Given({
        "A1 is 0x00008002",
        "A2 is 0x01030201",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "ADDA.W -(A1), A2"
    });
    Then({
        "A1 is 0x00008000",
        "A2 is 0x01030805",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0"
    });
}

TEST_F(ADDATestWord, AddressDisplacementWorks) {
    Given({
        "A1 is 0x00008000",
        "A2 is 0x01030201",
        "(0x00008002).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "ADDA.W (2, A1), A2"
    });
    Then({
        "A1 is 0x00008000",
        "A2 is 0x01030805",
        "(0x00008002).W is 0x0604",
        "SR is S,0,0"
    });
}

TEST_F(ADDATestWord, AddressIndexWorks) {
    Given({
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "A3 is 0x01030201",
        "(0x00008012).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "ADDA.W (2, A1, A2.L), A3"
    });
    Then({
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "A3 is 0x01030805",
        "(0x00008012).W is 0x0604",
        "SR is S,0,0"
    });
}

TEST_F(ADDATestWord, ShortWorks) {
    Given({
        "A1 is 0x01030201",
        "(0x00004000).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "ADDA.W (0x4000).W, A1"
    });
    Then({
        "A1 is 0x01030805",
        "(0x00004000).W is 0x0604",
        "SR is S,0,0"
    });
}

TEST_F(ADDATestWord, LongWorks) {
    Given({
        "A1 is 0x01030201",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "ADDA.W (0x8000).L, A1"
    });
    Then({
        "A1 is 0x01030805",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0"
    });
}

TEST_F(ADDATestWord, PCDisplacementWorks) {
    Given({
        "A1 is 0x01030201",
        "(0x00001060).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "ADDA.W (0x5E, PC), A1"
    });
    Then({
        "A1 is 0x01030805",
        "(0x00001060).W is 0x0604",
        "SR is S,0,0"
    });
}

TEST_F(ADDATestWord, PCIndexWorks) {
    Given({
        "A1 is 0x00000010",
        "A2 is 0x01030201",
        "(0x00001070).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "ADDA.W (0x5E, PC, A1.L), A2"
    });
    Then({
        "A1 is 0x00000010",
        "A2 is 0x01030805",
        "(0x00001070).W is 0x0604",
        "SR is S,0,0"
    });
}

TEST_F(ADDATestWord, ImmediateWorks) {
    Given({
        "A1 is 0x01030201",
        "SR is S,0,0"
    });
    When({
        "ADDA.W #0x0604, A1"
    });
    Then({
        "A1 is 0x01030805",
        "SR is S,0,0"
    });
}
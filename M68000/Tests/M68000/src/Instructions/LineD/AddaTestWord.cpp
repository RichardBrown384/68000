#include "M68000/Fixtures/M68000Test.h"

class ADDATestWord : public M68000Test {};

TEST_F(ADDATestWord, DataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01010101",
        "A2 is 0x01010101",
    });
    When({
        "ADDA.W D1, A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x01010101",
        "A2 is 0x01010202",
    });
}

TEST_F(ADDATestWord, DataRegisterSignExtend16Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00008080",
        "A2 is 0x01000080",
    });
    When({
        "ADDA.W D1, A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x00008080",
        "A2 is 0x00FF8100",
    });
}

TEST_F(ADDATestWord, DataRegisterFlagNVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000001",
        "A2 is 0x7FFFFFFF",
    });
    When({
        "ADDA.W D1, A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x00000001",
        "A2 is 0x80000000",
    });
}

TEST_F(ADDATestWord, AddressRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x01010101",
        "A2 is 0x01010101",
    });
    When({
        "ADDA.W A1, A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "A1 is 0x01010101",
        "A2 is 0x01010202",
    });
}

TEST_F(ADDATestWord, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00008000",
        "A2 is 0x01030201",
        "(0x00008000).W is 0x0604",
    });
    When({
        "ADDA.W (A1), A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "A1 is 0x00008000",
        "A2 is 0x01030805",
        "(0x00008000).W is 0x0604",
    });
}

TEST_F(ADDATestWord, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00008000",
        "A2 is 0x01030201",
        "(0x00008000).W is 0x0604",
    });
    When({
        "ADDA.W (A1)+, A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "A1 is 0x00008002",
        "A2 is 0x01030805",
        "(0x00008000).W is 0x0604",
    });
}

TEST_F(ADDATestWord, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00008002",
        "A2 is 0x01030201",
        "(0x00008000).W is 0x0604",
    });
    When({
        "ADDA.W -(A1), A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "A1 is 0x00008000",
        "A2 is 0x01030805",
        "(0x00008000).W is 0x0604",
    });
}

TEST_F(ADDATestWord, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00008000",
        "A2 is 0x01030201",
        "(0x00008002).W is 0x0604",
    });
    When({
        "ADDA.W (2, A1), A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "A1 is 0x00008000",
        "A2 is 0x01030805",
        "(0x00008002).W is 0x0604",
    });
}

TEST_F(ADDATestWord, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "A3 is 0x01030201",
        "(0x00008012).W is 0x0604",
    });
    When({
        "ADDA.W (2, A1, A2.L), A3"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "A3 is 0x01030805",
        "(0x00008012).W is 0x0604",
    });
}

TEST_F(ADDATestWord, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x01030201",
        "(0x00004000).W is 0x0604",
    });
    When({
        "ADDA.W (0x4000).W, A1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "A1 is 0x01030805",
        "(0x00004000).W is 0x0604",
    });
}

TEST_F(ADDATestWord, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x01030201",
        "(0x00008000).W is 0x0604",
    });
    When({
        "ADDA.W (0x8000).L, A1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 20",
        "A1 is 0x01030805",
        "(0x00008000).W is 0x0604",
    });
}

TEST_F(ADDATestWord, PCDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x01030201",
        "(0x00001060).W is 0x0604",
    });
    When({
        "ADDA.W (0x5E, PC), A1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "A1 is 0x01030805",
        "(0x00001060).W is 0x0604",
    });
}

TEST_F(ADDATestWord, PCIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00000010",
        "A2 is 0x01030201",
        "(0x00001070).W is 0x0604",
    });
    When({
        "ADDA.W (0x5E, PC, A1.L), A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "A1 is 0x00000010",
        "A2 is 0x01030805",
        "(0x00001070).W is 0x0604",
    });
}

TEST_F(ADDATestWord, ImmediateWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x01030201",
    });
    When({
        "ADDA.W #0x0604, A1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "A1 is 0x01030805",
    });
}

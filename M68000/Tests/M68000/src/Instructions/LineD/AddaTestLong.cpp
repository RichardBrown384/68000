#include "M68000/Fixtures/M68000Test.h"

class ADDATestLong : public M68000Test {};

TEST_F(ADDATestLong, DataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01010101",
        "A2 is 0x01010101",
    });
    When({
        "ADDA.L D1, A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x01010101",
        "A2 is 0x02020202",
    });
}

TEST_F(ADDATestLong, DataRegisterFlagNVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x10000000",
        "A2 is 0x70000000",
    });
    When({
        "ADDA.L D1, A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x10000000",
        "A2 is 0x80000000",
    });
}

TEST_F(ADDATestLong, AddressRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x01010101",
        "A2 is 0x01010101",
    });
    When({
        "ADDA.L A1, A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "A1 is 0x01010101",
        "A2 is 0x02020202",
    });
}

TEST_F(ADDATestLong, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00008000",
        "A2 is 0x01030201",
        "(0x00008000).L is 0x04060604",
    });
    When({
        "ADDA.L (A1), A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "A1 is 0x00008000",
        "A2 is 0x05090805",
        "(0x00008000).L is 0x04060604",
    });
}

TEST_F(ADDATestLong, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00008000",
        "A2 is 0x01030201",
        "(0x00008000).L is 0x04060604",
    });
    When({
        "ADDA.L (A1)+, A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "A1 is 0x00008004",
        "A2 is 0x05090805",
        "(0x00008000).L is 0x04060604",
    });
}

TEST_F(ADDATestLong, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00008004",
        "A2 is 0x01030201",
        "(0x00008000).L is 0x04060604",
    });
    When({
        "ADDA.L -(A1), A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 16",
        "A1 is 0x00008000",
        "A2 is 0x05090805",
        "(0x00008000).L is 0x04060604",
    });
}

TEST_F(ADDATestLong, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00008000",
        "A2 is 0x01030201",
        "(0x00008002).L is 0x04060604",
    });
    When({
        "ADDA.L (2, A1), A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "A1 is 0x00008000",
        "A2 is 0x05090805",
        "(0x00008002).L is 0x04060604",
    });
}

TEST_F(ADDATestLong, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "A3 is 0x01030201",
        "(0x00008012).L is 0x04060604",
    });
    When({
        "ADDA.L (2, A1, A2.L), A3"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 20",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "A3 is 0x05090805",
        "(0x00008012).L is 0x04060604",
    });
}

TEST_F(ADDATestLong, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x01030201",
        "(0x00004000).L is 0x04060604",
    });
    When({
        "ADDA.L (0x4000).W, A1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "A1 is 0x05090805",
        "(0x00004000).L is 0x04060604",
    });
}

TEST_F(ADDATestLong, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x01030201",
        "(0x00008000).L is 0x04060604",
    });
    When({
        "ADDA.L (0x8000).L, A1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 22",
        "A1 is 0x05090805",
        "(0x00008000).L is 0x04060604",
    });
}

TEST_F(ADDATestLong, PCDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x01030201",
        "(0x00001060).L is 0x04060604",
    });
    When({
        "ADDA.L (0x5E, PC), A1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "A1 is 0x05090805",
        "(0x00001060).L is 0x04060604",
    });
}

TEST_F(ADDATestLong, PCIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00000010",
        "A2 is 0x01030201",
        "(0x00001070).L is 0x04060604",
    });
    When({
        "ADDA.L (0x5E, PC, A1.L), A2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 20",
        "A1 is 0x00000010",
        "A2 is 0x05090805",
        "(0x00001070).L is 0x04060604",
    });
}

TEST_F(ADDATestLong, ImmediateWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x01030201",
    });
    When({
        "ADDA.L #0x04060604, A1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 16",
        "A1 is 0x05090805",
    });
}

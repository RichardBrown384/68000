#include "M68000/Fixtures/M68000Test.h"

class ADDATestLong : public M68000Test {};

TEST_F(ADDATestLong, DataRegisterWorks) {
    Given({
        "D1 is 0x01010101",
        "A2 is 0x01010101",
        "SR is S,0,0"
    });
    When({
        "ADDA.L D1, A2"
    });
    Then({
        "D1 is 0x01010101",
        "A2 is 0x02020202",
        "SR is S,0,0"
    });
}

TEST_F(ADDATestLong, DataRegisterFlagNVWorks) {
    Given({
        "D1 is 0x10000000",
        "A2 is 0x70000000",
        "SR is S,0,0"
    });
    When({
        "ADDA.L D1, A2"
    });
    Then({
        "D1 is 0x10000000",
        "A2 is 0x80000000",
        "SR is S,0,0"
    });
}

TEST_F(ADDATestLong, AddressRegisterWorks) {
    Given({
        "A1 is 0x01010101",
        "A2 is 0x01010101",
        "SR is S,0,0"
    });
    When({
        "ADDA.L A1, A2"
    });
    Then({
        "A1 is 0x01010101",
        "A2 is 0x02020202",
        "SR is S,0,0"
    });
}

TEST_F(ADDATestLong, AddressIndirectWorks) {
    Given({
        "A1 is 0x00008000",
        "A2 is 0x01030201",
        "(0x00008000).L is 0x04060604",
        "SR is S,0,0"
    });
    When({
        "ADDA.L (A1), A2"
    });
    Then({
        "A1 is 0x00008000",
        "A2 is 0x05090805",
        "(0x00008000).L is 0x04060604",
        "SR is S,0,0"
    });
}

TEST_F(ADDATestLong, AddressIncrementWorks) {
    Given({
        "A1 is 0x00008000",
        "A2 is 0x01030201",
        "(0x00008000).L is 0x04060604",
        "SR is S,0,0"
    });
    When({
        "ADDA.L (A1)+, A2"
    });
    Then({
        "A1 is 0x00008004",
        "A2 is 0x05090805",
        "(0x00008000).L is 0x04060604",
        "SR is S,0,0"
    });
}

TEST_F(ADDATestLong, AddressDecrementWorks) {
    Given({
        "A1 is 0x00008004",
        "A2 is 0x01030201",
        "(0x00008000).L is 0x04060604",
        "SR is S,0,0"
    });
    When({
        "ADDA.L -(A1), A2"
    });
    Then({
        "A1 is 0x00008000",
        "A2 is 0x05090805",
        "(0x00008000).L is 0x04060604",
        "SR is S,0,0"
    });
}

TEST_F(ADDATestLong, AddressDisplacementWorks) {
    Given({
        "A1 is 0x00008000",
        "A2 is 0x01030201",
        "(0x00008002).L is 0x04060604",
        "SR is S,0,0"
    });
    When({
        "ADDA.L (2, A1), A2"
    });
    Then({
        "A1 is 0x00008000",
        "A2 is 0x05090805",
        "(0x00008002).L is 0x04060604",
        "SR is S,0,0"
    });
}

TEST_F(ADDATestLong, AddressIndexWorks) {
    Given({
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "A3 is 0x01030201",
        "(0x00008012).L is 0x04060604",
        "SR is S,0,0"
    });
    When({
        "ADDA.L (2, A1, A2.L), A3"
    });
    Then({
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "A3 is 0x05090805",
        "(0x00008012).L is 0x04060604",
        "SR is S,0,0"
    });
}

TEST_F(ADDATestLong, ShortWorks) {
    Given({
        "A1 is 0x01030201",
        "(0x00004000).L is 0x04060604",
        "SR is S,0,0"
    });
    When({
        "ADDA.L (0x4000).W, A1"
    });
    Then({
        "A1 is 0x05090805",
        "(0x00004000).L is 0x04060604",
        "SR is S,0,0"
    });
}

TEST_F(ADDATestLong, LongWorks) {
    Given({
        "A1 is 0x01030201",
        "(0x00008000).L is 0x04060604",
        "SR is S,0,0"
    });
    When({
        "ADDA.L (0x8000).L, A1"
    });
    Then({
        "A1 is 0x05090805",
        "(0x00008000).L is 0x04060604",
        "SR is S,0,0"
    });
}

TEST_F(ADDATestLong, PCDisplacementWorks) {
    Given({
        "A1 is 0x01030201",
        "(0x00001060).L is 0x04060604",
        "SR is S,0,0"
    });
    When({
        "ADDA.L (0x5E, PC), A1"
    });
    Then({
        "A1 is 0x05090805",
        "(0x00001060).L is 0x04060604",
        "SR is S,0,0"
    });
}

TEST_F(ADDATestLong, PCIndexWorks) {
    Given({
        "A1 is 0x00000010",
        "A2 is 0x01030201",
        "(0x00001070).L is 0x04060604",
        "SR is S,0,0"
    });
    When({
        "ADDA.L (0x5E, PC, A1.L), A2"
    });
    Then({
        "A1 is 0x00000010",
        "A2 is 0x05090805",
        "(0x00001070).L is 0x04060604",
        "SR is S,0,0"
    });
}

TEST_F(ADDATestLong, ImmediateWorks) {
    Given({
        "A1 is 0x01030201",
        "SR is S,0,0"
    });
    When({
        "ADDA.L #0x04060604, A1"
    });
    Then({
        "A1 is 0x05090805",
        "SR is S,0,0"
    });
}
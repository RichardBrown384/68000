#include "M68000/Fixtures/M68000Test.h"

class LSLTest : public M68000Test {};

TEST_F(LSLTest, LSLImmediateByteWorks) {
    Given({
        "D1 is 0xFFFFFF08",
        "SR is S,0,0"
    });
    When({
        "LSL.B #2, D1"
    });
    Then({
        "D1 is 0xFFFFFF20",
        "SR is S,0,0"
    });
}

TEST_F(LSLTest, LSLImmediateByteSetsCarryExtendAndNegativeFlags) {
    Given({
        "D1 is 0xFFFFFFC0",
        "SR is S,0,0"
    });
    When({
        "LSL.B #1, D1"
    });
    Then({
        "D1 is 0xFFFFFF80",
        "SR is S,0,XNC"
    });
}

TEST_F(LSLTest, LSLImmediateByteSetsZeroFlag) {
    Given({
        "D1 is 0xFFFFFF40",
        "SR is S,0,0"
    });
    When({
        "LSL.B #2, D1"
    });
    Then({
        "D1 is 0xFFFFFF00",
        "SR is S,0,XZC"
    });
}

TEST_F(LSLTest, LSLImmediateWordWorks) {
    Given({
        "D1 is 0xFFFF0808",
        "SR is S,0,0"
    });
    When({
        "LSL.W #2, D1"
    });
    Then({
        "D1 is 0xFFFF2020",
        "SR is S,0,0"
    });
}

TEST_F(LSLTest, LSLImmediateLongWorks) {
    Given({
        "D1 is 0x08080808",
        "SR is S,0,0"
    });
    When({
        "LSL.L #3, D1"
    });
    Then({
        "D1 is 0x40404040",
        "SR is S,0,0"
    });
}

TEST_F(LSLTest, LSLRegisterByteWorks) {
    Given({
        "D0 is 0x2",
        "D1 is 0xFFFFFF08",
        "SR is S,0,0"
    });
    When({
        "LSL.B D0, D1"
    });
    Then({
        "D1 is 0xFFFFFF20",
        "SR is S,0,0"
    });
}

TEST_F(LSLTest, LSLRegisterByteZeroShiftWorks) {
    Given({
        "D0 is 0x0",
        "D1 is 0xFFFFFF08",
        "SR is S,0,XC"
    });
    When({
        "LSL.B D0, D1"
    });
    Then({
        "D1 is 0xFFFFFF08",
        "SR is S,0,X"
    });
}

TEST_F(LSLTest, LSLRegisterByteShift17Works) {
    Given({
        "D0 is 0x11",
        "D1 is 0xFFFFFF08",
        "SR is S,0,0"
    });
    When({
        "LSL.B D0, D1"
    });
    Then({
        "CYCLES is 40",
        "D1 is 0xFFFFFF00",
        "SR is S,0,Z"
    });
}

TEST_F(LSLTest, LSLRegisterByteShift66Works) {
    Given({
        "D0 is 0x42",
        "D1 is 0xFFFFFF08",
        "SR is S,0,0"
    });
    When({
        "LSL.B D0, D1"
    });
    Then({
        "CYCLES is 10",
        "D1 is 0xFFFFFF20",
        "SR is S,0,0"
    });
}

TEST_F(LSLTest, LSLRegisterWordWorks) {
    Given({
        "D0 is 0x2",
        "D1 is 0xFFFF0808",
        "SR is S,0,0"
    });
    When({
        "LSL.W D0, D1"
    });
    Then({
        "D1 is 0xFFFF2020",
        "SR is S,0,0"
    });
}

TEST_F(LSLTest, LSLRegisterWordZeroShiftWorks) {
    Given({
        "D0 is 0x0",
        "D1 is 0xFFFF0808",
        "SR is S,0,XC"
    });
    When({
        "LSL.W D0, D1"
    });
    Then({
        "D1 is 0xFFFF0808",
        "SR is S,0,X"
    });
}

TEST_F(LSLTest, LSLRegisterWordShift23Works) {
    Given({
        "D0 is 0x17",
        "D1 is 0xFFFF0808",
        "SR is S,0,0"
    });
    When({
        "LSL.W D0, D1"
    });
    Then({
        "CYCLES is 52",
        "D1 is 0xFFFF0000",
        "SR is S,0,Z"
    });
}

TEST_F(LSLTest, LSLRegisterWordShift66Works) {
    Given({
        "D0 is 0x42",
        "D1 is 0xFFFF0808",
        "SR is S,0,0"
    });
    When({
        "LSL.W D0, D1"
    });
    Then({
        "CYCLES is 10",
        "D1 is 0xFFFF2020",
        "SR is S,0,0"
    });
}

TEST_F(LSLTest, LSLRegisterLongWorks) {
    Given({
        "D0 is 0x3",
        "D1 is 0x08080808",
        "SR is S,0,0"
    });
    When({
        "LSL.L D0, D1"
    });
    Then({
        "D1 is 0x40404040",
        "SR is S,0,0"
    });
}

TEST_F(LSLTest, LSLRegisterLongZeroShiftWorks) {
    Given({
        "D0 is 0x0",
        "D1 is 0x08080808",
        "SR is S,0,XC"
    });
    When({
        "LSL.L D0, D1"
    });
    Then({
        "D1 is 0x08080808",
        "SR is S,0,X"
    });
}

TEST_F(LSLTest, LSLRegisterLongShift32Works) {
    Given({
        "D0 is 0x20",
        "D1 is 0x08080808",
        "SR is S,0,0"
    });
    When({
        "LSL.L D0, D1"
    });
    Then({
        "CYCLES is 72",
        "D1 is 0x00000000",
        "SR is S,0,Z"
    });
}

TEST_F(LSLTest, LSLRegisterLongShift45Works) {
    Given({
        "D0 is 0x2D",
        "D1 is 0x08080808",
        "SR is S,0,0"
    });
    When({
        "LSL.L D0, D1"
    });
    Then({
        "CYCLES is 98",
        "D1 is 0x00000000",
        "SR is S,0,Z"
    });
}

TEST_F(LSLTest, LSLRegisterLongShift66Works) {
    Given({
        "D0 is 0x42",
        "D1 is 0x08080808",
        "SR is S,0,0"
    });
    When({
        "LSL.L D0, D1"
    });
    Then({
        "CYCLES is 12",
        "D1 is 0x20202020",
        "SR is S,0,0"
    });
}


TEST_F(LSLTest, LSLMemoryWordWorks) {
    Given({
        "A1 is 0x00002000",
        "(0x2000).W is 0xEDAD",
        "SR is S,0,0"
    });
    When({
        "LSL.W (A1)"
    });
    Then({
        "A1 is 0x00002000",
        "(0x2000).W is 0xDB5A",
        "SR is S,0,XNC"
    });
}

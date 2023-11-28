#include "M68000/Fixtures/M68000Test.h"

class LSLTest : public M68000Test {};

TEST_F(LSLTest, LSLImmediateByteWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xFFFFFF08",
    });
    When({
        "LSL.B #2, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFFF20",
    });
}

TEST_F(LSLTest, LSLImmediateByteSetsCarryExtendAndNegativeFlags) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xFFFFFFC0",
    });
    When({
        "LSL.B #1, D1"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0xFFFFFF80",
    });
}

TEST_F(LSLTest, LSLImmediateByteSetsZeroFlag) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xFFFFFF40",
    });
    When({
        "LSL.B #2, D1"
    });
    Then({
        "SR is S,0,XZC",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFFF00",
    });
}

TEST_F(LSLTest, LSLImmediateWordWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xFFFF0808",
    });
    When({
        "LSL.W #2, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFF2020",
    });
}

TEST_F(LSLTest, LSLImmediateLongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x08080808",
    });
    When({
        "LSL.L #3, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x40404040",
    });
}

TEST_F(LSLTest, LSLRegisterByteWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x2",
        "D1 is 0xFFFFFF08",
    });
    When({
        "LSL.B D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFFF20",
    });
}

TEST_F(LSLTest, LSLRegisterByteZeroShiftWorks) {
    Given({
        "SR is S,0,XC",
        "PC is 0x1000",
        "D0 is 0x0",
        "D1 is 0xFFFFFF08",
    });
    When({
        "LSL.B D0, D1"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0xFFFFFF08",
    });
}

TEST_F(LSLTest, LSLRegisterByteShift17Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x11",
        "D1 is 0xFFFFFF08",
    });
    When({
        "LSL.B D0, D1"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 40",
        "D1 is 0xFFFFFF00",
    });
}

TEST_F(LSLTest, LSLRegisterByteShift66Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x42",
        "D1 is 0xFFFFFF08",
    });
    When({
        "LSL.B D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFFF20",
    });
}

TEST_F(LSLTest, LSLRegisterWordWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x2",
        "D1 is 0xFFFF0808",
    });
    When({
        "LSL.W D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFF2020",
    });
}

TEST_F(LSLTest, LSLRegisterWordZeroShiftWorks) {
    Given({
        "SR is S,0,XC",
        "PC is 0x1000",
        "D0 is 0x0",
        "D1 is 0xFFFF0808",
    });
    When({
        "LSL.W D0, D1"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0xFFFF0808",
    });
}

TEST_F(LSLTest, LSLRegisterWordShift23Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x17",
        "D1 is 0xFFFF0808",
    });
    When({
        "LSL.W D0, D1"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 52",
        "D1 is 0xFFFF0000",
    });
}

TEST_F(LSLTest, LSLRegisterWordShift66Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x42",
        "D1 is 0xFFFF0808",
    });
    When({
        "LSL.W D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFF2020",
    });
}

TEST_F(LSLTest, LSLRegisterLongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x3",
        "D1 is 0x08080808",
    });
    When({
        "LSL.L D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x40404040",
    });
}

TEST_F(LSLTest, LSLRegisterLongZeroShiftWorks) {
    Given({
        "SR is S,0,XC",
        "PC is 0x1000",
        "D0 is 0x0",
        "D1 is 0x08080808",
    });
    When({
        "LSL.L D0, D1"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x08080808",
    });
}

TEST_F(LSLTest, LSLRegisterLongShift32Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x20",
        "D1 is 0x08080808",
    });
    When({
        "LSL.L D0, D1"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 72",
        "D1 is 0x00000000",
    });
}

TEST_F(LSLTest, LSLRegisterLongShift45Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x2D",
        "D1 is 0x08080808",
    });
    When({
        "LSL.L D0, D1"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 98",
        "D1 is 0x00000000",
    });
}

TEST_F(LSLTest, LSLRegisterLongShift66Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x42",
        "D1 is 0x08080808",
    });
    When({
        "LSL.L D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x20202020",
    });
}


TEST_F(LSLTest, LSLMemoryWordWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00002000",
        "(0x2000).W is 0xEDAD",
    });
    When({
        "LSL.W (A1)"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 12",
        "A1 is 0x00002000",
        "(0x2000).W is 0xDB5A",
    });
}

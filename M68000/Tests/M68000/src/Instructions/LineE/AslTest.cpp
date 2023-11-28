#include "M68000/Fixtures/M68000Test.h"

class ASLTest : public M68000Test {};

TEST_F(ASLTest, ASLImmediateByteWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xFFFFFF08",
    });
    When({
        "ASL.B #2, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFFF20",
    });
}

TEST_F(ASLTest, ASLImmediateByteSetsCarryExtendAndNegativeFlags) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xFFFFFFC0",
    });
    When({
        "ASL.B #1, D1"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0xFFFFFF80",
    });
}

TEST_F(ASLTest, ASLImmediateByteSetsOverflowAndZeroFlags) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xFFFFFF40",
    });
    When({
        "ASL.B #2, D1"
    });
    Then({
        "SR is S,0,XZVC",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFFF00",
    });
}

TEST_F(ASLTest, ASLImmediateWordWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xFFFF0808",
    });
    When({
        "ASL.W #2, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFF2020",
    });
}

TEST_F(ASLTest, ASLImmediateLongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x08080808",
    });
    When({
        "ASL.L #3, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x40404040",
    });
}

TEST_F(ASLTest, ASLRegisterByteWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x2",
        "D1 is 0xFFFFFF08",
    });
    When({
        "ASL.B D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFFF20",
    });
}

TEST_F(ASLTest, ASLRegisterByteZeroShiftWorks) {
    Given({
        "SR is S,0,XC",
        "PC is 0x1000",
        "D0 is 0x0",
        "D1 is 0xFFFFFF08",
    });
    When({
        "ASL.B D0, D1"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0xFFFFFF08",
    });
}

TEST_F(ASLTest, ASLRegisterByteShift17Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x11",
        "D1 is 0xFFFFFF08",
    });
    When({
        "ASL.B D0, D1"
    });
    Then({
        "SR is S,0,ZV",
        "PC is 0x1002",
        "CYCLES is 40",
        "D1 is 0xFFFFFF00",
    });
}

TEST_F(ASLTest, ASLRegisterByteShift66Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x42",
        "D1 is 0xFFFFFF08",
    });
    When({
        "ASL.B D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFFF20",
    });
}

TEST_F(ASLTest, ASLRegisterWordWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x2",
        "D1 is 0xFFFF0808",
    });
    When({
        "ASL.W D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFF2020",
    });
}

TEST_F(ASLTest, ASLRegisterWordZeroShiftWorks) {
    Given({
        "SR is S,0,XC",
        "PC is 0x1000",
        "D0 is 0x0",
        "D1 is 0xFFFF0808",
    });
    When({
        "ASL.W D0, D1"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0xFFFF0808",
    });
}

TEST_F(ASLTest, ASLRegisterWordShift23Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x17",
        "D1 is 0xFFFF0808",
    });
    When({
        "ASL.W D0, D1"
    });
    Then({
        "SR is S,0,ZV",
        "PC is 0x1002",
        "CYCLES is 52",
        "D1 is 0xFFFF0000",
    });
}

TEST_F(ASLTest, ASLRegisterWordShift66Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x42",
        "D1 is 0xFFFF0808",
    });
    When({
        "ASL.W D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFF2020",
    });
}

TEST_F(ASLTest, ASLRegisterLongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x3",
        "D1 is 0x08080808",
    });
    When({
        "ASL.L D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x40404040",
    });
}

TEST_F(ASLTest, ASLRegisterLongZeroShiftWorks) {
    Given({
        "SR is S,0,XC",
        "PC is 0x1000",
        "D0 is 0x0",
        "D1 is 0x08080808",
    });
    When({
        "ASL.L D0, D1"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x08080808",
    });
}

TEST_F(ASLTest, ASLRegisterLongShift32Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x20",
        "D1 is 0x08080808",
    });
    When({
        "ASL.L D0, D1"
    });
    Then({
        "SR is S,0,ZV",
        "PC is 0x1002",
        "CYCLES is 72",
        "D1 is 0x00000000",
    });
}

TEST_F(ASLTest, ASLRegisterLongShift45Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x2D",
        "D1 is 0x08080808",
    });
    When({
        "ASL.L D0, D1"
    });
    Then({
        "SR is S,0,ZV",
        "PC is 0x1002",
        "CYCLES is 98",
        "D1 is 0x00000000",
    });
}

TEST_F(ASLTest, ASLRegisterLongShift66Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x42",
        "D1 is 0x08080808",
    });
    When({
        "ASL.L D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x20202020",
    });
}


TEST_F(ASLTest, ASLMemoryWordWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00002000",
        "(0x2000).W is 0xEDAD",
    });
    When({
        "ASL.W (A1)"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 12",
        "A1 is 0x00002000",
        "(0x2000).W is 0xDB5A",
    });
}

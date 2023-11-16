#include "M68000/Fixtures/M68000Test.h"

class ASLTest : public M68000Test {};

TEST_F(ASLTest, ASLImmediateByteWorks) {
    Given({
        "D1 is 0xFFFFFF08",
        "SR is S,0,0"
    });
    When({
        "ASL.B #2, D1"
    });
    Then({
        "D1 is 0xFFFFFF20",
        "SR is S,0,0"
    });
}

TEST_F(ASLTest, ASLImmediateByteSetsCarryExtendAndNegativeFlags) {
    Given({
        "D1 is 0xFFFFFFC0",
        "SR is S,0,0"
    });
    When({
        "ASL.B #1, D1"
    });
    Then({
        "D1 is 0xFFFFFF80",
        "SR is S,0,XNC"
    });
}

TEST_F(ASLTest, ASLImmediateByteSetsOverflowAndZeroFlags) {
    Given({
        "D1 is 0xFFFFFF40",
        "SR is S,0,0"
    });
    When({
        "ASL.B #2, D1"
    });
    Then({
        "D1 is 0xFFFFFF00",
        "SR is S,0,XZVC"
    });
}

TEST_F(ASLTest, ASLImmediateWordWorks) {
    Given({
        "D1 is 0xFFFF0808",
        "SR is S,0,0"
    });
    When({
        "ASL.W #2, D1"
    });
    Then({
        "D1 is 0xFFFF2020",
        "SR is S,0,0"
    });
}

TEST_F(ASLTest, ASLImmediateLongWorks) {
    Given({
        "D1 is 0x08080808",
        "SR is S,0,0"
    });
    When({
        "ASL.L #3, D1"
    });
    Then({
        "D1 is 0x40404040",
        "SR is S,0,0"
    });
}

TEST_F(ASLTest, ASLRegisterByteWorks) {
    Given({
        "D0 is 0x2",
        "D1 is 0xFFFFFF08",
        "SR is S,0,0"
    });
    When({
        "ASL.B D0, D1"
    });
    Then({
        "D1 is 0xFFFFFF20",
        "SR is S,0,0"
    });
}

TEST_F(ASLTest, ASLRegisterByteZeroShiftWorks) {
    Given({
        "D0 is 0x0",
        "D1 is 0xFFFFFF08",
        "SR is S,0,XC"
    });
    When({
        "ASL.B D0, D1"
    });
    Then({
        "D1 is 0xFFFFFF08",
        "SR is S,0,X"
    });
}

TEST_F(ASLTest, ASLRegisterByteShift17Works) {
    Given({
        "D0 is 0x11",
        "D1 is 0xFFFFFF08",
        "SR is S,0,0"
    });
    When({
        "ASL.B D0, D1"
    });
    Then({
        "CYCLES is 40",
        "D1 is 0xFFFFFF00",
        "SR is S,0,ZV"
    });
}

TEST_F(ASLTest, ASLRegisterByteShift66Works) {
    Given({
        "D0 is 0x42",
        "D1 is 0xFFFFFF08",
        "SR is S,0,0"
    });
    When({
        "ASL.B D0, D1"
    });
    Then({
        "CYCLES is 10",
        "D1 is 0xFFFFFF20",
        "SR is S,0,0"
    });
}

TEST_F(ASLTest, ASLRegisterWordWorks) {
    Given({
        "D0 is 0x2",
        "D1 is 0xFFFF0808",
        "SR is S,0,0"
    });
    When({
        "ASL.W D0, D1"
    });
    Then({
        "D1 is 0xFFFF2020",
        "SR is S,0,0"
    });
}

TEST_F(ASLTest, ASLRegisterWordZeroShiftWorks) {
    Given({
        "D0 is 0x0",
        "D1 is 0xFFFF0808",
        "SR is S,0,XC"
    });
    When({
        "ASL.W D0, D1"
    });
    Then({
        "D1 is 0xFFFF0808",
        "SR is S,0,X"
    });
}

TEST_F(ASLTest, ASLRegisterWordShift23Works) {
    Given({
        "D0 is 0x17",
        "D1 is 0xFFFF0808",
        "SR is S,0,0"
    });
    When({
        "ASL.W D0, D1"
    });
    Then({
        "CYCLES is 52",
        "D1 is 0xFFFF0000",
        "SR is S,0,ZV"
    });
}

TEST_F(ASLTest, ASLRegisterWordShift66Works) {
    Given({
        "D0 is 0x42",
        "D1 is 0xFFFF0808",
        "SR is S,0,0"
    });
    When({
        "ASL.W D0, D1"
    });
    Then({
        "CYCLES is 10",
        "D1 is 0xFFFF2020",
        "SR is S,0,0"
    });
}

TEST_F(ASLTest, ASLRegisterLongWorks) {
    Given({
        "D0 is 0x3",
        "D1 is 0x08080808",
        "SR is S,0,0"
    });
    When({
        "ASL.L D0, D1"
    });
    Then({
        "D1 is 0x40404040",
        "SR is S,0,0"
    });
}

TEST_F(ASLTest, ASLRegisterLongZeroShiftWorks) {
    Given({
        "D0 is 0x0",
        "D1 is 0x08080808",
        "SR is S,0,XC"
    });
    When({
        "ASL.L D0, D1"
    });
    Then({
        "D1 is 0x08080808",
        "SR is S,0,X"
    });
}

TEST_F(ASLTest, ASLRegisterLongShift32Works) {
    Given({
        "D0 is 0x20",
        "D1 is 0x08080808",
        "SR is S,0,0"
    });
    When({
        "ASL.L D0, D1"
    });
    Then({
        "CYCLES is 72",
        "D1 is 0x00000000",
        "SR is S,0,ZV"
    });
}

TEST_F(ASLTest, ASLRegisterLongShift45Works) {
    Given({
        "D0 is 0x2D",
        "D1 is 0x08080808",
        "SR is S,0,0"
    });
    When({
        "ASL.L D0, D1"
    });
    Then({
        "CYCLES is 98",
        "D1 is 0x00000000",
        "SR is S,0,ZV"
    });
}

TEST_F(ASLTest, ASLRegisterLongShift66Works) {
    Given({
        "D0 is 0x42",
        "D1 is 0x08080808",
        "SR is S,0,0"
    });
    When({
        "ASL.L D0, D1"
    });
    Then({
        "CYCLES is 12",
        "D1 is 0x20202020",
        "SR is S,0,0"
    });
}


TEST_F(ASLTest, ASLMemoryWordWorks) {
    Given({
        "A1 is 0x00002000",
        "(0x2000).W is 0xEDAD",
        "SR is S,0,0"
    });
    When({
        "ASL.W (A1)"
    });
    Then({
        "A1 is 0x00002000",
        "(0x2000).W is 0xDB5A",
        "SR is S,0,XNC"
    });
}

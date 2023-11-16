#include "M68000/Fixtures/M68000Test.h"

class ROXLTest : public M68000Test {};

TEST_F(ROXLTest, ROXLImmediateByteWorks) {
    Given({
        "D1 is 0xFFFFFF00",
        "SR is S,0,X"
    });
    When({
        "ROXL.B #2, D1"
    });
    Then({
        "D1 is 0xFFFFFF02",
        "SR is S,0,0"
    });
}

TEST_F(ROXLTest, ROXLImmediateByteWithNonZeroExtendWorks) {
    Given({
        "D1 is 0xFFFFFFE7",
        "SR is S,0,X"
    });
    When({
        "ROXL.B #4, D1"
    });
    Then({
        "D1 is 0xFFFFFF7F",
        "SR is S,0,0"
    });
}

TEST_F(ROXLTest, ROXLImmediateByteWithZeroExtendWorks) {
    Given({
        "D1 is 0xFFFFFFE7",
        "SR is S,0,0"
    });
    When({
        "ROXL.B #4, D1"
    });
    Then({
        "D1 is 0xFFFFFF77",
        "SR is S,0,0"
    });
}

TEST_F(ROXLTest, ROXLImmediateByteShift8Works) {
    Given({
        "D1 is 0xFFFFFFE7",
        "SR is S,0,X"
    });
    When({
        "ROXL.B #8, D1"
    });
    Then({
        "D1 is 0xFFFFFFF3",
        "SR is S,0,XNC"
    });
}

TEST_F(ROXLTest, ROXLImmediateByteSetsZeroFlag) {
    Given({
        "D1 is 0xFFFFFF00",
        "SR is S,0,0"
    });
    When({
        "ROXL.B #4, D1"
    });
    Then({
        "D1 is 0xFFFFFF00",
        "SR is S,0,Z"
    });
}

TEST_F(ROXLTest, ROXLImmediateWordWorks) {
    Given({
        "D1 is 0xFFFFC808",
        "SR is S,0,X"
    });
    When({
        "ROXL.W #2, D1"
    });
    Then({
        "D1 is 0xFFFF2023",
        "SR is S,0,XC"
    });
}

TEST_F(ROXLTest, ROXLImmediateLongWorks) {
    Given({
        "D1 is 0x88080808",
        "SR is S,0,X"
    });
    When({
        "ROXL.L #3, D1"
    });
    Then({
        "D1 is 0x40404046",
        "SR is S,0,0"
    });
}

TEST_F(ROXLTest, ROXLRegisterByteWorks) {
    Given({
        "D0 is 0x6",
        "D1 is 0xFFFFFFC8",
        "SR is S,0,X"
    });
    When({
        "ROXL.B D0, D1"
    });
    Then({
        "D1 is 0xFFFFFF39",
        "SR is S,0,0"
    });
}

TEST_F(ROXLTest, ROXLRegisterByteZeroShiftWithExtendSetWorks) {
    Given({
        "D0 is 0x0",
        "D1 is 0xFFFFFF08",
        "SR is S,0,X"
    });
    When({
        "ROXL.B D0, D1"
    });
    Then({
        "D1 is 0xFFFFFF08",
        "SR is S,0,XC"
    });
}

TEST_F(ROXLTest, ROXLRegisterByteZeroShiftWithExtendClearWorks) {
    Given({
        "D0 is 0x0",
        "D1 is 0xFFFFFF08",
        "SR is S,0,0"
    });
    When({
        "ROXL.B D0, D1"
    });
    Then({
        "D1 is 0xFFFFFF08",
        "SR is S,0,0"
    });
}

TEST_F(ROXLTest, ROXLRegisterByteShift17Works) {
    Given({
        "D0 is 0x11",
        "D1 is 0xFFFFFFC7",
        "SR is S,0,X"
    });
    When({
        "ROXL.B D0, D1"
    });
    Then({
        "CYCLES is 40",
        "D1 is 0xFFFFFFE3",
        "SR is S,0,XNC"
    });
}

TEST_F(ROXLTest, ROXLRegisterByteShift66Works) {
    Given({
        "D0 is 0x42",
        "D1 is 0xFFFFFF8F",
        "SR is S,0,0"
    });
    When({
        "ROXL.B D0, D1"
    });
    Then({
        "CYCLES is 10",
        "D1 is 0xFFFFFF3D",
        "SR is S,0,0"
    });
}

TEST_F(ROXLTest, ROXLRegisterWordWorks) {
    Given({
        "D0 is 0x2",
        "D1 is 0xFFFF7808",
        "SR is S,0,X"
    });
    When({
        "ROXL.W D0, D1"
    });
    Then({
        "D1 is 0xFFFFE022",
        "SR is S,0,XNC"
    });
}

TEST_F(ROXLTest, ROXLRegisterWordZeroShiftWithExtendedSetWorks) {
    Given({
        "D0 is 0x0",
        "D1 is 0xFFFF0808",
        "SR is S,0,X"
    });
    When({
        "ROXL.W D0, D1"
    });
    Then({
        "D1 is 0xFFFF0808",
        "SR is S,0,XC"
    });
}

TEST_F(ROXLTest, ROXLRegisterWordZeroShiftWithExtendedClearWorks) {
    Given({
        "D0 is 0x0",
        "D1 is 0xFFFF0808",
        "SR is S,0,0"
    });
    When({
        "ROXL.W D0, D1"
    });
    Then({
        "D1 is 0xFFFF0808",
        "SR is S,0,0"
    });
}

TEST_F(ROXLTest, ROXLRegisterWordShift23Works) {
    Given({
        "D0 is 0x17",
        "D1 is 0xFFFFBAAD",
        "SR is S,0,0"
    });
    When({
        "ROXL.W D0, D1"
    });
    Then({
        "CYCLES is 52",
        "D1 is 0xFFFFAB57",
        "SR is S,0,N"
    });
}

TEST_F(ROXLTest, ROXLRegisterWordShift66Works) {
    Given({
        "D0 is 0x42",
        "D1 is 0xFFFF56DD",
        "SR is S,0,0"
    });
    When({
        "ROXL.W D0, D1"
    });
    Then({
        "CYCLES is 10",
        "D1 is 0xFFFF5B74",
        "SR is S,0,XC"
    });
}

TEST_F(ROXLTest, ROXLRegisterLongWorks) {
    Given({
        "D0 is 0x3",
        "D1 is 0x88080808",
        "SR is S,0,X"
    });
    When({
        "ROXL.L D0, D1"
    });
    Then({
        "CYCLES is 14",
        "D1 is 0x40404046",
        "SR is S,0,0"
    });
}

TEST_F(ROXLTest, ROXLRegisterLongZeroShiftWithExtendSetWorks) {
    Given({
        "D0 is 0x0",
        "D1 is 0x08080808",
        "SR is S,0,X"
    });
    When({
        "ROXL.L D0, D1"
    });
    Then({
        "D1 is 0x08080808",
        "SR is S,0,XC"
    });
}

TEST_F(ROXLTest, ROXLRegisterLongZeroShiftWithExtendClearWorks) {
    Given({
        "D0 is 0x0",
        "D1 is 0x08080808",
        "SR is S,0,0"
    });
    When({
        "ROXL.L D0, D1"
    });
    Then({
        "D1 is 0x08080808",
        "SR is S,0,0"
    });
}

TEST_F(ROXLTest, ROXLRegisterLongShift32Works) {
    Given({
        "D0 is 0x20",
        "D1 is 0x88080801",
        "SR is S,0,X"
    });
    When({
        "ROXL.L D0, D1"
    });
    Then({
        "CYCLES is 72",
        "D1 is 0xC4040400",
        "SR is S,0,XNC"
    });
}

TEST_F(ROXLTest, ROXLRegisterLongShift33Works) {
    Given({
        "D0 is 0x21",
        "D1 is 0x88080801",
        "SR is S,0,X"
    });
    When({
        "ROXL.L D0, D1"
    });
    Then({
        "CYCLES is 74",
        "D1 is 0x88080801",
        "SR is S,0,XNC"
    });
}

TEST_F(ROXLTest, ROXLRegisterLongShift34Works) {
    Given({
        "D0 is 0x22",
        "D1 is 0x88080801",
        "SR is S,0,X"
    });
    When({
        "ROXL.L D0, D1"
    });
    Then({
        "CYCLES is 76",
        "D1 is 0x10101003",
        "SR is S,0,XC"
    });
}

TEST_F(ROXLTest, ROXLRegisterLongShift45Works) {
    Given({
        "D0 is 0x2D",
        "D1 is 0x88080808",
        "SR is S,0,0"
    });
    When({
        "ROXL.L D0, D1"
    });
    Then({
        "CYCLES is 98",
        "D1 is 0x80808440",
        "SR is S,0,N"
    });
}

TEST_F(ROXLTest, ROXLRegisterLongShift66Works) {
    Given({
        "D0 is 0x42",
        "D1 is 0x88080808",
        "SR is S,0,0"
    });
    When({
        "ROXL.L D0, D1"
    });
    Then({
        "CYCLES is 12",
        "D1 is 0x20202021",
        "SR is S,0,0"
    });
}

TEST_F(ROXLTest, ROXLMemoryWordWorks) {
    Given({
        "A1 is 0x00002000",
        "(0x2000).W is 0xC003",
        "SR is S,0,X"
    });
    When({
        "ROXL.W (A1)"
    });
    Then({
        "A1 is 0x00002000",
        "(0x2000).W is 0x8007",
        "SR is S,0,XNC"
    });
}

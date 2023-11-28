#include "M68000/Fixtures/M68000Test.h"

class ROXLTest : public M68000Test {};

TEST_F(ROXLTest, ROXLImmediateByteWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0xFFFFFF00",
    });
    When({
        "ROXL.B #2, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFFF02",
    });
}

TEST_F(ROXLTest, ROXLImmediateByteWithNonZeroExtendWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0xFFFFFFE7",
    });
    When({
        "ROXL.B #4, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0xFFFFFF7F",
    });
}

TEST_F(ROXLTest, ROXLImmediateByteWithZeroExtendWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xFFFFFFE7",
    });
    When({
        "ROXL.B #4, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0xFFFFFF77",
    });
}

TEST_F(ROXLTest, ROXLImmediateByteShift8Works) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0xFFFFFFE7",
    });
    When({
        "ROXL.B #8, D1"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 22",
        "D1 is 0xFFFFFFF3",
    });
}

TEST_F(ROXLTest, ROXLImmediateByteSetsZeroFlag) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xFFFFFF00",
    });
    When({
        "ROXL.B #4, D1"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0xFFFFFF00",
    });
}

TEST_F(ROXLTest, ROXLImmediateWordWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0xFFFFC808",
    });
    When({
        "ROXL.W #2, D1"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFF2023",
    });
}

TEST_F(ROXLTest, ROXLImmediateLongWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0x88080808",
    });
    When({
        "ROXL.L #3, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x40404046",
    });
}

TEST_F(ROXLTest, ROXLRegisterByteWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D0 is 0x6",
        "D1 is 0xFFFFFFC8",
    });
    When({
        "ROXL.B D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 18",
        "D1 is 0xFFFFFF39",
    });
}

TEST_F(ROXLTest, ROXLRegisterByteZeroShiftWithExtendSetWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D0 is 0x0",
        "D1 is 0xFFFFFF08",
    });
    When({
        "ROXL.B D0, D1"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0xFFFFFF08",
    });
}

TEST_F(ROXLTest, ROXLRegisterByteZeroShiftWithExtendClearWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x0",
        "D1 is 0xFFFFFF08",
    });
    When({
        "ROXL.B D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0xFFFFFF08",
    });
}

TEST_F(ROXLTest, ROXLRegisterByteShift17Works) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D0 is 0x11",
        "D1 is 0xFFFFFFC7",
    });
    When({
        "ROXL.B D0, D1"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 40",
        "D1 is 0xFFFFFFE3",
    });
}

TEST_F(ROXLTest, ROXLRegisterByteShift66Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x42",
        "D1 is 0xFFFFFF8F",
    });
    When({
        "ROXL.B D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFFF3D",
    });
}

TEST_F(ROXLTest, ROXLRegisterWordWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D0 is 0x2",
        "D1 is 0xFFFF7808",
    });
    When({
        "ROXL.W D0, D1"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFE022",
    });
}

TEST_F(ROXLTest, ROXLRegisterWordZeroShiftWithExtendedSetWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D0 is 0x0",
        "D1 is 0xFFFF0808",
    });
    When({
        "ROXL.W D0, D1"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0xFFFF0808",
    });
}

TEST_F(ROXLTest, ROXLRegisterWordZeroShiftWithExtendedClearWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x0",
        "D1 is 0xFFFF0808",
    });
    When({
        "ROXL.W D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0xFFFF0808",
    });
}

TEST_F(ROXLTest, ROXLRegisterWordShift23Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x17",
        "D1 is 0xFFFFBAAD",
    });
    When({
        "ROXL.W D0, D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 52",
        "D1 is 0xFFFFAB57",
    });
}

TEST_F(ROXLTest, ROXLRegisterWordShift66Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x42",
        "D1 is 0xFFFF56DD",
    });
    When({
        "ROXL.W D0, D1"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFF5B74",
    });
}

TEST_F(ROXLTest, ROXLRegisterLongWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D0 is 0x3",
        "D1 is 0x88080808",
    });
    When({
        "ROXL.L D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x40404046",
    });
}

TEST_F(ROXLTest, ROXLRegisterLongZeroShiftWithExtendSetWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D0 is 0x0",
        "D1 is 0x08080808",
    });
    When({
        "ROXL.L D0, D1"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x08080808",
    });
}

TEST_F(ROXLTest, ROXLRegisterLongZeroShiftWithExtendClearWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x0",
        "D1 is 0x08080808",
    });
    When({
        "ROXL.L D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x08080808",
    });
}

TEST_F(ROXLTest, ROXLRegisterLongShift32Works) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D0 is 0x20",
        "D1 is 0x88080801",
    });
    When({
        "ROXL.L D0, D1"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 72",
        "D1 is 0xC4040400",
    });
}

TEST_F(ROXLTest, ROXLRegisterLongShift33Works) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D0 is 0x21",
        "D1 is 0x88080801",
    });
    When({
        "ROXL.L D0, D1"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 74",
        "D1 is 0x88080801",
    });
}

TEST_F(ROXLTest, ROXLRegisterLongShift34Works) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D0 is 0x22",
        "D1 is 0x88080801",
    });
    When({
        "ROXL.L D0, D1"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 76",
        "D1 is 0x10101003",
    });
}

TEST_F(ROXLTest, ROXLRegisterLongShift45Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x2D",
        "D1 is 0x88080808",
    });
    When({
        "ROXL.L D0, D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 98",
        "D1 is 0x80808440",
    });
}

TEST_F(ROXLTest, ROXLRegisterLongShift66Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x42",
        "D1 is 0x88080808",
    });
    When({
        "ROXL.L D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x20202021",
    });
}

TEST_F(ROXLTest, ROXLMemoryWordWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "A1 is 0x00002000",
        "(0x2000).W is 0xC003",
    });
    When({
        "ROXL.W (A1)"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 12",
        "A1 is 0x00002000",
        "(0x2000).W is 0x8007",
    });
}

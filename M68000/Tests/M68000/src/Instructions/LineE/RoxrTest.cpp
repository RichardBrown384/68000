#include "M68000/Fixtures/M68000Test.h"

class ROXRTest : public M68000Test {};

TEST_F(ROXRTest, ROXRImmediateByteWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0xFFFFFF00",
    });
    When({
        "ROXR.B #2, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFFF40",
    });
}

TEST_F(ROXRTest, ROXRImmediateByteWithNonZeroExtendWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0xFFFFFFE7",
    });
    When({
        "ROXR.B #4, D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0xFFFFFFFE",
    });
}

TEST_F(ROXRTest, ROXRImmediateByteWithZeroExtendWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xFFFFFFE7",
    });
    When({
        "ROXR.B #4, D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0xFFFFFFEE",
    });
}

TEST_F(ROXRTest, ROXRImmediateByteShift8Works) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0xFFFFFFE7",
    });
    When({
        "ROXR.B #8, D1"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 22",
        "D1 is 0xFFFFFFCF",
    });
}

TEST_F(ROXRTest, ROXRImmediateByteSetsZeroFlag) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xFFFFFF08",
    });
    When({
        "ROXR.B #4, D1"
    });
    Then({
        "SR is S,0,XZC",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0xFFFFFF00",
    });
}

TEST_F(ROXRTest, ROXRImmediateWordWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0xFFFFC808",
    });
    When({
        "ROXR.W #2, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFF7202",
    });
}

TEST_F(ROXRTest, ROXRImmediateLongWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0x88080808",
    });
    When({
        "ROXR.L #3, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x31010101",
    });
}

TEST_F(ROXRTest, ROXRRegisterByteWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D0 is 0x6",
        "D1 is 0xFFFFFFC8",
    });
    When({
        "ROXR.B D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 18",
        "D1 is 0xFFFFFF47",
    });
}

TEST_F(ROXRTest, ROXRRegisterByteZeroShiftWithExtendSetWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D0 is 0x0",
        "D1 is 0xFFFFFF08",
    });
    When({
        "ROXR.B D0, D1"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0xFFFFFF08",
    });
}

TEST_F(ROXRTest, ROXRRegisterByteZeroShiftWithExtendClearWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x0",
        "D1 is 0xFFFFFF08",
    });
    When({
        "ROXR.B D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0xFFFFFF08",
    });
}

TEST_F(ROXRTest, ROXRRegisterByteShift17Works) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D0 is 0x11",
        "D1 is 0xFFFFFFC7",
    });
    When({
        "ROXR.B D0, D1"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 40",
        "D1 is 0xFFFFFF8F",
    });
}

TEST_F(ROXRTest, ROXRRegisterByteShift66Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x42",
        "D1 is 0xFFFFFF8F",
    });
    When({
        "ROXR.B D0, D1"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFFFA3",
    });
}

TEST_F(ROXRTest, ROXRRegisterWordWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D0 is 0x2",
        "D1 is 0xFFFF7808",
    });
    When({
        "ROXR.W D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFF5E02",
    });
}

TEST_F(ROXRTest, ROXRRegisterWordZeroShiftWithExtendedSetWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D0 is 0x0",
        "D1 is 0xFFFF0808",
    });
    When({
        "ROXR.W D0, D1"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0xFFFF0808",
    });
}

TEST_F(ROXRTest, ROXRRegisterWordZeroShiftWithExtendedClearWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x0",
        "D1 is 0xFFFF0808",
    });
    When({
        "ROXR.W D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0xFFFF0808",
    });
}

TEST_F(ROXRTest, ROXRRegisterWordShift23Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x17",
        "D1 is 0xFFFFBAAD",
    });
    When({
        "ROXR.W D0, D1"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 52",
        "D1 is 0xFFFF6AEA",
    });
}

TEST_F(ROXRTest, ROXRRegisterWordShift66Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x42",
        "D1 is 0xFFFF56DD",
    });
    When({
        "ROXR.W D0, D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFF95B7",
    });
}

TEST_F(ROXRTest, ROXRRegisterLongWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D0 is 0x3",
        "D1 is 0x88080808",
    });
    When({
        "ROXR.L D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x31010101",
    });
}

TEST_F(ROXRTest, ROXRRegisterLongZeroShiftWithExtendSetWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D0 is 0x0",
        "D1 is 0x08080808",
    });
    When({
        "ROXR.L D0, D1"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x08080808",
    });
}

TEST_F(ROXRTest, ROXRRegisterLongZeroShiftWithExtendClearWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x0",
        "D1 is 0x08080808",
    });
    When({
        "ROXR.L D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x08080808",
    });
}

TEST_F(ROXRTest, ROXRRegisterLongShift32Works) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D0 is 0x20",
        "D1 is 0x88080801",
    });
    When({
        "ROXR.L D0, D1"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 72",
        "D1 is 0x10101003",
    });
}

TEST_F(ROXRTest, ROXRRegisterLongShift33Works) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D0 is 0x21",
        "D1 is 0x88080801",
    });
    When({
        "ROXR.L D0, D1"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 74",
        "D1 is 0x88080801",
    });
}

TEST_F(ROXRTest, ROXRRegisterLongShift34Works) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D0 is 0x22",
        "D1 is 0x88080801",
    });
    When({
        "ROXR.L D0, D1"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 76",
        "D1 is 0xC4040400",
    });
}

TEST_F(ROXRTest, ROXRRegisterLongShift45Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x2D",
        "D1 is 0x88080808",
    });
    When({
        "ROXR.L D0, D1"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 98",
        "D1 is 0x01088080",
    });
}

TEST_F(ROXRTest, ROXRRegisterLongShift66Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x42",
        "D1 is 0x88080808",
    });
    When({
        "ROXR.L D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x22020202",
    });
}

TEST_F(ROXRTest, ROXRMemoryWordWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "A1 is 0x00002000",
        "(0x2000).W is 0xC003",
    });
    When({
        "ROXR.W (A1)"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 12",
        "A1 is 0x00002000",
        "(0x2000).W is 0xE001",
    });
}

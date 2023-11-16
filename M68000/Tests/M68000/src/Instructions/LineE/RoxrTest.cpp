#include "M68000/Fixtures/M68000Test.h"

class ROXRTest : public M68000Test {};

TEST_F(ROXRTest, ROXRImmediateByteWorks) {
    Given({
        "D1 is 0xFFFFFF00",
        "SR is S,0,X"
    });
    When({
        "ROXR.B #2, D1"
    });
    Then({
        "D1 is 0xFFFFFF40",
        "SR is S,0,0"
    });
}

TEST_F(ROXRTest, ROXRImmediateByteWithNonZeroExtendWorks) {
    Given({
        "D1 is 0xFFFFFFE7",
        "SR is S,0,X"
    });
    When({
        "ROXR.B #4, D1"
    });
    Then({
        "D1 is 0xFFFFFFFE",
        "SR is S,0,N"
    });
}

TEST_F(ROXRTest, ROXRImmediateByteWithZeroExtendWorks) {
    Given({
        "D1 is 0xFFFFFFE7",
        "SR is S,0,0"
    });
    When({
        "ROXR.B #4, D1"
    });
    Then({
        "D1 is 0xFFFFFFEE",
        "SR is S,0,N"
    });
}

TEST_F(ROXRTest, ROXRImmediateByteShift8Works) {
    Given({
        "D1 is 0xFFFFFFE7",
        "SR is S,0,X"
    });
    When({
        "ROXR.B #8, D1"
    });
    Then({
        "D1 is 0xFFFFFFCF",
        "SR is S,0,XNC"
    });
}

TEST_F(ROXRTest, ROXRImmediateByteSetsZeroFlag) {
    Given({
        "D1 is 0xFFFFFF08",
        "SR is S,0,0"
    });
    When({
        "ROXR.B #4, D1"
    });
    Then({
        "D1 is 0xFFFFFF00",
        "SR is S,0,XZC"
    });
}

TEST_F(ROXRTest, ROXRImmediateWordWorks) {
    Given({
        "D1 is 0xFFFFC808",
        "SR is S,0,X"
    });
    When({
        "ROXR.W #2, D1"
    });
    Then({
        "D1 is 0xFFFF7202",
        "SR is S,0,0"
    });
}

TEST_F(ROXRTest, ROXRImmediateLongWorks) {
    Given({
        "D1 is 0x88080808",
        "SR is S,0,X"
    });
    When({
        "ROXR.L #3, D1"
    });
    Then({
        "D1 is 0x31010101",
        "SR is S,0,0"
    });
}

TEST_F(ROXRTest, ROXRRegisterByteWorks) {
    Given({
        "D0 is 0x6",
        "D1 is 0xFFFFFFC8",
        "SR is S,0,X"
    });
    When({
        "ROXR.B D0, D1"
    });
    Then({
        "D1 is 0xFFFFFF47",
        "SR is S,0,0"
    });
}

TEST_F(ROXRTest, ROXRRegisterByteZeroShiftWithExtendSetWorks) {
    Given({
        "D0 is 0x0",
        "D1 is 0xFFFFFF08",
        "SR is S,0,X"
    });
    When({
        "ROXR.B D0, D1"
    });
    Then({
        "D1 is 0xFFFFFF08",
        "SR is S,0,XC"
    });
}

TEST_F(ROXRTest, ROXRRegisterByteZeroShiftWithExtendClearWorks) {
    Given({
        "D0 is 0x0",
        "D1 is 0xFFFFFF08",
        "SR is S,0,0"
    });
    When({
        "ROXR.B D0, D1"
    });
    Then({
        "D1 is 0xFFFFFF08",
        "SR is S,0,0"
    });
}

TEST_F(ROXRTest, ROXRRegisterByteShift17Works) {
    Given({
        "D0 is 0x11",
        "D1 is 0xFFFFFFC7",
        "SR is S,0,X"
    });
    When({
        "ROXR.B D0, D1"
    });
    Then({
        "CYCLES is 40",
        "D1 is 0xFFFFFF8F",
        "SR is S,0,XNC"
    });
}

TEST_F(ROXRTest, ROXRRegisterByteShift66Works) {
    Given({
        "D0 is 0x42",
        "D1 is 0xFFFFFF8F",
        "SR is S,0,0"
    });
    When({
        "ROXR.B D0, D1"
    });
    Then({
        "CYCLES is 10",
        "D1 is 0xFFFFFFA3",
        "SR is S,0,XNC"
    });
}

TEST_F(ROXRTest, ROXRRegisterWordWorks) {
    Given({
        "D0 is 0x2",
        "D1 is 0xFFFF7808",
        "SR is S,0,X"
    });
    When({
        "ROXR.W D0, D1"
    });
    Then({
        "D1 is 0xFFFF5E02",
        "SR is S,0,0"
    });
}

TEST_F(ROXRTest, ROXRRegisterWordZeroShiftWithExtendedSetWorks) {
    Given({
        "D0 is 0x0",
        "D1 is 0xFFFF0808",
        "SR is S,0,X"
    });
    When({
        "ROXR.W D0, D1"
    });
    Then({
        "D1 is 0xFFFF0808",
        "SR is S,0,XC"
    });
}

TEST_F(ROXRTest, ROXRRegisterWordZeroShiftWithExtendedClearWorks) {
    Given({
        "D0 is 0x0",
        "D1 is 0xFFFF0808",
        "SR is S,0,0"
    });
    When({
        "ROXR.W D0, D1"
    });
    Then({
        "D1 is 0xFFFF0808",
        "SR is S,0,0"
    });
}

TEST_F(ROXRTest, ROXRRegisterWordShift23Works) {
    Given({
        "D0 is 0x17",
        "D1 is 0xFFFFBAAD",
        "SR is S,0,0"
    });
    When({
        "ROXR.W D0, D1"
    });
    Then({
        "CYCLES is 52",
        "D1 is 0xFFFF6AEA",
        "SR is S,0,XC"
    });
}

TEST_F(ROXRTest, ROXRRegisterWordShift66Works) {
    Given({
        "D0 is 0x42",
        "D1 is 0xFFFF56DD",
        "SR is S,0,0"
    });
    When({
        "ROXR.W D0, D1"
    });
    Then({
        "CYCLES is 10",
        "D1 is 0xFFFF95B7",
        "SR is S,0,N"
    });
}

TEST_F(ROXRTest, ROXRRegisterLongWorks) {
    Given({
        "D0 is 0x3",
        "D1 is 0x88080808",
        "SR is S,0,X"
    });
    When({
        "ROXR.L D0, D1"
    });
    Then({
        "CYCLES is 14",
        "D1 is 0x31010101",
        "SR is S,0,0"
    });
}

TEST_F(ROXRTest, ROXRRegisterLongZeroShiftWithExtendSetWorks) {
    Given({
        "D0 is 0x0",
        "D1 is 0x08080808",
        "SR is S,0,X"
    });
    When({
        "ROXR.L D0, D1"
    });
    Then({
        "D1 is 0x08080808",
        "SR is S,0,XC"
    });
}

TEST_F(ROXRTest, ROXRRegisterLongZeroShiftWithExtendClearWorks) {
    Given({
        "D0 is 0x0",
        "D1 is 0x08080808",
        "SR is S,0,0"
    });
    When({
        "ROXR.L D0, D1"
    });
    Then({
        "D1 is 0x08080808",
        "SR is S,0,0"
    });
}

TEST_F(ROXRTest, ROXRRegisterLongShift32Works) {
    Given({
        "D0 is 0x20",
        "D1 is 0x88080801",
        "SR is S,0,X"
    });
    When({
        "ROXR.L D0, D1"
    });
    Then({
        "CYCLES is 72",
        "D1 is 0x10101003",
        "SR is S,0,XC"
    });
}

TEST_F(ROXRTest, ROXRRegisterLongShift33Works) {
    Given({
        "D0 is 0x21",
        "D1 is 0x88080801",
        "SR is S,0,X"
    });
    When({
        "ROXR.L D0, D1"
    });
    Then({
        "CYCLES is 74",
        "D1 is 0x88080801",
        "SR is S,0,XNC"
    });
}

TEST_F(ROXRTest, ROXRRegisterLongShift34Works) {
    Given({
        "D0 is 0x22",
        "D1 is 0x88080801",
        "SR is S,0,X"
    });
    When({
        "ROXR.L D0, D1"
    });
    Then({
        "CYCLES is 76",
        "D1 is 0xC4040400",
        "SR is S,0,XNC"
    });
}

TEST_F(ROXRTest, ROXRRegisterLongShift45Works) {
    Given({
        "D0 is 0x2D",
        "D1 is 0x88080808",
        "SR is S,0,0"
    });
    When({
        "ROXR.L D0, D1"
    });
    Then({
        "CYCLES is 98",
        "D1 is 0x01088080",
        "SR is S,0,XC"
    });
}

TEST_F(ROXRTest, ROXRRegisterLongShift66Works) {
    Given({
        "D0 is 0x42",
        "D1 is 0x88080808",
        "SR is S,0,0"
    });
    When({
        "ROXR.L D0, D1"
    });
    Then({
        "CYCLES is 12",
        "D1 is 0x22020202",
        "SR is S,0,0"
    });
}

TEST_F(ROXRTest, ROXRMemoryWordWorks) {
    Given({
        "A1 is 0x00002000",
        "(0x2000).W is 0xC003",
        "SR is S,0,X"
    });
    When({
        "ROXR.W (A1)"
    });
    Then({
        "A1 is 0x00002000",
        "(0x2000).W is 0xE001",
        "SR is S,0,XNC"
    });
}

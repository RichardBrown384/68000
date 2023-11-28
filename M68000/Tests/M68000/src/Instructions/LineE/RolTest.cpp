#include "M68000/Fixtures/M68000Test.h"

class ROLTest : public M68000Test {};

TEST_F(ROLTest, ROLImmediateByteWorks) {
    Given({
        "SR is S,0,XV",
        "PC is 0x1000",
        "D1 is 0xFFFFFFC8",
    });
    When({
        "ROL.B #2, D1"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFFF23",
    });
}

TEST_F(ROLTest, ROLImmediateByteSetsCarryAndNegativeFlags) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xFFFFFFC1",
    });
    When({
        "ROL.B #1, D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0xFFFFFF83",
    });
}

TEST_F(ROLTest, ROLImmediateByteSetsZeroFlag) {
    Given({
        "SR is S,0,XV",
        "PC is 0x1000",
        "D1 is 0xFFFFFF00",
    });
    When({
        "ROL.B #2, D1"
    });
    Then({
        "SR is S,0,XZ",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFFF00",
    });
}

TEST_F(ROLTest, ROLImmediateWordWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xFFFFC808",
    });
    When({
        "ROL.W #2, D1"
    });
    Then({
        "SR is S,0,C",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFF2023",
    });
}

TEST_F(ROLTest, ROLImmediateLongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x88080808",
    });
    When({
        "ROL.L #3, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x40404044",
    });
}

TEST_F(ROLTest, ROLRegisterByteWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x2",
        "D1 is 0xFFFFFFC8",
    });
    When({
        "ROL.B D0, D1"
    });
    Then({
        "SR is S,0,C",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFFF23",
    });
}

TEST_F(ROLTest, ROLRegisterByteZeroShiftWorks) {
    Given({
        "SR is S,0,XC",
        "PC is 0x1000",
        "D0 is 0x0",
        "D1 is 0xFFFFFF08",
    });
    When({
        "ROL.B D0, D1"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0xFFFFFF08",
    });
}

TEST_F(ROLTest, ROLRegisterByteShift17Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x11",
        "D1 is 0xFFFFFFC7",
    });
    When({
        "ROL.B D0, D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1002",
        "CYCLES is 40",
        "D1 is 0xFFFFFF8F",
    });
}

TEST_F(ROLTest, ROLRegisterByteShift66Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x42",
        "D1 is 0xFFFFFF8F",
    });
    When({
        "ROL.B D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFFF3E",
    });
}

TEST_F(ROLTest, ROLRegisterWordWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x2",
        "D1 is 0xFFFFF808",
    });
    When({
        "ROL.W D0, D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFE023",
    });
}

TEST_F(ROLTest, ROLRegisterWordZeroShiftWorks) {
    Given({
        "SR is S,0,XC",
        "PC is 0x1000",
        "D0 is 0x0",
        "D1 is 0xFFFF0808",
    });
    When({
        "ROL.W D0, D1"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0xFFFF0808",
    });
}

TEST_F(ROLTest, ROLRegisterWordShift23Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x17",
        "D1 is 0xFFFFBAAD",
    });
    When({
        "ROL.W D0, D1"
    });
    Then({
        "SR is S,0,C",
        "PC is 0x1002",
        "CYCLES is 52",
        "D1 is 0xFFFF56DD",
    });
}

TEST_F(ROLTest, ROLRegisterWordShift66Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x42",
        "D1 is 0xFFFF56DD",
    });
    When({
        "ROL.W D0, D1"
    });
    Then({
        "SR is S,0,C",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFF5B75",
    });
}

TEST_F(ROLTest, ROLRegisterLongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x3",
        "D1 is 0x88080808",
    });
    When({
        "ROL.L D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x40404044",
    });
}

TEST_F(ROLTest, ROLRegisterLongZeroShiftWorks) {
    Given({
        "SR is S,0,XC",
        "PC is 0x1000",
        "D0 is 0x0",
        "D1 is 0x08080808",
    });
    When({
        "ROL.L D0, D1"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x08080808",
    });
}

TEST_F(ROLTest, ROLRegisterLongShift32Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x20",
        "D1 is 0x88080801",
    });
    When({
        "ROL.L D0, D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1002",
        "CYCLES is 72",
        "D1 is 0x88080801",
    });
}

TEST_F(ROLTest, ROLRegisterLongShift32WorksNoCarry) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x20",
        "D1 is 0x88080800",
    });
    When({
        "ROL.L D0, D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 72",
        "D1 is 0x88080800",
    });
}

TEST_F(ROLTest, ROLRegisterLongShift45Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x2D",
        "D1 is 0x88080808",
    });
    When({
        "ROL.L D0, D1"
    });
    Then({
        "SR is S,0,C",
        "PC is 0x1002",
        "CYCLES is 98",
        "D1 is 0x01011101",
    });
}

TEST_F(ROLTest, ROLRegisterLongShift66Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x42",
        "D1 is 0x88080808",
    });
    When({
        "ROL.L D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x20202022",
    });
}

TEST_F(ROLTest, ROLMemoryWordWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00002000",
        "(0x2000).W is 0xC003",
    });
    When({
        "ROL.W (A1)"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1002",
        "CYCLES is 12",
        "A1 is 0x00002000",
        "(0x2000).W is 0x8007",
    });
}

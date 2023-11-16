#include "M68000/Fixtures/M68000Test.h"

class ROLTest : public M68000Test {};

TEST_F(ROLTest, ROLImmediateByteWorks) {
    Given({
        "D1 is 0xFFFFFFC8",
        "SR is S,0,XV"
    });
    When({
        "ROL.B #2, D1"
    });
    Then({
        "D1 is 0xFFFFFF23",
        "SR is S,0,XC"
    });
}

TEST_F(ROLTest, ROLImmediateByteSetsCarryAndNegativeFlags) {
    Given({
        "D1 is 0xFFFFFFC1",
        "SR is S,0,0"
    });
    When({
        "ROL.B #1, D1"
    });
    Then({
        "D1 is 0xFFFFFF83",
        "SR is S,0,NC"
    });
}

TEST_F(ROLTest, ROLImmediateByteSetsZeroFlag) {
    Given({
        "D1 is 0xFFFFFF00",
        "SR is S,0,XV"
    });
    When({
        "ROL.B #2, D1"
    });
    Then({
        "D1 is 0xFFFFFF00",
        "SR is S,0,XZ"
    });
}

TEST_F(ROLTest, ROLImmediateWordWorks) {
    Given({
        "D1 is 0xFFFFC808",
        "SR is S,0,0"
    });
    When({
        "ROL.W #2, D1"
    });
    Then({
        "D1 is 0xFFFF2023",
        "SR is S,0,C"
    });
}

TEST_F(ROLTest, ROLImmediateLongWorks) {
    Given({
        "D1 is 0x88080808",
        "SR is S,0,0"
    });
    When({
        "ROL.L #3, D1"
    });
    Then({
        "D1 is 0x40404044",
        "SR is S,0,0"
    });
}

TEST_F(ROLTest, ROLRegisterByteWorks) {
    Given({
        "D0 is 0x2",
        "D1 is 0xFFFFFFC8",
        "SR is S,0,0"
    });
    When({
        "ROL.B D0, D1"
    });
    Then({
        "D1 is 0xFFFFFF23",
        "SR is S,0,C"
    });
}

TEST_F(ROLTest, ROLRegisterByteZeroShiftWorks) {
    Given({
        "D0 is 0x0",
        "D1 is 0xFFFFFF08",
        "SR is S,0,XC"
    });
    When({
        "ROL.B D0, D1"
    });
    Then({
        "D1 is 0xFFFFFF08",
        "SR is S,0,X"
    });
}

TEST_F(ROLTest, ROLRegisterByteShift17Works) {
    Given({
        "D0 is 0x11",
        "D1 is 0xFFFFFFC7",
        "SR is S,0,0"
    });
    When({
        "ROL.B D0, D1"
    });
    Then({
        "CYCLES is 40",
        "D1 is 0xFFFFFF8F",
        "SR is S,0,NC"
    });
}

TEST_F(ROLTest, ROLRegisterByteShift66Works) {
    Given({
        "D0 is 0x42",
        "D1 is 0xFFFFFF8F",
        "SR is S,0,0"
    });
    When({
        "ROL.B D0, D1"
    });
    Then({
        "CYCLES is 10",
        "D1 is 0xFFFFFF3E",
        "SR is S,0,0"
    });
}

TEST_F(ROLTest, ROLRegisterWordWorks) {
    Given({
        "D0 is 0x2",
        "D1 is 0xFFFFF808",
        "SR is S,0,0"
    });
    When({
        "ROL.W D0, D1"
    });
    Then({
        "D1 is 0xFFFFE023",
        "SR is S,0,NC"
    });
}

TEST_F(ROLTest, ROLRegisterWordZeroShiftWorks) {
    Given({
        "D0 is 0x0",
        "D1 is 0xFFFF0808",
        "SR is S,0,XC"
    });
    When({
        "ROL.W D0, D1"
    });
    Then({
        "D1 is 0xFFFF0808",
        "SR is S,0,X"
    });
}

TEST_F(ROLTest, ROLRegisterWordShift23Works) {
    Given({
        "D0 is 0x17",
        "D1 is 0xFFFFBAAD",
        "SR is S,0,0"
    });
    When({
        "ROL.W D0, D1"
    });
    Then({
        "CYCLES is 52",
        "D1 is 0xFFFF56DD",
        "SR is S,0,C"
    });
}

TEST_F(ROLTest, ROLRegisterWordShift66Works) {
    Given({
        "D0 is 0x42",
        "D1 is 0xFFFF56DD",
        "SR is S,0,0"
    });
    When({
        "ROL.W D0, D1"
    });
    Then({
        "CYCLES is 10",
        "D1 is 0xFFFF5B75",
        "SR is S,0,C"
    });
}

TEST_F(ROLTest, ROLRegisterLongWorks) {
    Given({
        "D0 is 0x3",
        "D1 is 0x88080808",
        "SR is S,0,0"
    });
    When({
        "ROL.L D0, D1"
    });
    Then({
        "CYCLES is 14",
        "D1 is 0x40404044",
        "SR is S,0,0"
    });
}

TEST_F(ROLTest, ROLRegisterLongZeroShiftWorks) {
    Given({
        "D0 is 0x0",
        "D1 is 0x08080808",
        "SR is S,0,XC"
    });
    When({
        "ROL.L D0, D1"
    });
    Then({
        "D1 is 0x08080808",
        "SR is S,0,X"
    });
}

TEST_F(ROLTest, ROLRegisterLongShift32Works) {
    Given({
        "D0 is 0x20",
        "D1 is 0x88080801",
        "SR is S,0,0"
    });
    When({
        "ROL.L D0, D1"
    });
    Then({
        "CYCLES is 72",
        "D1 is 0x88080801",
        "SR is S,0,NC"
    });
}

TEST_F(ROLTest, ROLRegisterLongShift32WorksNoCarry) {
    Given({
        "D0 is 0x20",
        "D1 is 0x88080800",
        "SR is S,0,0"
    });
    When({
        "ROL.L D0, D1"
    });
    Then({
        "CYCLES is 72",
        "D1 is 0x88080800",
        "SR is S,0,N"
    });
}

TEST_F(ROLTest, ROLRegisterLongShift45Works) {
    Given({
        "D0 is 0x2D",
        "D1 is 0x88080808",
        "SR is S,0,0"
    });
    When({
        "ROL.L D0, D1"
    });
    Then({
        "CYCLES is 98",
        "D1 is 0x01011101",
        "SR is S,0,C"
    });
}

TEST_F(ROLTest, ROLRegisterLongShift66Works) {
    Given({
        "D0 is 0x42",
        "D1 is 0x88080808",
        "SR is S,0,0"
    });
    When({
        "ROL.L D0, D1"
    });
    Then({
        "CYCLES is 12",
        "D1 is 0x20202022",
        "SR is S,0,0"
    });
}

TEST_F(ROLTest, ROLMemoryWordWorks) {
    Given({
        "A1 is 0x00002000",
        "(0x2000).W is 0xC003",
        "SR is S,0,0"
    });
    When({
        "ROL.W (A1)"
    });
    Then({
        "A1 is 0x00002000",
        "(0x2000).W is 0x8007",
        "SR is S,0,NC"
    });
}

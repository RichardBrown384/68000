#include "M68000/Fixtures/M68000Test.h"

class RORTest : public M68000Test {};

TEST_F(RORTest, RORImmediateByteWorks) {
    Given({
        "D1 is 0xFFFFFFC1",
        "SR is S,0,XV"
    });
    When({
        "ROR.B #2, D1"
    });
    Then({
        "D1 is 0xFFFFFF70",
        "SR is S,0,X"
    });
}

TEST_F(RORTest, RORImmediateByteSetsCarryAndNegativeFlags) {
    Given({
        "D1 is 0xFFFFFFC1",
        "SR is S,0,0"
    });
    When({
        "ROR.B #1, D1"
    });
    Then({
        "D1 is 0xFFFFFFE0",
        "SR is S,0,NC"
    });
}

TEST_F(RORTest, RORImmediateByteSetsZeroFlag) {
    Given({
        "D1 is 0xFFFFFF00",
        "SR is S,0,XV"
    });
    When({
        "ROR.B #2, D1"
    });
    Then({
        "D1 is 0xFFFFFF00",
        "SR is S,0,XZ"
    });
}

TEST_F(RORTest, RORImmediateWordWorks) {
    Given({
        "D1 is 0xFFFFC808",
        "SR is S,0,0"
    });
    When({
        "ROR.W #2, D1"
    });
    Then({
        "D1 is 0xFFFF3202",
        "SR is S,0,0"
    });
}

TEST_F(RORTest, RORImmediateLongWorks) {
    Given({
        "D1 is 0x08080888",
        "SR is S,0,0"
    });
    When({
        "ROR.L #7, D1"
    });
    Then({
        "D1 is 0x10101011",
        "SR is S,0,0"
    });
}

TEST_F(RORTest, RORRegisterByteWorks) {
    Given({
        "D0 is 0x2",
        "D1 is 0xFFFFFFC1",
        "SR is S,0,0"
    });
    When({
        "ROR.B D0, D1"
    });
    Then({
        "D1 is 0xFFFFFF70",
        "SR is S,0,0"
    });
}

TEST_F(RORTest, RORRegisterByteZeroShiftWorks) {
    Given({
        "D0 is 0x0",
        "D1 is 0xFFFFFF08",
        "SR is S,0,XC"
    });
    When({
        "ROR.B D0, D1"
    });
    Then({
        "D1 is 0xFFFFFF08",
        "SR is S,0,X"
    });
}

TEST_F(RORTest, RORRegisterByteShift17Works) {
    Given({
        "D0 is 0x11",
        "D1 is 0xFFFFFFC7",
        "SR is S,0,0"
    });
    When({
        "ROR.B D0, D1"
    });
    Then({
        "CYCLES is 40",
        "D1 is 0xFFFFFFE3",
        "SR is S,0,NC"
    });
}

TEST_F(RORTest, RORRegisterByteShift66Works) {
    Given({
        "D0 is 0x42",
        "D1 is 0xFFFFFF81",
        "SR is S,0,0"
    });
    When({
        "ROR.B D0, D1"
    });
    Then({
        "CYCLES is 10",
        "D1 is 0xFFFFFF60",
        "SR is S,0,0"
    });
}

TEST_F(RORTest, RORRegisterWordWorks) {
    Given({
        "D0 is 0x2",
        "D1 is 0xFFFF807F",
        "SR is S,0,0"
    });
    When({
        "ROR.W D0, D1"
    });
    Then({
        "D1 is 0xFFFFE01F",
        "SR is S,0,NC"
    });
}

TEST_F(RORTest, RORRegisterWordZeroShiftWorks) {
    Given({
        "D0 is 0x0",
        "D1 is 0xFFFF0808",
        "SR is S,0,XC"
    });
    When({
        "ROR.W D0, D1"
    });
    Then({
        "D1 is 0xFFFF0808",
        "SR is S,0,X"
    });
}

TEST_F(RORTest, RORRegisterWordShift23Works) {
    Given({
        "D0 is 0x17",
        "D1 is 0xFFFFBAAD",
        "SR is S,0,0"
    });
    When({
        "ROR.W D0, D1"
    });
    Then({
        "CYCLES is 52",
        "D1 is 0xFFFF5B75",
        "SR is S,0,0"
    });
}

TEST_F(RORTest, RORRegisterWordShift66Works) {
    Given({
        "D0 is 0x42",
        "D1 is 0xFFFF56DD",
        "SR is S,0,0"
    });
    When({
        "ROR.W D0, D1"
    });
    Then({
        "CYCLES is 10",
        "D1 is 0xFFFF55B7",
        "SR is S,0,0"
    });
}

TEST_F(RORTest, RORRegisterLongWorks) {
    Given({
        "D0 is 0x3",
        "D1 is 0x88080808",
        "SR is S,0,0"
    });
    When({
        "ROR.L D0, D1"
    });
    Then({
        "CYCLES is 14",
        "D1 is 0x11010101",
        "SR is S,0,0"
    });
}

TEST_F(RORTest, RORRegisterLongZeroShiftWorks) {
    Given({
        "D0 is 0x0",
        "D1 is 0x08080808",
        "SR is S,0,XC"
    });
    When({
        "ROR.L D0, D1"
    });
    Then({
        "D1 is 0x08080808",
        "SR is S,0,X"
    });
}

TEST_F(RORTest, RORRegisterLongShift32Works) {
    Given({
        "D0 is 0x20",
        "D1 is 0x88080801",
        "SR is S,0,0"
    });
    When({
        "ROR.L D0, D1"
    });
    Then({
        "CYCLES is 72",
        "D1 is 0x88080801",
        "SR is S,0,NC"
    });
}

TEST_F(RORTest, RORRegisterLongShift32WorksNoCarry) {
    Given({
        "D0 is 0x20",
        "D1 is 0x78080801",
        "SR is S,0,0"
    });
    When({
        "ROR.L D0, D1"
    });
    Then({
        "CYCLES is 72",
        "D1 is 0x78080801",
        "SR is S,0,0"
    });
}

TEST_F(RORTest, RORRegisterLongShift45Works) {
    Given({
        "D0 is 0x2D",
        "D1 is 0x88080808",
        "SR is S,0,0"
    });
    When({
        "ROR.L D0, D1"
    });
    Then({
        "CYCLES is 98",
        "D1 is 0x40444040",
        "SR is S,0,0"
    });
}

TEST_F(RORTest, RORRegisterLongShift66Works) {
    Given({
        "D0 is 0x42",
        "D1 is 0x88080808",
        "SR is S,0,0"
    });
    When({
        "ROR.L D0, D1"
    });
    Then({
        "CYCLES is 12",
        "D1 is 0x22020202",
        "SR is S,0,0"
    });
}

TEST_F(RORTest, RORMemoryWordWorks) {
    Given({
        "A1 is 0x00002000",
        "(0x2000).W is 0xC003",
        "SR is S,0,0"
    });
    When({
        "ROR.W (A1)"
    });
    Then({
        "A1 is 0x00002000",
        "(0x2000).W is 0xE001",
        "SR is S,0,NC"
    });
}

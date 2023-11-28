#include "M68000/Fixtures/M68000Test.h"

class RORTest : public M68000Test {};

TEST_F(RORTest, RORImmediateByteWorks) {
    Given({
        "SR is S,0,XV",
        "PC is 0x1000",
        "D1 is 0xFFFFFFC1",
    });
    When({
        "ROR.B #2, D1"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFFF70",
    });
}

TEST_F(RORTest, RORImmediateByteSetsCarryAndNegativeFlags) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xFFFFFFC1",
    });
    When({
        "ROR.B #1, D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0xFFFFFFE0",
    });
}

TEST_F(RORTest, RORImmediateByteSetsZeroFlag) {
    Given({
        "SR is S,0,XV",
        "PC is 0x1000",
        "D1 is 0xFFFFFF00",
    });
    When({
        "ROR.B #2, D1"
    });
    Then({
        "SR is S,0,XZ",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFFF00",
    });
}

TEST_F(RORTest, RORImmediateWordWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xFFFFC808",
    });
    When({
        "ROR.W #2, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFF3202",
    });
}

TEST_F(RORTest, RORImmediateLongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x08080888",
    });
    When({
        "ROR.L #7, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 22",
        "D1 is 0x10101011",
    });
}

TEST_F(RORTest, RORRegisterByteWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x2",
        "D1 is 0xFFFFFFC1",
    });
    When({
        "ROR.B D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFFF70",
    });
}

TEST_F(RORTest, RORRegisterByteZeroShiftWorks) {
    Given({
        "SR is S,0,XC",
        "PC is 0x1000",
        "D0 is 0x0",
        "D1 is 0xFFFFFF08",
    });
    When({
        "ROR.B D0, D1"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0xFFFFFF08",
    });
}

TEST_F(RORTest, RORRegisterByteShift17Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x11",
        "D1 is 0xFFFFFFC7",
    });
    When({
        "ROR.B D0, D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1002",
        "CYCLES is 40",
        "D1 is 0xFFFFFFE3",
    });
}

TEST_F(RORTest, RORRegisterByteShift66Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x42",
        "D1 is 0xFFFFFF81",
    });
    When({
        "ROR.B D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFFF60",
    });
}

TEST_F(RORTest, RORRegisterWordWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x2",
        "D1 is 0xFFFF807F",
    });
    When({
        "ROR.W D0, D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFE01F",
    });
}

TEST_F(RORTest, RORRegisterWordZeroShiftWorks) {
    Given({
        "SR is S,0,XC",
        "PC is 0x1000",
        "D0 is 0x0",
        "D1 is 0xFFFF0808",
    });
    When({
        "ROR.W D0, D1"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0xFFFF0808",
    });
}

TEST_F(RORTest, RORRegisterWordShift23Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x17",
        "D1 is 0xFFFFBAAD",
    });
    When({
        "ROR.W D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 52",
        "D1 is 0xFFFF5B75",
    });
}

TEST_F(RORTest, RORRegisterWordShift66Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x42",
        "D1 is 0xFFFF56DD",
    });
    When({
        "ROR.W D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFF55B7",
    });
}

TEST_F(RORTest, RORRegisterLongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x3",
        "D1 is 0x88080808",
    });
    When({
        "ROR.L D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x11010101",
    });
}

TEST_F(RORTest, RORRegisterLongZeroShiftWorks) {
    Given({
        "SR is S,0,XC",
        "PC is 0x1000",
        "D0 is 0x0",
        "D1 is 0x08080808",
    });
    When({
        "ROR.L D0, D1"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x08080808",
    });
}

TEST_F(RORTest, RORRegisterLongShift32Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x20",
        "D1 is 0x88080801",
    });
    When({
        "ROR.L D0, D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1002",
        "CYCLES is 72",
        "D1 is 0x88080801",
    });
}

TEST_F(RORTest, RORRegisterLongShift32WorksNoCarry) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x20",
        "D1 is 0x78080801",
    });
    When({
        "ROR.L D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 72",
        "D1 is 0x78080801",
    });
}

TEST_F(RORTest, RORRegisterLongShift45Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x2D",
        "D1 is 0x88080808",
    });
    When({
        "ROR.L D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 98",
        "D1 is 0x40444040",
    });
}

TEST_F(RORTest, RORRegisterLongShift66Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x42",
        "D1 is 0x88080808",
    });
    When({
        "ROR.L D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x22020202",
    });
}

TEST_F(RORTest, RORMemoryWordWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00002000",
        "(0x2000).W is 0xC003",
    });
    When({
        "ROR.W (A1)"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1002",
        "CYCLES is 12",
        "A1 is 0x00002000",
        "(0x2000).W is 0xE001",
    });
}

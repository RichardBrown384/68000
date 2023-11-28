#include "M68000/Fixtures/M68000Test.h"

class LSRTest : public M68000Test {};

TEST_F(LSRTest, LSRImmediateByteWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xFFFFFF08",
    });
    When({
        "LSR.B #2, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFFF02",
    });
}

TEST_F(LSRTest, LSRImmediateByteSetsCarryAndExtendFlags) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xFFFFFF03",
    });
    When({
        "LSR.B #1, D1"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0xFFFFFF01",
    });
}

TEST_F(LSRTest, LSRImmediateWordWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xFFFF0808",
    });
    When({
        "LSR.W #1, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0xFFFF0404",
    });
}

TEST_F(LSRTest, LSRImmediateLongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x88080808",
    });
    When({
        "LSR.L #3, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x11010101",
    });
}

TEST_F(LSRTest, LSRRegisterByteWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x2",
        "D1 is 0xFFFFFF08",
    });
    When({
        "LSR.B D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFFF02",
    });
}

TEST_F(LSRTest, LSRRegisterByteZeroShiftWorks) {
    Given({
        "SR is S,0,XC",
        "PC is 0x1000",
        "D0 is 0x0",
        "D1 is 0xFFFFFF08",
    });
    When({
        "LSR.B D0, D1"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0xFFFFFF08",
    });
}

TEST_F(LSRTest, LSRRegisterByteShift17Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x11",
        "D1 is 0xFFFFFF08",
    });
    When({
        "LSR.B D0, D1"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 40",
        "D1 is 0xFFFFFF00",
    });
}

TEST_F(LSRTest, LSRRegisterByteShift38Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x26",
        "D1 is 0xFFFFFF08",
    });
    When({
        "LSR.B D0, D1"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 82",
        "D1 is 0xFFFFFF00",
    });
}

TEST_F(LSRTest, LSRRegisterByteShift66Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x42",
        "D1 is 0xFFFFFF08",
    });
    When({
        "LSR.B D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFFF02",
    });
}

TEST_F(LSRTest, LSRRegisterWordWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x2",
        "D1 is 0xFFFF8808",
    });
    When({
        "LSR.W D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFF2202",
    });
}

TEST_F(LSRTest, LSRRegisterWordZeroShiftWorks) {
    Given({
        "SR is S,0,XC",
        "PC is 0x1000",
        "D0 is 0x0",
        "D1 is 0xFFFF0808",
    });
    When({
        "LSR.W D0, D1"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0xFFFF0808",
    });
}

TEST_F(LSRTest, LSRRegisterWordShift23Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x17",
        "D1 is 0xFFFF0808",
    });
    When({
        "LSR.W D0, D1"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 52",
        "D1 is 0xFFFF0000",
    });
}

TEST_F(LSRTest, LSRRegisterWordShift66Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x42",
        "D1 is 0xFFFF0808",
    });
    When({
        "LSR.W D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFF0202",
    });
}

TEST_F(LSRTest, LSRRegisterLongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0xF",
        "D1 is 0x88080808",
    });
    When({
        "LSR.L D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 38",
        "D1 is 0x00011010",
    });
}

TEST_F(LSRTest, LSRRegisterLongZeroShiftWorks) {
    Given({
        "SR is S,0,XC",
        "PC is 0x1000",
        "D0 is 0x0",
        "D1 is 0x08080808",
    });
    When({
        "LSR.L D0, D1"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x08080808",
    });
}

TEST_F(LSRTest, LSRRegisterLongShift32Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x20",
        "D1 is 0x08080808",
    });
    When({
        "LSR.L D0, D1"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 72",
        "D1 is 0x00000000",
    });
}

TEST_F(LSRTest, LSRRegisterLongShift45Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x2D",
        "D1 is 0x08080808",
    });
    When({
        "LSR.L D0, D1"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 98",
        "D1 is 0x00000000",
    });
}

TEST_F(LSRTest, LSRRegisterLongShift66Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x42",
        "D1 is 0x88080808",
    });
    When({
        "LSR.L D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x22020202",
    });
}

TEST_F(LSRTest, LSRMemoryWordWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00002000",
        "(0x2000).W is 0xDB5A",
    });
    When({
        "LSR.W (A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "A1 is 0x00002000",
        "(0x2000).W is 0x6DAD",
    });
}

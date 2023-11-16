#include "M68000/Fixtures/M68000Test.h"

class LSRTest : public M68000Test {};

TEST_F(LSRTest, LSRImmediateByteWorks) {
    Given({
        "D1 is 0xFFFFFF08",
        "SR is S,0,0"
    });
    When({
        "LSR.B #2, D1"
    });
    Then({
        "CYCLES is 10",
        "D1 is 0xFFFFFF02",
        "SR is S,0,0"
    });
}

TEST_F(LSRTest, LSRImmediateByteSetsCarryAndExtendFlags) {
    Given({
        "D1 is 0xFFFFFF03",
        "SR is S,0,0"
    });
    When({
        "LSR.B #1, D1"
    });
    Then({
        "D1 is 0xFFFFFF01",
        "SR is S,0,XC"
    });
}

TEST_F(LSRTest, LSRImmediateWordWorks) {
    Given({
        "D1 is 0xFFFF0808",
        "SR is S,0,0"
    });
    When({
        "LSR.W #1, D1"
    });
    Then({
        "D1 is 0xFFFF0404",
        "SR is S,0,0"
    });
}

TEST_F(LSRTest, LSRImmediateLongWorks) {
    Given({
        "D1 is 0x88080808",
        "SR is S,0,0"
    });
    When({
        "LSR.L #3, D1"
    });
    Then({
        "D1 is 0x11010101",
        "SR is S,0,0"
    });
}

TEST_F(LSRTest, LSRRegisterByteWorks) {
    Given({
        "D0 is 0x2",
        "D1 is 0xFFFFFF08",
        "SR is S,0,0"
    });
    When({
        "LSR.B D0, D1"
    });
    Then({
        "D1 is 0xFFFFFF02",
        "SR is S,0,0"
    });
}

TEST_F(LSRTest, LSRRegisterByteZeroShiftWorks) {
    Given({
        "D0 is 0x0",
        "D1 is 0xFFFFFF08",
        "SR is S,0,XC"
    });
    When({
        "LSR.B D0, D1"
    });
    Then({
        "D1 is 0xFFFFFF08",
        "SR is S,0,X"
    });
}

TEST_F(LSRTest, LSRRegisterByteShift17Works) {
    Given({
        "D0 is 0x11",
        "D1 is 0xFFFFFF08",
        "SR is S,0,0"
    });
    When({
        "LSR.B D0, D1"
    });
    Then({
        "CYCLES is 40",
        "D1 is 0xFFFFFF00",
        "SR is S,0,Z"
    });
}

TEST_F(LSRTest, LSRRegisterByteShift38Works) {
    Given({
        "D0 is 0x26",
        "D1 is 0xFFFFFF08",
        "SR is S,0,0"
    });
    When({
        "LSR.B D0, D1"
    });
    Then({
        "CYCLES is 82",
        "D1 is 0xFFFFFF00",
        "SR is S,0,Z"
    });
}

TEST_F(LSRTest, LSRRegisterByteShift66Works) {
    Given({
        "D0 is 0x42",
        "D1 is 0xFFFFFF08",
        "SR is S,0,0"
    });
    When({
        "LSR.B D0, D1"
    });
    Then({
        "CYCLES is 10",
        "D1 is 0xFFFFFF02",
        "SR is S,0,0"
    });
}

TEST_F(LSRTest, LSRRegisterWordWorks) {
    Given({
        "D0 is 0x2",
        "D1 is 0xFFFF8808",
        "SR is S,0,0"
    });
    When({
        "LSR.W D0, D1"
    });
    Then({
        "D1 is 0xFFFF2202",
        "SR is S,0,0"
    });
}

TEST_F(LSRTest, LSRRegisterWordZeroShiftWorks) {
    Given({
        "D0 is 0x0",
        "D1 is 0xFFFF0808",
        "SR is S,0,XC"
    });
    When({
        "LSR.W D0, D1"
    });
    Then({
        "D1 is 0xFFFF0808",
        "SR is S,0,X"
    });
}

TEST_F(LSRTest, LSRRegisterWordShift23Works) {
    Given({
        "D0 is 0x17",
        "D1 is 0xFFFF0808",
        "SR is S,0,0"
    });
    When({
        "LSR.W D0, D1"
    });
    Then({
        "CYCLES is 52",
        "D1 is 0xFFFF0000",
        "SR is S,0,Z"
    });
}

TEST_F(LSRTest, LSRRegisterWordShift66Works) {
    Given({
        "D0 is 0x42",
        "D1 is 0xFFFF0808",
        "SR is S,0,0"
    });
    When({
        "LSR.W D0, D1"
    });
    Then({
        "CYCLES is 10",
        "D1 is 0xFFFF0202",
        "SR is S,0,0"
    });
}

TEST_F(LSRTest, LSRRegisterLongWorks) {
    Given({
        "D0 is 0xF",
        "D1 is 0x88080808",
        "SR is S,0,0"
    });
    When({
        "LSR.L D0, D1"
    });
    Then({
        "CYCLES is 38",
        "D1 is 0x00011010",
        "SR is S,0,0"
    });
}

TEST_F(LSRTest, LSRRegisterLongZeroShiftWorks) {
    Given({
        "D0 is 0x0",
        "D1 is 0x08080808",
        "SR is S,0,XC"
    });
    When({
        "LSR.L D0, D1"
    });
    Then({
        "D1 is 0x08080808",
        "SR is S,0,X"
    });
}

TEST_F(LSRTest, LSRRegisterLongShift32Works) {
    Given({
        "D0 is 0x20",
        "D1 is 0x08080808",
        "SR is S,0,0"
    });
    When({
        "LSR.L D0, D1"
    });
    Then({
        "CYCLES is 72",
        "D1 is 0x00000000",
        "SR is S,0,Z"
    });
}

TEST_F(LSRTest, LSRRegisterLongShift45Works) {
    Given({
        "D0 is 0x2D",
        "D1 is 0x08080808",
        "SR is S,0,0"
    });
    When({
        "LSR.L D0, D1"
    });
    Then({
        "CYCLES is 98",
        "D1 is 0x00000000",
        "SR is S,0,Z"
    });
}

TEST_F(LSRTest, LSRRegisterLongShift66Works) {
    Given({
        "D0 is 0x42",
        "D1 is 0x88080808",
        "SR is S,0,0"
    });
    When({
        "LSR.L D0, D1"
    });
    Then({
        "CYCLES is 12",
        "D1 is 0x22020202",
        "SR is S,0,0"
    });
}

TEST_F(LSRTest, LSRMemoryWordWorks) {
    Given({
        "A1 is 0x00002000",
        "(0x2000).W is 0xDB5A",
        "SR is S,0,0"
    });
    When({
        "LSR.W (A1)"
    });
    Then({
        "A1 is 0x00002000",
        "(0x2000).W is 0x6DAD",
        "SR is S,0,0"
    });
}

#include "M68000/Fixtures/M68000Test.h"

class ASRTest : public M68000Test {};

TEST_F(ASRTest, ASRImmediateByteWorks) {
    Given({
        "D1 is 0xFFFFFF08",
        "SR is S,0,0"
    });
    When({
        "ASR.B #2, D1"
    });
    Then({
        "CYCLES is 10",
        "D1 is 0xFFFFFF02",
        "SR is S,0,0"
    });
}

TEST_F(ASRTest, ASRImmediateByteWithSignBitSetWorks) {
    Given({
        "D1 is 0xFFFFFF88",
        "SR is S,0,0"
    });
    When({
        "ASR.B #2, D1"
    });
    Then({
        "CYCLES is 10",
        "D1 is 0xFFFFFFE2",
        "SR is S,0,N"
    });
}

TEST_F(ASRTest, ASRImmediateByteSetsCarryAndExtendFlags) {
    Given({
        "D1 is 0xFFFFFF03",
        "SR is S,0,0"
    });
    When({
        "ASR.B #1, D1"
    });
    Then({
        "D1 is 0xFFFFFF01",
        "SR is S,0,XC"
    });
}

TEST_F(ASRTest, ASRImmediateWordWorks) {
    Given({
        "D1 is 0xFFFF0808",
        "SR is S,0,0"
    });
    When({
        "ASR.W #1, D1"
    });
    Then({
        "D1 is 0xFFFF0404",
        "SR is S,0,0"
    });
}

TEST_F(ASRTest, ASRImmediateLongWorks) {
    Given({
        "D1 is 0x88080808",
        "SR is S,0,0"
    });
    When({
        "ASR.L #3, D1"
    });
    Then({
        "D1 is 0xF1010101",
        "SR is S,0,N"
    });
}

TEST_F(ASRTest, ASRRegisterByteWorks) {
    Given({
        "D0 is 0x2",
        "D1 is 0xFFFFFF08",
        "SR is S,0,0"
    });
    When({
        "ASR.B D0, D1"
    });
    Then({
        "D1 is 0xFFFFFF02",
        "SR is S,0,0"
    });
}

TEST_F(ASRTest, ASRRegisterByteZeroShiftWorks) {
    Given({
        "D0 is 0x0",
        "D1 is 0xFFFFFF08",
        "SR is S,0,XC"
    });
    When({
        "ASR.B D0, D1"
    });
    Then({
        "D1 is 0xFFFFFF08",
        "SR is S,0,X"
    });
}

TEST_F(ASRTest, ASRRegisterByteShift17Works) {
    Given({
        "D0 is 0x11",
        "D1 is 0xFFFFFF08",
        "SR is S,0,0"
    });
    When({
        "ASR.B D0, D1"
    });
    Then({
        "CYCLES is 40",
        "D1 is 0xFFFFFF00",
        "SR is S,0,Z"
    });
}

TEST_F(ASRTest, ASRRegisterByteShift38Works) {
    Given({
        "D0 is 0x26",
        "D1 is 0xFFFFFF08",
        "SR is S,0,0"
    });
    When({
        "ASR.B D0, D1"
    });
    Then({
        "CYCLES is 82",
        "D1 is 0xFFFFFF00",
        "SR is S,0,Z"
    });
}

TEST_F(ASRTest, ASRRegisterByteShift66Works) {
    Given({
        "D0 is 0x42",
        "D1 is 0xFFFFFF08",
        "SR is S,0,0"
    });
    When({
        "ASR.B D0, D1"
    });
    Then({
        "CYCLES is 10",
        "D1 is 0xFFFFFF02",
        "SR is S,0,0"
    });
}

TEST_F(ASRTest, ASRRegisterWordWorks) {
    Given({
        "D0 is 0x2",
        "D1 is 0xFFFF8808",
        "SR is S,0,0"
    });
    When({
        "ASR.W D0, D1"
    });
    Then({
        "D1 is 0xFFFFE202",
        "SR is S,0,N"
    });
}

TEST_F(ASRTest, ASRRegisterWordZeroShiftWorks) {
    Given({
        "D0 is 0x0",
        "D1 is 0xFFFF0808",
        "SR is S,0,XC"
    });
    When({
        "ASR.W D0, D1"
    });
    Then({
        "D1 is 0xFFFF0808",
        "SR is S,0,X"
    });
}

TEST_F(ASRTest, ASRRegisterWordShift23Works) {
    Given({
        "D0 is 0x17",
        "D1 is 0xFFFF0808",
        "SR is S,0,0"
    });
    When({
        "ASR.W D0, D1"
    });
    Then({
        "CYCLES is 52",
        "D1 is 0xFFFF0000",
        "SR is S,0,Z"
    });
}

TEST_F(ASRTest, ASRRegisterWordShift66Works) {
    Given({
        "D0 is 0x42",
        "D1 is 0xFFFF0808",
        "SR is S,0,0"
    });
    When({
        "ASR.W D0, D1"
    });
    Then({
        "CYCLES is 10",
        "D1 is 0xFFFF0202",
        "SR is S,0,0"
    });
}

TEST_F(ASRTest, ASRRegisterLongWorks) {
    Given({
        "D0 is 0x3",
        "D1 is 0x88080808",
        "SR is S,0,0"
    });
    When({
        "ASR.L D0, D1"
    });
    Then({
        "D1 is 0xF1010101",
        "SR is S,0,N"
    });
}

TEST_F(ASRTest, ASRRegisterLongZeroShiftWorks) {
    Given({
        "D0 is 0x0",
        "D1 is 0x08080808",
        "SR is S,0,XC"
    });
    When({
        "ASR.L D0, D1"
    });
    Then({
        "D1 is 0x08080808",
        "SR is S,0,X"
    });
}

TEST_F(ASRTest, ASRRegisterLongShift32Works) {
    Given({
        "D0 is 0x20",
        "D1 is 0x08080808",
        "SR is S,0,0"
    });
    When({
        "ASR.L D0, D1"
    });
    Then({
        "CYCLES is 72",
        "D1 is 0x00000000",
        "SR is S,0,Z"
    });
}

TEST_F(ASRTest, ASRRegisterLongShift45Works) {
    Given({
        "D0 is 0x2D",
        "D1 is 0x08080808",
        "SR is S,0,0"
    });
    When({
        "ASR.L D0, D1"
    });
    Then({
        "CYCLES is 98",
        "D1 is 0x00000000",
        "SR is S,0,Z"
    });
}

TEST_F(ASRTest, ASRRegisterLongShift66Works) {
    Given({
        "D0 is 0x42",
        "D1 is 0x88080808",
        "SR is S,0,0"
    });
    When({
        "ASR.L D0, D1"
    });
    Then({
        "CYCLES is 12",
        "D1 is 0xE2020202",
        "SR is S,0,N"
    });
}

TEST_F(ASRTest, ASRMemoryWordWorks) {
    Given({
        "A1 is 0x00002000",
        "(0x2000).W is 0xDB5A",
        "SR is S,0,0"
    });
    When({
        "ASR.W (A1)"
    });
    Then({
        "A1 is 0x00002000",
        "(0x2000).W is 0xEDAD",
        "SR is S,0,N"
    });
}

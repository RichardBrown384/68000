#include "M68000/Fixtures/M68000Test.h"

class ASRTest : public M68000Test {};

TEST_F(ASRTest, ASRImmediateByteWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xFFFFFF08",
    });
    When({
        "ASR.B #2, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFFF02",
    });
}

TEST_F(ASRTest, ASRImmediateByteWithSignBitSetWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xFFFFFF88",
    });
    When({
        "ASR.B #2, D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFFFE2",
    });
}

TEST_F(ASRTest, ASRImmediateByteSetsCarryAndExtendFlags) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xFFFFFF03",
    });
    When({
        "ASR.B #1, D1"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0xFFFFFF01",
    });
}

TEST_F(ASRTest, ASRImmediateWordWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xFFFF0808",
    });
    When({
        "ASR.W #1, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0xFFFF0404",
    });
}

TEST_F(ASRTest, ASRImmediateLongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x88080808",
    });
    When({
        "ASR.L #3, D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0xF1010101",
    });
}

TEST_F(ASRTest, ASRRegisterByteWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x2",
        "D1 is 0xFFFFFF08",
    });
    When({
        "ASR.B D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFFF02",
    });
}

TEST_F(ASRTest, ASRRegisterByteZeroShiftWorks) {
    Given({
        "SR is S,0,XC",
        "PC is 0x1000",
        "D0 is 0x0",
        "D1 is 0xFFFFFF08",
    });
    When({
        "ASR.B D0, D1"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0xFFFFFF08",
    });
}

TEST_F(ASRTest, ASRRegisterByteShift17Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x11",
        "D1 is 0xFFFFFF08",
    });
    When({
        "ASR.B D0, D1"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 40",
        "D1 is 0xFFFFFF00",
    });
}

TEST_F(ASRTest, ASRRegisterByteShift38Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x26",
        "D1 is 0xFFFFFF08",
    });
    When({
        "ASR.B D0, D1"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 82",
        "D1 is 0xFFFFFF00",
    });
}

TEST_F(ASRTest, ASRRegisterByteShift66Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x42",
        "D1 is 0xFFFFFF08",
    });
    When({
        "ASR.B D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFFF02",
    });
}

TEST_F(ASRTest, ASRRegisterWordWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x2",
        "D1 is 0xFFFF8808",
    });
    When({
        "ASR.W D0, D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFFE202",
    });
}

TEST_F(ASRTest, ASRRegisterWordZeroShiftWorks) {
    Given({
        "SR is S,0,XC",
        "PC is 0x1000",
        "D0 is 0x0",
        "D1 is 0xFFFF0808",
    });
    When({
        "ASR.W D0, D1"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0xFFFF0808",
    });
}

TEST_F(ASRTest, ASRRegisterWordShift23Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x17",
        "D1 is 0xFFFF0808",
    });
    When({
        "ASR.W D0, D1"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 52",
        "D1 is 0xFFFF0000",
    });
}

TEST_F(ASRTest, ASRRegisterWordShift66Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x42",
        "D1 is 0xFFFF0808",
    });
    When({
        "ASR.W D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0xFFFF0202",
    });
}

TEST_F(ASRTest, ASRRegisterLongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x3",
        "D1 is 0x88080808",
    });
    When({
        "ASR.L D0, D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0xF1010101",
    });
}

TEST_F(ASRTest, ASRRegisterLongZeroShiftWorks) {
    Given({
        "SR is S,0,XC",
        "PC is 0x1000",
        "D0 is 0x0",
        "D1 is 0x08080808",
    });
    When({
        "ASR.L D0, D1"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x08080808",
    });
}

TEST_F(ASRTest, ASRRegisterLongShift32Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x20",
        "D1 is 0x08080808",
    });
    When({
        "ASR.L D0, D1"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 72",
        "D1 is 0x00000000",
    });
}

TEST_F(ASRTest, ASRRegisterLongShift45Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x2D",
        "D1 is 0x08080808",
    });
    When({
        "ASR.L D0, D1"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 98",
        "D1 is 0x00000000",
    });
}

TEST_F(ASRTest, ASRRegisterLongShift66Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x42",
        "D1 is 0x88080808",
    });
    When({
        "ASR.L D0, D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0xE2020202",
    });
}

TEST_F(ASRTest, ASRMemoryWordWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00002000",
        "(0x2000).W is 0xDB5A",
    });
    When({
        "ASR.W (A1)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 12",
        "A1 is 0x00002000",
        "(0x2000).W is 0xEDAD",
    });
}

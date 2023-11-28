#include "M68000/Fixtures/M68000Test.h"

class CMPATestWord : public M68000Test {};

TEST_F(CMPATestWord, DataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01A10501",
        "A2 is 0x00000305",
    });
    When({
        "CMPA.W D1, A2"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x01A10501",
        "A2 is 0x00000305",
    });
}

TEST_F(CMPATestWord, DataRegisterSignExtend16Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00008080",
        "A2 is 0x01000080",
    });
    When({
        "CMPA.W D1, A2"
    });
    Then({
        "SR is S,0,C",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x00008080",
        "A2 is 0x01000080",
    });
}

TEST_F(CMPATestWord, DataRegisterFlagNVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0000FFFF",
        "A2 is 0x7FFFFFFF",
    });
    When({
        "CMPA.W D1, A2"
    });
    Then({
        "SR is S,0,NVC",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x0000FFFF",
        "A2 is 0x7FFFFFFF",
    });
}

TEST_F(CMPATestWord, DataRegisterFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x7F00FFF0",
        "A2 is 0xFFFFFFF0",
    });
    When({
        "CMPA.W D1, A2"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x7F00FFF0",
        "A2 is 0xFFFFFFF0",
    });
}

TEST_F(CMPATestWord, DataRegisterFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0x7F007FF0",
        "A2 is 0x7F007FF1",
    });
    When({
        "CMPA.W D1, A2"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x7F007FF0",
        "A2 is 0x7F007FF1",
    });
}

TEST_F(CMPATestWord, AddressRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x01010901",
        "A2 is 0x00000308",
    });
    When({
        "CMPA.W A1, A2"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1002",
        "CYCLES is 6",
        "A1 is 0x01010901",
        "A2 is 0x00000308",
    });
}

TEST_F(CMPATestWord, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00008000",
        "A2 is 0x01030908",
        "(0x00008000).W is 0x8087",
    });
    When({
        "CMPA.W (A1), A2"
    });
    Then({
        "SR is S,0,C",
        "PC is 0x1002",
        "CYCLES is 10",
        "A1 is 0x00008000",
        "A2 is 0x01030908",
        "(0x00008000).W is 0x8087",
    });
}

TEST_F(CMPATestWord, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00008000",
        "A2 is 0x01030908",
        "(0x00008000).W is 0x8087",
    });
    When({
        "CMPA.W (A1)+, A2"
    });
    Then({
        "SR is S,0,C",
        "PC is 0x1002",
        "CYCLES is 10",
        "A1 is 0x00008002",
        "A2 is 0x01030908",
        "(0x00008000).W is 0x8087",
    });
}

TEST_F(CMPATestWord, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00008002",
        "A2 is 0x01030908",
        "(0x00008000).W is 0x8087",
    });
    When({
        "CMPA.W -(A1), A2"
    });
    Then({
        "SR is S,0,C",
        "PC is 0x1002",
        "CYCLES is 12",
        "A1 is 0x00008000",
        "A2 is 0x01030908",
        "(0x00008000).W is 0x8087",
    });
}

TEST_F(CMPATestWord, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00008000",
        "A2 is 0x01030908",
        "(0x00008002).W is 0x8087",
    });
    When({
        "CMPA.W (2, A1), A2"
    });
    Then({
        "SR is S,0,C",
        "PC is 0x1004",
        "CYCLES is 14",
        "A1 is 0x00008000",
        "A2 is 0x01030908",
        "(0x00008002).W is 0x8087",
    });
}

TEST_F(CMPATestWord, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "A3 is 0x01030908",
        "(0x00008012).W is 0x8087",
    });
    When({
        "CMPA.W (2, A1, A2.L), A3"
    });
    Then({
        "SR is S,0,C",
        "PC is 0x1004",
        "CYCLES is 16",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "A3 is 0x01030908",
        "(0x00008012).W is 0x8087",
    });
}

TEST_F(CMPATestWord, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x01030908",
        "(0x00004000).W is 0x8087",
    });
    When({
        "CMPA.W (0x4000).W, A1"
    });
    Then({
        "SR is S,0,C",
        "PC is 0x1004",
        "CYCLES is 14",
        "A1 is 0x01030908",
        "(0x00004000).W is 0x8087",
    });
}

TEST_F(CMPATestWord, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x01030908",
        "(0x00008000).W is 0x8087",
    });
    When({
        "CMPA.W (0x8000).L, A1"
    });
    Then({
        "SR is S,0,C",
        "PC is 0x1006",
        "CYCLES is 18",
        "A1 is 0x01030908",
        "(0x00008000).W is 0x8087",
    });
}

TEST_F(CMPATestWord, PCDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x01030908",
        "(0x00001060).W is 0x8087",
    });
    When({
        "CMPA.W (0x5E, PC), A1"
    });
    Then({
        "SR is S,0,C",
        "PC is 0x1004",
        "CYCLES is 14",
        "A1 is 0x01030908",
        "(0x00001060).W is 0x8087",
    });
}

TEST_F(CMPATestWord, PCIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00000010",
        "A2 is 0x01030908",
        "(0x00001070).W is 0x8087",
    });
    When({
        "CMPA.W (0x5E, PC, A1.L), A2"
    });
    Then({
        "SR is S,0,C",
        "PC is 0x1004",
        "CYCLES is 16",
        "A1 is 0x00000010",
        "A2 is 0x01030908",
        "(0x00001070).W is 0x8087",
    });
}

TEST_F(CMPATestWord, ImmediateWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x01030908",
    });
    When({
        "CMPA.W #0x8087, A1"
    });
    Then({
        "SR is S,0,C",
        "PC is 0x1004",
        "CYCLES is 10",
        "A1 is 0x01030908",
    });
}

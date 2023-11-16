#include "M68000/Fixtures/M68000Test.h"

class CMPATestWord : public M68000Test {};

TEST_F(CMPATestWord, DataRegisterWorks) {
    Given({
        "D1 is 0x01A10501",
        "A2 is 0x00000305",
        "SR is S,0,0"
    });
    When({
        "CMPA.W D1, A2"
    });
    Then({
        "D1 is 0x01A10501",
        "A2 is 0x00000305",
        "SR is S,0,NC"
    });
}

TEST_F(CMPATestWord, DataRegisterSignExtend16Works) {
    Given({
        "D1 is 0x00008080",
        "A2 is 0x01000080",
        "SR is S,0,0"
    });
    When({
        "CMPA.W D1, A2"
    });
    Then({
        "D1 is 0x00008080",
        "A2 is 0x01000080",
        "SR is S,0,C"
    });
}

TEST_F(CMPATestWord, DataRegisterFlagNVWorks) {
    Given({
        "D1 is 0x0000FFFF",
        "A2 is 0x7FFFFFFF",
        "SR is S,0,0"
    });
    When({
        "CMPA.W D1, A2"
    });
    Then({
        "D1 is 0x0000FFFF",
        "A2 is 0x7FFFFFFF",
        "SR is S,0,NVC"
    });
}

TEST_F(CMPATestWord, DataRegisterFlagZWorks) {
    Given({
        "D1 is 0x7F00FFF0",
        "A2 is 0xFFFFFFF0",
        "SR is S,0,0"
    });
    When({
        "CMPA.W D1, A2"
    });
    Then({
        "D1 is 0x7F00FFF0",
        "A2 is 0xFFFFFFF0",
        "SR is S,0,Z"
    });
}

TEST_F(CMPATestWord, DataRegisterFlagXWorks) {
    Given({
        "D1 is 0x7F007FF0",
        "A2 is 0x7F007FF1",
        "SR is S,0,X"
    });
    When({
        "CMPA.W D1, A2"
    });
    Then({
        "D1 is 0x7F007FF0",
        "A2 is 0x7F007FF1",
        "SR is S,0,X"
    });
}

TEST_F(CMPATestWord, AddressRegisterWorks) {
    Given({
        "A1 is 0x01010901",
        "A2 is 0x00000308",
        "SR is S,0,0"
    });
    When({
        "CMPA.W A1, A2"
    });
    Then({
        "A1 is 0x01010901",
        "A2 is 0x00000308",
        "SR is S,0,NC"
    });
}

TEST_F(CMPATestWord, AddressIndirectWorks) {
    Given({
        "A1 is 0x00008000",
        "A2 is 0x01030908",
        "(0x00008000).W is 0x8087",
        "SR is S,0,0"
    });
    When({
        "CMPA.W (A1), A2"
    });
    Then({
        "A1 is 0x00008000",
        "A2 is 0x01030908",
        "(0x00008000).W is 0x8087",
        "SR is S,0,C"
    });
}

TEST_F(CMPATestWord, AddressIncrementWorks) {
    Given({
        "A1 is 0x00008000",
        "A2 is 0x01030908",
        "(0x00008000).W is 0x8087",
        "SR is S,0,0"
    });
    When({
        "CMPA.W (A1)+, A2"
    });
    Then({
        "A1 is 0x00008002",
        "A2 is 0x01030908",
        "(0x00008000).W is 0x8087",
        "SR is S,0,C"
    });
}

TEST_F(CMPATestWord, AddressDecrementWorks) {
    Given({
        "A1 is 0x00008002",
        "A2 is 0x01030908",
        "(0x00008000).W is 0x8087",
        "SR is S,0,0"
    });
    When({
        "CMPA.W -(A1), A2"
    });
    Then({
        "A1 is 0x00008000",
        "A2 is 0x01030908",
        "(0x00008000).W is 0x8087",
        "SR is S,0,C"
    });
}

TEST_F(CMPATestWord, AddressDisplacementWorks) {
    Given({
        "A1 is 0x00008000",
        "A2 is 0x01030908",
        "(0x00008002).W is 0x8087",
        "SR is S,0,0"
    });
    When({
        "CMPA.W (2, A1), A2"
    });
    Then({
        "A1 is 0x00008000",
        "A2 is 0x01030908",
        "(0x00008002).W is 0x8087",
        "SR is S,0,C"
    });
}

TEST_F(CMPATestWord, AddressIndexWorks) {
    Given({
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "A3 is 0x01030908",
        "(0x00008012).W is 0x8087",
        "SR is S,0,0"
    });
    When({
        "CMPA.W (2, A1, A2.L), A3"
    });
    Then({
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "A3 is 0x01030908",
        "(0x00008012).W is 0x8087",
        "SR is S,0,C"
    });
}

TEST_F(CMPATestWord, ShortWorks) {
    Given({
        "A1 is 0x01030908",
        "(0x00004000).W is 0x8087",
        "SR is S,0,0"
    });
    When({
        "CMPA.W (0x4000).W, A1"
    });
    Then({
        "A1 is 0x01030908",
        "(0x00004000).W is 0x8087",
        "SR is S,0,C"
    });
}

TEST_F(CMPATestWord, LongWorks) {
    Given({
        "A1 is 0x01030908",
        "(0x00008000).W is 0x8087",
        "SR is S,0,0"
    });
    When({
        "CMPA.W (0x8000).L, A1"
    });
    Then({
        "A1 is 0x01030908",
        "(0x00008000).W is 0x8087",
        "SR is S,0,C"
    });
}

TEST_F(CMPATestWord, PCDisplacementWorks) {
    Given({
        "A1 is 0x01030908",
        "(0x00001060).W is 0x8087",
        "SR is S,0,0"
    });
    When({
        "CMPA.W (0x5E, PC), A1"
    });
    Then({
        "A1 is 0x01030908",
        "(0x00001060).W is 0x8087",
        "SR is S,0,C"
    });
}

TEST_F(CMPATestWord, PCIndexWorks) {
    Given({
        "A1 is 0x00000010",
        "A2 is 0x01030908",
        "(0x00001070).W is 0x8087",
        "SR is S,0,0"
    });
    When({
        "CMPA.W (0x5E, PC, A1.L), A2"
    });
    Then({
        "A1 is 0x00000010",
        "A2 is 0x01030908",
        "(0x00001070).W is 0x8087",
        "SR is S,0,C"
    });
}

TEST_F(CMPATestWord, ImmediateWorks) {
    Given({
        "A1 is 0x01030908",
        "SR is S,0,0"
    });
    When({
        "CMPA.W #0x8087, A1"
    });
    Then({
        "A1 is 0x01030908",
        "SR is S,0,C"
    });
}
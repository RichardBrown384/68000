#include "M68000/Fixtures/M68000Test.h"

class MOVEATestWord : public M68000Test {};

TEST_F(MOVEATestWord, DataDirectWorks) {
    Given({
        "D1 is 0x347879BA",
        "A4 is 0x78120966",
        "SR is S,0,Z"
    });
    When({
        "MOVEA.W D1, A4"
    });
    Then({
        "D1 is 0x347879BA",
        "A4 is 0x000079BA",
        "SR is S,0,Z"
    });
}

TEST_F(MOVEATestWord, DataDirectSignExtendedWorks) {
    Given({
        "D1 is 0x347889BA",
        "A4 is 0x78120966",
        "SR is S,0,Z"
    });
    When({
        "MOVEA.W D1, A4"
    });
    Then({
        "D1 is 0x347889BA",
        "A4 is 0xFFFF89BA",
        "SR is S,0,Z"
    });
}

TEST_F(MOVEATestWord, AddressDirectWorks) {
    Given({
        "A1 is 0x347879BA",
        "A4 is 0x78120966",
        "SR is S,0,Z"
    });
    When({
        "MOVEA.W A1, A4"
    });
    Then({
        "A1 is 0x347879BA",
        "A4 is 0x000079BA",
        "SR is S,0,Z"
    });
}

TEST_F(MOVEATestWord, AddressIndirectWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).W is 0x79BA",
        "A4 is 0x78120966",
        "SR is S,0,Z"
    });
    When({
        "MOVEA.W (A1), A4"
    });
    Then({
        "A1 is 0x00005000",
        "(0x00005000).W is 0x79BA",
        "A4 is 0x000079BA",
        "SR is S,0,Z"
    });
}

TEST_F(MOVEATestWord, AddressIncrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).W is 0x79BA",
        "A4 is 0x78120966",
        "SR is S,0,Z"
    });
    When({
        "MOVEA.W (A1)+, A4"
    });
    Then({
        "A1 is 0x00005002",
        "(0x00005000).W is 0x79BA",
        "A4 is 0x000079BA",
        "SR is S,0,Z"
    });
}

TEST_F(MOVEATestWord, AddressDecrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00004FFE).W is 0x79BA",
        "A4 is 0x78120966",
        "SR is S,0,Z"
    });
    When({
        "MOVEA.W -(A1), A4"
    });
    Then({
        "A1 is 0x00004FFE",
        "(0x00004FFE).W is 0x79BA",
        "A4 is 0x000079BA",
        "SR is S,0,Z"
    });
}

TEST_F(MOVEATestWord, AddressDisplacementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x0000503C).W is 0x79BA",
        "A4 is 0x78120966",
        "SR is S,0,Z"
    });
    When({
        "MOVEA.W (0x003C, A1), A4"
    });
    Then({
        "A1 is 0x00005000",
        "(0x0000503C).W is 0x79BA",
        "A4 is 0x000079BA",
        "SR is S,0,Z"
    });
}

TEST_F(MOVEATestWord, AddressIndexWorks) {
    Given({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).W is 0x79BA",
        "A4 is 0x78120966",
        "SR is S,0,Z"
    });
    When({
        "MOVEA.W (0x5E, A1, A2.L), A4"
    });
    Then({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).W is 0x79BA",
        "A4 is 0x000079BA",
        "SR is S,0,Z"
    });
}

TEST_F(MOVEATestWord, ShortWorks) {
    Given({
        "(0x00005000).W is 0x79BA",
        "A4 is 0x78120966",
        "SR is S,0,Z"
    });
    When({
        "MOVEA.W (0x5000).W, A4"
    });
    Then({
        "(0x00005000).W is 0x79BA",
        "A4 is 0x000079BA",
        "SR is S,0,Z"
    });
}

TEST_F(MOVEATestWord, LongWorks) {
    Given({
        "(0x00005000).W is 0x79BA",
        "A4 is 0x78120966",
        "SR is S,0,Z"
    });
    When({
        "MOVEA.W (0x00005000).L, A4"
    });
    Then({
        "(0x00005000).W is 0x79BA",
        "A4 is 0x000079BA",
        "SR is S,0,Z"
    });
}

TEST_F(MOVEATestWord, PCDisplacementWorks) {
    Given({
        "(0x0000103E).W is 0x79BA",
        "A4 is 0x78120966",
        "SR is S,0,Z"
    });
    When({
        "MOVEA.W (0x003C, PC), A4"
    });
    Then({
        "(0x0000103E).W is 0x79BA",
        "A4 is 0x000079BA",
        "SR is S,0,Z"
    });
}

TEST_F(MOVEATestWord, PCIndexWorks) {
    Given({
        "A2 is 0x00000010",
        "(0x00001070).W is 0x79BA",
        "A4 is 0x78120966",
        "SR is S,0,Z"
    });
    When({
        "MOVEA.W (0x5E, PC, A2.L), A4"
    });
    Then({
        "A2 is 0x00000010",
        "(0x00001070).W is 0x79BA",
        "A4 is 0x000079BA",
        "SR is S,0,Z"
    });
}

TEST_F(MOVEATestWord, ImmediateWorks) {
    Given({
        "A4 is 0x78120966",
        "SR is S,0,Z"
    });
    When({
        "MOVEA.W #0x79BA, A4"
    });
    Then({
        "A4 is 0x000079BA",
        "SR is S,0,Z"
    });
}

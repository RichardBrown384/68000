#include "M68000/Fixtures/M68000Test.h"

class MOVEATestWord : public M68000Test {};

TEST_F(MOVEATestWord, DataDirectWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0x347879BA",
        "A4 is 0x78120966",
    });
    When({
        "MOVEA.W D1, A4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x347879BA",
        "A4 is 0x000079BA",
    });
}

TEST_F(MOVEATestWord, DataDirectSignExtendedWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0x347889BA",
        "A4 is 0x78120966",
    });
    When({
        "MOVEA.W D1, A4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x347889BA",
        "A4 is 0xFFFF89BA",
    });
}

TEST_F(MOVEATestWord, AddressDirectWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "A1 is 0x347879BA",
        "A4 is 0x78120966",
    });
    When({
        "MOVEA.W A1, A4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 4",
        "A1 is 0x347879BA",
        "A4 is 0x000079BA",
    });
}

TEST_F(MOVEATestWord, AddressIndirectWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A4 is 0x78120966",
        "(0x00005000).W is 0x79BA",
    });
    When({
        "MOVEA.W (A1), A4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 8",
        "A1 is 0x00005000",
        "A4 is 0x000079BA",
        "(0x00005000).W is 0x79BA",
    });
}

TEST_F(MOVEATestWord, AddressIncrementWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A4 is 0x78120966",
        "(0x00005000).W is 0x79BA",
    });
    When({
        "MOVEA.W (A1)+, A4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 8",
        "A1 is 0x00005002",
        "A4 is 0x000079BA",
        "(0x00005000).W is 0x79BA",
    });
}

TEST_F(MOVEATestWord, AddressDecrementWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A4 is 0x78120966",
        "(0x00004FFE).W is 0x79BA",
    });
    When({
        "MOVEA.W -(A1), A4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 10",
        "A1 is 0x00004FFE",
        "A4 is 0x000079BA",
        "(0x00004FFE).W is 0x79BA",
    });
}

TEST_F(MOVEATestWord, AddressDisplacementWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A4 is 0x78120966",
        "(0x0000503C).W is 0x79BA",
    });
    When({
        "MOVEA.W (0x003C, A1), A4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 12",
        "A1 is 0x00005000",
        "A4 is 0x000079BA",
        "(0x0000503C).W is 0x79BA",
    });
}

TEST_F(MOVEATestWord, AddressIndexWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "A4 is 0x78120966",
        "(0x0000506E).W is 0x79BA",
    });
    When({
        "MOVEA.W (0x5E, A1, A2.L), A4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 14",
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "A4 is 0x000079BA",
        "(0x0000506E).W is 0x79BA",
    });
}

TEST_F(MOVEATestWord, ShortWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "A4 is 0x78120966",
        "(0x00005000).W is 0x79BA",
    });
    When({
        "MOVEA.W (0x5000).W, A4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 12",
        "A4 is 0x000079BA",
        "(0x00005000).W is 0x79BA",
    });
}

TEST_F(MOVEATestWord, LongWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "A4 is 0x78120966",
        "(0x00005000).W is 0x79BA",
    });
    When({
        "MOVEA.W (0x00005000).L, A4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1006",
        "CYCLES is 16",
        "A4 is 0x000079BA",
        "(0x00005000).W is 0x79BA",
    });
}

TEST_F(MOVEATestWord, PCDisplacementWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "A4 is 0x78120966",
        "(0x0000103E).W is 0x79BA",
    });
    When({
        "MOVEA.W (0x003C, PC), A4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 12",
        "A4 is 0x000079BA",
        "(0x0000103E).W is 0x79BA",
    });
}

TEST_F(MOVEATestWord, PCIndexWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "A2 is 0x00000010",
        "A4 is 0x78120966",
        "(0x00001070).W is 0x79BA",
    });
    When({
        "MOVEA.W (0x5E, PC, A2.L), A4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 14",
        "A2 is 0x00000010",
        "A4 is 0x000079BA",
        "(0x00001070).W is 0x79BA",
    });
}

TEST_F(MOVEATestWord, ImmediateWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "A4 is 0x78120966",
    });
    When({
        "MOVEA.W #0x79BA, A4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 8",
        "A4 is 0x000079BA",
    });
}

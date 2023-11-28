#include "M68000/Fixtures/M68000Test.h"

class MOVEATestLong : public M68000Test {};

TEST_F(MOVEATestLong, DataDirectWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0x347879BA",
        "A4 is 0x78120966",
    });
    When({
        "MOVEA.L D1, A4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x347879BA",
        "A4 is 0x347879BA",
    });
}

TEST_F(MOVEATestLong, AddressDirectWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "A1 is 0x347879BA",
        "A4 is 0x78120966",
    });
    When({
        "MOVEA.L A1, A4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 4",
        "A1 is 0x347879BA",
        "A4 is 0x347879BA",
    });
}

TEST_F(MOVEATestLong, AddressIndirectWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A4 is 0x78120966",
        "(0x00005000).L is 0x347879BA",
    });
    When({
        "MOVEA.L (A1), A4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 12",
        "A1 is 0x00005000",
        "A4 is 0x347879BA",
        "(0x00005000).L is 0x347879BA",
    });
}

TEST_F(MOVEATestLong, AddressIncrementWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A4 is 0x78120966",
        "(0x00005000).L is 0x347879BA",
    });
    When({
        "MOVEA.L (A1)+, A4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 12",
        "A1 is 0x00005004",
        "A4 is 0x347879BA",
        "(0x00005000).L is 0x347879BA",
    });
}

TEST_F(MOVEATestLong, AddressDecrementWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A4 is 0x78120966",
        "(0x00004FFC).L is 0x347879BA",
    });
    When({
        "MOVEA.L -(A1), A4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 14",
        "A1 is 0x00004FFC",
        "A4 is 0x347879BA",
        "(0x00004FFC).L is 0x347879BA",
    });
}

TEST_F(MOVEATestLong, AddressDisplacementWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A4 is 0x78120966",
        "(0x0000503C).L is 0x347879BA",
    });
    When({
        "MOVEA.L (0x003C, A1), A4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 16",
        "A1 is 0x00005000",
        "A4 is 0x347879BA",
        "(0x0000503C).L is 0x347879BA",
    });
}

TEST_F(MOVEATestLong, AddressIndexWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "A4 is 0x78120966",
        "(0x0000506E).L is 0x347879BA",
    });
    When({
        "MOVEA.L (0x5E, A1, A2.L), A4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 18",
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "A4 is 0x347879BA",
        "(0x0000506E).L is 0x347879BA",
    });
}

TEST_F(MOVEATestLong, ShortWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "A4 is 0x78120966",
        "(0x00005000).L is 0x347879BA",
    });
    When({
        "MOVEA.L (0x5000).W, A4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 16",
        "A4 is 0x347879BA",
        "(0x00005000).L is 0x347879BA",
    });
}

TEST_F(MOVEATestLong, LongWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "A4 is 0x78120966",
        "(0x00005000).L is 0x347879BA",
    });
    When({
        "MOVEA.L (0x00005000).L, A4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1006",
        "CYCLES is 20",
        "A4 is 0x347879BA",
        "(0x00005000).L is 0x347879BA",
    });
}

TEST_F(MOVEATestLong, PCDisplacementWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "A4 is 0x78120966",
        "(0x0000103E).L is 0x347879BA",
    });
    When({
        "MOVEA.L (0x003C, PC), A4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 16",
        "A4 is 0x347879BA",
        "(0x0000103E).L is 0x347879BA",
    });
}

TEST_F(MOVEATestLong, PCIndexWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "A2 is 0x00000010",
        "A4 is 0x78120966",
        "(0x00001070).L is 0x347879BA",
    });
    When({
        "MOVEA.L (0x5E, PC, A2.L), A4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 18",
        "A2 is 0x00000010",
        "A4 is 0x347879BA",
        "(0x00001070).L is 0x347879BA",
    });
}

TEST_F(MOVEATestLong, ImmediateWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "A4 is 0x78120966",
    });
    When({
        "MOVEA.L #0x347879BA, A4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1006",
        "CYCLES is 12",
        "A4 is 0x347879BA",
    });
}

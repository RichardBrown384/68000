#include "M68000/Fixtures/M68000Test.h"

class MOVETestLong_Short : public M68000Test {};

TEST_F(MOVETestLong_Short, DataDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x347899BA",
        "(0x00006000).L is 0x78120966",
    });
    When({
        "MOVE.L D1, (0x6000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "D1 is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_Short, AddressDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x347899BA",
        "(0x00006000).L is 0x78120966",
    });
    When({
        "MOVE.L A1, (0x6000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "A1 is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_Short, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
    });
    When({
        "MOVE.L (A1), (0x6000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 24",
        "A1 is 0x00005000",
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_Short, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
    });
    When({
        "MOVE.L (A1)+, (0x6000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 24",
        "A1 is 0x00005004",
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_Short, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "(0x00004FFC).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
    });
    When({
        "MOVE.L -(A1), (0x6000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 26",
        "A1 is 0x00004FFC",
        "(0x00004FFC).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_Short, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "(0x0000503C).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
    });
    When({
        "MOVE.L (0x003C, A1), (0x6000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 28",
        "A1 is 0x00005000",
        "(0x0000503C).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_Short, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
    });
    When({
        "MOVE.L (0x5E, A1, A2.L), (0x6000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 30",
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_Short, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
    });
    When({
        "MOVE.L (0x5000).W, (0x6000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 28",
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_Short, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
    });
    When({
        "MOVE.L (0x00005000).L, (0x6000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1008",
        "CYCLES is 32",
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_Short, PCDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x0000103E).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
    });
    When({
        "MOVE.L (0x003C, PC), (0x6000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 28",
        "(0x0000103E).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_Short, PCIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A2 is 0x00000010",
        "(0x00001070).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
    });
    When({
        "MOVE.L (0x5E, PC, A2.L), (0x6000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 30",
        "A2 is 0x00000010",
        "(0x00001070).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_Short, ImmediateWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).L is 0x78120966",
    });
    When({
        "MOVE.L #0x347899BA, (0x6000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1008",
        "CYCLES is 24",
        "(0x00006000).L is 0x347899BA",
    });
}

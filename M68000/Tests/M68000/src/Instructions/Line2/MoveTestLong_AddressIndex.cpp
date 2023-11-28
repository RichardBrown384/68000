#include "M68000/Fixtures/M68000Test.h"

class MOVETestLong_AddressIndex : public M68000Test {};

TEST_F(MOVETestLong_AddressIndex, DataDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x347899BA",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0x78120966",
    });
    When({
        "MOVE.L D1, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "D1 is 0x347899BA",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_AddressIndex, AddressDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x347899BA",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0x78120966",
    });
    When({
        "MOVE.L A1, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "A1 is 0x347899BA",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_AddressIndex, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x00005000).L is 0x347899BA",
        "(0x0000608E).L is 0x78120966",
    });
    When({
        "MOVE.L (A1), (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 26",
        "A1 is 0x00005000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x00005000).L is 0x347899BA",
        "(0x0000608E).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_AddressIndex, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x00005000).L is 0x347899BA",
        "(0x0000608E).L is 0x78120966",
    });
    When({
        "MOVE.L (A1)+, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 26",
        "A1 is 0x00005004",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x00005000).L is 0x347899BA",
        "(0x0000608E).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_AddressIndex, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x00004FFC).L is 0x347899BA",
        "(0x0000608E).L is 0x78120966",
    });
    When({
        "MOVE.L -(A1), (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 28",
        "A1 is 0x00004FFC",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x00004FFC).L is 0x347899BA",
        "(0x0000608E).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_AddressIndex, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000503C).L is 0x347899BA",
        "(0x0000608E).L is 0x78120966",
    });
    When({
        "MOVE.L (0x003C, A1), (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 30",
        "A1 is 0x00005000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000503C).L is 0x347899BA",
        "(0x0000608E).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_AddressIndex, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000506E).L is 0x347899BA",
        "(0x0000608E).L is 0x78120966",
    });
    When({
        "MOVE.L (0x5E, A1, A2.L), (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 32",
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000506E).L is 0x347899BA",
        "(0x0000608E).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_AddressIndex, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x00005000).L is 0x347899BA",
        "(0x0000608E).L is 0x78120966",
    });
    When({
        "MOVE.L (0x5000).W, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 30",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x00005000).L is 0x347899BA",
        "(0x0000608E).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_AddressIndex, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x00005000).L is 0x347899BA",
        "(0x0000608E).L is 0x78120966",
    });
    When({
        "MOVE.L (0x00005000).L, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1008",
        "CYCLES is 34",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x00005000).L is 0x347899BA",
        "(0x0000608E).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_AddressIndex, PCDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000103E).L is 0x347899BA",
        "(0x0000608E).L is 0x78120966",
    });
    When({
        "MOVE.L (0x003C, PC), (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 30",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000103E).L is 0x347899BA",
        "(0x0000608E).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_AddressIndex, PCIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A2 is 0x00000010",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x00001070).L is 0x347899BA",
        "(0x0000608E).L is 0x78120966",
    });
    When({
        "MOVE.L (0x5E, PC, A2.L), (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 32",
        "A2 is 0x00000010",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x00001070).L is 0x347899BA",
        "(0x0000608E).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_AddressIndex, ImmediateWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0x78120966",
    });
    When({
        "MOVE.L #0x347899BA, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1008",
        "CYCLES is 26",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0x347899BA",
    });
}

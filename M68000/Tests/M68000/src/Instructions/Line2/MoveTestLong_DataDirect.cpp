#include "M68000/Fixtures/M68000Test.h"

class MOVETestLong_DataDirect : public M68000Test {};

TEST_F(MOVETestLong_DataDirect, DataDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x347899BA",
        "D4 is 0x78120966",
    });
    When({
        "MOVE.L D1, D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x347899BA",
        "D4 is 0x347899BA",
    });
}

TEST_F(MOVETestLong_DataDirect, AddressDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x78120966",
        "A1 is 0x347899BA",
    });
    When({
        "MOVE.L A1, D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D4 is 0x347899BA",
        "A1 is 0x347899BA",
    });
}

TEST_F(MOVETestLong_DataDirect, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x78120966",
        "A1 is 0x00005000",
        "(0x00005000).L is 0x347899BA",
    });
    When({
        "MOVE.L (A1), D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D4 is 0x347899BA",
        "A1 is 0x00005000",
        "(0x00005000).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_DataDirect, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x78120966",
        "A1 is 0x00005000",
        "(0x00005000).L is 0x347899BA",
    });
    When({
        "MOVE.L (A1)+, D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D4 is 0x347899BA",
        "A1 is 0x00005004",
        "(0x00005000).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_DataDirect, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x78120966",
        "A1 is 0x00005000",
        "(0x00004FFC).L is 0x347899BA",
    });
    When({
        "MOVE.L -(A1), D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D4 is 0x347899BA",
        "A1 is 0x00004FFC",
        "(0x00004FFC).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_DataDirect, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x78120966",
        "A1 is 0x00005000",
        "(0x0000503C).L is 0x347899BA",
    });
    When({
        "MOVE.L (0x003C, A1), D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "D4 is 0x347899BA",
        "A1 is 0x00005000",
        "(0x0000503C).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_DataDirect, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x78120966",
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).L is 0x347899BA",
    });
    When({
        "MOVE.L (0x5E, A1, A2.L), D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "D4 is 0x347899BA",
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_DataDirect, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x78120966",
        "(0x00005000).L is 0x347899BA",
    });
    When({
        "MOVE.L (0x5000).W, D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "D4 is 0x347899BA",
        "(0x00005000).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_DataDirect, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x78120966",
        "(0x00005000).L is 0x347899BA",
    });
    When({
        "MOVE.L (0x00005000).L, D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 20",
        "D4 is 0x347899BA",
        "(0x00005000).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_DataDirect, PCDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x78120966",
        "(0x0000103E).L is 0x347899BA",
    });
    When({
        "MOVE.L (0x003C, PC), D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "D4 is 0x347899BA",
        "(0x0000103E).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_DataDirect, PCIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x78120966",
        "A2 is 0x00000010",
        "(0x00001070).L is 0x347899BA",
    });
    When({
        "MOVE.L (0x5E, PC, A2.L), D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "D4 is 0x347899BA",
        "A2 is 0x00000010",
        "(0x00001070).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_DataDirect, ImmediateWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x78120966",
    });
    When({
        "MOVE.L #0x347899BA, D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 12",
        "D4 is 0x347899BA",
    });
}

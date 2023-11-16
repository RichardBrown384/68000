#include "M68000/Fixtures/M68000Test.h"

class MOVETestLong_Short : public M68000Test {};

TEST_F(MOVETestLong_Short, DataDirectWorks) {
    Given({
        "D1 is 0x347899BA",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L D1, (0x6000).W"
    });
    Then({
        "D1 is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_Short, AddressDirectWorks) {
    Given({
        "A1 is 0x347899BA",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L A1, (0x6000).W"
    });
    Then({
        "A1 is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_Short, AddressIndirectWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (A1), (0x6000).W"
    });
    Then({
        "A1 is 0x00005000",
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_Short, AddressIncrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (A1)+, (0x6000).W"
    });
    Then({
        "A1 is 0x00005004",
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_Short, AddressDecrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00004FFC).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L -(A1), (0x6000).W"
    });
    Then({
        "A1 is 0x00004FFC",
        "(0x00004FFC).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_Short, AddressDisplacementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x0000503C).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (0x003C, A1), (0x6000).W"
    });
    Then({
        "A1 is 0x00005000",
        "(0x0000503C).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_Short, AddressIndexWorks) {
    Given({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (0x5E, A1, A2.L), (0x6000).W"
    });
    Then({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_Short, ShortWorks) {
    Given({
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (0x5000).W, (0x6000).W"
    });
    Then({
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_Short, LongWorks) {
    Given({
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (0x00005000).L, (0x6000).W"
    });
    Then({
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_Short, PCDisplacementWorks) {
    Given({
        "(0x0000103E).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (0x003C, PC), (0x6000).W"
    });
    Then({
        "(0x0000103E).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_Short, PCIndexWorks) {
    Given({
        "A2 is 0x00000010",
        "(0x00001070).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (0x5E, PC, A2.L), (0x6000).W"
    });
    Then({
        "A2 is 0x00000010",
        "(0x00001070).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_Short, ImmediateWorks) {
    Given({
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L #0x347899BA, (0x6000).W"
    });
    Then({
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

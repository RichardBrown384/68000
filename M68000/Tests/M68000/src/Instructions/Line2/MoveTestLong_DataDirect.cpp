#include "M68000/Fixtures/M68000Test.h"

class MOVETestLong_DataDirect : public M68000Test {};

TEST_F(MOVETestLong_DataDirect, DataDirectWorks) {
    Given({
        "D1 is 0x347899BA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L D1, D4"
    });
    Then({
        "D1 is 0x347899BA",
        "D4 is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_DataDirect, AddressDirectWorks) {
    Given({
        "A1 is 0x347899BA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L A1, D4"
    });
    Then({
        "A1 is 0x347899BA",
        "D4 is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_DataDirect, AddressIndirectWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).L is 0x347899BA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (A1), D4"
    });
    Then({
        "A1 is 0x00005000",
        "(0x00005000).L is 0x347899BA",
        "D4 is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_DataDirect, AddressIncrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).L is 0x347899BA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (A1)+, D4"
    });
    Then({
        "A1 is 0x00005004",
        "(0x00005000).L is 0x347899BA",
        "D4 is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_DataDirect, AddressDecrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00004FFC).L is 0x347899BA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L -(A1), D4"
    });
    Then({
        "A1 is 0x00004FFC",
        "(0x00004FFC).L is 0x347899BA",
        "D4 is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_DataDirect, AddressDisplacementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x0000503C).L is 0x347899BA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (0x003C, A1), D4"
    });
    Then({
        "A1 is 0x00005000",
        "(0x0000503C).L is 0x347899BA",
        "D4 is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_DataDirect, AddressIndexWorks) {
    Given({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).L is 0x347899BA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (0x5E, A1, A2.L), D4"
    });
    Then({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).L is 0x347899BA",
        "D4 is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_DataDirect, ShortWorks) {
    Given({
        "(0x00005000).L is 0x347899BA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (0x5000).W, D4"
    });
    Then({
        "(0x00005000).L is 0x347899BA",
        "D4 is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_DataDirect, LongWorks) {
    Given({
        "(0x00005000).L is 0x347899BA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (0x00005000).L, D4"
    });
    Then({
        "(0x00005000).L is 0x347899BA",
        "D4 is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_DataDirect, PCDisplacementWorks) {
    Given({
        "(0x0000103E).L is 0x347899BA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (0x003C, PC), D4"
    });
    Then({
        "(0x0000103E).L is 0x347899BA",
        "D4 is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_DataDirect, PCIndexWorks) {
    Given({
        "A2 is 0x00000010",
        "(0x00001070).L is 0x347899BA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (0x5E, PC, A2.L), D4"
    });
    Then({
        "A2 is 0x00000010",
        "(0x00001070).L is 0x347899BA",
        "D4 is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_DataDirect, ImmediateWorks) {
    Given({
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L #0x347899BA, D4"
    });
    Then({
        "D4 is 0x347899BA",
        "SR is S,0,0"
    });
}

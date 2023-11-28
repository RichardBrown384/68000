#include "M68000/Fixtures/M68000Test.h"

class MOVETestLong_AddressDecrement : public M68000Test {};

TEST_F(MOVETestLong_AddressDecrement, DataDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x347899BA",
        "A4 is 0x00006000",
        "(0x00005FFC).L is 0x78120966",
    });
    When({
        "MOVE.L D1, -(A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x347899BA",
        "A4 is 0x00005FFC",
        "(0x00005FFC).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_AddressDecrement, AddressDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x347899BA",
        "A4 is 0x00006000",
        "(0x00005FFC).L is 0x78120966",
    });
    When({
        "MOVE.L A1, -(A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "A1 is 0x347899BA",
        "A4 is 0x00005FFC",
        "(0x00005FFC).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_AddressDecrement, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A4 is 0x00006000",
        "(0x00005000).L is 0x347899BA",
        "(0x00005FFC).L is 0x78120966",
    });
    When({
        "MOVE.L (A1), -(A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 20",
        "A1 is 0x00005000",
        "A4 is 0x00005FFC",
        "(0x00005000).L is 0x347899BA",
        "(0x00005FFC).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_AddressDecrement, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A4 is 0x00006000",
        "(0x00005000).L is 0x347899BA",
        "(0x00005FFC).L is 0x78120966",
    });
    When({
        "MOVE.L (A1)+, -(A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 20",
        "A1 is 0x00005004",
        "A4 is 0x00005FFC",
        "(0x00005000).L is 0x347899BA",
        "(0x00005FFC).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_AddressDecrement, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A4 is 0x00006000",
        "(0x00004FFC).L is 0x347899BA",
        "(0x00005FFC).L is 0x78120966",
    });
    When({
        "MOVE.L -(A1), -(A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 22",
        "A1 is 0x00004FFC",
        "A4 is 0x00005FFC",
        "(0x00004FFC).L is 0x347899BA",
        "(0x00005FFC).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_AddressDecrement, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A4 is 0x00006000",
        "(0x0000503C).L is 0x347899BA",
        "(0x00005FFC).L is 0x78120966",
    });
    When({
        "MOVE.L (0x003C, A1), -(A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 24",
        "A1 is 0x00005000",
        "A4 is 0x00005FFC",
        "(0x0000503C).L is 0x347899BA",
        "(0x00005FFC).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_AddressDecrement, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "A4 is 0x00006000",
        "(0x0000506E).L is 0x347899BA",
        "(0x00005FFC).L is 0x78120966",
    });
    When({
        "MOVE.L (0x5E, A1, A2.L), -(A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 26",
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "A4 is 0x00005FFC",
        "(0x0000506E).L is 0x347899BA",
        "(0x00005FFC).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_AddressDecrement, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005000).L is 0x347899BA",
        "(0x00005FFC).L is 0x78120966",
    });
    When({
        "MOVE.L (0x5000).W, -(A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 24",
        "A4 is 0x00005FFC",
        "(0x00005000).L is 0x347899BA",
        "(0x00005FFC).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_AddressDecrement, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005000).L is 0x347899BA",
        "(0x00005FFC).L is 0x78120966",
    });
    When({
        "MOVE.L (0x00005000).L, -(A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 28",
        "A4 is 0x00005FFC",
        "(0x00005000).L is 0x347899BA",
        "(0x00005FFC).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_AddressDecrement, PCDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x0000103E).L is 0x347899BA",
        "(0x00005FFC).L is 0x78120966",
    });
    When({
        "MOVE.L (0x003C, PC), -(A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 24",
        "A4 is 0x00005FFC",
        "(0x0000103E).L is 0x347899BA",
        "(0x00005FFC).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_AddressDecrement, PCIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A2 is 0x00000010",
        "A4 is 0x00006000",
        "(0x00001070).L is 0x347899BA",
        "(0x00005FFC).L is 0x78120966",
    });
    When({
        "MOVE.L (0x5E, PC, A2.L), -(A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 26",
        "A2 is 0x00000010",
        "A4 is 0x00005FFC",
        "(0x00001070).L is 0x347899BA",
        "(0x00005FFC).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_AddressDecrement, ImmediateWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005FFC).L is 0x78120966",
    });
    When({
        "MOVE.L #0x347899BA, -(A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 20",
        "A4 is 0x00005FFC",
        "(0x00005FFC).L is 0x347899BA",
    });
}

#include "M68000/Fixtures/M68000Test.h"

class MOVETestLong_Long : public M68000Test {};

TEST_F(MOVETestLong_Long, DataDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x347899BA",
        "(0x00006000).L is 0x78120966",
    });
    When({
        "MOVE.L D1, (0x00006000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 20",
        "D1 is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_Long, AddressDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x347899BA",
        "(0x00006000).L is 0x78120966",
    });
    When({
        "MOVE.L A1, (0x00006000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 20",
        "A1 is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_Long, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
    });
    When({
        "MOVE.L (A1), (0x00006000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 28",
        "A1 is 0x00005000",
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_Long, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
    });
    When({
        "MOVE.L (A1)+, (0x00006000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 28",
        "A1 is 0x00005004",
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_Long, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "(0x00004FFC).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
    });
    When({
        "MOVE.L -(A1), (0x00006000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 30",
        "A1 is 0x00004FFC",
        "(0x00004FFC).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_Long, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "(0x0000503C).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
    });
    When({
        "MOVE.L (0x003C, A1), (0x00006000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1008",
        "CYCLES is 32",
        "A1 is 0x00005000",
        "(0x0000503C).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_Long, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
    });
    When({
        "MOVE.L (0x5E, A1, A2.L), (0x00006000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1008",
        "CYCLES is 34",
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_Long, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
    });
    When({
        "MOVE.L (0x5000).W, (0x00006000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1008",
        "CYCLES is 32",
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_Long, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
    });
    When({
        "MOVE.L (0x00005000).L, (0x00006000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x100A",
        "CYCLES is 36",
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_Long, PCDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x0000103E).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
    });
    When({
        "MOVE.L (0x003C, PC), (0x00006000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1008",
        "CYCLES is 32",
        "(0x0000103E).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_Long, PCIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A2 is 0x00000010",
        "(0x00001070).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
    });
    When({
        "MOVE.L (0x5E, PC, A2.L), (0x00006000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1008",
        "CYCLES is 34",
        "A2 is 0x00000010",
        "(0x00001070).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
    });
}

TEST_F(MOVETestLong_Long, ImmediateWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).L is 0x78120966",
    });
    When({
        "MOVE.L #0x347899BA, (0x00006000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x100A",
        "CYCLES is 28",
        "(0x00006000).L is 0x347899BA",
    });
}

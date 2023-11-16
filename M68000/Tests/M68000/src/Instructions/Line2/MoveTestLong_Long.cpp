#include "M68000/Fixtures/M68000Test.h"

class MOVETestLong_Long : public M68000Test {};

TEST_F(MOVETestLong_Long, DataDirectWorks) {
    Given({
        "D1 is 0x347899BA",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L D1, (0x00006000).L"
    });
    Then({
        "D1 is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_Long, AddressDirectWorks) {
    Given({
        "A1 is 0x347899BA",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L A1, (0x00006000).L"
    });
    Then({
        "A1 is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_Long, AddressIndirectWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (A1), (0x00006000).L"
    });
    Then({
        "A1 is 0x00005000",
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_Long, AddressIncrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (A1)+, (0x00006000).L"
    });
    Then({
        "A1 is 0x00005004",
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_Long, AddressDecrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00004FFC).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L -(A1), (0x00006000).L"
    });
    Then({
        "A1 is 0x00004FFC",
        "(0x00004FFC).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_Long, AddressDisplacementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x0000503C).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (0x003C, A1), (0x00006000).L"
    });
    Then({
        "A1 is 0x00005000",
        "(0x0000503C).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_Long, AddressIndexWorks) {
    Given({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (0x5E, A1, A2.L), (0x00006000).L"
    });
    Then({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_Long, ShortWorks) {
    Given({
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (0x5000).W, (0x00006000).L"
    });
    Then({
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_Long, LongWorks) {
    Given({
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (0x00005000).L, (0x00006000).L"
    });
    Then({
        "(0x00005000).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_Long, PCDisplacementWorks) {
    Given({
        "(0x0000103E).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (0x003C, PC), (0x00006000).L"
    });
    Then({
        "(0x0000103E).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_Long, PCIndexWorks) {
    Given({
        "A2 is 0x00000010",
        "(0x00001070).L is 0x347899BA",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (0x5E, PC, A2.L), (0x00006000).L"
    });
    Then({
        "A2 is 0x00000010",
        "(0x00001070).L is 0x347899BA",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_Long, ImmediateWorks) {
    Given({
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L #0x347899BA, (0x00006000).L"
    });
    Then({
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

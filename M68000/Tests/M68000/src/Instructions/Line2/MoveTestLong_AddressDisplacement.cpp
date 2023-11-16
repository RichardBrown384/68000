#include "M68000/Fixtures/M68000Test.h"

class MOVETestLong_AddressDisplacement : public M68000Test {};

TEST_F(MOVETestLong_AddressDisplacement, DataDirectWorks) {
    Given({
        "D1 is 0x347899BA",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L D1, (0x004C, A4)"
    });
    Then({
        "D1 is 0x347899BA",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_AddressDisplacement, AddressDirectWorks) {
    Given({
        "A1 is 0x347899BA",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L A1, (0x004C, A4)"
    });
    Then({
        "A1 is 0x347899BA",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_AddressDisplacement, AddressIndirectWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).L is 0x347899BA",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (A1), (0x004C, A4)"
    });
    Then({
        "A1 is 0x00005000",
        "(0x00005000).L is 0x347899BA",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_AddressDisplacement, AddressIncrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).L is 0x347899BA",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (A1)+, (0x004C, A4)"
    });
    Then({
        "A1 is 0x00005004",
        "(0x00005000).L is 0x347899BA",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_AddressDisplacement, AddressDecrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00004FFC).L is 0x347899BA",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L -(A1), (0x004C, A4)"
    });
    Then({
        "A1 is 0x00004FFC",
        "(0x00004FFC).L is 0x347899BA",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_AddressDisplacement, AddressDisplacementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x0000503C).L is 0x347899BA",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (0x003C, A1), (0x004C, A4)"
    });
    Then({
        "A1 is 0x00005000",
        "(0x0000503C).L is 0x347899BA",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_AddressDisplacement, AddressIndexWorks) {
    Given({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).L is 0x347899BA",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (0x5E, A1, A2.L), (0x004C, A4)"
    });
    Then({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).L is 0x347899BA",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_AddressDisplacement, ShortWorks) {
    Given({
        "(0x00005000).L is 0x347899BA",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (0x5000).W, (0x004C, A4)"
    });
    Then({
        "(0x00005000).L is 0x347899BA",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_AddressDisplacement, LongWorks) {
    Given({
        "(0x00005000).L is 0x347899BA",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (0x00005000).L, (0x004C, A4)"
    });
    Then({
        "(0x00005000).L is 0x347899BA",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_AddressDisplacement, PCDisplacementWorks) {
    Given({
        "(0x0000103E).L is 0x347899BA",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (0x003C, PC), (0x004C, A4)"
    });
    Then({
        "(0x0000103E).L is 0x347899BA",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_AddressDisplacement, PCIndexWorks) {
    Given({
        "A2 is 0x00000010",
        "(0x00001070).L is 0x347899BA",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (0x5E, PC, A2.L), (0x004C, A4)"
    });
    Then({
        "A2 is 0x00000010",
        "(0x00001070).L is 0x347899BA",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_AddressDisplacement, ImmediateWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L #0x347899BA, (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x347899BA",
        "SR is S,0,0"
    });
}

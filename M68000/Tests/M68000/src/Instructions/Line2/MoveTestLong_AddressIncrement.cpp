#include "M68000/Fixtures/M68000Test.h"

class MOVETestLong_AddressIncrement : public M68000Test {};

TEST_F(MOVETestLong_AddressIncrement, DataDirectWorks) {
    Given({
        "D1 is 0x347899BA",
        "A4 is 0x00006000",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L D1, (A4)+"
    });
    Then({
        "D1 is 0x347899BA",
        "A4 is 0x00006004",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_AddressIncrement, AddressDirectWorks) {
    Given({
        "A1 is 0x347899BA",
        "A4 is 0x00006000",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L A1, (A4)+"
    });
    Then({
        "A1 is 0x347899BA",
        "A4 is 0x00006004",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_AddressIncrement, AddressIndirectWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).L is 0x347899BA",
        "A4 is 0x00006000",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (A1), (A4)+"
    });
    Then({
        "A1 is 0x00005000",
        "(0x00005000).L is 0x347899BA",
        "A4 is 0x00006004",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_AddressIncrement, AddressIncrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).L is 0x347899BA",
        "A4 is 0x00006000",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (A1)+, (A4)+"
    });
    Then({
        "A1 is 0x00005004",
        "(0x00005000).L is 0x347899BA",
        "A4 is 0x00006004",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_AddressIncrement, AddressDecrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00004FFC).L is 0x347899BA",
        "A4 is 0x00006000",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L -(A1), (A4)+"
    });
    Then({
        "A1 is 0x00004FFC",
        "(0x00004FFC).L is 0x347899BA",
        "A4 is 0x00006004",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_AddressIncrement, AddressDisplacementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x0000503C).L is 0x347899BA",
        "A4 is 0x00006000",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (0x003C, A1), (A4)+"
    });
    Then({
        "A1 is 0x00005000",
        "(0x0000503C).L is 0x347899BA",
        "A4 is 0x00006004",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_AddressIncrement, AddressIndexWorks) {
    Given({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).L is 0x347899BA",
        "A4 is 0x00006000",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (0x5E, A1, A2.L), (A4)+"
    });
    Then({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).L is 0x347899BA",
        "A4 is 0x00006004",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_AddressIncrement, ShortWorks) {
    Given({
        "(0x00005000).L is 0x347899BA",
        "A4 is 0x00006000",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (0x5000).W, (A4)+"
    });
    Then({
        "(0x00005000).L is 0x347899BA",
        "A4 is 0x00006004",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_AddressIncrement, LongWorks) {
    Given({
        "(0x00005000).L is 0x347899BA",
        "A4 is 0x00006000",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (0x00005000).L, (A4)+"
    });
    Then({
        "(0x00005000).L is 0x347899BA",
        "A4 is 0x00006004",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_AddressIncrement, PCDisplacementWorks) {
    Given({
        "(0x0000103E).L is 0x347899BA",
        "A4 is 0x00006000",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (0x003C, PC), (A4)+"
    });
    Then({
        "(0x0000103E).L is 0x347899BA",
        "A4 is 0x00006004",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_AddressIncrement, PCIndexWorks) {
    Given({
        "A2 is 0x00000010",
        "(0x00001070).L is 0x347899BA",
        "A4 is 0x00006000",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L (0x5E, PC, A2.L), (A4)+"
    });
    Then({
        "A2 is 0x00000010",
        "(0x00001070).L is 0x347899BA",
        "A4 is 0x00006004",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

TEST_F(MOVETestLong_AddressIncrement, ImmediateWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).L is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.L #0x347899BA, (A4)+"
    });
    Then({
        "A4 is 0x00006004",
        "(0x00006000).L is 0x347899BA",
        "SR is S,0,0"
    });
}

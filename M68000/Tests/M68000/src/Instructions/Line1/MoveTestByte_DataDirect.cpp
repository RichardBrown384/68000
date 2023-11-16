#include "M68000/Fixtures/M68000Test.h"

class MOVETestByte_DataDirect : public M68000Test {};

TEST_F(MOVETestByte_DataDirect, DataDirectWorks) {
    Given({
        "D1 is 0x347899BA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.B D1, D4"
    });
    Then({
        "D1 is 0x347899BA",
        "D4 is 0x781209BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_DataDirect, AddressIndirectWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).B is 0xBA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (A1), D4"
    });
    Then({
        "A1 is 0x00005000",
        "(0x00005000).B is 0xBA",
        "D4 is 0x781209BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_DataDirect, AddressIncrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).B is 0xBA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (A1)+, D4"
    });
    Then({
        "A1 is 0x00005001",
        "(0x00005000).B is 0xBA",
        "D4 is 0x781209BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_DataDirect, AddressDecrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00004FFF).B is 0xBA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.B -(A1), D4"
    });
    Then({
        "A1 is 0x00004FFF",
        "(0x00004FFF).B is 0xBA",
        "D4 is 0x781209BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_DataDirect, AddressDisplacementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x0000503C).B is 0xBA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (0x003C, A1), D4"
    });
    Then({
        "A1 is 0x00005000",
        "(0x0000503C).B is 0xBA",
        "D4 is 0x781209BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_DataDirect, AddressIndexWorks) {
    Given({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).B is 0xBA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (0x5E, A1, A2.L), D4"
    });
    Then({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).B is 0xBA",
        "D4 is 0x781209BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_DataDirect, ShortWorks) {
    Given({
        "(0x00005000).B is 0xBA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (0x5000).W, D4"
    });
    Then({
        "(0x00005000).B is 0xBA",
        "D4 is 0x781209BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_DataDirect, LongWorks) {
    Given({
        "(0x00005000).B is 0xBA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (0x00005000).L, D4"
    });
    Then({
        "(0x00005000).B is 0xBA",
        "D4 is 0x781209BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_DataDirect, PCDisplacementWorks) {
    Given({
        "(0x0000103E).B is 0xBA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (0x003C, PC), D4"
    });
    Then({
        "(0x0000103E).B is 0xBA",
        "D4 is 0x781209BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_DataDirect, PCIndexWorks) {
    Given({
        "A2 is 0x00000010",
        "(0x00001070).B is 0xBA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (0x5E, PC, A2.L), D4"
    });
    Then({
        "A2 is 0x00000010",
        "(0x00001070).B is 0xBA",
        "D4 is 0x781209BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_DataDirect, ImmediateWorks) {
    Given({
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.B #0xBA, D4"
    });
    Then({
        "D4 is 0x781209BA",
        "SR is S,0,N"
    });
}

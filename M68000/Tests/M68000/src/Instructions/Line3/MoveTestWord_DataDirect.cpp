#include "M68000/Fixtures/M68000Test.h"

class MOVETestWord_DataDirect : public M68000Test {};

TEST_F(MOVETestWord_DataDirect, DataDirectWorks) {
    Given({
        "D1 is 0x347899BA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W D1, D4"
    });
    Then({
        "D1 is 0x347899BA",
        "D4 is 0x781299BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_DataDirect, AddressDirectWorks) {
    Given({
        "A1 is 0x347899BA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W A1, D4"
    });
    Then({
        "A1 is 0x347899BA",
        "D4 is 0x781299BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_DataDirect, AddressIndirectWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).W is 0x99BA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (A1), D4"
    });
    Then({
        "A1 is 0x00005000",
        "(0x00005000).W is 0x99BA",
        "D4 is 0x781299BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_DataDirect, AddressIncrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).W is 0x99BA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (A1)+, D4"
    });
    Then({
        "A1 is 0x00005002",
        "(0x00005000).W is 0x99BA",
        "D4 is 0x781299BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_DataDirect, AddressDecrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00004FFE).W is 0x99BA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W -(A1), D4"
    });
    Then({
        "A1 is 0x00004FFE",
        "(0x00004FFE).W is 0x99BA",
        "D4 is 0x781299BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_DataDirect, AddressDisplacementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x0000503C).W is 0x99BA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x003C, A1), D4"
    });
    Then({
        "A1 is 0x00005000",
        "(0x0000503C).W is 0x99BA",
        "D4 is 0x781299BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_DataDirect, AddressIndexWorks) {
    Given({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).W is 0x99BA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x5E, A1, A2.L), D4"
    });
    Then({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).W is 0x99BA",
        "D4 is 0x781299BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_DataDirect, ShortWorks) {
    Given({
        "(0x00005000).W is 0x99BA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x5000).W, D4"
    });
    Then({
        "(0x00005000).W is 0x99BA",
        "D4 is 0x781299BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_DataDirect, LongWorks) {
    Given({
        "(0x00005000).W is 0x99BA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x00005000).L, D4"
    });
    Then({
        "(0x00005000).W is 0x99BA",
        "D4 is 0x781299BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_DataDirect, PCDisplacementWorks) {
    Given({
        "(0x0000103E).W is 0x99BA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x003C, PC), D4"
    });
    Then({
        "(0x0000103E).W is 0x99BA",
        "D4 is 0x781299BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_DataDirect, PCIndexWorks) {
    Given({
        "A2 is 0x00000010",
        "(0x00001070).W is 0x99BA",
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x5E, PC, A2.L), D4"
    });
    Then({
        "A2 is 0x00000010",
        "(0x00001070).W is 0x99BA",
        "D4 is 0x781299BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_DataDirect, ImmediateWorks) {
    Given({
        "D4 is 0x78120966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W #0x99BA, D4"
    });
    Then({
        "D4 is 0x781299BA",
        "SR is S,0,N"
    });
}

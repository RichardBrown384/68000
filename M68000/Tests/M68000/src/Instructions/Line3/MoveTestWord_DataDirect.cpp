#include "M68000/Fixtures/M68000Test.h"

class MOVETestWord_DataDirect : public M68000Test {};

TEST_F(MOVETestWord_DataDirect, DataDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x347899BA",
        "D4 is 0x78120966",
    });
    When({
        "MOVE.W D1, D4"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x347899BA",
        "D4 is 0x781299BA",
    });
}

TEST_F(MOVETestWord_DataDirect, AddressDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x78120966",
        "A1 is 0x347899BA",
    });
    When({
        "MOVE.W A1, D4"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 4",
        "D4 is 0x781299BA",
        "A1 is 0x347899BA",
    });
}

TEST_F(MOVETestWord_DataDirect, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x78120966",
        "A1 is 0x00005000",
        "(0x00005000).W is 0x99BA",
    });
    When({
        "MOVE.W (A1), D4"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 8",
        "D4 is 0x781299BA",
        "A1 is 0x00005000",
        "(0x00005000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_DataDirect, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x78120966",
        "A1 is 0x00005000",
        "(0x00005000).W is 0x99BA",
    });
    When({
        "MOVE.W (A1)+, D4"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 8",
        "D4 is 0x781299BA",
        "A1 is 0x00005002",
        "(0x00005000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_DataDirect, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x78120966",
        "A1 is 0x00005000",
        "(0x00004FFE).W is 0x99BA",
    });
    When({
        "MOVE.W -(A1), D4"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 10",
        "D4 is 0x781299BA",
        "A1 is 0x00004FFE",
        "(0x00004FFE).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_DataDirect, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x78120966",
        "A1 is 0x00005000",
        "(0x0000503C).W is 0x99BA",
    });
    When({
        "MOVE.W (0x003C, A1), D4"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 12",
        "D4 is 0x781299BA",
        "A1 is 0x00005000",
        "(0x0000503C).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_DataDirect, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x78120966",
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).W is 0x99BA",
    });
    When({
        "MOVE.W (0x5E, A1, A2.L), D4"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 14",
        "D4 is 0x781299BA",
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_DataDirect, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x78120966",
        "(0x00005000).W is 0x99BA",
    });
    When({
        "MOVE.W (0x5000).W, D4"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 12",
        "D4 is 0x781299BA",
        "(0x00005000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_DataDirect, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x78120966",
        "(0x00005000).W is 0x99BA",
    });
    When({
        "MOVE.W (0x00005000).L, D4"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 16",
        "D4 is 0x781299BA",
        "(0x00005000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_DataDirect, PCDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x78120966",
        "(0x0000103E).W is 0x99BA",
    });
    When({
        "MOVE.W (0x003C, PC), D4"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 12",
        "D4 is 0x781299BA",
        "(0x0000103E).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_DataDirect, PCIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x78120966",
        "A2 is 0x00000010",
        "(0x00001070).W is 0x99BA",
    });
    When({
        "MOVE.W (0x5E, PC, A2.L), D4"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 14",
        "D4 is 0x781299BA",
        "A2 is 0x00000010",
        "(0x00001070).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_DataDirect, ImmediateWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x78120966",
    });
    When({
        "MOVE.W #0x99BA, D4"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 8",
        "D4 is 0x781299BA",
    });
}

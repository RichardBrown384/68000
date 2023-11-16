#include "M68000/Fixtures/M68000Test.h"

class MOVETestWord_Short : public M68000Test {};

TEST_F(MOVETestWord_Short, DataDirectWorks) {
    Given({
        "D1 is 0x347899BA",
        "(0x00006000).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W D1, (0x6000).W"
    });
    Then({
        "D1 is 0x347899BA",
        "(0x00006000).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_Short, AddressDirectWorks) {
    Given({
        "A1 is 0x347899BA",
        "(0x00006000).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W A1, (0x6000).W"
    });
    Then({
        "A1 is 0x347899BA",
        "(0x00006000).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_Short, AddressIndirectWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (A1), (0x6000).W"
    });
    Then({
        "A1 is 0x00005000",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_Short, AddressIncrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (A1)+, (0x6000).W"
    });
    Then({
        "A1 is 0x00005002",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_Short, AddressDecrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00004FFE).W is 0x99BA",
        "(0x00006000).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W -(A1), (0x6000).W"
    });
    Then({
        "A1 is 0x00004FFE",
        "(0x00004FFE).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_Short, AddressDisplacementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x0000503C).W is 0x99BA",
        "(0x00006000).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x003C, A1), (0x6000).W"
    });
    Then({
        "A1 is 0x00005000",
        "(0x0000503C).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_Short, AddressIndexWorks) {
    Given({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).W is 0x99BA",
        "(0x00006000).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x5E, A1, A2.L), (0x6000).W"
    });
    Then({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_Short, ShortWorks) {
    Given({
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x5000).W, (0x6000).W"
    });
    Then({
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_Short, LongWorks) {
    Given({
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x00005000).L, (0x6000).W"
    });
    Then({
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_Short, PCDisplacementWorks) {
    Given({
        "(0x0000103E).W is 0x99BA",
        "(0x00006000).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x003C, PC), (0x6000).W"
    });
    Then({
        "(0x0000103E).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_Short, PCIndexWorks) {
    Given({
        "A2 is 0x00000010",
        "(0x00001070).W is 0x99BA",
        "(0x00006000).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x5E, PC, A2.L), (0x6000).W"
    });
    Then({
        "A2 is 0x00000010",
        "(0x00001070).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_Short, ImmediateWorks) {
    Given({
        "(0x00006000).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W #0x99BA, (0x6000).W"
    });
    Then({
        "(0x00006000).W is 0x99BA",
        "SR is S,0,N"
    });
}

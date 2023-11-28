#include "M68000/Fixtures/M68000Test.h"

class MOVETestWord_Short : public M68000Test {};

TEST_F(MOVETestWord_Short, DataDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x347899BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W D1, (0x6000).W"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x347899BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_Short, AddressDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x347899BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W A1, (0x6000).W"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 12",
        "A1 is 0x347899BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_Short, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W (A1), (0x6000).W"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 16",
        "A1 is 0x00005000",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_Short, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W (A1)+, (0x6000).W"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 16",
        "A1 is 0x00005002",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_Short, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "(0x00004FFE).W is 0x99BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W -(A1), (0x6000).W"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 18",
        "A1 is 0x00004FFE",
        "(0x00004FFE).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_Short, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "(0x0000503C).W is 0x99BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W (0x003C, A1), (0x6000).W"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 20",
        "A1 is 0x00005000",
        "(0x0000503C).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_Short, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).W is 0x99BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W (0x5E, A1, A2.L), (0x6000).W"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 22",
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_Short, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W (0x5000).W, (0x6000).W"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 20",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_Short, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W (0x00005000).L, (0x6000).W"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1008",
        "CYCLES is 24",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_Short, PCDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x0000103E).W is 0x99BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W (0x003C, PC), (0x6000).W"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 20",
        "(0x0000103E).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_Short, PCIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A2 is 0x00000010",
        "(0x00001070).W is 0x99BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W (0x5E, PC, A2.L), (0x6000).W"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 22",
        "A2 is 0x00000010",
        "(0x00001070).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_Short, ImmediateWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W #0x99BA, (0x6000).W"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 16",
        "(0x00006000).W is 0x99BA",
    });
}

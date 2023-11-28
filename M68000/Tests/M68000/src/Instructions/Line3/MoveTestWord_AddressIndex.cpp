#include "M68000/Fixtures/M68000Test.h"

class MOVETestWord_AddressIndex : public M68000Test {};

TEST_F(MOVETestWord_AddressIndex, DataDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x347899BA",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x0966",
    });
    When({
        "MOVE.W D1, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0x347899BA",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_AddressIndex, AddressDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x347899BA",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x0966",
    });
    When({
        "MOVE.W A1, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 14",
        "A1 is 0x347899BA",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_AddressIndex, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x00005000).W is 0x99BA",
        "(0x0000608E).W is 0x0966",
    });
    When({
        "MOVE.W (A1), (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 18",
        "A1 is 0x00005000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x00005000).W is 0x99BA",
        "(0x0000608E).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_AddressIndex, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x00005000).W is 0x99BA",
        "(0x0000608E).W is 0x0966",
    });
    When({
        "MOVE.W (A1)+, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 18",
        "A1 is 0x00005002",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x00005000).W is 0x99BA",
        "(0x0000608E).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_AddressIndex, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x00004FFE).W is 0x99BA",
        "(0x0000608E).W is 0x0966",
    });
    When({
        "MOVE.W -(A1), (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 20",
        "A1 is 0x00004FFE",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x00004FFE).W is 0x99BA",
        "(0x0000608E).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_AddressIndex, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000503C).W is 0x99BA",
        "(0x0000608E).W is 0x0966",
    });
    When({
        "MOVE.W (0x003C, A1), (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 22",
        "A1 is 0x00005000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000503C).W is 0x99BA",
        "(0x0000608E).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_AddressIndex, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000506E).W is 0x99BA",
        "(0x0000608E).W is 0x0966",
    });
    When({
        "MOVE.W (0x5E, A1, A2.L), (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 24",
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000506E).W is 0x99BA",
        "(0x0000608E).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_AddressIndex, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x00005000).W is 0x99BA",
        "(0x0000608E).W is 0x0966",
    });
    When({
        "MOVE.W (0x5000).W, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 22",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x00005000).W is 0x99BA",
        "(0x0000608E).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_AddressIndex, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x00005000).W is 0x99BA",
        "(0x0000608E).W is 0x0966",
    });
    When({
        "MOVE.W (0x00005000).L, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1008",
        "CYCLES is 26",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x00005000).W is 0x99BA",
        "(0x0000608E).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_AddressIndex, PCDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000103E).W is 0x99BA",
        "(0x0000608E).W is 0x0966",
    });
    When({
        "MOVE.W (0x003C, PC), (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 22",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000103E).W is 0x99BA",
        "(0x0000608E).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_AddressIndex, PCIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A2 is 0x00000010",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x00001070).W is 0x99BA",
        "(0x0000608E).W is 0x0966",
    });
    When({
        "MOVE.W (0x5E, PC, A2.L), (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 24",
        "A2 is 0x00000010",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x00001070).W is 0x99BA",
        "(0x0000608E).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_AddressIndex, ImmediateWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x0966",
    });
    When({
        "MOVE.W #0x99BA, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 18",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x99BA",
    });
}

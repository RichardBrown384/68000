#include "M68000/Fixtures/M68000Test.h"

class MOVETestWord_Long : public M68000Test {};

TEST_F(MOVETestWord_Long, DataDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x347899BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W D1, (0x00006000).L"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 16",
        "D1 is 0x347899BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_Long, AddressDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x347899BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W A1, (0x00006000).L"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 16",
        "A1 is 0x347899BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_Long, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W (A1), (0x00006000).L"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 20",
        "A1 is 0x00005000",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_Long, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W (A1)+, (0x00006000).L"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 20",
        "A1 is 0x00005002",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_Long, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "(0x00004FFE).W is 0x99BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W -(A1), (0x00006000).L"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 22",
        "A1 is 0x00004FFE",
        "(0x00004FFE).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_Long, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "(0x0000503C).W is 0x99BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W (0x003C, A1), (0x00006000).L"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1008",
        "CYCLES is 24",
        "A1 is 0x00005000",
        "(0x0000503C).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_Long, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).W is 0x99BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W (0x5E, A1, A2.L), (0x00006000).L"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1008",
        "CYCLES is 26",
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_Long, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W (0x5000).W, (0x00006000).L"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1008",
        "CYCLES is 24",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_Long, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W (0x00005000).L, (0x00006000).L"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x100A",
        "CYCLES is 28",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_Long, PCDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x0000103E).W is 0x99BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W (0x003C, PC), (0x00006000).L"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1008",
        "CYCLES is 24",
        "(0x0000103E).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_Long, PCIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A2 is 0x00000010",
        "(0x00001070).W is 0x99BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W (0x5E, PC, A2.L), (0x00006000).L"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1008",
        "CYCLES is 26",
        "A2 is 0x00000010",
        "(0x00001070).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_Long, ImmediateWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W #0x99BA, (0x00006000).L"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1008",
        "CYCLES is 20",
        "(0x00006000).W is 0x99BA",
    });
}

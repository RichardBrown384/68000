#include "M68000/Fixtures/M68000Test.h"

class MOVETestWord_AddressIncrement : public M68000Test {};

TEST_F(MOVETestWord_AddressIncrement, DataDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x347899BA",
        "A4 is 0x00006000",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W D1, (A4)+"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x347899BA",
        "A4 is 0x00006002",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_AddressIncrement, AddressDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x347899BA",
        "A4 is 0x00006000",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W A1, (A4)+"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 8",
        "A1 is 0x347899BA",
        "A4 is 0x00006002",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_AddressIncrement, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A4 is 0x00006000",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W (A1), (A4)+"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 12",
        "A1 is 0x00005000",
        "A4 is 0x00006002",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_AddressIncrement, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A4 is 0x00006000",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W (A1)+, (A4)+"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 12",
        "A1 is 0x00005002",
        "A4 is 0x00006002",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_AddressIncrement, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A4 is 0x00006000",
        "(0x00004FFE).W is 0x99BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W -(A1), (A4)+"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 14",
        "A1 is 0x00004FFE",
        "A4 is 0x00006002",
        "(0x00004FFE).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_AddressIncrement, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A4 is 0x00006000",
        "(0x0000503C).W is 0x99BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W (0x003C, A1), (A4)+"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 16",
        "A1 is 0x00005000",
        "A4 is 0x00006002",
        "(0x0000503C).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_AddressIncrement, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "A4 is 0x00006000",
        "(0x0000506E).W is 0x99BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W (0x5E, A1, A2.L), (A4)+"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 18",
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "A4 is 0x00006002",
        "(0x0000506E).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_AddressIncrement, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W (0x5000).W, (A4)+"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 16",
        "A4 is 0x00006002",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_AddressIncrement, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W (0x00005000).L, (A4)+"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 20",
        "A4 is 0x00006002",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_AddressIncrement, PCDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x0000103E).W is 0x99BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W (0x003C, PC), (A4)+"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 16",
        "A4 is 0x00006002",
        "(0x0000103E).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_AddressIncrement, PCIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A2 is 0x00000010",
        "A4 is 0x00006000",
        "(0x00001070).W is 0x99BA",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W (0x5E, PC, A2.L), (A4)+"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 18",
        "A2 is 0x00000010",
        "A4 is 0x00006002",
        "(0x00001070).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
    });
}

TEST_F(MOVETestWord_AddressIncrement, ImmediateWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).W is 0x0966",
    });
    When({
        "MOVE.W #0x99BA, (A4)+"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 12",
        "A4 is 0x00006002",
        "(0x00006000).W is 0x99BA",
    });
}

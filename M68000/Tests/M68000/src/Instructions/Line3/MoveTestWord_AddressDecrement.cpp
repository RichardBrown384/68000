#include "M68000/Fixtures/M68000Test.h"

class MOVETestWord_AddressDecrement : public M68000Test {};

TEST_F(MOVETestWord_AddressDecrement, DataDirectWorks) {
    Given({
        "D1 is 0x347899BA",
        "A4 is 0x00006000",
        "(0x00005FFE).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W D1, -(A4)"
    });
    Then({
        "D1 is 0x347899BA",
        "A4 is 0x00005FFE",
        "(0x00005FFE).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressDecrement, AddressDirectWorks) {
    Given({
        "A1 is 0x347899BA",
        "A4 is 0x00006000",
        "(0x00005FFE).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W A1, -(A4)"
    });
    Then({
        "A1 is 0x347899BA",
        "A4 is 0x00005FFE",
        "(0x00005FFE).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressDecrement, AddressIndirectWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).W is 0x99BA",
        "A4 is 0x00006000",
        "(0x00005FFE).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (A1), -(A4)"
    });
    Then({
        "A1 is 0x00005000",
        "(0x00005000).W is 0x99BA",
        "A4 is 0x00005FFE",
        "(0x00005FFE).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressDecrement, AddressIncrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).W is 0x99BA",
        "A4 is 0x00006000",
        "(0x00005FFE).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (A1)+, -(A4)"
    });
    Then({
        "A1 is 0x00005002",
        "(0x00005000).W is 0x99BA",
        "A4 is 0x00005FFE",
        "(0x00005FFE).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressDecrement, AddressDecrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00004FFE).W is 0x99BA",
        "A4 is 0x00006000",
        "(0x00005FFE).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W -(A1), -(A4)"
    });
    Then({
        "A1 is 0x00004FFE",
        "(0x00004FFE).W is 0x99BA",
        "A4 is 0x00005FFE",
        "(0x00005FFE).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressDecrement, AddressDisplacementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x0000503C).W is 0x99BA",
        "A4 is 0x00006000",
        "(0x00005FFE).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x003C, A1), -(A4)"
    });
    Then({
        "A1 is 0x00005000",
        "(0x0000503C).W is 0x99BA",
        "A4 is 0x00005FFE",
        "(0x00005FFE).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressDecrement, AddressIndexWorks) {
    Given({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).W is 0x99BA",
        "A4 is 0x00006000",
        "(0x00005FFE).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x5E, A1, A2.L), -(A4)"
    });
    Then({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).W is 0x99BA",
        "A4 is 0x00005FFE",
        "(0x00005FFE).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressDecrement, ShortWorks) {
    Given({
        "(0x00005000).W is 0x99BA",
        "A4 is 0x00006000",
        "(0x00005FFE).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x5000).W, -(A4)"
    });
    Then({
        "(0x00005000).W is 0x99BA",
        "A4 is 0x00005FFE",
        "(0x00005FFE).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressDecrement, LongWorks) {
    Given({
        "(0x00005000).W is 0x99BA",
        "A4 is 0x00006000",
        "(0x00005FFE).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x00005000).L, -(A4)"
    });
    Then({
        "(0x00005000).W is 0x99BA",
        "A4 is 0x00005FFE",
        "(0x00005FFE).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressDecrement, PCDisplacementWorks) {
    Given({
        "(0x0000103E).W is 0x99BA",
        "A4 is 0x00006000",
        "(0x00005FFE).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x003C, PC), -(A4)"
    });
    Then({
        "(0x0000103E).W is 0x99BA",
        "A4 is 0x00005FFE",
        "(0x00005FFE).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressDecrement, PCIndexWorks) {
    Given({
        "A2 is 0x00000010",
        "(0x00001070).W is 0x99BA",
        "A4 is 0x00006000",
        "(0x00005FFE).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x5E, PC, A2.L), -(A4)"
    });
    Then({
        "A2 is 0x00000010",
        "(0x00001070).W is 0x99BA",
        "A4 is 0x00005FFE",
        "(0x00005FFE).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressDecrement, ImmediateWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFE).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W #0x99BA, -(A4)"
    });
    Then({
        "A4 is 0x00005FFE",
        "(0x00005FFE).W is 0x99BA",
        "SR is S,0,N"
    });
}
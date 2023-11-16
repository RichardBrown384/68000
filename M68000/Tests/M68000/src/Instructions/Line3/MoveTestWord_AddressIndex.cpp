#include "M68000/Fixtures/M68000Test.h"

class MOVETestWord_AddressIndex : public M68000Test {};

TEST_F(MOVETestWord_AddressIndex, DataDirectWorks) {
    Given({
        "D1 is 0x347899BA",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W D1, (0x6E, A4, A5.L)"
    });
    Then({
        "D1 is 0x347899BA",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressIndex, AddressDirectWorks) {
    Given({
        "A1 is 0x347899BA",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W A1, (0x6E, A4, A5.L)"
    });
    Then({
        "A1 is 0x347899BA",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressIndex, AddressIndirectWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).W is 0x99BA",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (A1), (0x6E, A4, A5.L)"
    });
    Then({
        "A1 is 0x00005000",
        "(0x00005000).W is 0x99BA",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressIndex, AddressIncrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).W is 0x99BA",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (A1)+, (0x6E, A4, A5.L)"
    });
    Then({
        "A1 is 0x00005002",
        "(0x00005000).W is 0x99BA",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressIndex, AddressDecrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00004FFE).W is 0x99BA",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W -(A1), (0x6E, A4, A5.L)"
    });
    Then({
        "A1 is 0x00004FFE",
        "(0x00004FFE).W is 0x99BA",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressIndex, AddressDisplacementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x0000503C).W is 0x99BA",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x003C, A1), (0x6E, A4, A5.L)"
    });
    Then({
        "A1 is 0x00005000",
        "(0x0000503C).W is 0x99BA",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressIndex, AddressIndexWorks) {
    Given({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).W is 0x99BA",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x5E, A1, A2.L), (0x6E, A4, A5.L)"
    });
    Then({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).W is 0x99BA",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressIndex, ShortWorks) {
    Given({
        "(0x00005000).W is 0x99BA",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x5000).W, (0x6E, A4, A5.L)"
    });
    Then({
        "(0x00005000).W is 0x99BA",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressIndex, LongWorks) {
    Given({
        "(0x00005000).W is 0x99BA",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x00005000).L, (0x6E, A4, A5.L)"
    });
    Then({
        "(0x00005000).W is 0x99BA",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressIndex, PCDisplacementWorks) {
    Given({
        "(0x0000103E).W is 0x99BA",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x003C, PC), (0x6E, A4, A5.L)"
    });
    Then({
        "(0x0000103E).W is 0x99BA",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressIndex, PCIndexWorks) {
    Given({
        "A2 is 0x00000010",
        "(0x00001070).W is 0x99BA",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x5E, PC, A2.L), (0x6E, A4, A5.L)"
    });
    Then({
        "A2 is 0x00000010",
        "(0x00001070).W is 0x99BA",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressIndex, ImmediateWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W #0x99BA, (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).W is 0x99BA",
        "SR is S,0,N"
    });
}

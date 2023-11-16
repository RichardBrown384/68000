#include "M68000/Fixtures/M68000Test.h"

class MOVETestWord_AddressDisplacement : public M68000Test {};

TEST_F(MOVETestWord_AddressDisplacement, DataDirectWorks) {
    Given({
        "D1 is 0x347899BA",
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W D1, (0x004C, A4)"
    });
    Then({
        "D1 is 0x347899BA",
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressDisplacement, AddressDirectWorks) {
    Given({
        "A1 is 0x347899BA",
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W A1, (0x004C, A4)"
    });
    Then({
        "A1 is 0x347899BA",
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressDisplacement, AddressIndirectWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).W is 0x99BA",
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (A1), (0x004C, A4)"
    });
    Then({
        "A1 is 0x00005000",
        "(0x00005000).W is 0x99BA",
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressDisplacement, AddressIncrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).W is 0x99BA",
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (A1)+, (0x004C, A4)"
    });
    Then({
        "A1 is 0x00005002",
        "(0x00005000).W is 0x99BA",
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressDisplacement, AddressDecrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00004FFE).W is 0x99BA",
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W -(A1), (0x004C, A4)"
    });
    Then({
        "A1 is 0x00004FFE",
        "(0x00004FFE).W is 0x99BA",
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressDisplacement, AddressDisplacementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x0000503C).W is 0x99BA",
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x003C, A1), (0x004C, A4)"
    });
    Then({
        "A1 is 0x00005000",
        "(0x0000503C).W is 0x99BA",
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressDisplacement, AddressIndexWorks) {
    Given({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).W is 0x99BA",
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x5E, A1, A2.L), (0x004C, A4)"
    });
    Then({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).W is 0x99BA",
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressDisplacement, ShortWorks) {
    Given({
        "(0x00005000).W is 0x99BA",
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x5000).W, (0x004C, A4)"
    });
    Then({
        "(0x00005000).W is 0x99BA",
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressDisplacement, LongWorks) {
    Given({
        "(0x00005000).W is 0x99BA",
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x00005000).L, (0x004C, A4)"
    });
    Then({
        "(0x00005000).W is 0x99BA",
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressDisplacement, PCDisplacementWorks) {
    Given({
        "(0x0000103E).W is 0x99BA",
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x003C, PC), (0x004C, A4)"
    });
    Then({
        "(0x0000103E).W is 0x99BA",
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressDisplacement, PCIndexWorks) {
    Given({
        "A2 is 0x00000010",
        "(0x00001070).W is 0x99BA",
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x5E, PC, A2.L), (0x004C, A4)"
    });
    Then({
        "A2 is 0x00000010",
        "(0x00001070).W is 0x99BA",
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_AddressDisplacement, ImmediateWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W #0x99BA, (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).W is 0x99BA",
        "SR is S,0,N"
    });
}

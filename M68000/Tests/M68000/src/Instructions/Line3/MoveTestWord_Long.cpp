#include "M68000/Fixtures/M68000Test.h"

class MOVETestWord_Long : public M68000Test {};

TEST_F(MOVETestWord_Long, DataDirectWorks) {
    Given({
        "D1 is 0x347899BA",
        "(0x00006000).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W D1, (0x00006000).L"
    });
    Then({
        "D1 is 0x347899BA",
        "(0x00006000).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_Long, AddressDirectWorks) {
    Given({
        "A1 is 0x347899BA",
        "(0x00006000).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W A1, (0x00006000).L"
    });
    Then({
        "A1 is 0x347899BA",
        "(0x00006000).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_Long, AddressIndirectWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (A1), (0x00006000).L"
    });
    Then({
        "A1 is 0x00005000",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_Long, AddressIncrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (A1)+, (0x00006000).L"
    });
    Then({
        "A1 is 0x00005002",
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_Long, AddressDecrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00004FFE).W is 0x99BA",
        "(0x00006000).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W -(A1), (0x00006000).L"
    });
    Then({
        "A1 is 0x00004FFE",
        "(0x00004FFE).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_Long, AddressDisplacementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x0000503C).W is 0x99BA",
        "(0x00006000).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x003C, A1), (0x00006000).L"
    });
    Then({
        "A1 is 0x00005000",
        "(0x0000503C).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_Long, AddressIndexWorks) {
    Given({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).W is 0x99BA",
        "(0x00006000).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x5E, A1, A2.L), (0x00006000).L"
    });
    Then({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_Long, ShortWorks) {
    Given({
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x5000).W, (0x00006000).L"
    });
    Then({
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_Long, LongWorks) {
    Given({
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x00005000).L, (0x00006000).L"
    });
    Then({
        "(0x00005000).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_Long, PCDisplacementWorks) {
    Given({
        "(0x0000103E).W is 0x99BA",
        "(0x00006000).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x003C, PC), (0x00006000).L"
    });
    Then({
        "(0x0000103E).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_Long, PCIndexWorks) {
    Given({
        "A2 is 0x00000010",
        "(0x00001070).W is 0x99BA",
        "(0x00006000).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W (0x5E, PC, A2.L), (0x00006000).L"
    });
    Then({
        "A2 is 0x00000010",
        "(0x00001070).W is 0x99BA",
        "(0x00006000).W is 0x99BA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestWord_Long, ImmediateWorks) {
    Given({
        "(0x00006000).W is 0x0966",
        "SR is S,0,0"
    });
    When({
        "MOVE.W #0x99BA, (0x00006000).L"
    });
    Then({
        "(0x00006000).W is 0x99BA",
        "SR is S,0,N"
    });
}

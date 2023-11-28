#include "M68000/Fixtures/M68000Test.h"

class MOVETestByte_Short : public M68000Test {};

TEST_F(MOVETestByte_Short, DataDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x347899BA",
        "(0x00006000).B is 0x66",
    });
    When({
        "MOVE.B D1, (0x6000).W"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x347899BA",
        "(0x00006000).B is 0xBA",
    });
}

TEST_F(MOVETestByte_Short, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "(0x00005000).B is 0xBA",
        "(0x00006000).B is 0x66",
    });
    When({
        "MOVE.B (A1), (0x6000).W"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 16",
        "A1 is 0x00005000",
        "(0x00005000).B is 0xBA",
        "(0x00006000).B is 0xBA",
    });
}

TEST_F(MOVETestByte_Short, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "(0x00005000).B is 0xBA",
        "(0x00006000).B is 0x66",
    });
    When({
        "MOVE.B (A1)+, (0x6000).W"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 16",
        "A1 is 0x00005001",
        "(0x00005000).B is 0xBA",
        "(0x00006000).B is 0xBA",
    });
}

TEST_F(MOVETestByte_Short, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "(0x00004FFF).B is 0xBA",
        "(0x00006000).B is 0x66",
    });
    When({
        "MOVE.B -(A1), (0x6000).W"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 18",
        "A1 is 0x00004FFF",
        "(0x00004FFF).B is 0xBA",
        "(0x00006000).B is 0xBA",
    });
}

TEST_F(MOVETestByte_Short, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "(0x0000503C).B is 0xBA",
        "(0x00006000).B is 0x66",
    });
    When({
        "MOVE.B (0x003C, A1), (0x6000).W"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 20",
        "A1 is 0x00005000",
        "(0x0000503C).B is 0xBA",
        "(0x00006000).B is 0xBA",
    });
}

TEST_F(MOVETestByte_Short, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).B is 0xBA",
        "(0x00006000).B is 0x66",
    });
    When({
        "MOVE.B (0x5E, A1, A2.L), (0x6000).W"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 22",
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).B is 0xBA",
        "(0x00006000).B is 0xBA",
    });
}

TEST_F(MOVETestByte_Short, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00005000).B is 0xBA",
        "(0x00006000).B is 0x66",
    });
    When({
        "MOVE.B (0x5000).W, (0x6000).W"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 20",
        "(0x00005000).B is 0xBA",
        "(0x00006000).B is 0xBA",
    });
}

TEST_F(MOVETestByte_Short, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00005000).B is 0xBA",
        "(0x00006000).B is 0x66",
    });
    When({
        "MOVE.B (0x00005000).L, (0x6000).W"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1008",
        "CYCLES is 24",
        "(0x00005000).B is 0xBA",
        "(0x00006000).B is 0xBA",
    });
}

TEST_F(MOVETestByte_Short, PCDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x0000103E).B is 0xBA",
        "(0x00006000).B is 0x66",
    });
    When({
        "MOVE.B (0x003C, PC), (0x6000).W"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 20",
        "(0x0000103E).B is 0xBA",
        "(0x00006000).B is 0xBA",
    });
}

TEST_F(MOVETestByte_Short, PCIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A2 is 0x00000010",
        "(0x00001070).B is 0xBA",
        "(0x00006000).B is 0x66",
    });
    When({
        "MOVE.B (0x5E, PC, A2.L), (0x6000).W"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 22",
        "A2 is 0x00000010",
        "(0x00001070).B is 0xBA",
        "(0x00006000).B is 0xBA",
    });
}

TEST_F(MOVETestByte_Short, ImmediateWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).B is 0x66",
    });
    When({
        "MOVE.B #0xBA, (0x6000).W"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 16",
        "(0x00006000).B is 0xBA",
    });
}

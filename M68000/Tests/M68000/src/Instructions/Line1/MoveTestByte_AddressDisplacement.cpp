#include "M68000/Fixtures/M68000Test.h"

class MOVETestByte_AddressDisplacement : public M68000Test {};

TEST_F(MOVETestByte_AddressDisplacement, DataDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x347899BA",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x66",
    });
    When({
        "MOVE.B D1, (0x004C, A4)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x347899BA",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xBA",
    });
}

TEST_F(MOVETestByte_AddressDisplacement, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A4 is 0x00006000",
        "(0x00005000).B is 0xBA",
        "(0x0000604C).B is 0x66",
    });
    When({
        "MOVE.B (A1), (0x004C, A4)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 16",
        "A1 is 0x00005000",
        "A4 is 0x00006000",
        "(0x00005000).B is 0xBA",
        "(0x0000604C).B is 0xBA",
    });
}

TEST_F(MOVETestByte_AddressDisplacement, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A4 is 0x00006000",
        "(0x00005000).B is 0xBA",
        "(0x0000604C).B is 0x66",
    });
    When({
        "MOVE.B (A1)+, (0x004C, A4)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 16",
        "A1 is 0x00005001",
        "A4 is 0x00006000",
        "(0x00005000).B is 0xBA",
        "(0x0000604C).B is 0xBA",
    });
}

TEST_F(MOVETestByte_AddressDisplacement, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A4 is 0x00006000",
        "(0x00004FFF).B is 0xBA",
        "(0x0000604C).B is 0x66",
    });
    When({
        "MOVE.B -(A1), (0x004C, A4)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 18",
        "A1 is 0x00004FFF",
        "A4 is 0x00006000",
        "(0x00004FFF).B is 0xBA",
        "(0x0000604C).B is 0xBA",
    });
}

TEST_F(MOVETestByte_AddressDisplacement, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A4 is 0x00006000",
        "(0x0000503C).B is 0xBA",
        "(0x0000604C).B is 0x66",
    });
    When({
        "MOVE.B (0x003C, A1), (0x004C, A4)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 20",
        "A1 is 0x00005000",
        "A4 is 0x00006000",
        "(0x0000503C).B is 0xBA",
        "(0x0000604C).B is 0xBA",
    });
}

TEST_F(MOVETestByte_AddressDisplacement, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "A4 is 0x00006000",
        "(0x0000506E).B is 0xBA",
        "(0x0000604C).B is 0x66",
    });
    When({
        "MOVE.B (0x5E, A1, A2.L), (0x004C, A4)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 22",
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "A4 is 0x00006000",
        "(0x0000506E).B is 0xBA",
        "(0x0000604C).B is 0xBA",
    });
}

TEST_F(MOVETestByte_AddressDisplacement, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005000).B is 0xBA",
        "(0x0000604C).B is 0x66",
    });
    When({
        "MOVE.B (0x5000).W, (0x004C, A4)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 20",
        "A4 is 0x00006000",
        "(0x00005000).B is 0xBA",
        "(0x0000604C).B is 0xBA",
    });
}

TEST_F(MOVETestByte_AddressDisplacement, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005000).B is 0xBA",
        "(0x0000604C).B is 0x66",
    });
    When({
        "MOVE.B (0x00005000).L, (0x004C, A4)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1008",
        "CYCLES is 24",
        "A4 is 0x00006000",
        "(0x00005000).B is 0xBA",
        "(0x0000604C).B is 0xBA",
    });
}

TEST_F(MOVETestByte_AddressDisplacement, PCDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x0000103E).B is 0xBA",
        "(0x0000604C).B is 0x66",
    });
    When({
        "MOVE.B (0x003C, PC), (0x004C, A4)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 20",
        "A4 is 0x00006000",
        "(0x0000103E).B is 0xBA",
        "(0x0000604C).B is 0xBA",
    });
}

TEST_F(MOVETestByte_AddressDisplacement, PCIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A2 is 0x00000010",
        "A4 is 0x00006000",
        "(0x00001070).B is 0xBA",
        "(0x0000604C).B is 0x66",
    });
    When({
        "MOVE.B (0x5E, PC, A2.L), (0x004C, A4)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 22",
        "A2 is 0x00000010",
        "A4 is 0x00006000",
        "(0x00001070).B is 0xBA",
        "(0x0000604C).B is 0xBA",
    });
}

TEST_F(MOVETestByte_AddressDisplacement, ImmediateWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x66",
    });
    When({
        "MOVE.B #0xBA, (0x004C, A4)"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 16",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xBA",
    });
}

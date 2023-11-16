#include "M68000/Fixtures/M68000Test.h"

class MOVETestByte_AddressDecrement : public M68000Test {};

TEST_F(MOVETestByte_AddressDecrement, DataDirectWorks) {
    Given({
        "D1 is 0x347899BA",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B D1, -(A4)"
    });
    Then({
        "D1 is 0x347899BA",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xBA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_AddressDecrement, AddressIndirectWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).B is 0xBA",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (A1), -(A4)"
    });
    Then({
        "A1 is 0x00005000",
        "(0x00005000).B is 0xBA",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xBA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_AddressDecrement, AddressIncrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).B is 0xBA",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (A1)+, -(A4)"
    });
    Then({
        "A1 is 0x00005001",
        "(0x00005000).B is 0xBA",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xBA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_AddressDecrement, AddressDecrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00004FFF).B is 0xBA",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B -(A1), -(A4)"
    });
    Then({
        "A1 is 0x00004FFF",
        "(0x00004FFF).B is 0xBA",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xBA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_AddressDecrement, AddressDisplacementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x0000503C).B is 0xBA",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (0x003C, A1), -(A4)"
    });
    Then({
        "A1 is 0x00005000",
        "(0x0000503C).B is 0xBA",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xBA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_AddressDecrement, AddressIndexWorks) {
    Given({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).B is 0xBA",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (0x5E, A1, A2.L), -(A4)"
    });
    Then({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).B is 0xBA",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xBA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_AddressDecrement, ShortWorks) {
    Given({
        "(0x00005000).B is 0xBA",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (0x5000).W, -(A4)"
    });
    Then({
        "(0x00005000).B is 0xBA",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xBA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_AddressDecrement, LongWorks) {
    Given({
        "(0x00005000).B is 0xBA",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (0x00005000).L, -(A4)"
    });
    Then({
        "(0x00005000).B is 0xBA",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xBA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_AddressDecrement, PCDisplacementWorks) {
    Given({
        "(0x0000103E).B is 0xBA",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (0x003C, PC), -(A4)"
    });
    Then({
        "(0x0000103E).B is 0xBA",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xBA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_AddressDecrement, PCIndexWorks) {
    Given({
        "A2 is 0x00000010",
        "(0x00001070).B is 0xBA",
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (0x5E, PC, A2.L), -(A4)"
    });
    Then({
        "A2 is 0x00000010",
        "(0x00001070).B is 0xBA",
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xBA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_AddressDecrement, ImmediateWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFF).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B #0xBA, -(A4)"
    });
    Then({
        "A4 is 0x00005FFF",
        "(0x00005FFF).B is 0xBA",
        "SR is S,0,N"
    });
}

#include "M68000/Fixtures/M68000Test.h"

class MOVETestByte_AddressDisplacement : public M68000Test {};

TEST_F(MOVETestByte_AddressDisplacement, DataDirectWorks) {
    Given({
        "D1 is 0x347899BA",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B D1, (0x004C, A4)"
    });
    Then({
        "D1 is 0x347899BA",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xBA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_AddressDisplacement, AddressIndirectWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).B is 0xBA",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (A1), (0x004C, A4)"
    });
    Then({
        "A1 is 0x00005000",
        "(0x00005000).B is 0xBA",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xBA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_AddressDisplacement, AddressIncrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).B is 0xBA",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (A1)+, (0x004C, A4)"
    });
    Then({
        "A1 is 0x00005001",
        "(0x00005000).B is 0xBA",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xBA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_AddressDisplacement, AddressDecrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00004FFF).B is 0xBA",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B -(A1), (0x004C, A4)"
    });
    Then({
        "A1 is 0x00004FFF",
        "(0x00004FFF).B is 0xBA",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xBA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_AddressDisplacement, AddressDisplacementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x0000503C).B is 0xBA",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (0x003C, A1), (0x004C, A4)"
    });
    Then({
        "A1 is 0x00005000",
        "(0x0000503C).B is 0xBA",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xBA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_AddressDisplacement, AddressIndexWorks) {
    Given({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).B is 0xBA",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (0x5E, A1, A2.L), (0x004C, A4)"
    });
    Then({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).B is 0xBA",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xBA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_AddressDisplacement, ShortWorks) {
    Given({
        "(0x00005000).B is 0xBA",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (0x5000).W, (0x004C, A4)"
    });
    Then({
        "(0x00005000).B is 0xBA",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xBA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_AddressDisplacement, LongWorks) {
    Given({
        "(0x00005000).B is 0xBA",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (0x00005000).L, (0x004C, A4)"
    });
    Then({
        "(0x00005000).B is 0xBA",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xBA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_AddressDisplacement, PCDisplacementWorks) {
    Given({
        "(0x0000103E).B is 0xBA",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (0x003C, PC), (0x004C, A4)"
    });
    Then({
        "(0x0000103E).B is 0xBA",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xBA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_AddressDisplacement, PCIndexWorks) {
    Given({
        "A2 is 0x00000010",
        "(0x00001070).B is 0xBA",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (0x5E, PC, A2.L), (0x004C, A4)"
    });
    Then({
        "A2 is 0x00000010",
        "(0x00001070).B is 0xBA",
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xBA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_AddressDisplacement, ImmediateWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B #0xBA, (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).B is 0xBA",
        "SR is S,0,N"
    });
}

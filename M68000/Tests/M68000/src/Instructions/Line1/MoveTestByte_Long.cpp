#include "M68000/Fixtures/M68000Test.h"

class MOVETestByte_Long : public M68000Test {};

TEST_F(MOVETestByte_Long, DataDirectWorks) {
    Given({
        "D1 is 0x347899BA",
        "(0x00006000).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B D1, (0x00006000).L"
    });
    Then({
        "D1 is 0x347899BA",
        "(0x00006000).B is 0xBA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_Long, AddressIndirectWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).B is 0xBA",
        "(0x00006000).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (A1), (0x00006000).L"
    });
    Then({
        "A1 is 0x00005000",
        "(0x00005000).B is 0xBA",
        "(0x00006000).B is 0xBA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_Long, AddressIncrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00005000).B is 0xBA",
        "(0x00006000).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (A1)+, (0x00006000).L"
    });
    Then({
        "A1 is 0x00005001",
        "(0x00005000).B is 0xBA",
        "(0x00006000).B is 0xBA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_Long, AddressDecrementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x00004FFF).B is 0xBA",
        "(0x00006000).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B -(A1), (0x00006000).L"
    });
    Then({
        "A1 is 0x00004FFF",
        "(0x00004FFF).B is 0xBA",
        "(0x00006000).B is 0xBA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_Long, AddressDisplacementWorks) {
    Given({
        "A1 is 0x00005000",
        "(0x0000503C).B is 0xBA",
        "(0x00006000).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (0x003C, A1), (0x00006000).L"
    });
    Then({
        "A1 is 0x00005000",
        "(0x0000503C).B is 0xBA",
        "(0x00006000).B is 0xBA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_Long, AddressIndexWorks) {
    Given({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).B is 0xBA",
        "(0x00006000).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (0x5E, A1, A2.L), (0x00006000).L"
    });
    Then({
        "A1 is 0x00005000",
        "A2 is 0x00000010",
        "(0x0000506E).B is 0xBA",
        "(0x00006000).B is 0xBA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_Long, ShortWorks) {
    Given({
        "(0x00005000).B is 0xBA",
        "(0x00006000).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (0x5000).W, (0x00006000).L"
    });
    Then({
        "(0x00005000).B is 0xBA",
        "(0x00006000).B is 0xBA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_Long, LongWorks) {
    Given({
        "(0x00005000).B is 0xBA",
        "(0x00006000).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (0x00005000).L, (0x00006000).L"
    });
    Then({
        "(0x00005000).B is 0xBA",
        "(0x00006000).B is 0xBA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_Long, PCDisplacementWorks) {
    Given({
        "(0x0000103E).B is 0xBA",
        "(0x00006000).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (0x003C, PC), (0x00006000).L"
    });
    Then({
        "(0x0000103E).B is 0xBA",
        "(0x00006000).B is 0xBA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_Long, PCIndexWorks) {
    Given({
        "A2 is 0x00000010",
        "(0x00001070).B is 0xBA",
        "(0x00006000).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B (0x5E, PC, A2.L), (0x00006000).L"
    });
    Then({
        "A2 is 0x00000010",
        "(0x00001070).B is 0xBA",
        "(0x00006000).B is 0xBA",
        "SR is S,0,N"
    });
}

TEST_F(MOVETestByte_Long, ImmediateWorks) {
    Given({
        "(0x00006000).B is 0x66",
        "SR is S,0,0"
    });
    When({
        "MOVE.B #0xBA, (0x00006000).L"
    });
    Then({
        "(0x00006000).B is 0xBA",
        "SR is S,0,N"
    });
}
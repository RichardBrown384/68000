#include "M68000/Fixtures/M68000Test.h"

class EXTTest : public M68000Test {};

TEST_F(EXTTest, EXTWordWithExtension) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D2 is 0x00000080",
    });
    When({
        "EXT.W D2"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 4",
        "D2 is 0x0000FF80",
    });
}

TEST_F(EXTTest, EXTWordWithoutExtension) {
    Given({
        "SR is S,0,VC",
        "PC is 0x1000",
        "D2 is 0xFFFFFF70",
    });
    When({
        "EXT.W D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D2 is 0xFFFF0070",
    });
}

TEST_F(EXTTest, EXTWordSetsZeroFlag) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D2 is 0xFFFFFF00",
    });
    When({
        "EXT.W D2"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 4",
        "D2 is 0xFFFF0000",
    });
}

TEST_F(EXTTest, EXTLongWithExtension) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D2 is 0x00008000",
    });
    When({
        "EXT.L D2"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 4",
        "D2 is 0xFFFF8000",
    });
}

TEST_F(EXTTest, EXTLongWithoutExtension) {
    Given({
        "SR is S,0,VC",
        "PC is 0x1000",
        "D2 is 0xFFFF7000",
    });
    When({
        "EXT.L D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D2 is 0x00007000",
    });
}

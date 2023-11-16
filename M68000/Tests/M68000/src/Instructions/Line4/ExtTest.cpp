#include "M68000/Fixtures/M68000Test.h"

class EXTTest : public M68000Test {};

TEST_F(EXTTest, EXTWordWithExtension) {
    Given({
        "D2 is 0x00000080",
        "SR is S,0,0"
    });
    When({
        "EXT.W D2"
    });
    Then({
        "D2 is 0x0000FF80",
        "SR is S,0,N",
        "CYCLES is 4"
    });
}

TEST_F(EXTTest, EXTWordWithoutExtension) {
    Given({
        "D2 is 0xFFFFFF70",
        "SR is S,0,VC"
    });
    When({
        "EXT.W D2"
    });
    Then({
        "D2 is 0xFFFF0070",
        "SR is S,0,0",
        "CYCLES is 4"
    });
}

TEST_F(EXTTest, EXTWordSetsZeroFlag) {
    Given({
        "D2 is 0xFFFFFF00",
        "SR is S,0,0"
    });
    When({
        "EXT.W D2"
    });
    Then({
        "D2 is 0xFFFF0000",
        "SR is S,0,Z",
        "CYCLES is 4"
    });
}

TEST_F(EXTTest, EXTLongWithExtension) {
    Given({
        "D2 is 0x00008000",
        "SR is S,0,0"
    });
    When({
        "EXT.L D2"
    });
    Then({
        "D2 is 0xFFFF8000",
        "SR is S,0,N",
        "CYCLES is 4"
    });
}

TEST_F(EXTTest, EXTLongWithoutExtension) {
    Given({
        "D2 is 0xFFFF7000",
        "SR is S,0,VC"
    });
    When({
        "EXT.L D2"
    });
    Then({
        "D2 is 0x00007000",
        "SR is S,0,0",
        "CYCLES is 4"
    });
}

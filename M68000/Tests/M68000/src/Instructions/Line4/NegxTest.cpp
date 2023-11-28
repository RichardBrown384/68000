#include "M68000/Fixtures/M68000Test.h"

class NEGXTest : public M68000Test {};

TEST_F(NEGXTest, RegisterNEGXWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x22",
    });
    When({
        "NEGX.B D1"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0xDE",
    });
}

TEST_F(NEGXTest, ExtendFlagInfluencesResult) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0x22",
    });
    When({
        "NEGX.B D1"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0xDD",
    });
}

TEST_F(NEGXTest, ZeroFlagClearZeroResult) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00",
    });
    When({
        "NEGX.B D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x00",
    });
}

TEST_F(NEGXTest, ZeroFlagSetZeroResult) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0x00",
    });
    When({
        "NEGX.B D1"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 4",
        "D2 is 0x00",
    });
}

TEST_F(NEGXTest, ZeroFlagSetNonZeroResult) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0x02",
    });
    When({
        "NEGX.B D1"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0xFE",
    });
}

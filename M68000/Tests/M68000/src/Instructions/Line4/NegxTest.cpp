#include "M68000/Fixtures/M68000Test.h"

class NEGXTest : public M68000Test {};

TEST_F(NEGXTest, RegisterNEGXWorks) {
    Given({
        "D1 is 0x22",
        "SR is S,0,0"
    });
    When({
        "NEGX.B D1"
    });
    Then({
        "D1 is 0xDE",
        "SR is S,0,XNC"
    });
}

TEST_F(NEGXTest, ExtendFlagInfluencesResult) {
    Given({
        "D1 is 0x22",
        "SR is S,0,X"
    });
    When({
        "NEGX.B D1"
    });
    Then({
        "D1 is 0xDD",
        "SR is S,0,XNC"
    });
}

TEST_F(NEGXTest, ZeroFlagClearZeroResult) {
    Given({
        "D1 is 0x00",
        "SR is S,0,0"
    });
    When({
        "NEGX.B D1"
    });
    Then({
        "D1 is 0x00",
        "SR is S,0,0"
    });
}

TEST_F(NEGXTest, ZeroFlagSetZeroResult) {
    Given({
        "D1 is 0x00",
        "SR is S,0,Z"
    });
    When({
        "NEGX.B D1"
    });
    Then({
        "D2 is 0x00",
        "SR is S,0,Z"
    });
}

TEST_F(NEGXTest, ZeroFlagSetNonZeroResult) {
    Given({
        "D1 is 0x02",
        "SR is S,0,Z"
    });
    When({
        "NEGX.B D1"
    });
    Then({
        "D1 is 0xFE",
        "SR is S,0,XNC"
    });
}

#include "M68000/Fixtures/M68000Test.h"

class NBCDTest : public M68000Test {};

TEST_F(NBCDTest, RegisterNBCDWorks) {
    Given({
        "D1 is 0x22",
        "SR is S,0,0"
    });
    When({
        "NBCD D1"
    });
    Then({
        "D1 is 0x78",
        "SR is S,0,XVC"
    });
}

TEST_F(NBCDTest, ExtendFlagInfluencesResult) {
    Given({
        "D1 is 0x22",
        "SR is S,0,X"
    });
    When({
        "NBCD D1"
    });
    Then({
        "D1 is 0x77",
        "SR is S,0,XVC"
    });
}

TEST_F(NBCDTest, ZeroFlagClearZeroResult) {
    Given({
        "D1 is 0x00",
        "SR is S,0,0"
    });
    When({
        "NBCD D1"
    });
    Then({
        "D1 is 0x00",
        "SR is S,0,0"
    });
}

TEST_F(NBCDTest, ZeroFlagSetZeroResult) {
    Given({
        "D1 is 0x00",
        "SR is S,0,Z"
    });
    When({
        "NBCD D1"
    });
    Then({
        "D2 is 0x00",
        "SR is S,0,Z"
    });
}

TEST_F(NBCDTest, ZeroFlagSetNonZeroResult) {
    Given({
        "D1 is 0x02",
        "SR is S,0,Z"
    });
    When({
        "NBCD D1"
    });
    Then({
        "D1 is 0x98",
        "SR is S,0,XNC"
    });
}

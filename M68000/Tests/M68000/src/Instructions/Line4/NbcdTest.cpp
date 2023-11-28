#include "M68000/Fixtures/M68000Test.h"

class NBCDTest : public M68000Test {};

TEST_F(NBCDTest, RegisterNBCDWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x22",
    });
    When({
        "NBCD D1"
    });
    Then({
        "SR is S,0,XVC",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x78",
    });
}

TEST_F(NBCDTest, ExtendFlagInfluencesResult) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0x22",
    });
    When({
        "NBCD D1"
    });
    Then({
        "SR is S,0,XVC",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x77",
    });
}

TEST_F(NBCDTest, ZeroFlagClearZeroResult) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00",
    });
    When({
        "NBCD D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x00",
    });
}

TEST_F(NBCDTest, ZeroFlagSetZeroResult) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0x00",
    });
    When({
        "NBCD D1"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 6",
        "D2 is 0x00",
    });
}

TEST_F(NBCDTest, ZeroFlagSetNonZeroResult) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0x02",
    });
    When({
        "NBCD D1"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x98",
    });
}

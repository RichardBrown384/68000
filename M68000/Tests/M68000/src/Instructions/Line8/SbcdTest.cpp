#include "M68000/Fixtures/M68000Test.h"

class SBCDTest : public M68000Test {};

TEST_F(SBCDTest, DataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x17",
        "D2 is 0x36",
    });
    When({
        "SBCD D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x17",
        "D2 is 0x19",
    });
}

TEST_F(SBCDTest, DataRegisterWorksWithSubtrahendGreaterThanMinuend) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11",
        "D2 is 0x02",
    });
    When({
        "SBCD D1, D2"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x11",
        "D2 is 0x91",
    });
}

TEST_F(SBCDTest, DataRegisterFlagNWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x02",
        "D2 is 0x89",
    });
    When({
        "SBCD D1, D2"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x02",
        "D2 is 0x87",
    });
}

TEST_F(SBCDTest, DataRegisterFlagVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x81",
        "D2 is 0x29",
    });
    When({
        "SBCD D1, D2"
    });
    Then({
        "SR is S,0,XVC",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x81",
        "D2 is 0x48",
    });
}

TEST_F(SBCDTest, DataRegisterFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0x17",
        "D2 is 0x38",
    });
    When({
        "SBCD D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x17",
        "D2 is 0x20",
    });
}

TEST_F(SBCDTest, DataRegisterFlagZClearThenZeroResult) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01",
        "D2 is 0x01",
    });
    When({
        "SBCD D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x01",
        "D2 is 0x00",
    });
}

TEST_F(SBCDTest, DataRegisterFlagZSetThenZeroResult) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0x01",
        "D2 is 0x01",
    });
    When({
        "SBCD D1, D2"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x01",
        "D2 is 0x00",
    });
}

TEST_F(SBCDTest, DataRegisterFlagZSetNonZeroResult) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0x01",
        "D2 is 0x02",
    });
    When({
        "SBCD D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x01",
        "D2 is 0x01",
    });
}

TEST_F(SBCDTest, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x2FFF).B is 0x35",
        "(0x3FFF).B is 0x44",
    });
    When({
        "SBCD -(A1), -(A2)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 18",
        "A1 is 0x2FFF",
        "A2 is 0x3FFF",
        "(0x2FFF).B is 0x35",
        "(0x3FFF).B is 0x09",
    });
}

TEST_F(SBCDTest, AddressDecrementSameRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x3000",
        "(0x2FFF).B is 0x35",
        "(0x2FFE).B is 0x44",
    });
    When({
        "SBCD -(A1), -(A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 18",
        "A1 is 0x2FFE",
        "(0x2FFF).B is 0x35",
        "(0x2FFE).B is 0x09",
    });
}

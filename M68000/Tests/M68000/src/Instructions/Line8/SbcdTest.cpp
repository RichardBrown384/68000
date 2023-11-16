#include "M68000/Fixtures/M68000Test.h"

class SBCDTest : public M68000Test {};

TEST_F(SBCDTest, DataRegisterWorks) {
    Given({
        "D1 is 0x17",
        "D2 is 0x36",
        "SR is S,0,0"
    });
    When({
        "SBCD D1, D2"
    });
    Then({
        "D1 is 0x17",
        "D2 is 0x19",
        "SR is S,0,0"
    });
}

TEST_F(SBCDTest, DataRegisterWorksWithSubtrahendGreaterThanMinuend) {
    Given({
        "D1 is 0x11",
        "D2 is 0x02",
        "SR is S,0,0"
    });
    When({
        "SBCD D1, D2"
    });
    Then({
        "D1 is 0x11",
        "D2 is 0x91",
        "SR is S,0,XNC"
    });
}

TEST_F(SBCDTest, DataRegisterFlagNWorks) {
    Given({
        "D1 is 0x02",
        "D2 is 0x89",
        "SR is S,0,0"
    });
    When({
        "SBCD D1, D2"
    });
    Then({
        "D1 is 0x02",
        "D2 is 0x87",
        "SR is S,0,N"
    });
}

TEST_F(SBCDTest, DataRegisterFlagVWorks) {
    Given({
        "D1 is 0x81",
        "D2 is 0x29",
        "SR is S,0,0"
    });
    When({
        "SBCD D1, D2"
    });
    Then({
        "D1 is 0x81",
        "D2 is 0x48",
        "SR is S,0,XVC"
    });
}

TEST_F(SBCDTest, DataRegisterFlagXWorks) {
    Given({
        "D1 is 0x17",
        "D2 is 0x38",
        "SR is S,0,X",
    });
    When({
        "SBCD D1, D2"
    });
    Then({
        "D1 is 0x17",
        "D2 is 0x20",
        "SR is S,0,0"
    });
}

TEST_F(SBCDTest, DataRegisterFlagZClearThenZeroResult) {
    Given({
        "D1 is 0x01",
        "D2 is 0x01",
        "SR is S,0,0"
    });
    When({
        "SBCD D1, D2"
    });
    Then({
        "D1 is 0x01",
        "D2 is 0x00",
        "SR is S,0,0"
    });
}

TEST_F(SBCDTest, DataRegisterFlagZSetThenZeroResult) {
    Given({
        "D1 is 0x01",
        "D2 is 0x01",
        "SR is S,0,Z"
    });
    When({
        "SBCD D1, D2"
    });
    Then({
        "D1 is 0x01",
        "D2 is 0x00",
        "SR is S,0,Z"
    });
}

TEST_F(SBCDTest, DataRegisterFlagZSetNonZeroResult) {
    Given({
        "D1 is 0x01",
        "D2 is 0x02",
        "SR is S,0,Z"
    });
    When({
        "SBCD D1, D2"
    });
    Then({
        "D1 is 0x01",
        "D2 is 0x01",
        "SR is S,0,0"
    });
}

TEST_F(SBCDTest, AddressDecrementWorks) {
    Given({
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x2FFF).B is 0x35",
        "(0x3FFF).B is 0x44",
        "SR is S,0,0"
    });
    When({
        "SBCD -(A1), -(A2)"
    });
    Then({
        "A1 is 0x2FFF",
        "A2 is 0x3FFF",
        "(0x2FFF).B is 0x35",
        "(0x3FFF).B is 0x09",
        "SR is S,0,0"
    });
}

TEST_F(SBCDTest, AddressDecrementSameRegisterWorks) {
    Given({
        "A1 is 0x3000",
        "(0x2FFF).B is 0x35",
        "(0x2FFE).B is 0x44",
        "SR is S,0,0"
    });
    When({
        "SBCD -(A1), -(A1)"
    });
    Then({
        "A1 is 0x2FFE",
        "(0x2FFF).B is 0x35",
        "(0x2FFE).B is 0x09",
        "SR is S,0,0"
    });
}
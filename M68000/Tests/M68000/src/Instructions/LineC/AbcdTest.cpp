#include "M68000/Fixtures/M68000Test.h"

class ABCDTest : public M68000Test {};

TEST_F(ABCDTest, DataRegisterWorks) {
    Given({
        "D1 is 0x22",
        "D2 is 0x19",
        "SR is S,0,0"
    });
    When({
        "ABCD D1, D2"
    });
    Then({
        "D1 is 0x22",
        "D2 is 0x41",
        "SR is S,0,0"
    });
}

TEST_F(ABCDTest, DataRegisterFlagNVWorks) {
    Given({
        "D1 is 0x62",
        "D2 is 0x19",
        "SR is S,0,0"
    });
    When({
        "ABCD D1, D2"
    });
    Then({
        "D1 is 0x62",
        "D2 is 0x81",
        "SR is S,0,NV"
    });
}

TEST_F(ABCDTest, DataRegisterFlagXWorks) {
    Given({
        "D1 is 0x62",
        "D2 is 0x19",
        "SR is S,0,X",
    });
    When({
        "ABCD D1, D2"
    });
    Then({
        "D1 is 0x62",
        "D2 is 0x82",
        "SR is S,0,NV"
    });
}

TEST_F(ABCDTest, DataRegisterFlagZClearThenZeroResult) {
    Given({
        "D1 is 0x99",
        "D2 is 0x01",
        "SR is S,0,0"
    });
    When({
        "ABCD D1, D2"
    });
    Then({
        "D1 is 0x99",
        "D2 is 0x00",
        "SR is S,0,XC"
    });
}

TEST_F(ABCDTest, DataRegisterFlagZSetThenZeroResult) {
    Given({
        "D1 is 0x99",
        "D2 is 0x01",
        "SR is S,0,Z"
    });
    When({
        "ABCD D1, D2"
    });
    Then({
        "D1 is 0x99",
        "D2 is 0x00",
        "SR is S,0,XZC"
    });
}

TEST_F(ABCDTest, DataRegisterFlagZSetNonZeroResult) {
    Given({
        "D1 is 0x98",
        "D2 is 0x01",
        "SR is S,0,Z"
    });
    When({
        "ABCD D1, D2"
    });
    Then({
        "D1 is 0x98",
        "D2 is 0x99",
        "SR is S,0,N"
    });
}

TEST_F(ABCDTest, AddressDecrementWorks) {
    Given({
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x2FFF).B is 0x33",
        "(0x3FFF).B is 0x38",
        "SR is S,0,0"
    });
    When({
        "ABCD -(A1), -(A2)"
    });
    Then({
        "A1 is 0x2FFF",
        "A2 is 0x3FFF",
        "(0x2FFF).B is 0x33",
        "(0x3FFF).B is 0x71",
        "SR is S,0,0"
    });
}

TEST_F(ABCDTest, AddressDecrementSameRegisterWorks) {
    Given({
        "A1 is 0x3000",
        "(0x2FFF).B is 0x33",
        "(0x2FFE).B is 0x38",
        "SR is S,0,0"
    });
    When({
        "ABCD -(A1), -(A1)"
    });
    Then({
        "A1 is 0x2FFE",
        "(0x2FFF).B is 0x33",
        "(0x2FFE).B is 0x71",
        "SR is S,0,0"
    });
}

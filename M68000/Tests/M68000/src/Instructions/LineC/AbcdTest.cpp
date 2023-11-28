#include "M68000/Fixtures/M68000Test.h"

class ABCDTest : public M68000Test {};

TEST_F(ABCDTest, DataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x22",
        "D2 is 0x19",
    });
    When({
        "ABCD D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x22",
        "D2 is 0x41",
    });
}

TEST_F(ABCDTest, DataRegisterFlagNVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x62",
        "D2 is 0x19",
    });
    When({
        "ABCD D1, D2"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x62",
        "D2 is 0x81",
    });
}

TEST_F(ABCDTest, DataRegisterFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0x62",
        "D2 is 0x19",
    });
    When({
        "ABCD D1, D2"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x62",
        "D2 is 0x82",
    });
}

TEST_F(ABCDTest, DataRegisterFlagZClearThenZeroResult) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x99",
        "D2 is 0x01",
    });
    When({
        "ABCD D1, D2"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x99",
        "D2 is 0x00",
    });
}

TEST_F(ABCDTest, DataRegisterFlagZSetThenZeroResult) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0x99",
        "D2 is 0x01",
    });
    When({
        "ABCD D1, D2"
    });
    Then({
        "SR is S,0,XZC",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x99",
        "D2 is 0x00",
    });
}

TEST_F(ABCDTest, DataRegisterFlagZSetNonZeroResult) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0x98",
        "D2 is 0x01",
    });
    When({
        "ABCD D1, D2"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x98",
        "D2 is 0x99",
    });
}

TEST_F(ABCDTest, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x2FFF).B is 0x33",
        "(0x3FFF).B is 0x38",
    });
    When({
        "ABCD -(A1), -(A2)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 18",
        "A1 is 0x2FFF",
        "A2 is 0x3FFF",
        "(0x2FFF).B is 0x33",
        "(0x3FFF).B is 0x71",
    });
}

TEST_F(ABCDTest, AddressDecrementSameRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x3000",
        "(0x2FFF).B is 0x33",
        "(0x2FFE).B is 0x38",
    });
    When({
        "ABCD -(A1), -(A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 18",
        "A1 is 0x2FFE",
        "(0x2FFF).B is 0x33",
        "(0x2FFE).B is 0x71",
    });
}

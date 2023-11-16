#include "M68000/Fixtures/M68000Test.h"

class SUBXTestWord : public M68000Test {};

TEST_F(SUBXTestWord, DataRegisterWorks) {
    Given({
        "D1 is 0x01012201",
        "D2 is 0x01011901",
        "SR is S,0,0"
    });
    When({
        "SUBX.W D1, D2"
    });
    Then({
        "D1 is 0x01012201",
        "D2 is 0x0101F700",
        "SR is S,0,XNC"
    });
}

TEST_F(SUBXTestWord, DataRegisterFlagNVWorks) {
    Given({
        "D1 is 0x01018001",
        "D2 is 0x01013201",
        "SR is S,0,0"
    });
    When({
        "SUBX.W D1, D2"
    });
    Then({
        "D1 is 0x01018001",
        "D2 is 0x0101B200",
        "SR is S,0,XNVC"
    });
}

TEST_F(SUBXTestWord, DataRegisterFlagXWorks) {
    Given({
        "D1 is 0x01011212",
        "D2 is 0x01011919",
        "SR is S,0,X",
    });
    When({
        "SUBX.W D1, D2"
    });
    Then({
        "D1 is 0x01011212",
        "D2 is 0x01010706",
        "SR is S,0,0"
    });
}

TEST_F(SUBXTestWord, DataRegisterFlagZClearThenZeroResult) {
    Given({
        "D1 is 0x01010101",
        "D2 is 0x01010101",
        "SR is S,0,0"
    });
    When({
        "SUBX.W D1, D2"
    });
    Then({
        "D1 is 0x01010101",
        "D2 is 0x01010000",
        "SR is S,0,0"
    });
}

TEST_F(SUBXTestWord, DataRegisterFlagZSetThenZeroResult) {
    Given({
        "D1 is 0x01010101",
        "D2 is 0x01010101",
        "SR is S,0,Z"
    });
    When({
        "SUBX.W D1, D2"
    });
    Then({
        "D1 is 0x01010101",
        "D2 is 0x01010000",
        "SR is S,0,Z"
    });
}

TEST_F(SUBXTestWord, DataRegisterFlagZSetThenNonZeroResult) {
    Given({
        "D1 is 0x01010101",
        "D2 is 0x01010203",
        "SR is S,0,Z"
    });
    When({
        "SUBX.W D1, D2"
    });
    Then({
        "D1 is 0x01010101",
        "D2 is 0x01010102",
        "SR is S,0,0"
    });
}

TEST_F(SUBXTestWord, AddressDecrementWorks) {
    Given({
        "A1 is 0x3002",
        "A2 is 0x4002",
        "(0x3000).W is 0x1144",
        "(0x4000).W is 0x5566",
        "SR is S,0,0"
    });
    When({
        "SUBX.W -(A1), -(A2)"
    });
    Then({
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).W is 0x1144",
        "(0x4000).W is 0x4422",
        "SR is S,0,0"
    });
}

TEST_F(SUBXTestWord, AddressDecrementFlagXWorks) {
    Given({
        "A1 is 0x3002",
        "A2 is 0x4002",
        "(0x3000).W is 0x1144",
        "(0x4000).W is 0x5566",
        "SR is S,0,X"
    });
    When({
        "SUBX.W -(A1), -(A2)"
    });
    Then({
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).W is 0x1144",
        "(0x4000).W is 0x4421",
        "SR is S,0,0"
    });
}

TEST_F(SUBXTestWord, AddressDecrementSameRegisterWorks) {
    Given({
        "A1 is 0x3004",
        "(0x3002).W is 0x1144",
        "(0x3000).W is 0x5566",
        "SR is S,0,0"
    });
    When({
        "SUBX.W -(A1), -(A1)"
    });
    Then({
        "A1 is 0x3000",
        "(0x3002).W is 0x1144",
        "(0x3000).W is 0x4422",
        "SR is S,0,0"
    });
}
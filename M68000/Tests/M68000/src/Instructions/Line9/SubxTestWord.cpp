#include "M68000/Fixtures/M68000Test.h"

class SUBXTestWord : public M68000Test {};

TEST_F(SUBXTestWord, DataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01012201",
        "D2 is 0x01011901",
    });
    When({
        "SUBX.W D1, D2"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01012201",
        "D2 is 0x0101F700",
    });
}

TEST_F(SUBXTestWord, DataRegisterFlagNVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01018001",
        "D2 is 0x01013201",
    });
    When({
        "SUBX.W D1, D2"
    });
    Then({
        "SR is S,0,XNVC",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01018001",
        "D2 is 0x0101B200",
    });
}

TEST_F(SUBXTestWord, DataRegisterFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0x01011212",
        "D2 is 0x01011919",
    });
    When({
        "SUBX.W D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01011212",
        "D2 is 0x01010706",
    });
}

TEST_F(SUBXTestWord, DataRegisterFlagZClearThenZeroResult) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01010101",
        "D2 is 0x01010101",
    });
    When({
        "SUBX.W D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01010101",
        "D2 is 0x01010000",
    });
}

TEST_F(SUBXTestWord, DataRegisterFlagZSetThenZeroResult) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0x01010101",
        "D2 is 0x01010101",
    });
    When({
        "SUBX.W D1, D2"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01010101",
        "D2 is 0x01010000",
    });
}

TEST_F(SUBXTestWord, DataRegisterFlagZSetThenNonZeroResult) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0x01010101",
        "D2 is 0x01010203",
    });
    When({
        "SUBX.W D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01010101",
        "D2 is 0x01010102",
    });
}

TEST_F(SUBXTestWord, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x3002",
        "A2 is 0x4002",
        "(0x3000).W is 0x1144",
        "(0x4000).W is 0x5566",
    });
    When({
        "SUBX.W -(A1), -(A2)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 18",
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).W is 0x1144",
        "(0x4000).W is 0x4422",
    });
}

TEST_F(SUBXTestWord, AddressDecrementFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "A1 is 0x3002",
        "A2 is 0x4002",
        "(0x3000).W is 0x1144",
        "(0x4000).W is 0x5566",
    });
    When({
        "SUBX.W -(A1), -(A2)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 18",
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).W is 0x1144",
        "(0x4000).W is 0x4421",
    });
}

TEST_F(SUBXTestWord, AddressDecrementSameRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x3004",
        "(0x3002).W is 0x1144",
        "(0x3000).W is 0x5566",
    });
    When({
        "SUBX.W -(A1), -(A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 18",
        "A1 is 0x3000",
        "(0x3002).W is 0x1144",
        "(0x3000).W is 0x4422",
    });
}

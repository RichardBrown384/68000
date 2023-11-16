#include "M68000/Fixtures/M68000Test.h"

class ADDXTestWord : public M68000Test {};

TEST_F(ADDXTestWord, DataRegisterWorks) {
    Given({
        "D1 is 0x01012201",
        "D2 is 0x01011901",
        "SR is S,0,0"
    });
    When({
        "ADDX.W D1, D2"
    });
    Then({
        "D1 is 0x01012201",
        "D2 is 0x01013B02",
        "SR is S,0,0"
    });
}

TEST_F(ADDXTestWord, DataRegisterFlagNVWorks) {
    Given({
        "D1 is 0x01016201",
        "D2 is 0x01011F01",
        "SR is S,0,0"
    });
    When({
        "ADDX.W D1, D2"
    });
    Then({
        "D1 is 0x01016201",
        "D2 is 0x01018102",
        "SR is S,0,NV"
    });
}

TEST_F(ADDXTestWord, DataRegisterFlagXWorks) {
    Given({
        "D1 is 0x01016262",
        "D2 is 0x01011919",
        "SR is S,0,X",
    });
    When({
        "ADDX.W D1, D2"
    });
    Then({
        "D1 is 0x01016262",
        "D2 is 0x01017B7C",
        "SR is S,0,0"
    });
}

TEST_F(ADDXTestWord, DataRegisterFlagZClearThenZeroResult) {
    Given({
        "D1 is 0xFFFF",
        "D2 is 0x0001",
        "SR is S,0,0"
    });
    When({
        "ADDX.W D1, D2"
    });
    Then({
        "D1 is 0xFFFF",
        "D2 is 0x0000",
        "SR is S,0,XC"
    });
}

TEST_F(ADDXTestWord, DataRegisterFlagZSetThenZeroResult) {
    Given({
        "D1 is 0xFFFF",
        "D2 is 0x0001",
        "SR is S,0,Z"
    });
    When({
        "ADDX.W D1, D2"
    });
    Then({
        "D1 is 0xFFFF",
        "D2 is 0x0000",
        "SR is S,0,XZC"
    });
}

TEST_F(ADDXTestWord, DataRegisterFlagZSetThenNonZeroResult) {
    Given({
        "D1 is 0xFFFE",
        "D2 is 0x0001",
        "SR is S,0,Z"
    });
    When({
        "ADDX.W D1, D2"
    });
    Then({
        "D1 is 0xFFFE",
        "D2 is 0xFFFF",
        "SR is S,0,N"
    });
}

TEST_F(ADDXTestWord, AddressDecrementWorks) {
    Given({
        "A1 is 0x3002",
        "A2 is 0x4002",
        "(0x3000).W is 0x5533",
        "(0x4000).W is 0x1144",
        "SR is S,0,0"
    });
    When({
        "ADDX.W -(A1), -(A2)"
    });
    Then({
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).W is 0x5533",
        "(0x4000).W is 0x6677",
        "SR is S,0,0"
    });
}

TEST_F(ADDXTestWord, AddressDecrementFlagXWorks) {
    Given({
        "A1 is 0x3002",
        "A2 is 0x4002",
        "(0x3000).W is 0x5533",
        "(0x4000).W is 0x1144",
        "SR is S,0,X"
    });
    When({
        "ADDX.W -(A1), -(A2)"
    });
    Then({
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).W is 0x5533",
        "(0x4000).W is 0x6678",
        "SR is S,0,0"
    });
}

TEST_F(ADDXTestWord, AddressDecrementSameRegisterWorks) {
    Given({
        "A1 is 0x3004",
        "(0x3002).W is 0x5533",
        "(0x3000).W is 0x1144",
        "SR is S,0,0"
    });
    When({
        "ADDX.W -(A1), -(A1)"
    });
    Then({
        "A1 is 0x3000",
        "(0x3002).W is 0x5533",
        "(0x3000).W is 0x6677",
        "SR is S,0,0"
    });
}
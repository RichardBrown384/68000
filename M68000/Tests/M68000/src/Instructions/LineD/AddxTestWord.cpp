#include "M68000/Fixtures/M68000Test.h"

class ADDXTestWord : public M68000Test {};

TEST_F(ADDXTestWord, DataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01012201",
        "D2 is 0x01011901",
    });
    When({
        "ADDX.W D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01012201",
        "D2 is 0x01013B02",
    });
}

TEST_F(ADDXTestWord, DataRegisterFlagNVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01016201",
        "D2 is 0x01011F01",
    });
    When({
        "ADDX.W D1, D2"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01016201",
        "D2 is 0x01018102",
    });
}

TEST_F(ADDXTestWord, DataRegisterFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0x01016262",
        "D2 is 0x01011919",
    });
    When({
        "ADDX.W D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01016262",
        "D2 is 0x01017B7C",
    });
}

TEST_F(ADDXTestWord, DataRegisterFlagZClearThenZeroResult) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xFFFF",
        "D2 is 0x0001",
    });
    When({
        "ADDX.W D1, D2"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0xFFFF",
        "D2 is 0x0000",
    });
}

TEST_F(ADDXTestWord, DataRegisterFlagZSetThenZeroResult) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0xFFFF",
        "D2 is 0x0001",
    });
    When({
        "ADDX.W D1, D2"
    });
    Then({
        "SR is S,0,XZC",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0xFFFF",
        "D2 is 0x0000",
    });
}

TEST_F(ADDXTestWord, DataRegisterFlagZSetThenNonZeroResult) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0xFFFE",
        "D2 is 0x0001",
    });
    When({
        "ADDX.W D1, D2"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0xFFFE",
        "D2 is 0xFFFF",
    });
}

TEST_F(ADDXTestWord, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x3002",
        "A2 is 0x4002",
        "(0x3000).W is 0x5533",
        "(0x4000).W is 0x1144",
    });
    When({
        "ADDX.W -(A1), -(A2)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 18",
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).W is 0x5533",
        "(0x4000).W is 0x6677",
    });
}

TEST_F(ADDXTestWord, AddressDecrementFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "A1 is 0x3002",
        "A2 is 0x4002",
        "(0x3000).W is 0x5533",
        "(0x4000).W is 0x1144",
    });
    When({
        "ADDX.W -(A1), -(A2)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 18",
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).W is 0x5533",
        "(0x4000).W is 0x6678",
    });
}

TEST_F(ADDXTestWord, AddressDecrementSameRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x3004",
        "(0x3002).W is 0x5533",
        "(0x3000).W is 0x1144",
    });
    When({
        "ADDX.W -(A1), -(A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 18",
        "A1 is 0x3000",
        "(0x3002).W is 0x5533",
        "(0x3000).W is 0x6677",
    });
}

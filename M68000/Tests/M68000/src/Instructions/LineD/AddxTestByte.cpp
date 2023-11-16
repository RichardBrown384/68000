#include "M68000/Fixtures/M68000Test.h"

class ADDXTestByte : public M68000Test {};

TEST_F(ADDXTestByte, DataRegisterWorks) {
    Given({
        "D1 is 0x01010122",
        "D2 is 0x01010119",
        "SR is S,0,0"
    });
    When({
        "ADDX.B D1, D2"
    });
    Then({
        "D1 is 0x01010122",
        "D2 is 0x0101013B",
        "SR is S,0,0"
    });
}

TEST_F(ADDXTestByte, DataRegisterFlagNVWorks) {
    Given({
        "D1 is 0x01010162",
        "D2 is 0x0101011F",
        "SR is S,0,0"
    });
    When({
        "ADDX.B D1, D2"
    });
    Then({
        "D1 is 0x01010162",
        "D2 is 0x01010181",
        "SR is S,0,NV"
    });
}

TEST_F(ADDXTestByte, DataRegisterFlagXWorks) {
    Given({
        "D1 is 0x01010162",
        "D2 is 0x01010119",
        "SR is S,0,X",
    });
    When({
        "ADDX.B D1, D2"
    });
    Then({
        "D1 is 0x01010162",
        "D2 is 0x0101017C",
        "SR is S,0,0"
    });
}

TEST_F(ADDXTestByte, DataRegisterFlagZClearThenZeroResult) {
    Given({
        "D1 is 0xFF",
        "D2 is 0x01",
        "SR is S,0,0"
    });
    When({
        "ADDX.B D1, D2"
    });
    Then({
        "D1 is 0xFF",
        "D2 is 0x00",
        "SR is S,0,XC"
    });
}

TEST_F(ADDXTestByte, DataRegisterFlagZSetThenZeroResult) {
    Given({
        "D1 is 0xFF",
        "D2 is 0x01",
        "SR is S,0,Z"
    });
    When({
        "ADDX.B D1, D2"
    });
    Then({
        "D1 is 0xFF",
        "D2 is 0x00",
        "SR is S,0,XZC"
    });
}

TEST_F(ADDXTestByte, DataRegisterFlagZSetThenNonZeroResult) {
    Given({
        "D1 is 0xFE",
        "D2 is 0x01",
        "SR is S,0,Z"
    });
    When({
        "ADDX.B D1, D2"
    });
    Then({
        "D1 is 0xFE",
        "D2 is 0xFF",
        "SR is S,0,N"
    });
}

TEST_F(ADDXTestByte, AddressDecrementWorks) {
    Given({
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x2FFF).B is 0x33",
        "(0x3FFF).B is 0x44",
        "SR is S,0,0"
    });
    When({
        "ADDX.B -(A1), -(A2)"
    });
    Then({
        "A1 is 0x2FFF",
        "A2 is 0x3FFF",
        "(0x2FFF).B is 0x33",
        "(0x3FFF).B is 0x77",
        "SR is S,0,0"
    });
}

TEST_F(ADDXTestByte, AddressDecrementFlagXWorks) {
    Given({
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x2FFF).B is 0x33",
        "(0x3FFF).B is 0x44",
        "SR is S,0,X"
    });
    When({
        "ADDX.B -(A1), -(A2)"
    });
    Then({
        "A1 is 0x2FFF",
        "A2 is 0x3FFF",
        "(0x2FFF).B is 0x33",
        "(0x3FFF).B is 0x78",
        "SR is S,0,0"
    });
}

TEST_F(ADDXTestByte, AddressDecrementSameRegisterWorks) {
    Given({
        "A1 is 0x3000",
        "(0x2FFF).B is 0x33",
        "(0x2FFE).B is 0x44",
        "SR is S,0,0"
    });
    When({
        "ADDX.B -(A1), -(A1)"
    });
    Then({
        "A1 is 0x2FFE",
        "(0x2FFF).B is 0x33",
        "(0x2FFE).B is 0x77",
        "SR is S,0,0"
    });
}

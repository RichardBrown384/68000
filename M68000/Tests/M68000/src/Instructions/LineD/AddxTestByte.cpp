#include "M68000/Fixtures/M68000Test.h"

class ADDXTestByte : public M68000Test {};

TEST_F(ADDXTestByte, DataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01010122",
        "D2 is 0x01010119",
    });
    When({
        "ADDX.B D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01010122",
        "D2 is 0x0101013B",
    });
}

TEST_F(ADDXTestByte, DataRegisterFlagNVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01010162",
        "D2 is 0x0101011F",
    });
    When({
        "ADDX.B D1, D2"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01010162",
        "D2 is 0x01010181",
    });
}

TEST_F(ADDXTestByte, DataRegisterFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0x01010162",
        "D2 is 0x01010119",
    });
    When({
        "ADDX.B D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01010162",
        "D2 is 0x0101017C",
    });
}

TEST_F(ADDXTestByte, DataRegisterFlagZClearThenZeroResult) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xFF",
        "D2 is 0x01",
    });
    When({
        "ADDX.B D1, D2"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0xFF",
        "D2 is 0x00",
    });
}

TEST_F(ADDXTestByte, DataRegisterFlagZSetThenZeroResult) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0xFF",
        "D2 is 0x01",
    });
    When({
        "ADDX.B D1, D2"
    });
    Then({
        "SR is S,0,XZC",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0xFF",
        "D2 is 0x00",
    });
}

TEST_F(ADDXTestByte, DataRegisterFlagZSetThenNonZeroResult) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0xFE",
        "D2 is 0x01",
    });
    When({
        "ADDX.B D1, D2"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0xFE",
        "D2 is 0xFF",
    });
}

TEST_F(ADDXTestByte, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x2FFF).B is 0x33",
        "(0x3FFF).B is 0x44",
    });
    When({
        "ADDX.B -(A1), -(A2)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 18",
        "A1 is 0x2FFF",
        "A2 is 0x3FFF",
        "(0x2FFF).B is 0x33",
        "(0x3FFF).B is 0x77",
    });
}

TEST_F(ADDXTestByte, AddressDecrementFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x2FFF).B is 0x33",
        "(0x3FFF).B is 0x44",
    });
    When({
        "ADDX.B -(A1), -(A2)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 18",
        "A1 is 0x2FFF",
        "A2 is 0x3FFF",
        "(0x2FFF).B is 0x33",
        "(0x3FFF).B is 0x78",
    });
}

TEST_F(ADDXTestByte, AddressDecrementSameRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x3000",
        "(0x2FFF).B is 0x33",
        "(0x2FFE).B is 0x44",
    });
    When({
        "ADDX.B -(A1), -(A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 18",
        "A1 is 0x2FFE",
        "(0x2FFF).B is 0x33",
        "(0x2FFE).B is 0x77",
    });
}

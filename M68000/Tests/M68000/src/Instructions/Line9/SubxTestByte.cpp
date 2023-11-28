#include "M68000/Fixtures/M68000Test.h"

class SUBXTestByte : public M68000Test {};

TEST_F(SUBXTestByte, DataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01010122",
        "D2 is 0x01010119",
    });
    When({
        "SUBX.B D1, D2"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01010122",
        "D2 is 0x010101F7",
    });
}

TEST_F(SUBXTestByte, DataRegisterFlagNVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01010180",
        "D2 is 0x01010132",
    });
    When({
        "SUBX.B D1, D2"
    });
    Then({
        "SR is S,0,XNVC",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01010180",
        "D2 is 0x010101B2",
    });
}

TEST_F(SUBXTestByte, DataRegisterFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0x01010112",
        "D2 is 0x01010119",
    });
    When({
        "SUBX.B D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01010112",
        "D2 is 0x01010106",
    });
}

TEST_F(SUBXTestByte, DataRegisterFlagZClearThenZeroResult) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01010101",
        "D2 is 0x01010101",
    });
    When({
        "SUBX.B D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01010101",
        "D2 is 0x01010100",
    });
}

TEST_F(SUBXTestByte, DataRegisterFlagZSetThenZeroResult) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0x01010101",
        "D2 is 0x01010101",
    });
    When({
        "SUBX.B D1, D2"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01010101",
        "D2 is 0x01010100",
    });
}

TEST_F(SUBXTestByte, DataRegisterFlagZSetThenNonZeroResult) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0x01010101",
        "D2 is 0x01010103",
    });
    When({
        "SUBX.B D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01010101",
        "D2 is 0x01010102",
    });
}

TEST_F(SUBXTestByte, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x2FFF).B is 0x33",
        "(0x3FFF).B is 0x44",
    });
    When({
        "SUBX.B -(A1), -(A2)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 18",
        "A1 is 0x2FFF",
        "A2 is 0x3FFF",
        "(0x2FFF).B is 0x33",
        "(0x3FFF).B is 0x11",
    });
}

TEST_F(SUBXTestByte, AddressDecrementFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x2FFF).B is 0x33",
        "(0x3FFF).B is 0x44",
    });
    When({
        "SUBX.B -(A1), -(A2)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 18",
        "A1 is 0x2FFF",
        "A2 is 0x3FFF",
        "(0x2FFF).B is 0x33",
        "(0x3FFF).B is 0x10",
    });
}

TEST_F(SUBXTestByte, AddressDecrementSameRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x3000",
        "(0x2FFF).B is 0x33",
        "(0x2FFE).B is 0x44",
    });
    When({
        "SUBX.B -(A1), -(A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 18",
        "A1 is 0x2FFE",
        "(0x2FFF).B is 0x33",
        "(0x2FFE).B is 0x11",
    });
}

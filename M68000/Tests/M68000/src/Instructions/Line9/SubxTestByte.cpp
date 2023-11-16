#include "M68000/Fixtures/M68000Test.h"

class SUBXTestByte : public M68000Test {};

TEST_F(SUBXTestByte, DataRegisterWorks) {
    Given({
        "D1 is 0x01010122",
        "D2 is 0x01010119",
        "SR is S,0,0"
    });
    When({
        "SUBX.B D1, D2"
    });
    Then({
        "D1 is 0x01010122",
        "D2 is 0x010101F7",
        "SR is S,0,XNC"
    });
}

TEST_F(SUBXTestByte, DataRegisterFlagNVWorks) {
    Given({
        "D1 is 0x01010180",
        "D2 is 0x01010132",
        "SR is S,0,0"
    });
    When({
        "SUBX.B D1, D2"
    });
    Then({
        "D1 is 0x01010180",
        "D2 is 0x010101B2",
        "SR is S,0,XNVC"
    });
}

TEST_F(SUBXTestByte, DataRegisterFlagXWorks) {
    Given({
        "D1 is 0x01010112",
        "D2 is 0x01010119",
        "SR is S,0,X",
    });
    When({
        "SUBX.B D1, D2"
    });
    Then({
        "D1 is 0x01010112",
        "D2 is 0x01010106",
        "SR is S,0,0"
    });
}

TEST_F(SUBXTestByte, DataRegisterFlagZClearThenZeroResult) {
    Given({
        "D1 is 0x01010101",
        "D2 is 0x01010101",
        "SR is S,0,0"
    });
    When({
        "SUBX.B D1, D2"
    });
    Then({
        "D1 is 0x01010101",
        "D2 is 0x01010100",
        "SR is S,0,0"
    });
}

TEST_F(SUBXTestByte, DataRegisterFlagZSetThenZeroResult) {
    Given({
        "D1 is 0x01010101",
        "D2 is 0x01010101",
        "SR is S,0,Z"
    });
    When({
        "SUBX.B D1, D2"
    });
    Then({
        "D1 is 0x01010101",
        "D2 is 0x01010100",
        "SR is S,0,Z"
    });
}

TEST_F(SUBXTestByte, DataRegisterFlagZSetThenNonZeroResult) {
    Given({
        "D1 is 0x01010101",
        "D2 is 0x01010103",
        "SR is S,0,Z"
    });
    When({
        "SUBX.B D1, D2"
    });
    Then({
        "D1 is 0x01010101",
        "D2 is 0x01010102",
        "SR is S,0,0"
    });
}

TEST_F(SUBXTestByte, AddressDecrementWorks) {
    Given({
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x2FFF).B is 0x33",
        "(0x3FFF).B is 0x44",
        "SR is S,0,0"
    });
    When({
        "SUBX.B -(A1), -(A2)"
    });
    Then({
        "A1 is 0x2FFF",
        "A2 is 0x3FFF",
        "(0x2FFF).B is 0x33",
        "(0x3FFF).B is 0x11",
        "SR is S,0,0"
    });
}

TEST_F(SUBXTestByte, AddressDecrementFlagXWorks) {
    Given({
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x2FFF).B is 0x33",
        "(0x3FFF).B is 0x44",
        "SR is S,0,X"
    });
    When({
        "SUBX.B -(A1), -(A2)"
    });
    Then({
        "A1 is 0x2FFF",
        "A2 is 0x3FFF",
        "(0x2FFF).B is 0x33",
        "(0x3FFF).B is 0x10",
        "SR is S,0,0"
    });
}

TEST_F(SUBXTestByte, AddressDecrementSameRegisterWorks) {
    Given({
        "A1 is 0x3000",
        "(0x2FFF).B is 0x33",
        "(0x2FFE).B is 0x44",
        "SR is S,0,0"
    });
    When({
        "SUBX.B -(A1), -(A1)"
    });
    Then({
        "A1 is 0x2FFE",
        "(0x2FFF).B is 0x33",
        "(0x2FFE).B is 0x11",
        "SR is S,0,0"
    });
}

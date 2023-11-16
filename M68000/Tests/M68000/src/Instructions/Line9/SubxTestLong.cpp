#include "M68000/Fixtures/M68000Test.h"

class SUBXTestLong : public M68000Test {};

TEST_F(SUBXTestLong, DataRegisterWorks) {
    Given({
        "D1 is 0x22010101",
        "D2 is 0x19010101",
        "SR is S,0,0"
    });
    When({
        "SUBX.L D1, D2"
    });
    Then({
        "D1 is 0x22010101",
        "D2 is 0xF7000000",
        "SR is S,0,XNC"
    });
}

TEST_F(SUBXTestLong, DataRegisterFlagNVWorks) {
    Given({
        "D1 is 0x80010101",
        "D2 is 0x32010101",
        "SR is S,0,0"
    });
    When({
        "SUBX.L D1, D2"
    });
    Then({
        "D1 is 0x80010101",
        "D2 is 0xB2000000",
        "SR is S,0,XNVC"
    });
}

TEST_F(SUBXTestLong, DataRegisterFlagXWorks) {
    Given({
        "D1 is 0x12010112",
        "D2 is 0x19010119",
        "SR is S,0,X",
    });
    When({
        "SUBX.L D1, D2"
    });
    Then({
        "D1 is 0x12010112",
        "D2 is 0x07000006",
        "SR is S,0,0"
    });
}

TEST_F(SUBXTestLong, DataRegisterFlagZClearThenZeroResult) {
    Given({
        "D1 is 0x01010101",
        "D2 is 0x01010101",
        "SR is S,0,0"
    });
    When({
        "SUBX.L D1, D2"
    });
    Then({
        "D1 is 0x01010101",
        "D2 is 0x00000000",
        "SR is S,0,0"
    });
}

TEST_F(SUBXTestLong, DataRegisterFlagZSetThenZeroResult) {
    Given({
        "D1 is 0x01010101",
        "D2 is 0x01010101",
        "SR is S,0,Z"
    });
    When({
        "SUBX.L D1, D2"
    });
    Then({
        "D1 is 0x01010101",
        "D2 is 0x00000000",
        "SR is S,0,Z"
    });
}

TEST_F(SUBXTestLong, DataRegisterFlagZSetThenNonZeroResult) {
    Given({
        "D1 is 0x01020201",
        "D2 is 0x02020202",
        "SR is S,0,Z"
    });
    When({
        "SUBX.L D1, D2"
    });
    Then({
        "D1 is 0x01020201",
        "D2 is 0x01000001",
        "SR is S,0,0"
    });
}

TEST_F(SUBXTestLong, AddressDecrementWorks) {
    Given({
        "A1 is 0x3004",
        "A2 is 0x4004",
        "(0x3000).L is 0x44113322",
        "(0x4000).L is 0x66778899",
        "SR is S,0,0"
    });
    When({
        "SUBX.L -(A1), -(A2)"
    });
    Then({
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).L is 0x44113322",
        "(0x4000).L is 0x22665577",
        "SR is S,0,0"
    });
}

TEST_F(SUBXTestLong, AddressDecrementFlagXWorks) {
    Given({
        "A1 is 0x3004",
        "A2 is 0x4004",
        "(0x3000).L is 0x44113322",
        "(0x4000).L is 0x66778899",
        "SR is S,0,X"
    });
    When({
        "SUBX.L -(A1), -(A2)"
    });
    Then({
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).L is 0x44113322",
        "(0x4000).L is 0x22665576",
        "SR is S,0,0"
    });
}

TEST_F(SUBXTestLong, AddressDecrementSameRegisterWorks) {
    Given({
        "A1 is 0x3008",
        "(0x3004).L is 0x44113322",
        "(0x3000).L is 0x66778899",
        "SR is S,0,0"
    });
    When({
        "SUBX.L -(A1), -(A1)"
    });
    Then({
        "A1 is 0x3000",
        "(0x3004).L is 0x44113322",
        "(0x3000).L is 0x22665577",
        "SR is S,0,0"
    });
}
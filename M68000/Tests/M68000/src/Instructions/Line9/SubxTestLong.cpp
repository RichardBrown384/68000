#include "M68000/Fixtures/M68000Test.h"

class SUBXTestLong : public M68000Test {};

TEST_F(SUBXTestLong, DataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x22010101",
        "D2 is 0x19010101",
    });
    When({
        "SUBX.L D1, D2"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x22010101",
        "D2 is 0xF7000000",
    });
}

TEST_F(SUBXTestLong, DataRegisterFlagNVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x80010101",
        "D2 is 0x32010101",
    });
    When({
        "SUBX.L D1, D2"
    });
    Then({
        "SR is S,0,XNVC",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x80010101",
        "D2 is 0xB2000000",
    });
}

TEST_F(SUBXTestLong, DataRegisterFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0x12010112",
        "D2 is 0x19010119",
    });
    When({
        "SUBX.L D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x12010112",
        "D2 is 0x07000006",
    });
}

TEST_F(SUBXTestLong, DataRegisterFlagZClearThenZeroResult) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01010101",
        "D2 is 0x01010101",
    });
    When({
        "SUBX.L D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x01010101",
        "D2 is 0x00000000",
    });
}

TEST_F(SUBXTestLong, DataRegisterFlagZSetThenZeroResult) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0x01010101",
        "D2 is 0x01010101",
    });
    When({
        "SUBX.L D1, D2"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x01010101",
        "D2 is 0x00000000",
    });
}

TEST_F(SUBXTestLong, DataRegisterFlagZSetThenNonZeroResult) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0x01020201",
        "D2 is 0x02020202",
    });
    When({
        "SUBX.L D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x01020201",
        "D2 is 0x01000001",
    });
}

TEST_F(SUBXTestLong, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x3004",
        "A2 is 0x4004",
        "(0x3000).L is 0x44113322",
        "(0x4000).L is 0x66778899",
    });
    When({
        "SUBX.L -(A1), -(A2)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 30",
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).L is 0x44113322",
        "(0x4000).L is 0x22665577",
    });
}

TEST_F(SUBXTestLong, AddressDecrementFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "A1 is 0x3004",
        "A2 is 0x4004",
        "(0x3000).L is 0x44113322",
        "(0x4000).L is 0x66778899",
    });
    When({
        "SUBX.L -(A1), -(A2)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 30",
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).L is 0x44113322",
        "(0x4000).L is 0x22665576",
    });
}

TEST_F(SUBXTestLong, AddressDecrementSameRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x3008",
        "(0x3004).L is 0x44113322",
        "(0x3000).L is 0x66778899",
    });
    When({
        "SUBX.L -(A1), -(A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 30",
        "A1 is 0x3000",
        "(0x3004).L is 0x44113322",
        "(0x3000).L is 0x22665577",
    });
}

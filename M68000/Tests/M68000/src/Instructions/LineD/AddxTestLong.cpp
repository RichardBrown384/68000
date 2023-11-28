#include "M68000/Fixtures/M68000Test.h"

class ADDXTestLong : public M68000Test {};

TEST_F(ADDXTestLong, DataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x22010101",
        "D2 is 0x19010101",
    });
    When({
        "ADDX.L D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x22010101",
        "D2 is 0x3B020202",
    });
}

TEST_F(ADDXTestLong, DataRegisterFlagNVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x62010101",
        "D2 is 0x1F010101",
    });
    When({
        "ADDX.L D1, D2"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x62010101",
        "D2 is 0x81020202",
    });
}

TEST_F(ADDXTestLong, DataRegisterFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0x62010101",
        "D2 is 0x19010101",
    });
    When({
        "ADDX.L D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x62010101",
        "D2 is 0x7B020203",
    });
}

TEST_F(ADDXTestLong, DataRegisterFlagZClearThenZeroResult) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xFFFFFFFF",
        "D2 is 0x00000001",
    });
    When({
        "ADDX.L D1, D2"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0xFFFFFFFF",
        "D2 is 0x00000000",
    });
}

TEST_F(ADDXTestLong, DataRegisterFlagZSetThenZeroResult) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0xFFFFFFFF",
        "D2 is 0x00000001",
    });
    When({
        "ADDX.L D1, D2"
    });
    Then({
        "SR is S,0,XZC",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0xFFFFFFFF",
        "D2 is 0x00000000",
    });
}

TEST_F(ADDXTestLong, DataRegisterFlagZSetThenNonZeroResult) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0xFFFFFFFE",
        "D2 is 0x00000001",
    });
    When({
        "ADDX.L D1, D2"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0xFFFFFFFE",
        "D2 is 0xFFFFFFFF",
    });
}

TEST_F(ADDXTestLong, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x3004",
        "A2 is 0x4004",
        "(0x3000).L is 0x22775533",
        "(0x4000).L is 0x33221144",
    });
    When({
        "ADDX.L -(A1), -(A2)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 30",
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).L is 0x22775533",
        "(0x4000).L is 0x55996677",
    });
}

TEST_F(ADDXTestLong, AddressDecrementFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "A1 is 0x3004",
        "A2 is 0x4004",
        "(0x3000).L is 0x22775533",
        "(0x4000).L is 0x33221144",
    });
    When({
        "ADDX.L -(A1), -(A2)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 30",
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).L is 0x22775533",
        "(0x4000).L is 0x55996678",
    });
}

TEST_F(ADDXTestLong, AddressDecrementSameRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x3008",
        "(0x3004).L is 0x22775533",
        "(0x3000).L is 0x33221144",
    });
    When({
        "ADDX.L -(A1), -(A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 30",
        "A1 is 0x3000",
        "(0x3004).L is 0x22775533",
        "(0x3000).L is 0x55996677",
    });
}

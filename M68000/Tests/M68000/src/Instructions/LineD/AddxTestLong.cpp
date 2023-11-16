#include "M68000/Fixtures/M68000Test.h"

class ADDXTestLong : public M68000Test {};

TEST_F(ADDXTestLong, DataRegisterWorks) {
    Given({
        "D1 is 0x22010101",
        "D2 is 0x19010101",
        "SR is S,0,0"
    });
    When({
        "ADDX.L D1, D2"
    });
    Then({
        "D1 is 0x22010101",
        "D2 is 0x3B020202",
        "SR is S,0,0"
    });
}

TEST_F(ADDXTestLong, DataRegisterFlagNVWorks) {
    Given({
        "D1 is 0x62010101",
        "D2 is 0x1F010101",
        "SR is S,0,0"
    });
    When({
        "ADDX.L D1, D2"
    });
    Then({
        "D1 is 0x62010101",
        "D2 is 0x81020202",
        "SR is S,0,NV"
    });
}

TEST_F(ADDXTestLong, DataRegisterFlagXWorks) {
    Given({
        "D1 is 0x62010101",
        "D2 is 0x19010101",
        "SR is S,0,X",
    });
    When({
        "ADDX.L D1, D2"
    });
    Then({
        "D1 is 0x62010101",
        "D2 is 0x7B020203",
        "SR is S,0,0"
    });
}

TEST_F(ADDXTestLong, DataRegisterFlagZClearThenZeroResult) {
    Given({
        "D1 is 0xFFFFFFFF",
        "D2 is 0x00000001",
        "SR is S,0,0"
    });
    When({
        "ADDX.L D1, D2"
    });
    Then({
        "D1 is 0xFFFFFFFF",
        "D2 is 0x00000000",
        "SR is S,0,XC"
    });
}

TEST_F(ADDXTestLong, DataRegisterFlagZSetThenZeroResult) {
    Given({
        "D1 is 0xFFFFFFFF",
        "D2 is 0x00000001",
        "SR is S,0,Z"
    });
    When({
        "ADDX.L D1, D2"
    });
    Then({
        "D1 is 0xFFFFFFFF",
        "D2 is 0x00000000",
        "SR is S,0,XZC"
    });
}

TEST_F(ADDXTestLong, DataRegisterFlagZSetThenNonZeroResult) {
    Given({
        "D1 is 0xFFFFFFFE",
        "D2 is 0x00000001",
        "SR is S,0,Z"
    });
    When({
        "ADDX.L D1, D2"
    });
    Then({
        "D1 is 0xFFFFFFFE",
        "D2 is 0xFFFFFFFF",
        "SR is S,0,N"
    });
}

TEST_F(ADDXTestLong, AddressDecrementWorks) {
    Given({
        "A1 is 0x3004",
        "A2 is 0x4004",
        "(0x3000).L is 0x22775533",
        "(0x4000).L is 0x33221144",
        "SR is S,0,0"
    });
    When({
        "ADDX.L -(A1), -(A2)"
    });
    Then({
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).L is 0x22775533",
        "(0x4000).L is 0x55996677",
        "SR is S,0,0"
    });
}

TEST_F(ADDXTestLong, AddressDecrementFlagXWorks) {
    Given({
        "A1 is 0x3004",
        "A2 is 0x4004",
        "(0x3000).L is 0x22775533",
        "(0x4000).L is 0x33221144",
        "SR is S,0,X"
    });
    When({
        "ADDX.L -(A1), -(A2)"
    });
    Then({
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).L is 0x22775533",
        "(0x4000).L is 0x55996678",
        "SR is S,0,0"
    });
}

TEST_F(ADDXTestLong, AddressDecrementSameRegisterWorks) {
    Given({
        "A1 is 0x3008",
        "(0x3004).L is 0x22775533",
        "(0x3000).L is 0x33221144",
        "SR is S,0,0"
    });
    When({
        "ADDX.L -(A1), -(A1)"
    });
    Then({
        "A1 is 0x3000",
        "(0x3004).L is 0x22775533",
        "(0x3000).L is 0x55996677",
        "SR is S,0,0"
    });
}
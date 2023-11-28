#include "M68000/Fixtures/M68000Test.h"

class ANDTestByte : public M68000Test {};

TEST_F(ANDTestByte, DataRegisterDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0303030A",
        "D2 is 0xFFFFFFFD",
    });
    When({
        "AND.B D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x0303030A",
        "D2 is 0xFFFFFF08",
    });
}

TEST_F(ANDTestByte, DataRegisterDataRegisterFlagNWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01010180",
        "D2 is 0x11111181",
    });
    When({
        "AND.B D1, D2"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01010180",
        "D2 is 0x11111180",
    });
}

TEST_F(ANDTestByte, DataRegisterDataRegisterFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x03030300",
        "D2 is 0xFFFFFFFF",
    });
    When({
        "AND.B D1, D2"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x03030300",
        "D2 is 0xFFFFFF00",
    });
}

TEST_F(ANDTestByte, DataRegisterDataRegisterFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0x01010101",
        "D2 is 0x11111103",
    });
    When({
        "AND.B D1, D2"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01010101",
        "D2 is 0x11111101",
    });
}

TEST_F(ANDTestByte, DataRegisterDataRegisterFlagVCWorks) {
    Given({
        "SR is S,0,VC",
        "PC is 0x1000",
        "D1 is 0x01010101",
        "D2 is 0x11111103",
    });
    When({
        "AND.B D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01010101",
        "D2 is 0x11111101",
    });
}

TEST_F(ANDTestByte, AddressIndirectDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x1111117A",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4C",
    });
    When({
        "AND.B (A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x11111148",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4C",
    });
}

TEST_F(ANDTestByte, AddressIncrementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x1111117A",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4C",
    });
    When({
        "AND.B (A1)+, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x11111148",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x4C",
    });
}

TEST_F(ANDTestByte, AddressDecrementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x1111117A",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x4C",
    });
    When({
        "AND.B -(A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0x11111148",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4C",
    });
}

TEST_F(ANDTestByte, AddressDisplacementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x1111117A",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x4C",
    });
    When({
        "AND.B (2, A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x11111148",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x4C",
    });
}

TEST_F(ANDTestByte, AddressIndexDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x1111117A",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x4C",
    });
    When({
        "AND.B (2, A1, A2.L), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0x11111148",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x4C",
    });
}

TEST_F(ANDTestByte, ShortDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x1111117A",
        "(0x00004000).B is 0x4C",
    });
    When({
        "AND.B (0x4000).W, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x11111148",
        "(0x00004000).B is 0x4C",
    });
}

TEST_F(ANDTestByte, LongDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x1111117A",
        "(0x00008000).B is 0x4C",
    });
    When({
        "AND.B (0x8000).L, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 16",
        "D1 is 0x11111148",
        "(0x00008000).B is 0x4C",
    });
}

TEST_F(ANDTestByte, PCDisplacementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x1111117A",
        "(0x00001060).B is 0x4C",
    });
    When({
        "AND.B (0x5E, PC), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x11111148",
        "(0x00001060).B is 0x4C",
    });
}

TEST_F(ANDTestByte, PCIndexDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x1111117A",
        "A1 is 0x00000010",
        "(0x00001070).B is 0x4C",
    });
    When({
        "AND.B (0x5E, PC, A1.L), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0x11111148",
        "A1 is 0x00000010",
        "(0x00001070).B is 0x4C",
    });
}

TEST_F(ANDTestByte, ImmediateDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x1111117A",
    });
    When({
        "AND.B #0x4C, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 8",
        "D1 is 0x11111148",
    });
}

TEST_F(ANDTestByte, DataRegisterAddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x7A",
    });
    When({
        "AND.B D1, (A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x48",
    });
}

TEST_F(ANDTestByte, DataRegisterAddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x7A",
    });
    When({
        "AND.B D1, (A1)+"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x0101014C",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x48",
    });
}

TEST_F(ANDTestByte, DataRegisterAddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0101014C",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x7A",
    });
    When({
        "AND.B D1, -(A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x48",
    });
}

TEST_F(ANDTestByte, DataRegisterAddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x7A",
    });
    When({
        "AND.B D1, (2, A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x48",
    });
}

TEST_F(ANDTestByte, DataRegisterAddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x7A",
    });
    When({
        "AND.B D1, (2, A1, A2.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x48",
    });
}

TEST_F(ANDTestByte, DataRegisterShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0101014C",
        "(0x00004000).B is 0x7A",
    });
    When({
        "AND.B D1, (0x4000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "D1 is 0x0101014C",
        "(0x00004000).B is 0x48",
    });
}

TEST_F(ANDTestByte, DataRegisterLongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0101014C",
        "(0x00008000).B is 0x7A",
    });
    When({
        "AND.B D1, (0x8000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 20",
        "D1 is 0x0101014C",
        "(0x00008000).B is 0x48",
    });
}

#include "M68000/Fixtures/M68000Test.h"

class ORTestByte : public M68000Test {};

TEST_F(ORTestByte, DataRegisterDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x03030313",
        "D2 is 0xF0F0F041",
    });
    When({
        "OR.B D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x03030313",
        "D2 is 0xF0F0F053",
    });
}

TEST_F(ORTestByte, DataRegisterDataRegisterFlagNWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x03030381",
        "D2 is 0xF0F0F014",
    });
    When({
        "OR.B D1, D2"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x03030381",
        "D2 is 0xF0F0F095",
    });
}

TEST_F(ORTestByte, DataRegisterDataRegisterFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x03030300",
        "D2 is 0xF0F0F000",
    });
    When({
        "OR.B D1, D2"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x03030300",
        "D2 is 0xF0F0F000",
    });
}

TEST_F(ORTestByte, DataRegisterDataRegisterFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0x03030313",
        "D2 is 0xF0F0F054",
    });
    When({
        "OR.B D1, D2"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x03030313",
        "D2 is 0xF0F0F057",
    });
}

TEST_F(ORTestByte, DataRegisterDataRegisterFlagVCWorks) {
    Given({
        "SR is S,0,VC",
        "PC is 0x1000",
        "D1 is 0x01010113",
        "D2 is 0x10101021",
    });
    When({
        "OR.B D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01010113",
        "D2 is 0x10101033",
    });
}

TEST_F(ORTestByte, AddressIndirectDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x1111117A",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4C",
    });
    When({
        "OR.B (A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x1111117E",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4C",
    });
}

TEST_F(ORTestByte, AddressIncrementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x1111117A",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4C",
    });
    When({
        "OR.B (A1)+, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x1111117E",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x4C",
    });
}

TEST_F(ORTestByte, AddressDecrementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x1111117A",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x4C",
    });
    When({
        "OR.B -(A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0x1111117E",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4C",
    });
}

TEST_F(ORTestByte, AddressDisplacementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x1111117A",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x4C",
    });
    When({
        "OR.B (2, A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x1111117E",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x4C",
    });
}

TEST_F(ORTestByte, AddressIndexDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x1111117A",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x4C",
    });
    When({
        "OR.B (2, A1, A2.L), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0x1111117E",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x4C",
    });
}

TEST_F(ORTestByte, ShortDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x1111117A",
        "(0x00004000).B is 0x4C",
    });
    When({
        "OR.B (0x4000).W, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x1111117E",
        "(0x00004000).B is 0x4C",
    });
}

TEST_F(ORTestByte, LongDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x1111117A",
        "(0x00008000).B is 0x4C",
    });
    When({
        "OR.B (0x8000).L, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 16",
        "D1 is 0x1111117E",
        "(0x00008000).B is 0x4C",
    });
}

TEST_F(ORTestByte, PCDisplacementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x1111117A",
        "(0x00001060).B is 0x4C",
    });
    When({
        "OR.B (0x5E, PC), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x1111117E",
        "(0x00001060).B is 0x4C",
    });
}

TEST_F(ORTestByte, PCIndexDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x1111117A",
        "A1 is 0x00000010",
        "(0x00001070).B is 0x4C",
    });
    When({
        "OR.B (0x5E, PC, A1.L), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0x1111117E",
        "A1 is 0x00000010",
        "(0x00001070).B is 0x4C",
    });
}

TEST_F(ORTestByte, ImmediateDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x1111117A",
    });
    When({
        "OR.B #0x4C, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 8",
        "D1 is 0x1111117E",
    });
}

TEST_F(ORTestByte, DataRegisterAddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x7A",
    });
    When({
        "OR.B D1, (A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x7E",
    });
}

TEST_F(ORTestByte, DataRegisterAddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x7A",
    });
    When({
        "OR.B D1, (A1)+"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x0101014C",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x7E",
    });
}

TEST_F(ORTestByte, DataRegisterAddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0101014C",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x7A",
    });
    When({
        "OR.B D1, -(A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x7E",
    });
}

TEST_F(ORTestByte, DataRegisterAddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x7A",
    });
    When({
        "OR.B D1, (2, A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x7E",
    });
}

TEST_F(ORTestByte, DataRegisterAddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x7A",
    });
    When({
        "OR.B D1, (2, A1, A2.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x7E",
    });
}

TEST_F(ORTestByte, DataRegisterShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0101014C",
        "(0x00004000).B is 0x7A",
    });
    When({
        "OR.B D1, (0x4000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "D1 is 0x0101014C",
        "(0x00004000).B is 0x7E",
    });
}

TEST_F(ORTestByte, DataRegisterLongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0101014C",
        "(0x00008000).B is 0x7A",
    });
    When({
        "OR.B D1, (0x8000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 20",
        "D1 is 0x0101014C",
        "(0x00008000).B is 0x7E",
    });
}

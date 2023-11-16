#include "M68000/Fixtures/M68000Test.h"

class ORTestByte : public M68000Test {};

TEST_F(ORTestByte, DataRegisterDataRegisterWorks) {
    Given({
        "D1 is 0x03030313",
        "D2 is 0xF0F0F041",
        "SR is S,0,0"
    });
    When({
        "OR.B D1, D2"
    });
    Then({
        "D1 is 0x03030313",
        "D2 is 0xF0F0F053",
        "SR is S,0,0"
    });
}

TEST_F(ORTestByte, DataRegisterDataRegisterFlagNWorks) {
    Given({
        "D1 is 0x03030381",
        "D2 is 0xF0F0F014",
        "SR is S,0,0"
    });
    When({
        "OR.B D1, D2"
    });
    Then({
        "D1 is 0x03030381",
        "D2 is 0xF0F0F095",
        "SR is S,0,N"
    });
}

TEST_F(ORTestByte, DataRegisterDataRegisterFlagZWorks) {
    Given({
        "D1 is 0x03030300",
        "D2 is 0xF0F0F000",
        "SR is S,0,0"
    });
    When({
        "OR.B D1, D2"
    });
    Then({
        "D1 is 0x03030300",
        "D2 is 0xF0F0F000",
        "SR is S,0,Z"
    });
}

TEST_F(ORTestByte, DataRegisterDataRegisterFlagXWorks) {
    Given({
        "D1 is 0x03030313",
        "D2 is 0xF0F0F054",
        "SR is S,0,X"
    });
    When({
        "OR.B D1, D2"
    });
    Then({
        "D1 is 0x03030313",
        "D2 is 0xF0F0F057",
        "SR is S,0,X"
    });
}

TEST_F(ORTestByte, DataRegisterDataRegisterFlagVCWorks) {
    Given({
        "D1 is 0x01010113",
        "D2 is 0x10101021",
        "SR is S,0,VC"
    });
    When({
        "OR.B D1, D2"
    });
    Then({
        "D1 is 0x01010113",
        "D2 is 0x10101033",
        "SR is S,0,0"
    });
}

TEST_F(ORTestByte, AddressIndirectDataRegisterWorks) {
    Given({
        "D1 is 0x1111117A",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4C",
        "SR is S,0,0"
    });
    When({
        "OR.B (A1), D1"
    });
    Then({
        "D1 is 0x1111117E",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4C",
        "SR is S,0,0"
    });
}

TEST_F(ORTestByte, AddressIncrementDataRegisterWorks) {
    Given({
        "D1 is 0x1111117A",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4C",
        "SR is S,0,0"
    });
    When({
        "OR.B (A1)+, D1"
    });
    Then({
        "D1 is 0x1111117E",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x4C",
        "SR is S,0,0"
    });
}

TEST_F(ORTestByte, AddressDecrementDataRegisterWorks) {
    Given({
        "D1 is 0x1111117A",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x4C",
        "SR is S,0,0"
    });
    When({
        "OR.B -(A1), D1"
    });
    Then({
        "D1 is 0x1111117E",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4C",
        "SR is S,0,0"
    });
}

TEST_F(ORTestByte, AddressDisplacementDataRegisterWorks) {
    Given({
        "D1 is 0x1111117A",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x4C",
        "SR is S,0,0"
    });
    When({
        "OR.B (2, A1), D1"
    });
    Then({
        "D1 is 0x1111117E",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x4C",
        "SR is S,0,0"
    });
}

TEST_F(ORTestByte, AddressIndexDataRegisterWorks) {
    Given({
        "D1 is 0x1111117A",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x4C",
        "SR is S,0,0"
    });
    When({
        "OR.B (2, A1, A2.L), D1"
    });
    Then({
        "D1 is 0x1111117E",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x4C",
        "SR is S,0,0"
    });
}

TEST_F(ORTestByte, ShortDataRegisterWorks) {
    Given({
        "D1 is 0x1111117A",
        "(0x00004000).B is 0x4C",
        "SR is S,0,0"
    });
    When({
        "OR.B (0x4000).W, D1"
    });
    Then({
        "D1 is 0x1111117E",
        "(0x00004000).B is 0x4C",
        "SR is S,0,0"
    });
}

TEST_F(ORTestByte, LongDataRegisterWorks) {
    Given({
        "D1 is 0x1111117A",
        "(0x00008000).B is 0x4C",
        "SR is S,0,0"
    });
    When({
        "OR.B (0x8000).L, D1"
    });
    Then({
        "D1 is 0x1111117E",
        "(0x00008000).B is 0x4C",
        "SR is S,0,0"
    });
}

TEST_F(ORTestByte, PCDisplacementDataRegisterWorks) {
    Given({
        "D1 is 0x1111117A",
        "(0x00001060).B is 0x4C",
        "SR is S,0,0"
    });
    When({
        "OR.B (0x5E, PC), D1"
    });
    Then({
        "D1 is 0x1111117E",
        "(0x00001060).B is 0x4C",
        "SR is S,0,0"
    });
}

TEST_F(ORTestByte, PCIndexDataRegisterWorks) {
    Given({
        "D1 is 0x1111117A",
        "A1 is 0x00000010",
        "(0x00001070).B is 0x4C",
        "SR is S,0,0"
    });
    When({
        "OR.B (0x5E, PC, A1.L), D1"
    });
    Then({
        "D1 is 0x1111117E",
        "A1 is 0x00000010",
        "(0x00001070).B is 0x4C",
        "SR is S,0,0"
    });
}

TEST_F(ORTestByte, ImmediateDataRegisterWorks) {
    Given({
        "D1 is 0x1111117A",
        "SR is S,0,0"
    });
    When({
        "OR.B #0x4C, D1"
    });
    Then({
        "D1 is 0x1111117E",
        "SR is S,0,0"
    });
}

TEST_F(ORTestByte, DataRegisterAddressIndirectWorks) {
    Given({
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x7A",
        "SR is S,0,0"
    });
    When({
        "OR.B D1, (A1)"
    });
    Then({
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x7E",
        "SR is S,0,0"
    });
}

TEST_F(ORTestByte, DataRegisterAddressIncrementWorks) {
    Given({
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x7A",
        "SR is S,0,0"
    });
    When({
        "OR.B D1, (A1)+"
    });
    Then({
        "D1 is 0x0101014C",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x7E",
        "SR is S,0,0"
    });
}

TEST_F(ORTestByte, DataRegisterAddressDecrementWorks) {
    Given({
        "D1 is 0x0101014C",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x7A",
        "SR is S,0,0"
    });
    When({
        "OR.B D1, -(A1)"
    });
    Then({
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x7E",
        "SR is S,0,0"
    });
}

TEST_F(ORTestByte, DataRegisterAddressIndexWorks) {
    Given({
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x7A",
        "SR is S,0,0"
    });
    When({
        "OR.B D1, (2, A1)"
    });
    Then({
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x7E",
        "SR is S,0,0"
    });
}

TEST_F(ORTestByte, DataRegisterAddressDisplacementWorks) {
    Given({
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x7A",
        "SR is S,0,0"
    });
    When({
        "OR.B D1, (2, A1, A2.L)"
    });
    Then({
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x7E",
        "SR is S,0,0"
    });
}

TEST_F(ORTestByte, DataRegisterShortWorks) {
    Given({
        "D1 is 0x0101014C",
        "(0x00004000).B is 0x7A",
        "SR is S,0,0"
    });
    When({
        "OR.B D1, (0x4000).W"
    });
    Then({
        "D1 is 0x0101014C",
        "(0x00004000).B is 0x7E",
        "SR is S,0,0"
    });
}

TEST_F(ORTestByte, DataRegisterLongWorks) {
    Given({
        "D1 is 0x0101014C",
        "(0x00008000).B is 0x7A",
        "SR is S,0,0"
    });
    When({
        "OR.B D1, (0x8000).L"
    });
    Then({
        "D1 is 0x0101014C",
        "(0x00008000).B is 0x7E",
        "SR is S,0,0"
    });
}
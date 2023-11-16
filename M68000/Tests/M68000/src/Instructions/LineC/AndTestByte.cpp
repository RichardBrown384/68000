#include "M68000/Fixtures/M68000Test.h"

class ANDTestByte : public M68000Test {};

TEST_F(ANDTestByte, DataRegisterDataRegisterWorks) {
    Given({
        "D1 is 0x0303030A",
        "D2 is 0xFFFFFFFD",
        "SR is S,0,0"
    });
    When({
        "AND.B D1, D2"
    });
    Then({
        "D1 is 0x0303030A",
        "D2 is 0xFFFFFF08",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestByte, DataRegisterDataRegisterFlagNWorks) {
    Given({
        "D1 is 0x01010180",
        "D2 is 0x11111181",
        "SR is S,0,0"
    });
    When({
        "AND.B D1, D2"
    });
    Then({
        "D1 is 0x01010180",
        "D2 is 0x11111180",
        "SR is S,0,N"
    });
}

TEST_F(ANDTestByte, DataRegisterDataRegisterFlagZWorks) {
    Given({
        "D1 is 0x03030300",
        "D2 is 0xFFFFFFFF",
        "SR is S,0,0"
    });
    When({
        "AND.B D1, D2"
    });
    Then({
        "D1 is 0x03030300",
        "D2 is 0xFFFFFF00",
        "SR is S,0,Z"
    });
}

TEST_F(ANDTestByte, DataRegisterDataRegisterFlagXWorks) {
    Given({
        "D1 is 0x01010101",
        "D2 is 0x11111103",
        "SR is S,0,X"
    });
    When({
        "AND.B D1, D2"
    });
    Then({
        "D1 is 0x01010101",
        "D2 is 0x11111101",
        "SR is S,0,X"
    });
}

TEST_F(ANDTestByte, DataRegisterDataRegisterFlagVCWorks) {
    Given({
        "D1 is 0x01010101",
        "D2 is 0x11111103",
        "SR is S,0,VC"
    });
    When({
        "AND.B D1, D2"
    });
    Then({
        "D1 is 0x01010101",
        "D2 is 0x11111101",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestByte, AddressIndirectDataRegisterWorks) {
    Given({
        "D1 is 0x1111117A",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4C",
        "SR is S,0,0"
    });
    When({
        "AND.B (A1), D1"
    });
    Then({
        "D1 is 0x11111148",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4C",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestByte, AddressIncrementDataRegisterWorks) {
    Given({
        "D1 is 0x1111117A",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4C",
        "SR is S,0,0"
    });
    When({
        "AND.B (A1)+, D1"
    });
    Then({
        "D1 is 0x11111148",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x4C",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestByte, AddressDecrementDataRegisterWorks) {
    Given({
        "D1 is 0x1111117A",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x4C",
        "SR is S,0,0"
    });
    When({
        "AND.B -(A1), D1"
    });
    Then({
        "D1 is 0x11111148",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4C",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestByte, AddressDisplacementDataRegisterWorks) {
    Given({
        "D1 is 0x1111117A",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x4C",
        "SR is S,0,0"
    });
    When({
        "AND.B (2, A1), D1"
    });
    Then({
        "D1 is 0x11111148",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x4C",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestByte, AddressIndexDataRegisterWorks) {
    Given({
        "D1 is 0x1111117A",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x4C",
        "SR is S,0,0"
    });
    When({
        "AND.B (2, A1, A2.L), D1"
    });
    Then({
        "D1 is 0x11111148",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x4C",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestByte, ShortDataRegisterWorks) {
    Given({
        "D1 is 0x1111117A",
        "(0x00004000).B is 0x4C",
        "SR is S,0,0"
    });
    When({
        "AND.B (0x4000).W, D1"
    });
    Then({
        "D1 is 0x11111148",
        "(0x00004000).B is 0x4C",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestByte, LongDataRegisterWorks) {
    Given({
        "D1 is 0x1111117A",
        "(0x00008000).B is 0x4C",
        "SR is S,0,0"
    });
    When({
        "AND.B (0x8000).L, D1"
    });
    Then({
        "D1 is 0x11111148",
        "(0x00008000).B is 0x4C",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestByte, PCDisplacementDataRegisterWorks) {
    Given({
        "D1 is 0x1111117A",
        "(0x00001060).B is 0x4C",
        "SR is S,0,0"
    });
    When({
        "AND.B (0x5E, PC), D1"
    });
    Then({
        "D1 is 0x11111148",
        "(0x00001060).B is 0x4C",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestByte, PCIndexDataRegisterWorks) {
    Given({
        "D1 is 0x1111117A",
        "A1 is 0x00000010",
        "(0x00001070).B is 0x4C",
        "SR is S,0,0"
    });
    When({
        "AND.B (0x5E, PC, A1.L), D1"
    });
    Then({
        "D1 is 0x11111148",
        "A1 is 0x00000010",
        "(0x00001070).B is 0x4C",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestByte, ImmediateDataRegisterWorks) {
    Given({
        "D1 is 0x1111117A",
        "SR is S,0,0"
    });
    When({
        "AND.B #0x4C, D1"
    });
    Then({
        "D1 is 0x11111148",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestByte, DataRegisterAddressIndirectWorks) {
    Given({
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x7A",
        "SR is S,0,0"
    });
    When({
        "AND.B D1, (A1)"
    });
    Then({
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x48",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestByte, DataRegisterAddressIncrementWorks) {
    Given({
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x7A",
        "SR is S,0,0"
    });
    When({
        "AND.B D1, (A1)+"
    });
    Then({
        "D1 is 0x0101014C",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x48",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestByte, DataRegisterAddressDecrementWorks) {
    Given({
        "D1 is 0x0101014C",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x7A",
        "SR is S,0,0"
    });
    When({
        "AND.B D1, -(A1)"
    });
    Then({
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x48",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestByte, DataRegisterAddressIndexWorks) {
    Given({
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x7A",
        "SR is S,0,0"
    });
    When({
        "AND.B D1, (2, A1)"
    });
    Then({
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x48",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestByte, DataRegisterAddressDisplacementWorks) {
    Given({
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x7A",
        "SR is S,0,0"
    });
    When({
        "AND.B D1, (2, A1, A2.L)"
    });
    Then({
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x48",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestByte, DataRegisterShortWorks) {
    Given({
        "D1 is 0x0101014C",
        "(0x00004000).B is 0x7A",
        "SR is S,0,0"
    });
    When({
        "AND.B D1, (0x4000).W"
    });
    Then({
        "D1 is 0x0101014C",
        "(0x00004000).B is 0x48",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestByte, DataRegisterLongWorks) {
    Given({
        "D1 is 0x0101014C",
        "(0x00008000).B is 0x7A",
        "SR is S,0,0"
    });
    When({
        "AND.B D1, (0x8000).L"
    });
    Then({
        "D1 is 0x0101014C",
        "(0x00008000).B is 0x48",
        "SR is S,0,0"
    });
}
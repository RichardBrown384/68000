#include "M68000/Fixtures/M68000Test.h"

class SUBTestByte : public M68000Test {};

TEST_F(SUBTestByte, DataRegisterDataRegisterWorks) {
    Given({
        "D1 is 0x01010120",
        "D2 is 0x010101E3",
        "SR is S,0,0"
    });
    When({
        "SUB.B D1, D2"
    });
    Then({
        "D1 is 0x01010120",
        "D2 is 0x010101C3",
        "SR is S,0,N"
    });
}

TEST_F(SUBTestByte, DataRegisterDataRegisterFlagNVWorks) {
    Given({
        "D1 is 0x01010180",
        "D2 is 0x01010132",
        "SR is S,0,0"
    });
    When({
        "SUB.B D1, D2"
    });
    Then({
        "D1 is 0x01010180",
        "D2 is 0x010101B2",
        "SR is S,0,XNVC"
    });
}

TEST_F(SUBTestByte, DataRegisterDataRegisterFlagXWorks) {
    Given({
        "D1 is 0x01010101",
        "D2 is 0x01010103",
        "SR is S,0,X"
    });
    When({
        "SUB.B D1, D2"
    });
    Then({
        "D1 is 0x01010101",
        "D2 is 0x01010102",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestByte, AddressIndirectDataRegisterWorks) {
    Given({
        "D1 is 0x00000004",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x1",
        "SR is S,0,0"
    });
    When({
        "SUB.B (A1), D1"
    });
    Then({
        "D1 is 0x00000003",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x1",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestByte, AddressIncrementDataRegisterWorks) {
    Given({
        "D1 is 0x00000004",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x1",
        "SR is S,0,0"
    });
    When({
        "SUB.B (A1)+, D1"
    });
    Then({
        "D1 is 0x00000003",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x1",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestByte, AddressDecrementDataRegisterWorks) {
    Given({
        "D1 is 0x00000004",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x1",
        "SR is S,0,0"
    });
    When({
        "SUB.B -(A1), D1"
    });
    Then({
        "D1 is 0x00000003",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x1",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestByte, AddressDisplacementDataRegisterWorks) {
    Given({
        "D1 is 0x00000004",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x1",
        "SR is S,0,0"
    });
    When({
        "SUB.B (2, A1), D1"
    });
    Then({
        "D1 is 0x00000003",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x1",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestByte, AddressIndexDataRegisterWorks) {
    Given({
        "D1 is 0x00000004",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x1",
        "SR is S,0,0"
    });
    When({
        "SUB.B (2, A1, A2.L), D1"
    });
    Then({
        "D1 is 0x00000003",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x1",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestByte, ShortDataRegisterWorks) {
    Given({
        "D1 is 0x00000004",
        "(0x00004000).B is 0x1",
        "SR is S,0,0"
    });
    When({
        "SUB.B (0x4000).W, D1"
    });
    Then({
        "D1 is 0x00000003",
        "(0x00004000).B is 0x1",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestByte, LongDataRegisterWorks) {
    Given({
        "D1 is 0x00000004",
        "(0x00008000).B is 0x1",
        "SR is S,0,0"
    });
    When({
        "SUB.B (0x8000).L, D1"
    });
    Then({
        "D1 is 0x00000003",
        "(0x00008000).B is 0x1",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestByte, PCDisplacementDataRegisterWorks) {
    Given({
        "D1 is 0x00000004",
        "(0x00001060).B is 0x1",
        "SR is S,0,0"
    });
    When({
        "SUB.B (0x5E, PC), D1"
    });
    Then({
        "D1 is 0x00000003",
        "(0x00001060).B is 0x1",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestByte, PCIndexDataRegisterWorks) {
    Given({
        "D1 is 0x00000004",
        "A1 is 0x00000010",
        "(0x00001070).B is 0x1",
        "SR is S,0,0"
    });
    When({
        "SUB.B (0x5E, PC, A1.L), D1"
    });
    Then({
        "D1 is 0x00000003",
        "A1 is 0x00000010",
        "(0x00001070).B is 0x1",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestByte, ImmediateDataRegisterWorks) {
    Given({
        "D1 is 0x00000004",
        "SR is S,0,0"
    });
    When({
        "SUB.B #0x1, D1"
    });
    Then({
        "D1 is 0x00000003",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestByte, DataRegisterAddressIndirectWorks) {
    Given({
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4",
        "SR is S,0,0"
    });
    When({
        "SUB.B D1, (A1)"
    });
    Then({
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x3",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestByte, DataRegisterAddressIncrementWorks) {
    Given({
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4",
        "SR is S,0,0"
    });
    When({
        "SUB.B D1, (A1)+"
    });
    Then({
        "D1 is 0x00000001",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x3",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestByte, DataRegisterAddressDecrementWorks) {
    Given({
        "D1 is 0x00000001",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x4",
        "SR is S,0,0"
    });
    When({
        "SUB.B D1, -(A1)"
    });
    Then({
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x3",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestByte, DataRegisterAddressIndexWorks) {
    Given({
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x4",
        "SR is S,0,0"
    });
    When({
        "SUB.B D1, (2, A1)"
    });
    Then({
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x3",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestByte, DataRegisterAddressDisplacementWorks) {
    Given({
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x4",
        "SR is S,0,0"
    });
    When({
        "SUB.B D1, (2, A1, A2.L)"
    });
    Then({
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x3",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestByte, DataRegisterShortWorks) {
    Given({
        "D1 is 0x00000001",
        "(0x00004000).B is 0x4",
        "SR is S,0,0"
    });
    When({
        "SUB.B D1, (0x4000).W"
    });
    Then({
        "D1 is 0x00000001",
        "(0x00004000).B is 0x3",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestByte, DataRegisterLongWorks) {
    Given({
        "D1 is 0x00000001",
        "(0x00008000).B is 0x4",
        "SR is S,0,0"
    });
    When({
        "SUB.B D1, (0x8000).L"
    });
    Then({
        "D1 is 0x00000001",
        "(0x00008000).B is 0x3",
        "SR is S,0,0"
    });
}
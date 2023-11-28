#include "M68000/Fixtures/M68000Test.h"

class SUBTestByte : public M68000Test {};

TEST_F(SUBTestByte, DataRegisterDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01010120",
        "D2 is 0x010101E3",
    });
    When({
        "SUB.B D1, D2"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01010120",
        "D2 is 0x010101C3",
    });
}

TEST_F(SUBTestByte, DataRegisterDataRegisterFlagNVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01010180",
        "D2 is 0x01010132",
    });
    When({
        "SUB.B D1, D2"
    });
    Then({
        "SR is S,0,XNVC",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01010180",
        "D2 is 0x010101B2",
    });
}

TEST_F(SUBTestByte, DataRegisterDataRegisterFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0x01010101",
        "D2 is 0x01010103",
    });
    When({
        "SUB.B D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01010101",
        "D2 is 0x01010102",
    });
}

TEST_F(SUBTestByte, AddressIndirectDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000004",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x1",
    });
    When({
        "SUB.B (A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x00000003",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x1",
    });
}

TEST_F(SUBTestByte, AddressIncrementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000004",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x1",
    });
    When({
        "SUB.B (A1)+, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x00000003",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x1",
    });
}

TEST_F(SUBTestByte, AddressDecrementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000004",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x1",
    });
    When({
        "SUB.B -(A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0x00000003",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x1",
    });
}

TEST_F(SUBTestByte, AddressDisplacementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000004",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x1",
    });
    When({
        "SUB.B (2, A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x00000003",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x1",
    });
}

TEST_F(SUBTestByte, AddressIndexDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000004",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x1",
    });
    When({
        "SUB.B (2, A1, A2.L), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0x00000003",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x1",
    });
}

TEST_F(SUBTestByte, ShortDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000004",
        "(0x00004000).B is 0x1",
    });
    When({
        "SUB.B (0x4000).W, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x00000003",
        "(0x00004000).B is 0x1",
    });
}

TEST_F(SUBTestByte, LongDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000004",
        "(0x00008000).B is 0x1",
    });
    When({
        "SUB.B (0x8000).L, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 16",
        "D1 is 0x00000003",
        "(0x00008000).B is 0x1",
    });
}

TEST_F(SUBTestByte, PCDisplacementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000004",
        "(0x00001060).B is 0x1",
    });
    When({
        "SUB.B (0x5E, PC), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x00000003",
        "(0x00001060).B is 0x1",
    });
}

TEST_F(SUBTestByte, PCIndexDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000004",
        "A1 is 0x00000010",
        "(0x00001070).B is 0x1",
    });
    When({
        "SUB.B (0x5E, PC, A1.L), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0x00000003",
        "A1 is 0x00000010",
        "(0x00001070).B is 0x1",
    });
}

TEST_F(SUBTestByte, ImmediateDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000004",
    });
    When({
        "SUB.B #0x1, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 8",
        "D1 is 0x00000003",
    });
}

TEST_F(SUBTestByte, DataRegisterAddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4",
    });
    When({
        "SUB.B D1, (A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x3",
    });
}

TEST_F(SUBTestByte, DataRegisterAddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4",
    });
    When({
        "SUB.B D1, (A1)+"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x00000001",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x3",
    });
}

TEST_F(SUBTestByte, DataRegisterAddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000001",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x4",
    });
    When({
        "SUB.B D1, -(A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x3",
    });
}

TEST_F(SUBTestByte, DataRegisterAddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x4",
    });
    When({
        "SUB.B D1, (2, A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x3",
    });
}

TEST_F(SUBTestByte, DataRegisterAddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x4",
    });
    When({
        "SUB.B D1, (2, A1, A2.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x3",
    });
}

TEST_F(SUBTestByte, DataRegisterShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000001",
        "(0x00004000).B is 0x4",
    });
    When({
        "SUB.B D1, (0x4000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "D1 is 0x00000001",
        "(0x00004000).B is 0x3",
    });
}

TEST_F(SUBTestByte, DataRegisterLongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000001",
        "(0x00008000).B is 0x4",
    });
    When({
        "SUB.B D1, (0x8000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 20",
        "D1 is 0x00000001",
        "(0x00008000).B is 0x3",
    });
}

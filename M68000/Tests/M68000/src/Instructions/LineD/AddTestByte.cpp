#include "M68000/Fixtures/M68000Test.h"

class ADDTestByte : public M68000Test {};

TEST_F(ADDTestByte, DataRegisterDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01010120",
        "D2 is 0x010101E3",
    });
    When({
        "ADD.B D1, D2"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01010120",
        "D2 is 0x01010103",
    });
}

TEST_F(ADDTestByte, DataRegisterDataRegisterFlagNVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01010110",
        "D2 is 0x01010170",
    });
    When({
        "ADD.B D1, D2"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01010110",
        "D2 is 0x01010180",
    });
}

TEST_F(ADDTestByte, DataRegisterDataRegisterFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0x01010101",
        "D2 is 0x01010101",
    });
    When({
        "ADD.B D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01010101",
        "D2 is 0x01010102",
    });
}

TEST_F(ADDTestByte, AddressIndirectDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4",
    });
    When({
        "ADD.B (A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x00000005",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4",
    });
}

TEST_F(ADDTestByte, AddressIncrementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4",
    });
    When({
        "ADD.B (A1)+, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x00000005",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x4",
    });
}

TEST_F(ADDTestByte, AddressDecrementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000001",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x4",
    });
    When({
        "ADD.B -(A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0x00000005",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4",
    });
}

TEST_F(ADDTestByte, AddressDisplacementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x4",
    });
    When({
        "ADD.B (2, A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x00000005",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x4",
    });
}

TEST_F(ADDTestByte, AddressIndexDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x4",
    });
    When({
        "ADD.B (2, A1, A2.L), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0x00000005",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x4",
    });
}

TEST_F(ADDTestByte, ShortDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000001",
        "(0x00004000).B is 0x4",
    });
    When({
        "ADD.B (0x4000).W, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x00000005",
        "(0x00004000).B is 0x4",
    });
}

TEST_F(ADDTestByte, LongDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000001",
        "(0x00008000).B is 0x4",
    });
    When({
        "ADD.B (0x8000).L, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 16",
        "D1 is 0x00000005",
        "(0x00008000).B is 0x4",
    });
}

TEST_F(ADDTestByte, PCDisplacementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000001",
        "(0x00001060).B is 0x4",
    });
    When({
        "ADD.B (0x5E, PC), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x00000005",
        "(0x00001060).B is 0x4",
    });
}

TEST_F(ADDTestByte, PCIndexDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000001",
        "A1 is 0x00000010",
        "(0x00001070).B is 0x4",
    });
    When({
        "ADD.B (0x5E, PC, A1.L), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0x00000005",
        "A1 is 0x00000010",
        "(0x00001070).B is 0x4",
    });
}

TEST_F(ADDTestByte, ImmediateDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000001",
    });
    When({
        "ADD.B #0x4, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 8",
        "D1 is 0x00000005",
    });
}

TEST_F(ADDTestByte, DataRegisterAddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4",
    });
    When({
        "ADD.B D1, (A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x5",
    });
}

TEST_F(ADDTestByte, DataRegisterAddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4",
    });
    When({
        "ADD.B D1, (A1)+"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x00000001",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x5",
    });
}

TEST_F(ADDTestByte, DataRegisterAddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000001",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x4",
    });
    When({
        "ADD.B D1, -(A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x5",
    });
}

TEST_F(ADDTestByte, DataRegisterAddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x4",
    });
    When({
        "ADD.B D1, (2, A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x5",
    });
}

TEST_F(ADDTestByte, DataRegisterAddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x4",
    });
    When({
        "ADD.B D1, (2, A1, A2.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x5",
    });
}

TEST_F(ADDTestByte, DataRegisterShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000001",
        "(0x00004000).B is 0x4",
    });
    When({
        "ADD.B D1, (0x4000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "D1 is 0x00000001",
        "(0x00004000).B is 0x5",
    });
}

TEST_F(ADDTestByte, DataRegisterLongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000001",
        "(0x00008000).B is 0x4",
    });
    When({
        "ADD.B D1, (0x8000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 20",
        "D1 is 0x00000001",
        "(0x00008000).B is 0x5",
    });
}

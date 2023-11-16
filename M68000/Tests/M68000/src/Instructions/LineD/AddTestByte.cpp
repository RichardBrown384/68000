#include "M68000/Fixtures/M68000Test.h"

class ADDTestByte : public M68000Test {};

TEST_F(ADDTestByte, DataRegisterDataRegisterWorks) {
    Given({
        "D1 is 0x01010120",
        "D2 is 0x010101E3",
        "SR is S,0,0"
    });
    When({
        "ADD.B D1, D2"
    });
    Then({
        "D1 is 0x01010120",
        "D2 is 0x01010103",
        "SR is S,0,XC",
        "CYCLES is 4"
    });
}

TEST_F(ADDTestByte, DataRegisterDataRegisterFlagNVWorks) {
    Given({
        "D1 is 0x01010110",
        "D2 is 0x01010170",
        "SR is S,0,0"
    });
    When({
        "ADD.B D1, D2"
    });
    Then({
        "D1 is 0x01010110",
        "D2 is 0x01010180",
        "SR is S,0,NV",
        "CYCLES is 4"
    });
}

TEST_F(ADDTestByte, DataRegisterDataRegisterFlagXWorks) {
    Given({
        "D1 is 0x01010101",
        "D2 is 0x01010101",
        "SR is S,0,X"
    });
    When({
        "ADD.B D1, D2"
    });
    Then({
        "D1 is 0x01010101",
        "D2 is 0x01010102",
        "SR is S,0,0",
        "CYCLES is 4"
    });
}

TEST_F(ADDTestByte, AddressIndirectDataRegisterWorks) {
    Given({
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4",
        "SR is S,0,0"
    });
    When({
        "ADD.B (A1), D1"
    });
    Then({
        "D1 is 0x00000005",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4",
        "SR is S,0,0",
        "CYCLES is 8"
    });
}

TEST_F(ADDTestByte, AddressIncrementDataRegisterWorks) {
    Given({
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4",
        "SR is S,0,0"
    });
    When({
        "ADD.B (A1)+, D1"
    });
    Then({
        "D1 is 0x00000005",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x4",
        "SR is S,0,0",
        "CYCLES is 8"
    });
}

TEST_F(ADDTestByte, AddressDecrementDataRegisterWorks) {
    Given({
        "D1 is 0x00000001",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x4",
        "SR is S,0,0"
    });
    When({
        "ADD.B -(A1), D1"
    });
    Then({
        "D1 is 0x00000005",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4",
        "SR is S,0,0",
        "CYCLES is 10"
    });
}

TEST_F(ADDTestByte, AddressDisplacementDataRegisterWorks) {
    Given({
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x4",
        "SR is S,0,0"
    });
    When({
        "ADD.B (2, A1), D1"
    });
    Then({
        "D1 is 0x00000005",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x4",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(ADDTestByte, AddressIndexDataRegisterWorks) {
    Given({
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x4",
        "SR is S,0,0"
    });
    When({
        "ADD.B (2, A1, A2.L), D1"
    });
    Then({
        "D1 is 0x00000005",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x4",
        "SR is S,0,0",
        "CYCLES is 14"
    });
}

TEST_F(ADDTestByte, ShortDataRegisterWorks) {
    Given({
        "D1 is 0x00000001",
        "(0x00004000).B is 0x4",
        "SR is S,0,0"
    });
    When({
        "ADD.B (0x4000).W, D1"
    });
    Then({
        "D1 is 0x00000005",
        "(0x00004000).B is 0x4",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(ADDTestByte, LongDataRegisterWorks) {
    Given({
        "D1 is 0x00000001",
        "(0x00008000).B is 0x4",
        "SR is S,0,0"
    });
    When({
        "ADD.B (0x8000).L, D1"
    });
    Then({
        "D1 is 0x00000005",
        "(0x00008000).B is 0x4",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(ADDTestByte, PCDisplacementDataRegisterWorks) {
    Given({
        "D1 is 0x00000001",
        "(0x00001060).B is 0x4",
        "SR is S,0,0"
    });
    When({
        "ADD.B (0x5E, PC), D1"
    });
    Then({
        "D1 is 0x00000005",
        "(0x00001060).B is 0x4",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(ADDTestByte, PCIndexDataRegisterWorks) {
    Given({
        "D1 is 0x00000001",
        "A1 is 0x00000010",
        "(0x00001070).B is 0x4",
        "SR is S,0,0"
    });
    When({
        "ADD.B (0x5E, PC, A1.L), D1"
    });
    Then({
        "D1 is 0x00000005",
        "A1 is 0x00000010",
        "(0x00001070).B is 0x4",
        "SR is S,0,0",
        "CYCLES is 14"
    });
}

TEST_F(ADDTestByte, ImmediateDataRegisterWorks) {
    Given({
        "D1 is 0x00000001",
        "SR is S,0,0"
    });
    When({
        "ADD.B #0x4, D1"
    });
    Then({
        "D1 is 0x00000005",
        "SR is S,0,0",
        "CYCLES is 8"
    });
}

TEST_F(ADDTestByte, DataRegisterAddressIndirectWorks) {
    Given({
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4",
        "SR is S,0,0"
    });
    When({
        "ADD.B D1, (A1)"
    });
    Then({
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x5",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(ADDTestByte, DataRegisterAddressIncrementWorks) {
    Given({
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x4",
        "SR is S,0,0"
    });
    When({
        "ADD.B D1, (A1)+"
    });
    Then({
        "D1 is 0x00000001",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x5",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(ADDTestByte, DataRegisterAddressDecrementWorks) {
    Given({
        "D1 is 0x00000001",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x4",
        "SR is S,0,0"
    });
    When({
        "ADD.B D1, -(A1)"
    });
    Then({
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x5",
        "SR is S,0,0",
        "CYCLES is 14"
    });
}

TEST_F(ADDTestByte, DataRegisterAddressIndexWorks) {
    Given({
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x4",
        "SR is S,0,0"
    });
    When({
        "ADD.B D1, (2, A1)"
    });
    Then({
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x5",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(ADDTestByte, DataRegisterAddressDisplacementWorks) {
    Given({
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x4",
        "SR is S,0,0"
    });
    When({
        "ADD.B D1, (2, A1, A2.L)"
    });
    Then({
        "D1 is 0x00000001",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x5",
        "SR is S,0,0",
        "CYCLES is 18"
    });
}

TEST_F(ADDTestByte, DataRegisterShortWorks) {
    Given({
        "D1 is 0x00000001",
        "(0x00004000).B is 0x4",
        "SR is S,0,0"
    });
    When({
        "ADD.B D1, (0x4000).W"
    });
    Then({
        "D1 is 0x00000001",
        "(0x00004000).B is 0x5",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(ADDTestByte, DataRegisterLongWorks) {
    Given({
        "D1 is 0x00000001",
        "(0x00008000).B is 0x4",
        "SR is S,0,0"
    });
    When({
        "ADD.B D1, (0x8000).L"
    });
    Then({
        "D1 is 0x00000001",
        "(0x00008000).B is 0x5",
        "SR is S,0,0",
        "CYCLES is 20"
    });
}
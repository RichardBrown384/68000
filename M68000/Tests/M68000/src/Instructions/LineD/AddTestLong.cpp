#include "M68000/Fixtures/M68000Test.h"

class ADDTestLong : public M68000Test {};

TEST_F(ADDTestLong, DataRegisterDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01010101",
        "D2 is 0x01010101",
    });
    When({
        "ADD.L D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x01010101",
        "D2 is 0x02020202",
    });
}

TEST_F(ADDTestLong, DataRegisterDataRegisterFlagNVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x10000000",
        "D2 is 0x70000000",
    });
    When({
        "ADD.L D1, D2"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x10000000",
        "D2 is 0x80000000",
    });
}

TEST_F(ADDTestLong, AddressRegisterDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D2 is 0x01010101",
        "A2 is 0x01010101",
    });
    When({
        "ADD.L A2, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D2 is 0x02020202",
        "A2 is 0x01010101",
    });
}

TEST_F(ADDTestLong, AddressIndirectDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01030201",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x04060604",
    });
    When({
        "ADD.L (A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x05090805",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x04060604",
    });
}

TEST_F(ADDTestLong, AddressIncrementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01030201",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x04060604",
    });
    When({
        "ADD.L (A1)+, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x05090805",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x04060604",
    });
}

TEST_F(ADDTestLong, AddressDecrementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01030201",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x04060604",
    });
    When({
        "ADD.L -(A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 16",
        "D1 is 0x05090805",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x04060604",
    });
}

TEST_F(ADDTestLong, AddressDisplacementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01030201",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x04060604",
    });
    When({
        "ADD.L (2, A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "D1 is 0x05090805",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x04060604",
    });
}

TEST_F(ADDTestLong, AddressIndexDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01030201",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x04060604",
    });
    When({
        "ADD.L (2, A1, A2.L), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 20",
        "D1 is 0x05090805",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x04060604",
    });
}

TEST_F(ADDTestLong, ShortDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01030201",
        "(0x00004000).L is 0x04060604",
    });
    When({
        "ADD.L (0x4000).W, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "D1 is 0x05090805",
        "(0x00004000).L is 0x04060604",
    });
}

TEST_F(ADDTestLong, LongDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01030201",
        "(0x00008000).L is 0x04060604",
    });
    When({
        "ADD.L (0x8000).L, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 22",
        "D1 is 0x05090805",
        "(0x00008000).L is 0x04060604",
    });
}

TEST_F(ADDTestLong, PCDisplacementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01030201",
        "(0x00001060).L is 0x04060604",
    });
    When({
        "ADD.L (0x5E, PC), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "D1 is 0x05090805",
        "(0x00001060).L is 0x04060604",
    });
}

TEST_F(ADDTestLong, PCIndexDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01030201",
        "A1 is 0x00000010",
        "(0x00001070).L is 0x04060604",
    });
    When({
        "ADD.L (0x5E, PC, A1.L), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 20",
        "D1 is 0x05090805",
        "A1 is 0x00000010",
        "(0x00001070).L is 0x04060604",
    });
}

TEST_F(ADDTestLong, ImmediateDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01030201",
    });
    When({
        "ADD.L #0x04060604, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 16",
        "D1 is 0x05090805",
    });
}

TEST_F(ADDTestLong, DataRegisterAddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x04060604",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x01030201",
    });
    When({
        "ADD.L D1, (A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 20",
        "D1 is 0x04060604",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x05090805",
    });
}

TEST_F(ADDTestLong, DataRegisterAddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x04060604",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x01030201",
    });
    When({
        "ADD.L D1, (A1)+"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 20",
        "D1 is 0x04060604",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x05090805",
    });
}

TEST_F(ADDTestLong, DataRegisterAddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x04060604",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x01030201",
    });
    When({
        "ADD.L D1, -(A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 22",
        "D1 is 0x04060604",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x05090805",
    });
}

TEST_F(ADDTestLong, DataRegisterAddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x04060604",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x01030201",
    });
    When({
        "ADD.L D1, (2, A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 24",
        "D1 is 0x04060604",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x05090805",
    });
}

TEST_F(ADDTestLong, DataRegisterAddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x04060604",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x01030201",
    });
    When({
        "ADD.L D1, (2, A1, A2.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 26",
        "D1 is 0x04060604",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x05090805",
    });
}

TEST_F(ADDTestLong, DataRegisterAddressShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x04060604",
        "(0x00004000).L is 0x01030201",
    });
    When({
        "ADD.L D1, (0x4000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 24",
        "D1 is 0x04060604",
        "(0x00004000).L is 0x05090805",
    });
}

TEST_F(ADDTestLong, DataRegisterAddressLongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x04060604",
        "(0x00008000).L is 0x01030201",
    });
    When({
        "ADD.L D1, (0x8000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 28",
        "D1 is 0x04060604",
        "(0x00008000).L is 0x05090805",
    });
}

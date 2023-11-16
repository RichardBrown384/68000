#include "M68000/Fixtures/M68000Test.h"

class ADDTestLong : public M68000Test {};

TEST_F(ADDTestLong, DataRegisterDataRegisterWorks) {
    Given({
        "D1 is 0x01010101",
        "D2 is 0x01010101",
        "SR is S,0,0"
    });
    When({
        "ADD.L D1, D2"
    });
    Then({
        "D1 is 0x01010101",
        "D2 is 0x02020202",
        "SR is S,0,0"
    });
}

TEST_F(ADDTestLong, DataRegisterDataRegisterFlagNVWorks) {
    Given({
        "D1 is 0x10000000",
        "D2 is 0x70000000",
        "SR is S,0,0"
    });
    When({
        "ADD.L D1, D2"
    });
    Then({
        "D1 is 0x10000000",
        "D2 is 0x80000000",
        "SR is S,0,NV"
    });
}

TEST_F(ADDTestLong, AddressRegisterDataRegisterWorks) {
    Given({
        "A2 is 0x01010101",
        "D2 is 0x01010101",
        "SR is S,0,0"
    });
    When({
        "ADD.L A2, D2"
    });
    Then({
        "A2 is 0x01010101",
        "D2 is 0x02020202",
        "SR is S,0,0"
    });
}

TEST_F(ADDTestLong, AddressIndirectDataRegisterWorks) {
    Given({
        "D1 is 0x01030201",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x04060604",
        "SR is S,0,0"
    });
    When({
        "ADD.L (A1), D1"
    });
    Then({
        "D1 is 0x05090805",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x04060604",
        "SR is S,0,0"
    });
}

TEST_F(ADDTestLong, AddressIncrementDataRegisterWorks) {
    Given({
        "D1 is 0x01030201",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x04060604",
        "SR is S,0,0"
    });
    When({
        "ADD.L (A1)+, D1"
    });
    Then({
        "D1 is 0x05090805",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x04060604",
        "SR is S,0,0"
    });
}

TEST_F(ADDTestLong, AddressDecrementDataRegisterWorks) {
    Given({
        "D1 is 0x01030201",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x04060604",
        "SR is S,0,0"
    });
    When({
        "ADD.L -(A1), D1"
    });
    Then({
        "D1 is 0x05090805",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x04060604",
        "SR is S,0,0"
    });
}

TEST_F(ADDTestLong, AddressDisplacementDataRegisterWorks) {
    Given({
        "D1 is 0x01030201",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x04060604",
        "SR is S,0,0"
    });
    When({
        "ADD.L (2, A1), D1"
    });
    Then({
        "D1 is 0x05090805",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x04060604",
        "SR is S,0,0"
    });
}

TEST_F(ADDTestLong, AddressIndexDataRegisterWorks) {
    Given({
        "D1 is 0x01030201",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x04060604",
        "SR is S,0,0"
    });
    When({
        "ADD.L (2, A1, A2.L), D1"
    });
    Then({
        "D1 is 0x05090805",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x04060604",
        "SR is S,0,0"
    });
}

TEST_F(ADDTestLong, ShortDataRegisterWorks) {
    Given({
        "D1 is 0x01030201",
        "(0x00004000).L is 0x04060604",
        "SR is S,0,0"
    });
    When({
        "ADD.L (0x4000).W, D1"
    });
    Then({
        "D1 is 0x05090805",
        "(0x00004000).L is 0x04060604",
        "SR is S,0,0"
    });
}

TEST_F(ADDTestLong, LongDataRegisterWorks) {
    Given({
        "D1 is 0x01030201",
        "(0x00008000).L is 0x04060604",
        "SR is S,0,0"
    });
    When({
        "ADD.L (0x8000).L, D1"
    });
    Then({
        "D1 is 0x05090805",
        "(0x00008000).L is 0x04060604",
        "SR is S,0,0"
    });
}

TEST_F(ADDTestLong, PCDisplacementDataRegisterWorks) {
    Given({
        "D1 is 0x01030201",
        "(0x00001060).L is 0x04060604",
        "SR is S,0,0"
    });
    When({
        "ADD.L (0x5E, PC), D1"
    });
    Then({
        "D1 is 0x05090805",
        "(0x00001060).L is 0x04060604",
        "SR is S,0,0"
    });
}

TEST_F(ADDTestLong, PCIndexDataRegisterWorks) {
    Given({
        "D1 is 0x01030201",
        "A1 is 0x00000010",
        "(0x00001070).L is 0x04060604",
        "SR is S,0,0"
    });
    When({
        "ADD.L (0x5E, PC, A1.L), D1"
    });
    Then({
        "D1 is 0x05090805",
        "A1 is 0x00000010",
        "(0x00001070).L is 0x04060604",
        "SR is S,0,0"
    });
}

TEST_F(ADDTestLong, ImmediateDataRegisterWorks) {
    Given({
        "D1 is 0x01030201",
        "SR is S,0,0"
    });
    When({
        "ADD.L #0x04060604, D1"
    });
    Then({
        "D1 is 0x05090805",
        "SR is S,0,0"
    });
}

TEST_F(ADDTestLong, DataRegisterAddressIndirectWorks) {
    Given({
        "D1 is 0x04060604",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x01030201",
        "SR is S,0,0"
    });
    When({
        "ADD.L D1, (A1)"
    });
    Then({
        "D1 is 0x04060604",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x05090805",
        "SR is S,0,0"
    });
}

TEST_F(ADDTestLong, DataRegisterAddressIncrementWorks) {
    Given({
        "D1 is 0x04060604",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x01030201",
        "SR is S,0,0"
    });
    When({
        "ADD.L D1, (A1)+"
    });
    Then({
        "D1 is 0x04060604",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x05090805",
        "SR is S,0,0"
    });
}

TEST_F(ADDTestLong, DataRegisterAddressDecrementWorks) {
    Given({
        "D1 is 0x04060604",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x01030201",
        "SR is S,0,0"
    });
    When({
        "ADD.L D1, -(A1)"
    });
    Then({
        "D1 is 0x04060604",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x05090805",
        "SR is S,0,0"
    });
}

TEST_F(ADDTestLong, DataRegisterAddressIndexWorks) {
    Given({
        "D1 is 0x04060604",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x01030201",
        "SR is S,0,0"
    });
    When({
        "ADD.L D1, (2, A1)"
    });
    Then({
        "D1 is 0x04060604",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x05090805",
        "SR is S,0,0"
    });
}

TEST_F(ADDTestLong, DataRegisterAddressDisplacementWorks) {
    Given({
        "D1 is 0x04060604",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x01030201",
        "SR is S,0,0"
    });
    When({
        "ADD.L D1, (2, A1, A2.L)"
    });
    Then({
        "D1 is 0x04060604",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x05090805",
        "SR is S,0,0"
    });
}

TEST_F(ADDTestLong, DataRegisterAddressShortWorks) {
    Given({
        "D1 is 0x04060604",
        "(0x00004000).L is 0x01030201",
        "SR is S,0,0"
    });
    When({
        "ADD.L D1, (0x4000).W"
    });
    Then({
        "D1 is 0x04060604",
        "(0x00004000).L is 0x05090805",
        "SR is S,0,0"
    });
}

TEST_F(ADDTestLong, DataRegisterAddressLongWorks) {
    Given({
        "D1 is 0x04060604",
        "(0x00008000).L is 0x01030201",
        "SR is S,0,0"
    });
    When({
        "ADD.L D1, (0x8000).L"
    });
    Then({
        "D1 is 0x04060604",
        "(0x00008000).L is 0x05090805",
        "SR is S,0,0"
    });
}
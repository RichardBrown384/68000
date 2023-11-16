#include "M68000/Fixtures/M68000Test.h"

class ADDTestWord : public M68000Test {};

TEST_F(ADDTestWord, DataRegisterDataRegisterWorks) {
    Given({
        "D1 is 0x01012003",
        "D2 is 0x0101E000",
        "SR is S,0,0"
    });
    When({
        "ADD.W D1, D2"
    });
    Then({
        "D1 is 0x01012003",
        "D2 is 0x01010003",
        "SR is S,0,XC",
        "CYCLES is 4"
    });
}

TEST_F(ADDTestWord, DataRegisterDataRegisterFlagNVWorks) {
    Given({
        "D1 is 0x01011000",
        "D2 is 0x01017000",
        "SR is S,0,0"
    });
    When({
        "ADD.W D1, D2"
    });
    Then({
        "D1 is 0x01011000",
        "D2 is 0x01018000",
        "SR is S,0,NV",
        "CYCLES is 4"
    });
}

TEST_F(ADDTestWord, AddressRegisterDataRegisterWorks) {
    Given({
        "A2 is 0x01010101",
        "D2 is 0x01010101",
        "SR is S,0,0"
    });
    When({
        "ADD.W A2, D2"
    });
    Then({
        "A2 is 0x01010101",
        "D2 is 0x01010202",
        "SR is S,0,0",
        "CYCLES is 4"
    });
}

TEST_F(ADDTestWord, AddressIndirectDataRegisterWorks) {
    Given({
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "ADD.W (A1), D1"
    });
    Then({
        "D1 is 0x00000805",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0",
        "CYCLES is 8"
    });
}

TEST_F(ADDTestWord, AddressIncrementDataRegisterWorks) {
    Given({
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "ADD.W (A1)+, D1"
    });
    Then({
        "D1 is 0x00000805",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0",
        "CYCLES is 8"
    });
}

TEST_F(ADDTestWord, AddressDecrementDataRegisterWorks) {
    Given({
        "D1 is 0x00000201",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "ADD.W -(A1), D1"
    });
    Then({
        "D1 is 0x00000805",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0",
        "CYCLES is 10"
    });
}

TEST_F(ADDTestWord, AddressDisplacementDataRegisterWorks) {
    Given({
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "ADD.W (2, A1), D1"
    });
    Then({
        "D1 is 0x00000805",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x0604",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(ADDTestWord, AddressIndexDataRegisterWorks) {
    Given({
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "ADD.W (2, A1, A2.L), D1"
    });
    Then({
        "D1 is 0x00000805",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x0604",
        "SR is S,0,0",
        "CYCLES is 14"
    });
}

TEST_F(ADDTestWord, ShortDataRegisterWorks) {
    Given({
        "D1 is 0x00000201",
        "(0x00004000).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "ADD.W (0x4000).W, D1"
    });
    Then({
        "D1 is 0x00000805",
        "(0x00004000).W is 0x0604",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(ADDTestWord, LongDataRegisterWorks) {
    Given({
        "D1 is 0x00000201",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "ADD.W (0x8000).L, D1"
    });
    Then({
        "D1 is 0x00000805",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(ADDTestWord, PCDisplacementDataRegisterWorks) {
    Given({
        "D1 is 0x00000201",
        "(0x00001060).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "ADD.W (0x5E, PC), D1"
    });
    Then({
        "D1 is 0x00000805",
        "(0x00001060).W is 0x0604",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(ADDTestWord, PCIndexDataRegisterWorks) {
    Given({
        "D1 is 0x00000201",
        "A1 is 0x00000010",
        "(0x00001070).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "ADD.W (0x5E, PC, A1.L), D1"
    });
    Then({
        "D1 is 0x00000805",
        "A1 is 0x00000010",
        "(0x00001070).W is 0x0604",
        "SR is S,0,0",
        "CYCLES is 14"
    });
}

TEST_F(ADDTestWord, ImmediateDataRegisterWorks) {
    Given({
        "D1 is 0x00000201",
        "SR is S,0,0"
    });
    When({
        "ADD.W #0x0604, D1"
    });
    Then({
        "D1 is 0x00000805",
        "SR is S,0,0",
        "CYCLES is 8"
    });
}

TEST_F(ADDTestWord, DataRegisterAddressIndirectWorks) {
    Given({
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "ADD.W D1, (A1)"
    });
    Then({
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0805",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(ADDTestWord, DataRegisterAddressIncrementWorks) {
    Given({
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "ADD.W D1, (A1)+"
    });
    Then({
        "D1 is 0x00000201",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x0805",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(ADDTestWord, DataRegisterAddressDecrementWorks) {
    Given({
        "D1 is 0x00000201",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "ADD.W D1, -(A1)"
    });
    Then({
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0805",
        "SR is S,0,0",
        "CYCLES is 14"
    });
}

TEST_F(ADDTestWord, DataRegisterAddressIndexWorks) {
    Given({
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "ADD.W D1, (2, A1)"
    });
    Then({
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x0805",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(ADDTestWord, DataRegisterAddressDisplacementWorks) {
    Given({
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "ADD.W D1, (2, A1, A2.L)"
    });
    Then({
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x0805",
        "SR is S,0,0",
        "CYCLES is 18"
    });
}

TEST_F(ADDTestWord, DataRegisterShortWorks) {
    Given({
        "D1 is 0x00000201",
        "(0x00004000).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "ADD.W D1, (0x4000).W"
    });
    Then({
        "D1 is 0x00000201",
        "(0x00004000).W is 0x0805",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(ADDTestWord, DataRegisterLongWorks) {
    Given({
        "D1 is 0x00000201",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "ADD.W D1, (0x8000).L"
    });
    Then({
        "D1 is 0x00000201",
        "(0x00008000).W is 0x0805",
        "SR is S,0,0",
        "CYCLES is 20"
    });
}
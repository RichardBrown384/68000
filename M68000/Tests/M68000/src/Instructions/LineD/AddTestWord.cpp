#include "M68000/Fixtures/M68000Test.h"

class ADDTestWord : public M68000Test {};

TEST_F(ADDTestWord, DataRegisterDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01012003",
        "D2 is 0x0101E000",
    });
    When({
        "ADD.W D1, D2"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01012003",
        "D2 is 0x01010003",
    });
}

TEST_F(ADDTestWord, DataRegisterDataRegisterFlagNVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01011000",
        "D2 is 0x01017000",
    });
    When({
        "ADD.W D1, D2"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01011000",
        "D2 is 0x01018000",
    });
}

TEST_F(ADDTestWord, AddressRegisterDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D2 is 0x01010101",
        "A2 is 0x01010101",
    });
    When({
        "ADD.W A2, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D2 is 0x01010202",
        "A2 is 0x01010101",
    });
}

TEST_F(ADDTestWord, AddressIndirectDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0604",
    });
    When({
        "ADD.W (A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x00000805",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0604",
    });
}

TEST_F(ADDTestWord, AddressIncrementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0604",
    });
    When({
        "ADD.W (A1)+, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x00000805",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x0604",
    });
}

TEST_F(ADDTestWord, AddressDecrementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000201",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x0604",
    });
    When({
        "ADD.W -(A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0x00000805",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0604",
    });
}

TEST_F(ADDTestWord, AddressDisplacementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x0604",
    });
    When({
        "ADD.W (2, A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x00000805",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x0604",
    });
}

TEST_F(ADDTestWord, AddressIndexDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x0604",
    });
    When({
        "ADD.W (2, A1, A2.L), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0x00000805",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x0604",
    });
}

TEST_F(ADDTestWord, ShortDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000201",
        "(0x00004000).W is 0x0604",
    });
    When({
        "ADD.W (0x4000).W, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x00000805",
        "(0x00004000).W is 0x0604",
    });
}

TEST_F(ADDTestWord, LongDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000201",
        "(0x00008000).W is 0x0604",
    });
    When({
        "ADD.W (0x8000).L, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 16",
        "D1 is 0x00000805",
        "(0x00008000).W is 0x0604",
    });
}

TEST_F(ADDTestWord, PCDisplacementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000201",
        "(0x00001060).W is 0x0604",
    });
    When({
        "ADD.W (0x5E, PC), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x00000805",
        "(0x00001060).W is 0x0604",
    });
}

TEST_F(ADDTestWord, PCIndexDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000201",
        "A1 is 0x00000010",
        "(0x00001070).W is 0x0604",
    });
    When({
        "ADD.W (0x5E, PC, A1.L), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0x00000805",
        "A1 is 0x00000010",
        "(0x00001070).W is 0x0604",
    });
}

TEST_F(ADDTestWord, ImmediateDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000201",
    });
    When({
        "ADD.W #0x0604, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 8",
        "D1 is 0x00000805",
    });
}

TEST_F(ADDTestWord, DataRegisterAddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0604",
    });
    When({
        "ADD.W D1, (A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0805",
    });
}

TEST_F(ADDTestWord, DataRegisterAddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0604",
    });
    When({
        "ADD.W D1, (A1)+"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x00000201",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x0805",
    });
}

TEST_F(ADDTestWord, DataRegisterAddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000201",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x0604",
    });
    When({
        "ADD.W D1, -(A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0805",
    });
}

TEST_F(ADDTestWord, DataRegisterAddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x0604",
    });
    When({
        "ADD.W D1, (2, A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x0805",
    });
}

TEST_F(ADDTestWord, DataRegisterAddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x0604",
    });
    When({
        "ADD.W D1, (2, A1, A2.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x0805",
    });
}

TEST_F(ADDTestWord, DataRegisterShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000201",
        "(0x00004000).W is 0x0604",
    });
    When({
        "ADD.W D1, (0x4000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "D1 is 0x00000201",
        "(0x00004000).W is 0x0805",
    });
}

TEST_F(ADDTestWord, DataRegisterLongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000201",
        "(0x00008000).W is 0x0604",
    });
    When({
        "ADD.W D1, (0x8000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 20",
        "D1 is 0x00000201",
        "(0x00008000).W is 0x0805",
    });
}

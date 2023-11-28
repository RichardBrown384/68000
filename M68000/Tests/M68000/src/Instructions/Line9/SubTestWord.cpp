#include "M68000/Fixtures/M68000Test.h"

class SUBTestWord : public M68000Test {};

TEST_F(SUBTestWord, DataRegisterDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01012000",
        "D2 is 0x0101E300",
    });
    When({
        "SUB.W D1, D2"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01012000",
        "D2 is 0x0101C300",
    });
}

TEST_F(SUBTestWord, DataRegisterDataRegisterFlagNVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01018001",
        "D2 is 0x01013201",
    });
    When({
        "SUB.W D1, D2"
    });
    Then({
        "SR is S,0,XNVC",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01018001",
        "D2 is 0x0101B200",
    });
}

TEST_F(SUBTestWord, AddressRegisterDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D2 is 0x01010607",
        "A2 is 0x01010103",
    });
    When({
        "SUB.W A2, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D2 is 0x01010504",
        "A2 is 0x01010103",
    });
}

TEST_F(SUBTestWord, AddressIndirectDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0103",
    });
    When({
        "SUB.W (A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x00000504",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0103",
    });
}

TEST_F(SUBTestWord, AddressIncrementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0103",
    });
    When({
        "SUB.W (A1)+, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x00000504",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x0103",
    });
}

TEST_F(SUBTestWord, AddressDecrementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000607",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x0103",
    });
    When({
        "SUB.W -(A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0x00000504",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0103",
    });
}

TEST_F(SUBTestWord, AddressDisplacementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000607",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x0103",
    });
    When({
        "SUB.W (2, A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x00000504",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x0103",
    });
}

TEST_F(SUBTestWord, AddressIndexDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000607",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x0103",
    });
    When({
        "SUB.W (2, A1, A2.L), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0x00000504",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x0103",
    });
}

TEST_F(SUBTestWord, ShortDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000607",
        "(0x00004000).W is 0x0103",
    });
    When({
        "SUB.W (0x4000).W, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x00000504",
        "(0x00004000).W is 0x0103",
    });
}

TEST_F(SUBTestWord, LongDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000607",
        "(0x00008000).W is 0x0103",
    });
    When({
        "SUB.W (0x8000).L, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 16",
        "D1 is 0x00000504",
        "(0x00008000).W is 0x0103",
    });
}

TEST_F(SUBTestWord, PCDisplacementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000607",
        "(0x00001060).W is 0x0103",
    });
    When({
        "SUB.W (0x5E, PC), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x00000504",
        "(0x00001060).W is 0x0103",
    });
}

TEST_F(SUBTestWord, PCIndexDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000607",
        "A1 is 0x00000010",
        "(0x00001070).W is 0x0103",
    });
    When({
        "SUB.W (0x5E, PC, A1.L), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0x00000504",
        "A1 is 0x00000010",
        "(0x00001070).W is 0x0103",
    });
}

TEST_F(SUBTestWord, ImmediateDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000607",
    });
    When({
        "SUB.W #0x0103, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 8",
        "D1 is 0x00000504",
    });
}

TEST_F(SUBTestWord, DataRegisterAddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0604",
    });
    When({
        "SUB.W D1, (A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0403",
    });
}

TEST_F(SUBTestWord, DataRegisterAddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0604",
    });
    When({
        "SUB.W D1, (A1)+"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x00000201",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x0403",
    });
}

TEST_F(SUBTestWord, DataRegisterAddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000201",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x0604",
    });
    When({
        "SUB.W D1, -(A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0403",
    });
}

TEST_F(SUBTestWord, DataRegisterAddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x0604",
    });
    When({
        "SUB.W D1, (2, A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x0403",
    });
}

TEST_F(SUBTestWord, DataRegisterAddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x0604",
    });
    When({
        "SUB.W D1, (2, A1, A2.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x0403",
    });
}

TEST_F(SUBTestWord, DataRegisterShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000201",
        "(0x00004000).W is 0x0604",
    });
    When({
        "SUB.W D1, (0x4000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "D1 is 0x00000201",
        "(0x00004000).W is 0x0403",
    });
}

TEST_F(SUBTestWord, DataRegisterLongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000201",
        "(0x00008000).W is 0x0604",
    });
    When({
        "SUB.W D1, (0x8000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 20",
        "D1 is 0x00000201",
        "(0x00008000).W is 0x0403",
    });
}

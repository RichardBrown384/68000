#include "M68000/Fixtures/M68000Test.h"

class SUBTestWord : public M68000Test {};

TEST_F(SUBTestWord, DataRegisterDataRegisterWorks) {
    Given({
        "D1 is 0x01012000",
        "D2 is 0x0101E300",
        "SR is S,0,0"
    });
    When({
        "SUB.W D1, D2"
    });
    Then({
        "D1 is 0x01012000",
        "D2 is 0x0101C300",
        "SR is S,0,N"
    });
}

TEST_F(SUBTestWord, DataRegisterDataRegisterFlagNVWorks) {
    Given({
        "D1 is 0x01018001",
        "D2 is 0x01013201",
        "SR is S,0,0"
    });
    When({
        "SUB.W D1, D2"
    });
    Then({
        "D1 is 0x01018001",
        "D2 is 0x0101B200",
        "SR is S,0,XNVC"
    });
}

TEST_F(SUBTestWord, AddressRegisterDataRegisterWorks) {
    Given({
        "A2 is 0x01010103",
        "D2 is 0x01010607",
        "SR is S,0,0"
    });
    When({
        "SUB.W A2, D2"
    });
    Then({
        "A2 is 0x01010103",
        "D2 is 0x01010504",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestWord, AddressIndirectDataRegisterWorks) {
    Given({
        "D1 is 0x00000607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0103",
        "SR is S,0,0"
    });
    When({
        "SUB.W (A1), D1"
    });
    Then({
        "D1 is 0x00000504",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0103",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestWord, AddressIncrementDataRegisterWorks) {
    Given({
        "D1 is 0x00000607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0103",
        "SR is S,0,0"
    });
    When({
        "SUB.W (A1)+, D1"
    });
    Then({
        "D1 is 0x00000504",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x0103",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestWord, AddressDecrementDataRegisterWorks) {
    Given({
        "D1 is 0x00000607",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x0103",
        "SR is S,0,0"
    });
    When({
        "SUB.W -(A1), D1"
    });
    Then({
        "D1 is 0x00000504",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0103",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestWord, AddressDisplacementDataRegisterWorks) {
    Given({
        "D1 is 0x00000607",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x0103",
        "SR is S,0,0"
    });
    When({
        "SUB.W (2, A1), D1"
    });
    Then({
        "D1 is 0x00000504",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x0103",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestWord, AddressIndexDataRegisterWorks) {
    Given({
        "D1 is 0x00000607",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x0103",
        "SR is S,0,0"
    });
    When({
        "SUB.W (2, A1, A2.L), D1"
    });
    Then({
        "D1 is 0x00000504",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x0103",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestWord, ShortDataRegisterWorks) {
    Given({
        "D1 is 0x00000607",
        "(0x00004000).W is 0x0103",
        "SR is S,0,0"
    });
    When({
        "SUB.W (0x4000).W, D1"
    });
    Then({
        "D1 is 0x00000504",
        "(0x00004000).W is 0x0103",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestWord, LongDataRegisterWorks) {
    Given({
        "D1 is 0x00000607",
        "(0x00008000).W is 0x0103",
        "SR is S,0,0"
    });
    When({
        "SUB.W (0x8000).L, D1"
    });
    Then({
        "D1 is 0x00000504",
        "(0x00008000).W is 0x0103",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestWord, PCDisplacementDataRegisterWorks) {
    Given({
        "D1 is 0x00000607",
        "(0x00001060).W is 0x0103",
        "SR is S,0,0"
    });
    When({
        "SUB.W (0x5E, PC), D1"
    });
    Then({
        "D1 is 0x00000504",
        "(0x00001060).W is 0x0103",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestWord, PCIndexDataRegisterWorks) {
    Given({
        "D1 is 0x00000607",
        "A1 is 0x00000010",
        "(0x00001070).W is 0x0103",
        "SR is S,0,0"
    });
    When({
        "SUB.W (0x5E, PC, A1.L), D1"
    });
    Then({
        "D1 is 0x00000504",
        "A1 is 0x00000010",
        "(0x00001070).W is 0x0103",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestWord, ImmediateDataRegisterWorks) {
    Given({
        "D1 is 0x00000607",
        "SR is S,0,0"
    });
    When({
        "SUB.W #0x0103, D1"
    });
    Then({
        "D1 is 0x00000504",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestWord, DataRegisterAddressIndirectWorks) {
    Given({
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "SUB.W D1, (A1)"
    });
    Then({
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0403",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestWord, DataRegisterAddressIncrementWorks) {
    Given({
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "SUB.W D1, (A1)+"
    });
    Then({
        "D1 is 0x00000201",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x0403",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestWord, DataRegisterAddressDecrementWorks) {
    Given({
        "D1 is 0x00000201",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "SUB.W D1, -(A1)"
    });
    Then({
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0403",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestWord, DataRegisterAddressIndexWorks) {
    Given({
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "SUB.W D1, (2, A1)"
    });
    Then({
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x0403",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestWord, DataRegisterAddressDisplacementWorks) {
    Given({
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "SUB.W D1, (2, A1, A2.L)"
    });
    Then({
        "D1 is 0x00000201",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x0403",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestWord, DataRegisterShortWorks) {
    Given({
        "D1 is 0x00000201",
        "(0x00004000).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "SUB.W D1, (0x4000).W"
    });
    Then({
        "D1 is 0x00000201",
        "(0x00004000).W is 0x0403",
        "SR is S,0,0"
    });
}

TEST_F(SUBTestWord, DataRegisterLongWorks) {
    Given({
        "D1 is 0x00000201",
        "(0x00008000).W is 0x0604",
        "SR is S,0,0"
    });
    When({
        "SUB.W D1, (0x8000).L"
    });
    Then({
        "D1 is 0x00000201",
        "(0x00008000).W is 0x0403",
        "SR is S,0,0"
    });
}
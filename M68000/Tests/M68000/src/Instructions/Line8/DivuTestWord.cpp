#include "M68000/Fixtures/M68000Test.h"

class DIVUTestWord : public M68000Test {};

TEST_F(DIVUTestWord, DataRegisterTrivialDividendAndDivisorWork) {
    Given({
        "D0 is 0x00000004",
        "D1 is 0x00000009",
        "SR is S,0,0"
    });
    When({
        "DIVU D0, D1"
    });
    Then({
        "D0 is 0x00000004",
        "D1 is 0x00010002",
        "SR is S,0,0",
        "CYCLES is 134"
    });
}

TEST_F(DIVUTestWord, DataRegisterLargeDividendAndDivisorWork) {
    Given({
        "D0 is 0x0000FFFC",
        "D1 is 0x0FFFFFF7",
        "SR is S,0,0"
    });
    When({
        "DIVU D0, D1"
    });
    Then({
        "D0 is 0x0000FFFC",
        "D1 is 0x3FF71000",
        "SR is S,0,0",
        "CYCLES is 134"
    });
}

TEST_F(DIVUTestWord, DataRegisterSmallDividendLargeDivisorWork) {
    Given({
        "D0 is 0x0000FFFC",
        "D1 is 0x0000ABCD",
        "SR is S,0,0"
    });
    When({
        "DIVU D0, D1"
    });
    Then({
        "D0 is 0x0000FFFC",
        "D1 is 0xABCD0000",
        "SR is S,0,Z",
        "CYCLES is 136"
    });
}

TEST_F(DIVUTestWord, DataRegisterUpper16BitsOfDivisorAreIgnored) {
    Given({
        "D0 is 0x0010FFFC",
        "D1 is 0x0010ABCD",
        "SR is S,0,0"
    });
    When({
        "DIVU D0, D1"
    });
    Then({
        "D0 is 0x0010FFFC",
        "D1 is 0xAC0D0010",
        "SR is S,0,0",
        "CYCLES is 132"
    });
}

TEST_F(DIVUTestWord, DataRegisterFlagNWorks) {
    Given({
        "D1 is 0x00000001",
        "D2 is 0x0000FFFF",
        "SR is S,0,0"
    });
    When({
        "DIVU D1, D2"
    });
    Then({
        "D1 is 0x00000001",
        "D2 is 0x0000FFFF",
        "SR is S,0,N",
        "CYCLES is 106"
    });
}

TEST_F(DIVUTestWord, DataRegisterFlagZWorks) {
    Given({
        "D1 is 0x00000008",
        "D2 is 0x00000003",
        "SR is S,0,0"
    });
    When({
        "DIVU D1, D2"
    });
    Then({
        "D1 is 0x00000008",
        "D2 is 0x00030000",
        "SR is S,0,Z",
        "CYCLES is 136"
    });
}

TEST_F(DIVUTestWord, DataRegisterFlagVWorks) {
    Given({
        "D0 is 0x00000001",
        "D1 is 0x00010000",
        "SR is S,0,0"
    });
    When({
        "DIVU D0, D1"
    });
    Then({
        "D0 is 0x00000001",
        "D1 is 0x00010000",
        "SR is S,0,V",
        "CYCLES is 10"
    });
}


TEST_F(DIVUTestWord, DataRegisterDivisionIsUnsigned) {
    Given({
        "D1 is 0x0000FFFF",
        "D2 is 0x0000FFFF",
        "SR is S,0,0"
    });
    When({
        "DIVU D1, D2"
    });
    Then({
        "D1 is 0x0000FFFF",
        "D2 is 0x00000001",
        "SR is S,0,0",
        "CYCLES is 136"
    });
}

TEST_F(DIVUTestWord, AddressIndirectWorks) {
    Given({
        "D1 is 0x0011A55A",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x8607",
        "SR is S,0,0"
    });
    When({
        "DIVU (A1), D1"
    });
    Then({
        "D1 is 0x5E730021",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x8607",
        "SR is S,0,0"
    });
}

TEST_F(DIVUTestWord, AddressIncrementWorks) {
    Given({
        "D1 is 0x0011A55A",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x8607",
        "SR is S,0,0"
    });
    When({
        "DIVU (A1)+, D1"
    });
    Then({
        "D1 is 0x5E730021",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x8607",
        "SR is S,0,0"
    });
}

TEST_F(DIVUTestWord, AddressDecrementWorks) {
    Given({
        "D1 is 0x0011A55A",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x8607",
        "SR is S,0,0"
    });
    When({
        "DIVU -(A1), D1"
    });
    Then({
        "D1 is 0x5E730021",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x8607",
        "SR is S,0,0"
    });
}

TEST_F(DIVUTestWord, AddressDisplacementWorks) {
    Given({
        "D1 is 0x0011A55A",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x8607",
        "SR is S,0,0"
    });
    When({
        "DIVU (2, A1), D1"
    });
    Then({
        "D1 is 0x5E730021",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x8607",
        "SR is S,0,0"
    });
}

TEST_F(DIVUTestWord, AddressIndexWorks) {
    Given({
        "D1 is 0x0011A55A",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x8607",
        "SR is S,0,0"
    });
    When({
        "DIVU (2, A1, A2.L), D1"
    });
    Then({
        "D1 is 0x5E730021",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x8607",
        "SR is S,0,0"
    });
}

TEST_F(DIVUTestWord, ShortWorks) {
    Given({
        "D1 is 0x0011A55A",
        "(0x00004000).W is 0x8607",
        "SR is S,0,0"
    });
    When({
        "DIVU (0x4000).W, D1"
    });
    Then({
        "D1 is 0x5E730021",
        "(0x00004000).W is 0x8607",
        "SR is S,0,0"
    });
}

TEST_F(DIVUTestWord, LongWorks) {
    Given({
        "D1 is 0x0011A55A",
        "(0x00008000).W is 0x8607",
        "SR is S,0,0"
    });
    When({
        "DIVU (0x8000).L, D1"
    });
    Then({
        "D1 is 0x5E730021",
        "(0x00008000).W is 0x8607",
        "SR is S,0,0"
    });
}

TEST_F(DIVUTestWord, PCDisplacementWorks) {
    Given({
        "D1 is 0x0011A55A",
        "(0x00001060).W is 0x8607",
        "SR is S,0,0"
    });
    When({
        "DIVU (0x5E, PC), D1"
    });
    Then({
        "D1 is 0x5E730021",
        "(0x00001060).W is 0x8607",
        "SR is S,0,0"
    });
}

TEST_F(DIVUTestWord, PCIndexWorks) {
    Given({
        "D1 is 0x0011A55A",
        "A1 is 0x00000010",
        "(0x00001070).W is 0x8607",
        "SR is S,0,0"
    });
    When({
        "DIVU (0x5E, PC, A1.L), D1"
    });
    Then({
        "D1 is 0x5E730021",
        "A1 is 0x00000010",
        "(0x00001070).W is 0x8607",
        "SR is S,0,0"
    });
}

TEST_F(DIVUTestWord, ImmediateWorks) {
    Given({
        "D1 is 0x0011A55A",
        "SR is S,0,0"
    });
    When({
        "DIVU #0x8607, D1"
    });
    Then({
        "D1 is 0x5E730021",
        "SR is S,0,0"
    });
}
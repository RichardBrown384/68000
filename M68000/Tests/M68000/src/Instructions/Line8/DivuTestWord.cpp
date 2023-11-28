#include "M68000/Fixtures/M68000Test.h"

class DIVUTestWord : public M68000Test {};

TEST_F(DIVUTestWord, DataRegisterTrivialDividendAndDivisorWork) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x00000004",
        "D1 is 0x00000009",
    });
    When({
        "DIVU D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 134",
        "D0 is 0x00000004",
        "D1 is 0x00010002",
    });
}

TEST_F(DIVUTestWord, DataRegisterLargeDividendAndDivisorWork) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x0000FFFC",
        "D1 is 0x0FFFFFF7",
    });
    When({
        "DIVU D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 134",
        "D0 is 0x0000FFFC",
        "D1 is 0x3FF71000",
    });
}

TEST_F(DIVUTestWord, DataRegisterSmallDividendLargeDivisorWork) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x0000FFFC",
        "D1 is 0x0000ABCD",
    });
    When({
        "DIVU D0, D1"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 136",
        "D0 is 0x0000FFFC",
        "D1 is 0xABCD0000",
    });
}

TEST_F(DIVUTestWord, DataRegisterUpper16BitsOfDivisorAreIgnored) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x0010FFFC",
        "D1 is 0x0010ABCD",
    });
    When({
        "DIVU D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 132",
        "D0 is 0x0010FFFC",
        "D1 is 0xAC0D0010",
    });
}

TEST_F(DIVUTestWord, DataRegisterFlagNWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000001",
        "D2 is 0x0000FFFF",
    });
    When({
        "DIVU D1, D2"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 106",
        "D1 is 0x00000001",
        "D2 is 0x0000FFFF",
    });
}

TEST_F(DIVUTestWord, DataRegisterFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000008",
        "D2 is 0x00000003",
    });
    When({
        "DIVU D1, D2"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 136",
        "D1 is 0x00000008",
        "D2 is 0x00030000",
    });
}

TEST_F(DIVUTestWord, DataRegisterFlagVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x00000001",
        "D1 is 0x00010000",
    });
    When({
        "DIVU D0, D1"
    });
    Then({
        "SR is S,0,V",
        "PC is 0x1002",
        "CYCLES is 10",
        "D0 is 0x00000001",
        "D1 is 0x00010000",
    });
}


TEST_F(DIVUTestWord, DataRegisterDivisionIsUnsigned) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0000FFFF",
        "D2 is 0x0000FFFF",
    });
    When({
        "DIVU D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 136",
        "D1 is 0x0000FFFF",
        "D2 is 0x00000001",
    });
}

TEST_F(DIVUTestWord, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0011A55A",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x8607",
    });
    When({
        "DIVU (A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 138",
        "D1 is 0x5E730021",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x8607",
    });
}

TEST_F(DIVUTestWord, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0011A55A",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x8607",
    });
    When({
        "DIVU (A1)+, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 138",
        "D1 is 0x5E730021",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x8607",
    });
}

TEST_F(DIVUTestWord, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0011A55A",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x8607",
    });
    When({
        "DIVU -(A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 140",
        "D1 is 0x5E730021",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x8607",
    });
}

TEST_F(DIVUTestWord, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0011A55A",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x8607",
    });
    When({
        "DIVU (2, A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 142",
        "D1 is 0x5E730021",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x8607",
    });
}

TEST_F(DIVUTestWord, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0011A55A",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x8607",
    });
    When({
        "DIVU (2, A1, A2.L), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 144",
        "D1 is 0x5E730021",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x8607",
    });
}

TEST_F(DIVUTestWord, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0011A55A",
        "(0x00004000).W is 0x8607",
    });
    When({
        "DIVU (0x4000).W, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 142",
        "D1 is 0x5E730021",
        "(0x00004000).W is 0x8607",
    });
}

TEST_F(DIVUTestWord, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0011A55A",
        "(0x00008000).W is 0x8607",
    });
    When({
        "DIVU (0x8000).L, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 146",
        "D1 is 0x5E730021",
        "(0x00008000).W is 0x8607",
    });
}

TEST_F(DIVUTestWord, PCDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0011A55A",
        "(0x00001060).W is 0x8607",
    });
    When({
        "DIVU (0x5E, PC), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 142",
        "D1 is 0x5E730021",
        "(0x00001060).W is 0x8607",
    });
}

TEST_F(DIVUTestWord, PCIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0011A55A",
        "A1 is 0x00000010",
        "(0x00001070).W is 0x8607",
    });
    When({
        "DIVU (0x5E, PC, A1.L), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 144",
        "D1 is 0x5E730021",
        "A1 is 0x00000010",
        "(0x00001070).W is 0x8607",
    });
}

TEST_F(DIVUTestWord, ImmediateWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0011A55A",
    });
    When({
        "DIVU #0x8607, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 138",
        "D1 is 0x5E730021",
    });
}

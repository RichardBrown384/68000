#include "M68000/Fixtures/M68000Test.h"

class DIVSTestWord : public M68000Test {};

TEST_F(DIVSTestWord, DataRegisterTrivialPositiveDividendAndDivisorWork) {
    Given({
        "D0 is 0x00000004",
        "D1 is 0x00000009",
        "SR is S,0,0"
    });
    When({
        "DIVS D0, D1"
    });
    Then({
        "D0 is 0x00000004",
        "D1 is 0x00010002",
        "SR is S,0,0",
        "CYCLES is 148"
    });
}

TEST_F(DIVSTestWord, DataRegisterTrivialNegativeDividendAndDivisorWork) {
    Given({
        "D0 is 0x0000FFFC",
        "D1 is 0xFFFFFFF7",
        "SR is S,0,0"
    });
    When({
        "DIVS D0, D1"
    });
    Then({
        "D0 is 0x0000FFFC",
        "D1 is 0xFFFF0002",
        "SR is S,0,0",
        "CYCLES is 152"
    });
}

TEST_F(DIVSTestWord, DataRegisterTrivialPositiveDividendNegativeDivisorWorks) {
    Given({
        "D0 is 0x0000FFFC",
        "D1 is 0x0000ABCD",
        "SR is S,0,0"
    });
    When({
        "DIVS D0, D1"
    });
    Then({
        "D0 is 0x0000FFFC",
        "D1 is 0x0001D50D",
        "SR is S,0,N",
        "CYCLES is 136"
    });
}

TEST_F(DIVSTestWord, DataRegisterTrivialNegativeDividendPositiveDivisorWorks) {
    Given({
        "D0 is 0x0000000B",
        "D1 is 0xFFFFABCD",
        "SR is S,0,0"
    });
    When({
        "DIVS D0, D1"
    });
    Then({
        "D0 is 0x0000000B",
        "D1 is 0xFFFAF859",
        "SR is S,0,N",
        "CYCLES is 142"
    });
}

TEST_F(DIVSTestWord, DataRegisterPostiveOverflowWorks) {
    Given({
        "D0 is 0x00000001",
        "D1 is 0x00010000",
        "SR is S,0,0"
    });
    When({
        "DIVS D0, D1"
    });
    Then({
        "D0 is 0x00000001",
        "D1 is 0x00010000",
        "SR is S,0,V",
        "CYCLES is 16"
    });
}

TEST_F(DIVSTestWord, DataRegisterNegativeOverflowWorks) {
    Given({
        "D0 is 0x00000001",
        "D1 is 0xFFF10000",
        "SR is S,0,0"
    });
    When({
        "DIVS D0, D1"
    });
    Then({
        "D0 is 0x00000001",
        "D1 is 0xFFF10000",
        "SR is S,0,V",
        "CYCLES is 18"
    });
}

TEST_F(DIVSTestWord, DataRegisterMinValueDividedByMinusOneWorks) {
    Given({
        "D0 is 0x0000FFFF",
        "D1 is 0x80000000",
        "SR is S,0,0"
    });
    When({
        "DIVS D0, D1"
    });
    Then({
        "D0 is 0x0000FFFF",
        "D1 is 0x80000000",
        "SR is S,0,V",
        "CYCLES is 18"
    });
}

TEST_F(DIVSTestWord, LateOverflowPositiveDividendPositiveDivisor) {
    Given({
        "D0 is 0x00000001",
        "D1 is 0x00008000",
        "SR is S,0,0"
    });
    When({
        "DIVS D0, D1"
    });
    Then({
        "D0 is 0x00000001",
        "D1 is 0x00008000",
        "SR is S,0,V",
        "CYCLES is 148"
    });
}

TEST_F(DIVSTestWord, LateOverflowNegativeDividendPositiveDivisor) {
    Given({
        "D0 is 0x00000001",
        "D1 is 0xFFFF0001",
        "SR is S,0,0"
    });
    When({
        "DIVS D0, D1"
    });
    Then({
        "D0 is 0x00000001",
        "D1 is 0xFFFF0001",
        "SR is S,0,V",
        "CYCLES is 126"
    });
}

TEST_F(DIVSTestWord, LateOverflowPositiveDividendNegativeDivisor) {
    Given({
        "D0 is 0x00008000",
        "D1 is 0x40008000",
        "SR is S,0,0"
    });
    When({
        "DIVS D0, D1"
    });
    Then({
        "D0 is 0x00008000",
        "D1 is 0x40008000",
        "SR is S,0,V",
        "CYCLES is 150"
    });
}

TEST_F(DIVSTestWord, LateOverflowNegativeDividendNegativeDivisor) {
    Given({
        "D0 is 0x00008000",
        "D1 is 0x80000001",
        "SR is S,0,0"
    });
    When({
        "DIVS D0, D1"
    });
    Then({
        "D0 is 0x00008000",
        "D1 is 0x80000001",
        "SR is S,0,V",
        "CYCLES is 124"
    });
}


TEST_F(DIVSTestWord, DataRegisterFlagZWorks) {
    Given({
        "D1 is 0x00001FFF",
        "D2 is 0x00000FFF",
        "SR is S,0,0"
    });
    When({
        "DIVS D1, D2"
    });
    Then({
        "D1 is 0x00001FFF",
        "D2 is 0x0FFF0000",
        "SR is S,0,Z"
    });
}

TEST_F(DIVSTestWord, DataRegisterDivisionIsSigned) {
    Given({
        "D1 is 0x0000FFFE",
        "D2 is 0x00000009",
        "SR is S,0,0"
    });
    When({
        "DIVS D1, D2"
    });
    Then({
        "D1 is 0x0000FFFE",
        "D2 is 0x0001FFFC",
        "SR is S,0,N",
        "CYCLES is 150"
    });
}

TEST_F(DIVSTestWord, AddressIndirectWorks) {
    Given({
        "D1 is 0x0011A55A",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x8607",
        "SR is S,0,0"
    });
    When({
        "DIVS (A1), D1"
    });
    Then({
        "D1 is 0x045DFFDB",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x8607",
        "SR is S,0,N"
    });
}

TEST_F(DIVSTestWord, AddressIncrementWorks) {
    Given({
        "D1 is 0x0011A55A",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x8607",
        "SR is S,0,0"
    });
    When({
        "DIVS (A1)+, D1"
    });
    Then({
        "D1 is 0x045DFFDB",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x8607",
        "SR is S,0,N"
    });
}

TEST_F(DIVSTestWord, AddressDecrementWorks) {
    Given({
        "D1 is 0x0011A55A",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x8607",
        "SR is S,0,0"
    });
    When({
        "DIVS -(A1), D1"
    });
    Then({
        "D1 is 0x045DFFDB",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x8607",
        "SR is S,0,N"
    });
}

TEST_F(DIVSTestWord, AddressDisplacementWorks) {
    Given({
        "D1 is 0x0011A55A",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x8607",
        "SR is S,0,0"
    });
    When({
        "DIVS (2, A1), D1"
    });
    Then({
        "D1 is 0x045DFFDB",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x8607",
        "SR is S,0,N"
    });
}

TEST_F(DIVSTestWord, AddressIndexWorks) {
    Given({
        "D1 is 0x0011A55A",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x8607",
        "SR is S,0,0"
    });
    When({
        "DIVS (2, A1, A2.L), D1"
    });
    Then({
        "D1 is 0x045DFFDB",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x8607",
        "SR is S,0,N"
    });
}

TEST_F(DIVSTestWord, ShortWorks) {
    Given({
        "D1 is 0x0011A55A",
        "(0x00004000).W is 0x8607",
        "SR is S,0,0"
    });
    When({
        "DIVS (0x4000).W, D1"
    });
    Then({
        "D1 is 0x045DFFDB",
        "(0x00004000).W is 0x8607",
        "SR is S,0,N"
    });
}

TEST_F(DIVSTestWord, LongWorks) {
    Given({
        "D1 is 0x0011A55A",
        "(0x00008000).W is 0x8607",
        "SR is S,0,0"
    });
    When({
        "DIVS (0x8000).L, D1"
    });
    Then({
        "D1 is 0x045DFFDB",
        "(0x00008000).W is 0x8607",
        "SR is S,0,N"
    });
}

TEST_F(DIVSTestWord, PCDisplacementWorks) {
    Given({
        "D1 is 0x0011A55A",
        "(0x00001060).W is 0x8607",
        "SR is S,0,0"
    });
    When({
        "DIVS (0x5E, PC), D1"
    });
    Then({
        "D1 is 0x045DFFDB",
        "(0x00001060).W is 0x8607",
        "SR is S,0,N"
    });
}

TEST_F(DIVSTestWord, PCIndexWorks) {
    Given({
        "D1 is 0x0011A55A",
        "A1 is 0x00000010",
        "(0x00001070).W is 0x8607",
        "SR is S,0,0"
    });
    When({
        "DIVS (0x5E, PC, A1.L), D1"
    });
    Then({
        "D1 is 0x045DFFDB",
        "A1 is 0x00000010",
        "(0x00001070).W is 0x8607",
        "SR is S,0,N"
    });
}

TEST_F(DIVSTestWord, ImmediateWorks) {
    Given({
        "D1 is 0x0011A55A",
        "SR is S,0,0"
    });
    When({
        "DIVS #0x8607, D1"
    });
    Then({
        "D1 is 0x045DFFDB",
        "SR is S,0,N"
    });
}
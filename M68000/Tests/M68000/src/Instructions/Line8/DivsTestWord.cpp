#include "M68000/Fixtures/M68000Test.h"

class DIVSTestWord : public M68000Test {};

TEST_F(DIVSTestWord, DataRegisterTrivialPositiveDividendAndDivisorWork) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x00000004",
        "D1 is 0x00000009",
    });
    When({
        "DIVS D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 148",
        "D0 is 0x00000004",
        "D1 is 0x00010002",
    });
}

TEST_F(DIVSTestWord, DataRegisterTrivialNegativeDividendAndDivisorWork) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x0000FFFC",
        "D1 is 0xFFFFFFF7",
    });
    When({
        "DIVS D0, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 152",
        "D0 is 0x0000FFFC",
        "D1 is 0xFFFF0002",
    });
}

TEST_F(DIVSTestWord, DataRegisterTrivialPositiveDividendNegativeDivisorWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x0000FFFC",
        "D1 is 0x0000ABCD",
    });
    When({
        "DIVS D0, D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 136",
        "D0 is 0x0000FFFC",
        "D1 is 0x0001D50D",
    });
}

TEST_F(DIVSTestWord, DataRegisterTrivialNegativeDividendPositiveDivisorWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x0000000B",
        "D1 is 0xFFFFABCD",
    });
    When({
        "DIVS D0, D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 142",
        "D0 is 0x0000000B",
        "D1 is 0xFFFAF859",
    });
}

TEST_F(DIVSTestWord, DataRegisterPostiveOverflowWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x00000001",
        "D1 is 0x00010000",
    });
    When({
        "DIVS D0, D1"
    });
    Then({
        "SR is S,0,V",
        "PC is 0x1002",
        "CYCLES is 16",
        "D0 is 0x00000001",
        "D1 is 0x00010000",
    });
}

TEST_F(DIVSTestWord, DataRegisterNegativeOverflowWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x00000001",
        "D1 is 0xFFF10000",
    });
    When({
        "DIVS D0, D1"
    });
    Then({
        "SR is S,0,V",
        "PC is 0x1002",
        "CYCLES is 18",
        "D0 is 0x00000001",
        "D1 is 0xFFF10000",
    });
}

TEST_F(DIVSTestWord, DataRegisterMinValueDividedByMinusOneWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x0000FFFF",
        "D1 is 0x80000000",
    });
    When({
        "DIVS D0, D1"
    });
    Then({
        "SR is S,0,V",
        "PC is 0x1002",
        "CYCLES is 18",
        "D0 is 0x0000FFFF",
        "D1 is 0x80000000",
    });
}

TEST_F(DIVSTestWord, LateOverflowPositiveDividendPositiveDivisor) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x00000001",
        "D1 is 0x00008000",
    });
    When({
        "DIVS D0, D1"
    });
    Then({
        "SR is S,0,V",
        "PC is 0x1002",
        "CYCLES is 148",
        "D0 is 0x00000001",
        "D1 is 0x00008000",
    });
}

TEST_F(DIVSTestWord, LateOverflowNegativeDividendPositiveDivisor) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x00000001",
        "D1 is 0xFFFF0001",
    });
    When({
        "DIVS D0, D1"
    });
    Then({
        "SR is S,0,V",
        "PC is 0x1002",
        "CYCLES is 126",
        "D0 is 0x00000001",
        "D1 is 0xFFFF0001",
    });
}

TEST_F(DIVSTestWord, LateOverflowPositiveDividendNegativeDivisor) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x00008000",
        "D1 is 0x40008000",
    });
    When({
        "DIVS D0, D1"
    });
    Then({
        "SR is S,0,V",
        "PC is 0x1002",
        "CYCLES is 150",
        "D0 is 0x00008000",
        "D1 is 0x40008000",
    });
}

TEST_F(DIVSTestWord, LateOverflowNegativeDividendNegativeDivisor) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D0 is 0x00008000",
        "D1 is 0x80000001",
    });
    When({
        "DIVS D0, D1"
    });
    Then({
        "SR is S,0,V",
        "PC is 0x1002",
        "CYCLES is 124",
        "D0 is 0x00008000",
        "D1 is 0x80000001",
    });
}


TEST_F(DIVSTestWord, DataRegisterFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00001FFF",
        "D2 is 0x00000FFF",
    });
    When({
        "DIVS D1, D2"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 150",
        "D1 is 0x00001FFF",
        "D2 is 0x0FFF0000",
    });
}

TEST_F(DIVSTestWord, DataRegisterDivisionIsSigned) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0000FFFE",
        "D2 is 0x00000009",
    });
    When({
        "DIVS D1, D2"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 150",
        "D1 is 0x0000FFFE",
        "D2 is 0x0001FFFC",
    });
}

TEST_F(DIVSTestWord, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0011A55A",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x8607",
    });
    When({
        "DIVS (A1), D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 152",
        "D1 is 0x045DFFDB",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x8607",
    });
}

TEST_F(DIVSTestWord, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0011A55A",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x8607",
    });
    When({
        "DIVS (A1)+, D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 152",
        "D1 is 0x045DFFDB",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x8607",
    });
}

TEST_F(DIVSTestWord, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0011A55A",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x8607",
    });
    When({
        "DIVS -(A1), D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 154",
        "D1 is 0x045DFFDB",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x8607",
    });
}

TEST_F(DIVSTestWord, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0011A55A",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x8607",
    });
    When({
        "DIVS (2, A1), D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 156",
        "D1 is 0x045DFFDB",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x8607",
    });
}

TEST_F(DIVSTestWord, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0011A55A",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x8607",
    });
    When({
        "DIVS (2, A1, A2.L), D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 158",
        "D1 is 0x045DFFDB",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x8607",
    });
}

TEST_F(DIVSTestWord, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0011A55A",
        "(0x00004000).W is 0x8607",
    });
    When({
        "DIVS (0x4000).W, D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 156",
        "D1 is 0x045DFFDB",
        "(0x00004000).W is 0x8607",
    });
}

TEST_F(DIVSTestWord, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0011A55A",
        "(0x00008000).W is 0x8607",
    });
    When({
        "DIVS (0x8000).L, D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1006",
        "CYCLES is 160",
        "D1 is 0x045DFFDB",
        "(0x00008000).W is 0x8607",
    });
}

TEST_F(DIVSTestWord, PCDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0011A55A",
        "(0x00001060).W is 0x8607",
    });
    When({
        "DIVS (0x5E, PC), D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 156",
        "D1 is 0x045DFFDB",
        "(0x00001060).W is 0x8607",
    });
}

TEST_F(DIVSTestWord, PCIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0011A55A",
        "A1 is 0x00000010",
        "(0x00001070).W is 0x8607",
    });
    When({
        "DIVS (0x5E, PC, A1.L), D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 158",
        "D1 is 0x045DFFDB",
        "A1 is 0x00000010",
        "(0x00001070).W is 0x8607",
    });
}

TEST_F(DIVSTestWord, ImmediateWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0011A55A",
    });
    When({
        "DIVS #0x8607, D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 152",
        "D1 is 0x045DFFDB",
    });
}

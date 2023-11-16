#include "M68000/Fixtures/M68000Test.h"

class ANDTestWord : public M68000Test {};

TEST_F(ANDTestWord, DataRegisterDataRegisterWorks) {
    Given({
        "D1 is 0x0303050A",
        "D2 is 0xFFFFFFFD",
        "SR is S,0,0"
    });
    When({
        "AND.W D1, D2"
    });
    Then({
        "D1 is 0x0303050A",
        "D2 is 0xFFFF0508",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestWord, DataRegisterDataRegisterFlagNWorks) {
    Given({
        "D1 is 0x01018001",
        "D2 is 0x11118000",
        "SR is S,0,0"
    });
    When({
        "AND.W D1, D2"
    });
    Then({
        "D1 is 0x01018001",
        "D2 is 0x11118000",
        "SR is S,0,N"
    });
}

TEST_F(ANDTestWord, DataRegisterDataRegisterFlagZWorks) {
    Given({
        "D1 is 0x0303AAAA",
        "D2 is 0xFFFF5555",
        "SR is S,0,0"
    });
    When({
        "AND.W D1, D2"
    });
    Then({
        "D1 is 0x0303AAAA",
        "D2 is 0xFFFF0000",
        "SR is S,0,Z"
    });
}

TEST_F(ANDTestWord, DataRegisterDataRegisterFlagXWorks) {
    Given({
        "D1 is 0x010101F1",
        "D2 is 0x111111F3",
        "SR is S,0,X"
    });
    When({
        "AND.W D1, D2"
    });
    Then({
        "D1 is 0x010101F1",
        "D2 is 0x111101F1",
        "SR is S,0,X"
    });
}

TEST_F(ANDTestWord, DataRegisterDataRegisterFlagVCWorks) {
    Given({
        "D1 is 0x010101F1",
        "D2 is 0x111111F3",
        "SR is S,0,VC"
    });
    When({
        "AND.W D1, D2"
    });
    Then({
        "D1 is 0x010101F1",
        "D2 is 0x111101F1",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestWord, AddressIndirectDataRegisterWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "AND.W (A1), D1"
    });
    Then({
        "D1 is 0x11110205",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5AA5",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestWord, AddressIncrementDataRegisterWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "AND.W (A1)+, D1"
    });
    Then({
        "D1 is 0x11110205",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x5AA5",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestWord, AddressDecrementDataRegisterWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "AND.W -(A1), D1"
    });
    Then({
        "D1 is 0x11110205",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5AA5",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestWord, AddressDisplacementDataRegisterWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "AND.W (2, A1), D1"
    });
    Then({
        "D1 is 0x11110205",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x5AA5",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestWord, AddressIndexDataRegisterWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "AND.W (2, A1, A2.L), D1"
    });
    Then({
        "D1 is 0x11110205",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x5AA5",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestWord, ShortDataRegisterWorks) {
    Given({
        "D1 is 0x11110607",
        "(0x00004000).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "AND.W (0x4000).W, D1"
    });
    Then({
        "D1 is 0x11110205",
        "(0x00004000).W is 0x5AA5",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestWord, LongDataRegisterWorks) {
    Given({
        "D1 is 0x11110607",
        "(0x00008000).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "AND.W (0x8000).L, D1"
    });
    Then({
        "D1 is 0x11110205",
        "(0x00008000).W is 0x5AA5",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestWord, PCDisplacementDataRegisterWorks) {
    Given({
        "D1 is 0x11110607",
        "(0x00001060).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "AND.W (0x5E, PC), D1"
    });
    Then({
        "D1 is 0x11110205",
        "(0x00001060).W is 0x5AA5",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestWord, PCIndexDataRegisterWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00000010",
        "(0x00001070).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "AND.W (0x5E, PC, A1.L), D1"
    });
    Then({
        "D1 is 0x11110205",
        "A1 is 0x00000010",
        "(0x00001070).W is 0x5AA5",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestWord, ImmediateDataRegisterWorks) {
    Given({
        "D1 is 0x11110607",
        "SR is S,0,0"
    });
    When({
        "AND.W #0x5AA5, D1"
    });
    Then({
        "D1 is 0x11110205",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestWord, DataRegisterAddressIndirectWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "AND.W D1, (A1)"
    });
    Then({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0205",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestWord, DataRegisterAddressIncrementWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "AND.W D1, (A1)+"
    });
    Then({
        "D1 is 0x11110607",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x0205",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestWord, DataRegisterAddressDecrementWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "AND.W D1, -(A1)"
    });
    Then({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0205",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestWord, DataRegisterAddressIndexWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "AND.W D1, (2, A1)"
    });
    Then({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x0205",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestWord, DataRegisterAddressDisplacementWorks) {
    Given({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "AND.W D1, (2, A1, A2.L)"
    });
    Then({
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x0205",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestWord, DataRegisterShortWorks) {
    Given({
        "D1 is 0x11110607",
        "(0x00004000).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "AND.W D1, (0x4000).W"
    });
    Then({
        "D1 is 0x11110607",
        "(0x00004000).W is 0x0205",
        "SR is S,0,0"
    });
}

TEST_F(ANDTestWord, DataRegisterLongWorks) {
    Given({
        "D1 is 0x11110607",
        "(0x00008000).W is 0x5AA5",
        "SR is S,0,0"
    });
    When({
        "AND.W D1, (0x8000).L"
    });
    Then({
        "D1 is 0x11110607",
        "(0x00008000).W is 0x0205",
        "SR is S,0,0"
    });
}
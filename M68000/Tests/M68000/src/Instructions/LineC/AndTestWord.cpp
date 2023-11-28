#include "M68000/Fixtures/M68000Test.h"

class ANDTestWord : public M68000Test {};

TEST_F(ANDTestWord, DataRegisterDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0303050A",
        "D2 is 0xFFFFFFFD",
    });
    When({
        "AND.W D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x0303050A",
        "D2 is 0xFFFF0508",
    });
}

TEST_F(ANDTestWord, DataRegisterDataRegisterFlagNWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01018001",
        "D2 is 0x11118000",
    });
    When({
        "AND.W D1, D2"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01018001",
        "D2 is 0x11118000",
    });
}

TEST_F(ANDTestWord, DataRegisterDataRegisterFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0303AAAA",
        "D2 is 0xFFFF5555",
    });
    When({
        "AND.W D1, D2"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x0303AAAA",
        "D2 is 0xFFFF0000",
    });
}

TEST_F(ANDTestWord, DataRegisterDataRegisterFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0x010101F1",
        "D2 is 0x111111F3",
    });
    When({
        "AND.W D1, D2"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x010101F1",
        "D2 is 0x111101F1",
    });
}

TEST_F(ANDTestWord, DataRegisterDataRegisterFlagVCWorks) {
    Given({
        "SR is S,0,VC",
        "PC is 0x1000",
        "D1 is 0x010101F1",
        "D2 is 0x111111F3",
    });
    When({
        "AND.W D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x010101F1",
        "D2 is 0x111101F1",
    });
}

TEST_F(ANDTestWord, AddressIndirectDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5AA5",
    });
    When({
        "AND.W (A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x11110205",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5AA5",
    });
}

TEST_F(ANDTestWord, AddressIncrementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5AA5",
    });
    When({
        "AND.W (A1)+, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x11110205",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x5AA5",
    });
}

TEST_F(ANDTestWord, AddressDecrementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x5AA5",
    });
    When({
        "AND.W -(A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0x11110205",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5AA5",
    });
}

TEST_F(ANDTestWord, AddressDisplacementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x5AA5",
    });
    When({
        "AND.W (2, A1), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x11110205",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x5AA5",
    });
}

TEST_F(ANDTestWord, AddressIndexDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x5AA5",
    });
    When({
        "AND.W (2, A1, A2.L), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0x11110205",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x5AA5",
    });
}

TEST_F(ANDTestWord, ShortDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "(0x00004000).W is 0x5AA5",
    });
    When({
        "AND.W (0x4000).W, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x11110205",
        "(0x00004000).W is 0x5AA5",
    });
}

TEST_F(ANDTestWord, LongDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "(0x00008000).W is 0x5AA5",
    });
    When({
        "AND.W (0x8000).L, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 16",
        "D1 is 0x11110205",
        "(0x00008000).W is 0x5AA5",
    });
}

TEST_F(ANDTestWord, PCDisplacementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "(0x00001060).W is 0x5AA5",
    });
    When({
        "AND.W (0x5E, PC), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x11110205",
        "(0x00001060).W is 0x5AA5",
    });
}

TEST_F(ANDTestWord, PCIndexDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00000010",
        "(0x00001070).W is 0x5AA5",
    });
    When({
        "AND.W (0x5E, PC, A1.L), D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0x11110205",
        "A1 is 0x00000010",
        "(0x00001070).W is 0x5AA5",
    });
}

TEST_F(ANDTestWord, ImmediateDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
    });
    When({
        "AND.W #0x5AA5, D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 8",
        "D1 is 0x11110205",
    });
}

TEST_F(ANDTestWord, DataRegisterAddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5AA5",
    });
    When({
        "AND.W D1, (A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0205",
    });
}

TEST_F(ANDTestWord, DataRegisterAddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x5AA5",
    });
    When({
        "AND.W D1, (A1)+"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x11110607",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x0205",
    });
}

TEST_F(ANDTestWord, DataRegisterAddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x5AA5",
    });
    When({
        "AND.W D1, -(A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0205",
    });
}

TEST_F(ANDTestWord, DataRegisterAddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x5AA5",
    });
    When({
        "AND.W D1, (2, A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x0205",
    });
}

TEST_F(ANDTestWord, DataRegisterAddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x5AA5",
    });
    When({
        "AND.W D1, (2, A1, A2.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "D1 is 0x11110607",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x0205",
    });
}

TEST_F(ANDTestWord, DataRegisterShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "(0x00004000).W is 0x5AA5",
    });
    When({
        "AND.W D1, (0x4000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "D1 is 0x11110607",
        "(0x00004000).W is 0x0205",
    });
}

TEST_F(ANDTestWord, DataRegisterLongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x11110607",
        "(0x00008000).W is 0x5AA5",
    });
    When({
        "AND.W D1, (0x8000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 20",
        "D1 is 0x11110607",
        "(0x00008000).W is 0x0205",
    });
}

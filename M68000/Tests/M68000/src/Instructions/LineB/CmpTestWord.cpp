#include "M68000/Fixtures/M68000Test.h"

class CMPTestWord : public M68000Test {};

TEST_F(CMPTestWord, DataRegisterDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01012000",
        "D2 is 0x71A1E300",
    });
    When({
        "CMP.W D1, D2"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01012000",
        "D2 is 0x71A1E300",
    });
}

TEST_F(CMPTestWord, DataRegisterDataRegisterFlagNVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01018001",
        "D2 is 0x01013201",
    });
    When({
        "CMP.W D1, D2"
    });
    Then({
        "SR is S,0,NVC",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01018001",
        "D2 is 0x01013201",
    });
}

TEST_F(CMPTestWord, DataRegisterDataRegisterFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01013201",
        "D2 is 0x01A13201",
    });
    When({
        "CMP.W D1, D2"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01013201",
        "D2 is 0x01A13201",
    });
}

TEST_F(CMPTestWord, DataRegisterDataRegisterFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0x01A18001",
        "D2 is 0x01019001",
    });
    When({
        "CMP.W D1, D2"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01A18001",
        "D2 is 0x01019001",
    });
}

TEST_F(CMPTestWord, AddressRegisterDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D2 is 0x01A10107",
        "A2 is 0x01010603",
    });
    When({
        "CMP.W A2, D2"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1002",
        "CYCLES is 4",
        "D2 is 0x01A10107",
        "A2 is 0x01010603",
    });
}


TEST_F(CMPTestWord, AddressIndirectDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01A10107",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0603",
    });
    When({
        "CMP.W (A1), D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x01A10107",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0603",
    });
}

TEST_F(CMPTestWord, AddressIncrementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01A10107",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0603",
    });
    When({
        "CMP.W (A1)+, D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x01A10107",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x0603",
    });
}

TEST_F(CMPTestWord, AddressDecrementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01A10107",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x0603",
    });
    When({
        "CMP.W -(A1), D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0x01A10107",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0603",
    });
}

TEST_F(CMPTestWord, AddressDisplacementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01A10107",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x0603",
    });
    When({
        "CMP.W (2, A1), D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x01A10107",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x0603",
    });
}

TEST_F(CMPTestWord, AddressIndexDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01A10107",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x0603",
    });
    When({
        "CMP.W (2, A1, A2.L), D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0x01A10107",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x0603",
    });
}

TEST_F(CMPTestWord, ShortDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01A10107",
        "(0x00004000).W is 0x0603",
    });
    When({
        "CMP.W (0x4000).W, D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x01A10107",
        "(0x00004000).W is 0x0603",
    });
}

TEST_F(CMPTestWord, LongDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01A10107",
        "(0x00008000).W is 0x0603",
    });
    When({
        "CMP.W (0x8000).L, D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1006",
        "CYCLES is 16",
        "D1 is 0x01A10107",
        "(0x00008000).W is 0x0603",
    });
}

TEST_F(CMPTestWord, PCDisplacementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01A10107",
        "(0x00001060).W is 0x0603",
    });
    When({
        "CMP.W (0x5E, PC), D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x01A10107",
        "(0x00001060).W is 0x0603",
    });
}

TEST_F(CMPTestWord, PCIndexDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01A10107",
        "A1 is 0x00000010",
        "(0x00001070).W is 0x0603",
    });
    When({
        "CMP.W (0x5E, PC, A1.L), D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0x01A10107",
        "A1 is 0x00000010",
        "(0x00001070).W is 0x0603",
    });
}

TEST_F(CMPTestWord, ImmediateDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01A10107",
    });
    When({
        "CMP.W #0x0603, D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1004",
        "CYCLES is 8",
        "D1 is 0x01A10107",
    });
}

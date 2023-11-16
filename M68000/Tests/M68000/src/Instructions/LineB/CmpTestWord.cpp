#include "M68000/Fixtures/M68000Test.h"

class CMPTestWord : public M68000Test {};

TEST_F(CMPTestWord, DataRegisterDataRegisterWorks) {
    Given({
        "D1 is 0x01012000",
        "D2 is 0x71A1E300",
        "SR is S,0,0"
    });
    When({
        "CMP.W D1, D2"
    });
    Then({
        "D1 is 0x01012000",
        "D2 is 0x71A1E300",
        "SR is S,0,N"
    });
}

TEST_F(CMPTestWord, DataRegisterDataRegisterFlagNVWorks) {
    Given({
        "D1 is 0x01018001",
        "D2 is 0x01013201",
        "SR is S,0,0"
    });
    When({
        "CMP.W D1, D2"
    });
    Then({
        "D1 is 0x01018001",
        "D2 is 0x01013201",
        "SR is S,0,NVC"
    });
}

TEST_F(CMPTestWord, DataRegisterDataRegisterFlagZWorks) {
    Given({
        "D1 is 0x01013201",
        "D2 is 0x01A13201",
        "SR is S,0,0"
    });
    When({
        "CMP.W D1, D2"
    });
    Then({
        "D1 is 0x01013201",
        "D2 is 0x01A13201",
        "SR is S,0,Z"
    });
}

TEST_F(CMPTestWord, DataRegisterDataRegisterFlagXWorks) {
    Given({
        "D1 is 0x01A18001",
        "D2 is 0x01019001",
        "SR is S,0,X"
    });
    When({
        "CMP.W D1, D2"
    });
    Then({
        "D1 is 0x01A18001",
        "D2 is 0x01019001",
        "SR is S,0,X"
    });
}

TEST_F(CMPTestWord, AddressRegisterDataRegisterWorks) {
    Given({
        "A2 is 0x01010603",
        "D2 is 0x01A10107",
        "SR is S,0,0"
    });
    When({
        "CMP.W A2, D2"
    });
    Then({
        "A2 is 0x01010603",
        "D2 is 0x01A10107",
        "SR is S,0,NC"
    });
}


TEST_F(CMPTestWord, AddressIndirectDataRegisterWorks) {
    Given({
        "D1 is 0x01A10107",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0603",
        "SR is S,0,0"
    });
    When({
        "CMP.W (A1), D1"
    });
    Then({
        "D1 is 0x01A10107",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0603",
        "SR is S,0,NC"
    });
}

TEST_F(CMPTestWord, AddressIncrementDataRegisterWorks) {
    Given({
        "D1 is 0x01A10107",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0603",
        "SR is S,0,0"
    });
    When({
        "CMP.W (A1)+, D1"
    });
    Then({
        "D1 is 0x01A10107",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x0603",
        "SR is S,0,NC"
    });
}

TEST_F(CMPTestWord, AddressDecrementDataRegisterWorks) {
    Given({
        "D1 is 0x01A10107",
        "A1 is 0x00008002",
        "(0x00008000).W is 0x0603",
        "SR is S,0,0"
    });
    When({
        "CMP.W -(A1), D1"
    });
    Then({
        "D1 is 0x01A10107",
        "A1 is 0x00008000",
        "(0x00008000).W is 0x0603",
        "SR is S,0,NC"
    });
}

TEST_F(CMPTestWord, AddressDisplacementDataRegisterWorks) {
    Given({
        "D1 is 0x01A10107",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x0603",
        "SR is S,0,0"
    });
    When({
        "CMP.W (2, A1), D1"
    });
    Then({
        "D1 is 0x01A10107",
        "A1 is 0x00008000",
        "(0x00008002).W is 0x0603",
        "SR is S,0,NC"
    });
}

TEST_F(CMPTestWord, AddressIndexDataRegisterWorks) {
    Given({
        "D1 is 0x01A10107",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x0603",
        "SR is S,0,0"
    });
    When({
        "CMP.W (2, A1, A2.L), D1"
    });
    Then({
        "D1 is 0x01A10107",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).W is 0x0603",
        "SR is S,0,NC"
    });
}

TEST_F(CMPTestWord, ShortDataRegisterWorks) {
    Given({
        "D1 is 0x01A10107",
        "(0x00004000).W is 0x0603",
        "SR is S,0,0"
    });
    When({
        "CMP.W (0x4000).W, D1"
    });
    Then({
        "D1 is 0x01A10107",
        "(0x00004000).W is 0x0603",
        "SR is S,0,NC"
    });
}

TEST_F(CMPTestWord, LongDataRegisterWorks) {
    Given({
        "D1 is 0x01A10107",
        "(0x00008000).W is 0x0603",
        "SR is S,0,0"
    });
    When({
        "CMP.W (0x8000).L, D1"
    });
    Then({
        "D1 is 0x01A10107",
        "(0x00008000).W is 0x0603",
        "SR is S,0,NC"
    });
}

TEST_F(CMPTestWord, PCDisplacementDataRegisterWorks) {
    Given({
        "D1 is 0x01A10107",
        "(0x00001060).W is 0x0603",
        "SR is S,0,0"
    });
    When({
        "CMP.W (0x5E, PC), D1"
    });
    Then({
        "D1 is 0x01A10107",
        "(0x00001060).W is 0x0603",
        "SR is S,0,NC"
    });
}

TEST_F(CMPTestWord, PCIndexDataRegisterWorks) {
    Given({
        "D1 is 0x01A10107",
        "A1 is 0x00000010",
        "(0x00001070).W is 0x0603",
        "SR is S,0,0"
    });
    When({
        "CMP.W (0x5E, PC, A1.L), D1"
    });
    Then({
        "D1 is 0x01A10107",
        "A1 is 0x00000010",
        "(0x00001070).W is 0x0603",
        "SR is S,0,NC"
    });
}

TEST_F(CMPTestWord, ImmediateDataRegisterWorks) {
    Given({
        "D1 is 0x01A10107",
        "SR is S,0,0"
    });
    When({
        "CMP.W #0x0603, D1"
    });
    Then({
        "D1 is 0x01A10107",
        "SR is S,0,NC"
    });
}
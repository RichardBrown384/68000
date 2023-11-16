#include "M68000/Fixtures/M68000Test.h"

class CMPATestLong : public M68000Test {};

TEST_F(CMPATestLong, DataRegisterWorks) {
    Given({
        "D1 is 0x08010101",
        "A2 is 0x0708090A",
        "SR is S,0,0"
    });
    When({
        "CMPA.L D1, A2"
    });
    Then({
        "D1 is 0x08010101",
        "A2 is 0x0708090A",
        "SR is S,0,NC"
    });
}

TEST_F(CMPATestLong, DataRegisterFlagNVWorks) {
    Given({
        "D1 is 0xFFFFFFFF",
        "A2 is 0x7FFFFFFF",
        "SR is S,0,0"
    });
    When({
        "CMPA.L D1, A2"
    });
    Then({
        "D1 is 0xFFFFFFFF",
        "A2 is 0x7FFFFFFF",
        "SR is S,0,NVC"
    });
}

TEST_F(CMPATestLong, DataRegisterFlagZWorks) {
    Given({
        "D1 is 0x7F00FFF0",
        "A2 is 0x7F00FFF0",
        "SR is S,0,0"
    });
    When({
        "CMPA.L D1, A2"
    });
    Then({
        "D1 is 0x7F00FFF0",
        "A2 is 0x7F00FFF0",
        "SR is S,0,Z"
    });
}

TEST_F(CMPATestLong, DataRegisterFlagXWorks) {
    Given({
        "D1 is 0x7F00FFF0",
        "A2 is 0x7F00FFF1",
        "SR is S,0,X"
    });
    When({
        "CMPA.L D1, A2"
    });
    Then({
        "D1 is 0x7F00FFF0",
        "A2 is 0x7F00FFF1",
        "SR is S,0,X"
    });
}

TEST_F(CMPATestLong, AddressRegisterWorks) {
    Given({
        "A1 is 0x07060604",
        "A2 is 0x05080907",
        "SR is S,0,0"
    });
    When({
        "CMPA.L A1, A2"
    });
    Then({
        "A1 is 0x07060604",
        "A2 is 0x05080907",
        "SR is S,0,NC"
    });
}

TEST_F(CMPATestLong, AddressIndirectWorks) {
    Given({
        "A1 is 0x00008000",
        "A2 is 0x05080907",
        "(0x00008000).L is 0x07060604",
        "SR is S,0,0"
    });
    When({
        "CMPA.L (A1), A2"
    });
    Then({
        "A1 is 0x00008000",
        "A2 is 0x05080907",
        "(0x00008000).L is 0x07060604",
        "SR is S,0,NC"
    });
}

TEST_F(CMPATestLong, AddressIncrementWorks) {
    Given({
        "A1 is 0x00008000",
        "A2 is 0x05080907",
        "(0x00008000).L is 0x07060604",
        "SR is S,0,0"
    });
    When({
        "CMPA.L (A1)+, A2"
    });
    Then({
        "A1 is 0x00008004",
        "A2 is 0x05080907",
        "(0x00008000).L is 0x07060604",
        "SR is S,0,NC"
    });
}

TEST_F(CMPATestLong, AddressDecrementWorks) {
    Given({
        "A1 is 0x00008004",
        "A2 is 0x05080907",
        "(0x00008000).L is 0x07060604",
        "SR is S,0,0"
    });
    When({
        "CMPA.L -(A1), A2"
    });
    Then({
        "A1 is 0x00008000",
        "A2 is 0x05080907",
        "(0x00008000).L is 0x07060604",
        "SR is S,0,NC"
    });
}

TEST_F(CMPATestLong, AddressDisplacementWorks) {
    Given({
        "A1 is 0x00008000",
        "A2 is 0x05080907",
        "(0x00008002).L is 0x07060604",
        "SR is S,0,0"
    });
    When({
        "CMPA.L (2, A1), A2"
    });
    Then({
        "A1 is 0x00008000",
        "A2 is 0x05080907",
        "(0x00008002).L is 0x07060604",
        "SR is S,0,NC"
    });
}

TEST_F(CMPATestLong, AddressIndexWorks) {
    Given({
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "A3 is 0x05080907",
        "(0x00008012).L is 0x07060604",
        "SR is S,0,0"
    });
    When({
        "CMPA.L (2, A1, A2.L), A3"
    });
    Then({
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "A3 is 0x05080907",
        "(0x00008012).L is 0x07060604",
        "SR is S,0,NC"
    });
}

TEST_F(CMPATestLong, ShortWorks) {
    Given({
        "A1 is 0x05080907",
        "(0x00004000).L is 0x07060604",
        "SR is S,0,0"
    });
    When({
        "CMPA.L (0x4000).W, A1"
    });
    Then({
        "A1 is 0x05080907",
        "(0x00004000).L is 0x07060604",
        "SR is S,0,NC"
    });
}

TEST_F(CMPATestLong, LongWorks) {
    Given({
        "A1 is 0x05080907",
        "(0x00008000).L is 0x07060604",
        "SR is S,0,0"
    });
    When({
        "CMPA.L (0x8000).L, A1"
    });
    Then({
        "A1 is 0x05080907",
        "(0x00008000).L is 0x07060604",
        "SR is S,0,NC"
    });
}

TEST_F(CMPATestLong, PCDisplacementWorks) {
    Given({
        "A1 is 0x05080907",
        "(0x00001060).L is 0x07060604",
        "SR is S,0,0"
    });
    When({
        "CMPA.L (0x5E, PC), A1"
    });
    Then({
        "A1 is 0x05080907",
        "(0x00001060).L is 0x07060604",
        "SR is S,0,NC"
    });
}

TEST_F(CMPATestLong, PCIndexWorks) {
    Given({
        "A1 is 0x00000010",
        "A2 is 0x05080907",
        "(0x00001070).L is 0x07060604",
        "SR is S,0,0"
    });
    When({
        "CMPA.L (0x5E, PC, A1.L), A2"
    });
    Then({
        "A1 is 0x00000010",
        "A2 is 0x05080907",
        "(0x00001070).L is 0x07060604",
        "SR is S,0,NC"
    });
}

TEST_F(CMPATestLong, ImmediateWorks) {
    Given({
        "A1 is 0x05080907",
        "SR is S,0,0"
    });
    When({
        "CMPA.L #0x07060604, A1"
    });
    Then({
        "A1 is 0x05080907",
        "SR is S,0,NC"
    });
}
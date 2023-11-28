#include "M68000/Fixtures/M68000Test.h"

class CMPATestLong : public M68000Test {};

TEST_F(CMPATestLong, DataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x08010101",
        "A2 is 0x0708090A",
    });
    When({
        "CMPA.L D1, A2"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x08010101",
        "A2 is 0x0708090A",
    });
}

TEST_F(CMPATestLong, DataRegisterFlagNVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xFFFFFFFF",
        "A2 is 0x7FFFFFFF",
    });
    When({
        "CMPA.L D1, A2"
    });
    Then({
        "SR is S,0,NVC",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0xFFFFFFFF",
        "A2 is 0x7FFFFFFF",
    });
}

TEST_F(CMPATestLong, DataRegisterFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x7F00FFF0",
        "A2 is 0x7F00FFF0",
    });
    When({
        "CMPA.L D1, A2"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x7F00FFF0",
        "A2 is 0x7F00FFF0",
    });
}

TEST_F(CMPATestLong, DataRegisterFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0x7F00FFF0",
        "A2 is 0x7F00FFF1",
    });
    When({
        "CMPA.L D1, A2"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x7F00FFF0",
        "A2 is 0x7F00FFF1",
    });
}

TEST_F(CMPATestLong, AddressRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x07060604",
        "A2 is 0x05080907",
    });
    When({
        "CMPA.L A1, A2"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1002",
        "CYCLES is 6",
        "A1 is 0x07060604",
        "A2 is 0x05080907",
    });
}

TEST_F(CMPATestLong, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00008000",
        "A2 is 0x05080907",
        "(0x00008000).L is 0x07060604",
    });
    When({
        "CMPA.L (A1), A2"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1002",
        "CYCLES is 14",
        "A1 is 0x00008000",
        "A2 is 0x05080907",
        "(0x00008000).L is 0x07060604",
    });
}

TEST_F(CMPATestLong, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00008000",
        "A2 is 0x05080907",
        "(0x00008000).L is 0x07060604",
    });
    When({
        "CMPA.L (A1)+, A2"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1002",
        "CYCLES is 14",
        "A1 is 0x00008004",
        "A2 is 0x05080907",
        "(0x00008000).L is 0x07060604",
    });
}

TEST_F(CMPATestLong, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00008004",
        "A2 is 0x05080907",
        "(0x00008000).L is 0x07060604",
    });
    When({
        "CMPA.L -(A1), A2"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1002",
        "CYCLES is 16",
        "A1 is 0x00008000",
        "A2 is 0x05080907",
        "(0x00008000).L is 0x07060604",
    });
}

TEST_F(CMPATestLong, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00008000",
        "A2 is 0x05080907",
        "(0x00008002).L is 0x07060604",
    });
    When({
        "CMPA.L (2, A1), A2"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1004",
        "CYCLES is 18",
        "A1 is 0x00008000",
        "A2 is 0x05080907",
        "(0x00008002).L is 0x07060604",
    });
}

TEST_F(CMPATestLong, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "A3 is 0x05080907",
        "(0x00008012).L is 0x07060604",
    });
    When({
        "CMPA.L (2, A1, A2.L), A3"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1004",
        "CYCLES is 20",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "A3 is 0x05080907",
        "(0x00008012).L is 0x07060604",
    });
}

TEST_F(CMPATestLong, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x05080907",
        "(0x00004000).L is 0x07060604",
    });
    When({
        "CMPA.L (0x4000).W, A1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1004",
        "CYCLES is 18",
        "A1 is 0x05080907",
        "(0x00004000).L is 0x07060604",
    });
}

TEST_F(CMPATestLong, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x05080907",
        "(0x00008000).L is 0x07060604",
    });
    When({
        "CMPA.L (0x8000).L, A1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1006",
        "CYCLES is 22",
        "A1 is 0x05080907",
        "(0x00008000).L is 0x07060604",
    });
}

TEST_F(CMPATestLong, PCDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x05080907",
        "(0x00001060).L is 0x07060604",
    });
    When({
        "CMPA.L (0x5E, PC), A1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1004",
        "CYCLES is 18",
        "A1 is 0x05080907",
        "(0x00001060).L is 0x07060604",
    });
}

TEST_F(CMPATestLong, PCIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00000010",
        "A2 is 0x05080907",
        "(0x00001070).L is 0x07060604",
    });
    When({
        "CMPA.L (0x5E, PC, A1.L), A2"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1004",
        "CYCLES is 20",
        "A1 is 0x00000010",
        "A2 is 0x05080907",
        "(0x00001070).L is 0x07060604",
    });
}

TEST_F(CMPATestLong, ImmediateWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x05080907",
    });
    When({
        "CMPA.L #0x07060604, A1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1006",
        "CYCLES is 14",
        "A1 is 0x05080907",
    });
}

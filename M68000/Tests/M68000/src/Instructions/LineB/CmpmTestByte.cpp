#include "M68000/Fixtures/M68000Test.h"

class CMPMTestByte : public M68000Test {};

TEST_F(CMPMTestByte, DifferentRegistersWork) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).B is 0x44",
        "(0x4000).B is 0x33",
    });
    When({
        "CMPM.B (A1)+, (A2)+"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1002",
        "CYCLES is 12",
        "A1 is 0x3001",
        "A2 is 0x4001",
        "(0x3000).B is 0x44",
        "(0x4000).B is 0x33",
    });
}

TEST_F(CMPMTestByte, DifferentRegistersFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).B is 0x44",
        "(0x4000).B is 0x44",
    });
    When({
        "CMPM.B (A1)+, (A2)+"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 12",
        "A1 is 0x3001",
        "A2 is 0x4001",
        "(0x3000).B is 0x44",
        "(0x4000).B is 0x44",
    });
}

TEST_F(CMPMTestByte, DifferentRegistersFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).B is 0x44",
        "(0x4000).B is 0x55",
    });
    When({
        "CMPM.B (A1)+, (A2)+"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 12",
        "A1 is 0x3001",
        "A2 is 0x4001",
        "(0x3000).B is 0x44",
        "(0x4000).B is 0x55",
    });
}

TEST_F(CMPMTestByte, SameRegistersWork) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x3000",
        "(0x3000).B is 0x44",
        "(0x3001).B is 0x33",
    });
    When({
        "CMPM.B (A1)+, (A1)+"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1002",
        "CYCLES is 12",
        "A1 is 0x3002",
        "(0x3000).B is 0x44",
        "(0x3001).B is 0x33",
    });
}

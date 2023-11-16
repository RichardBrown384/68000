#include "M68000/Fixtures/M68000Test.h"

class CMPMTestByte : public M68000Test {};

TEST_F(CMPMTestByte, DifferentRegistersWork) {
    Given({
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).B is 0x44",
        "(0x4000).B is 0x33",
        "SR is S,0,0"
    });
    When({
        "CMPM.B (A1)+, (A2)+"
    });
    Then({
        "A1 is 0x3001",
        "A2 is 0x4001",
        "(0x3000).B is 0x44",
        "(0x4000).B is 0x33",
        "SR is S,0,NC"
    });
}

TEST_F(CMPMTestByte, DifferentRegistersFlagZWorks) {
    Given({
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).B is 0x44",
        "(0x4000).B is 0x44",
        "SR is S,0,0"
    });
    When({
        "CMPM.B (A1)+, (A2)+"
    });
    Then({
        "A1 is 0x3001",
        "A2 is 0x4001",
        "(0x3000).B is 0x44",
        "(0x4000).B is 0x44",
        "SR is S,0,Z"
    });
}

TEST_F(CMPMTestByte, DifferentRegistersFlagXWorks) {
    Given({
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).B is 0x44",
        "(0x4000).B is 0x55",
        "SR is S,0,X"
    });
    When({
        "CMPM.B (A1)+, (A2)+"
    });
    Then({
        "A1 is 0x3001",
        "A2 is 0x4001",
        "(0x3000).B is 0x44",
        "(0x4000).B is 0x55",
        "SR is S,0,X"
    });
}

TEST_F(CMPMTestByte, SameRegistersWork) {
    Given({
        "A1 is 0x3000",
        "(0x3000).B is 0x44",
        "(0x3001).B is 0x33",
        "SR is S,0,0"
    });
    When({
        "CMPM.B (A1)+, (A1)+"
    });
    Then({
        "A1 is 0x3002",
        "(0x3000).B is 0x44",
        "(0x3001).B is 0x33",
        "SR is S,0,NC"
    });
}

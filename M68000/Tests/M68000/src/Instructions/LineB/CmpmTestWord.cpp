#include "M68000/Fixtures/M68000Test.h"

class CMPMTestWord : public M68000Test {};

TEST_F(CMPMTestWord, DifferentRegistersWork) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).W is 0x4455",
        "(0x4000).W is 0x8633",
    });
    When({
        "CMPM.W (A1)+, (A2)+"
    });
    Then({
        "SR is S,0,V",
        "PC is 0x1002",
        "CYCLES is 12",
        "A1 is 0x3002",
        "A2 is 0x4002",
        "(0x3000).W is 0x4455",
        "(0x4000).W is 0x8633",
    });
}

TEST_F(CMPMTestWord, DifferentRegistersFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).W is 0x4455",
        "(0x4000).W is 0x4455",
    });
    When({
        "CMPM.W (A1)+, (A2)+"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 12",
        "A1 is 0x3002",
        "A2 is 0x4002",
        "(0x3000).W is 0x4455",
        "(0x4000).W is 0x4455",
    });
}

TEST_F(CMPMTestWord, DifferentRegistersFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).W is 0x4455",
        "(0x4000).W is 0x5544",
    });
    When({
        "CMPM.W (A1)+, (A2)+"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 12",
        "A1 is 0x3002",
        "A2 is 0x4002",
        "(0x3000).W is 0x4455",
        "(0x4000).W is 0x5544",
    });
}

TEST_F(CMPMTestWord, SameRegistersWork) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x3000",
        "(0x3000).W is 0x4455",
        "(0x3002).W is 0x8633",
    });
    When({
        "CMPM.W (A1)+, (A1)+"
    });
    Then({
        "SR is S,0,V",
        "PC is 0x1002",
        "CYCLES is 12",
        "A1 is 0x3004",
        "(0x3000).W is 0x4455",
        "(0x3002).W is 0x8633",
    });
}

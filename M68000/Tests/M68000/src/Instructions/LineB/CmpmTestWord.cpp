#include "M68000/Fixtures/M68000Test.h"

class CMPMTestWord : public M68000Test {};

TEST_F(CMPMTestWord, DifferentRegistersWork) {
    Given({
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).W is 0x4455",
        "(0x4000).W is 0x8633",
        "SR is S,0,0"
    });
    When({
        "CMPM.W (A1)+, (A2)+"
    });
    Then({
        "A1 is 0x3002",
        "A2 is 0x4002",
        "(0x3000).W is 0x4455",
        "(0x4000).W is 0x8633",
        "SR is S,0,V"
    });
}

TEST_F(CMPMTestWord, DifferentRegistersFlagZWorks) {
    Given({
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).W is 0x4455",
        "(0x4000).W is 0x4455",
        "SR is S,0,0"
    });
    When({
        "CMPM.W (A1)+, (A2)+"
    });
    Then({
        "A1 is 0x3002",
        "A2 is 0x4002",
        "(0x3000).W is 0x4455",
        "(0x4000).W is 0x4455",
        "SR is S,0,Z"
    });
}

TEST_F(CMPMTestWord, DifferentRegistersFlagXWorks) {
    Given({
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).W is 0x4455",
        "(0x4000).W is 0x5544",
        "SR is S,0,X"
    });
    When({
        "CMPM.W (A1)+, (A2)+"
    });
    Then({
        "A1 is 0x3002",
        "A2 is 0x4002",
        "(0x3000).W is 0x4455",
        "(0x4000).W is 0x5544",
        "SR is S,0,X"
    });
}

TEST_F(CMPMTestWord, SameRegistersWork) {
    Given({
        "A1 is 0x3000",
        "(0x3000).W is 0x4455",
        "(0x3002).W is 0x8633",
        "SR is S,0,0"
    });
    When({
        "CMPM.W (A1)+, (A1)+"
    });
    Then({
        "A1 is 0x3004",
        "(0x3000).W is 0x4455",
        "(0x3002).W is 0x8633",
        "SR is S,0,V"
    });
}

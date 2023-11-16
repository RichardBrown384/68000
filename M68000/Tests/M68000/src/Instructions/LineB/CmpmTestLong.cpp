#include "M68000/Fixtures/M68000Test.h"

class CMPMTestLong : public M68000Test {};

TEST_F(CMPMTestLong, DifferentRegistersWork) {
    Given({
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).L is 0xFF004455",
        "(0x4000).L is 0x10108633",
        "SR is S,0,0"
    });
    When({
        "CMPM.L (A1)+, (A2)+"
    });
    Then({
        "A1 is 0x3004",
        "A2 is 0x4004",
        "(0x3000).L is 0xFF004455",
        "(0x4000).L is 0x10108633",
        "SR is S,0,C"
    });
}

TEST_F(CMPMTestLong, DifferentRegistersFlagZWorks) {
    Given({
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).L is 0xFF004455",
        "(0x4000).L is 0xFF004455",
        "SR is S,0,0"
    });
    When({
        "CMPM.L (A1)+, (A2)+"
    });
    Then({
        "A1 is 0x3004",
        "A2 is 0x4004",
        "(0x3000).L is 0xFF004455",
        "(0x4000).L is 0xFF004455",
        "SR is S,0,Z"
    });
}

TEST_F(CMPMTestLong, DifferentRegistersFlagXWorks) {
    Given({
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).L is 0xFF004455",
        "(0x4000).L is 0xFF005544",
        "SR is S,0,X"
    });
    When({
        "CMPM.L (A1)+, (A2)+"
    });
    Then({
        "A1 is 0x3004",
        "A2 is 0x4004",
        "(0x3000).L is 0xFF004455",
        "(0x4000).L is 0xFF005544",
        "SR is S,0,X"
    });
}

TEST_F(CMPMTestLong, SameRegistersWork) {
    Given({
        "A1 is 0x3000",
        "(0x3000).L is 0xFF004455",
        "(0x3004).L is 0x10108633",
        "SR is S,0,0"
    });
    When({
        "CMPM.L (A1)+, (A1)+"
    });
    Then({
        "A1 is 0x3008",
        "(0x3000).L is 0xFF004455",
        "(0x3004).L is 0x10108633",
        "SR is S,0,C"
    });
}



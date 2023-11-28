#include "M68000/Fixtures/M68000Test.h"

class CMPMTestLong : public M68000Test {};

TEST_F(CMPMTestLong, DifferentRegistersWork) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).L is 0xFF004455",
        "(0x4000).L is 0x10108633",
    });
    When({
        "CMPM.L (A1)+, (A2)+"
    });
    Then({
        "SR is S,0,C",
        "PC is 0x1002",
        "CYCLES is 20",
        "A1 is 0x3004",
        "A2 is 0x4004",
        "(0x3000).L is 0xFF004455",
        "(0x4000).L is 0x10108633",
    });
}

TEST_F(CMPMTestLong, DifferentRegistersFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).L is 0xFF004455",
        "(0x4000).L is 0xFF004455",
    });
    When({
        "CMPM.L (A1)+, (A2)+"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 20",
        "A1 is 0x3004",
        "A2 is 0x4004",
        "(0x3000).L is 0xFF004455",
        "(0x4000).L is 0xFF004455",
    });
}

TEST_F(CMPMTestLong, DifferentRegistersFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "A1 is 0x3000",
        "A2 is 0x4000",
        "(0x3000).L is 0xFF004455",
        "(0x4000).L is 0xFF005544",
    });
    When({
        "CMPM.L (A1)+, (A2)+"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 20",
        "A1 is 0x3004",
        "A2 is 0x4004",
        "(0x3000).L is 0xFF004455",
        "(0x4000).L is 0xFF005544",
    });
}

TEST_F(CMPMTestLong, SameRegistersWork) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x3000",
        "(0x3000).L is 0xFF004455",
        "(0x3004).L is 0x10108633",
    });
    When({
        "CMPM.L (A1)+, (A1)+"
    });
    Then({
        "SR is S,0,C",
        "PC is 0x1002",
        "CYCLES is 20",
        "A1 is 0x3008",
        "(0x3000).L is 0xFF004455",
        "(0x3004).L is 0x10108633",
    });
}



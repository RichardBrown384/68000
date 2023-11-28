#include "M68000/Fixtures/M68000Test.h"

const char* const VALUES[] = {
    "ANDI.W #0x12, SR",
    "EORI.W #0x12, SR",
    "MOVE.W D1, SR",
    "MOVE.L A5, USP",
    "MOVE.L USP, A5",
    "ORI.W #0x12, SR",
    "RESET",
    "RTE",
    "STOP #0x2000"
};

class PrivilegeViolationExceptionTest :
        public M68000Test,
        public ::testing::WithParamInterface<const char*> {};

TEST_P(PrivilegeViolationExceptionTest, PrivilegeViolationRaised) {
    const char* param = GetParam();
    Given({
        "SR is 0,0,X",
        "PC is 0x1000",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "(0x20).L is 0x2000",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
        "(0x00FFFFFA).W is 0xCDCD",
    });
    When({
        param
    });
    Then({
        "SR is S,0,X",
        "PC is 0x2000",
        "CYCLES is 34",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "(0x20).L is 0x2000",
        "(0x00FFFFFC).L is 0x00001000",
        "(0x00FFFFFA).W is 0x0010",
    });
}

INSTANTIATE_TEST_SUITE_P(PrivilegeViolations,
    PrivilegeViolationExceptionTest,
    ::testing::ValuesIn(VALUES)
);

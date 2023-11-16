#include "M68000/Fixtures/M68000Test.h"

class IllegalInstructionExceptionTest: public M68000Test {};

TEST_F(IllegalInstructionExceptionTest, IllegalFromUserModeWorks) {
    Given({
        "SR is 0,0,XC",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "(0x10).L is 0x00BCBCBC",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "ILLEGAL"
    });
    Then({
        "SR is S,0,XC",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "PC is 0x00BCBCBC",
        "(0x10).L is 0x00BCBCBC",
        "(0x00FFFFFA).W is 0x0011",
        "(0x00FFFFFC).L is 0x00001002",
        "CYCLES is 34"
    });
}

TEST_F(IllegalInstructionExceptionTest, IllegalFromSupervisorModeWorks) {
    Given({
        "SR is TS,0,XC",
        "A7 is 0x01000000",
        "USP is 0x00FF0000",
        "(0x10).L is 0x00BCBCBC",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD"
    });
    When({
        "ILLEGAL"
    });
    Then({
        "SR is S,0,XC",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "PC is 0x00BCBCBC",
        "(0x10).L is 0x00BCBCBC",
        "(0x00FFFFFA).W is 0xA011",
        "(0x00FFFFFC).L is 0x00001002",
        "CYCLES is 34"
    });
}
#include "M68000/Fixtures/M68000Test.h"

class Line7IllegalInstructionTest: public M68000Test {};

TEST_F(Line7IllegalInstructionTest, IllegalInstructionPattern) {
    Given({
        "SR is 0,0,XC",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "(0x10).L is 0x00ADBCBC",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        0x7100
    });
    Then({
        "SR is S,0,XC",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "PC is 0x00ADBCBC",
        "(0x10).L is 0x00ADBCBC",
        "(0x00FFFFFA).W is 0x0011",
        "(0x00FFFFFC).L is 0x00001002",
        "CYCLES is 34"
    });
}
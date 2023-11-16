#include "M68000/Fixtures/M68000Test.h"

class LineFEmulatorExceptionTest: public M68000Test {};

TEST_F(LineFEmulatorExceptionTest, LineFFromUserModeWorks) {
    Given({
        "SR is 0,0,0",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "(0x2C).L is 0x00ADBCBC",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        0xF000u
    });
    Then({
        "SR is S,0,0",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "PC is 0x00ADBCBC",
        "(0x2C).L is 0x00ADBCBC",
        "(0x00FFFFFA).W is 0x0000",
        "(0x00FFFFFC).L is 0x00001000",
        "CYCLES is 34"
    });
}

TEST_F(LineFEmulatorExceptionTest, LineFFromSupervisorModeWorks) {
    Given({
        "SR is S,0,0",
        "A7 is 0x01000000",
        "USP is 0x00FF0000",
        "(0x2C).L is 0x00ADBCBC",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        0xF000u
    });
    Then({
        "SR is S,0,0",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "PC is 0x00ADBCBC",
        "(0x2C).L is 0x00ADBCBC",
        "(0x00FFFFFA).W is 0x2000",
        "(0x00FFFFFC).L is 0x00001000",
        "CYCLES is 34"
    });
}
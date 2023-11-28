#include "M68000/Fixtures/M68000Test.h"

class LineAEmulatorExceptionTest: public M68000Test {};

TEST_F(LineAEmulatorExceptionTest, LineAFromUserModeWorks) {
    Given({
        "SR is 0,0,0",
        "PC is 0x1000",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "(0x28).L is 0x00ADBCBC",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        0xA000u
    });
    Then({
        "SR is S,0,0",
        "PC is 0x00ADBCBC",
        "CYCLES is 34",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "(0x28).L is 0x00ADBCBC",
        "(0x00FFFFFA).W is 0x0000",
        "(0x00FFFFFC).L is 0x00001000",
    });
}

TEST_F(LineAEmulatorExceptionTest, LineAFromSupervisorModeWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A7 is 0x01000000",
        "USP is 0x00FF0000",
        "(0x28).L is 0x00ADBCBC",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        0xA000u
    });
    Then({
        "SR is S,0,0",
        "PC is 0x00ADBCBC",
        "CYCLES is 34",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "(0x28).L is 0x00ADBCBC",
        "(0x00FFFFFA).W is 0x2000",
        "(0x00FFFFFC).L is 0x00001000",
    });
}

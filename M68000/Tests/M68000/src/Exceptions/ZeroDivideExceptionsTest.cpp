#include "M68000/Fixtures/M68000Test.h"

class ZeroDivideExceptionTest: public M68000Test {};

TEST_F(ZeroDivideExceptionTest, DivsByZeroFromUserModeWorks) {
    Given({
        "SR is 0,0,XC",
        "PC is 0x1000",
        "D0 is 0x00000000",
        "D1 is 0x00000001",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "(0x14).L is 0x0BBBCCCC",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "DIVS D0, D1"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x0BBBCCCC",
        "CYCLES is 38",
        "D0 is 0x00000000",
        "D1 is 0x00000001",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "(0x14).L is 0x0BBBCCCC",
        "(0x00FFFFFA).W is 0x0011",
        "(0x00FFFFFC).L is 0x00001000",
    });
}

TEST_F(ZeroDivideExceptionTest, DivsByZeroFromSupervisorModeWorks) {
    Given({
        "SR is TS,0,XC",
        "PC is 0x1000",
        "D0 is 0x00000000",
        "D1 is 0x00000001",
        "A7 is 0x01000000",
        "USP is 0x00FF0000",
        "(0x14).L is 0x0BBBCCCC",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "DIVS D0, D1"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x0BBBCCCC",
        "CYCLES is 38",
        "D0 is 0x00000000",
        "D1 is 0x00000001",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "(0x14).L is 0x0BBBCCCC",
        "(0x00FFFFFA).W is 0xA011",
        "(0x00FFFFFC).L is 0x00001000",
    });
}

TEST_F(ZeroDivideExceptionTest, DivuByZeroFromUserModeWorks) {
    Given({
        "SR is 0,0,XC",
        "PC is 0x1000",
        "D0 is 0x00000000",
        "D1 is 0x00000001",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "(0x14).L is 0x0BBBCCCC",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "DIVU D0, D1"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x0BBBCCCC",
        "CYCLES is 38",
        "D0 is 0x00000000",
        "D1 is 0x00000001",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "(0x14).L is 0x0BBBCCCC",
        "(0x00FFFFFA).W is 0x0011",
        "(0x00FFFFFC).L is 0x00001000",
    });
}

TEST_F(ZeroDivideExceptionTest, DivuByZeroFromSupervisorModeWorks) {
    Given({
        "SR is TS,0,XC",
        "PC is 0x1000",
        "D0 is 0x00000000",
        "D1 is 0x00000001",
        "A7 is 0x01000000",
        "USP is 0x00FF0000",
        "(0x14).L is 0x0BBBCCCC",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "DIVU D0, D1"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x0BBBCCCC",
        "CYCLES is 38",
        "D0 is 0x00000000",
        "D1 is 0x00000001",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "(0x14).L is 0x0BBBCCCC",
        "(0x00FFFFFA).W is 0xA011",
        "(0x00FFFFFC).L is 0x00001000",
    });
}

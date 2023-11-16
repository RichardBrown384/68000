#include "M68000/Fixtures/M68000Test.h"

class TrapExceptionTest: public M68000Test {};

TEST_F(TrapExceptionTest, Trap0FromUserModeWorks) {
    Given({
        "SR is 0,0,V",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "(0x80).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "TRAP #0"
    });
    Then({
        "SR is S,0,V",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "PC is 0x00CAFED0",
        "(0x80).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0x0002",
        "(0x00FFFFFC).L is 0x00001002",
        "CYCLES is 34"
    });
}

TEST_F(TrapExceptionTest, Trap0FromSupervisorModeWorks) {
    Given({
        "SR is TS,0,V",
        "A7 is 0x01000000",
        "USP is 0x00FF0000",
        "(0x80).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD"
    });
    When({
        "TRAP #0"
    });
    Then({
        "SR is S,0,V",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "PC is 0x00CAFED0",
        "(0x80).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0xA002",
        "(0x00FFFFFC).L is 0x00001002",
        "CYCLES is 34"
    });
}

TEST_F(TrapExceptionTest, Trap7FromUserModeWorks) {
    Given({
        "SR is 0,0,V",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "(0x9C).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "TRAP #7"
    });
    Then({
        "SR is S,0,V",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "PC is 0x00CAFED0",
        "(0x9C).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0x0002",
        "(0x00FFFFFC).L is 0x00001002",
        "CYCLES is 34"
    });
}

TEST_F(TrapExceptionTest, Trap15FromUserModeWorks) {
    Given({
        "SR is 0,0,V",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "(0xBC).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "TRAP #15"
    });
    Then({
        "SR is S,0,V",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "PC is 0x00CAFED0",
        "(0xBC).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0x0002",
        "(0x00FFFFFC).L is 0x00001002",
        "CYCLES is 34"
    });
}
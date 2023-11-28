#include "M68000/Fixtures/M68000Test.h"

class TrapvExceptionTest: public M68000Test {};

TEST_F(TrapvExceptionTest, TrapvFromUserModeWorks) {
    Given({
        "SR is 0,0,V",
        "PC is 0x1000",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "(0x1C).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "TRAPV"
    });
    Then({
        "SR is S,0,V",
        "PC is 0x00CAFED0",
        "CYCLES is 34",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "(0x1C).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0x0002",
        "(0x00FFFFFC).L is 0x00001002",
    });
}

TEST_F(TrapvExceptionTest, TrapvFromSupervisorModeWorks) {
    Given({
        "SR is TS,0,V",
        "PC is 0x1000",
        "A7 is 0x01000000",
        "USP is 0x00FF0000",
        "(0x1C).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "TRAPV"
    });
    Then({
        "SR is S,0,V",
        "PC is 0x00CAFED0",
        "CYCLES is 34",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "(0x1C).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0xA002",
        "(0x00FFFFFC).L is 0x00001002",
    });
}

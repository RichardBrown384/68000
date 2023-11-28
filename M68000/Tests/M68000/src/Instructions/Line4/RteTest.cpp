#include "M68000/Fixtures/M68000Test.h"

class RTETest : public M68000Test {};

TEST_F(RTETest, RteToUserModeWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A7 is 0x00FFFFFA",
        "USP is 0x00005000",
        "(0x00FFFFFA).W is 0x0011",
        "(0x00FFFFFC).L is 0x00FECAFE",
    });
    When({
        "RTE"
    });
    Then({
        "SR is 0,0,XC",
        "PC is 0x00FECAFE",
        "CYCLES is 20",
        "A7 is 0x00005000",
        "SSP is 0x01000000",
        "(0x00FFFFFA).W is 0x0011",
        "(0x00FFFFFC).L is 0x00FECAFE",
    });
}

TEST_F(RTETest, RteToSupervisorModeWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A7 is 0x00FFFFFA",
        "USP is 0x00005000",
        "(0x00FFFFFA).W is 0x2011",
        "(0x00FFFFFC).L is 0x00FECAFE",
    });
    When({
        "RTE"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x00FECAFE",
        "CYCLES is 20",
        "A7 is 0x01000000",
        "USP is 0x00005000",
        "(0x00FFFFFA).W is 0x2011",
        "(0x00FFFFFC).L is 0x00FECAFE",
    });
}

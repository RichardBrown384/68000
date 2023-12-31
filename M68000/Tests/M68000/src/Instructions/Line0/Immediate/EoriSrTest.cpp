#include "M68000/Fixtures/M68000Test.h"

class EORISRTest: public M68000Test {};

TEST_F(EORISRTest, EoriSRPreservingSupervisorBitWorks) {
    Given({
        "SR is S,3,XC",
        "PC is 0x1000",
        "A7 is 0x01000000",
        "USP is 0x00FF0000",
    });
    When({
        "EORI.W #0x1F, SR"
    });
    Then({
        "SR is S,3,NZV",
        "PC is 0x1004",
        "CYCLES is 20",
        "A7 is 0x01000000",
        "USP is 0x00FF0000",
    });
}

TEST_F(EORISRTest, EoriSRClearingSupervisorBitWorks) {
    Given({
        "SR is S,3,XC",
        "PC is 0x1000",
        "A7 is 0x01000000",
        "USP is 0x00FF0000",
    });
    When({
        "EORI.W #0xFFFF, SR"
    });
    Then({
        "SR is T,4,NZV",
        "PC is 0x1004",
        "CYCLES is 20",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
    });
}

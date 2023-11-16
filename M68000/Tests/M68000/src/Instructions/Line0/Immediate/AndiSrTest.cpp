#include "M68000/Fixtures/M68000Test.h"

class ANDISRTest: public M68000Test {};

TEST_F(ANDISRTest, AndiSRPreservingSupervisorBitWorks) {
    Given({
        "SR is S,3,XC",
        "A7 is 0x01000000",
        "USP is 0x00FF0000",
    });
    When({
        "ANDI.W #0xFFFF, SR"
    });
    Then({
        "SR is S,3,XC",
        "A7 is 0x01000000",
        "USP is 0x00FF0000",
    });
}

TEST_F(ANDISRTest, AndiSRClearingSupervisorBitWorks) {
    Given({
        "SR is S,3,XC",
        "A7 is 0x01000000",
        "USP is 0x00FF0000",
    });
    When({
        "ANDI.W #0xFF, SR"
    });
    Then({
        "SR is 0,0,XC",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
    });
}

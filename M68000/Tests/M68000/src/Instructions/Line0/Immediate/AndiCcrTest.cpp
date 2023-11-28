#include "M68000/Fixtures/M68000Test.h"

class ANDICCRTest: public M68000Test {};

TEST_F(ANDICCRTest, AndiCCRWorks) {
    Given({
        "SR is S,0,XNZVC",
        "PC is 0x1000",
    });
    When({
        "ANDI.B #0x15, CCR"
    });
    Then({
        "SR is S,0,XZC",
        "PC is 0x1004",
        "CYCLES is 20",
    });
}


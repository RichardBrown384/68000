#include "M68000/Fixtures/M68000Test.h"

class ORICCRTest: public M68000Test {};

TEST_F(ORICCRTest, OriCCRWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
    });
    When({
        "ORI.B #0x1F, CCR"
    });
    Then({
        "SR is S,0,XNZVC",
        "PC is 0x1004",
        "CYCLES is 20",
    });
}

#include "M68000/Fixtures/M68000Test.h"

class ORISRTest: public M68000Test {};

TEST_F(ORISRTest, OriSRWorks) {
    Given({
        "SR is S,3,XC",
        "A7 is 0x01000000",
        "USP is 0x00FF0000",
    });
    When({
        "ORI.W #0xFFFF, SR"
    });
    Then({
        "SR is TS,7,XNZVC",
        "A7 is 0x01000000",
        "USP is 0x00FF0000",
    });
}

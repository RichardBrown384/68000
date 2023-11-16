#include "M68000/Fixtures/M68000Test.h"

class ANDICCRTest: public M68000Test {};

TEST_F(ANDICCRTest, AndiCCRWorks) {
    Given({
        "SR is S,0,XNZVC"
    });
    When({
        "ANDI.B #0x15, CCR"
    });
    Then({
        "SR is S,0,XZC"
    });
}


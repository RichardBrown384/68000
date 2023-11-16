#include "M68000/Fixtures/M68000Test.h"

class ORICCRTest: public M68000Test {};

TEST_F(ORICCRTest, OriCCRWorks) {
    Given({
        "SR is S,0,0"
    });
    When({
        "ORI.B #0x1F, CCR"
    });
    Then({
        "SR is S,0,XNZVC"
    });
}

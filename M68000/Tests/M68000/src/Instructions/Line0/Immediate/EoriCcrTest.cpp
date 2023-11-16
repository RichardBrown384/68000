#include "M68000/Fixtures/M68000Test.h"

class EORICCRTest: public M68000Test {};

TEST_F(EORICCRTest, EoriCCRWorks) {
    Given({
        "SR is S,0,XZC"
    });
    When({
        "EORI.B #0xFF, CCR"
    });
    Then({
        "SR is S,0,NV"
    });
}
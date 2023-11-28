#include "M68000/Fixtures/M68000Test.h"

class EORICCRTest: public M68000Test {};

TEST_F(EORICCRTest, EoriCCRWorks) {
    Given({
        "SR is S,0,XZC",
        "PC is 0x1000",
    });
    When({
        "EORI.B #0xFF, CCR"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1004",
        "CYCLES is 20",
    });
}

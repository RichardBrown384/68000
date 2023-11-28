#include "M68000/Fixtures/M68000Test.h"

class TRAPVTest : public M68000Test {};

TEST_F(TRAPVTest, TrapvWhenOverflowIsClearWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
    });
    When({
        "TRAPV"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
    });
}

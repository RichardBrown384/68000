#include "M68000/Fixtures/M68000Test.h"

class NOPTest : public M68000Test {};

TEST_F(NOPTest, NOPWorks) {
    Given({
        "SR is S,0,0"
    });
    When({
        "NOP"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4"
    });
}


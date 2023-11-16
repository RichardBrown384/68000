#include "M68000/Fixtures/M68000Test.h"

class RESETTest : public M68000Test {};

TEST_F(RESETTest, ResetWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000"
    });
    When({
        "RESET"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 132"
    });
}

#include "M68000/Fixtures/M68000Test.h"

class MoveUSPTest : public M68000Test {};

TEST_F(MoveUSPTest, ToUsp) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A5 is 0xDEADBEEF",
        "USP is 0xCDCDCDCD",
    });
    When({
        "MOVE.L A5, USP"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "A5 is 0xDEADBEEF",
        "USP is 0xDEADBEEF",
    });
}

TEST_F(MoveUSPTest, ToRegister) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A5 is 0xCDCDCDCD",
        "USP is 0xDEADBEEF",
    });
    When({
        "MOVE.L USP, A5"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "A5 is 0xDEADBEEF",
        "USP is 0xDEADBEEF",
    });
}

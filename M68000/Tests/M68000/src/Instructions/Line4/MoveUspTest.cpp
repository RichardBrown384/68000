#include "M68000/Fixtures/M68000Test.h"

class MoveUSPTest : public M68000Test {};

TEST_F(MoveUSPTest, ToUsp) {
    Given({
        "A5 is 0xDEADBEEF",
        "USP is 0xCDCDCDCD",
    });
    When({
        "MOVE.L A5, USP"
    });
    Then({
        "A5 is 0xDEADBEEF",
        "USP is 0xDEADBEEF",
        "CYCLES is 4"
    });
}

TEST_F(MoveUSPTest, ToRegister) {
    Given({
        "A5 is 0xCDCDCDCD",
        "USP is 0xDEADBEEF",
    });
    When({
        "MOVE.L USP, A5"
    });
    Then({
        "A5 is 0xDEADBEEF",
        "USP is 0xDEADBEEF",
        "CYCLES is 4"
    });
}

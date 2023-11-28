#include "M68000/Fixtures/M68000Test.h"

class MoveFromSRTest : public M68000Test {};

TEST_F(MoveFromSRTest, DataRegister) {
    Given({
        "SR is 0,0,XZC",
        "PC is 0x1000",
        "D1 is 0xCDCDCDCD",
    });
    When({
        "MOVE.W SR, D1"
    });
    Then({
        "SR is 0,0,XZC",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0xCDCD0015",
    });
}

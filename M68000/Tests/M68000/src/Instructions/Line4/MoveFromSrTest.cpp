#include "M68000/Fixtures/M68000Test.h"

class MoveFromSRTest : public M68000Test {};

TEST_F(MoveFromSRTest, DataRegister) {
    Given({
        "D1 is 0xCDCDCDCD",
        "SR is 0,0,XZC"
    });
    When({
        "MOVE.W SR, D1"
    });
    Then({
        "D1 is 0xCDCD0015",
        "SR is 0,0,XZC"
    });
}

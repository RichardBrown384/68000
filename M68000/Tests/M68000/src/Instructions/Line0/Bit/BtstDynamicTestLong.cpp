#include "M68000/Fixtures/M68000Test.h"

class BTSTDynamicTestLong : public M68000Test {};

TEST_F(BTSTDynamicTestLong, BitSetWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0x17",
        "D2 is 0x00800001",
    });
    When({
        "BTST.L D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x17",
        "D2 is 0x00800001",
    });
}

TEST_F(BTSTDynamicTestLong, BitClearWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x17",
        "D2 is 0x00000001",
    });
    When({
        "BTST.L D1, D2"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x17",
        "D2 is 0x00000001",
    });
}

#include "M68000/Fixtures/M68000Test.h"

class BCHGDynamicTestLong : public M68000Test {};

TEST_F(BCHGDynamicTestLong, BitSetWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x17",
        "D2 is 0x00800001",
    });
    When({
        "BCHG.L D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x17",
        "D2 is 0x00000001",
    });
}

TEST_F(BCHGDynamicTestLong, BitClearWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x17",
        "D2 is 0x00000001",
    });
    When({
        "BCHG.L D1, D2"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x17",
        "D2 is 0x00800001",
    });
}

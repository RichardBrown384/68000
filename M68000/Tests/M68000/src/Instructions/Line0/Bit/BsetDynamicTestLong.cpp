#include "M68000/Fixtures/M68000Test.h"

class BSETDynamicTestLong : public M68000Test {};

TEST_F(BSETDynamicTestLong, BitSetWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0x17",
        "D2 is 0x00800001",
    });
    When({
        "BSET.L D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x17",
        "D2 is 0x00800001",
    });
}

TEST_F(BSETDynamicTestLong, BitClearWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x17",
        "D2 is 0x00000001",
    });
    When({
        "BSET.L D1, D2"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x17",
        "D2 is 0x00800001",
    });
}

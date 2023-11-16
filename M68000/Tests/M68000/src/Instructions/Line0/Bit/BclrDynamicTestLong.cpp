#include "M68000/Fixtures/M68000Test.h"

class BCLRDynamicTestLong : public M68000Test {};

TEST_F(BCLRDynamicTestLong, BitSetWorks) {
    Given({
        "D1 is 0x17",
        "D2 is 0x00800001",
        "SR is S,0,0"
    });
    When({
        "BCLR.L D1, D2"
    });
    Then({
        "D1 is 0x17",
        "D2 is 0x00000001",
        "SR is S,0,0"
    });
}

TEST_F(BCLRDynamicTestLong, BitClearWorks) {
    Given({
        "D1 is 0x17",
        "D2 is 0x00000001",
        "SR is S,0,0"
    });
    When({
        "BCLR.L D1, D2"
    });
    Then({
        "D1 is 0x17",
        "D2 is 0x00000001",
        "SR is S,0,Z"
    });
}
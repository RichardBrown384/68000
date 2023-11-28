#include "M68000/Fixtures/M68000Test.h"

class BCLRStaticTestLong : public M68000Test {};

TEST_F(BCLRStaticTestLong, BitSetWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D2 is 0x00800001",
    });
    When({
        "BCLR.L #0x17, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 14",
        "D2 is 0x00000001",
    });
}

TEST_F(BCLRStaticTestLong, BitClearWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D2 is 0x00000001",
    });
    When({
        "BCLR.L #0x17, D2"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 14",
        "D2 is 0x00000001",
    });
}

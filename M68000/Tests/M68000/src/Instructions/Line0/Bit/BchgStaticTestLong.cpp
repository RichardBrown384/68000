#include "M68000/Fixtures/M68000Test.h"

class BCHGStaticTestLong : public M68000Test {};

TEST_F(BCHGStaticTestLong, BitSetWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D2 is 0x00800001",
    });
    When({
        "BCHG.L #0x17, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D2 is 0x00000001",
    });
}

TEST_F(BCHGStaticTestLong, BitClearWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D2 is 0x00000001",
    });
    When({
        "BCHG.L #0x17, D2"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 12",
        "D2 is 0x00800001",
    });
}

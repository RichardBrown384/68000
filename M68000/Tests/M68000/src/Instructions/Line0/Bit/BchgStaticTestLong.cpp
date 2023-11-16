#include "M68000/Fixtures/M68000Test.h"

class BCHGStaticTestLong : public M68000Test {};

TEST_F(BCHGStaticTestLong, BitSetWorks) {
    Given({
        "D2 is 0x00800001",
        "SR is S,0,0"
    });
    When({
        "BCHG.L #0x17, D2"
    });
    Then({
        "D2 is 0x00000001",
        "SR is S,0,0"
    });
}

TEST_F(BCHGStaticTestLong, BitClearWorks) {
    Given({
        "D2 is 0x00000001",
        "SR is S,0,0"
    });
    When({
        "BCHG.L #0x17, D2"
    });
    Then({
        "D2 is 0x00800001",
        "SR is S,0,Z"
    });
}
#include "M68000/Fixtures/M68000Test.h"

class BSETStaticTestLong : public M68000Test {};

TEST_F(BSETStaticTestLong, BitSetWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D2 is 0x00800001",
    });
    When({
        "BSET.L #0x17, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D2 is 0x00800001",
    });
}

TEST_F(BSETStaticTestLong, BitClearWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D2 is 0x00000001",
    });
    When({
        "BSET.L #0x17, D2"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 12",
        "D2 is 0x00800001",
    });
}

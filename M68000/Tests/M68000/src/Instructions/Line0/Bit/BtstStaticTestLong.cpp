#include "M68000/Fixtures/M68000Test.h"

class BTSTStaticTestLong : public M68000Test {};

TEST_F(BTSTStaticTestLong, BitSetWorks) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D2 is 0x00800001",
    });
    When({
        "BTST.L #0x17, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 10",
        "D2 is 0x00800001",
    });
}

TEST_F(BTSTStaticTestLong, BitClearWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D2 is 0x00000001",
    });
    When({
        "BTST.L #0x17, D2"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 10",
        "D2 is 0x00000001",
    });
}

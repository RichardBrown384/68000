#include "M68000/Fixtures/M68000Test.h"

class BSETDynamicTestLong : public M68000Test {};

TEST_F(BSETDynamicTestLong, BitSetWorks) {
    Given({
        "D1 is 0x17",
        "D2 is 0x00800001",
        "SR is S,0,Z"
    });
    When({
        "BSET.L D1, D2"
    });
    Then({
        "D1 is 0x17",
        "D2 is 0x00800001",
        "SR is S,0,0"
    });
}

TEST_F(BSETDynamicTestLong, BitClearWorks) {
    Given({
        "D1 is 0x17",
        "D2 is 0x00000001",
        "SR is S,0,0"
    });
    When({
        "BSET.L D1, D2"
    });
    Then({
        "D1 is 0x17",
        "D2 is 0x00800001",
        "SR is S,0,Z"
    });
}
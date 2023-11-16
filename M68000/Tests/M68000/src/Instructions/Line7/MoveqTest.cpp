#include "M68000/Fixtures/M68000Test.h"

class MOVEQTest : public M68000Test {};

TEST_F(MOVEQTest, ZeroShouldZeroTheRegister) {
    Given({
        "SR is S,0,0",
        "D2 is 0xFFFFFFFF"
    });
    When({
        "MOVEQ #0, D2"
    });
    Then({
        "SR is S,0,Z",
        "D2 is 0x0",
        "CYCLES is 4"
    });
}

TEST_F(MOVEQTest, PositiveValueShouldClearFlagN) {
    Given({
        "D3 is 0x0",
        "SR is S,0,N"
    });
    When({
        "MOVEQ #0x7E, D3"
    });
    Then({
        "D3 is 0x7E",
        "SR is S,0,0",
        "CYCLES is 4",
    });
}

TEST_F(MOVEQTest, NegativeValueShouldSetFlagN) {
    Given({
        "SR is S,0,0"
    });
    When({
        "MOVEQ #-12, D3"
    });
    Then({
        "D3 is 0x0FFFFFFF4",
        "SR is S,0,N",
        "CYCLES is 4"
    });
}

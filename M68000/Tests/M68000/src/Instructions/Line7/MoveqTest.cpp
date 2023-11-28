#include "M68000/Fixtures/M68000Test.h"

class MOVEQTest : public M68000Test {};

TEST_F(MOVEQTest, ZeroShouldZeroTheRegister) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D2 is 0xFFFFFFFF",
    });
    When({
        "MOVEQ #0, D2"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 4",
        "D2 is 0x0",
    });
}

TEST_F(MOVEQTest, PositiveValueShouldClearFlagN) {
    Given({
        "SR is S,0,N",
        "PC is 0x1000",
        "D3 is 0x0",
    });
    When({
        "MOVEQ #0x7E, D3"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D3 is 0x7E",
    });
}

TEST_F(MOVEQTest, NegativeValueShouldSetFlagN) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
    });
    When({
        "MOVEQ #-12, D3"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 4",
        "D3 is 0x0FFFFFFF4",
    });
}

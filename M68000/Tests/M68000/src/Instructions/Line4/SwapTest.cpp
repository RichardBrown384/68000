#include "M68000/Fixtures/M68000Test.h"

class SWAPTest : public M68000Test {};

TEST_F(SWAPTest, SwapWorks) {
    Given({
        "SR is S,0,XVC",
        "PC is 0x1000",
        "D6 is 0x98ABCDEF",
    });
    When({
        "SWAP D6"
    });
    Then({
        "SR is S,0,XN",
        "PC is 0x1002",
        "CYCLES is 4",
        "D6 is 0xCDEF98AB",
    });
}

TEST_F(SWAPTest, ZeroFlagShouldNotBeSetWhenOnlyLowerWordIsZero) {
    Given({
        "SR is S,0,XVC",
        "PC is 0x1000",
        "D6 is 0x0000CDEF",
    });
    When({
        "SWAP D6"
    });
    Then({
        "SR is S,0,XN",
        "PC is 0x1002",
        "CYCLES is 4",
        "D6 is 0xCDEF0000",
    });
}

TEST_F(SWAPTest, ZeroFlagShouldBeSetWhenResultIsZero) {
    Given({
        "SR is S,0,XVC",
        "PC is 0x1000",
        "D6 is 0x00000000",
    });
    When({
        "SWAP D6"
    });
    Then({
        "SR is S,0,XZ",
        "PC is 0x1002",
        "CYCLES is 4",
        "D6 is 0x00000000",
    });
}

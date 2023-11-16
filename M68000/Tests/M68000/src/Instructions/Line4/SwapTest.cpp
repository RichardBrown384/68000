#include "M68000/Fixtures/M68000Test.h"

class SWAPTest : public M68000Test {};

TEST_F(SWAPTest, SwapWorks) {
    Given({
        "D6 is 0x98ABCDEF",
        "SR is S,0,XVC"
    });
    When({
        "SWAP D6"
    });
    Then({
        "D6 is 0xCDEF98AB",
        "SR is S,0,XN",
        "CYCLES is 4"
    });
}

TEST_F(SWAPTest, ZeroFlagShouldNotBeSetWhenOnlyLowerWordIsZero) {
    Given({
        "D6 is 0x0000CDEF",
        "SR is S,0,XVC"
    });
    When({
        "SWAP D6"
    });
    Then({
        "D6 is 0xCDEF0000",
        "SR is S,0,XN",
        "CYCLES is 4"
    });
}

TEST_F(SWAPTest, ZeroFlagShouldBeSetWhenResultIsZero) {
    Given({
        "D6 is 0x00000000",
        "SR is S,0,XVC"
    });
    When({
        "SWAP D6"
    });
    Then({
        "D6 is 0x00000000",
        "SR is S,0,XZ",
        "CYCLES is 4"
    });
}

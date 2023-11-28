#include "M68000/Fixtures/M68000Test.h"

class BRATest : public M68000Test {};

TEST_F(BRATest, BRAByteWorksPositiveDisplacement) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
    });
    When({
        "BRA.B *+0x10"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1010",
        "CYCLES is 10",
    });
}

TEST_F(BRATest, BRAByteWorksNegativeDisplacement) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
    });
    When({
        "BRA.B *-0x10"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x0FF0",
        "CYCLES is 10",
    });
}

TEST_F(BRATest, BRAWordWorksPositiveDisplacement) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
    });
    When({
        "BRA.W *+0x200"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1200",
        "CYCLES is 10",
    });
}

TEST_F(BRATest, BRAWordWorksNegativeDisplacement) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
    });
    When({
        "BRA.W *-0x200"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x0E00",
        "CYCLES is 10",
    });
}

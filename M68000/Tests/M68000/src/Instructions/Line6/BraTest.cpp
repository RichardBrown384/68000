#include "M68000/Fixtures/M68000Test.h"

class BRATest : public M68000Test {};

TEST_F(BRATest, BRAByteWorksPositiveDisplacement) {
    Given({
        "SR is S,0,0"
    });
    When({
        "BRA.B *+0x10"
    });
    Then({
        "PC is 0x1010",
        "SR is S,0,0"
    });
}

TEST_F(BRATest, BRAByteWorksNegativeDisplacement) {
    Given({
        "SR is S,0,0"
    });
    When({
        "BRA.B *-0x10"
    });
    Then({
        "PC is 0x0FF0",
        "SR is S,0,0"
    });
}

TEST_F(BRATest, BRAWordWorksPositiveDisplacement) {
    Given({
        "SR is S,0,0"
    });
    When({
        "BRA.W *+0x200"
    });
    Then({
        "PC is 0x1200",
        "SR is S,0,0"
    });
}

TEST_F(BRATest, BRAWordWorksNegativeDisplacement) {
    Given({
        "SR is S,0,0"
    });
    When({
        "BRA.W *-0x200"
    });
    Then({
        "PC is 0x0E00",
        "SR is S,0,0"
    });
}

#include "M68000/Fixtures/M68000Test.h"

class NEGTest : public M68000Test {};

TEST_F(NEGTest, RegisterNEGWorks) {
    Given({
        "D1 is 0x22",
        "SR is S,0,0"
    });
    When({
        "NEG.B D1"
    });
    Then({
        "D1 is 0xDE",
        "SR is S,0,XNC"
    });
}

TEST_F(NEGTest, ExtendFlagDoesNotInfluencesResult) {
    Given({
        "D1 is 0x22",
        "SR is S,0,X"
    });
    When({
        "NEG.B D1"
    });
    Then({
        "D1 is 0xDE",
        "SR is S,0,XNC"
    });
}

TEST_F(NEGTest, ZeroResultClearsCarryFlag) {
    Given({
        "D1 is 0x00",
        "SR is S,0,C"
    });
    When({
        "NEG.B D1"
    });
    Then({
        "D1 is 0x00",
        "SR is S,0,Z"
    });
}

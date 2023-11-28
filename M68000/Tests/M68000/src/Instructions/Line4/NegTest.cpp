#include "M68000/Fixtures/M68000Test.h"

class NEGTest : public M68000Test {};

TEST_F(NEGTest, RegisterNEGWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x22",
    });
    When({
        "NEG.B D1"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0xDE",
    });
}

TEST_F(NEGTest, ExtendFlagDoesNotInfluencesResult) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0x22",
    });
    When({
        "NEG.B D1"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0xDE",
    });
}

TEST_F(NEGTest, ZeroResultClearsCarryFlag) {
    Given({
        "SR is S,0,C",
        "PC is 0x1000",
        "D1 is 0x00",
    });
    When({
        "NEG.B D1"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x00",
    });
}

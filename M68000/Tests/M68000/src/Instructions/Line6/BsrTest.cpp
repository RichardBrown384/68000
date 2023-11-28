#include "M68000/Fixtures/M68000Test.h"

class BSRTest : public M68000Test {};

TEST_F(BSRTest, BSRByteWorksPositiveDisplacement) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A7 is 0x01000000",
        "(0x01000000).L is 0xDEADBEEF",
    });
    When({
        "BSR.B *+0x10"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1010",
        "CYCLES is 18",
        "A7 is 0x00FFFFFC",
        "(0x00FFFFFC).L is 0x1002",
    });
}

TEST_F(BSRTest, BSRByteWorksNegativeDisplacement) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A7 is 0x01000000",
        "(0x01000000).L is 0xDEADBEEF",
    });
    When({
        "BSR.B *-0x10"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x0FF0",
        "CYCLES is 18",
        "A7 is 0x00FFFFFC",
        "(0x00FFFFFC).L is 0x1002",
    });
}

TEST_F(BSRTest, BSRWordWorksPositiveDisplacement) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A7 is 0x01000000",
        "(0x01000000).L is 0xDEADBEEF",
    });
    When({
        "BSR.W *+0x200"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1200",
        "CYCLES is 18",
        "A7 is 0x00FFFFFC",
        "(0x00FFFFFC).L is 0x1004",
    });
}

TEST_F(BSRTest, BSRWordWorksNegativeDisplacement) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A7 is 0x01000000",
        "(0x01000000).L is 0xDEADBEEF",
    });
    When({
        "BSR.W *-0x200"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x0E00",
        "CYCLES is 18",
        "A7 is 0x00FFFFFC",
        "(0x00FFFFFC).L is 0x1004",
    });
}

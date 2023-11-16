#include "M68000/Fixtures/M68000Test.h"

class BSRTest : public M68000Test {};

TEST_F(BSRTest, BSRByteWorksPositiveDisplacement) {
    Given({
        "SR is S,0,0",
        "A7 is 0x01000000",
        "(0x01000000).L is 0xDEADBEEF"
    });
    When({
        "BSR.B *+0x10"
    });
    Then({
        "A7 is 0x00FFFFFC",
        "(0x00FFFFFC).L is 0x1002",
        "PC is 0x1010",
        "SR is S,0,0"
    });
}

TEST_F(BSRTest, BSRByteWorksNegativeDisplacement) {
    Given({
        "SR is S,0,0",
        "A7 is 0x01000000",
        "(0x01000000).L is 0xDEADBEEF"
    });
    When({
        "BSR.B *-0x10"
    });
    Then({
        "A7 is 0x00FFFFFC",
        "(0x00FFFFFC).L is 0x1002",
        "PC is 0x0FF0",
        "SR is S,0,0"
    });
}

TEST_F(BSRTest, BSRWordWorksPositiveDisplacement) {
    Given({
        "SR is S,0,0",
        "A7 is 0x01000000",
        "(0x01000000).L is 0xDEADBEEF"
    });
    When({
        "BSR.W *+0x200"
    });
    Then({
        "A7 is 0x00FFFFFC",
        "(0x00FFFFFC).L is 0x1004",
        "PC is 0x1200",
        "SR is S,0,0"
    });
}

TEST_F(BSRTest, BSRWordWorksNegativeDisplacement) {
    Given({
        "SR is S,0,0",
        "A7 is 0x01000000",
        "(0x01000000).L is 0xDEADBEEF"
    });
    When({
        "BSR.W *-0x200"
    });
    Then({
        "A7 is 0x00FFFFFC",
        "(0x00FFFFFC).L is 0x1004",
        "PC is 0x0E00",
        "SR is S,0,0"
    });
}

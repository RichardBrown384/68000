#include "M68000/Fixtures/M68000Test.h"

class NOTTest : public M68000Test {};

TEST_F(NOTTest, RegisterNOTWorks) {
    Given({
        "D1 is 0xAA",
        "SR is S,0,0"
    });
    When({
        "NOT.B D1"
    });
    Then({
        "D1 is 0x55",
        "SR is S,0,0"
    });
}

TEST_F(NOTTest, SetsNFlag) {
    Given({
        "D1 is 0x55",
        "SR is S,0,0"
    });
    When({
        "NOT.B D1"
    });
    Then({
        "D1 is 0xAA",
        "SR is S,0,N"
    });
}

TEST_F(NOTTest, PreservesXAndClearsVC) {
    Given({
        "D1 is 0x80",
        "SR is S,0,XVC"
    });
    When({
        "NOT.B D1"
    });
    Then({
        "D1 is 0x7F",
        "SR is S,0,X"
    });
}

TEST_F(NOTTest, ZeroResultSetsZeroFlag) {
    Given({
        "D1 is 0xFF",
        "SR is S,0,0"
    });
    When({
        "NOT.B D1"
    });
    Then({
        "D1 is 0x00",
        "SR is S,0,Z"
    });
}

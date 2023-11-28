#include "M68000/Fixtures/M68000Test.h"

class NOTTest : public M68000Test {};

TEST_F(NOTTest, RegisterNOTWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xAA",
    });
    When({
        "NOT.B D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x55",
    });
}

TEST_F(NOTTest, SetsNFlag) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x55",
    });
    When({
        "NOT.B D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0xAA",
    });
}

TEST_F(NOTTest, PreservesXAndClearsVC) {
    Given({
        "SR is S,0,XVC",
        "PC is 0x1000",
        "D1 is 0x80",
    });
    When({
        "NOT.B D1"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x7F",
    });
}

TEST_F(NOTTest, ZeroResultSetsZeroFlag) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xFF",
    });
    When({
        "NOT.B D1"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x00",
    });
}

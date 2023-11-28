#include "M68000/Fixtures/M68000Test.h"

class STOPTest : public M68000Test {};

TEST_F(STOPTest, RemainAsSupervisor) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A7 is 0x001000000",
        "USP is 0x00FFFFFF",
        "STOPPED is 0",
    });
    When({
        "STOP #0xA001"
    });
    Then({
        "SR is TS,0,C",
        "PC is 0x1004",
        "CYCLES is 4",
        "A7 is 0x001000000",
        "USP is 0x00FFFFFF",
        "STOPPED is 1",
    });
}

TEST_F(STOPTest, SwitchToUser) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A7 is 0x001000000",
        "USP is 0x00FFFFFF",
        "STOPPED is 0",
    });
    When({
        "STOP #0x0001"
    });
    Then({
        "SR is 0,0,C",
        "PC is 0x1004",
        "CYCLES is 4",
        "A7 is 0x00FFFFFF",
        "SSP is 0x001000000",
        "STOPPED is 1",
    });
}

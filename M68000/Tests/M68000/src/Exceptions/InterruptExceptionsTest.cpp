#include "M68000/Fixtures/M68000Test.h"

class InterruptTest: public M68000Test {};

TEST_F(InterruptTest, MaskedInterruptsAreIgnored) {
    Given({
        "SR is 0,3,0",
        "PC is 0x1000",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "INT is 0,2,25",
        "(0x64).L is 0x00CC11AA",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "NOP"
    });
    Then({
        "SR is 0,3,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "(0x64).L is 0x00CC11AA",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
}

TEST_F(InterruptTest, MaskedInterruptsWithSameLevelAreIgnored) {
    Given({
        "SR is 0,3,0",
        "PC is 0x1000",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "INT is 0,3,25",
        "(0x64).L is 0x00CC11AA",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "NOP"
    });
    Then({
        "SR is 0,3,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "(0x64).L is 0x00CC11AA",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
}

TEST_F(InterruptTest, UnmaskedInterruptsAreAcknowledged) {
    Given({
        "SR is 0,3,0",
        "PC is 0x1000",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "INT is 0,4,25",
        "(0x64).L is 0x00CC11AA",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "NOP"
    });
    Then({
        "SR is S,4,0",
        "PC is 0x00CC11AA",
        "CYCLES is 48", // INT(44) + NOP(4)
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "(0x64).L is 0x00CC11AA",
        "(0x00FFFFFA).W is 0x0300",
        "(0x00FFFFFC).L is 0x00001002",
    });
}

TEST_F(InterruptTest, UnmaskedInterruptsAreAcknowledgedInSupervisorMode) {
    Given({
        "SR is S,3,0",
        "PC is 0x1000",
        "A7 is 0x01000000",
        "USP is 0x00FF0000",
        "INT is 0,4,26",
        "(0x68).L is 0x00CC11AA",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "NOP"
    });
    Then({
        "SR is S,4,0",
        "PC is 0x00CC11AA",
        "CYCLES is 48", // INT(44) + NOP(4)
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "(0x68).L is 0x00CC11AA",
        "(0x00FFFFFA).W is 0x2300",
        "(0x00FFFFFC).L is 0x00001002",
    });
}

TEST_F(InterruptTest, InterruptClearsStoppedFlag) {
    Given({
        "SR is S,3,0",
        "PC is 0x1000",
        "A7 is 0x01000000",
        "USP is 0x00FF0000",
        "STOPPED is 1",
        "INT is 0,4,26",
        "(0x68).L is 0x00CC11AA",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "NOP"
    });
    Then({
        "SR is S,4,0",
        "PC is 0x00CC11AA",
        "CYCLES is 48", // INT(44) + NOP(4)
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "STOPPED is 0",
        "(0x68).L is 0x00CC11AA",
        "(0x00FFFFFA).W is 0x2300",
        "(0x00FFFFFC).L is 0x00001000",
    });
}

TEST_F(InterruptTest, NonMaskableInterruptsAreEdgeTriggered) {
    Given({
        "SR is S,7,0",
        "PC is 0x1000",
        "A7 is 0x01000000",
        "USP is 0x00FF0000",
        "INT is 0,7,26",
        "(0x68).L is 0x00DDAACC",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "NOP"
    });
    Then({
        "SR is S,7,0",
        "PC is 0x00DDAACC",
        "CYCLES is 48", // INT(44) + NOP(4)
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "(0x68).L is 0x00DDAACC",
        "(0x00FFFFFA).W is 0x2700",
        "(0x00FFFFFC).L is 0x00001002",
    });
}

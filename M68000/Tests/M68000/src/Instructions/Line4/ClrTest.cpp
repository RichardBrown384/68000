#include "M68000/Fixtures/M68000Test.h"

class CLRTest : public M68000Test {};

TEST_F(CLRTest, RegisterCLRByteWorks) {
    Given({
        "SR is S,0,XNVC",
        "PC is 0x1000",
        "D1 is 0xFFFFFFFF",
    });
    When({
        "CLR.B D1"
    });
    Then({
        "SR is S,0,XZ",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0xFFFFFF00",
    });
}

TEST_F(CLRTest, RegisterCLRWordWorks) {
    Given({
        "SR is S,0,XNVC",
        "PC is 0x1000",
        "D1 is 0xFFFFFFFF",
    });
    When({
        "CLR.W D1"
    });
    Then({
        "SR is S,0,XZ",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0xFFFF0000",
    });
}

TEST_F(CLRTest, RegisterCLRLongWorks) {
    Given({
        "SR is S,0,XNVC",
        "PC is 0x1000",
        "D1 is 0xFFFFFFFF",
    });
    When({
        "CLR.L D1"
    });
    Then({
        "SR is S,0,XZ",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x00000000",
    });
}

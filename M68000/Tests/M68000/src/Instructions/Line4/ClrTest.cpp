#include "M68000/Fixtures/M68000Test.h"

class CLRTest : public M68000Test {};

TEST_F(CLRTest, RegisterCLRByteWorks) {
    Given({
        "D1 is 0xFFFFFFFF",
        "SR is S,0,XNVC"
    });
    When({
        "CLR.B D1"
    });
    Then({
        "D1 is 0xFFFFFF00",
        "SR is S,0,XZ"
    });
}

TEST_F(CLRTest, RegisterCLRWordWorks) {
    Given({
        "D1 is 0xFFFFFFFF",
        "SR is S,0,XNVC"
    });
    When({
        "CLR.W D1"
    });
    Then({
        "D1 is 0xFFFF0000",
        "SR is S,0,XZ"
    });
}

TEST_F(CLRTest, RegisterCLRLongWorks) {
    Given({
        "D1 is 0xFFFFFFFF",
        "SR is S,0,XNVC"
    });
    When({
        "CLR.L D1"
    });
    Then({
        "D1 is 0x00000000",
        "SR is S,0,XZ"
    });
}

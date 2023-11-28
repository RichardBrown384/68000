#include "M68000/Fixtures/M68000Test.h"

class LINKTest : public M68000Test {};

TEST_F(LINKTest, AddressRegister) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0xCAFECAFE",
        "A7 is 0x01000000",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "LINK A1, #-0x3000"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "A1 is 0x00FFFFFC",
        "A7 is 0x00FFCFFC",
        "(0x00FFFFFC).L is 0xCAFECAFE",
    });
}

TEST_F(LINKTest, StackPointer) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A7 is 0x01000000",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "LINK A7, #-0x3000"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "A7 is 0x00FFCFFC",
        "(0x00FFFFFC).L is 0x01000000",
    });
}

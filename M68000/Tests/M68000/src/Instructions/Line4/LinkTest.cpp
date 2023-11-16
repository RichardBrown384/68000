#include "M68000/Fixtures/M68000Test.h"

class LINKTest : public M68000Test {};

TEST_F(LINKTest, AddressRegister) {
    Given({
        "A1 is 0xCAFECAFE",
        "A7 is 0x01000000",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
        "SR is S,0,0"
    });
    When({
        "LINK A1, #-0x3000"
    });
    Then({
        "A1 is 0x00FFFFFC",
        "A7 is 0x00FFCFFC",
        "(0x00FFFFFC).L is 0xCAFECAFE",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(LINKTest, StackPointer) {
    Given({
        "A7 is 0x01000000",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
        "SR is S,0,0"
    });
    When({
        "LINK A7, #-0x3000"
    });
    Then({
        "A7 is 0x00FFCFFC",
        "(0x00FFFFFC).L is 0x01000000",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

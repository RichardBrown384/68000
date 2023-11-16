#include "M68000/Fixtures/M68000Test.h"

class UNLKTest : public M68000Test {};

TEST_F(UNLKTest, AddressRegister) {
    Given({
        "A1 is 0x00FFFFFC",
        "A7 is 0x00FFCFFC",
        "(0x00FFFFFC).L is 0xDEADBEEF",
        "SR is S,0,0"
    });
    When({
        "UNLK A1"
    });
    Then({
        "A1 is 0xDEADBEEF",
        "A7 is 0x01000000",
        "(0x00FFFFFC).L is 0xDEADBEEF",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(UNLKTest, StackPointer) {
    Given({
        "A7 is 0x00FFCFFC",
        "(0x00FFCFFC).L is 0xDECAFF00",
        "SR is S,0,0"
    });
    When({
        "UNLK A7"
    });
    Then({
        "A7 is 0xDECAFF00",
        "(0x00FFCFFC).L is 0xDECAFF00",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

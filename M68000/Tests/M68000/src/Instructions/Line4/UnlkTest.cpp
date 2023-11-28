#include "M68000/Fixtures/M68000Test.h"

class UNLKTest : public M68000Test {};

TEST_F(UNLKTest, AddressRegister) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x00FFFFFC",
        "A7 is 0x00FFCFFC",
        "(0x00FFFFFC).L is 0xDEADBEEF",
    });
    When({
        "UNLK A1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "A1 is 0xDEADBEEF",
        "A7 is 0x01000000",
        "(0x00FFFFFC).L is 0xDEADBEEF",
    });
}

TEST_F(UNLKTest, StackPointer) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A7 is 0x00FFCFFC",
        "(0x00FFCFFC).L is 0xDECAFF00",
    });
    When({
        "UNLK A7"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "A7 is 0xDECAFF00",
        "(0x00FFCFFC).L is 0xDECAFF00",
    });
}

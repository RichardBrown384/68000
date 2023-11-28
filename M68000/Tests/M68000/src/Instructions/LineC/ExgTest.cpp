#include "M68000/Fixtures/M68000Test.h"

class EXGTest : public M68000Test {};

TEST_F(EXGTest, DataRegisterWithDataRegister) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D2 is 0xBEADBEAD",
        "D3 is 0xDEEDDEED",
    });
    When({
        "EXG D2, D3"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 6",
        "D2 is 0xDEEDDEED",
        "D3 is 0xBEADBEAD",
    });
}

TEST_F(EXGTest, AddressRegisterWithAddressRegister) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A2 is 0xBEADBEAD",
        "A3 is 0xDEEDDEED",
    });
    When({
        "EXG A2, A3"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 6",
        "A2 is 0xDEEDDEED",
        "A3 is 0xBEADBEAD",
    });
}

TEST_F(EXGTest, DataRegisterWithAddressRegister) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xBEADBEAD",
        "A6 is 0xDEEDDEED",
    });
    When({
        "EXG D1, A6"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0xDEEDDEED",
        "A6 is 0xBEADBEAD",
    });
}

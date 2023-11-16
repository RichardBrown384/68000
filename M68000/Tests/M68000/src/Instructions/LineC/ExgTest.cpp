#include "M68000/Fixtures/M68000Test.h"

class EXGTest : public M68000Test {};

TEST_F(EXGTest, DataRegisterWithDataRegister) {
    Given({
        "D2 is 0xBEADBEAD",
        "D3 is 0xDEEDDEED",
        "SR is S,0,0"
    });
    When({
        "EXG D2, D3"
    });
    Then({
        "D2 is 0xDEEDDEED",
        "D3 is 0xBEADBEAD",
        "SR is S,0,0",
        "CYCLES is 6"
    });
}

TEST_F(EXGTest, AddressRegisterWithAddressRegister) {
    Given({
        "A2 is 0xBEADBEAD",
        "A3 is 0xDEEDDEED",
        "SR is S,0,0"
    });
    When({
        "EXG A2, A3"
    });
    Then({
        "A2 is 0xDEEDDEED",
        "A3 is 0xBEADBEAD",
        "SR is S,0,0",
        "CYCLES is 6"
    });
}

TEST_F(EXGTest, DataRegisterWithAddressRegister) {
    Given({
        "D1 is 0xBEADBEAD",
        "A6 is 0xDEEDDEED",
        "SR is S,0,0"
    });
    When({
        "EXG D1, A6"
    });
    Then({
        "D1 is 0xDEEDDEED",
        "A6 is 0xBEADBEAD",
        "SR is S,0,0",
        "CYCLES is 6"
    });
}

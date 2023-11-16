#include "M68000/Fixtures/M68000Test.h"

class LEATest : public M68000Test {};

TEST_F(LEATest, AddressRegisterIndirect) {
    Given({
        "A1 is 0xDEADBEEF",
        "A5 is 0xBBCBBBCB",
        "SR is S,0,0"
    });
    When({
        "LEA (A1), A5"
    });
    Then({
        "A1 is 0xDEADBEEF",
        "A5 is 0xDEADBEEF",
        "SR is S,0,0",
        "CYCLES is 4"
    });
}

TEST_F(LEATest, AddressRegisterIndirectDisplacement) {
    Given({
        "A1 is 0xDEADBE00",
        "A5 is 0xBBCBBBCB",
        "SR is S,0,0"
    });
    When({
        "LEA (0xEF, A1), A5"
    });
    Then({
        "A1 is 0xDEADBE00",
        "A5 is 0xDEADBEEF",
        "SR is S,0,0",
        "CYCLES is 8"
    });
}

TEST_F(LEATest, AddressRegisterIndirectIndex) {
    Given({
       "A1 is 0xDEADBE00",
       "A2 is 0x000000E0",
       "A5 is 0xAAAAAAAA",
       "SR is S,0,0"
    });
    When({
        "LEA (0xF, A1, A2.L), A5"
    });
    Then({
        "A1 is 0xDEADBE00",
        "A2 is 0x000000E0",
        "A5 is 0xDEADBEEF",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(LEATest, AbsoluteShort) {
    Given({
        "A5 is 0x55555555",
        "SR is S,0,0"
    });
    When({
        "LEA (0xBEEF).W, A5"
    });
    Then({
        "A5 is 0xFFFFBEEF",
        "SR is S,0,0",
        "CYCLES is 8"
    });
}

TEST_F(LEATest, AbsoluteLong) {
    Given({
        "A5 is 0x00BBCB00",
        "SR is S,0,0"
    });
    When({
        "LEA (0xDEADBEEF).L, A5"
    });
    Then({
        "A5 is 0xDEADBEEF",
        "SR is S,0,0"
    });
}

TEST_F(LEATest, PCDisplacement) {
    Given({
        "A5 is 0xBBCBBBCB",
        "SR is S,0,0"
    });
    When({
        "LEA (0x7E, PC), A5"
    });
    Then({
        "A5 is 0x00001080",
        "SR is S,0,0",
        "CYCLES is 8"
    });
}

TEST_F(LEATest, PCIndex) {
    Given({
       "A2 is 0x000000E0",
       "A5 is 0xAAAAAAAA",
       "SR is S,0,0"
    });
    When({
        "LEA (0xF, PC, A2.L), A5"
    });
    Then({
        "A2 is 0x000000E0",
        "A5 is 0x000010F1",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

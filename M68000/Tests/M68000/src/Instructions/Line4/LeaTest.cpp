#include "M68000/Fixtures/M68000Test.h"

class LEATest : public M68000Test {};

TEST_F(LEATest, AddressRegisterIndirect) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0xDEADBEEF",
        "A5 is 0xBBCBBBCB",
    });
    When({
        "LEA (A1), A5"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "A1 is 0xDEADBEEF",
        "A5 is 0xDEADBEEF",
    });
}

TEST_F(LEATest, AddressRegisterIndirectDisplacement) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0xDEADBE00",
        "A5 is 0xBBCBBBCB",
    });
    When({
        "LEA (0xEF, A1), A5"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 8",
        "A1 is 0xDEADBE00",
        "A5 is 0xDEADBEEF",
    });
}

TEST_F(LEATest, AddressRegisterIndirectIndex) {
    Given({
       "SR is S,0,0",
        "PC is 0x1000",
       "A1 is 0xDEADBE00",
       "A2 is 0x000000E0",
       "A5 is 0xAAAAAAAA",
    });
    When({
        "LEA (0xF, A1, A2.L), A5"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "A1 is 0xDEADBE00",
        "A2 is 0x000000E0",
        "A5 is 0xDEADBEEF",
    });
}

TEST_F(LEATest, AbsoluteShort) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A5 is 0x55555555",
    });
    When({
        "LEA (0xBEEF).W, A5"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 8",
        "A5 is 0xFFFFBEEF",
    });
}

TEST_F(LEATest, AbsoluteLong) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A5 is 0x00BBCB00",
    });
    When({
        "LEA (0xDEADBEEF).L, A5"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 12",
        "A5 is 0xDEADBEEF",
    });
}

TEST_F(LEATest, PCDisplacement) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A5 is 0xBBCBBBCB",
    });
    When({
        "LEA (0x7E, PC), A5"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 8",
        "A5 is 0x00001080",
    });
}

TEST_F(LEATest, PCIndex) {
    Given({
       "SR is S,0,0",
        "PC is 0x1000",
       "A2 is 0x000000E0",
       "A5 is 0xAAAAAAAA",
    });
    When({
        "LEA (0xF, PC, A2.L), A5"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "A2 is 0x000000E0",
        "A5 is 0x000010F1",
    });
}

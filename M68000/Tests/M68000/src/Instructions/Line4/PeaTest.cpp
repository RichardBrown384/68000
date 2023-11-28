#include "M68000/Fixtures/M68000Test.h"

class PEATest : public M68000Test {};

TEST_F(PEATest, AddressRegisterIndirect) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0xDEADBEEF",
        "A7 is 0x01000000",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "PEA (A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "A1 is 0xDEADBEEF",
        "A7 is 0x00FFFFFC",
        "(0x00FFFFFC).L is 0xDEADBEEF",
    });
}

TEST_F(PEATest, AddressRegisterIndirectDisplacement) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0xDEADBE00",
        "A7 is 0x01000000",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "PEA (0xEF, A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "A1 is 0xDEADBE00",
        "A7 is 0x00FFFFFC",
        "(0x00FFFFFC).L is 0xDEADBEEF",
    });
}

TEST_F(PEATest, AddressRegisterIndirectIndex) {
    Given({
       "SR is S,0,0",
        "PC is 0x1000",
       "A1 is 0xDEADBE00",
       "A2 is 0x000000E0",
       "A7 is 0x01000000",
       "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "PEA (0xF, A1, A2.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 20",
        "A1 is 0xDEADBE00",
        "A2 is 0x000000E0",
        "A7 is 0x00FFFFFC",
        "(0x00FFFFFC).L is 0xDEADBEEF",
    });
}

TEST_F(PEATest, AbsoluteShort) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A7 is 0x01000000",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "PEA (0xBEEF).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "A7 is 0x00FFFFFC",
        "(0x00FFFFFC).L is 0xFFFFBEEF",
    });
}

TEST_F(PEATest, AbsoluteLong) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A7 is 0x01000000",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "PEA (0xDEADBEEF).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 20",
        "A7 is 0x00FFFFFC",
        "(0x00FFFFFC).L is 0xDEADBEEF",
    });
}

TEST_F(PEATest, PCDisplacement) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A7 is 0x01000000",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "PEA (0xEE, PC)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "A7 is 0x00FFFFFC",
        "(0x00FFFFFC).L is 0x000010F0",
    });
}

TEST_F(PEATest, PCIndex) {
    Given({
       "SR is S,0,0",
        "PC is 0x1000",
       "A2 is 0x000000E0",
       "A7 is 0x01000000",
       "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "PEA (0x10, PC, A2.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 20",
        "A2 is 0x000000E0",
        "A7 is 0x00FFFFFC",
        "(0x00FFFFFC).L is 0x000010F2",
    });
}

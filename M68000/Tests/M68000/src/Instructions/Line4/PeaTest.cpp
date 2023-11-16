#include "M68000/Fixtures/M68000Test.h"

class PEATest : public M68000Test {};

TEST_F(PEATest, AddressRegisterIndirect) {
    Given({
        "A1 is 0xDEADBEEF",
        "A7 is 0x01000000",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
        "SR is S,0,0"
    });
    When({
        "PEA (A1)"
    });
    Then({
        "A1 is 0xDEADBEEF",
        "A7 is 0x00FFFFFC",
        "(0x00FFFFFC).L is 0xDEADBEEF",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(PEATest, AddressRegisterIndirectDisplacement) {
    Given({
        "A1 is 0xDEADBE00",
        "A7 is 0x01000000",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
        "SR is S,0,0"
    });
    When({
        "PEA (0xEF, A1)"
    });
    Then({
        "A1 is 0xDEADBE00",
        "A7 is 0x00FFFFFC",
        "(0x00FFFFFC).L is 0xDEADBEEF",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(PEATest, AddressRegisterIndirectIndex) {
    Given({
       "A1 is 0xDEADBE00",
       "A2 is 0x000000E0",
       "A7 is 0x01000000",
       "(0x00FFFFFC).L is 0xCDCDCDCD",
       "SR is S,0,0"
    });
    When({
        "PEA (0xF, A1, A2.L)"
    });
    Then({
        "A1 is 0xDEADBE00",
        "A2 is 0x000000E0",
        "A7 is 0x00FFFFFC",
        "(0x00FFFFFC).L is 0xDEADBEEF",
        "SR is S,0,0",
        "CYCLES is 20"
    });
}

TEST_F(PEATest, AbsoluteShort) {
    Given({
        "A7 is 0x01000000",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
        "SR is S,0,0"
    });
    When({
        "PEA (0xBEEF).W"
    });
    Then({
        "A7 is 0x00FFFFFC",
        "(0x00FFFFFC).L is 0xFFFFBEEF",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(PEATest, AbsoluteLong) {
    Given({
        "A7 is 0x01000000",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
        "SR is S,0,0"
    });
    When({
        "PEA (0xDEADBEEF).L"
    });
    Then({
        "A7 is 0x00FFFFFC",
        "(0x00FFFFFC).L is 0xDEADBEEF",
        "SR is S,0,0",
        "CYCLES is 20"
    });
}

TEST_F(PEATest, PCDisplacement) {
    Given({
        "A7 is 0x01000000",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
        "SR is S,0,0"
    });
    When({
        "PEA (0xEE, PC)"
    });
    Then({
        "A7 is 0x00FFFFFC",
        "(0x00FFFFFC).L is 0x000010F0",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(PEATest, PCIndex) {
    Given({
       "A2 is 0x000000E0",
       "A7 is 0x01000000",
       "(0x00FFFFFC).L is 0xCDCDCDCD",
       "SR is S,0,0"
    });
    When({
        "PEA (0x10, PC, A2.L)"
    });
    Then({
        "A2 is 0x000000E0",
        "A7 is 0x00FFFFFC",
        "(0x00FFFFFC).L is 0x000010F2",
        "SR is S,0,0",
        "CYCLES is 20"
    });
}
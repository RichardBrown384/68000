#include "M68000/Fixtures/M68000Test.h"

class JSRTest : public M68000Test {};

TEST_F(JSRTest, AddressRegisterIndirect) {
    Given({
        "A1 is 0xDCDCDCDC",
        "A7 is 0x01000000",
        "(0x00FFFFFC).L is 0xDEADBEEF",
        "SR is S,0,0"
    });
    When({
        "JSR (A1)"
    });
    Then({
        "A1 is 0xDCDCDCDC",
        "A7 is 0x00FFFFFC",
        "PC is 0xDCDCDCDC",
        "(0x00FFFFFC).L is 0x1002",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(JSRTest, AddressRegisterIndirectDisplacement) {
    Given({
        "A1 is 0xDCDCDC00",
        "A7 is 0x01000000",
        "(0x00FFFFFC).L is 0xDEADBEEF",
        "SR is S,0,0"
    });
    When({
        "JSR (0xDC, A1)"
    });
    Then({
        "A1 is 0xDCDCDC00",
        "A7 is 0x00FFFFFC",
        "PC is 0xDCDCDCDC",
        "(0x00FFFFFC).L is 0x1004",
        "SR is S,0,0",
        "CYCLES is 18"
    });
}

TEST_F(JSRTest, AddressRegisterIndirectIndex) {
    Given({
       "A1 is 0xDCDCDC00",
       "A2 is 0x000000D0",
       "A7 is 0x01000000",
       "(0x00FFFFFC).L is 0xDEADBEEF",
       "SR is S,0,0"
    });
    When({
        "JSR (0xC, A1, A2.L)"
    });
    Then({
        "A1 is 0xDCDCDC00",
        "A2 is 0x000000D0",
        "A7 is 0x00FFFFFC",
        "PC is 0xDCDCDCDC",
        "(0x00FFFFFC).L is 0x1004",
        "SR is S,0,0",
        "CYCLES is 22"
    });
}

TEST_F(JSRTest, AbsoluteShort) {
    Given({
        "A7 is 0x01000000",
        "(0x00FFFFFC).L is 0xDEADBEEF",
        "SR is S,0,0"
    });
    When({
        "JSR (0xDCDC).W"
    });
    Then({
        "A7 is 0x00FFFFFC",
        "PC is 0xFFFFDCDC",
        "(0x00FFFFFC).L is 0x1004",
        "SR is S,0,0",
        "CYCLES is 18"
    });
}

TEST_F(JSRTest, AbsoluteLong) {
    Given({
        "A7 is 0x01000000",
        "(0x00FFFFFC).L is 0xDEADBEEF",
        "SR is S,0,0"
    });
    When({
        "JSR (0xDCDCDCDC).L"
    });
    Then({
        "A7 is 0x00FFFFFC",
        "PC is 0xDCDCDCDC",
        "(0x00FFFFFC).L is 0x1006",
        "SR is S,0,0",
        "CYCLES is 20"
    });
}

TEST_F(JSRTest, PCDisplacement) {
    Given({
        "A7 is 0x01000000",
        "(0x00FFFFFC).L is 0xDEADBEEF",
        "SR is S,0,0"
    });
    When({
        "JSR (0xDC, PC)"
    });
    Then({
        "A7 is 0x00FFFFFC",
        "PC is 0x000010DE",
        "(0x00FFFFFC).L is 0x1004",
        "SR is S,0,0",
        "CYCLES is 18"
    });
}

TEST_F(JSRTest, PCIndirectIndex) {
    Given({
       "A2 is 0x000000D0",
       "A7 is 0x01000000",
       "(0x00FFFFFC).L is 0xDEADBEEF",
       "SR is S,0,0"
    });
    When({
        "JSR (0xC, PC, A2.L)"
    });
    Then({
        "A2 is 0x000000D0",
        "A7 is 0x00FFFFFC",
        "PC is 0x000010DE",
        "(0x00FFFFFC).L is 0x1004",
        "SR is S,0,0",
        "CYCLES is 22"
    });
}
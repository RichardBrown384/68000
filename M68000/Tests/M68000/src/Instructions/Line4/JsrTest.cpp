#include "M68000/Fixtures/M68000Test.h"

class JSRTest : public M68000Test {};

TEST_F(JSRTest, AddressRegisterIndirect) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0xDCDCDCDC",
        "A7 is 0x01000000",
        "(0x00FFFFFC).L is 0xDEADBEEF",
    });
    When({
        "JSR (A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0xDCDCDCDC",
        "CYCLES is 16",
        "A1 is 0xDCDCDCDC",
        "A7 is 0x00FFFFFC",
        "(0x00FFFFFC).L is 0x1002",
    });
}

TEST_F(JSRTest, AddressRegisterIndirectDisplacement) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0xDCDCDC00",
        "A7 is 0x01000000",
        "(0x00FFFFFC).L is 0xDEADBEEF",
    });
    When({
        "JSR (0xDC, A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0xDCDCDCDC",
        "CYCLES is 18",
        "A1 is 0xDCDCDC00",
        "A7 is 0x00FFFFFC",
        "(0x00FFFFFC).L is 0x1004",
    });
}

TEST_F(JSRTest, AddressRegisterIndirectIndex) {
    Given({
       "SR is S,0,0",
        "PC is 0x1000",
       "A1 is 0xDCDCDC00",
       "A2 is 0x000000D0",
       "A7 is 0x01000000",
       "(0x00FFFFFC).L is 0xDEADBEEF",
    });
    When({
        "JSR (0xC, A1, A2.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0xDCDCDCDC",
        "CYCLES is 22",
        "A1 is 0xDCDCDC00",
        "A2 is 0x000000D0",
        "A7 is 0x00FFFFFC",
        "(0x00FFFFFC).L is 0x1004",
    });
}

TEST_F(JSRTest, AbsoluteShort) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A7 is 0x01000000",
        "(0x00FFFFFC).L is 0xDEADBEEF",
    });
    When({
        "JSR (0xDCDC).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0xFFFFDCDC",
        "CYCLES is 18",
        "A7 is 0x00FFFFFC",
        "(0x00FFFFFC).L is 0x1004",
    });
}

TEST_F(JSRTest, AbsoluteLong) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A7 is 0x01000000",
        "(0x00FFFFFC).L is 0xDEADBEEF",
    });
    When({
        "JSR (0xDCDCDCDC).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0xDCDCDCDC",
        "CYCLES is 20",
        "A7 is 0x00FFFFFC",
        "(0x00FFFFFC).L is 0x1006",
    });
}

TEST_F(JSRTest, PCDisplacement) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A7 is 0x01000000",
        "(0x00FFFFFC).L is 0xDEADBEEF",
    });
    When({
        "JSR (0xDC, PC)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x000010DE",
        "CYCLES is 18",
        "A7 is 0x00FFFFFC",
        "(0x00FFFFFC).L is 0x1004",
    });
}

TEST_F(JSRTest, PCIndirectIndex) {
    Given({
       "SR is S,0,0",
        "PC is 0x1000",
       "A2 is 0x000000D0",
       "A7 is 0x01000000",
       "(0x00FFFFFC).L is 0xDEADBEEF",
    });
    When({
        "JSR (0xC, PC, A2.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x000010DE",
        "CYCLES is 22",
        "A2 is 0x000000D0",
        "A7 is 0x00FFFFFC",
        "(0x00FFFFFC).L is 0x1004",
    });
}

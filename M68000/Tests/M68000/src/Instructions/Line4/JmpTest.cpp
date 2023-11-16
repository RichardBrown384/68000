#include "M68000/Fixtures/M68000Test.h"

class JMPTest : public M68000Test {};

TEST_F(JMPTest, AddressRegisterIndirect) {
    Given({
        "A1 is 0xDCDCDCDC",
        "SR is S,0,0"
    });
    When({
        "JMP (A1)"
    });
    Then({
        "A1 is 0xDCDCDCDC",
        "PC is 0xDCDCDCDC",
        "SR is S,0,0",
        "CYCLES is 8"
    });
}

TEST_F(JMPTest, AddressRegisterIndirectDisplacement) {
    Given({
        "A1 is 0xDCDCDC00",
        "SR is S,0,0"
    });
    When({
        "JMP (0xDC, A1)"
    });
    Then({
        "A1 is 0xDCDCDC00",
        "PC is 0xDCDCDCDC",
        "SR is S,0,0",
        "CYCLES is 10"
    });
}

TEST_F(JMPTest, AddressRegisterIndirectIndex) {
    Given({
       "A1 is 0xDCDCDC00",
       "A2 is 0x000000D0",
       "SR is S,0,0"
    });
    When({
        "JMP (0xA, A1, A2.L)"
    });
    Then({
        "A1 is 0xDCDCDC00",
        "A2 is 0x000000D0",
        "PC is 0xDCDCDCDA",
        "SR is S,0,0",
        "CYCLES is 14"
    });
}

TEST_F(JMPTest, AbsoluteShort) {
    Given({
        "SR is S,0,0"
    });
    When({
        "JMP (0xDCDC).W"
    });
    Then({
        "PC is 0xFFFFDCDC",
        "SR is S,0,0",
        "CYCLES is 10"
    });
}

TEST_F(JMPTest, AbsoluteLong) {
    Given({
        "SR is S,0,0"
    });
    When({
        "JMP (0xBBCCBBCC).L"
    });
    Then({
        "PC is 0xBBCCBBCC",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(JMPTest, PCDisplacement) {
    Given({
        "SR is S,0,0"
    });
    When({
        "JMP (0x200, PC)"
    });
    Then({
        "PC is 0x1202",
        "SR is S,0,0",
        "CYCLES is 10"
    });
}

TEST_F(JMPTest, PCIndex) {
    Given({
        "A2 is 0x00000300",
        "SR is S,0,0"
    });
    When({
        "JMP (0x60, PC, A2.L)"
    });
    Then({
        "A2 is 0x00000300",
        "PC is 0x1362",
        "SR is S,0,0",
        "CYCLES is 14"
    });
}
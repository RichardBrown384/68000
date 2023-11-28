#include "M68000/Fixtures/M68000Test.h"

class JMPTest : public M68000Test {};

TEST_F(JMPTest, AddressRegisterIndirect) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0xDCDCDCDC",
    });
    When({
        "JMP (A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0xDCDCDCDC",
        "CYCLES is 8",
        "A1 is 0xDCDCDCDC",
    });
}

TEST_F(JMPTest, AddressRegisterIndirectDisplacement) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0xDCDCDC00",
    });
    When({
        "JMP (0xDC, A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0xDCDCDCDC",
        "CYCLES is 10",
        "A1 is 0xDCDCDC00",
    });
}

TEST_F(JMPTest, AddressRegisterIndirectIndex) {
    Given({
       "SR is S,0,0",
        "PC is 0x1000",
       "A1 is 0xDCDCDC00",
       "A2 is 0x000000D0",
    });
    When({
        "JMP (0xA, A1, A2.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0xDCDCDCDA",
        "CYCLES is 14",
        "A1 is 0xDCDCDC00",
        "A2 is 0x000000D0",
    });
}

TEST_F(JMPTest, AbsoluteShort) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
    });
    When({
        "JMP (0xDCDC).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0xFFFFDCDC",
        "CYCLES is 10",
    });
}

TEST_F(JMPTest, AbsoluteLong) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
    });
    When({
        "JMP (0xBBCCBBCC).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0xBBCCBBCC",
        "CYCLES is 12",
    });
}

TEST_F(JMPTest, PCDisplacement) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
    });
    When({
        "JMP (0x200, PC)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1202",
        "CYCLES is 10",
    });
}

TEST_F(JMPTest, PCIndex) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A2 is 0x00000300",
    });
    When({
        "JMP (0x60, PC, A2.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1362",
        "CYCLES is 14",
        "A2 is 0x00000300",
    });
}

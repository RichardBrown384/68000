#include "M68000/Fixtures/M68000Test.h"

class CHKTest : public M68000Test {};

TEST_F(CHKTest, WhenRegisterIsWithinBoundsItShouldNotRaiseAnException) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000008",
        "D2 is 0x00000007",
    });
    When({
        "CHK D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0x00000008",
        "D2 is 0x00000007",
    });
}

TEST_F(CHKTest, UpperSixteenBitsOfRegisterShouldBeIgnored) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000008",
        "D2 is 0xFFFF0007",
    });
    When({
        "CHK D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0x00000008",
        "D2 is 0xFFFF0007",
    });
}

TEST_F(CHKTest, EqualValuesShouldNotRaiseAnException) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000008",
        "D2 is 0x00000008",
    });
    When({
        "CHK D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0x00000008",
        "D2 is 0x00000008",
    });
}

TEST_F(CHKTest, AddressIndirectUserMode) {
    Given({
        "SR is 0,0,N",
        "PC is 0x1000",
        "D1 is 0x00000002",
        "A0 is 0x00004000",
        "(0x4000).W is 0x0003",
    });
    When({
        "CHK (A0), D1"
    });
    Then({
        "SR is 0,0,N",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x00000002",
        "A0 is 0x00004000",
        "(0x4000).W is 0x0003",
    });
}

TEST_F(CHKTest, AddressIncrementUserMode) {
    Given({
        "SR is 0,0,N",
        "PC is 0x1000",
        "D1 is 0x00000002",
        "A0 is 0x00004000",
        "(0x4000).W is 0x0003",
    });
    When({
        "CHK (A0)+, D1"
    });
    Then({
        "SR is 0,0,N",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x00000002",
        "A0 is 0x00004002",
        "(0x4000).W is 0x0003",
    });
}

TEST_F(CHKTest, AddressDecrementUserMode) {
    Given({
        "SR is 0,0,N",
        "PC is 0x1000",
        "D1 is 0x00000002",
        "A0 is 0x00004002",
        "(0x4000).W is 0x0003",
    });
    When({
        "CHK -(A0), D1"
    });
    Then({
        "SR is 0,0,N",
        "PC is 0x1002",
        "CYCLES is 16",
        "D1 is 0x00000002",
        "A0 is 0x00004000",
        "(0x4000).W is 0x0003",
    });
}

TEST_F(CHKTest, AddressDisplacementUserMode) {
    Given({
        "SR is 0,0,N",
        "PC is 0x1000",
        "D1 is 0x00000002",
        "A0 is 0x00004000",
        "(0x4002).W is 0x0003",
    });
    When({
        "CHK (0x2, A0), D1"
    });
    Then({
        "SR is 0,0,N",
        "PC is 0x1004",
        "CYCLES is 18",
        "D1 is 0x00000002",
        "A0 is 0x00004000",
        "(0x4002).W is 0x0003",
    });
}

TEST_F(CHKTest, AddressIndexUserMode) {
    Given({
        "SR is 0,0,N",
        "PC is 0x1000",
        "D1 is 0x00000002",
        "A0 is 0x00004000",
        "A1 is 0x00004000",
        "(0x8002).W is 0x0003",
    });
    When({
        "CHK (0x2, A0, A1.L), D1"
    });
    Then({
        "SR is 0,0,N",
        "PC is 0x1004",
        "CYCLES is 20",
        "D1 is 0x00000002",
        "A0 is 0x00004000",
        "(0x8002).W is 0x0003",
    });
}

TEST_F(CHKTest, ShortUserMode) {
    Given({
        "SR is 0,0,N",
        "PC is 0x1000",
        "D1 is 0x00000002",
        "(0x4000).W is 0x03",
    });
    When({
        "CHK (0x4000).W, D1"
    });
    Then({
        "SR is 0,0,N",
        "PC is 0x1004",
        "CYCLES is 18",
        "D1 is 0x00000002",
        "(0x4000).W is 0x03",
    });
}

TEST_F(CHKTest, LongUserMode) {
    Given({
        "SR is 0,0,N",
        "PC is 0x1000",
        "D1 is 0x00000002",
        "(0x00800000).W is 0x03",
    });
    When({
        "CHK (0x00800000).L, D1"
    });
    Then({
        "SR is 0,0,N",
        "PC is 0x1006",
        "CYCLES is 22",
        "D1 is 0x00000002",
        "(0x00800000).W is 0x03",
    });
}

TEST_F(CHKTest, PCDisplacementUserMode) {
    Given({
        "SR is 0,0,N",
        "PC is 0x1000",
        "D1 is 0x00000002",
        "(0x1202).W is 0x0003",
    });
    When({
        "CHK (0x200, PC), D1"
    });
    Then({
        "SR is 0,0,N",
        "PC is 0x1004",
        "CYCLES is 18",
        "D1 is 0x00000002",
        "(0x1202).W is 0x0003",
    });
}

TEST_F(CHKTest, PCIndexUserMode) {
    Given({
        "SR is 0,0,N",
        "PC is 0x1000",
        "D1 is 0x00000002",
        "A1 is 0x00000200",
        "(0x1204).W is 0x0003",
    });
    When({
        "CHK (0x2, PC, A1.L), D1"
    });
    Then({
        "SR is 0,0,N",
        "PC is 0x1004",
        "CYCLES is 20",
        "D1 is 0x00000002",
        "A1 is 0x00000200",
        "(0x1204).W is 0x0003",
    });
}

TEST_F(CHKTest, ImmediateUserMode) {
    Given({
        "SR is 0,0,N",
        "PC is 0x1000",
        "D1 is 0x00000002",
    });
    When({
        "CHK #3, D1"
    });
    Then({
        "SR is 0,0,N",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0x00000002",
    });
}

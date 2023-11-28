#include "M68000/Fixtures/M68000Test.h"

class TASTest : public M68000Test {};

TEST_F(TASTest, NonZeroDataRegisterDirect) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000008",
    });
    When({
        "TAS D1"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x00000088",
    });
}

TEST_F(TASTest, ZeroDataRegisterDirect) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000000",
    });
    When({
        "TAS D1"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x00000080",
    });
}

TEST_F(TASTest, Bit7SetDataRegisterDirect) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x00000080",
    });
    When({
        "TAS D1"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x00000080",
    });
}

TEST_F(TASTest, ExtendedFlagUnaffectedOverflowAndCarryClearedDataRegisterDirect) {
    Given({
        "SR is S,0,XVC",
        "PC is 0x1000",
        "D1 is 0x000000008",
    });
    When({
        "TAS D1"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x00000088",
    });
}

TEST_F(TASTest, AddressIndirect) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x2000",
        "(0x2000).B is 0x08",
    });
    When({
        "TAS (A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "A1 is 0x2000",
        "(0x2000).B is 0x88",
    });
}

TEST_F(TASTest, AddressIncrement) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x2000",
        "(0x2000).B is 0x08",
    });
    When({
        "TAS (A1)+"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "A1 is 0x2001",
        "(0x2000).B is 0x88",
    });
}

TEST_F(TASTest, AddressDecrement) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x2001",
        "(0x2000).B is 0x08",
    });
    When({
        "TAS -(A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 16",
        "A1 is 0x2000",
        "(0x2000).B is 0x88",
    });
}

TEST_F(TASTest, AddressDisplacement) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x2000",
        "(0x2001).B is 0x08",
    });
    When({
        "TAS (0x1, A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "A1 is 0x2000",
        "(0x2001).B is 0x88",
    });
}

TEST_F(TASTest, AddressIndex) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A1 is 0x2000",
        "A2 is 0x0001",
        "(0x2002).B is 0x08",
    });
    When({
        "TAS (0x1, A1, A2.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 20",
        "A1 is 0x2000",
        "A2 is 0x0001",
        "(0x2002).B is 0x88",
    });
}

TEST_F(TASTest, Short) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x2002).B is 0x08",
    });
    When({
        "TAS (0x2002).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "(0x2002).B is 0x88",
    });
}

TEST_F(TASTest, Long) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00102002).B is 0x08",
    });
    When({
        "TAS (0x00102002).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 22",
        "(0x00102002).B is 0x88",
    });
}

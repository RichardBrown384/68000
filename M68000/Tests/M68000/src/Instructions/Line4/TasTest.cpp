#include "M68000/Fixtures/M68000Test.h"

class TASTest : public M68000Test {};

TEST_F(TASTest, NonZeroDataRegisterDirect) {
    Given({
        "D1 is 0x00000008",
        "SR is S,0,0"
    });
    When({
        "TAS D1"
    });
    Then({
        "D1 is 0x00000088",
        "SR is S,0,0",
        "CYCLES is 4"
    });
}

TEST_F(TASTest, ZeroDataRegisterDirect) {
    Given({
        "D1 is 0x00000000",
        "SR is S,0,0"
    });
    When({
        "TAS D1"
    });
    Then({
        "D1 is 0x00000080",
        "SR is S,0,Z",
        "CYCLES is 4"
    });
}

TEST_F(TASTest, Bit7SetDataRegisterDirect) {
    Given({
        "D1 is 0x00000080",
        "SR is S,0,0"
    });
    When({
        "TAS D1"
    });
    Then({
        "D1 is 0x00000080",
        "SR is S,0,N",
        "CYCLES is 4"
    });
}

TEST_F(TASTest, ExtendedFlagUnaffectedOverflowAndCarryClearedDataRegisterDirect) {
    Given({
        "D1 is 0x000000008",
        "SR is S,0,XVC"
    });
    When({
        "TAS D1"
    });
    Then({
        "D1 is 0x00000088",
        "SR is S,0,X",
        "CYCLES is 4"
    });
}

TEST_F(TASTest, AddressIndirect) {
    Given({
        "A1 is 0x2000",
        "SR is S,0,0",
        "(0x2000).B is 0x08"
    });
    When({
        "TAS (A1)"
    });
    Then({
        "A1 is 0x2000",
        "(0x2000).B is 0x88",
        "SR is S,0,0",
        "CYCLES is 14"
    });
}

TEST_F(TASTest, AddressIncrement) {
    Given({
        "A1 is 0x2000",
        "SR is S,0,0",
        "(0x2000).B is 0x08"
    });
    When({
        "TAS (A1)+"
    });
    Then({
        "A1 is 0x2001",
        "(0x2000).B is 0x88",
        "SR is S,0,0",
        "CYCLES is 14"
    });
}

TEST_F(TASTest, AddressDecrement) {
    Given({
        "A1 is 0x2001",
        "SR is S,0,0",
        "(0x2000).B is 0x08"
    });
    When({
        "TAS -(A1)"
    });
    Then({
        "A1 is 0x2000",
        "(0x2000).B is 0x88",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}

TEST_F(TASTest, AddressDisplacement) {
    Given({
        "A1 is 0x2000",
        "SR is S,0,0",
        "(0x2001).B is 0x08"
    });
    When({
        "TAS (0x1, A1)"
    });
    Then({
        "A1 is 0x2000",
        "(0x2001).B is 0x88",
        "SR is S,0,0",
        "CYCLES is 18"
    });
}

TEST_F(TASTest, AddressIndex) {
    Given({
        "A1 is 0x2000",
        "A2 is 0x0001",
        "SR is S,0,0",
        "(0x2002).B is 0x08"
    });
    When({
        "TAS (0x1, A1, A2.L)"
    });
    Then({
        "A1 is 0x2000",
        "A2 is 0x0001",
        "(0x2002).B is 0x88",
        "SR is S,0,0",
        "CYCLES is 20"
    });
}

TEST_F(TASTest, Short) {
    Given({
        "SR is S,0,0",
        "(0x2002).B is 0x08"
    });
    When({
        "TAS (0x2002).W"
    });
    Then({
        "(0x2002).B is 0x88",
        "SR is S,0,0",
        "CYCLES is 18"
    });
}

TEST_F(TASTest, Long) {
    Given({
        "SR is S,0,0",
        "(0x00102002).B is 0x08"
    });
    When({
        "TAS (0x00102002).L"
    });
    Then({
        "(0x00102002).B is 0x88",
        "SR is S,0,0",
        "CYCLES is 22"
    });
}

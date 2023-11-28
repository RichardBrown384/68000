#include "M68000/Fixtures/M68000Test.h"

class MoveToCCRTest : public M68000Test {};

TEST_F(MoveToCCRTest, DataRegister) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0xCDCDCD15",
    });
    When({
        "MOVE.W D1, CCR"
    });
    Then({
        "SR is S,0,XZC",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0xCDCDCD15",
    });
}

TEST_F(MoveToCCRTest, AddressIndirect) {
    Given({
        "SR is 0,0,N",
        "PC is 0x1000",
        "A0 is 0x00004000",
        "(0x4000).W is 0xFF15",
    });
    When({
        "MOVE.W (A0), CCR"
    });
    Then({
        "SR is 0,0,XZC",
        "PC is 0x1002",
        "CYCLES is 16",
        "A0 is 0x00004000",
        "(0x4000).W is 0xFF15",
    });
}

TEST_F(MoveToCCRTest, AddressIncrement) {
    Given({
        "SR is 0,0,N",
        "PC is 0x1000",
        "A0 is 0x00004000",
        "(0x4000).W is 0xFF15",
    });
    When({
        "MOVE.W (A0)+, CCR"
    });
    Then({
        "SR is 0,0,XZC",
        "PC is 0x1002",
        "CYCLES is 16",
        "A0 is 0x00004002",
        "(0x4000).W is 0xFF15",
    });
}

TEST_F(MoveToCCRTest, AddressDecrement) {
    Given({
        "SR is 0,0,N",
        "PC is 0x1000",
        "A0 is 0x00004002",
        "(0x4000).W is 0xFF15",
    });
    When({
        "MOVE.W -(A0), CCR"
    });
    Then({
        "SR is 0,0,XZC",
        "PC is 0x1002",
        "CYCLES is 18",
        "A0 is 0x00004000",
        "(0x4000).W is 0xFF15",
    });
}

TEST_F(MoveToCCRTest, AddressDisplacement) {
    Given({
        "SR is 0,0,N",
        "PC is 0x1000",
        "A0 is 0x00004000",
        "(0x4002).W is 0xFF15",
    });
    When({
        "MOVE.W (0x2, A0), CCR"
    });
    Then({
        "SR is 0,0,XZC",
        "PC is 0x1004",
        "CYCLES is 20",
        "A0 is 0x00004000",
        "(0x4002).W is 0xFF15",
    });
}

TEST_F(MoveToCCRTest, AddressIndex) {
    Given({
        "SR is 0,0,N",
        "PC is 0x1000",
        "A0 is 0x00004000",
        "A1 is 0x00004000",
        "(0x8002).W is 0xFF15",
    });
    When({
        "MOVE.W (0x2, A0, A1.L), CCR"
    });
    Then({
        "SR is 0,0,XZC",
        "PC is 0x1004",
        "CYCLES is 22",
        "A0 is 0x00004000",
        "(0x8002).W is 0xFF15",
    });
}

TEST_F(MoveToCCRTest, Short) {
    Given({
        "SR is 0,0,N",
        "PC is 0x1000",
        "(0x4000).W is 0xFF15",
    });
    When({
        "MOVE.W (0x4000).W, CCR"
    });
    Then({
        "SR is 0,0,XZC",
        "PC is 0x1004",
        "CYCLES is 20",
        "(0x4000).W is 0xFF15",
    });
}

TEST_F(MoveToCCRTest, Long) {
    Given({
        "SR is 0,0,N",
        "PC is 0x1000",
        "(0x00800000).W is 0xFF15",
    });
    When({
        "MOVE.W (0x00800000).L, CCR"
    });
    Then({
        "SR is 0,0,XZC",
        "PC is 0x1006",
        "CYCLES is 24",
        "(0x00800000).W is 0xFF15",
    });
}

TEST_F(MoveToCCRTest, PCDisplacement) {
    Given({
        "SR is 0,0,N",
        "PC is 0x1000",
        "(0x1202).W is 0xFF15",
    });
    When({
        "MOVE.W (0x200, PC), CCR"
    });
    Then({
        "SR is 0,0,XZC",
        "PC is 0x1004",
        "CYCLES is 20",
        "(0x1202).W is 0xFF15",
    });
}

TEST_F(MoveToCCRTest, PCIndex) {
    Given({
        "SR is 0,0,N",
        "PC is 0x1000",
        "A1 is 0x00000200",
        "(0x1204).W is 0xFF15",
    });
    When({
        "MOVE.W (0x2, PC, A1.L), CCR"
    });
    Then({
        "SR is 0,0,XZC",
        "PC is 0x1004",
        "CYCLES is 22",
        "A1 is 0x00000200",
        "(0x1204).W is 0xFF15",
    });
}

TEST_F(MoveToCCRTest, Immediate) {
    Given({
        "SR is 0,0,N",
        "PC is 0x1000",
    });
    When({
        "MOVE.W #0xFF15, CCR"
    });
    Then({
        "SR is 0,0,XZC",
        "PC is 0x1004",
        "CYCLES is 16",
    });
}

#include "M68000/Fixtures/M68000Test.h"

class MoveToSRTest : public M68000Test {};

TEST_F(MoveToSRTest, DataRegisterPreserveSupervisorMode) {
    Given({
        "SR is S,0,0",
        "D1 is 0xCDCD2015",
        "A7 is 0x01000000",
        "USP is 0x00FF0000",
    });
    When({
        "MOVE.W D1, SR"
    });
    Then({
        "SR is S,0,XZC",
        "D1 is 0xCDCD2015",
        "A7 is 0x01000000",
        "USP is 0x00FF0000",
        "CYCLES is 12",
    });
}

TEST_F(MoveToSRTest, DataRegisterTransitionToUserMode) {
    Given({
        "SR is S,0,0",
        "D1 is 0xCDCD0015",
        "A7 is 0x01000000",
        "USP is 0x00FF0000",
    });
    When({
        "MOVE.W D1, SR"
    });
    Then({
        "SR is 0,0,XZC",
        "D1 is 0xCDCD0015",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "CYCLES is 12"
    });
}

TEST_F(MoveToSRTest, AddressIndirect) {
    Given({
        "SR is S,0,N",
        "A0 is 0x00004000",
        "(0x4000).W is 0x2715"
    });
    When({
        "MOVE.W (A0), SR"
    });
    Then({
        "SR is S,7,XZC",
        "A0 is 0x00004000",
        "(0x4000).W is 0x2715",
        "PC is 0x1002",
        "CYCLES is 16"
    });
}

TEST_F(MoveToSRTest, AddressIncrement) {
    Given({
        "SR is S,0,N",
        "A0 is 0x00004000",
        "(0x4000).W is 0x2715"
    });
    When({
        "MOVE.W (A0)+, SR"
    });
    Then({
        "SR is S,7,XZC",
        "A0 is 0x00004002",
        "(0x4000).W is 0x2715",
        "PC is 0x1002",
        "CYCLES is 16"
    });
}

TEST_F(MoveToSRTest, AddressDecrement) {
    Given({
        "SR is S,0,N",
        "A0 is 0x00004002",
        "(0x4000).W is 0x2715"
    });
    When({
        "MOVE.W -(A0), SR"
    });
    Then({
        "SR is S,7,XZC",
        "A0 is 0x00004000",
        "(0x4000).W is 0x2715",
        "PC is 0x1002",
        "CYCLES is 18"
    });
}

TEST_F(MoveToSRTest, AddressDisplacement) {
    Given({
        "SR is S,0,N",
        "A0 is 0x00004000",
        "(0x4002).W is 0x2715"
    });
    When({
        "MOVE.W (0x2, A0), SR"
    });
    Then({
        "SR is S,7,XZC",
        "A0 is 0x00004000",
        "(0x4002).W is 0x2715",
        "PC is 0x1004",
        "CYCLES is 20"
    });
}

TEST_F(MoveToSRTest, AddressIndex) {
    Given({
        "SR is S,0,N",
        "A0 is 0x00004000",
        "A1 is 0x00004000",
        "(0x8002).W is 0x2715"
    });
    When({
        "MOVE.W (0x2, A0, A1.L), SR"
    });
    Then({
        "SR is S,7,XZC",
        "A0 is 0x00004000",
        "(0x8002).W is 0x2715",
        "PC is 0x1004",
        "CYCLES is 22"
    });
}

TEST_F(MoveToSRTest, Short) {
    Given({
        "SR is S,0,N",
        "(0x4000).W is 0x2715"
    });
    When({
        "MOVE.W (0x4000).W, SR"
    });
    Then({
        "SR is S,7,XZC",
        "(0x4000).W is 0x2715",
        "PC is 0x1004",
        "CYCLES is 20"
    });
}

TEST_F(MoveToSRTest, Long) {
    Given({
        "SR is S,0,N",
        "(0x00800000).W is 0x2715"
    });
    When({
        "MOVE.W (0x00800000).L, SR"
    });
    Then({
        "SR is S,7,XZC",
        "(0x00800000).W is 0x2715",
        "PC is 0x1006",
        "CYCLES is 24"
    });
}

TEST_F(MoveToSRTest, PCDisplacement) {
    Given({
        "SR is S,0,N",
        "(0x1202).W is 0x2715"
    });
    When({
        "MOVE.W (0x200, PC), SR"
    });
    Then({
        "SR is S,7,XZC",
        "(0x1202).W is 0x2715",
        "PC is 0x1004",
        "CYCLES is 20"
    });
}

TEST_F(MoveToSRTest, PCIndex) {
    Given({
        "SR is S,0,N",
        "A1 is 0x00000200",
        "(0x1204).W is 0x2715"
    });
    When({
        "MOVE.W (0x2, PC, A1.L), SR"
    });
    Then({
        "SR is S,7,XZC",
        "A1 is 0x00000200",
        "(0x1204).W is 0x2715",
        "PC is 0x1004",
        "CYCLES is 22"
    });
}

TEST_F(MoveToSRTest, Immediate) {
    Given({
        "SR is S,0,N",
    });
    When({
        "MOVE.W #0x2715, SR"
    });
    Then({
        "SR is S,7,XZC",
        "PC is 0x1004",
        "CYCLES is 16"
    });
}

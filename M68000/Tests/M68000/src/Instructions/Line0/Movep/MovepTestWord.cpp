#include "M68000/Fixtures/M68000Test.h"

class MOVEPTestWord : public M68000Test {};

TEST_F(MOVEPTestWord, MoveToMemoryEvenAddress) {
    Given({
        "D1 is 0xAABBCCDD",
        "A1 is 0x00002000",
        "(0x00002000).L is 0xEEEEEEEE",
        "SR is S,0,0"
    });
    When({
        "MOVEP.W D1, (0, A1)"
    });
    Then({
        "D1 is 0xAABBCCDD",
        "A1 is 0x00002000",
        "(0x00002000).L is 0xCCEEDDEE",
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16"
    });
}

TEST_F(MOVEPTestWord, MoveToMemoryOddAddress) {
    Given({
        "D1 is 0xAABBCCDD",
        "A1 is 0x00002000",
        "(0x00002000).L is 0xEEEEEEEE",
        "SR is S,0,0"
    });
    When({
        "MOVEP.W D1, (1, A1)"
    });
    Then({
        "D1 is 0xAABBCCDD",
        "A1 is 0x00002000",
        "(0x00002000).L is 0xEECCEEDD",
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16"
    });
}

TEST_F(MOVEPTestWord, MoveToRegisterEvenAddress) {
    Given({
        "D1 is 0x55555555",
        "A1 is 0x00002000",
        "(0x00002000).L is 0xAABBCCDD",
        "SR is S,0,0"
    });
    When({
        "MOVEP.W (0, A1), D1"
    });
    Then({
        "D1 is 0x5555AACC",
        "A1 is 0x00002000",
        "(0x00002000).L is 0xAABBCCDD",
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16"
    });
}

TEST_F(MOVEPTestWord, MoveToRegisterOddAddress) {
    Given({
        "D1 is 0x55555555",
        "A1 is 0x00002000",
        "(0x00002000).L is 0xAABBCCDD",
        "SR is S,0,0"
    });
    When({
        "MOVEP.W (1, A1), D1"
    });
    Then({
        "D1 is 0x5555BBDD",
        "A1 is 0x00002000",
        "(0x00002000).L is 0xAABBCCDD",
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16"
    });
}

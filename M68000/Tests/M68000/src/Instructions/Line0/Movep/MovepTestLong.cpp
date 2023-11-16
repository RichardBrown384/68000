#include "M68000/Fixtures/M68000Test.h"

class MOVEPTestLong : public M68000Test {};

TEST_F(MOVEPTestLong, MoveToMemoryEvenAddress) {
    Given({
        "D1 is 0xAABBCCDD",
        "A1 is 0x00002000",
        "(0x00002000).L is 0xEEEEEEEE",
        "(0x00002004).L is 0xEEEEEEEE",
        "SR is S,0,0"
    });
    When({
        "MOVEP.L D1, (0, A1)"
    });
    Then({
        "D1 is 0xAABBCCDD",
        "A1 is 0x00002000",
        "(0x00002000).L is 0xAAEEBBEE",
        "(0x00002004).L is 0xCCEEDDEE",
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 24"
    });
}

TEST_F(MOVEPTestLong, MoveToMemoryOddAddress) {
    Given({
        "D1 is 0xAABBCCDD",
        "A1 is 0x00002000",
        "(0x00002000).L is 0xEEEEEEEE",
        "(0x00002004).L is 0xEEEEEEEE",
        "SR is S,0,0"
    });
    When({
        "MOVEP.L D1, (1, A1)"
    });
    Then({
        "D1 is 0xAABBCCDD",
        "A1 is 0x00002000",
        "(0x00002000).L is 0xEEAAEEBB",
        "(0x00002004).L is 0xEECCEEDD",
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 24"
    });
}

TEST_F(MOVEPTestLong, MoveToRegisterEvenAddress) {
    Given({
        "D1 is 0x55555555",
        "A1 is 0x00002000",
        "(0x00002000).L is 0xAABBCCDD",
        "(0x00002004).L is 0x66778899",
        "SR is S,0,0"
    });
    When({
        "MOVEP.L (0, A1), D1"
    });
    Then({
        "D1 is 0xAACC6688",
        "A1 is 0x00002000",
        "(0x00002000).L is 0xAABBCCDD",
        "(0x00002004).L is 0x66778899",
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 24"
    });
}

TEST_F(MOVEPTestLong, MoveToRegisterOddAddress) {
    Given({
        "D1 is 0x55555555",
        "A1 is 0x00002000",
        "(0x00002000).L is 0xAABBCCDD",
        "(0x00002004).L is 0x66778899",
        "SR is S,0,0"
    });
    When({
        "MOVEP.L (1, A1), D1"
    });
    Then({
        "D1 is 0xBBDD7799",
        "A1 is 0x00002000",
        "(0x00002000).L is 0xAABBCCDD",
        "(0x00002004).L is 0x66778899",
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 24"
    });
}

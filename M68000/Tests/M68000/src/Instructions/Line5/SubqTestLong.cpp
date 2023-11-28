#include "M68000/Fixtures/M68000Test.h"

class SUBQTestLong : public M68000Test {};

TEST_F(SUBQTestLong, DataDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x01000004",
    });
    When({
        "SUBQ.L #0x00000006, D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D4 is 0x00FFFFFE",
    });
}

TEST_F(SUBQTestLong, DataDirectSub8Works) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x700F0006",
    });
    When({
        "SUBQ.L #0x08, D4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "D4 is 0x700EFFFE",
    });
}

TEST_F(SUBQTestLong, DataDirectFlagNWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0xF000FFFF",
    });
    When({
        "SUBQ.L #0x01, D4"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 8",
        "D4 is 0xF000FFFE",
    });
}

TEST_F(SUBQTestLong, DataDirectFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x00000001",
    });
    When({
        "SUBQ.L #0x01, D4"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 8",
        "D4 is 0x00000000",
    });
}

TEST_F(SUBQTestLong, DataDirectFlagVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x80000000",
    });
    When({
        "SUBQ.L #0x01, D4"
    });
    Then({
        "SR is S,0,V",
        "PC is 0x1002",
        "CYCLES is 8",
        "D4 is 0x7FFFFFFF",
    });
}

TEST_F(SUBQTestLong, DataDirectFlagCWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D4 is 0x00000001",
    });
    When({
        "SUBQ.L #0x02, D4"
    });
    Then({
        "SR is S,0,XNC",
        "PC is 0x1002",
        "CYCLES is 8",
        "D4 is 0xFFFFFFFF",
    });
}

TEST_F(SUBQTestLong, AddressDirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x01000004",
    });
    When({
        "SUBQ.L #0x00000006, A4"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 8",
        "A4 is 0x00FFFFFE",
    });
}

TEST_F(SUBQTestLong, AddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).L is 0x01000004",
    });
    When({
        "SUBQ.L #0x00000006, (A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 20",
        "A4 is 0x00006000",
        "(0x00006000).L is 0x00FFFFFE",
    });
}

TEST_F(SUBQTestLong, AddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00006000).L is 0x01000004",
    });
    When({
        "SUBQ.L #0x00000006, (A4)+"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 20",
        "A4 is 0x00006004",
        "(0x00006000).L is 0x00FFFFFE",
    });
}

TEST_F(SUBQTestLong, AddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x00005FFC).L is 0x01000004",
    });
    When({
        "SUBQ.L #0x00000006, -(A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 22",
        "A4 is 0x00005FFC",
        "(0x00005FFC).L is 0x00FFFFFE",
    });
}

TEST_F(SUBQTestLong, AddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x01000004",
    });
    When({
        "SUBQ.L #0x00000006, (0x004C, A4)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 24",
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x00FFFFFE",
    });
}

TEST_F(SUBQTestLong, AddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0x01000004",
    });
    When({
        "SUBQ.L #0x00000006, (0x6E, A4, A5.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 26",
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0x00FFFFFE",
    });
}

TEST_F(SUBQTestLong, ShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).L is 0x01000004",
    });
    When({
        "SUBQ.L #0x00000006, (0x6000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 24",
        "(0x00006000).L is 0x00FFFFFE",
    });
}

TEST_F(SUBQTestLong, LongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "(0x00006000).L is 0x01000004",
    });
    When({
        "SUBQ.L #0x00000006, (0x00006000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 28",
        "(0x00006000).L is 0x00FFFFFE",
    });
}

#include "M68000/Fixtures/M68000Test.h"

class SUBQTestLong : public M68000Test {};

TEST_F(SUBQTestLong, DataDirectWorks) {
    Given({
        "D4 is 0x01000004",
        "SR is S,0,0"
    });
    When({
        "SUBQ.L #0x00000006, D4"
    });
    Then({
        "D4 is 0x00FFFFFE",
        "SR is S,0,0"
    });
}

TEST_F(SUBQTestLong, DataDirectSub8Works) {
    Given({
        "D4 is 0x700F0006",
        "SR is S,0,0"
    });
    When({
        "SUBQ.L #0x08, D4"
    });
    Then({
        "D4 is 0x700EFFFE",
        "SR is S,0,0"
    });
}

TEST_F(SUBQTestLong, DataDirectFlagNWorks) {
    Given({
        "D4 is 0xF000FFFF",
        "SR is S,0,0"
    });
    When({
        "SUBQ.L #0x01, D4"
    });
    Then({
        "D4 is 0xF000FFFE",
        "SR is S,0,N"
    });
}

TEST_F(SUBQTestLong, DataDirectFlagZWorks) {
    Given({
        "D4 is 0x00000001",
        "SR is S,0,0"
    });
    When({
        "SUBQ.L #0x01, D4"
    });
    Then({
        "D4 is 0x00000000",
        "SR is S,0,Z"
    });
}

TEST_F(SUBQTestLong, DataDirectFlagVWorks) {
    Given({
        "D4 is 0x80000000",
        "SR is S,0,0"
    });
    When({
        "SUBQ.L #0x01, D4"
    });
    Then({
        "D4 is 0x7FFFFFFF",
        "SR is S,0,V"
    });
}

TEST_F(SUBQTestLong, DataDirectFlagCWorks) {
    Given({
        "D4 is 0x00000001",
        "SR is S,0,0"
    });
    When({
        "SUBQ.L #0x02, D4"
    });
    Then({
        "D4 is 0xFFFFFFFF",
        "SR is S,0,XNC"
    });
}

TEST_F(SUBQTestLong, AddressDirectWorks) {
    Given({
        "A4 is 0x01000004",
        "SR is S,0,0"
    });
    When({
        "SUBQ.L #0x00000006, A4"
    });
    Then({
        "A4 is 0x00FFFFFE",
        "SR is S,0,0"
    });
}

TEST_F(SUBQTestLong, AddressIndirectWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).L is 0x01000004",
        "SR is S,0,0"
    });
    When({
        "SUBQ.L #0x00000006, (A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x00006000).L is 0x00FFFFFE",
        "SR is S,0,0"
    });
}

TEST_F(SUBQTestLong, AddressIncrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00006000).L is 0x01000004",
        "SR is S,0,0"
    });
    When({
        "SUBQ.L #0x00000006, (A4)+"
    });
    Then({
        "A4 is 0x00006004",
        "(0x00006000).L is 0x00FFFFFE",
        "SR is S,0,0"
    });
}

TEST_F(SUBQTestLong, AddressDecrementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x00005FFC).L is 0x01000004",
        "SR is S,0,0"
    });
    When({
        "SUBQ.L #0x00000006, -(A4)"
    });
    Then({
        "A4 is 0x00005FFC",
        "(0x00005FFC).L is 0x00FFFFFE",
        "SR is S,0,0"
    });
}

TEST_F(SUBQTestLong, AddressDisplacementWorks) {
    Given({
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x01000004",
        "SR is S,0,0"
    });
    When({
        "SUBQ.L #0x00000006, (0x004C, A4)"
    });
    Then({
        "A4 is 0x00006000",
        "(0x0000604C).L is 0x00FFFFFE",
        "SR is S,0,0"
    });
}

TEST_F(SUBQTestLong, AddressIndexWorks) {
    Given({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0x01000004",
        "SR is S,0,0"
    });
    When({
        "SUBQ.L #0x00000006, (0x6E, A4, A5.L)"
    });
    Then({
        "A4 is 0x00006000",
        "A5 is 0x00000020",
        "(0x0000608E).L is 0x00FFFFFE",
        "SR is S,0,0"
    });
}

TEST_F(SUBQTestLong, ShortWorks) {
    Given({
        "(0x00006000).L is 0x01000004",
        "SR is S,0,0"
    });
    When({
        "SUBQ.L #0x00000006, (0x6000).W"
    });
    Then({
        "(0x00006000).L is 0x00FFFFFE",
        "SR is S,0,0"
    });
}

TEST_F(SUBQTestLong, LongWorks) {
    Given({
        "(0x00006000).L is 0x01000004",
        "SR is S,0,0"
    });
    When({
        "SUBQ.L #0x00000006, (0x00006000).L"
    });
    Then({
        "(0x00006000).L is 0x00FFFFFE",
        "SR is S,0,0"
    });
}

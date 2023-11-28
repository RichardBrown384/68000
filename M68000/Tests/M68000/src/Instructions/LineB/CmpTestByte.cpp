#include "M68000/Fixtures/M68000Test.h"

class CMPTestByte : public M68000Test {};

TEST_F(CMPTestByte, DataRegisterDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01010120",
        "D2 is 0x719121E3",
    });
    When({
        "CMP.B D1, D2"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01010120",
        "D2 is 0x719121E3",
    });
}

TEST_F(CMPTestByte, DataRegisterDataRegisterFlagNVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01010180",
        "D2 is 0x71912132",
    });
    When({
        "CMP.B D1, D2"
    });
    Then({
        "SR is S,0,NVC",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01010180",
        "D2 is 0x71912132",
    });
}

TEST_F(CMPTestByte, DataRegisterDataRegisterFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x01A18061",
        "D2 is 0x01019A61",
    });
    When({
        "CMP.B D1, D2"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01A18061",
        "D2 is 0x01019A61",
    });
}

TEST_F(CMPTestByte, DataRegisterDataRegisterFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0x0101A101",
        "D2 is 0x01010B03",
    });
    When({
        "CMP.B D1, D2"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x0101A101",
        "D2 is 0x01010B03",
    });
}

TEST_F(CMPTestByte, AddressIndirectDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0A01B003",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x75",
    });
    When({
        "CMP.B (A1), D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x0A01B003",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x75",
    });
}

TEST_F(CMPTestByte, AddressIncrementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0A01B003",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x75",
    });
    When({
        "CMP.B (A1)+, D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1002",
        "CYCLES is 8",
        "D1 is 0x0A01B003",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x75",
    });
}

TEST_F(CMPTestByte, AddressDecrementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0A01B003",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x75",
    });
    When({
        "CMP.B -(A1), D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1002",
        "CYCLES is 10",
        "D1 is 0x0A01B003",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x75",
    });
}

TEST_F(CMPTestByte, AddressDisplacementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0A01B003",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x75",
    });
    When({
        "CMP.B (2, A1), D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x0A01B003",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x75",
    });
}

TEST_F(CMPTestByte, AddressIndexDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0A01B003",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x75",
    });
    When({
        "CMP.B (2, A1, A2.L), D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0x0A01B003",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x75",
    });
}

TEST_F(CMPTestByte, ShortDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0A01B003",
        "(0x00004000).B is 0x75",
    });
    When({
        "CMP.B (0x4000).W, D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x0A01B003",
        "(0x00004000).B is 0x75",
    });
}

TEST_F(CMPTestByte, LongDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0A01B003",
        "(0x00008000).B is 0x75",
    });
    When({
        "CMP.B (0x8000).L, D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1006",
        "CYCLES is 16",
        "D1 is 0x0A01B003",
        "(0x00008000).B is 0x75",
    });
}

TEST_F(CMPTestByte, PCDisplacementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0A01B003",
        "(0x00001060).B is 0x75",
    });
    When({
        "CMP.B (0x5E, PC), D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x0A01B003",
        "(0x00001060).B is 0x75",
    });
}

TEST_F(CMPTestByte, PCIndexDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0A01B003",
        "A1 is 0x00000010",
        "(0x00001070).B is 0x75",
    });
    When({
        "CMP.B (0x5E, PC, A1.L), D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0x0A01B003",
        "A1 is 0x00000010",
        "(0x00001070).B is 0x75",
    });
}

TEST_F(CMPTestByte, ImmediateDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0A01B003",
    });
    When({
        "CMP.B #0x75, D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1004",
        "CYCLES is 8",
        "D1 is 0x0A01B003",
    });
}

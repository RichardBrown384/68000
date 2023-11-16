#include "M68000/Fixtures/M68000Test.h"

class CMPTestByte : public M68000Test {};

TEST_F(CMPTestByte, DataRegisterDataRegisterWorks) {
    Given({
        "D1 is 0x01010120",
        "D2 is 0x719121E3",
        "SR is S,0,0"
    });
    When({
        "CMP.B D1, D2"
    });
    Then({
        "D1 is 0x01010120",
        "D2 is 0x719121E3",
        "SR is S,0,N"
    });
}

TEST_F(CMPTestByte, DataRegisterDataRegisterFlagNVWorks) {
    Given({
        "D1 is 0x01010180",
        "D2 is 0x71912132",
        "SR is S,0,0"
    });
    When({
        "CMP.B D1, D2"
    });
    Then({
        "D1 is 0x01010180",
        "D2 is 0x71912132",
        "SR is S,0,NVC"
    });
}

TEST_F(CMPTestByte, DataRegisterDataRegisterFlagZWorks) {
    Given({
        "D1 is 0x01A18061",
        "D2 is 0x01019A61",
        "SR is S,0,0"
    });
    When({
        "CMP.B D1, D2"
    });
    Then({
        "D1 is 0x01A18061",
        "D2 is 0x01019A61",
        "SR is S,0,Z"
    });
}

TEST_F(CMPTestByte, DataRegisterDataRegisterFlagXWorks) {
    Given({
        "D1 is 0x0101A101",
        "D2 is 0x01010B03",
        "SR is S,0,X"
    });
    When({
        "CMP.B D1, D2"
    });
    Then({
        "D1 is 0x0101A101",
        "D2 is 0x01010B03",
        "SR is S,0,X"
    });
}

TEST_F(CMPTestByte, AddressIndirectDataRegisterWorks) {
    Given({
        "D1 is 0x0A01B003",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x75",
        "SR is S,0,0"
    });
    When({
        "CMP.B (A1), D1"
    });
    Then({
        "D1 is 0x0A01B003",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x75",
        "SR is S,0,NC"
    });
}

TEST_F(CMPTestByte, AddressIncrementDataRegisterWorks) {
    Given({
        "D1 is 0x0A01B003",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x75",
        "SR is S,0,0"
    });
    When({
        "CMP.B (A1)+, D1"
    });
    Then({
        "D1 is 0x0A01B003",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x75",
        "SR is S,0,NC"
    });
}

TEST_F(CMPTestByte, AddressDecrementDataRegisterWorks) {
    Given({
        "D1 is 0x0A01B003",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x75",
        "SR is S,0,0"
    });
    When({
        "CMP.B -(A1), D1"
    });
    Then({
        "D1 is 0x0A01B003",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x75",
        "SR is S,0,NC"
    });
}

TEST_F(CMPTestByte, AddressDisplacementDataRegisterWorks) {
    Given({
        "D1 is 0x0A01B003",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x75",
        "SR is S,0,0"
    });
    When({
        "CMP.B (2, A1), D1"
    });
    Then({
        "D1 is 0x0A01B003",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x75",
        "SR is S,0,NC"
    });
}

TEST_F(CMPTestByte, AddressIndexDataRegisterWorks) {
    Given({
        "D1 is 0x0A01B003",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x75",
        "SR is S,0,0"
    });
    When({
        "CMP.B (2, A1, A2.L), D1"
    });
    Then({
        "D1 is 0x0A01B003",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x75",
        "SR is S,0,NC"
    });
}

TEST_F(CMPTestByte, ShortDataRegisterWorks) {
    Given({
        "D1 is 0x0A01B003",
        "(0x00004000).B is 0x75",
        "SR is S,0,0"
    });
    When({
        "CMP.B (0x4000).W, D1"
    });
    Then({
        "D1 is 0x0A01B003",
        "(0x00004000).B is 0x75",
        "SR is S,0,NC"
    });
}

TEST_F(CMPTestByte, LongDataRegisterWorks) {
    Given({
        "D1 is 0x0A01B003",
        "(0x00008000).B is 0x75",
        "SR is S,0,0"
    });
    When({
        "CMP.B (0x8000).L, D1"
    });
    Then({
        "D1 is 0x0A01B003",
        "(0x00008000).B is 0x75",
        "SR is S,0,NC"
    });
}

TEST_F(CMPTestByte, PCDisplacementDataRegisterWorks) {
    Given({
        "D1 is 0x0A01B003",
        "(0x00001060).B is 0x75",
        "SR is S,0,0"
    });
    When({
        "CMP.B (0x5E, PC), D1"
    });
    Then({
        "D1 is 0x0A01B003",
        "(0x00001060).B is 0x75",
        "SR is S,0,NC"
    });
}

TEST_F(CMPTestByte, PCIndexDataRegisterWorks) {
    Given({
        "D1 is 0x0A01B003",
        "A1 is 0x00000010",
        "(0x00001070).B is 0x75",
        "SR is S,0,0"
    });
    When({
        "CMP.B (0x5E, PC, A1.L), D1"
    });
    Then({
        "D1 is 0x0A01B003",
        "A1 is 0x00000010",
        "(0x00001070).B is 0x75",
        "SR is S,0,NC"
    });
}

TEST_F(CMPTestByte, ImmediateDataRegisterWorks) {
    Given({
        "D1 is 0x0A01B003",
        "SR is S,0,0"
    });
    When({
        "CMP.B #0x75, D1"
    });
    Then({
        "D1 is 0x0A01B003",
        "SR is S,0,NC"
    });
}
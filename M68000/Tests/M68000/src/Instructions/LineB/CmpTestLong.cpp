#include "M68000/Fixtures/M68000Test.h"

class CMPTestLong : public M68000Test {};

TEST_F(CMPTestLong, DataRegisterDataRegisterWorks) {
    Given({
        "D1 is 0x20010101",
        "D2 is 0xE3010101",
        "SR is S,0,0"
    });
    When({
        "CMP.L D1, D2"
    });
    Then({
        "D1 is 0x20010101",
        "D2 is 0xE3010101",
        "SR is S,0,N"
    });
}

TEST_F(CMPTestLong, DataRegisterDataRegisterFlagNVWorks) {
    Given({
        "D1 is 0x80010001",
        "D2 is 0x32010001",
        "SR is S,0,0"
    });
    When({
        "CMP.L D1, D2"
    });
    Then({
        "D1 is 0x80010001",
        "D2 is 0x32010001",
        "SR is S,0,NVC"
    });
}

TEST_F(CMPTestLong, DataRegisterDataRegisterFlagZWorks) {
    Given({
        "D1 is 0x80010001",
        "D2 is 0x80010001",
        "SR is S,0,0"
    });
    When({
        "CMP.L D1, D2"
    });
    Then({
        "D1 is 0x80010001",
        "D2 is 0x80010001",
        "SR is S,0,Z"
    });
}

TEST_F(CMPTestLong, DataRegisterDataRegisterFlagXWorks) {
    Given({
        "D1 is 0x80010001",
        "D2 is 0x80010002",
        "SR is S,0,X"
    });
    When({
        "CMP.L D1, D2"
    });
    Then({
        "D1 is 0x80010001",
        "D2 is 0x80010002",
        "SR is S,0,X"
    });
}

TEST_F(CMPTestLong, AddressRegisterDataRegisterWorks) {
    Given({
        "A2 is 0x09080706",
        "D2 is 0x07050301",
        "SR is S,0,0"
    });
    When({
        "CMP.L A2, D2"
    });
    Then({
        "A2 is 0x09080706",
        "D2 is 0x07050301",
        "SR is S,0,NC"
    });
}

TEST_F(CMPTestLong, AddressIndirectDataRegisterWorks) {
    Given({
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x09080706",
        "SR is S,0,0"
    });
    When({
        "CMP.L (A1), D1"
    });
    Then({
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x09080706",
        "SR is S,0,NC"
    });
}

TEST_F(CMPTestLong, AddressIncrementDataRegisterWorks) {
    Given({
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x09080706",
        "SR is S,0,0"
    });
    When({
        "CMP.L (A1)+, D1"
    });
    Then({
        "D1 is 0x07050301",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x09080706",
        "SR is S,0,NC"
    });
}

TEST_F(CMPTestLong, AddressDecrementDataRegisterWorks) {
    Given({
        "D1 is 0x07050301",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x09080706",
        "SR is S,0,0"
    });
    When({
        "CMP.L -(A1), D1"
    });
    Then({
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x09080706",
        "SR is S,0,NC"
    });
}

TEST_F(CMPTestLong, AddressDisplacementDataRegisterWorks) {
    Given({
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x09080706",
        "SR is S,0,0"
    });
    When({
        "CMP.L (2, A1), D1"
    });
    Then({
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x09080706",
        "SR is S,0,NC"
    });
}

TEST_F(CMPTestLong, AddressIndexDataRegisterWorks) {
    Given({
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x09080706",
        "SR is S,0,0"
    });
    When({
        "CMP.L (2, A1, A2.L), D1"
    });
    Then({
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x09080706",
        "SR is S,0,NC"
    });
}

TEST_F(CMPTestLong, ShortDataRegisterWorks) {
    Given({
        "D1 is 0x07050301",
        "(0x00004000).L is 0x09080706",
        "SR is S,0,0"
    });
    When({
        "CMP.L (0x4000).W, D1"
    });
    Then({
        "D1 is 0x07050301",
        "(0x00004000).L is 0x09080706",
        "SR is S,0,NC"
    });
}

TEST_F(CMPTestLong, LongDataRegisterWorks) {
    Given({
        "D1 is 0x07050301",
        "(0x00008000).L is 0x09080706",
        "SR is S,0,0"
    });
    When({
        "CMP.L (0x8000).L, D1"
    });
    Then({
        "D1 is 0x07050301",
        "(0x00008000).L is 0x09080706",
        "SR is S,0,NC"
    });
}

TEST_F(CMPTestLong, PCDisplacementDataRegisterWorks) {
    Given({
        "D1 is 0x07050301",
        "(0x00001060).L is 0x09080706",
        "SR is S,0,0"
    });
    When({
        "CMP.L (0x5E, PC), D1"
    });
    Then({
        "D1 is 0x07050301",
        "(0x00001060).L is 0x09080706",
        "SR is S,0,NC"
    });
}

TEST_F(CMPTestLong, PCIndexDataRegisterWorks) {
    Given({
        "D1 is 0x07050301",
        "A1 is 0x00000010",
        "(0x00001070).L is 0x09080706",
        "SR is S,0,0"
    });
    When({
        "CMP.L (0x5E, PC, A1.L), D1"
    });
    Then({
        "D1 is 0x07050301",
        "A1 is 0x00000010",
        "(0x00001070).L is 0x09080706",
        "SR is S,0,NC"
    });
}

TEST_F(CMPTestLong, ImmediateDataRegisterWorks) {
    Given({
        "D1 is 0x07050301",
        "SR is S,0,0"
    });
    When({
        "CMP.L #0x09080706, D1"
    });
    Then({
        "D1 is 0x07050301",
        "SR is S,0,NC"
    });
}

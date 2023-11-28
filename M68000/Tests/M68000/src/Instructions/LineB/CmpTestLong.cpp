#include "M68000/Fixtures/M68000Test.h"

class CMPTestLong : public M68000Test {};

TEST_F(CMPTestLong, DataRegisterDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x20010101",
        "D2 is 0xE3010101",
    });
    When({
        "CMP.L D1, D2"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x20010101",
        "D2 is 0xE3010101",
    });
}

TEST_F(CMPTestLong, DataRegisterDataRegisterFlagNVWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x80010001",
        "D2 is 0x32010001",
    });
    When({
        "CMP.L D1, D2"
    });
    Then({
        "SR is S,0,NVC",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x80010001",
        "D2 is 0x32010001",
    });
}

TEST_F(CMPTestLong, DataRegisterDataRegisterFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x80010001",
        "D2 is 0x80010001",
    });
    When({
        "CMP.L D1, D2"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x80010001",
        "D2 is 0x80010001",
    });
}

TEST_F(CMPTestLong, DataRegisterDataRegisterFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0x80010001",
        "D2 is 0x80010002",
    });
    When({
        "CMP.L D1, D2"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 6",
        "D1 is 0x80010001",
        "D2 is 0x80010002",
    });
}

TEST_F(CMPTestLong, AddressRegisterDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D2 is 0x07050301",
        "A2 is 0x09080706",
    });
    When({
        "CMP.L A2, D2"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1002",
        "CYCLES is 6",
        "D2 is 0x07050301",
        "A2 is 0x09080706",
    });
}

TEST_F(CMPTestLong, AddressIndirectDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x09080706",
    });
    When({
        "CMP.L (A1), D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x09080706",
    });
}

TEST_F(CMPTestLong, AddressIncrementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x09080706",
    });
    When({
        "CMP.L (A1)+, D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x07050301",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x09080706",
    });
}

TEST_F(CMPTestLong, AddressDecrementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x07050301",
        "A1 is 0x00008004",
        "(0x00008000).L is 0x09080706",
    });
    When({
        "CMP.L -(A1), D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1002",
        "CYCLES is 16",
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "(0x00008000).L is 0x09080706",
    });
}

TEST_F(CMPTestLong, AddressDisplacementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x09080706",
    });
    When({
        "CMP.L (2, A1), D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1004",
        "CYCLES is 18",
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "(0x00008002).L is 0x09080706",
    });
}

TEST_F(CMPTestLong, AddressIndexDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x09080706",
    });
    When({
        "CMP.L (2, A1, A2.L), D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1004",
        "CYCLES is 20",
        "D1 is 0x07050301",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).L is 0x09080706",
    });
}

TEST_F(CMPTestLong, ShortDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x07050301",
        "(0x00004000).L is 0x09080706",
    });
    When({
        "CMP.L (0x4000).W, D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1004",
        "CYCLES is 18",
        "D1 is 0x07050301",
        "(0x00004000).L is 0x09080706",
    });
}

TEST_F(CMPTestLong, LongDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x07050301",
        "(0x00008000).L is 0x09080706",
    });
    When({
        "CMP.L (0x8000).L, D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1006",
        "CYCLES is 22",
        "D1 is 0x07050301",
        "(0x00008000).L is 0x09080706",
    });
}

TEST_F(CMPTestLong, PCDisplacementDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x07050301",
        "(0x00001060).L is 0x09080706",
    });
    When({
        "CMP.L (0x5E, PC), D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1004",
        "CYCLES is 18",
        "D1 is 0x07050301",
        "(0x00001060).L is 0x09080706",
    });
}

TEST_F(CMPTestLong, PCIndexDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x07050301",
        "A1 is 0x00000010",
        "(0x00001070).L is 0x09080706",
    });
    When({
        "CMP.L (0x5E, PC, A1.L), D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1004",
        "CYCLES is 20",
        "D1 is 0x07050301",
        "A1 is 0x00000010",
        "(0x00001070).L is 0x09080706",
    });
}

TEST_F(CMPTestLong, ImmediateDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x07050301",
    });
    When({
        "CMP.L #0x09080706, D1"
    });
    Then({
        "SR is S,0,NC",
        "PC is 0x1006",
        "CYCLES is 14",
        "D1 is 0x07050301",
    });
}

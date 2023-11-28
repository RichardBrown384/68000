#include "M68000/Fixtures/M68000Test.h"

class EORTestByte : public M68000Test {};

TEST_F(EORTestByte, DataRegisterDataRegisterWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x03030313",
        "D2 is 0xF0F0F041",
    });
    When({
        "EOR.B D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x03030313",
        "D2 is 0xF0F0F052",
    });
}

TEST_F(EORTestByte, DataRegisterDataRegisterFlagNWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x03030385",
        "D2 is 0xF0F0F014",
    });
    When({
        "EOR.B D1, D2"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x03030385",
        "D2 is 0xF0F0F091",
    });
}

TEST_F(EORTestByte, DataRegisterDataRegisterFlagZWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x03030360",
        "D2 is 0xF0F0F060",
    });
    When({
        "EOR.B D1, D2"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x03030360",
        "D2 is 0xF0F0F000",
    });
}

TEST_F(EORTestByte, DataRegisterDataRegisterFlagXWorks) {
    Given({
        "SR is S,0,X",
        "PC is 0x1000",
        "D1 is 0x03030313",
        "D2 is 0xF0F0F054",
    });
    When({
        "EOR.B D1, D2"
    });
    Then({
        "SR is S,0,X",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x03030313",
        "D2 is 0xF0F0F047",
    });
}

TEST_F(EORTestByte, DataRegisterDataRegisterFlagVCWorks) {
    Given({
        "SR is S,0,VC",
        "PC is 0x1000",
        "D1 is 0x01010113",
        "D2 is 0x10101021",
    });
    When({
        "EOR.B D1, D2"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 4",
        "D1 is 0x01010113",
        "D2 is 0x10101032",
    });
}

TEST_F(EORTestByte, DataRegisterAddressIndirectWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x7A",
    });
    When({
        "EOR.B D1, (A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x36",
    });
}

TEST_F(EORTestByte, DataRegisterAddressIncrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x7A",
    });
    When({
        "EOR.B D1, (A1)+"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 12",
        "D1 is 0x0101014C",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x36",
    });
}

TEST_F(EORTestByte, DataRegisterAddressDecrementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0101014C",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x7A",
    });
    When({
        "EOR.B D1, -(A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1002",
        "CYCLES is 14",
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x36",
    });
}

TEST_F(EORTestByte, DataRegisterAddressIndexWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x7A",
    });
    When({
        "EOR.B D1, (2, A1)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x36",
    });
}

TEST_F(EORTestByte, DataRegisterAddressDisplacementWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x7A",
    });
    When({
        "EOR.B D1, (2, A1, A2.L)"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 18",
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x36",
    });
}

TEST_F(EORTestByte, DataRegisterShortWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0101014C",
        "(0x00004000).B is 0x7A",
    });
    When({
        "EOR.B D1, (0x4000).W"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 16",
        "D1 is 0x0101014C",
        "(0x00004000).B is 0x36",
    });
}

TEST_F(EORTestByte, DataRegisterLongWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0101014C",
        "(0x00008000).B is 0x7A",
    });
    When({
        "EOR.B D1, (0x8000).L"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1006",
        "CYCLES is 20",
        "D1 is 0x0101014C",
        "(0x00008000).B is 0x36",
    });
}

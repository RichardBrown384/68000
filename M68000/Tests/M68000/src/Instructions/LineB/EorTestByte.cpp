#include "M68000/Fixtures/M68000Test.h"

class EORTestByte : public M68000Test {};

TEST_F(EORTestByte, DataRegisterDataRegisterWorks) {
    Given({
        "D1 is 0x03030313",
        "D2 is 0xF0F0F041",
        "SR is S,0,0"
    });
    When({
        "EOR.B D1, D2"
    });
    Then({
        "D1 is 0x03030313",
        "D2 is 0xF0F0F052",
        "SR is S,0,0"
    });
}

TEST_F(EORTestByte, DataRegisterDataRegisterFlagNWorks) {
    Given({
        "D1 is 0x03030385",
        "D2 is 0xF0F0F014",
        "SR is S,0,0"
    });
    When({
        "EOR.B D1, D2"
    });
    Then({
        "D1 is 0x03030385",
        "D2 is 0xF0F0F091",
        "SR is S,0,N"
    });
}

TEST_F(EORTestByte, DataRegisterDataRegisterFlagZWorks) {
    Given({
        "D1 is 0x03030360",
        "D2 is 0xF0F0F060",
        "SR is S,0,0"
    });
    When({
        "EOR.B D1, D2"
    });
    Then({
        "D1 is 0x03030360",
        "D2 is 0xF0F0F000",
        "SR is S,0,Z"
    });
}

TEST_F(EORTestByte, DataRegisterDataRegisterFlagXWorks) {
    Given({
        "D1 is 0x03030313",
        "D2 is 0xF0F0F054",
        "SR is S,0,X"
    });
    When({
        "EOR.B D1, D2"
    });
    Then({
        "D1 is 0x03030313",
        "D2 is 0xF0F0F047",
        "SR is S,0,X"
    });
}

TEST_F(EORTestByte, DataRegisterDataRegisterFlagVCWorks) {
    Given({
        "D1 is 0x01010113",
        "D2 is 0x10101021",
        "SR is S,0,VC"
    });
    When({
        "EOR.B D1, D2"
    });
    Then({
        "D1 is 0x01010113",
        "D2 is 0x10101032",
        "SR is S,0,0"
    });
}

TEST_F(EORTestByte, DataRegisterAddressIndirectWorks) {
    Given({
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x7A",
        "SR is S,0,0"
    });
    When({
        "EOR.B D1, (A1)"
    });
    Then({
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x36",
        "SR is S,0,0"
    });
}

TEST_F(EORTestByte, DataRegisterAddressIncrementWorks) {
    Given({
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x7A",
        "SR is S,0,0"
    });
    When({
        "EOR.B D1, (A1)+"
    });
    Then({
        "D1 is 0x0101014C",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x36",
        "SR is S,0,0"
    });
}

TEST_F(EORTestByte, DataRegisterAddressDecrementWorks) {
    Given({
        "D1 is 0x0101014C",
        "A1 is 0x00008001",
        "(0x00008000).B is 0x7A",
        "SR is S,0,0"
    });
    When({
        "EOR.B D1, -(A1)"
    });
    Then({
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008000).B is 0x36",
        "SR is S,0,0"
    });
}

TEST_F(EORTestByte, DataRegisterAddressIndexWorks) {
    Given({
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x7A",
        "SR is S,0,0"
    });
    When({
        "EOR.B D1, (2, A1)"
    });
    Then({
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "(0x00008002).B is 0x36",
        "SR is S,0,0"
    });
}

TEST_F(EORTestByte, DataRegisterAddressDisplacementWorks) {
    Given({
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x7A",
        "SR is S,0,0"
    });
    When({
        "EOR.B D1, (2, A1, A2.L)"
    });
    Then({
        "D1 is 0x0101014C",
        "A1 is 0x00008000",
        "A2 is 0x00000010",
        "(0x00008012).B is 0x36",
        "SR is S,0,0"
    });
}

TEST_F(EORTestByte, DataRegisterShortWorks) {
    Given({
        "D1 is 0x0101014C",
        "(0x00004000).B is 0x7A",
        "SR is S,0,0"
    });
    When({
        "EOR.B D1, (0x4000).W"
    });
    Then({
        "D1 is 0x0101014C",
        "(0x00004000).B is 0x36",
        "SR is S,0,0"
    });
}

TEST_F(EORTestByte, DataRegisterLongWorks) {
    Given({
        "D1 is 0x0101014C",
        "(0x00008000).B is 0x7A",
        "SR is S,0,0"
    });
    When({
        "EOR.B D1, (0x8000).L"
    });
    Then({
        "D1 is 0x0101014C",
        "(0x00008000).B is 0x36",
        "SR is S,0,0"
    });
}
#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "BHI.B *+8",
    "BLS.B *+8",
    "BCC.B *+8",
    "BCS.B *+8",
    "BNE.B *+8",
    "BEQ.B *+8",
    "BVC.B *+8",
    "BVS.B *+8",
    "BPL.B *+8",
    "BMI.B *+8",
    "BGE.B *+8",
    "BLT.B *+8",
    "BGT.B *+8",
    "BLE.B *+8",
    "BLE.B *-8",
    "BHI.W *+800",
    "BLS.W *+800",
    "BCC.W *+800",
    "BCS.W *+800",
    "BNE.W *+800",
    "BEQ.W *+800",
    "BVC.W *+800",
    "BVS.W *+800",
    "BPL.W *+800",
    "BMI.W *+800",
    "BGE.W *+800",
    "BLT.W *+800",
    "BGT.W *+800",
    "BLE.W *+800",
    "BLE.W *-800",
};

constexpr auto NEGATIVE_VALUES = {
    "BHI.L *+100",
    "BHI.L *-100",
};

INSTANTIATE_TEST_SUITE_P(ParserBccPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserBccNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "MOVE.W D1, CCR",
    "MOVE.W (A1), CCR",
    "MOVE.W (A1)+, CCR",
    "MOVE.W -(A1), CCR",
    "MOVE.W (15, A1), CCR",
    "MOVE.W (15, A1, D1.L), CCR",
    "MOVE.W (200).W, CCR",
    "MOVE.W (200).L, CCR",
    "MOVE.W (15, PC), CCR",
    "MOVE.W (15, PC, D1.L), CCR",
    "MOVE.W #200, CCR"
};

constexpr auto NEGATIVE_VALUES = {
    "MOVE.B D1, CCR",
    "MOVE.L D1, CCR",
    "MOVE.W A1, CCR",
    "MOVE.W CCR, CCR",
};

INSTANTIATE_TEST_SUITE_P(ParserMOVECCRPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserMOVECCRNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
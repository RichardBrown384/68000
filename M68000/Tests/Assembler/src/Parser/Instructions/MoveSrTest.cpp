#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "MOVE.W D1, SR",
    "MOVE.W (A1), SR",
    "MOVE.W (A1)+, SR",
    "MOVE.W -(A1), SR",
    "MOVE.W (15, A1), SR",
    "MOVE.W (15, A1, D1.L), SR",
    "MOVE.W (200).W, SR",
    "MOVE.W (200).L, SR",
    "MOVE.W (15, PC), SR",
    "MOVE.W (15, PC, D1.L), SR",
    "MOVE.W #200, SR",
    "MOVE.W SR, D1",
    "MOVE.W SR, (A1)",
    "MOVE.W SR, (A1)+",
    "MOVE.W SR, -(A1)",
    "MOVE.W SR, (16, A1)",
    "MOVE.W SR, (16, A1, D1.L)",
    "MOVE.W SR, (200).W",
    "MOVE.W SR, (200).L"
};

constexpr auto NEGATIVE_VALUES = {
    "MOVE.B D1, SR",
    "MOVE.L D1, SR",
    "MOVE.W A1, SR",
    "MOVE.W SR, SR",
    "MOVE.W SR, A1",
    "MOVE.W SR, (15, PC)",
    "MOVE.W SR, (15, PC, D1.L)",
    "MOVE.W SR, #200",
};

INSTANTIATE_TEST_SUITE_P(ParserMOVESRPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserMOVESRNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "NEG.B D1",
    "NEG.B (A1)",
    "NEG.B (A1)+",
    "NEG.B -(A1)",
    "NEG.B (10, A1)",
    "NEG.B (10, A1, A2.L)",
    "NEG.B (123).W",
    "NEG.B (123).L",
    "NEG.W D1",
    "NEG.W (A1)",
    "NEG.W (A1)+",
    "NEG.W -(A1)",
    "NEG.W (10, A1)",
    "NEG.W (10, A1, A2.L)",
    "NEG.W (123).W",
    "NEG.W (123).L",
    "NEG.L D1",
    "NEG.L (A1)",
    "NEG.L (A1)+",
    "NEG.L -(A1)",
    "NEG.L (10, A1)",
    "NEG.L (10, A1, A2.L)",
    "NEG.L (123).W",
    "NEG.L (123).L"
};

constexpr auto NEGATIVE_VALUES = {
    "NEG.B A1",
    "NEG.B (10, PC)",
    "NEG.B (10, PC, D1.L)",
    "NEG.B #123",
    "NEG.W A1",
    "NEG.W (10, PC)",
    "NEG.W (10, PC, D1.L)",
    "NEG.W #123",
    "NEG.L A1",
    "NEG.L (10, PC)",
    "NEG.L (10, PC, D1.L)",
    "NEG.L #123"
};

INSTANTIATE_TEST_SUITE_P(ParserNEGPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserNEGNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "NOT.B D1",
    "NOT.B (A1)",
    "NOT.B (A1)+",
    "NOT.B -(A1)",
    "NOT.B (10, A1)",
    "NOT.B (10, A1, A2.L)",
    "NOT.B (123).W",
    "NOT.B (123).L",
    "NOT.W D1",
    "NOT.W (A1)",
    "NOT.W (A1)+",
    "NOT.W -(A1)",
    "NOT.W (10, A1)",
    "NOT.W (10, A1, A2.L)",
    "NOT.W (123).W",
    "NOT.W (123).L",
    "NOT.L D1",
    "NOT.L (A1)",
    "NOT.L (A1)+",
    "NOT.L -(A1)",
    "NOT.L (10, A1)",
    "NOT.L (10, A1, A2.L)",
    "NOT.L (123).W",
    "NOT.L (123).L"
};

constexpr auto NEGATIVE_VALUES = {
    "NOT.B A1",
    "NOT.B (10, PC)",
    "NOT.B (10, PC, D1.L)",
    "NOT.B #123",
    "NOT.W A1",
    "NOT.W (10, PC)",
    "NOT.W (10, PC, D1.L)",
    "NOT.W #123",
    "NOT.L A1",
    "NOT.L (10, PC)",
    "NOT.L (10, PC, D1.L)",
    "NOT.L #123"
};

INSTANTIATE_TEST_SUITE_P(ParserNOTPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserNOTNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
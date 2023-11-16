#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "NEGX.B D1",
    "NEGX.B (A1)",
    "NEGX.B (A1)+",
    "NEGX.B -(A1)",
    "NEGX.B (10, A1)",
    "NEGX.B (10, A1, A2.L)",
    "NEGX.B (123).W",
    "NEGX.B (123).L",
    "NEGX.W D1",
    "NEGX.W (A1)",
    "NEGX.W (A1)+",
    "NEGX.W -(A1)",
    "NEGX.W (10, A1)",
    "NEGX.W (10, A1, A2.L)",
    "NEGX.W (123).W",
    "NEGX.W (123).L",
    "NEGX.L D1",
    "NEGX.L (A1)",
    "NEGX.L (A1)+",
    "NEGX.L -(A1)",
    "NEGX.L (10, A1)",
    "NEGX.L (10, A1, A2.L)",
    "NEGX.L (123).W",
    "NEGX.L (123).L"
};

constexpr auto NEGATIVE_VALUES = {
    "NEGX.B A1",
    "NEGX.B (10, PC)",
    "NEGX.B (10, PC, D1.L)",
    "NEGX.B #123",
    "NEGX.W A1",
    "NEGX.W (10, PC)",
    "NEGX.W (10, PC, D1.L)",
    "NEGX.W #123",
    "NEGX.L A1",
    "NEGX.L (10, PC)",
    "NEGX.L (10, PC, D1.L)",
    "NEGX.L #123"
};

INSTANTIATE_TEST_SUITE_P(ParserNEGXPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserNEGXNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
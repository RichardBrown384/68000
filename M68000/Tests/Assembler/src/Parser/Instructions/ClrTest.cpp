#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "CLR.B D1",
    "CLR.B (A1)",
    "CLR.B (A1)+",
    "CLR.B -(A1)",
    "CLR.B (10, A1)",
    "CLR.B (10, A1, A2.L)",
    "CLR.B (123).W",
    "CLR.B (123).L",
    "CLR.W D1",
    "CLR.W (A1)",
    "CLR.W (A1)+",
    "CLR.W -(A1)",
    "CLR.W (10, A1)",
    "CLR.W (10, A1, A2.L)",
    "CLR.W (123).W",
    "CLR.W (123).L",
    "CLR.L D1",
    "CLR.L (A1)",
    "CLR.L (A1)+",
    "CLR.L -(A1)",
    "CLR.L (10, A1)",
    "CLR.L (10, A1, A2.L)",
    "CLR.L (123).W",
    "CLR.L (123).L"
};

constexpr auto NEGATIVE_VALUES = {
    "CLR.B A1",
    "CLR.B (10, PC)",
    "CLR.B (10, PC, D1.L)",
    "CLR.B #123",
    "CLR.W A1",
    "CLR.W (10, PC)",
    "CLR.W (10, PC, D1.L)",
    "CLR.W #123",
    "CLR.L A1",
    "CLR.L (10, PC)",
    "CLR.L (10, PC, D1.L)",
    "CLR.L #123"
};

INSTANTIATE_TEST_SUITE_P(ParserCLRPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserCLRNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
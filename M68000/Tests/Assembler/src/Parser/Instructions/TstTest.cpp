#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "TST.B D1",
    "TST.B (A1)",
    "TST.B (A1)+",
    "TST.B -(A1)",
    "TST.B (15, A1)",
    "TST.B (15, A1, D1.L)",
    "TST.B (200).W",
    "TST.B (200).L",
    "TST.W D1",
    "TST.W (A1)",
    "TST.W (A1)+",
    "TST.W -(A1)",
    "TST.W (15, A1)",
    "TST.W (15, A1, D1.L)",
    "TST.W (200).W",
    "TST.W (200).L",
    "TST.L D1",
    "TST.L (A1)",
    "TST.L (A1)+",
    "TST.L -(A1)",
    "TST.L (15, A1)",
    "TST.L (15, A1, D1.L)",
    "TST.L (200).W",
    "TST.L (200).L",
};

constexpr auto NEGATIVE_VALUES = {
    "TST.B A1",
    "TST.B #12",
    "TST.B (15, PC)",
    "TST.B (15, PC, D1.L)",
    "TST.W A1",
    "TST.W #12",
    "TST.W (15, PC)",
    "TST.W (15, PC, D1.L)",
    "TST.L A1",
    "TST.L #12",
    "TST.L (15, PC)",
    "TST.L (15, PC, D1.L)"
};

INSTANTIATE_TEST_SUITE_P(ParserTSTPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserTSTNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
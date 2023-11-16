#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "TAS D1",
    "TAS (A1)",
    "TAS (A1)+",
    "TAS -(A1)",
    "TAS (15, A1)",
    "TAS (15, A1, D1.L)",
    "TAS (200).W",
    "TAS (200).L"
};

constexpr auto NEGATIVE_VALUES = {
    "TAS A1",
    "TAS (15, PC)",
    "TAS (15, PC, D1.L)",
    "TAS #200"
};

INSTANTIATE_TEST_SUITE_P(ParserTASPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserTASNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
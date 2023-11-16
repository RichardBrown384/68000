#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "MOVEQ #0, D1",
    "MOVEQ #-1, D6",
    "MOVEQ #255, D2",
    "MOVEQ #-128, D3",
    "MOVEQ #127, D4"
};

constexpr auto NEGATIVE_VALUES = {
    "MOVEQ #2, A0",
    "MOVEQ #2, (A1)",
    "MOVEQ #2, (A1)+",
    "MOVEQ #2, -(A1)",
    "MOVEQ #2, (2, A1)",
    "MOVEQ #2, (2, A1, D2.L)",
    "MOVEQ #2, (123).W",
    "MOVEQ #2, (123).L",
    "MOVEQ #2, (2, PC)",
    "MOVEQ #2, (2, PC, D2.L)",
    "MOVEQ #2, #123"
};

INSTANTIATE_TEST_SUITE_P(ParserMOVEQPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserMOVEQNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
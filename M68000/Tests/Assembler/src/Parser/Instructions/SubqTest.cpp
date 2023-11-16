#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "SUBQ.B #1, D0",
    "SUBQ.B #8, D0",
    "SUBQ.W #1, D0",
    "SUBQ.L #1, D0",
    "SUBQ.W #1, A0",
    "SUBQ.L #1, A0",
    "SUBQ.L #1, (A0)",
    "SUBQ.L #1, (A0)+",
    "SUBQ.L #1, -(A0)",
    "SUBQ.L #1, (1000, A0)",
    "SUBQ.L #1, (125, A0, D1.L)",
    "SUBQ.L #1, (125, A0, A1.L)",
    "SUBQ.L #1, (123).W",
    "SUBQ.L #1, (123).L"
};

constexpr auto NEGATIVE_VALUES = {
    "SUBQ.B #1, A0",
    "SUBQ.B #0, D0",
    "SUBQ.B #9, D0",
    "SUBQ.L #1, (1000, PC)",
    "SUBQ.L #1, (125, PC, D1.L)",
    "SUBQ.L #1, (125, PC, A1.L)",
    "SUBQ.L #1, #123"
};

INSTANTIATE_TEST_SUITE_P(ParserSUBQPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserSUBQNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);

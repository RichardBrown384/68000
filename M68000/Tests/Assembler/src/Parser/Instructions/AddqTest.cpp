#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "ADDQ.B #1, D0",
    "ADDQ.B #8, D0",
    "ADDQ.W #1, D0",
    "ADDQ.L #1, D0",
    "ADDQ.W #1, A0",
    "ADDQ.L #1, A0",
    "ADDQ.L #1, (A0)",
    "ADDQ.L #1, (A0)+",
    "ADDQ.L #1, -(A0)",
    "ADDQ.L #1, (1000, A0)",
    "ADDQ.L #1, (125, A0, D1.L)",
    "ADDQ.L #1, (125, A0, A1.L)",
    "ADDQ.L #1, (123).W",
    "ADDQ.L #1, (123).L"
};

constexpr auto NEGATIVE_VALUES = {
    "ADDQ.B #1, A0",
    "ADDQ.B #0, D0",
    "ADDQ.B #9, D0",
    "ADDQ.L #1, (1000, PC)",
    "ADDQ.L #1, (125, PC, D1.L)",
    "ADDQ.L #1, (125, PC, A1.L)",
    "ADDQ.L #1, #123"
};

INSTANTIATE_TEST_SUITE_P(ParserADDQPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserADDQNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);

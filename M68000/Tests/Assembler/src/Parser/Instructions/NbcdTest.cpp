#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "NBCD D1",
    "NBCD (A1)",
    "NBCD (A1)+",
    "NBCD -(A1)",
    "NBCD (10, A1)",
    "NBCD (10, A1, A2.L)",
    "NBCD (123).W",
    "NBCD (123).L",
};

constexpr auto NEGATIVE_VALUES = {
    "NBCD A1",
    "NBCD (10, PC)",
    "NBCD (10, PC, D1.L)",
    "NBCD #123"
};

INSTANTIATE_TEST_SUITE_P(ParserNBCDPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserNBCDNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
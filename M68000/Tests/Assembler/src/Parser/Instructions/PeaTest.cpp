#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "PEA (A1)",
    "PEA (10, A1)",
    "PEA (10, A1, D2.L)",
    "PEA (2000).W",
    "PEA (2000).L",
    "PEA (10, PC)",
    "PEA (10, PC, D2.L)"
};

constexpr auto NEGATIVE_VALUES = {
    "PEA D1",
    "PEA A1",
    "PEA (A1)+",
    "PEA -(A1)",
    "PEA #1"
};

INSTANTIATE_TEST_SUITE_P(ParserPEAPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
 );

INSTANTIATE_TEST_SUITE_P(ParserPEANegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);

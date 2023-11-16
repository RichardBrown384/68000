#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "SBCD D0, D1",
    "SBCD -(A1), -(A2)"
};

constexpr auto NEGATIVE_VALUES = {
    "SBCD D3, -(A1)",
    "SBCD -(A1), D3",
    "SBCD (A1), D0",
    "SBCD (A1)+, D0",
    "SBCD (2, A3), D0",
    "SBCD (2, A3, D3.L), D0",
    "SBCD (123).W, D0",
    "SBCD (128).L, D0",
    "SBCD (2, PC), D0",
    "SBCD (2, PC, D3.L), D0",
    "SBCD #123, D0",
    "SBCD D1, (A1)",
    "SBCD D1, (A1)+",
    "SBCD D1, (2, A3)",
    "SBCD D1, (2, A3, D3.L)",
    "SBCD D1, (123).W",
    "SBCD D1, (128).L",
    "SBCD D1, (2, PC)",
    "SBCD D1, (2, PC, D3.L)",
    "SBCD D1, #123"
};

INSTANTIATE_TEST_SUITE_P(ParserSBCDPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
 );

INSTANTIATE_TEST_SUITE_P(ParserSBCDNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);

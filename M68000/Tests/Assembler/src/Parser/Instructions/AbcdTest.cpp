#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "ABCD D0, D1",
    "ABCD -(A1), -(A2)"
};

constexpr auto NEGATIVE_VALUES = {
    "ABCD D3, -(A1)",
    "ABCD -(A1), D3",
    "ABCD (A1), D0",
    "ABCD (A1)+, D0",
    "ABCD (2, A3), D0",
    "ABCD (2, A3, D3.L), D0",
    "ABCD (123).W, D0",
    "ABCD (128).L, D0",
    "ABCD (2, PC), D0",
    "ABCD (2, PC, D3.L), D0",
    "ABCD #123, D0",
    "ABCD D1, (A1)",
    "ABCD D1, (A1)+",
    "ABCD D1, (2, A3)",
    "ABCD D1, (2, A3, D3.L)",
    "ABCD D1, (123).W",
    "ABCD D1, (128).L",
    "ABCD D1, (2, PC)",
    "ABCD D1, (2, PC, D3.L)",
    "ABCD D1, #123"
};

INSTANTIATE_TEST_SUITE_P(ParserABCDPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
 );

INSTANTIATE_TEST_SUITE_P(ParserABCDNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);

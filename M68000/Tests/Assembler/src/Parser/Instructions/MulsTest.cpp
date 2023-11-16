#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "MULS D0, D1",
    "MULS (A1), D1",
    "MULS (A1)+, D1",
    "MULS -(A1), D1",
    "MULS (10, A1), D3",
    "MULS (10, A1, D2.L), D3",
    "MULS (123).W, D3",
    "MULS (123).L, D3",
    "MULS (10, PC, D2.L), D3",
    "MULS #123, D3"
};

constexpr auto NEGATIVE_VALUES = {
    "MULS A1, D0",
    "MULS D0, A1",
    "MULS D0, (A1)",
    "MULS D0, (A1)+",
    "MULS D0, -(A1)",
    "MULS D0, (10, A1)",
    "MULS D0, (10, A1, D2.L)",
    "MULS D0, (123).W",
    "MULS D0, (123).L",
    "MULS D0, (10, PC, D2.L)",
    "MULS D0, #123"
};

INSTANTIATE_TEST_SUITE_P(ParserMULSPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserMULSNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
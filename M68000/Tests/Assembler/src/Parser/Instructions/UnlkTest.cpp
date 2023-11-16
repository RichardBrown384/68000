#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "UNLK A1"
};

constexpr auto NEGATIVE_VALUES = {
    "UNLK D1",
    "UNLK (A1)",
    "UNLK (A1)+",
    "UNLK -(A1)",
    "UNLK (2, A3)",
    "UNLK (2, A3, D3.L)",
    "UNLK (123).W",
    "UNLK (128).L",
    "UNLK (2, PC)",
    "UNLK (2, PC, D3.L)"
};

INSTANTIATE_TEST_SUITE_P(ParserUNLKPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserUNLKNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
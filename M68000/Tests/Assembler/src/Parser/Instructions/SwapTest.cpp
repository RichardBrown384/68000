#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "SWAP D1"
};

constexpr auto NEGATIVE_VALUES = {
    "SWAP A1",
    "SWAP (A1)",
    "SWAP (A1)+",
    "SWAP -(A1)",
    "SWAP (2, A3)",
    "SWAP (2, A3, D3.L)",
    "SWAP (123).W",
    "SWAP (128).L",
    "SWAP (2, PC)",
    "SWAP (2, PC, D3.L)"
};

INSTANTIATE_TEST_SUITE_P(ParserSWAPPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserSWAPNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
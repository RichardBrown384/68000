#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "LINK A1, #3"
};

constexpr auto NEGATIVE_VALUES = {
    "LINK D1, #3",
    "LINK (A1), #3",
    "LINK (A1)+, #3",
    "LINK -(A1), #3",
    "LINK (2, A3), #3",
    "LINK (2, A3, D3.L), #3",
    "LINK (123).W, #3",
    "LINK (128).L, #3",
    "LINK (2, PC), #3",
    "LINK (2, PC, D3.L), #3",
    "LINK #123, #3",
    "LINK A1, D1",
    "LINK A1, A2",
    "LINK A1, (A2)+",
    "LINK A1, -(A2)",
    "LINK A1, (2, A3)",
    "LINK A1, (2, A3, D3.L)",
    "LINK A1, (123).W",
    "LINK A1, (128).L",
    "LINK A1, (2, PC)",
    "LINK A1, (2, PC, D3.L)"
};

INSTANTIATE_TEST_SUITE_P(ParserLINKPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserLINKNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
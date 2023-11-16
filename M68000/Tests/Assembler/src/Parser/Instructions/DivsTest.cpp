#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "DIVS D0, D1",
    "DIVS (A1), D1",
    "DIVS (A1)+, D1",
    "DIVS -(A1), D1",
    "DIVS (10, A1), D3",
    "DIVS (10, A1, D2.L), D3",
    "DIVS (123).W, D3",
    "DIVS (123).L, D3",
    "DIVS (10, PC, D2.L), D3",
    "DIVS #123, D3"
};

constexpr auto NEGATIVE_VALUES = {
    "DIVS A0, D1",
    "DIVS D0, A1",
    "DIVS D0, (A1)",
    "DIVS D0, (A1)+",
    "DIVS D0, -(A1)",
    "DIVS D0, (10, A1)",
    "DIVS D0, (10, A1, D2.L)",
    "DIVS D0, (123).W",
    "DIVS D0, (123).L",
    "DIVS D0, (10, PC, D2.L)",
    "DIVS D0, #123"
};

INSTANTIATE_TEST_SUITE_P(ParserDIVSPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserDIVSNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "OR.B D0, D1",
    "OR.W D0, D1",
    "OR.L D0, D1",
    "OR.W D0, D1",
    "OR.W D0, (A1)",
    "OR.W D0, (A1)+",
    "OR.W D0, -(A1)",
    "OR.W D0, (10, A1)",
    "OR.W D0, (10, A1, D2.L)",
    "OR.W D0, (10, A1, A2.L)",
    "OR.W D0, (123).W",
    "OR.W D0, (123).L",
    "OR.W D0, D1",
    "OR.W (A1), D1",
    "OR.W (A1)+, D1",
    "OR.W -(A1), D1",
    "OR.W (10, A1), D3",
    "OR.W (10, A1, D2.L), D3",
    "OR.W (10, A1, A2.L), D3",
    "OR.W (123).W, D3",
    "OR.W (123).L, D3",
    "OR.W (10, PC, D2.L), D3",
    "OR.W (10, PC, A2.L), D3",
    "OR.W #123, D3"
};

constexpr auto NEGATIVE_VALUES = {
    "OR.W D0, A1",
    "OR.W D0, (10, PC, A1.L)",
    "OR.W D0, (10, PC, D1.L)",
    "OR.W D0, #123",
    "OR.W A0, D0",
    "OR.W (A1), (A2)"
};

INSTANTIATE_TEST_SUITE_P(ParserORPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserORNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
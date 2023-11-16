#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "MULU D0, D1",
    "MULU (A1), D1",
    "MULU (A1)+, D1",
    "MULU -(A1), D1",
    "MULU (10, A1), D3",
    "MULU (10, A1, D2.L), D3",
    "MULU (123).W, D3",
    "MULU (123).L, D3",
    "MULU (10, PC, D2.L), D3",
    "MULU #123, D3"
};

constexpr auto NEGATIVE_VALUES = {
    "MULU A1, D0",
    "MULU D0, A1",
    "MULU D0, (A1)",
    "MULU D0, (A1)+",
    "MULU D0, -(A1)",
    "MULU D0, (10, A1)",
    "MULU D0, (10, A1, D2.L)",
    "MULU D0, (123).W",
    "MULU D0, (123).L",
    "MULU D0, (10, PC, D2.L)",
    "MULU D0, #123"
};

INSTANTIATE_TEST_SUITE_P(ParserMULUPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserMULUNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
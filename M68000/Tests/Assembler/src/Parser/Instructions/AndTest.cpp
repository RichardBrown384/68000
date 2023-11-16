#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "AND.B D0, D1",
    "AND.W D0, D1",
    "AND.L D0, D1",
    "AND.W D0, D1",
    "AND.W D0, (A1)",
    "AND.W D0, (A1)+",
    "AND.W D0, -(A1)",
    "AND.W D0, (10, A1)",
    "AND.W D0, (10, A1, D2.L)",
    "AND.W D0, (10, A1, A2.L)",
    "AND.W D0, (123).W",
    "AND.W D0, (123).L",
    "AND.W D0, D1",
    "AND.W (A1), D1",
    "AND.W (A1)+, D1",
    "AND.W -(A1), D1",
    "AND.W (10, A1), D3",
    "AND.W (10, A1, D2.L), D3",
    "AND.W (10, A1, A2.L), D3",
    "AND.W (123).W, D3",
    "AND.W (123).L, D3",
    "AND.W (10, PC, D2.L), D3",
    "AND.W (10, PC, A2.L), D3",
    "AND.W #123, D3"
};

constexpr auto NEGATIVE_VALUES = {
    "AND.W D0, A1",
    "AND.W D0, (10, PC, A1.L)",
    "AND.W D0, (10, PC, D1.L)",
    "AND.W D0, #123",
    "AND.W A0, D0",
    "AND.W (A1), (A2)"
};

INSTANTIATE_TEST_SUITE_P(ParserANDPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserANDNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
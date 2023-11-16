#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "ADDX.B D0, D1",
    "ADDX.B -(A1), -(A2)",
    "ADDX.W D0, D1",
    "ADDX.W -(A1), -(A2)",
    "ADDX.L D0, D1",
    "ADDX.L -(A1), -(A2)"
};

constexpr auto NEGATIVE_VALUES = {
    "ADDX.B D3, -(A1)",
    "ADDX.B -(A1), D3",
    "ADDX.B (A1), D0",
    "ADDX.B (A1)+, D0",
    "ADDX.B (2, A3), D0",
    "ADDX.B (2, A3, D3.L), D0",
    "ADDX.B (123).W, D0",
    "ADDX.B (128).L, D0",
    "ADDX.B (2, PC), D0",
    "ADDX.B (2, PC, D3.L), D0",
    "ADDX.B #123, D0",
    "ADDX.B D1, (A1)",
    "ADDX.B D1, (A1)+",
    "ADDX.B D1, (2, A3)",
    "ADDX.B D1, (2, A3, D3.L)",
    "ADDX.B D1, (123).W",
    "ADDX.B D1, (128).L",
    "ADDX.B D1, (2, PC)",
    "ADDX.B D1, (2, PC, D3.L)",
    "ADDX.B D1, #123"
};

INSTANTIATE_TEST_SUITE_P(ParserADDXPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserADDXNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);

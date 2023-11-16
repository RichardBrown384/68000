#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "SUBX.B D0, D1",
    "SUBX.B -(A1), -(A2)",
    "SUBX.W D0, D1",
    "SUBX.W -(A1), -(A2)",
    "SUBX.L D0, D1",
    "SUBX.L -(A1), -(A2)"
};

constexpr auto NEGATIVE_VALUES = {
    "SUBX.B D3, -(A1)",
    "SUBX.B -(A1), D3",
    "SUBX.B (A1), D0",
    "SUBX.B (A1)+, D0",
    "SUBX.B (2, A3), D0",
    "SUBX.B (2, A3, D3.L), D0",
    "SUBX.B (123).W, D0",
    "SUBX.B (128).L, D0",
    "SUBX.B (2, PC), D0",
    "SUBX.B (2, PC, D3.L), D0",
    "SUBX.B #123, D0",
    "SUBX.B D1, (A1)",
    "SUBX.B D1, (A1)+",
    "SUBX.B D1, (2, A3)",
    "SUBX.B D1, (2, A3, D3.L)",
    "SUBX.B D1, (123).W",
    "SUBX.B D1, (128).L",
    "SUBX.B D1, (2, PC)",
    "SUBX.B D1, (2, PC, D3.L)",
    "SUBX.B D1, #123"
};

INSTANTIATE_TEST_SUITE_P(ParserADDXPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserADDXNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);

#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "CMPM.B (A1)+, (A2)+",
    "CMPM.W (A1)+, (A2)+",
    "CMPM.L (A1)+, (A2)+"
};

constexpr auto NEGATIVE_VALUES = {
    "CMPM.B D1, D2",
    "CMPM.B D1, (A1)",
    "CMPM.B D1, (A1)+",
    "CMPM.B D3, -(A1)",
    "CMPM.B D1, (2, A3)",
    "CMPM.B D1, (2, A3, D3.L)",
    "CMPM.B D1, (123).W",
    "CMPM.B D1, (128).L",
    "CMPM.B D1, (2, PC)",
    "CMPM.B D1, (2, PC, D3.L)",
    "CMPM.B D1, #123",
    "CMPM.B (A1), D0",
    "CMPM.B -(A1), D3",
    "CMPM.B (A1)+, D0",
    "CMPM.B (2, A3), D0",
    "CMPM.B (2, A3, D3.L), D0",
    "CMPM.B (123).W, D0",
    "CMPM.B (128).L, D0",
    "CMPM.B (2, PC), D0",
    "CMPM.B (2, PC, D3.L), D0",
    "CMPM.B #123, D0",
};

INSTANTIATE_TEST_SUITE_P(ParserADDXPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserADDXNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);

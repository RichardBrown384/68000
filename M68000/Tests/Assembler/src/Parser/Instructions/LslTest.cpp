#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "LSL.B D2, D1",
    "LSL.B #1, D1",
    "LSL.W D2, D1",
    "LSL.W #1, D1",
    "LSL.L D2, D1",
    "LSL.L #1, D1",
    "LSL.W (A1)",
    "LSL.W (A1)+",
    "LSL.W -(A1)",
    "LSL.W (10, A2)",
    "LSL.W (10, A2, A1.L)",
    "LSL.W (2000).W",
    "LSL.W (2000).L"
};

constexpr auto NEGATIVE_VALUES = {
    "LSL.B #0, D1",
    "LSL.B #9, D1",
    "LSL.B (A1), D1",
    "LSL.B (A1)+, D1",
    "LSL.B -(A1), D1",
    "LSL.B (10, A2), D1",
    "LSL.B (10, A2, A3.L), D1",
    "LSL.B (2000).W, D1",
    "LSL.B (2000).L, D1",
    "LSL.B (10, PC), D1",
    "LSL.B (10, PC, A3.L), D1",
    "LSL.W D1, (A1)",
    "LSL.W D1, (A1)+",
    "LSL.W D1, -(A1)",
    "LSL.W D1, (10, A2)",
    "LSL.W D1, (10, A2, A3.L)",
    "LSL.W D1, (2000).W",
    "LSL.W D1, (2000).L",
    "LSL.W D1, (10, PC)",
    "LSL.W D1, (10, PC, A3.L)",
    "LSL.W D1, #12",
    "LSL.L #2, (A1)",
    "LSL.L #2, (A1)+",
    "LSL.L #2, -(A1)",
    "LSL.L #2, (10, A2)",
    "LSL.L #2, (10, A2, A3.L)",
    "LSL.L #2, (2000).W",
    "LSL.L #2, (2000).L",
    "LSL.L #2, (10, PC)",
    "LSL.L #2, (10, PC, A3.L)",
    "LSL.L #2, #12",
    "LSL.W A1",
    "LSL.W (10, PC)",
    "LSL.W (10, PC, A1.L)",
    "LSL.B (A1)",
    "LSL.L (A1)",
};

INSTANTIATE_TEST_SUITE_P(ParserLSLPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserLSLNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
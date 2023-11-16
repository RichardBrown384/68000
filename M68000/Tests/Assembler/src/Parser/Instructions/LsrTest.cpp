#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "LSR.B D2, D1",
    "LSR.B #1, D1",
    "LSR.W D2, D1",
    "LSR.W #1, D1",
    "LSR.L D2, D1",
    "LSR.L #1, D1",
    "LSR.W (A1)",
    "LSR.W (A1)+",
    "LSR.W -(A1)",
    "LSR.W (10, A2)",
    "LSR.W (10, A2, A1.L)",
    "LSR.W (2000).W",
    "LSR.W (2000).L"
};

constexpr auto NEGATIVE_VALUES = {
    "LSR.B #0, D1",
    "LSR.B #9, D1",
    "LSR.B (A1), D1",
    "LSR.B (A1)+, D1",
    "LSR.B -(A1), D1",
    "LSR.B (10, A2), D1",
    "LSR.B (10, A2, A3.L), D1",
    "LSR.B (2000).W, D1",
    "LSR.B (2000).L, D1",
    "LSR.B (10, PC), D1",
    "LSR.B (10, PC, A3.L), D1",
    "LSR.W D1, (A1)",
    "LSR.W D1, (A1)+",
    "LSR.W D1, -(A1)",
    "LSR.W D1, (10, A2)",
    "LSR.W D1, (10, A2, A3.L)",
    "LSR.W D1, (2000).W",
    "LSR.W D1, (2000).L",
    "LSR.W D1, (10, PC)",
    "LSR.W D1, (10, PC, A3.L)",
    "LSR.W D1, #12",
    "LSR.L #2, (A1)",
    "LSR.L #2, (A1)+",
    "LSR.L #2, -(A1)",
    "LSR.L #2, (10, A2)",
    "LSR.L #2, (10, A2, A3.L)",
    "LSR.L #2, (2000).W",
    "LSR.L #2, (2000).L",
    "LSR.L #2, (10, PC)",
    "LSR.L #2, (10, PC, A3.L)",
    "LSR.L #2, #12",
    "LSR.W A1",
    "LSR.W (10, PC)",
    "LSR.W (10, PC, A1.L)",
    "LSR.B (A1)",
    "LSR.L (A1)",
};

INSTANTIATE_TEST_SUITE_P(ParserLSRPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserLSRNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
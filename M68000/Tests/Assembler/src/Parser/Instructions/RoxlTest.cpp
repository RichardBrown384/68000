#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "ROXL.B D2, D1",
    "ROXL.B #1, D1",
    "ROXL.W D2, D1",
    "ROXL.W #1, D1",
    "ROXL.L D2, D1",
    "ROXL.L #1, D1",
    "ROXL.W (A1)",
    "ROXL.W (A1)+",
    "ROXL.W -(A1)",
    "ROXL.W (10, A2)",
    "ROXL.W (10, A2, A1.L)",
    "ROXL.W (2000).W",
    "ROXL.W (2000).L"
};

constexpr auto NEGATIVE_VALUES = {
    "ROXL.B #0, D1",
    "ROXL.B #9, D1",
    "ROXL.B (A1), D1",
    "ROXL.B (A1)+, D1",
    "ROXL.B -(A1), D1",
    "ROXL.B (10, A2), D1",
    "ROXL.B (10, A2, A3.L), D1",
    "ROXL.B (2000).W, D1",
    "ROXL.B (2000).L, D1",
    "ROXL.B (10, PC), D1",
    "ROXL.B (10, PC, A3.L), D1",
    "ROXL.W D1, (A1)",
    "ROXL.W D1, (A1)+",
    "ROXL.W D1, -(A1)",
    "ROXL.W D1, (10, A2)",
    "ROXL.W D1, (10, A2, A3.L)",
    "ROXL.W D1, (2000).W",
    "ROXL.W D1, (2000).L",
    "ROXL.W D1, (10, PC)",
    "ROXL.W D1, (10, PC, A3.L)",
    "ROXL.W D1, #12",
    "ROXL.L #2, (A1)",
    "ROXL.L #2, (A1)+",
    "ROXL.L #2, -(A1)",
    "ROXL.L #2, (10, A2)",
    "ROXL.L #2, (10, A2, A3.L)",
    "ROXL.L #2, (2000).W",
    "ROXL.L #2, (2000).L",
    "ROXL.L #2, (10, PC)",
    "ROXL.L #2, (10, PC, A3.L)",
    "ROXL.L #2, #12",
    "ROXL.W A1",
    "ROXL.W (10, PC)",
    "ROXL.W (10, PC, A1.L)",
    "ROXL.B (A1)",
    "ROXL.L (A1)",
};

INSTANTIATE_TEST_SUITE_P(ParserROXLPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserROXLNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
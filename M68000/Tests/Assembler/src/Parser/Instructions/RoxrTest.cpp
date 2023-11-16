#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "ROXR.B D2, D1",
    "ROXR.B #1, D1",
    "ROXR.W D2, D1",
    "ROXR.W #1, D1",
    "ROXR.L D2, D1",
    "ROXR.L #1, D1",
    "ROXR.W (A1)",
    "ROXR.W (A1)+",
    "ROXR.W -(A1)",
    "ROXR.W (10, A2)",
    "ROXR.W (10, A2, A1.L)",
    "ROXR.W (2000).W",
    "ROXR.W (2000).L"
};

constexpr auto NEGATIVE_VALUES = {
    "ROXR.B #0, D1",
    "ROXR.B #9, D1",
    "ROXR.B (A1), D1",
    "ROXR.B (A1)+, D1",
    "ROXR.B -(A1), D1",
    "ROXR.B (10, A2), D1",
    "ROXR.B (10, A2, A3.L), D1",
    "ROXR.B (2000).W, D1",
    "ROXR.B (2000).L, D1",
    "ROXR.B (10, PC), D1",
    "ROXR.B (10, PC, A3.L), D1",
    "ROXR.W D1, (A1)",
    "ROXR.W D1, (A1)+",
    "ROXR.W D1, -(A1)",
    "ROXR.W D1, (10, A2)",
    "ROXR.W D1, (10, A2, A3.L)",
    "ROXR.W D1, (2000).W",
    "ROXR.W D1, (2000).L",
    "ROXR.W D1, (10, PC)",
    "ROXR.W D1, (10, PC, A3.L)",
    "ROXR.W D1, #12",
    "ROXR.L #2, (A1)",
    "ROXR.L #2, (A1)+",
    "ROXR.L #2, -(A1)",
    "ROXR.L #2, (10, A2)",
    "ROXR.L #2, (10, A2, A3.L)",
    "ROXR.L #2, (2000).W",
    "ROXR.L #2, (2000).L",
    "ROXR.L #2, (10, PC)",
    "ROXR.L #2, (10, PC, A3.L)",
    "ROXR.L #2, #12",
    "ROXR.W A1",
    "ROXR.W (10, PC)",
    "ROXR.W (10, PC, A1.L)",
    "ROXR.B (A1)",
    "ROXR.L (A1)",
};

INSTANTIATE_TEST_SUITE_P(ParserROXRPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserROXRNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
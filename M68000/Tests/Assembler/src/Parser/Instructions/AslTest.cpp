#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "ASL.B D2, D1",
    "ASL.B #1, D1",
    "ASL.W D2, D1",
    "ASL.W #1, D1",
    "ASL.L D2, D1",
    "ASL.L #1, D1",
    "ASL.W (A1)",
    "ASL.W (A1)+",
    "ASL.W -(A1)",
    "ASL.W (10, A2)",
    "ASL.W (10, A2, A1.L)",
    "ASL.W (2000).W",
    "ASL.W (2000).L"
};

constexpr auto NEGATIVE_VALUES = {
    "ASL.B #0, D1",
    "ASL.B #9, D1",
    "ASL.B (A1), D1",
    "ASL.B (A1)+, D1",
    "ASL.B -(A1), D1",
    "ASL.B (10, A2), D1",
    "ASL.B (10, A2, A3.L), D1",
    "ASL.B (2000).W, D1",
    "ASL.B (2000).L, D1",
    "ASL.B (10, PC), D1",
    "ASL.B (10, PC, A3.L), D1",
    "ASL.W D1, (A1)",
    "ASL.W D1, (A1)+",
    "ASL.W D1, -(A1)",
    "ASL.W D1, (10, A2)",
    "ASL.W D1, (10, A2, A3.L)",
    "ASL.W D1, (2000).W",
    "ASL.W D1, (2000).L",
    "ASL.W D1, (10, PC)",
    "ASL.W D1, (10, PC, A3.L)",
    "ASL.W D1, #12",
    "ASL.L #2, (A1)",
    "ASL.L #2, (A1)+",
    "ASL.L #2, -(A1)",
    "ASL.L #2, (10, A2)",
    "ASL.L #2, (10, A2, A3.L)",
    "ASL.L #2, (2000).W",
    "ASL.L #2, (2000).L",
    "ASL.L #2, (10, PC)",
    "ASL.L #2, (10, PC, A3.L)",
    "ASL.L #2, #12",
    "ASL.W A1",
    "ASL.W (10, PC)",
    "ASL.W (10, PC, A1.L)",
    "ASL.B (A1)",
    "ASL.L (A1)",
};

INSTANTIATE_TEST_SUITE_P(ParserASLPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserASLNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
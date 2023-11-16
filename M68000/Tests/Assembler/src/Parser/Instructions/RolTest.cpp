#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "ROL.B D2, D1",
    "ROL.B #1, D1",
    "ROL.W D2, D1",
    "ROL.W #1, D1",
    "ROL.L D2, D1",
    "ROL.L #1, D1",
    "ROL.W (A1)",
    "ROL.W (A1)+",
    "ROL.W -(A1)",
    "ROL.W (10, A2)",
    "ROL.W (10, A2, A1.L)",
    "ROL.W (2000).W",
    "ROL.W (2000).L"
};

constexpr auto NEGATIVE_VALUES = {
    "ROL.B #0, D1",
    "ROL.B #9, D1",
    "ROL.B (A1), D1",
    "ROL.B (A1)+, D1",
    "ROL.B -(A1), D1",
    "ROL.B (10, A2), D1",
    "ROL.B (10, A2, A3.L), D1",
    "ROL.B (2000).W, D1",
    "ROL.B (2000).L, D1",
    "ROL.B (10, PC), D1",
    "ROL.B (10, PC, A3.L), D1",
    "ROL.W D1, (A1)",
    "ROL.W D1, (A1)+",
    "ROL.W D1, -(A1)",
    "ROL.W D1, (10, A2)",
    "ROL.W D1, (10, A2, A3.L)",
    "ROL.W D1, (2000).W",
    "ROL.W D1, (2000).L",
    "ROL.W D1, (10, PC)",
    "ROL.W D1, (10, PC, A3.L)",
    "ROL.W D1, #12",
    "ROL.L #2, (A1)",
    "ROL.L #2, (A1)+",
    "ROL.L #2, -(A1)",
    "ROL.L #2, (10, A2)",
    "ROL.L #2, (10, A2, A3.L)",
    "ROL.L #2, (2000).W",
    "ROL.L #2, (2000).L",
    "ROL.L #2, (10, PC)",
    "ROL.L #2, (10, PC, A3.L)",
    "ROL.L #2, #12",
    "ROL.W A1",
    "ROL.W (10, PC)",
    "ROL.W (10, PC, A1.L)",
    "ROL.B (A1)",
    "ROL.L (A1)",
};

INSTANTIATE_TEST_SUITE_P(ParserROLPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserROLNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
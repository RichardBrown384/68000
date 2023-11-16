#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "ROR.B D2, D1",
    "ROR.B #1, D1",
    "ROR.W D2, D1",
    "ROR.W #1, D1",
    "ROR.L D2, D1",
    "ROR.L #1, D1",
    "ROR.W (A1)",
    "ROR.W (A1)+",
    "ROR.W -(A1)",
    "ROR.W (10, A2)",
    "ROR.W (10, A2, A1.L)",
    "ROR.W (2000).W",
    "ROR.W (2000).L"
};

constexpr auto NEGATIVE_VALUES = {
    "ROR.B #0, D1",
    "ROR.B #9, D1",
    "ROR.B (A1), D1",
    "ROR.B (A1)+, D1",
    "ROR.B -(A1), D1",
    "ROR.B (10, A2), D1",
    "ROR.B (10, A2, A3.L), D1",
    "ROR.B (2000).W, D1",
    "ROR.B (2000).L, D1",
    "ROR.B (10, PC), D1",
    "ROR.B (10, PC, A3.L), D1",
    "ROR.W D1, (A1)",
    "ROR.W D1, (A1)+",
    "ROR.W D1, -(A1)",
    "ROR.W D1, (10, A2)",
    "ROR.W D1, (10, A2, A3.L)",
    "ROR.W D1, (2000).W",
    "ROR.W D1, (2000).L",
    "ROR.W D1, (10, PC)",
    "ROR.W D1, (10, PC, A3.L)",
    "ROR.W D1, #12",
    "ROR.L #2, (A1)",
    "ROR.L #2, (A1)+",
    "ROR.L #2, -(A1)",
    "ROR.L #2, (10, A2)",
    "ROR.L #2, (10, A2, A3.L)",
    "ROR.L #2, (2000).W",
    "ROR.L #2, (2000).L",
    "ROR.L #2, (10, PC)",
    "ROR.L #2, (10, PC, A3.L)",
    "ROR.L #2, #12",
    "ROR.W A1",
    "ROR.W (10, PC)",
    "ROR.W (10, PC, A1.L)",
    "ROR.B (A1)",
    "ROR.L (A1)",
};

INSTANTIATE_TEST_SUITE_P(ParserRORPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserRORNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
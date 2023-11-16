#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "MOVEM.W (A1), D1-D2/A4-A5",
    "MOVEM.W (A1)+, D1-D2/A4-A5",
    "MOVEM.W (10, A1), D1-D2/A4-A5",
    "MOVEM.W (10, A1, A2.L), D1-D2/A4-A5",
    "MOVEM.W (1000).W, D1-D2/A4-A5",
    "MOVEM.W (1000).L, D1-D2/A4-A5",
    "MOVEM.W (2000, PC), D1-D2/A4-A5",
    "MOVEM.W (20, PC, A2.L), D1-D2/A4-A5",

    "MOVEM.L (A1), D1-D2/A4-A5",
    "MOVEM.L (A1)+, D1-D2/A4-A5",
    "MOVEM.L (10, A1), D1-D2/A4-A5",
    "MOVEM.L (10, A1, A2.L), D1-D2/A4-A5",
    "MOVEM.L (1000).W, D1-D2/A4-A5",
    "MOVEM.L (1000).L, D1-D2/A4-A5",
    "MOVEM.L (2000, PC), D1-D2/A4-A5",
    "MOVEM.L (20, PC, A2.L), D1-D2/A4-A5",

    "MOVEM.W D1-D2/A4-A5, (A1)",
    "MOVEM.W D1-D2/A4-A5, -(A1)",
    "MOVEM.W D1-D2/A4-A5, (10, A1)",
    "MOVEM.W D1-D2/A4-A5, (10, A1, A2.L)",
    "MOVEM.W D1-D2/A4-A5, (1000).W",
    "MOVEM.W D1-D2/A4-A5, (1000).L",

    "MOVEM.L D1-D2/A4-A5, (A1)",
    "MOVEM.L D1-D2/A4-A5, -(A1)",
    "MOVEM.L D1-D2/A4-A5, (10, A1)",
    "MOVEM.L D1-D2/A4-A5, (10, A1, A2.L)",
    "MOVEM.L D1-D2/A4-A5, (1000).W",
    "MOVEM.L D1-D2/A4-A5, (1000).L"
};

constexpr auto NEGATIVE_VALUES = {
    "MOVEM.W -(A1), D1-D2/A4-A5",
    "MOVEM.W #123, D1-D2/A4-A5",

    "MOVEM.L -(A1), D1-D2/A4-A5",
    "MOVEM.L #123, D1-D2/A4-A5",

    "MOVEM.W D1-D2/A4-A5, D1",
    "MOVEM.W D1-D2/A4-A5, A1",
    "MOVEM.W D1-D2/A4-A5, (A1)+",
    "MOVEM.W D1-D2/A4-A5, (2000, PC)",
    "MOVEM.W D1-D2/A4-A5, (20, PC, A2.L)",
    "MOVEM.W D1-D2/A4-A5, #1121",

    "MOVEM.L D1-D2/A4-A5, D1",
    "MOVEM.L D1-D2/A4-A5, A1",
    "MOVEM.L D1-D2/A4-A5, (A1)+",
    "MOVEM.L D1-D2/A4-A5, (2000, PC)",
    "MOVEM.L D1-D2/A4-A5, (20, PC, A2.L)",
    "MOVEM.L D1-D2/A4-A5, #1121"
};

INSTANTIATE_TEST_SUITE_P(ParserMOVEMPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserMOVEMNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
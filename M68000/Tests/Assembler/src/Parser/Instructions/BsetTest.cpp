#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "BSET.L D1, D2",
    "BSET.L #1, D2",
    "BSET.B D1, (A1)",
    "BSET.B #1, (A1)",
    "BSET.B D1, (A1)+",
    "BSET.B D1, -(A1)",
    "BSET.B D1, (10, A1)",
    "BSET.B D1, (10, A1, A2.L)",
    "BSET.B D1, (2000).W",
    "BSET.B D1, (2000).L",
    "BSET.B #1, (A1)",
    "BSET.B #1, (A1)+",
    "BSET.B #1, -(A1)",
    "BSET.B #1, (10, A1)",
    "BSET.B #1, (10, A1, A2.L)",
    "BSET.B #1, (2000).W",
    "BSET.B #1, (2000).L",
};

constexpr auto NEGATIVE_VALUES = {
    "BSET.W D1, D2",
    "BSET.B D1, D2",
    "BSET.W #2, D2",
    "BSET.B #2, D2",
    "BSET.W D1, (A1)",
    "BSET.L D1, (A1)",
    "BSET.W #1, (A1)",
    "BSET.L #1, (A1)",
    "BSET.B D1, A1",
    "BSET.B D1, (10, PC)",
    "BSET.B D1, (10, PC, A2.L)",
    "BSET.B D1, #100",
    "BSET.L D1, A1",
    "BSET.L D1, (10, PC)",
    "BSET.L D1, (10, PC, A2.L)",
    "BSET.L D1, #100",
    "BSET.B A1, (A1)",
    "BSET.B (A1), (A1)",
    "BSET.B (A1)+, (A1)",
    "BSET.B -(A1), (A1)",
    "BSET.B (10, A1), (A1)",
    "BSET.B (10, A1, A2.L), (A1)",
    "BSET.B (2000).W, (A1)",
    "BSET.B (2000).L, (A1)",
    "BSET.B (10, PC), (A1)",
    "BSET.B (10, PC, D2.L), (A1)",
    "BSET.L A1, D1",
    "BSET.L (A1), D1",
    "BSET.L (A1)+, D1",
    "BSET.L -(A1), D1",
    "BSET.L (10, A1), D1",
    "BSET.L (10, A1, A2.L), D1",
    "BSET.L (2000).W, D1",
    "BSET.L (2000).L, D1",
    "BSET.L (10, PC), D1",
    "BSET.L (10, PC, D2.L), D1",
};

INSTANTIATE_TEST_SUITE_P(ParserBSETPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserBSETNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
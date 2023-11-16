#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "BCHG.L D1, D2",
    "BCHG.L #1, D2",
    "BCHG.B D1, (A1)",
    "BCHG.B #1, (A1)",
    "BCHG.B D1, (A1)+",
    "BCHG.B D1, -(A1)",
    "BCHG.B D1, (10, A1)",
    "BCHG.B D1, (10, A1, A2.L)",
    "BCHG.B D1, (2000).W",
    "BCHG.B D1, (2000).L",
    "BCHG.B #1, (A1)",
    "BCHG.B #1, (A1)+",
    "BCHG.B #1, -(A1)",
    "BCHG.B #1, (10, A1)",
    "BCHG.B #1, (10, A1, A2.L)",
    "BCHG.B #1, (2000).W",
    "BCHG.B #1, (2000).L",
};

constexpr auto NEGATIVE_VALUES = {
    "BCHG.W D1, D2",
    "BCHG.B D1, D2",
    "BCHG.W #2, D2",
    "BCHG.B #2, D2",
    "BCHG.W D1, (A1)",
    "BCHG.L D1, (A1)",
    "BCHG.W #1, (A1)",
    "BCHG.L #1, (A1)",
    "BCHG.B D1, A1",
    "BCHG.B D1, (10, PC)",
    "BCHG.B D1, (10, PC, A2.L)",
    "BCHG.B D1, #100",
    "BCHG.L D1, A1",
    "BCHG.L D1, (10, PC)",
    "BCHG.L D1, (10, PC, A2.L)",
    "BCHG.L D1, #100",
    "BCHG.B A1, (A1)",
    "BCHG.B (A1), (A1)",
    "BCHG.B (A1)+, (A1)",
    "BCHG.B -(A1), (A1)",
    "BCHG.B (10, A1), (A1)",
    "BCHG.B (10, A1, A2.L), (A1)",
    "BCHG.B (2000).W, (A1)",
    "BCHG.B (2000).L, (A1)",
    "BCHG.B (10, PC), (A1)",
    "BCHG.B (10, PC, D2.L), (A1)",
    "BCHG.L A1, D1",
    "BCHG.L (A1), D1",
    "BCHG.L (A1)+, D1",
    "BCHG.L -(A1), D1",
    "BCHG.L (10, A1), D1",
    "BCHG.L (10, A1, A2.L), D1",
    "BCHG.L (2000).W, D1",
    "BCHG.L (2000).L, D1",
    "BCHG.L (10, PC), D1",
    "BCHG.L (10, PC, D2.L), D1",
};

INSTANTIATE_TEST_SUITE_P(ParserBCHGPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserBCHGNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
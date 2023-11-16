#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "LEA (A1), A2",
    "LEA (10, A1), A2",
    "LEA (10, A1, D2.L), A2",
    "LEA (2000).W, A2",
    "LEA (2000).L, A2",
    "LEA (10, PC), A2",
    "LEA (10, PC, D2.L), A2"
};

constexpr auto NEGATIVE_VALUES = {
    "LEA D1, A2",
    "LEA A1, A2",
    "LEA (A1)+, A2",
    "LEA -(A1), A2",
    "LEA #1, A2",
    "LEA (A1), (A2)",
    "LEA (A1), (A2)+",
    "LEA (A1), -(A2)",
    "LEA (A1), (10, A2)",
    "LEA (A1), (10, A2, D2.L)",
    "LEA (A1), (2000).W",
    "LEA (A1), (2000).L",
    "LEA (A1), (2, PC)",
    "LEA (A1), (2, PC, D2.L)"
};

INSTANTIATE_TEST_SUITE_P(ParserLEAPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
 );

INSTANTIATE_TEST_SUITE_P(ParserLEANegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);

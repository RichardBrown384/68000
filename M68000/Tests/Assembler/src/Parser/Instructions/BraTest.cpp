#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "BRA.B *+8",
    "BRA.W *+800",
    "BRA.B *-8",
    "BRA.W *-800",
};

constexpr auto NEGATIVE_VALUES = {
    "BRA.L *+100",
    "BRA.L *-100",
};

INSTANTIATE_TEST_SUITE_P(ParserBRAPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserBRANegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
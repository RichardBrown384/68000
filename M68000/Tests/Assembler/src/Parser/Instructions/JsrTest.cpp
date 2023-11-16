#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "JSR (A1)",
    "JSR (10, A1)",
    "JSR (10, A1, D2.L)",
    "JSR (2000).W",
    "JSR (2000).L",
    "JSR (10, PC)",
    "JSR (10, PC, D2.L)"
};

constexpr auto NEGATIVE_VALUES = {
    "JSR D1",
    "JSR A1",
    "JSR (A1)+",
    "JSR -(A1)",
    "JSR #1"
};

INSTANTIATE_TEST_SUITE_P(ParserJSRPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
 );

INSTANTIATE_TEST_SUITE_P(ParserJSRNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);

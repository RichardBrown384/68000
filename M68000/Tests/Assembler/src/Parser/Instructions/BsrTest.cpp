#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "BSR.B *+8",
    "BSR.W *+800",
    "BSR.B *-8",
    "BSR.W *-800",
};

constexpr auto NEGATIVE_VALUES = {
    "BSR.L *+100",
    "BSR.L *-100",
};

INSTANTIATE_TEST_SUITE_P(ParserBSRPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserBSRNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
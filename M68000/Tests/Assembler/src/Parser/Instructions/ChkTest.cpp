#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "CHK D1, D2",
    "CHK (A1), D2",
    "CHK (A1)+, D2",
    "CHK -(A1), D2",
    "CHK (15, A1), D2",
    "CHK (15, A1, D1.L), D2",
    "CHK (200).W, D2",
    "CHK (200).L, D2",
    "CHK (15, PC), D2",
    "CHK (15, PC, D1.L), D2",
    "CHK #200, D2"
};

constexpr auto NEGATIVE_VALUES = {
    "CHK A1, D2",
};

INSTANTIATE_TEST_SUITE_P(ParserCHKPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserCHKNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
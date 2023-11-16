#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "EXG D0, D1",
    "EXG A2, A2",
    "EXG A2, D1",
    "EXG D1, D2"
};

constexpr auto NEGATIVE_VALUES = {
    "EXG (A1), D0",
    "EXG (A1)+, D0",
    "EXG -(A1), D0",
    "EXG (2, A3), D0",
    "EXG (2, A3, D3.L), D0",
    "EXG (123).W, D0",
    "EXG (128).L, D0",
    "EXG (2, PC), D0",
    "EXG (2, PC, D3.L), D0",
    "EXG #123, D0",
    "EXG D1, (A1)",
    "EXG D1, (A1)+",
    "EXG D1, -(A1)",
    "EXG D1, (2, A3)",
    "EXG D1, (2, A3, D3.L)",
    "EXG D1, (123).W",
    "EXG D1, (128).L",
    "EXG D1, (2, PC)",
    "EXG D1, (2, PC, D3.L)",
    "EXG D1, #123"
};

INSTANTIATE_TEST_SUITE_P(ParserEXGPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
 );

INSTANTIATE_TEST_SUITE_P(ParserEXGNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);

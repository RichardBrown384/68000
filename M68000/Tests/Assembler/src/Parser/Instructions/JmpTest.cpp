#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "JMP (A1)",
    "JMP (10, A1)",
    "JMP (10, A1, D2.L)",
    "JMP (2000).W",
    "JMP (2000).L",
    "JMP (10, PC)",
    "JMP (10, PC, D2.L)"
};

constexpr auto NEGATIVE_VALUES = {
    "JMP D1",
    "JMP A1",
    "JMP (A1)+",
    "JMP -(A1)",
    "JMP #1"
};

INSTANTIATE_TEST_SUITE_P(ParserJMPPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
 );

INSTANTIATE_TEST_SUITE_P(ParserJMPNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);

#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "TRAP #1",
    "TRAP #0x0",
    "TRAP #0xF"
};

constexpr auto NEGATIVE_VALUES = {
    "TRAP D1",
    "TRAP A1",
    "TRAP (A1)",
    "TRAP (A1)+",
    "TRAP -(A1)",
    "TRAP (15, A1)",
    "TRAP (15, A1, D1.L)",
    "TRAP (200).W",
    "TRAP (200).L",
    "TRAP (15, PC)",
    "TRAP (15, PC, D1.L)",
    "TRAP #-1",
    "TRAP #16",
};

INSTANTIATE_TEST_SUITE_P(ParserTRAPPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserTRAPNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
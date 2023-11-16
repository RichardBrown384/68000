#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "STOP #0x0000",
    "STOP #0xFFFF"
};

constexpr auto NEGATIVE_VALUES = {
    "STOP D1",
    "STOP A1",
    "STOP (A1)",
    "STOP (A1)+",
    "STOP -(A1)",
    "STOP (15, A1)",
    "STOP (15, A1, D1.L)",
    "STOP (200).W",
    "STOP (200).L",
    "STOP (15, PC)",
    "STOP (15, PC, D1.L)"
};

INSTANTIATE_TEST_SUITE_P(ParserSTOPPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserSTOPNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
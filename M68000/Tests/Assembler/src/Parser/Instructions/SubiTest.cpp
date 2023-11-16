#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "SUBI.B #1, D2",
    "SUBI.B #1, (A2)",
    "SUBI.B #1, (A2)+",
    "SUBI.B #1, -(A2)",
    "SUBI.B #1, (2, A3)",
    "SUBI.B #1, (2, A3, D4.L)",
    "SUBI.B #1, (2, A3, A4.L)",
    "SUBI.B #1, (123).W",
    "SUBI.B #1, (123).L",
    "SUBI.B #255, D2",
    "SUBI.W #65535, D2",
    "SUBI.L #65536, D2"
};

constexpr auto NEGATIVE_VALUES = {
    "SUBI.B #1, A2",
    "SUBI.B #1, (2, PC)",
    "SUBI.B #1, (2, PC, D3.L)",
    "SUBI.B #1, (2, PC, A3.L)",
    "SUBI.B #1, #1",
    "SUBI.B #256, D2",
    "SUBI.W #65536, D2"
};

INSTANTIATE_TEST_SUITE_P(ParserSUBIPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserSUBINegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
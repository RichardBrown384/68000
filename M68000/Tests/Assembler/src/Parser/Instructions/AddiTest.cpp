#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "ADDI.B #1, D2",
    "ADDI.B #1, (A2)",
    "ADDI.B #1, (A2)+",
    "ADDI.B #1, -(A2)",
    "ADDI.B #1, (2, A3)",
    "ADDI.B #1, (2, A3, D4.L)",
    "ADDI.B #1, (2, A3, A4.L)",
    "ADDI.B #1, (123).W",
    "ADDI.B #1, (123).L",
    "ADDI.B #255, D2",
    "ADDI.W #65535, D2",
    "ADDI.L #65536, D2"
};

constexpr auto NEGATIVE_VALUES = {
    "ADDI.B #1, A2",
    "ADDI.B #1, (2, PC)",
    "ADDI.B #1, (2, PC, D3.L)",
    "ADDI.B #1, (2, PC, A3.L)",
    "ADDI.B #1, #1",
    "ADDI.B #256, D2",
    "ADDI.W #65536, D2"
};

INSTANTIATE_TEST_SUITE_P(ParserADDIPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserADDINegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
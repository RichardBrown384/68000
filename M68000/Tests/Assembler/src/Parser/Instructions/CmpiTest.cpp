#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "CMPI.B #1, D2",
    "CMPI.B #1, (A2)",
    "CMPI.B #1, (A2)+",
    "CMPI.B #1, -(A2)",
    "CMPI.B #1, (2, A3)",
    "CMPI.B #1, (2, A3, D4.L)",
    "CMPI.B #1, (2, A3, A4.L)",
    "CMPI.B #1, (123).W",
    "CMPI.B #1, (123).L",
    "CMPI.B #255, D2",
    "CMPI.W #65535, D2",
    "CMPI.L #65536, D2"
};

constexpr auto NEGATIVE_VALUES = {
    "CMPI.B #1, A2",
    "CMPI.B #1, (2, PC)",
    "CMPI.B #1, (2, PC, D3.L)",
    "CMPI.B #1, (2, PC, A3.L)",
    "CMPI.B #1, #1",
    "CMPI.B #256, D2",
    "CMPI.W #65536, D2"
};

INSTANTIATE_TEST_SUITE_P(ParserCMPIPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserCMPINegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
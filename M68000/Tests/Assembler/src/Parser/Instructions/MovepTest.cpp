#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "MOVEP.W D0, (10, A1)",
    "MOVEP.W (10, A1), D0",
    "MOVEP.L D0, (10, A1)",
    "MOVEP.L (10, A1), D0",
};

constexpr auto NEGATIVE_VALUES = {
    "MOVEP.B D0, (10, A1)",
    "MOVEP.B (10, A1), D0",
    "MOVEP.W D0, A0",
    "MOVEP.W D0, (A1)",
    "MOVEP.W D0, (A1)+",
    "MOVEP.W D0, -(A1)",
    "MOVEP.W D0, (2, A1, D2.L)",
    "MOVEP.W D0, (123).W",
    "MOVEP.W D0, (123).L",
    "MOVEP.W D0, (2, PC)",
    "MOVEP.W D0, (2, PC, D2.L)",
    "MOVEP.W D0, #123",
    "MOVEP.W A0, D0",
    "MOVEP.W (A1), D0",
    "MOVEP.W (A1)+, D0",
    "MOVEP.W -(A1), D0",
    "MOVEP.W (2, A1, D2.L), D0",
    "MOVEP.W (123).W, D0",
    "MOVEP.W (123).L, D0",
    "MOVEP.W (2, PC), D0",
    "MOVEP.W (2, PC, D2.L), D0",
    "MOVEP.W #123, D0",
    "MOVEP.W (2, A2), (2, A2)",
    "MOVEP.W D0, D0"
};

INSTANTIATE_TEST_SUITE_P(ParserMOVEPPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserMOVEPNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
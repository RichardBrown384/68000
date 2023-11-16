#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "MOVE.L USP, A1",
    "MOVE.L A1, USP"
};

constexpr auto NEGATIVE_VALUES = {
    "MOVE.B A1, USP",
    "MOVE.W A1, USP",
    "MOVE.L USP, USP",
    "MOVE.L D1, USP",
    "MOVE.L (A1), USP",
    "MOVE.L (A1)+, USP",
    "MOVE.L -(A1), USP",
    "MOVE.L (2, A1), USP",
    "MOVE.L (2, A1, D2.L), USP",
    "MOVE.L (123).W, USP",
    "MOVE.L (123).L, USP",
    "MOVE.L (2, PC), USP",
    "MOVE.L (2, PC, D2.L), USP",
    "MOVE.L #-1, USP",
    "MOVE.L USP, D1",
    "MOVE.L USP, (A1)",
    "MOVE.L USP, (A1)+",
    "MOVE.L USP, -(A1)",
    "MOVE.L USP, (2, A1)",
    "MOVE.L USP, (2, A1, D2.L)",
    "MOVE.L USP, (123).W",
    "MOVE.L USP, (123).L",
    "MOVE.L USP, (2, PC)",
    "MOVE.L USP, (2, PC, D2.L)",
    "MOVE.L USP, #123"
};

INSTANTIATE_TEST_SUITE_P(ParserMOVEUSPPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserMOVEUSPNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
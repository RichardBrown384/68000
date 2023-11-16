#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "MOVE.B D0, D1",
    "MOVE.W D0, D1",
    "MOVE.L D0, D1",
    "MOVE.W D0, D1",
    "MOVE.W D0, (A1)",
    "MOVE.W D0, (A1)+",
    "MOVE.W D0, -(A1)",
    "MOVE.W D0, (10, A1)",
    "MOVE.W D0, (10, A1, D2.L)",
    "MOVE.W D0, (10, A1, A2.L)",
    "MOVE.W D0, (123).W",
    "MOVE.W D0, (123).L",
    "MOVE.W D0, D1",
    "MOVE.W A0, D1",
    "MOVE.W (A1), D1",
    "MOVE.W (A1)+, D1",
    "MOVE.W -(A1), D1",
    "MOVE.W (10, A1), D3",
    "MOVE.W (10, A1, D2.L), D3",
    "MOVE.W (10, A1, A2.L), D3",
    "MOVE.W (123).W, D3",
    "MOVE.W (123).L, D3",
    "MOVE.W (10, PC, D2.L), D3",
    "MOVE.W (10, PC, A2.L), D3",
    "MOVE.W #123, D3"
};

constexpr auto NEGATIVE_VALUES = {
    "MOVE.B A2, D3",
    "MOVE.W D0, A1",
    "MOVE.W D0, (10, PC, A1.L)",
    "MOVE.W D0, (10, PC, D1.L)",
    "MOVE.W D0, #123",
};

INSTANTIATE_TEST_SUITE_P(ParserMOVEPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserMOVENegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "SUB.B D0, D1",
    "SUB.W D0, D1",
    "SUB.L D0, D1",
    "SUB.W D0, D1",
    "SUB.W D0, (A1)",
    "SUB.W D0, (A1)+",
    "SUB.W D0, -(A1)",
    "SUB.W D0, (10, A1)",
    "SUB.W D0, (10, A1, D2.L)",
    "SUB.W D0, (10, A1, A2.L)",
    "SUB.W D0, (123).W",
    "SUB.W D0, (123).L",
    "SUB.W D0, D1",
    "SUB.W A0, D1",
    "SUB.W (A1), D1",
    "SUB.W (A1)+, D1",
    "SUB.W -(A1), D1",
    "SUB.W (10, A1), D3",
    "SUB.W (10, A1, D2.L), D3",
    "SUB.W (10, A1, A2.L), D3",
    "SUB.W (123).W, D3",
    "SUB.W (123).L, D3",
    "SUB.W (10, PC), D3",
    "SUB.W (10, PC, D2.L), D3",
    "SUB.W (10, PC, A2.L), D3",
    "SUB.W #123, D3"
};

constexpr auto NEGATIVE_VALUES = {
    "SUB.B A2, D3",
    "SUB.W D0, A1",
    "SUB.W D0, (10, PC, A1.L)",
    "SUB.W D0, (10, PC, D1.L)",
    "SUB.W D0, #123",
    "SUB.W (A1), (A2)"
};

INSTANTIATE_TEST_SUITE_P(ParserSUBPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserSUBNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
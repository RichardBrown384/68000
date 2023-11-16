#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "ADD.B D0, D1",
    "ADD.W D0, D1",
    "ADD.L D0, D1",
    "ADD.W D0, D1",
    "ADD.W D0, (A1)",
    "ADD.W D0, (A1)+",
    "ADD.W D0, -(A1)",
    "ADD.W D0, (10, A1)",
    "ADD.W D0, (10, A1, D2.L)",
    "ADD.W D0, (10, A1, A2.L)",
    "ADD.W D0, (123).W",
    "ADD.W D0, (123).L",
    "ADD.W D0, D1",
    "ADD.W A0, D1",
    "ADD.W (A1), D1",
    "ADD.W (A1)+, D1",
    "ADD.W -(A1), D1",
    "ADD.W (10, A1), D3",
    "ADD.W (10, A1, D2.L), D3",
    "ADD.W (10, A1, A2.L), D3",
    "ADD.W (123).W, D3",
    "ADD.W (123).L, D3",
    "ADD.W (10, PC, D2.L), D3",
    "ADD.W (10, PC, A2.L), D3",
    "ADD.W #123, D3"
};

constexpr auto NEGATIVE_VALUES = {
    "ADD.B A2, D3",
    "ADD.W D0, A1",
    "ADD.W D0, (10, PC, A1.L)",
    "ADD.W D0, (10, PC, D1.L)",
    "ADD.W D0, #123",
    "ADD.W (A1), (A2)"
};

INSTANTIATE_TEST_SUITE_P(ParserADDPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserADDNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
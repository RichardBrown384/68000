#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "EOR.B D0, D1",
    "EOR.W D0, D1",
    "EOR.L D0, D1",
    "EOR.W D0, D1",
    "EOR.W D0, (A1)",
    "EOR.W D0, (A1)+",
    "EOR.W D0, -(A1)",
    "EOR.W D0, (10, A1)",
    "EOR.W D0, (10, A1, D2.L)",
    "EOR.W D0, (10, A1, A2.L)",
    "EOR.W D0, (123).W",
    "EOR.W D0, (123).L"
};

constexpr auto NEGATIVE_VALUES = {
    "EOR.W (A1), D1",
    "EOR.W (A1)+, D1",
    "EOR.W -(A1), D1",
    "EOR.W (10, A1), D3",
    "EOR.W (10, A1, D2.L), D3",
    "EOR.W (10, A1, A2.L), D3",
    "EOR.W (123).W, D3",
    "EOR.W (123).L, D3",
    "EOR.W (10, PC, D2.L), D3",
    "EOR.W (10, PC, A2.L), D3",
    "EOR.W #123, D3",
    "EOR.W D0, A1",
    "EOR.W D0, (10, PC, A1.L)",
    "EOR.W D0, (10, PC, D1.L)",
    "EOR.W D0, #123",
    "EOR.W A0, D0",
    "EOR.W (A1), (A2)"
};

INSTANTIATE_TEST_SUITE_P(ParserEORPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserEORNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
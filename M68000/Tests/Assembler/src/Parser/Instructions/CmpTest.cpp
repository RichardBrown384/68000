#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "CMP.B D0, D1",
    "CMP.W D0, D1",
    "CMP.L D0, D1",
    "CMP.W A0, D1",
    "CMP.W (A1), D1",
    "CMP.W (A1)+, D1",
    "CMP.W -(A1), D1",
    "CMP.W (10, A1), D3",
    "CMP.W (10, A1, D2.L), D3",
    "CMP.W (10, A1, A2.L), D3",
    "CMP.W (123).W, D3",
    "CMP.W (123).L, D3",
    "CMP.W (10, PC), D3",
    "CMP.W (10, PC, D2.L), D3",
    "CMP.W (10, PC, A2.L), D3",
    "CMP.W #123, D3"
};

constexpr auto NEGATIVE_VALUES = {
    "CMP.B A2, D3",
    "CMP.W D0, A1",
    "CMP.W D0, (A1)",
    "CMP.W D0, (A1)+",
    "CMP.W D0, -(A1)",
    "CMP.W D0, (10, A1)",
    "CMP.W D0, (10, A1, D2.L)",
    "CMP.W D0, (10, A1, A2.L)",
    "CMP.W D0, (123).W",
    "CMP.W D0, (123).L",
    "CMP.W D0, (10, PC)",
    "CMP.W D0, (10, PC, A1.L)",
    "CMP.W D0, (10, PC, D1.L)",
    "CMP.W D0, #123",
    "CMP.W (A1), (A2)"
};

INSTANTIATE_TEST_SUITE_P(ParserCMPPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserCMPNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
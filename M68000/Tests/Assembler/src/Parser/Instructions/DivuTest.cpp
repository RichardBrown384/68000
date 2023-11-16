#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "DIVU D0, D1",
    "DIVU (A1), D1",
    "DIVU (A1)+, D1",
    "DIVU -(A1), D1",
    "DIVU (10, A1), D3",
    "DIVU (10, A1, D2.L), D3",
    "DIVU (123).W, D3",
    "DIVU (123).L, D3",
    "DIVU (10, PC, D2.L), D3",
    "DIVU #123, D3"
};

constexpr auto NEGATIVE_VALUES = {
    "DIVU A0, D1",    
    "DIVU D0, A1",
    "DIVU D0, (A1)",
    "DIVU D0, (A1)+",
    "DIVU D0, -(A1)",
    "DIVU D0, (10, A1)",
    "DIVU D0, (10, A1, D2.L)",
    "DIVU D0, (123).W",
    "DIVU D0, (123).L",
    "DIVU D0, (10, PC, D2.L)",
    "DIVU D0, #123"
};

INSTANTIATE_TEST_SUITE_P(ParserDIVUPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserDIVUNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
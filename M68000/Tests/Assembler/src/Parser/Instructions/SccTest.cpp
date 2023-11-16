#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "ST D3",
    "SF D3",
    "SHI D3",
    "SLS D3",
    "SCC D3",
    "SCS D3",
    "SNE D3",
    "SEQ D3",
    "SVC D3",
    "SVS D3",
    "SPL D3",
    "SMI D3",
    "SGE D3",
    "SLT D3",
    "SGT D3",
    "SLE D3",
    "SVC D1",
    "SVC (A1)",
    "SVC (A1)+",
    "SVC -(A1)",
    "SVC (15, A1)",
    "SVC (15, A1, D1.L)",
    "SVC (200).W",
    "SVC (200).L",
};

constexpr auto NEGATIVE_VALUES = {
    "SVC (10, PC)",
    "SVC (10, PC, A2.L)",
    "SVC #123"
};

INSTANTIATE_TEST_SUITE_P(ParserSccPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserSccNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
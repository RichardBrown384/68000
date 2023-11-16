#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "SUBA.W D1, A0",
    "SUBA.L D1, A0",
    "SUBA.L A1, A0",
    "SUBA.L (A1), A0",
    "SUBA.L (A1)+, A0",
    "SUBA.L -(A1), A0",
    "SUBA.L (2, A1), A0",
    "SUBA.L (2, A1, D2.L), A0",
    "SUBA.L (123).W, A0",
    "SUBA.L (123).L, A0",
    "SUBA.L (2, PC), A0",
    "SUBA.L (2, PC, D2.L), A0",
    "SUBA.W #-1, A0",
    "SUBA.W #3432, A0",
    "SUBA.L #88888, A0"
};

constexpr auto NEGATIVE_VALUES = {
    "SUBA.L D0, D1",
    "SUBA.L D0, (A1)",
    "SUBA.L D0, (A1)+",
    "SUBA.L D0, -(A1)",
    "SUBA.L D0, (2, A1)",
    "SUBA.L D0, (2, A1, D2.L)",
    "SUBA.L D0, (123).W",
    "SUBA.L D0, (123).L",
    "SUBA.L D0, (2, PC)",
    "SUBA.L D0, (2, PC, D2.L)",
    "SUBA.L D0, #123",
    "SUBA.B D0, A0",
    "SUBA.W #65536, A0"
};

INSTANTIATE_TEST_SUITE_P(ParserSUBAPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserSUBANegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
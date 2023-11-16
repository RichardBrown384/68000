#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "ADDA.W D1, A0",
    "ADDA.L D1, A0",
    "ADDA.L A1, A0",
    "ADDA.L (A1), A0",
    "ADDA.L (A1)+, A0",
    "ADDA.L -(A1), A0",
    "ADDA.L (2, A1), A0",
    "ADDA.L (2, A1, D2.L), A0",
    "ADDA.L (123).W, A0",
    "ADDA.L (123).L, A0",
    "ADDA.L (2, PC), A0",
    "ADDA.L (2, PC, D2.L), A0",
    "ADDA.W #-1, A0",
    "ADDA.W #3432, A0",
    "ADDA.L #88888, A0"
};

constexpr auto NEGATIVE_VALUES = {
    "ADDA.L D0, D1",
    "ADDA.L D0, (A1)",
    "ADDA.L D0, (A1)+",
    "ADDA.L D0, -(A1)",
    "ADDA.L D0, (2, A1)",
    "ADDA.L D0, (2, A1, D2.L)",
    "ADDA.L D0, (123).W",
    "ADDA.L D0, (123).L",
    "ADDA.L D0, (2, PC)",
    "ADDA.L D0, (2, PC, D2.L)",
    "ADDA.L D0, #123",
    "ADDA.B D0, A0",
    "ADDA.W #65536, A0"
};

INSTANTIATE_TEST_SUITE_P(ParserADDAPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserADDANegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
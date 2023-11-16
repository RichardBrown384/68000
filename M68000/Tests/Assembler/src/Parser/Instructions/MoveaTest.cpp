#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "MOVEA.W D1, A0",
    "MOVEA.L D1, A0",
    "MOVEA.L A1, A0",
    "MOVEA.L (A1), A0",
    "MOVEA.L (A1)+, A0",
    "MOVEA.L -(A1), A0",
    "MOVEA.L (2, A1), A0",
    "MOVEA.L (2, A1, D2.L), A0",
    "MOVEA.L (123).W, A0",
    "MOVEA.L (123).L, A0",
    "MOVEA.L (2, PC), A0",
    "MOVEA.L (2, PC, D2.L), A0",
    "MOVEA.W #-1, A0",
    "MOVEA.W #3432, A0",
    "MOVEA.L #88888, A0"
};

constexpr auto NEGATIVE_VALUES = {
    "MOVEA.L D0, D1",
    "MOVEA.L D0, (A1)",
    "MOVEA.L D0, (A1)+",
    "MOVEA.L D0, -(A1)",
    "MOVEA.L D0, (2, A1)",
    "MOVEA.L D0, (2, A1, D2.L)",
    "MOVEA.L D0, (123).W",
    "MOVEA.L D0, (123).L",
    "MOVEA.L D0, (2, PC)",
    "MOVEA.L D0, (2, PC, D2.L)",
    "MOVEA.L D0, #123",
    "MOVEA.B D0, A0",
    "MOVEA.W #65536, A0"
};

INSTANTIATE_TEST_SUITE_P(ParserMOVEAPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserMOVEANegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
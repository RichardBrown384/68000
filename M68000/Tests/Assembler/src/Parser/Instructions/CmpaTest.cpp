#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "CMPA.W D1, A0",
    "CMPA.L D1, A0",
    "CMPA.L A1, A0",
    "CMPA.L (A1), A0",
    "CMPA.L (A1)+, A0",
    "CMPA.L -(A1), A0",
    "CMPA.L (2, A1), A0",
    "CMPA.L (2, A1, D2.L), A0",
    "CMPA.L (123).W, A0",
    "CMPA.L (123).L, A0",
    "CMPA.L (2, PC), A0",
    "CMPA.L (2, PC, D2.L), A0",
    "CMPA.W #-1, A0",
    "CMPA.W #3432, A0",
    "CMPA.L #88888, A0"
};

constexpr auto NEGATIVE_VALUES = {
    "CMPA.L D0, D1",
    "CMPA.L D0, (A1)",
    "CMPA.L D0, (A1)+",
    "CMPA.L D0, -(A1)",
    "CMPA.L D0, (2, A1)",
    "CMPA.L D0, (2, A1, D2.L)",
    "CMPA.L D0, (123).W",
    "CMPA.L D0, (123).L",
    "CMPA.L D0, (2, PC)",
    "CMPA.L D0, (2, PC, D2.L)",
    "CMPA.L D0, #123",
    "CMPA.B D0, A0",
    "CMPA.W #65536, A0"
};

INSTANTIATE_TEST_SUITE_P(ParserCMPAPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserCMPANegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
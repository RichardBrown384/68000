#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "ANDI.B #12, D0",
    "ANDI.B #12, (A0)",
    "ANDI.B #12, (A0)+",
    "ANDI.B #12, -(A0)",
    "ANDI.B #12, (3, A0)",
    "ANDI.B #12, (3, A0, A1.L)",
    "ANDI.B #12, (3, A0, D1.L)",
    "ANDI.B #12, (14).W",
    "ANDI.B #12, (14).L"
};

constexpr auto NEGATIVE_VALUES = {
    "ANDI.W #12, A0",
    "ANDI.W #12, (2, PC)",
    "ANDI.W #12, (2, PC, A1.L)",
    "ANDI.W #12, (2, PC, D1.L)",
    "ANDI.W #12, #13"
};

const char* const POSITIVE_CCR_VALUES[] = {
    "ANDI.B #12, CCR"
};

const char* const NEGATIVE_CCR_VALUES[] = {
    "ANDI.W #12, CCR",
    "ANDI.L #12, CCR"
};

const char* const POSITIVE_SR_VALUES[] = {
    "ANDI.W #12, SR"
};

const char* const NEGATIVE_SR_VALUES[] = {
    "ANDI.B #12, SR",
    "ANDI.L #12, SR"
};

INSTANTIATE_TEST_SUITE_P(ParserANDIPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserANDINegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserANDICCRPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_CCR_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserANDICCRNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_CCR_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserANDISRPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_SR_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserANDISRNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_SR_VALUES)
);

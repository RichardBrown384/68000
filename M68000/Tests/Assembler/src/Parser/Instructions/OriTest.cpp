#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "ORI.B #12, D0",
    "ORI.B #12, (A0)",
    "ORI.B #12, (A0)+",
    "ORI.B #12, -(A0)",
    "ORI.B #12, (3, A0)",
    "ORI.B #12, (3, A0, A1.L)",
    "ORI.B #12, (3, A0, D1.L)",
    "ORI.B #12, (14).W",
    "ORI.B #12, (14).L"
};

constexpr auto NEGATIVE_VALUES = {
    "ORI.W #12, A0",
    "ORI.W #12, (2, PC)",
    "ORI.W #12, (2, PC, A1.L)",
    "ORI.W #12, (2, PC, D1.L)",
    "ORI.W #12, #13"
};

const char* const POSITIVE_CCR_VALUES[] = {
    "ORI.B #12, CCR"
};

const char* const NEGATIVE_CCR_VALUES[] = {
    "ORI.W #12, CCR",
    "ORI.L #12, CCR"
};

const char* const POSITIVE_SR_VALUES[] = {
    "ORI.W #12, SR"
};

const char* const NEGATIVE_SR_VALUES[] = {
    "ORI.B #12, SR",
    "ORI.L #12, SR"
};

INSTANTIATE_TEST_SUITE_P(ParserORIPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserORINegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserORICCRPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_CCR_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserORICCRNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_CCR_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserORISRPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_SR_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserORISRNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_SR_VALUES)
);

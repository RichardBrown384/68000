#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "EORI.B #12, D0",
    "EORI.B #12, (A0)",
    "EORI.B #12, (A0)+",
    "EORI.B #12, -(A0)",
    "EORI.B #12, (3, A0)",
    "EORI.B #12, (3, A0, A1.L)",
    "EORI.B #12, (3, A0, D1.L)",
    "EORI.B #12, (14).W",
    "EORI.B #12, (14).L"
};

constexpr auto NEGATIVE_VALUES = {
    "EORI.W #12, A0",
    "EORI.W #12, (2, PC)",
    "EORI.W #12, (2, PC, A1.L)",
    "EORI.W #12, (2, PC, D1.L)",
    "EORI.W #12, #13"
};

const char* const POSITIVE_CCR_VALUES[] = {
    "EORI.B #12, CCR"
};

const char* const NEGATIVE_CCR_VALUES[] = {
    "EORI.W #12, CCR",
    "EORI.L #12, CCR"
};

const char* const POSITIVE_SR_VALUES[] = {
    "EORI.W #12, SR"
};

const char* const NEGATIVE_SR_VALUES[] = {
    "EORI.B #12, SR",
    "EORI.L #12, SR"
};

INSTANTIATE_TEST_SUITE_P(ParserEORIPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserEORINegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserEORICCRPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_CCR_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserEORICCRNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_CCR_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserEORISRPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_SR_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserEORISRNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_SR_VALUES)
);

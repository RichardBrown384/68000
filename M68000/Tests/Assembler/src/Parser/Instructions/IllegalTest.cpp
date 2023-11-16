#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "ILLEGAL"
};

INSTANTIATE_TEST_SUITE_P(ParserILLEGALPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);
#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "TRAPV"
};

INSTANTIATE_TEST_SUITE_P(ParserTRAPVPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);
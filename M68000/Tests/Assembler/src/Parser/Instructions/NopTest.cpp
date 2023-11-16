#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "NOP"
};

INSTANTIATE_TEST_SUITE_P(ParserNOPPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);
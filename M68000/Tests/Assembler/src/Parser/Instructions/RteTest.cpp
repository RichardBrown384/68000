#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "RTE"
};

INSTANTIATE_TEST_SUITE_P(ParserRTEPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);
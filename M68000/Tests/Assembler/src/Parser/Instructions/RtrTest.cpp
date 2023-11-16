#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "RTR"
};

INSTANTIATE_TEST_SUITE_P(ParserRTSPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);
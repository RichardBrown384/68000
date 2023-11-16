#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "RTS"
};

INSTANTIATE_TEST_SUITE_P(ParserRTSPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);
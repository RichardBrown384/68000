#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "RESET"
};

INSTANTIATE_TEST_SUITE_P(ParserRESETPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);
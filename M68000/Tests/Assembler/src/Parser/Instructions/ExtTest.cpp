#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "EXT.W D0",
    "EXT.L D2"
};

constexpr auto NEGATIVE_VALUES = {
    "EXT.B D0",
    "EXT.W A0",
    "EXT.W (A1)",
    "EXT.W (A1)+",
    "EXT.W -(A1)",
    "EXT.W (2, A3)",
    "EXT.W (2, A3, D3.L)",
    "EXT.W (123).W",
    "EXT.W (128).L",
    "EXT.W (2, PC)",
    "EXT.W (2, PC, D3.L)",
    "EXT.W #123"
};

INSTANTIATE_TEST_SUITE_P(ParserEXTPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
 );

INSTANTIATE_TEST_SUITE_P(ParserEXTNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);

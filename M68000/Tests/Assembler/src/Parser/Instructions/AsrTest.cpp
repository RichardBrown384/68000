#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "ASR.B D2, D1",
    "ASR.B #1, D1",
    "ASR.W D2, D1",
    "ASR.W #1, D1",
    "ASR.L D2, D1",
    "ASR.L #1, D1",
    "ASR.W (A1)",
    "ASR.W (A1)+",
    "ASR.W -(A1)",
    "ASR.W (10, A2)",
    "ASR.W (10, A2, A1.L)",
    "ASR.W (2000).W",
    "ASR.W (2000).L"
};

constexpr auto NEGATIVE_VALUES = {
    "ASR.B #0, D1",
    "ASR.B #9, D1",
    "ASR.B (A1), D1",
    "ASR.B (A1)+, D1",
    "ASR.B -(A1), D1",
    "ASR.B (10, A2), D1",
    "ASR.B (10, A2, A3.L), D1",
    "ASR.B (2000).W, D1",
    "ASR.B (2000).L, D1",
    "ASR.B (10, PC), D1",
    "ASR.B (10, PC, A3.L), D1",
    "ASR.W D1, (A1)",
    "ASR.W D1, (A1)+",
    "ASR.W D1, -(A1)",
    "ASR.W D1, (10, A2)",
    "ASR.W D1, (10, A2, A3.L)",
    "ASR.W D1, (2000).W",
    "ASR.W D1, (2000).L",
    "ASR.W D1, (10, PC)",
    "ASR.W D1, (10, PC, A3.L)",
    "ASR.W D1, #12",
    "ASR.L #2, (A1)",
    "ASR.L #2, (A1)+",
    "ASR.L #2, -(A1)",
    "ASR.L #2, (10, A2)",
    "ASR.L #2, (10, A2, A3.L)",
    "ASR.L #2, (2000).W",
    "ASR.L #2, (2000).L",
    "ASR.L #2, (10, PC)",
    "ASR.L #2, (10, PC, A3.L)",
    "ASR.L #2, #12",
    "ASR.W A1",
    "ASR.W (10, PC)",
    "ASR.W (10, PC, A1.L)",
    "ASR.B (A1)",
    "ASR.L (A1)",
};

INSTANTIATE_TEST_SUITE_P(ParserASRPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserASRNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
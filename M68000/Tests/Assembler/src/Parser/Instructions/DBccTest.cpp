#include "Assembler/Parser/Instructions/InstructionsTest.h"

constexpr auto POSITIVE_VALUES = {
    "DBT D1, *+800",
    "DBF D2, *-260",
    "DBRA D2, *-260",
    "DBHI D3, *+8",
    "DBLS D3, *+8",
    "DBCC D3, *+8",
    "DBCS D3, *+8",
    "DBNE D3, *+8",
    "DBEQ D3, *+8",
    "DBVC D3, *+8",
    "DBVS D3, *+8",
    "DBPL D3, *+8",
    "DBMI D3, *+8",
    "DBGE D3, *+8",
    "DBLT D3, *+8",
    "DBGT D3, *+8",
    "DBLE D3, *+8",
    "DBLE D3, *-8"
};

constexpr auto NEGATIVE_VALUES = {
    "DBHI A1, *+8",
    "DBHI (A1), *+8",
    "DBHI (A1)+, *+8",
    "DBHI -(A1), *+8",
    "DBHI (10, A1), *+8",
    "DBHI (10, A1, D2.L), *+8",
    "DBHI (10, A1, A2.L), *+8",
    "DBHI (123).W, *+8",
    "DBHI (123).L, *+8",
    "DBHI (10, PC, D2.L), *+8",
    "DBHI (10, PC, A2.L), *+8",
    "DBHI #123, *+8"
};

INSTANTIATE_TEST_SUITE_P(ParserDBccPositives,
    PositiveTest,
    ::testing::ValuesIn(POSITIVE_VALUES)
);

INSTANTIATE_TEST_SUITE_P(ParserDBccNegatives,
    NegativeTest,
    ::testing::ValuesIn(NEGATIVE_VALUES)
);
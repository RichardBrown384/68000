#include "M68000/Fixtures/M68000Test.h"

class DBccTest_T : public M68000Test {};
class DBccTest_F : public M68000Test {};
class DBccTest_HI : public M68000Test {};
class DBccTest_LS : public M68000Test {};
class DBccTest_CC : public M68000Test {};
class DBccTest_CS : public M68000Test {};
class DBccTest_NE : public M68000Test {};
class DBccTest_EQ : public M68000Test {};
class DBccTest_VC : public M68000Test {};
class DBccTest_VS : public M68000Test {};
class DBccTest_PL : public M68000Test {};
class DBccTest_MI : public M68000Test {};
class DBccTest_GE : public M68000Test {};
class DBccTest_LT : public M68000Test {};
class DBccTest_GT : public M68000Test {};
class DBccTest_LE : public M68000Test {};

TEST_F(DBccTest_T, BranchNotTaken) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x20",
    });
    When({
        "DBT D1, *+0x10"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x20",
    });
}

TEST_F(DBccTest_F, BranchTakenWhenCounterNonZero) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x20",
    });
    When({
        "DBF D1, *+0x10"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1010",
        "CYCLES is 10",
        "D1 is 0x1F",
    });
}

TEST_F(DBccTest_F, BranchNotTakenWhenCounterExpired) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0",
    });
    When({
        "DBF D1, *+0x10"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0xFFFF",
    });
}

TEST_F(DBccTest_HI, BranchNotTakenWhenConditionTrue) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x20",
    });
    When({
        "DBHI D1, *+0x10"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x20",
    });
}

TEST_F(DBccTest_HI, BranchNotTakenWhenCounterExpired) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0x0",
    });
    When({
        "DBHI D1, *+0x10"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0xFFFF",
    });
}

TEST_F(DBccTest_HI, BranchTakenWhenCounterNonZero) {
    Given({
        "SR is S,0,C",
        "PC is 0x1000",
        "D1 is 0x20",
    });
    When({
        "DBHI D1, *+0x10"
    });
    Then({
        "SR is S,0,C",
        "PC is 0x1010",
        "CYCLES is 10",
        "D1 is 0x1F",
    });
}

TEST_F(DBccTest_LS, BranchNotTakenWhenConditionTrue) {
    Given({
        "SR is S,0,ZC",
        "PC is 0x1000",
        "D1 is 0x20",
    });
    When({
        "DBLS D1, *+0x10"
    });
    Then({
        "SR is S,0,ZC",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x20",
    });
}

TEST_F(DBccTest_LS, BranchNotTakenWhenCounterExpired) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0",
    });
    When({
        "DBLS D1, *+0x10"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0xFFFF",
    });
}

TEST_F(DBccTest_LS, BranchTakenWhenCounterNonZero) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x20",
    });
    When({
        "DBLS D1, *+0x10"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1010",
        "CYCLES is 10",
        "D1 is 0x1F",
    });
}

TEST_F(DBccTest_CC, BranchNotTakenWhenConditionTrue) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x20",
    });
    When({
        "DBCC D1, *+0x10"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x20",
    });
}

TEST_F(DBccTest_CC, BranchNotTakenWhenCounterExpired) {
    Given({
        "SR is S,0,C",
        "PC is 0x1000",
        "D1 is 0x0",
    });
    When({
        "DBCC D1, *+0x10"
    });
    Then({
        "SR is S,0,C",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0xFFFF",
    });
}

TEST_F(DBccTest_CC, BranchTakenWhenCounterNonZero) {
    Given({
        "SR is S,0,C",
        "PC is 0x1000",
        "D1 is 0x20",
    });
    When({
        "DBCC D1, *+0x10"
    });
    Then({
        "SR is S,0,C",
        "PC is 0x1010",
        "CYCLES is 10",
        "D1 is 0x1F",
    });
}

TEST_F(DBccTest_CS, BranchNotTakenWhenConditionTrue) {
    Given({
        "SR is S,0,C",
        "PC is 0x1000",
        "D1 is 0x20",
    });
    When({
        "DBCS D1, *+0x10"
    });
    Then({
        "SR is S,0,C",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x20",
    });
}

TEST_F(DBccTest_CS, BranchNotTakenWhenCounterExpired) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0",
    });
    When({
        "DBCS D1, *+0x10"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0xFFFF",
    });
}

TEST_F(DBccTest_CS, BranchTakenWhenCounterNonZero) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x20",
    });
    When({
        "DBCS D1, *+0x10"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1010",
        "CYCLES is 10",
        "D1 is 0x1F",
    });
}

TEST_F(DBccTest_NE, BranchNotTakenWhenConditionTrue) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x20",
    });
    When({
        "DBNE D1, *+0x10"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x20",
    });
}

TEST_F(DBccTest_NE, BranchNotTakenWhenCounterExpired) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0x0",
    });
    When({
        "DBNE D1, *+0x10"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0xFFFF",
    });
}

TEST_F(DBccTest_NE, BranchTakenWhenCounterNonZero) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0x20",
    });
    When({
        "DBNE D1, *+0x10"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1010",
        "CYCLES is 10",
        "D1 is 0x1F",
    });
}

TEST_F(DBccTest_EQ, BranchNotTakenWhenConditionTrue) {
    Given({
        "SR is S,0,Z",
        "PC is 0x1000",
        "D1 is 0x20",
    });
    When({
        "DBEQ D1, *+0x10"
    });
    Then({
        "SR is S,0,Z",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x20",
    });
}

TEST_F(DBccTest_EQ, BranchNotTakenWhenCounterExpired) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0",
    });
    When({
        "DBEQ D1, *+0x10"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0xFFFF",
    });
}

TEST_F(DBccTest_EQ, BranchTakenWhenCounterNonZero) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x20",
    });
    When({
        "DBEQ D1, *+0x10"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1010",
        "CYCLES is 10",
        "D1 is 0x1F",
    });
}

TEST_F(DBccTest_VC, BranchNotTakenWhenConditionTrue) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x20",
    });
    When({
        "DBVC D1, *+0x10"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x20",
    });
}

TEST_F(DBccTest_VC, BranchNotTakenWhenCounterExpired) {
    Given({
        "SR is S,0,V",
        "PC is 0x1000",
        "D1 is 0x0",
    });
    When({
        "DBVC D1, *+0x10"
    });
    Then({
        "SR is S,0,V",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0xFFFF",
    });
}

TEST_F(DBccTest_VC, BranchTakenWhenCounterNonZero) {
    Given({
        "SR is S,0,V",
        "PC is 0x1000",
        "D1 is 0x20",
    });
    When({
        "DBVC D1, *+0x10"
    });
    Then({
        "SR is S,0,V",
        "PC is 0x1010",
        "CYCLES is 10",
        "D1 is 0x1F",
    });
}

TEST_F(DBccTest_VS, BranchNotTakenWhenConditionTrue) {
    Given({
        "SR is S,0,V",
        "PC is 0x1000",
        "D1 is 0x20",
    });
    When({
        "DBVS D1, *+0x10"
    });
    Then({
        "SR is S,0,V",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x20",
    });
}

TEST_F(DBccTest_VS, BranchNotTakenWhenCounterExpired) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0",
    });
    When({
        "DBVS D1, *+0x10"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0xFFFF",
    });
}

TEST_F(DBccTest_VS, BranchTakenWhenCounterNonZero) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x20",
    });
    When({
        "DBVS D1, *+0x10"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1010",
        "CYCLES is 10",
        "D1 is 0x1F",
    });
}

TEST_F(DBccTest_PL, BranchNotTakenWhenConditionTrue) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x20",
    });
    When({
        "DBPL D1, *+0x10"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x20",
    });
}

TEST_F(DBccTest_PL, BranchNotTakenWhenCounterExpired) {
    Given({
        "SR is S,0,N",
        "PC is 0x1000",
        "D1 is 0x0",
    });
    When({
        "DBPL D1, *+0x10"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0xFFFF",
    });
}

TEST_F(DBccTest_PL, BranchTakenWhenCounterNonZero) {
    Given({
        "SR is S,0,N",
        "PC is 0x1000",
        "D1 is 0x20",
    });
    When({
        "DBPL D1, *+0x10"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1010",
        "CYCLES is 10",
        "D1 is 0x1F",
    });
}

TEST_F(DBccTest_MI, BranchNotTakenWhenConditionTrue) {
    Given({
        "SR is S,0,N",
        "PC is 0x1000",
        "D1 is 0x20",
    });
    When({
        "DBMI D1, *+0x10"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x20",
    });
}

TEST_F(DBccTest_MI, BranchNotTakenWhenCounterExpired) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x0",
    });
    When({
        "DBMI D1, *+0x10"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0xFFFF",
    });
}

TEST_F(DBccTest_MI, BranchTakenWhenCounterNonZero) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "D1 is 0x20",
    });
    When({
        "DBMI D1, *+0x10"
    });
    Then({
        "SR is S,0,0",
        "PC is 0x1010",
        "CYCLES is 10",
        "D1 is 0x1F",
    });
}

TEST_F(DBccTest_GE, BranchNotTakenWhenConditionTrue) {
    Given({
        "SR is S,0,NV",
        "PC is 0x1000",
        "D1 is 0x20",
    });
    When({
        "DBGE D1, *+0x10"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x20",
    });
}

TEST_F(DBccTest_GE, BranchNotTakenWhenCounterExpired) {
    Given({
        "SR is S,0,N",
        "PC is 0x1000",
        "D1 is 0x0",
    });
    When({
        "DBGE D1, *+0x10"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0xFFFF",
    });
}

TEST_F(DBccTest_GE, BranchTakenWhenCounterNonZero) {
    Given({
        "SR is S,0,V",
        "PC is 0x1000",
        "D1 is 0x20",
    });
    When({
        "DBGE D1, *+0x10"
    });
    Then({
        "SR is S,0,V",
        "PC is 0x1010",
        "CYCLES is 10",
        "D1 is 0x1F",
    });
}

TEST_F(DBccTest_LT, BranchNotTakenWhenConditionTrue) {
    Given({
        "SR is S,0,N",
        "PC is 0x1000",
        "D1 is 0x20",
    });
    When({
        "DBLT D1, *+0x10"
    });
    Then({
        "SR is S,0,N",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x20",
    });
}

TEST_F(DBccTest_LT, BranchNotTakenWhenCounterExpired) {
    Given({
        "SR is S,0,NV",
        "PC is 0x1000",
        "D1 is 0x0",
    });
    When({
        "DBLT D1, *+0x10"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0xFFFF",
    });
}

TEST_F(DBccTest_LT, BranchTakenWhenCounterNonZero) {
    Given({
        "SR is S,0,NV",
        "PC is 0x1000",
        "D1 is 0x20",
    });
    When({
        "DBLT D1, *+0x10"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1010",
        "CYCLES is 10",
        "D1 is 0x1F",
    });
}

TEST_F(DBccTest_GT, BranchNotTakenWhenConditionTrue) {
    Given({
        "SR is S,0,NV",
        "PC is 0x1000",
        "D1 is 0x20",
    });
    When({
        "DBGT D1, *+0x10"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x20",
    });
}

TEST_F(DBccTest_GT, BranchNotTakenWhenCounterExpired) {
    Given({
        "SR is S,0,NZ",
        "PC is 0x1000",
        "D1 is 0x0",
    });
    When({
        "DBGT D1, *+0x10"
    });
    Then({
        "SR is S,0,NZ",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0xFFFF",
    });
}

TEST_F(DBccTest_GT, BranchTakenWhenCounterNonZero) {
    Given({
        "SR is S,0,NZ",
        "PC is 0x1000",
        "D1 is 0x20",
    });
    When({
        "DBGT D1, *+0x10"
    });
    Then({
        "SR is S,0,NZ",
        "PC is 0x1010",
        "CYCLES is 10",
        "D1 is 0x1F",
    });
}

TEST_F(DBccTest_LE, BranchNotTakenWhenConditionTrue) {
    Given({
        "SR is S,0,NZ",
        "PC is 0x1000",
        "D1 is 0x20",
    });
    When({
        "DBLE D1, *+0x10"
    });
    Then({
        "SR is S,0,NZ",
        "PC is 0x1004",
        "CYCLES is 12",
        "D1 is 0x20",
    });
}

TEST_F(DBccTest_LE, BranchNotTakenWhenCounterExpired) {
    Given({
        "SR is S,0,NV",
        "PC is 0x1000",
        "D1 is 0x0",
    });
    When({
        "DBLE D1, *+0x10"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1004",
        "CYCLES is 14",
        "D1 is 0xFFFF",
    });
}

TEST_F(DBccTest_LE, BranchTakenWhenCounterNonZero) {
    Given({
        "SR is S,0,NV",
        "PC is 0x1000",
        "D1 is 0x20",
    });
    When({
        "DBLE D1, *+0x10"
    });
    Then({
        "SR is S,0,NV",
        "PC is 0x1010",
        "CYCLES is 10",
        "D1 is 0x1F",
    });
}

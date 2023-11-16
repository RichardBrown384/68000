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
        "D1 is 0x20",
        "SR is S,0,0"
    });
    When({
        "DBT D1, *+0x10"
    });
    Then({
        "PC is 0x1004",
        "D1 is 0x20",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(DBccTest_F, BranchTakenWhenCounterNonZero) {
    Given({
        "D1 is 0x20",
        "SR is S,0,0"
    });
    When({
        "DBF D1, *+0x10"
    });
    Then({
        "PC is 0x1010",
        "D1 is 0x1F",
        "SR is S,0,0",
        "CYCLES is 10"
    });
}

TEST_F(DBccTest_F, BranchNotTakenWhenCounterExpired) {
    Given({
        "D1 is 0x0",
        "SR is S,0,0"
    });
    When({
        "DBF D1, *+0x10"
    });
    Then({
        "PC is 0x1004",
        "D1 is 0xFFFF",
        "SR is S,0,0",
        "CYCLES is 14"
    });
}

TEST_F(DBccTest_HI, BranchNotTakenWhenConditionTrue) {
    Given({
        "D1 is 0x20",
        "SR is S,0,0"
    });
    When({
        "DBHI D1, *+0x10"
    });
    Then({
        "PC is 0x1004",
        "D1 is 0x20",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(DBccTest_HI, BranchNotTakenWhenCounterExpired) {
    Given({
        "D1 is 0x0",
        "SR is S,0,Z"
    });
    When({
        "DBHI D1, *+0x10"
    });
    Then({
        "PC is 0x1004",
        "D1 is 0xFFFF",
        "SR is S,0,Z",
        "CYCLES is 14",
    });
}

TEST_F(DBccTest_HI, BranchTakenWhenCounterNonZero) {
    Given({
        "D1 is 0x20",
        "SR is S,0,C"
    });
    When({
        "DBHI D1, *+0x10"
    });
    Then({
        "PC is 0x1010",
        "D1 is 0x1F",
        "SR is S,0,C",
        "CYCLES is 10"
    });
}

TEST_F(DBccTest_LS, BranchNotTakenWhenConditionTrue) {
    Given({
        "D1 is 0x20",
        "SR is S,0,ZC"
    });
    When({
        "DBLS D1, *+0x10"
    });
    Then({
        "PC is 0x1004",
        "D1 is 0x20",
        "SR is S,0,ZC",
        "CYCLES is 12"
    });
}

TEST_F(DBccTest_LS, BranchNotTakenWhenCounterExpired) {
    Given({
        "D1 is 0x0",
        "SR is S,0,0"
    });
    When({
        "DBLS D1, *+0x10"
    });
    Then({
        "PC is 0x1004",
        "D1 is 0xFFFF",
        "SR is S,0,0",
        "CYCLES is 14",
    });
}

TEST_F(DBccTest_LS, BranchTakenWhenCounterNonZero) {
    Given({
        "D1 is 0x20",
        "SR is S,0,0"
    });
    When({
        "DBLS D1, *+0x10"
    });
    Then({
        "PC is 0x1010",
        "D1 is 0x1F",
        "SR is S,0,0",
        "CYCLES is 10"
    });
}

TEST_F(DBccTest_CC, BranchNotTakenWhenConditionTrue) {
    Given({
        "D1 is 0x20",
        "SR is S,0,0"
    });
    When({
        "DBCC D1, *+0x10"
    });
    Then({
        "PC is 0x1004",
        "D1 is 0x20",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(DBccTest_CC, BranchNotTakenWhenCounterExpired) {
    Given({
        "D1 is 0x0",
        "SR is S,0,C"
    });
    When({
        "DBCC D1, *+0x10"
    });
    Then({
        "PC is 0x1004",
        "D1 is 0xFFFF",
        "SR is S,0,C",
        "CYCLES is 14",
    });
}

TEST_F(DBccTest_CC, BranchTakenWhenCounterNonZero) {
    Given({
        "D1 is 0x20",
        "SR is S,0,C"
    });
    When({
        "DBCC D1, *+0x10"
    });
    Then({
        "PC is 0x1010",
        "D1 is 0x1F",
        "SR is S,0,C",
        "CYCLES is 10"
    });
}

TEST_F(DBccTest_CS, BranchNotTakenWhenConditionTrue) {
    Given({
        "D1 is 0x20",
        "SR is S,0,C"
    });
    When({
        "DBCS D1, *+0x10"
    });
    Then({
        "PC is 0x1004",
        "D1 is 0x20",
        "SR is S,0,C",
        "CYCLES is 12"
    });
}

TEST_F(DBccTest_CS, BranchNotTakenWhenCounterExpired) {
    Given({
        "D1 is 0x0",
        "SR is S,0,0"
    });
    When({
        "DBCS D1, *+0x10"
    });
    Then({
        "PC is 0x1004",
        "D1 is 0xFFFF",
        "SR is S,0,0",
        "CYCLES is 14",
    });
}

TEST_F(DBccTest_CS, BranchTakenWhenCounterNonZero) {
    Given({
        "D1 is 0x20",
        "SR is S,0,0"
    });
    When({
        "DBCS D1, *+0x10"
    });
    Then({
        "PC is 0x1010",
        "D1 is 0x1F",
        "SR is S,0,0",
        "CYCLES is 10"
    });
}

TEST_F(DBccTest_NE, BranchNotTakenWhenConditionTrue) {
    Given({
        "D1 is 0x20",
        "SR is S,0,0"
    });
    When({
        "DBNE D1, *+0x10"
    });
    Then({
        "PC is 0x1004",
        "D1 is 0x20",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(DBccTest_NE, BranchNotTakenWhenCounterExpired) {
    Given({
        "D1 is 0x0",
        "SR is S,0,Z"
    });
    When({
        "DBNE D1, *+0x10"
    });
    Then({
        "PC is 0x1004",
        "D1 is 0xFFFF",
        "SR is S,0,Z",
        "CYCLES is 14",
    });
}

TEST_F(DBccTest_NE, BranchTakenWhenCounterNonZero) {
    Given({
        "D1 is 0x20",
        "SR is S,0,Z"
    });
    When({
        "DBNE D1, *+0x10"
    });
    Then({
        "PC is 0x1010",
        "D1 is 0x1F",
        "SR is S,0,Z",
        "CYCLES is 10"
    });
}

TEST_F(DBccTest_EQ, BranchNotTakenWhenConditionTrue) {
    Given({
        "D1 is 0x20",
        "SR is S,0,Z"
    });
    When({
        "DBEQ D1, *+0x10"
    });
    Then({
        "PC is 0x1004",
        "D1 is 0x20",
        "SR is S,0,Z",
        "CYCLES is 12"
    });
}

TEST_F(DBccTest_EQ, BranchNotTakenWhenCounterExpired) {
    Given({
        "D1 is 0x0",
        "SR is S,0,0"
    });
    When({
        "DBEQ D1, *+0x10"
    });
    Then({
        "PC is 0x1004",
        "D1 is 0xFFFF",
        "SR is S,0,0",
        "CYCLES is 14",
    });
}

TEST_F(DBccTest_EQ, BranchTakenWhenCounterNonZero) {
    Given({
        "D1 is 0x20",
        "SR is S,0,0"
    });
    When({
        "DBEQ D1, *+0x10"
    });
    Then({
        "PC is 0x1010",
        "D1 is 0x1F",
        "SR is S,0,0",
        "CYCLES is 10"
    });
}

TEST_F(DBccTest_VC, BranchNotTakenWhenConditionTrue) {
    Given({
        "D1 is 0x20",
        "SR is S,0,0"
    });
    When({
        "DBVC D1, *+0x10"
    });
    Then({
        "PC is 0x1004",
        "D1 is 0x20",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(DBccTest_VC, BranchNotTakenWhenCounterExpired) {
    Given({
        "D1 is 0x0",
        "SR is S,0,V"
    });
    When({
        "DBVC D1, *+0x10"
    });
    Then({
        "PC is 0x1004",
        "D1 is 0xFFFF",
        "SR is S,0,V",
        "CYCLES is 14",
    });
}

TEST_F(DBccTest_VC, BranchTakenWhenCounterNonZero) {
    Given({
        "D1 is 0x20",
        "SR is S,0,V"
    });
    When({
        "DBVC D1, *+0x10"
    });
    Then({
        "PC is 0x1010",
        "D1 is 0x1F",
        "SR is S,0,V",
        "CYCLES is 10"
    });
}

TEST_F(DBccTest_VS, BranchNotTakenWhenConditionTrue) {
    Given({
        "D1 is 0x20",
        "SR is S,0,V"
    });
    When({
        "DBVS D1, *+0x10"
    });
    Then({
        "PC is 0x1004",
        "D1 is 0x20",
        "SR is S,0,V",
        "CYCLES is 12"
    });
}

TEST_F(DBccTest_VS, BranchNotTakenWhenCounterExpired) {
    Given({
        "D1 is 0x0",
        "SR is S,0,0"
    });
    When({
        "DBVS D1, *+0x10"
    });
    Then({
        "PC is 0x1004",
        "D1 is 0xFFFF",
        "SR is S,0,0",
        "CYCLES is 14",
    });
}

TEST_F(DBccTest_VS, BranchTakenWhenCounterNonZero) {
    Given({
        "D1 is 0x20",
        "SR is S,0,0"
    });
    When({
        "DBVS D1, *+0x10"
    });
    Then({
        "PC is 0x1010",
        "D1 is 0x1F",
        "SR is S,0,0",
        "CYCLES is 10"
    });
}

TEST_F(DBccTest_PL, BranchNotTakenWhenConditionTrue) {
    Given({
        "D1 is 0x20",
        "SR is S,0,0"
    });
    When({
        "DBPL D1, *+0x10"
    });
    Then({
        "PC is 0x1004",
        "D1 is 0x20",
        "SR is S,0,0",
        "CYCLES is 12"
    });
}

TEST_F(DBccTest_PL, BranchNotTakenWhenCounterExpired) {
    Given({
        "D1 is 0x0",
        "SR is S,0,N"
    });
    When({
        "DBPL D1, *+0x10"
    });
    Then({
        "PC is 0x1004",
        "D1 is 0xFFFF",
        "SR is S,0,N",
        "CYCLES is 14",
    });
}

TEST_F(DBccTest_PL, BranchTakenWhenCounterNonZero) {
    Given({
        "D1 is 0x20",
        "SR is S,0,N"
    });
    When({
        "DBPL D1, *+0x10"
    });
    Then({
        "PC is 0x1010",
        "D1 is 0x1F",
        "SR is S,0,N",
        "CYCLES is 10"
    });
}

TEST_F(DBccTest_MI, BranchNotTakenWhenConditionTrue) {
    Given({
        "D1 is 0x20",
        "SR is S,0,N"
    });
    When({
        "DBMI D1, *+0x10"
    });
    Then({
        "PC is 0x1004",
        "D1 is 0x20",
        "SR is S,0,N",
        "CYCLES is 12"
    });
}

TEST_F(DBccTest_MI, BranchNotTakenWhenCounterExpired) {
    Given({
        "D1 is 0x0",
        "SR is S,0,0"
    });
    When({
        "DBMI D1, *+0x10"
    });
    Then({
        "PC is 0x1004",
        "D1 is 0xFFFF",
        "SR is S,0,0",
        "CYCLES is 14",
    });
}

TEST_F(DBccTest_MI, BranchTakenWhenCounterNonZero) {
    Given({
        "D1 is 0x20",
        "SR is S,0,0"
    });
    When({
        "DBMI D1, *+0x10"
    });
    Then({
        "PC is 0x1010",
        "D1 is 0x1F",
        "SR is S,0,0",
        "CYCLES is 10"
    });
}

TEST_F(DBccTest_GE, BranchNotTakenWhenConditionTrue) {
    Given({
        "D1 is 0x20",
        "SR is S,0,NV"
    });
    When({
        "DBGE D1, *+0x10"
    });
    Then({
        "PC is 0x1004",
        "D1 is 0x20",
        "SR is S,0,NV",
        "CYCLES is 12"
    });
}

TEST_F(DBccTest_GE, BranchNotTakenWhenCounterExpired) {
    Given({
        "D1 is 0x0",
        "SR is S,0,N"
    });
    When({
        "DBGE D1, *+0x10"
    });
    Then({
        "PC is 0x1004",
        "D1 is 0xFFFF",
        "SR is S,0,N",
        "CYCLES is 14",
    });
}

TEST_F(DBccTest_GE, BranchTakenWhenCounterNonZero) {
    Given({
        "D1 is 0x20",
        "SR is S,0,V"
    });
    When({
        "DBGE D1, *+0x10"
    });
    Then({
        "PC is 0x1010",
        "D1 is 0x1F",
        "SR is S,0,V",
        "CYCLES is 10"
    });
}

TEST_F(DBccTest_LT, BranchNotTakenWhenConditionTrue) {
    Given({
        "D1 is 0x20",
        "SR is S,0,N"
    });
    When({
        "DBLT D1, *+0x10"
    });
    Then({
        "PC is 0x1004",
        "D1 is 0x20",
        "SR is S,0,N",
        "CYCLES is 12"
    });
}

TEST_F(DBccTest_LT, BranchNotTakenWhenCounterExpired) {
    Given({
        "D1 is 0x0",
        "SR is S,0,NV"
    });
    When({
        "DBLT D1, *+0x10"
    });
    Then({
        "PC is 0x1004",
        "D1 is 0xFFFF",
        "SR is S,0,NV",
        "CYCLES is 14",
    });
}

TEST_F(DBccTest_LT, BranchTakenWhenCounterNonZero) {
    Given({
        "D1 is 0x20",
        "SR is S,0,NV"
    });
    When({
        "DBLT D1, *+0x10"
    });
    Then({
        "PC is 0x1010",
        "D1 is 0x1F",
        "SR is S,0,NV",
        "CYCLES is 10"
    });
}

TEST_F(DBccTest_GT, BranchNotTakenWhenConditionTrue) {
    Given({
        "D1 is 0x20",
        "SR is S,0,NV"
    });
    When({
        "DBGT D1, *+0x10"
    });
    Then({
        "PC is 0x1004",
        "D1 is 0x20",
        "SR is S,0,NV",
        "CYCLES is 12"
    });
}

TEST_F(DBccTest_GT, BranchNotTakenWhenCounterExpired) {
    Given({
        "D1 is 0x0",
        "SR is S,0,NZ"
    });
    When({
        "DBGT D1, *+0x10"
    });
    Then({
        "PC is 0x1004",
        "D1 is 0xFFFF",
        "SR is S,0,NZ",
        "CYCLES is 14",
    });
}

TEST_F(DBccTest_GT, BranchTakenWhenCounterNonZero) {
    Given({
        "D1 is 0x20",
        "SR is S,0,NZ"
    });
    When({
        "DBGT D1, *+0x10"
    });
    Then({
        "PC is 0x1010",
        "D1 is 0x1F",
        "SR is S,0,NZ",
        "CYCLES is 10"
    });
}

TEST_F(DBccTest_LE, BranchNotTakenWhenConditionTrue) {
    Given({
        "D1 is 0x20",
        "SR is S,0,NZ"
    });
    When({
        "DBLE D1, *+0x10"
    });
    Then({
        "PC is 0x1004",
        "D1 is 0x20",
        "SR is S,0,NZ",
        "CYCLES is 12"
    });
}

TEST_F(DBccTest_LE, BranchNotTakenWhenCounterExpired) {
    Given({
        "D1 is 0x0",
        "SR is S,0,NV"
    });
    When({
        "DBLE D1, *+0x10"
    });
    Then({
        "PC is 0x1004",
        "D1 is 0xFFFF",
        "SR is S,0,NV",
        "CYCLES is 14",
    });
}

TEST_F(DBccTest_LE, BranchTakenWhenCounterNonZero) {
    Given({
        "D1 is 0x20",
        "SR is S,0,NV"
    });
    When({
        "DBLE D1, *+0x10"
    });
    Then({
        "PC is 0x1010",
        "D1 is 0x1F",
        "SR is S,0,NV",
        "CYCLES is 10"
    });
}
#include "M68000/Fixtures/M68000Test.h"

class TraceExceptionExceptionTest: public M68000Test {};

TEST_F(TraceExceptionExceptionTest, UserModeTraceNop) {
    Given({
        "SR is T,0,XC",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "PC is 0x1000",
        "(0x24).L is 0x00BCBCBC",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "NOP"
    });
    Then({
        "SR is S,0,XC",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "PC is 0x00BCBCBC",
        "(0x24).L is 0x00BCBCBC",
        "(0x00FFFFFA).W is 0x8011",
        "(0x00FFFFFC).L is 0x00001002",
        "CYCLES is 38" // NOP(4) + TRACE(34)
    });
}

TEST_F(TraceExceptionExceptionTest, SupervisorModeTraceNop) {
    Given({
        "SR is TS,0,XC",
        "A7 is 0x01000000",
        "PC is 0x1000",
        "(0x24).L is 0x00BCBCBC",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "NOP"
    });
    Then({
        "SR is S,0,XC",
        "A7 is 0x00FFFFFA",
        "PC is 0x00BCBCBC",
        "(0x24).L is 0x00BCBCBC",
        "(0x00FFFFFA).W is 0xA011",
        "(0x00FFFFFC).L is 0x00001002",
        "CYCLES is 38" // NOP(4) + TRACE(34)
    });
}

TEST_F(TraceExceptionExceptionTest, SupervisorModeTraceStop) {
    Given({
        "SR is TS,0,XC",
        "A7 is 0x01000000",
        "USP is 0x00FF0000",
        "PC is 0x1000",
        "STOPPED is 0",
        "(0x24).L is 0x00BCBCBC",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "STOP #0x0000"
    });
    Then({
        "SR is S,0,0",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "PC is 0x00BCBCBC",
        "STOPPED is 0",
        "(0x24).L is 0x00BCBCBC",
        "(0x00FFFFFA).W is 0x0000",
        "(0x00FFFFFC).L is 0x00001004",
        "CYCLES is 38" // STOP(4) + TRACE(34)
    });
}

TEST_F(TraceExceptionExceptionTest, UserModeTraceNopWithInterrupt) {
    Given({
        "SR is T,3,0",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "PC is 0x1000",
        "INT is 0,4,25",
        "(0x24).L is 0x00BCBCBC",
        "(0x64).L is 0x00CC11AA",
        "(0x00FFFFF4).W is 0xCDCD",
        "(0x00FFFFF6).L is 0xCDCDCDCD",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "NOP"
    });
    Then({
        "SR is S,4,0",
        "A7 is 0x00FFFFF4",
        "USP is 0x00FF0000",
        "PC is 0x00CC11AA",
        "(0x24).L is 0x00BCBCBC",
        "(0x64).L is 0x00CC11AA",
        "(0x00FFFFF4).W is 0x2300",
        "(0x00FFFFF6).L is 0x00BCBCBC",
        "(0x00FFFFFA).W is 0x8300",
        "(0x00FFFFFC).L is 0x00001002",
        "CYCLES is 82" // NOP(4) + TRACE(34) + INT(44)
    });
}

TEST_F(TraceExceptionExceptionTest, SupervisorModeTraceNopWithInterrupt) {
    Given({
        "SR is TS,3,0",
        "A7 is 0x01000000",
        "PC is 0x1000",
        "INT is 0,4,25",
        "(0x24).L is 0x00BCBCBC",
        "(0x64).L is 0x00CC11AA",
        "(0x00FFFFF4).W is 0xCDCD",
        "(0x00FFFFF6).L is 0xCDCDCDCD",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "NOP"
    });
    Then({
        "SR is S,4,0",
        "A7 is 0x00FFFFF4",
        "PC is 0x00CC11AA",
        "(0x24).L is 0x00BCBCBC",
        "(0x64).L is 0x00CC11AA",
        "(0x00FFFFF4).W is 0x2300",
        "(0x00FFFFF6).L is 0x00BCBCBC",
        "(0x00FFFFFA).W is 0xA300",
        "(0x00FFFFFC).L is 0x00001002",
        "CYCLES is 82" // NOP(4) + TRACE(34) + INT(44)
    });
}

TEST_F(TraceExceptionExceptionTest, SupervisorModeTraceStopWithInterrupt) {
    Given({
        "SR is TS,3,0",
        "A7 is 0x01000000",
        "PC is 0x1000",
        "INT is 0,4,25",
        "(0x24).L is 0x00BCBCBC",
        "(0x64).L is 0x00CC11AA",
        "(0x00FFFFF4).W is 0xCDCD",
        "(0x00FFFFF6).L is 0xCDCDCDCD",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "STOP #0x0000"
    });
    Then({
        "SR is S,4,0",
        "A7 is 0x00FFFFF4",
        "PC is 0x00CC11AA",
        "(0x24).L is 0x00BCBCBC",
        "(0x64).L is 0x00CC11AA",
        "(0x00FFFFF4).W is 0x2000",
        "(0x00FFFFF6).L is 0x00BCBCBC",
        "(0x00FFFFFA).W is 0x0000",
        "(0x00FFFFFC).L is 0x00001004",
        "CYCLES is 82" // STOP(4) + TRACE(34) + INT(44)
    });
}

TEST_F(TraceExceptionExceptionTest, SupervisorModeTraceStopWithInterruptMakedByStop) {
    Given({
        "SR is TS,3,0",
        "A7 is 0x01000000",
        "PC is 0x1000",
        "INT is 0,4,25",
        "(0x24).L is 0x00BCBCBC",
        "(0x64).L is 0x00CC11AA",
        "(0x00FFFFF4).W is 0xCDCD",
        "(0x00FFFFF6).L is 0xCDCDCDCD",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "STOP #0x0500"
    });
    Then({
        "SR is S,5,0",
        "A7 is 0x00FFFFFA",
        "PC is 0x00BCBCBC",
        "(0x24).L is 0x00BCBCBC",
        "(0x64).L is 0x00CC11AA",
        "(0x00FFFFF4).W is 0xCDCD",
        "(0x00FFFFF6).L is 0xCDCDCDCD",
        "(0x00FFFFFA).W is 0x0500",
        "(0x00FFFFFC).L is 0x00001004",
        "CYCLES is 38" // STOP(4) + TRACE(34)
    });
}
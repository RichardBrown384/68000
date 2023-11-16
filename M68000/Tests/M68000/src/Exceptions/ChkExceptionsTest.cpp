#include "M68000/Fixtures/M68000Test.h"

class ChkExceptionTest: public M68000Test {};

TEST_F(ChkExceptionTest, DataRegisterUserMode) {
    Given({
        "SR is 0,0,N",
        "D0 is 0x00000001",
        "D1 is 0x00000002",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "(0x18).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "CHK D0, D1"
    });
    Then({
        "SR is S,0,0",
        "D0 is 0x00000001",
        "D1 is 0x00000002",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "PC is 0x00CAFED0",
        "(0x18).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0x0000",
        "(0x00FFFFFC).L is 0x00001002",
        "CYCLES is 44"
    });
}

TEST_F(ChkExceptionTest, DataRegisterSupervisorMode) {
    Given({
        "SR is S,0,N",
        "D0 is 0x00000001",
        "D1 is 0x00000002",
        "A7 is 0x01000000",
        "USP is 0x00FF0000",
        "(0x18).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "CHK D0, D1"
    });
    Then({
        "SR is S,0,0",
        "D0 is 0x00000001",
        "D1 is 0x00000002",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "PC is 0x00CAFED0",
        "(0x18).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0x2000",
        "(0x00FFFFFC).L is 0x00001002",
        "CYCLES is 44"
    });
}

TEST_F(ChkExceptionTest, DataRegisterLessThanZero) {
    Given({
        "SR is S,0,0",
        "D0 is 0x00000001",
        "D1 is 0x0000FFFF",
        "A7 is 0x01000000",
        "USP is 0x00FF0000",
        "(0x18).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        "CHK D0, D1"
    });
    Then({
        "SR is S,0,N",
        "D0 is 0x00000001",
        "D1 is 0x0000FFFF",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "PC is 0x00CAFED0",
        "(0x18).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0x2008",
        "(0x00FFFFFC).L is 0x00001002",
        "CYCLES is 44"
    });
}

TEST_F(ChkExceptionTest, AddressIndirectUserMode) {
    Given({
        "SR is 0,0,N",
        "D1 is 0x00000002",
        "A0 is 0x00004000",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "(0x18).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
        "(0x4000).W is 0x0001"
    });
    When({
        "CHK (A0), D1"
    });
    Then({
        "SR is S,0,0",
        "D1 is 0x00000002",
        "A0 is 0x00004000",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "PC is 0x00CAFED0",
        "(0x18).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0x0000",
        "(0x00FFFFFC).L is 0x00001002",
        "(0x4000).W is 0x0001",
        "CYCLES is 48"
    });
}

TEST_F(ChkExceptionTest, AddressIncrementUserMode) {
    Given({
        "SR is 0,0,N",
        "D1 is 0x00000002",
        "A0 is 0x00004000",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "(0x18).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
        "(0x4000).W is 0x0001"
    });
    When({
        "CHK (A0)+, D1"
    });
    Then({
        "SR is S,0,0",
        "D1 is 0x00000002",
        "A0 is 0x00004002",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "PC is 0x00CAFED0",
        "(0x18).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0x0000",
        "(0x00FFFFFC).L is 0x00001002",
        "(0x4000).W is 0x0001",
        "CYCLES is 48"
    });
}

TEST_F(ChkExceptionTest, AddressDecrementUserMode) {
    Given({
        "SR is 0,0,N",
        "D1 is 0x00000002",
        "A0 is 0x00004002",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "(0x18).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
        "(0x4000).W is 0x0001"
    });
    When({
        "CHK -(A0), D1"
    });
    Then({
        "SR is S,0,0",
        "D1 is 0x00000002",
        "A0 is 0x00004000",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "PC is 0x00CAFED0",
        "(0x18).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0x0000",
        "(0x00FFFFFC).L is 0x00001002",
        "(0x4000).W is 0x0001",
        "CYCLES is 50"
    });
}

TEST_F(ChkExceptionTest, AddressDisplacementUserMode) {
    Given({
        "SR is 0,0,N",
        "D1 is 0x00000002",
        "A0 is 0x00004000",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "(0x18).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
        "(0x4002).W is 0x0001"
    });
    When({
        "CHK (0x2, A0), D1"
    });
    Then({
        "SR is S,0,0",
        "D1 is 0x00000002",
        "A0 is 0x00004000",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "PC is 0x00CAFED0",
        "(0x18).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0x0000",
        "(0x00FFFFFC).L is 0x00001004",
        "(0x4002).W is 0x0001",
        "CYCLES is 52"
    });
}

TEST_F(ChkExceptionTest, AddressIndexUserMode) {
    Given({
        "SR is 0,0,N",
        "D1 is 0x00000002",
        "A0 is 0x00004000",
        "A1 is 0x00004000",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "(0x18).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
        "(0x8002).W is 0x0001"
    });
    When({
        "CHK (0x2, A0, A1.L), D1"
    });
    Then({
        "SR is S,0,0",
        "D1 is 0x00000002",
        "A0 is 0x00004000",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "PC is 0x00CAFED0",
        "(0x18).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0x0000",
        "(0x00FFFFFC).L is 0x00001004",
        "(0x8002).W is 0x0001",
        "CYCLES is 54"
    });
}

TEST_F(ChkExceptionTest, ShortUserMode) {
    Given({
        "SR is 0,0,N",
        "D1 is 0x00000002",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "(0x18).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
        "(0x4000).W is 0x01"
    });
    When({
        "CHK (0x4000).W, D1"
    });
    Then({
        "SR is S,0,0",
        "D1 is 0x00000002",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "PC is 0x00CAFED0",
        "(0x18).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0x0000",
        "(0x00FFFFFC).L is 0x00001004",
        "(0x4000).W is 0x01",
        "CYCLES is 52"
    });
}

TEST_F(ChkExceptionTest, LongUserMode) {
    Given({
        "SR is 0,0,N",
        "D1 is 0x00000002",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "(0x18).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
        "(0x00800000).W is 0x01"
    });
    When({
        "CHK (0x00800000).L, D1"
    });
    Then({
        "SR is S,0,0",
        "D1 is 0x00000002",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "PC is 0x00CAFED0",
        "(0x18).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0x0000",
        "(0x00FFFFFC).L is 0x00001006",
        "(0x00800000).W is 0x01",
        "CYCLES is 56"
    });
}

TEST_F(ChkExceptionTest, PCDisplacementUserMode) {
    Given({
        "SR is 0,0,N",
        "D1 is 0x00000002",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "(0x18).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
        "(0x1202).W is 0x0001"
    });
    When({
        "CHK (0x200, PC), D1"
    });
    Then({
        "SR is S,0,0",
        "D1 is 0x00000002",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "PC is 0x00CAFED0",
        "(0x18).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0x0000",
        "(0x00FFFFFC).L is 0x00001004",
        "(0x1202).W is 0x0001",
        "CYCLES is 52"
    });
}

TEST_F(ChkExceptionTest, PCIndexUserMode) {
    Given({
        "SR is 0,0,N",
        "D1 is 0x00000002",
        "A1 is 0x00000200",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "(0x18).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
        "(0x1204).W is 0x0001"
    });
    When({
        "CHK (0x2, PC, A1.L), D1"
    });
    Then({
        "SR is S,0,0",
        "D1 is 0x00000002",
        "A1 is 0x00000200",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "PC is 0x00CAFED0",
        "(0x18).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0x0000",
        "(0x00FFFFFC).L is 0x00001004",
        "(0x1204).W is 0x0001",
        "CYCLES is 54"
    });
}

TEST_F(ChkExceptionTest, ImmediateUserMode) {
    Given({
        "SR is 0,0,N",
        "D1 is 0x00000002",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "(0x18).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD"
    });
    When({
        "CHK #1, D1"
    });
    Then({
        "SR is S,0,0",
        "D1 is 0x00000002",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "PC is 0x00CAFED0",
        "(0x18).L is 0x00CAFED0",
        "(0x00FFFFFA).W is 0x0000",
        "(0x00FFFFFC).L is 0x00001004",
        "CYCLES is 48"
    });
}
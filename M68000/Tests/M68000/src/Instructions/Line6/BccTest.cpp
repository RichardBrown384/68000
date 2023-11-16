#include "M68000/Fixtures/M68000Test.h"

class BccTest : public M68000Test {};

TEST_F(BccTest, BHIBranchesWhenZeroAndCarryClear) {
    Given({
        "SR is S,0,0"
    });
    When({
        "BHI.B *+0x10"
    });
    Then({
        "PC is 0x1010",
        "SR is S,0,0"
    });
}

TEST_F(BccTest, BHIDoesNotBranchWhenCarrySet) {
    Given({
        "SR is S,0,C"
    });
    When({
        "BHI.B *+0x10"
    });
    Then({
        "CYCLES is 8",
        "PC is 0x1002",
        "SR is S,0,C"
    });
}

TEST_F(BccTest, BHIDoesNotBranchWhenZeroSet) {
    Given({
        "SR is S,0,Z"
    });
    When({
        "BHI.B *+0x10"
    });
    Then({
        "CYCLES is 8",
        "PC is 0x1002",
        "SR is S,0,Z"
    });
}

TEST_F(BccTest, BHIDoesNotBranchWhenZeroAndCarrySet) {
    Given({
        "SR is S,0,ZC"
    });
    When({
        "BHI.B *+0x10"
    });
    Then({
        "CYCLES is 8",
        "PC is 0x1002",
        "SR is S,0,ZC"
    });
}

TEST_F(BccTest, BLSBranchesWhenZeroAndCarrySet) {
    Given({
        "SR is S,0,ZC"
    });
    When({
        "BLS.B *+0x10"
    });
    Then({
        "PC is 0x1010",
        "SR is S,0,ZC"
    });
}

TEST_F(BccTest, BLSBranchesWhenCarrySet) {
    Given({
        "SR is S,0,C"
    });
    When({
        "BLS.B *+0x10"
    });
    Then({
        "PC is 0x1010",
        "SR is S,0,C"
    });
}

TEST_F(BccTest, BLSBranchesWhenZeroSet) {
    Given({
        "SR is S,0,Z"
    });
    When({
        "BLS.B *+0x10"
    });
    Then({
        "PC is 0x1010",
        "SR is S,0,Z"
    });
}

TEST_F(BccTest, BLSDoesNotBranchWhenZeroAndCarryClear) {
    Given({
        "SR is S,0,0"
    });
    When({
        "BLS.B *+0x10"
    });
    Then({
        "CYCLES is 8",
        "PC is 0x1002",
        "SR is S,0,0"
    });
}

TEST_F(BccTest, BCCBranchesWhenCarryClear) {
    Given({
        "SR is S,0,0"
    });
    When({
        "BCC.B *+0x10"
    });
    Then({
        "PC is 0x1010",
        "SR is S,0,0"
    });
}

TEST_F(BccTest, BCCDoesNotBranchWhenCarrySet) {
    Given({
        "SR is S,0,C"
    });
    When({
        "BCC.B *+0x10"
    });
    Then({
        "CYCLES is 8",
        "PC is 0x1002",
        "SR is S,0,C"
    });
}

TEST_F(BccTest, BCSBranchesWhenCarrySet) {
    Given({
        "SR is S,0,C"
    });
    When({
        "BCS.B *+0x10"
    });
    Then({
        "PC is 0x1010",
        "SR is S,0,C"
    });
}

TEST_F(BccTest, BCSDoesNotBranchWhenCarryClear) {
    Given({
        "SR is S,0,0"
    });
    When({
        "BCS.B *+0x10"
    });
    Then({
        "CYCLES is 8",
        "PC is 0x1002",
        "SR is S,0,0"
    });
}

TEST_F(BccTest, BNEBranchesWhenZeroClear) {
    Given({
        "SR is S,0,0"
    });
    When({
        "BNE.B *+0x10"
    });
    Then({
        "PC is 0x1010",
        "SR is S,0,0"
    });
}

TEST_F(BccTest, BNEDoesNotBranchWhenZeroSet) {
    Given({
        "SR is S,0,Z"
    });
    When({
        "BNE.B *+0x10"
    });
    Then({
        "CYCLES is 8",
        "PC is 0x1002",
        "SR is S,0,Z"
    });
}

TEST_F(BccTest, BEQBranchesWhenZeroSet) {
    Given({
        "SR is S,0,Z"
    });
    When({
        "BEQ.B *+0x10"
    });
    Then({
        "PC is 0x1010",
        "SR is S,0,Z"
    });
}

TEST_F(BccTest, BEQDoesNotBranchWhenZeroClear) {
    Given({
        "SR is S,0,0"
    });
    When({
        "BEQ.B *+0x10"
    });
    Then({
        "CYCLES is 8",
        "PC is 0x1002",
        "SR is S,0,0"
    });
}

TEST_F(BccTest, BVCBranchesWhenOverflowClear) {
    Given({
        "SR is S,0,0"
    });
    When({
        "BVC.B *+0x10"
    });
    Then({
        "PC is 0x1010",
        "SR is S,0,0"
    });
}

TEST_F(BccTest, BVCDoesNotBranchWhenOverflowSet) {
    Given({
        "SR is S,0,V"
    });
    When({
        "BVC.B *+0x10"
    });
    Then({
        "CYCLES is 8",
        "PC is 0x1002",
        "SR is S,0,V"
    });
}

TEST_F(BccTest, BVSBranchesWhenOverflowSet) {
    Given({
        "SR is S,0,V"
    });
    When({
        "BVS.B *+0x10"
    });
    Then({
        "PC is 0x1010",
        "SR is S,0,V"
    });
}

TEST_F(BccTest, BVSDoesNotBranchWhenOverflowClear) {
    Given({
        "SR is S,0,0"
    });
    When({
        "BVS.B *+0x10"
    });
    Then({
        "CYCLES is 8",
        "PC is 0x1002",
        "SR is S,0,0"
    });
}

TEST_F(BccTest, BPLBranchesWhenNegativeClear) {
    Given({
        "SR is S,0,0"
    });
    When({
        "BPL.B *+0x10"
    });
    Then({
        "PC is 0x1010",
        "SR is S,0,0"
    });
}

TEST_F(BccTest, BPLDoesNotBranchWhenNegativeSet) {
    Given({
        "SR is S,0,N"
    });
    When({
        "BPL.B *+0x10"
    });
    Then({
        "CYCLES is 8",
        "PC is 0x1002",
        "SR is S,0,N"
    });
}

TEST_F(BccTest, BMIBranchesWhenNegativeSet) {
    Given({
        "SR is S,0,N"
    });
    When({
        "BMI.B *+0x10"
    });
    Then({
        "PC is 0x1010",
        "SR is S,0,N"
    });
}

TEST_F(BccTest, BMIDoesNotBranchWhenNegativeClear) {
    Given({
        "SR is S,0,0"
    });
    When({
        "BMI.B *+0x10"
    });
    Then({
        "CYCLES is 8",
        "PC is 0x1002",
        "SR is S,0,0"
    });
}

TEST_F(BccTest, BGEDoesNotBranchWhenNegativeSet) {
    Given({
        "SR is S,0,N"
    });
    When({
        "BGE.B *+0x10"
    });
    Then({
        "CYCLES is 8",
        "PC is 0x1002",
        "SR is S,0,N"
    });
}

TEST_F(BccTest, BGEDoesNotBranchWhenOverflowSet) {
    Given({
        "SR is S,0,V"
    });
    When({
        "BGE.B *+0x10"
    });
    Then({
        "CYCLES is 8",
        "PC is 0x1002",
        "SR is S,0,V"
    });
}

TEST_F(BccTest, BGEBranchesWhenNegativeAndOverflowSet) {
    Given({
        "SR is S,0,NV"
    });
    When({
        "BGE.B *+0x10"
    });
    Then({
        "PC is 0x1010",
        "SR is S,0,NV"
    });
}

TEST_F(BccTest, BGEBranchesWhenNegativeAndOverflowClear) {
    Given({
        "SR is S,0,0"
    });
    When({
        "BGE.B *+0x10"
    });
    Then({
        "PC is 0x1010",
        "SR is S,0,0"
    });
}

TEST_F(BccTest, BLTDoesNotBranchWhenNegativeAndOverflowClear) {
    Given({
        "SR is S,0,0"
    });
    When({
        "BLT.B *+0x10"
    });
    Then({
        "CYCLES is 8",
        "PC is 0x1002",
        "SR is S,0,0"
    });
}

TEST_F(BccTest, BLTDoesNotBranchWhenNegativeAndOverflowSet) {
    Given({
        "SR is S,0,NV"
    });
    When({
        "BLT.B *+0x10"
    });
    Then({
        "CYCLES is 8",
        "PC is 0x1002",
        "SR is S,0,NV"
    });
}

TEST_F(BccTest, BLTBranchesWhenNegativeSet) {
    Given({
        "SR is S,0,N"
    });
    When({
        "BLT.B *+0x10"
    });
    Then({
        "PC is 0x1010",
        "SR is S,0,N"
    });
}

TEST_F(BccTest, BLTBranchesWhenOverflowSet) {
    Given({
        "SR is S,0,V"
    });
    When({
        "BLT.B *+0x10"
    });
    Then({
        "PC is 0x1010",
        "SR is S,0,V"
    });
}

TEST_F(BccTest, BGTDoesNotBranchWhenNegativeSet) {
    Given({
        "SR is S,0,N"
    });
    When({
        "BGT.B *+0x10"
    });
    Then({
        "CYCLES is 8",
        "PC is 0x1002",
        "SR is S,0,N"
    });
}

TEST_F(BccTest, BGTDoesNotBranchWhenOverflowSet) {
    Given({
        "SR is S,0,V"
    });
    When({
        "BGT.B *+0x10"
    });
    Then({
        "CYCLES is 8",
        "PC is 0x1002",
        "SR is S,0,V"
    });
}

TEST_F(BccTest, BGTBranchesWhenNegativeAndOverflowSet) {
    Given({
        "SR is S,0,NV"
    });
    When({
        "BGT.B *+0x10"
    });
    Then({
        "PC is 0x1010",
        "SR is S,0,NV"
    });
}

TEST_F(BccTest, BGTBranchesWhenNegativeAndOverflowClear) {
    Given({
        "SR is S,0,0"
    });
    When({
        "BGT.B *+0x10"
    });
    Then({
        "PC is 0x1010",
        "SR is S,0,0"
    });
}

TEST_F(BccTest, BGTDoesNotBranchWhenNegativeOverflowAndZeroSet) {
    Given({
        "SR is S,0,NVZ"
    });
    When({
        "BGT.B *+0x10"
    });
    Then({
        "CYCLES is 8",
        "PC is 0x1002",
        "SR is S,0,NVZ"
    });
}

TEST_F(BccTest, BGTDoesNotBranchWhenZeroSet) {
    Given({
        "SR is S,0,Z"
    });
    When({
        "BGT.B *+0x10"
    });
    Then({
        "CYCLES is 8",
        "PC is 0x1002",
        "SR is S,0,Z"
    });
}

TEST_F(BccTest, BLEDoesNotBranchWhenNegativeAndOverflowAndZeroClear) {
    Given({
        "SR is S,0,0"
    });
    When({
        "BLE.B *+0x10"
    });
    Then({
        "CYCLES is 8",
        "PC is 0x1002",
        "SR is S,0,0"
    });
}

TEST_F(BccTest, BLEDoesNotBranchWhenNegativeAndOverflowSet) {
    Given({
        "SR is S,0,NV"
    });
    When({
        "BLE.B *+0x10"
    });
    Then({
        "CYCLES is 8",
        "PC is 0x1002",
        "SR is S,0,NV"
    });
}

TEST_F(BccTest, BLEBranchesWhenNegativeAndOverflowAndZeroSet) {
    Given({
        "SR is S,0,NVZ"
    });
    When({
        "BLE.B *+0x10"
    });
    Then({
        "PC is 0x1010",
        "SR is S,0,NVZ"
    });
}

TEST_F(BccTest, BLEBranchesWhenNegativeSet) {
    Given({
        "SR is S,0,N"
    });
    When({
        "BLE.B *+0x10"
    });
    Then({
        "PC is 0x1010",
        "SR is S,0,N"
    });
}

TEST_F(BccTest, BLEBranchesWhenNegativeAndZeroSet) {
    Given({
        "SR is S,0,NZ"
    });
    When({
        "BLE.B *+0x10"
    });
    Then({
        "PC is 0x1010",
        "SR is S,0,NZ"
    });
}

TEST_F(BccTest, BLEBranchesWhenOverflowSet) {
    Given({
        "SR is S,0,V"
    });
    When({
        "BLE.B *+0x10"
    });
    Then({
        "PC is 0x1010",
        "SR is S,0,V"
    });
}

TEST_F(BccTest, BLEBranchesWhenOverflowAndZeroSet) {
    Given({
        "SR is S,0,VZ"
    });
    When({
        "BLE.B *+0x10"
    });
    Then({
        "PC is 0x1010",
        "SR is S,0,VZ"
    });
}

TEST_F(BccTest, BCCNegativeByteDisplacement) {
    Given({
        "SR is S,0,0"
    });
    When({
        "BCC.B *-0x20"
    });
    Then({
        "PC is 0x0FE0",
        "SR is S,0,0"
    });
}

TEST_F(BccTest, BCCNegativeWordDisplacement) {
    Given({
        "SR is S,0,0"
    });
    When({
        "BCC.W *-0x482"
    });
    Then({
        "PC is 0x0B7E",
        "SR is S,0,0"
    });
}

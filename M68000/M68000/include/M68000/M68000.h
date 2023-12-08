#pragma once

#include <cstdint>
#include <array>

namespace rbrown::m68000 {

class Interrupts {
public:
    virtual ~Interrupts() = default;
    virtual uint32_t GetInterruptLevel() = 0;
    virtual uint32_t GetInterruptVector(uint32_t) = 0;
};

class Memory {
public:
    virtual ~Memory() = default;

    virtual bool ReadByte(uint32_t, uint32_t&) = 0;
    virtual bool ReadWord(uint32_t, uint32_t&) = 0;

    virtual bool WriteByte(uint32_t, uint32_t) = 0;
    virtual bool WriteWord(uint32_t, uint32_t) = 0;
};

class Observer {
public:
    virtual ~Observer() = default;

    virtual void Cycles(uint32_t) = 0;

    virtual void Reset() = 0;
};

class M68000 {
public:
    M68000(Interrupts&, Memory&, Observer& observer);

    [[nodiscard]] auto ReadDataRegisterLong(uint32_t r) const { return data[r]; }
    [[nodiscard]] auto ReadAddressRegisterLong(uint32_t r) const { return addr[r]; }

    [[nodiscard]] auto ReadSP() const { return ReadAddressRegisterLong(7u); }
    [[nodiscard]] auto ReadPC() const { return pc; }
    [[nodiscard]] auto ReadUSP() const { return usp; }
    [[nodiscard]] auto ReadSSP() const { return ssp; }
    [[nodiscard]] auto ReadIRC() const { return irc; }
    [[nodiscard]] auto ReadIRD() const { return ird; }

    [[nodiscard]] auto ReadSR() const -> uint16_t;
    [[nodiscard]] auto ReadCCR() const -> uint16_t;

    [[nodiscard]] auto ReadFlagT() const { return flagT; }
    [[nodiscard]] auto ReadFlagS() const { return flagS; }

    [[nodiscard]] auto ReadInterruptPriorityMask() const { return interruptPriorityMask; }

    [[nodiscard]] auto ReadFlagX() const { return (flagX & 0x80000000u) != 0u; }
    [[nodiscard]] auto ReadFlagN() const { return (flagN & 0x80000000u) != 0u; }
    [[nodiscard]] auto ReadFlagZ() const { return flagZ == 0u; }
    [[nodiscard]] auto ReadFlagV() const { return (flagV & 0x80000000u) != 0u; }
    [[nodiscard]] auto ReadFlagC() const { return (flagC & 0x80000000u) != 0u; }

    [[nodiscard]] auto ReadTrace() const { return trace; }

    [[nodiscard]] auto ReadStopped() const { return stopped; }
    [[nodiscard]] auto ReadHalted() const { return halted; }

    auto WriteDataRegisterByte(uint32_t r, uint32_t v) { data[r] = (data[r] & ~0xFFu) + (v & 0xFFu); }
    auto WriteDataRegisterWord(uint32_t r, uint32_t v) { data[r] = (data[r] & ~0xFFFFu) + (v & 0xFFFFu); }
    auto WriteDataRegisterLong(uint32_t r, uint32_t v) { data[r] = v; }

    auto WriteAddressRegisterLong(uint32_t r, uint32_t v) { addr[r] = v; };

    auto WriteSP(uint32_t v) { WriteAddressRegisterLong(7u, v); }
    auto WritePC(uint32_t v) { pc = v; }
    auto WriteUSP(uint32_t v) { usp = v; }
    auto WriteSSP(uint32_t v) { ssp = v; }
    auto WriteIRC(uint16_t v) { irc = v; }
    auto WriteIRD(uint16_t v) { ird = v; }

    auto WriteSR(uint16_t v) -> void;
    auto WriteCCR(uint16_t v) -> void;

    auto WriteFlagT(bool v) { flagT = v; }
    auto WriteFlagS(bool v) -> void;

    auto WriteInterruptPriorityMask(uint32_t v) { interruptPriorityMask = v & 7u; }

    auto WriteFlagX(uint32_t v) { flagX = v; };
    auto WriteFlagN(uint32_t v) { flagN = v; };
    auto WriteFlagZ(uint32_t v) { flagZ = v; };
    auto WriteFlagV(uint32_t v) { flagV = v; };
    auto WriteFlagC(uint32_t v) { flagC = v; };

    auto WriteTrace(bool v) { trace = v; }

    auto WriteStopped(bool v) { stopped = v; }
    auto WriteHalted(bool v) { stopped = v; halted = v; }

    auto Reset() -> void;
    auto Execute() -> void;

private:
    auto& GetInterrupts() { return interrupts; }
    auto& GetMemory() { return memory; }
    auto& GetObserver() { return observer; }

    auto ResetExternalDevices() -> void;
    auto ElapseCycles(uint32_t) -> void;
    auto InternalCycle() -> void;

    [[nodiscard]] auto TestCondition(uint32_t) const -> bool;

    auto ReadByte(uint32_t, uint32_t&) -> bool;
    auto ReadWord(uint32_t, uint32_t&) -> bool;
    auto ReadLong(uint32_t, uint32_t&) -> bool;

    auto WriteByte(uint32_t, uint32_t) -> bool;
    auto WriteWord(uint32_t, uint32_t) -> bool;
    auto WriteLong(uint32_t, uint32_t) -> bool;

    auto ReadWordNoException(uint32_t, uint32_t&) -> bool;
    auto ReadLongNoException(uint32_t, uint32_t&) -> bool;

    auto WriteWordNoException(uint32_t, uint32_t) -> bool;

    auto PushWord(uint32_t) -> bool;
    auto PushLong(uint32_t) -> bool;

    auto PopWord(uint32_t&) -> bool;
    auto PopLong(uint32_t&) -> bool;

    auto PushWordNoException(uint32_t) -> bool;
    auto PushLongNoException(uint32_t) -> bool;

    auto PushGroup0ExceptionStackFrame(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t) -> bool;
    auto PushGroup1And2ExceptionStackFrame(uint32_t, uint32_t) -> bool;

    auto ExecuteFinalPrefetchCycle() -> bool;
    auto ExecutePrefetchCycle() -> bool;
    auto ExecuteIllegal() -> void;

    auto Jump(uint32_t) -> bool;
    auto JumpNoException(uint32_t) -> bool;
    auto JumpSubroutine(uint32_t, uint32_t) -> bool;

    auto GetInterruptLevel() -> uint32_t;
    auto GetInterruptVector(uint32_t) -> uint32_t;

    auto EnterExceptionSupervisorMode() -> uint16_t;
    auto JumpToExceptionVector(uint32_t) -> bool;
    auto JumpToExceptionVectorNoException(uint32_t) -> bool;
    auto RaiseGroup0Exception(uint32_t, uint32_t) -> void;
    auto RaiseGroup1And2Exception(uint32_t) -> void;
    auto RaiseBusErrorException(uint32_t) -> void;
    auto RaiseAddressErrorException(uint32_t) -> void;
    auto RaiseIllegalInstructionException() -> void;
    auto RaiseZeroDivideException() -> void;
    auto RaiseChkException() -> void;
    auto RaiseTrapvException() -> void;
    auto RaisePrivilegeViolationException() -> void;
    auto RaiseTraceException() -> void;
    auto RaiseLineEmulatorException(uint32_t) -> void;
    auto RaiseLineAEmulatorException() -> void;
    auto RaiseLineFEmulatorException() -> void;
    auto RaiseTrapException(uint32_t) -> void;
    auto RaiseInterruptException(uint32_t) -> void;
    auto RaiseInterruptException(uint32_t, uint32_t) -> void;
    auto RaiseResetException() -> void;

    auto ExecuteInner() -> void;
    auto ExecuteLine0(uint32_t) -> void;
    auto ExecuteImmediateOperationByte(uint32_t) -> void;
    auto ExecuteImmediateOperationWord(uint32_t) -> void;
    auto ExecuteImmediateOperationLong(uint32_t) -> void;
    auto ExecuteImmediateOperationBset(uint32_t) -> void;

    auto ExecuteLine1(uint32_t) -> void;
    auto ExecuteLine2(uint32_t) -> void;
    auto ExecuteLine3(uint32_t) -> void;

    auto ExecuteLine4(uint32_t) -> void;
    auto ExecuteSingleOperationByte(uint32_t) -> void;
    auto ExecuteSingleOperationWord(uint32_t) -> void;
    auto ExecuteSingleOperationLong(uint32_t) -> void;
    auto ExecuteSingleOperationMove(uint32_t) -> void;
    auto ExecuteSingleOperationMisc(uint32_t) -> void;

    auto ExecuteLine5(uint32_t) -> void;
    auto ExecuteLine6(uint32_t) -> void;
    auto ExecuteLine7(uint32_t) -> void;
    auto ExecuteLine8(uint32_t) -> void;
    auto ExecuteLine9(uint32_t) -> void;
    auto ExecuteLineB(uint32_t) -> void;
    auto ExecuteLineC(uint32_t) -> void;
    auto ExecuteLineD(uint32_t) -> void;
    auto ExecuteLineE(uint32_t) -> void;

    [[nodiscard]] auto ComputeIndexFromExtensionWord(uint32_t) const -> uint32_t;
    
    [[nodiscard]] auto EffectiveAddressAddressIndirect(uint32_t, uint32_t&) const -> bool;
    template<typename T>
    auto EffectiveAddressAddressIncrement(uint32_t, uint32_t&) -> bool;
    template<typename T>
    auto EffectiveAddressAddressDecrement(uint32_t, uint32_t&) -> bool;
    template<typename T>
    auto EffectiveAddressAddressDecrementWithoutInternalCycle(uint32_t, uint32_t&) -> bool;
    auto EffectiveAddressAddressDisplacement(uint32_t, uint32_t&) -> bool;
    auto EffectiveAddressAddressIndex(uint32_t, uint32_t&) -> bool;
    auto EffectiveAddressAddressIndexControl(uint32_t, uint32_t&) -> bool;
    auto EffectiveAddressShort(uint32_t, uint32_t&) -> bool;
    auto EffectiveAddressLong(uint32_t, uint32_t&) -> bool;
    auto EffectiveAddressPCDisplacement(uint32_t, uint32_t&) -> bool;
    auto EffectiveAddressPCIndex(uint32_t, uint32_t&) -> bool;
    auto EffectiveAddressPCIndexControl(uint32_t, uint32_t&) -> bool;

    [[nodiscard]] auto ControlAddressIndirect(uint32_t, uint32_t&) const -> bool;
    [[nodiscard]] auto ControlAddressDisplacement(uint32_t, uint32_t&) -> bool;
    auto ControlAddressIndex(uint32_t, uint32_t&) -> bool;
    auto ControlShort(uint32_t, uint32_t&) -> bool;
    auto ControlLong(uint32_t, uint32_t&) -> bool;
    auto ControlPCDisplacement(uint32_t, uint32_t&) -> bool;
    auto ControlPCIndex(uint32_t, uint32_t&) -> bool;

    template<typename T>
    auto WriteDataRegister(uint32_t, uint32_t) -> void;

    template<typename T>
    auto ReadMemory(uint32_t, uint32_t&) -> bool;
    template<typename T>
    auto WriteMemory(uint32_t, uint32_t) -> bool;

    template<typename T>
    auto ReadFromDataRegister(uint32_t, uint32_t&, uint32_t&) -> bool;
    template<typename T>
    auto ReadFromAddressRegister(uint32_t, uint32_t&, uint32_t&) -> bool;
    template<typename T>
    auto ReadFromAddressIndirect(uint32_t, uint32_t&, uint32_t&) -> bool;
    template<typename T>
    auto ReadFromAddressIncrement(uint32_t, uint32_t&, uint32_t&) -> bool;
    template<typename T>
    auto ReadFromAddressDecrement(uint32_t, uint32_t&, uint32_t&) -> bool;
    template<typename T>
    auto ReadFromAddressDecrementWithoutInternalCycle(uint32_t, uint32_t&, uint32_t&) -> bool;
    template<typename T>
    auto ReadFromAddressDisplacement(uint32_t, uint32_t&, uint32_t&) -> bool;
    template<typename T>
    auto ReadFromAddressIndex(uint32_t, uint32_t&, uint32_t&) -> bool;
    template<typename T>
    auto ReadFromShort(uint32_t, uint32_t&, uint32_t&) -> bool;
    template<typename T>
    auto ReadFromLong(uint32_t, uint32_t&, uint32_t&) -> bool;
    template<typename T>
    auto ReadFromPCDisplacement(uint32_t, uint32_t&, uint32_t&) -> bool;
    template<typename T>
    auto ReadFromPCIndex(uint32_t, uint32_t&, uint32_t&) -> bool;
    template<typename T>
    auto ReadFromImmediate(uint32_t, uint32_t&, uint32_t&) -> bool;

    template<typename T>
    auto ExecuteOrImmediate(uint32_t) -> void;
    template<typename T>
    auto ExecuteOrImmediateDataRegister(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteOrImmediateEffectiveAddress(uint32_t) -> void;
    auto ExecuteOrImmediateCCR() -> void;
    auto ExecuteOrImmediateSR() -> void;

    template<typename T>
    auto ExecuteAndImmediate(uint32_t) -> void;
    template<typename T>
    auto ExecuteAndImmediateDataRegister(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteAndImmediateEffectiveAddress(uint32_t) -> void;
    auto ExecuteAndImmediateCCR() -> void;
    auto ExecuteAndImmediateSR() -> void;

    template<typename T>
    auto ExecuteSubImmediate(uint32_t) -> void;
    template<typename T>
    auto ExecuteSubImmediateDataRegister(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteSubImmediateEffectiveAddress(uint32_t) -> void;

    template<typename T>
    auto ExecuteAddImmediate(uint32_t) -> void;
    template<typename T>
    auto ExecuteAddImmediateDataRegister(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteAddImmediateEffectiveAddress(uint32_t) -> void;

    template<typename T>
    auto ExecuteEorImmediate(uint32_t) -> void;
    template<typename T>
    auto ExecuteEorImmediateDataRegister(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteEorImmediateEffectiveAddress(uint32_t) -> void;
    auto ExecuteEorImmediateCCR() -> void;
    auto ExecuteEorImmediateSR() -> void;

    template<typename T>
    auto ExecuteCmpImmediate(uint32_t) -> void;
    template<typename T>
    auto ExecuteCmpImmediateDataRegister(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteCmpImmediateEffectiveAddress(uint32_t) -> void;

    auto ExecuteBtstStatic(uint32_t) -> void;
    auto ExecuteBtstStaticDataRegister(uint32_t) -> void;
    template<auto Source>
    auto ExecuteBtstStaticEffectiveAddress(uint32_t) -> void;

    auto ExecuteBchgStatic(uint32_t) -> void;
    auto ExecuteBchgStaticDataRegister(uint32_t) -> void;
    template<auto Source>
    auto ExecuteBchgStaticEffectiveAddress(uint32_t) -> void;

    auto ExecuteBclrStatic(uint32_t) -> void;
    auto ExecuteBclrStaticDataRegister(uint32_t) -> void;
    template<auto Source>
    auto ExecuteBclrStaticEffectiveAddress(uint32_t) -> void;

    auto ExecuteBsetStatic(uint32_t) -> void;
    auto ExecuteBsetStaticDataRegister(uint32_t) -> void;
    template<auto Source>
    auto ExecuteBsetStaticEffectiveAddress(uint32_t) -> void;

    auto ExecuteBtstDynamic(uint32_t) -> void;
    auto ExecuteBtstDynamicDataRegister(uint32_t) -> void;
    template<auto Source>
    auto ExecuteBtstDynamicEffectiveAddress(uint32_t) -> void;

    auto ExecuteBchgDynamic(uint32_t) -> void;
    auto ExecuteBchgDynamicDataRegister(uint32_t) -> void;
    template<auto Source>
    auto ExecuteBchgDynamicEffectiveAddress(uint32_t) -> void;

    auto ExecuteBclrDynamic(uint32_t) -> void;
    auto ExecuteBclrDynamicDataRegister(uint32_t) -> void;
    template<auto Source>
    auto ExecuteBclrDynamicEffectiveAddress(uint32_t) -> void;

    auto ExecuteBsetDynamic(uint32_t) -> void;
    auto ExecuteBsetDynamicDataRegister(uint32_t) -> void;
    template<auto Source>
    auto ExecuteBsetDynamicEffectiveAddress(uint32_t) -> void;

    auto ExecuteMovepWordDataRegister(uint32_t) -> void;
    auto ExecuteMovepLongDataRegister(uint32_t) -> void;
    auto ExecuteMovepWordAddressDisplacement(uint32_t) -> void;
    auto ExecuteMovepLongAddressDisplacement(uint32_t) -> void;

    template<typename T>
    auto ExecuteMove(uint32_t) -> void;

    template<typename T>
    auto ExecuteMoveDataRegister(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteMoveDataRegister(uint32_t) -> void;

    template<typename T>
    auto ExecuteMoveAddressRegister(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteMoveAddressRegister(uint32_t) -> void;

    template<typename T>
    auto ExecuteMoveAddressIndirect(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteMoveAddressIndirect(uint32_t) -> void;

    template<typename T>
    auto ExecuteMoveAddressIncrement(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteMoveAddressIncrement(uint32_t) -> void;

    template<typename T>
    auto ExecuteMoveAddressDecrement(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteMoveAddressDecrement(uint32_t) -> void;

    template<typename T>
    auto ExecuteMoveAddressDisplacement(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteMoveAddressDisplacement(uint32_t) -> void;

    template<typename T>
    auto ExecuteMoveAddressIndex(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteMoveAddressIndex(uint32_t) -> void;

    template<typename T>
    auto ExecuteMoveShort(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteMoveShort(uint32_t) -> void;

    template<typename T>
    auto ExecuteMoveLong(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteMoveLong_Register(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteMoveLong(uint32_t) -> void;

    template<typename T>
    auto ExecuteNegx(uint32_t) -> void;
    template<typename T>
    void ExecuteNegxDataRegister(uint32_t);
    template<auto Source, typename T>
    void ExecuteNegxEffectiveAddress(uint32_t);

    template<typename T>
    auto ExecuteClr(uint32_t) -> void;
    template<typename T>
    void ExecuteClrDataRegister(uint32_t);
    template<auto Source, typename T>
    void ExecuteClrEffectiveAddress(uint32_t);

    template<typename T>
    auto ExecuteNeg(uint32_t) -> void;
    template<typename T>
    void ExecuteNegDataRegister(uint32_t);
    template<auto Source, typename T>
    void ExecuteNegEffectiveAddress(uint32_t);

    template<typename T>
    auto ExecuteNot(uint32_t) -> void;
    template<typename T>
    void ExecuteNotDataRegister(uint32_t);
    template<auto Source, typename T>
    void ExecuteNotEffectiveAddress(uint32_t);

    template<typename T>
    auto ExecuteNbcd(uint32_t) -> void;
    template<typename T>
    void ExecuteNbcdDataRegister(uint32_t);
    template<auto Source, typename T>
    void ExecuteNbcdEffectiveAddress(uint32_t);

    template<typename T>
    auto ExecuteTst(uint32_t) -> void;
    template<typename T>
    void ExecuteTstDataRegister(uint32_t);
    template<auto Source, typename T>
    void ExecuteTstEffectiveAddress(uint32_t);

    auto ExecuteSwapDataRegister(uint32_t) -> void;

    auto ExecutePea(uint32_t) -> void;
    template<auto Address>
    auto ExecutePeaEffectiveAddress(uint32_t) -> void;

    auto ExecuteTrap(uint32_t) -> void;
    auto ExecuteLink(uint32_t) -> void;
    auto ExecuteUnlk(uint32_t) -> void;
    auto ExecuteMoveToUSP(uint32_t) -> void;
    auto ExecuteMoveFromUSP(uint32_t) -> void;
    auto ExecuteReset() -> void;
    auto ExecuteNop() -> void;
    auto ExecuteStop() -> void;
    auto ExecuteRte() -> void;
    auto ExecuteRts() -> void;
    auto ExecuteTrapv() -> void;
    auto ExecuteRtr() -> void;

    template<typename T>
    auto ExecuteExtDataRegister(uint32_t) -> void;

    template<typename T>
    auto ExecuteMovemEffectiveAddress(uint32_t) -> void;
    template<auto EffectiveAddress, typename T>
    auto ExecuteMovemEffectiveAddress(uint32_t) -> void;
    template<class T>
    auto ExecuteRegisterListEffectiveAddress(uint32_t, uint32_t) -> bool;
    template<typename T>
    auto ExecuteMovemEffectiveAddressAddressDecrement(uint32_t) -> void;
    template<class T>
    auto ExecuteRegisterListAddressDecrement(uint32_t, uint32_t&) -> bool;

    template<typename T>
    auto ExecuteMovemRegister(uint32_t) -> void;
    template<auto Address, typename T>
    auto ExecuteMovemRegister(uint32_t) -> void;
    template<typename T>
    auto ExecuteMovemRegisterAddressIncrement(uint32_t opcode) -> void;
    template<typename T>
    auto ExecuteRegisterListRegister(uint32_t, uint32_t&) -> bool;

    auto ExecuteMoveFromSR(uint32_t) -> void;
    auto ExecuteMoveFromSRDataRegister(uint32_t) -> void;
    template<auto Source>
    auto ExecuteMoveFromSREffectiveAddress(uint32_t) -> void;

    auto ExecuteMoveToCCR(uint32_t) -> void;
    template<auto Source>
    auto ExecuteMoveToCCREffectiveAddress(uint32_t) -> void;

    auto ExecuteMoveToSR(uint32_t) -> void;
    template<auto Source>
    auto ExecuteMoveToSREffectiveAddress(uint32_t) -> void;

    auto ExecuteTas(uint32_t) -> void;
    auto ExecuteTasDataRegister(uint32_t) -> void;
    template<auto Source>
    auto ExecuteTasEffectiveAddress(uint32_t) -> void;

    auto ExecuteJsr(uint32_t) -> void;
    auto ExecuteJsrAddressIndirect(uint32_t) -> void;
    template<auto Control>
    auto ExecuteJsr(uint32_t) -> void;

    auto ExecuteJmp(uint32_t) -> void;
    template<auto Control>
    auto ExecuteJmp(uint32_t) -> void;

    auto ExecuteChk(uint32_t) -> void;
    template<auto Source>
    auto ExecuteChkDataRegister(uint32_t) -> void;

    auto ExecuteLea(uint32_t) -> void;
    template<auto Address>
    auto ExecuteLeaAddressRegister(uint32_t) -> void;

    template<typename T>
    auto ExecuteAddq(uint32_t) -> void;
    template<typename T>
    auto ExecuteAddqDataRegister(uint32_t) -> void;
    template<typename T>
    auto ExecuteAddqAddressRegister(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteAddqEffectiveAddress(uint32_t) -> void;

    template<typename T>
    auto ExecuteSubq(uint32_t) -> void;
    template<typename T>
    auto ExecuteSubqDataRegister(uint32_t) -> void;
    template<typename T>
    auto ExecuteSubqAddressRegister(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteSubqEffectiveAddress(uint32_t) -> void;

    auto ExecuteScc(uint32_t) -> void;
    auto ExecuteSccDataRegister(uint32_t) -> void;
    template<auto Source>
    auto ExecuteSccEffectiveAddress(uint32_t) -> void;

    auto ExecuteDbcc(uint32_t) -> void;
    auto ExecuteDbccConditionTrue() -> void;
    auto ExecuteDbccCounterNotExpired() -> void;
    auto ExecuteDbccCounterExpired() -> void;

    auto ExecuteBcc(uint32_t) -> void;
    auto ExecuteBccBranchTaken(uint32_t) -> void;
    auto ExecuteBccBranchNotTaken(uint32_t) -> void;
    auto ExecuteBsr(uint32_t) -> void;
    auto BccDisplacementAndSize(uint32_t, uint32_t&, uint32_t&) const -> void;
    
    auto ExecuteMoveqDataRegister(uint32_t) -> void;
    
    template<typename T>
    auto ExecuteOrDataRegister(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteOrDataRegister_RegisterImmediate(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteOrDataRegister(uint32_t) -> void;
    
    template<typename T>
    auto ExecuteOrEffectiveAddress(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteOrEffectiveAddress(uint32_t) -> void;

    auto ExecuteDivuDataRegister(uint32_t) -> void;
    template<auto Source>
    auto ExecuteDivuDataRegister(uint32_t) -> void;

    auto ExecuteDivsDataRegister(uint32_t) -> void;
    template<auto Source>
    auto ExecuteDivsDataRegister(uint32_t) -> void;

    auto ExecuteSbcdDataRegister(uint32_t) -> void;
    auto ExecuteSbcdAddressDecrement(uint32_t) -> void;

    template<typename T>
    auto ExecuteSubDataRegister(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteSubDataRegister_RegisterImmediate(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteSubDataRegister(uint32_t) -> void;

    template<typename T>
    auto ExecuteSubAddressRegister(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteSubAddressRegister_RegisterImmediate(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteSubAddressRegister(uint32_t) -> void;

    template<typename T>
    auto ExecuteSubEffectiveAddress(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteSubEffectiveAddress(uint32_t) -> void;

    template<typename T>
    auto ExecuteSubxDataRegister(uint32_t) -> void;
    template<typename T>
    auto ExecuteSubxAddressDecrement(uint32_t) -> void;

    template<typename T>
    auto ExecuteCmpDataRegister(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteCmpDataRegister(uint32_t) -> void;

    template<typename T>
    auto ExecuteCmpAddressRegister(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteCmpAddressRegister(uint32_t) -> void;

    template<typename T>
    auto ExecuteCmpAddressIncrement(uint32_t) -> void;

    template<typename T>
    auto ExecuteEorDataRegister(uint32_t) -> void;
    template<typename T>
    auto ExecuteEorEffectiveAddress(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteEorEffectiveAddress(uint32_t) -> void;

    template<typename T>
    auto ExecuteAndDataRegister(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteAndDataRegister_RegisterImmediate(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteAndDataRegister(uint32_t) -> void;

    template<typename T>
    auto ExecuteAndEffectiveAddress(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteAndEffectiveAddress(uint32_t) -> void;
    
    auto ExecuteMuluDataRegister(uint32_t) -> void;
    template<auto Source>
    auto ExecuteMuluDataRegister(uint32_t) -> void;
    
    auto ExecuteMulsDataRegister(uint32_t) -> void;
    template<auto Source>
    auto ExecuteMulsDataRegister(uint32_t) -> void;
    
    auto ExecuteAbcdDataRegister(uint32_t) -> void;
    auto ExecuteAbcdAddressDecrement(uint32_t) -> void;
    
    auto ExecuteExgDataRegisterDataRegister(uint32_t) -> void;
    auto ExecuteExgAddressRegisterAddressRegister(uint32_t) -> void;
    auto ExecuteExgDataRegisterAddressRegister(uint32_t) -> void;

    template<typename T>
    auto ExecuteAddDataRegister(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteAddDataRegister_RegisterImmediate(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteAddDataRegister(uint32_t) -> void;

    template<typename T>
    auto ExecuteAddAddressRegister(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteAddAddressRegister_RegisterImmediate(uint32_t) -> void;
    template<auto Source, typename T>
    auto ExecuteAddAddressRegister(uint32_t) -> void;

    template<typename T>
    auto ExecuteAddEffectiveAddress(uint32_t) -> void;

    template<auto Source, typename T>
    auto ExecuteAddEffectiveAddress(uint32_t) -> void;

    template<typename T>
    auto ExecuteAddxDataRegister(uint32_t) -> void;
    template<typename T>
    auto ExecuteAddxAddressDecrement(uint32_t) -> void;

    template<typename T>
    auto ExecuteShiftRotateRightDataRegister(uint32_t) -> void;
    auto ExecuteShiftRotateRightEffectiveAddress(uint32_t) -> void;
    template<typename T>
    auto ExecuteShiftRotateLeftDataRegister(uint32_t) -> void;
    auto ExecuteShiftRotateLeftEffectiveAddress(uint32_t) -> void;

    template<auto ShiftRotate, typename>
    auto ExecuteShiftRotateCountDataRegister(uint32_t) -> void;
    template<auto ShiftRotate, typename>
    auto ExecuteShiftRotateRegisterDataRegister(uint32_t) -> void;

    template<auto ShiftRotate>
    auto ExecuteShiftRotateEffectiveAddress(uint32_t) -> void;
    template<auto ShiftRotate, auto Source>
    auto ExecuteShiftRotateEffectiveAddress(uint32_t) -> void;

    template<typename T>
    auto WriteFlagX(uint32_t) -> void;
    template<typename T>
    auto WriteFlagN(uint32_t) -> void;
    template<typename T>
    auto WriteFlagZ(uint32_t) -> void;
    template<typename T>
    auto WriteFlagV(uint32_t) -> void;
    template<typename T>
    auto WriteFlagC(uint32_t) -> void;

    template<typename T>
    auto WriteFlagsArithmetic(uint32_t, uint32_t, uint32_t) -> void;
    template<typename T>
    auto WriteFlagsCompare(uint32_t, uint32_t, uint32_t) -> void;
    template<typename T>
    auto WriteFlagsLogical(uint32_t result) -> void;
    template<typename T>
    auto WriteFlagsMultiprecision(uint32_t, uint32_t, uint32_t) -> void;
    template<typename T>
    auto WriteFlagsDivisionOverflow() -> void;
    template<typename T>
    auto WriteFlagsShiftRotate(uint32_t, uint32_t, uint32_t, uint32_t) -> void;
    template<typename T>
    auto WriteFlagsRotate(uint32_t, uint32_t) -> void;

    template<typename T>
    auto Add(uint32_t, uint32_t) -> uint32_t;
    template<typename T>
    auto Sub(uint32_t, uint32_t) -> uint32_t;
    template<class T>
    auto Cmp(uint32_t, uint32_t) -> void;
    template<class T>
    auto Or(uint32_t, uint32_t) -> uint32_t;
    template<class T>
    auto And(uint32_t, uint32_t) -> uint32_t;
    template<class T>
    auto Eor(uint32_t, uint32_t) -> uint32_t;

    template<class T>
    auto Mulu(uint32_t, uint32_t) -> uint32_t;
    template<class T>
    auto Muls(uint32_t, uint32_t) -> uint32_t;

    template<typename T>
    auto Adda(uint32_t, uint32_t) -> uint32_t;
    template<typename T>
    auto Suba(uint32_t, uint32_t) -> uint32_t;
    template<typename T>
    auto Cmpa(uint32_t, uint32_t) -> void;

    template<typename T>
    auto Addx(uint32_t, uint32_t) -> uint32_t;
    template<typename T>
    auto Subx(uint32_t, uint32_t) -> uint32_t;
    template<typename T>
    auto Abcd(uint32_t, uint32_t) -> uint32_t;
    template<typename T>
    auto Sbcd(uint32_t, uint32_t) -> uint32_t;

    template<typename T>
    auto Btst(uint32_t, uint32_t) -> void;
    template<typename T>
    auto Bchg(uint32_t, uint32_t) -> uint32_t;
    template<typename T>
    auto Bclr(uint32_t, uint32_t) -> uint32_t;
    template<typename T>
    auto Bset(uint32_t, uint32_t) -> uint32_t;

    template<typename T>
    auto Move(uint32_t) -> uint32_t;
    template<typename T>
    auto Movea(uint32_t) -> uint32_t;

    template<typename T>
    auto Negx(uint32_t) -> uint32_t;
    template<typename T>
    auto Clr(uint32_t) -> uint32_t;
    template<typename T>
    auto Neg(uint32_t) -> uint32_t;
    template<typename T>
    auto Not(uint32_t) -> uint32_t;
    template<typename T>
    auto Nbcd(uint32_t) -> uint32_t;
    template<typename T>
    auto Tst(uint32_t) -> void;

    template<typename T>
    auto Ext(uint32_t) -> uint32_t;

    auto Swap(uint32_t) -> uint32_t;
    auto Tas(uint32_t) -> uint32_t;

    [[nodiscard]] auto Scc(uint32_t, uint32_t) const -> uint32_t;

    auto Moveq(uint32_t) -> uint32_t;

    template<typename T>
    auto Asr(uint32_t, uint32_t) -> uint32_t;
    template<typename T>
    static auto AsrShift(uint32_t, uint32_t) -> uint32_t;
    template<typename T>
    static auto AsrCarry(uint32_t, uint32_t) -> uint32_t;

    template<typename T>
    auto Lsr(uint32_t, uint32_t) -> uint32_t;
    template<typename T>
    static auto LsrShift(uint32_t, uint32_t) -> uint32_t;
    template<typename T>
    static auto LsrCarry(uint32_t, uint32_t) -> uint32_t;

    template<typename T>
    auto Roxr(uint32_t, uint32_t) -> uint32_t;
    template<typename T>
    static auto RoxrRotate(uint32_t, uint32_t, uint32_t) -> uint32_t;
    template<typename T>
    static auto RoxrCarry(uint32_t, uint32_t, uint32_t) -> uint32_t;

    template<typename T>
    auto Ror(uint32_t, uint32_t) -> uint32_t;
    template<typename T>
    static auto RorRotate(uint32_t, uint32_t) -> uint32_t;
    template<typename T>
    static auto RorCarry(uint32_t, uint32_t) -> uint32_t;

    template<typename T>
    auto Asl(uint32_t, uint32_t) -> uint32_t;
    template<typename T>
    static auto AslShift(uint32_t, uint32_t) -> uint32_t;
    template<typename T>
    static auto AslOverflow(uint32_t, uint32_t) -> uint32_t;
    template<typename T>
    static auto AslCarry(uint32_t, uint32_t) -> uint32_t;

    template<typename T>
    auto Lsl(uint32_t, uint32_t) -> uint32_t;
    template<typename T>
    static auto LslShift(uint32_t, uint32_t) -> uint32_t;
    template<typename T>
    static auto LslCarry(uint32_t, uint32_t) -> uint32_t;

    template<typename T>
    auto Roxl(uint32_t, uint32_t) -> uint32_t;
    template<typename T>
    static auto RoxlRotate(uint32_t, uint32_t, uint32_t) -> uint32_t;
    template<typename T>
    static auto RoxlCarry(uint32_t, uint32_t, uint32_t) -> uint32_t;

    template<typename T>
    auto Rol(uint32_t, uint32_t) -> uint32_t;
    template<typename T>
    static auto RolRotate(uint32_t, uint32_t) -> uint32_t;
    template<typename T>
    static auto RolCarry(uint32_t, uint32_t) -> uint32_t;

    Interrupts& interrupts;
    Memory& memory;
    Observer& observer;

    std::array<uint32_t, 8> data;
    std::array<uint32_t, 8> addr;

    uint32_t pc;
    uint32_t usp;
    uint32_t ssp;
    uint16_t irc;
    uint16_t ird;

    uint32_t interruptPriorityMask;

    uint32_t flagX;
    uint32_t flagN;
    uint32_t flagZ;
    uint32_t flagV;
    uint32_t flagC;

    bool flagT;
    bool flagS;

    bool trace;
    bool stopped;
    bool halted;
};

}
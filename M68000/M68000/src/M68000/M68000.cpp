#include "M68000/M68000.h"
#include "M68000/M68000_Constants.h"
#include "M68000/M68000_Int.h"
#include "M68000/M68000_Opcode.h"
#include "M68000/M68000_EffectiveAddress.h"

using namespace rbrown::m68000;

M68000::M68000(Interrupts& i, Memory& m, Observer& o) :
    interrupts(i),
    memory(m),
    observer(o),
    data{},
    addr{},
    pc{},
    usp{},
    ssp{},
    irc{},
    ird{},
    interruptPriorityMask{ 7u },
    flagX{},
    flagN{},
    flagZ{ 1u },
    flagV{},
    flagC{},
    flagT{},
    flagS{ true },
    trace{},
    stopped{},
    halted{} {}

// Observer wrappers

auto M68000::ResetExternalDevices() -> void { GetObserver().Reset(); }

auto M68000::ElapseCycles(uint32_t cycles) -> void { GetObserver().Cycles(cycles); }

auto M68000::InternalCycle() -> void { GetObserver().Cycles(2u); }

// Status register

auto M68000::ReadSR() const -> uint16_t {
    uint16_t sr{};
    if (ReadFlagT()) sr |= FLAG_T;
    if (ReadFlagS()) sr |= FLAG_S;
    sr |= ReadInterruptPriorityMask() << 8u;
    sr |= ReadCCR();
    return sr;
}

auto M68000::ReadCCR() const -> uint16_t {
    uint16_t ccr{};
    if (ReadFlagC()) ccr |= FLAG_C;
    if (ReadFlagV()) ccr |= FLAG_V;
    if (ReadFlagZ()) ccr |= FLAG_Z;
    if (ReadFlagN()) ccr |= FLAG_N;
    if (ReadFlagX()) ccr |= FLAG_X;
    return ccr;
}

auto M68000::WriteSR(uint16_t v) -> void {
    WriteFlagT(v & FLAG_T);
    WriteFlagS(v & FLAG_S);
    WriteInterruptPriorityMask(v >> 8u);
    WriteCCR(v);
}

auto M68000::WriteCCR(uint16_t v) -> void {
    WriteFlagC((v & FLAG_C) ? 0x80000000u : 0u);
    WriteFlagV((v & FLAG_V) ? 0x80000000u : 0u);
    WriteFlagZ((v & FLAG_Z) ? 0x00000000u : 1u);
    WriteFlagN((v & FLAG_N) ? 0x80000000u : 0u);
    WriteFlagX((v & FLAG_X) ? 0x80000000u : 0u);
}

auto M68000::WriteFlagS(bool v) -> void {
    if (flagS ^ v) {
        if (flagS) {
            WriteSSP(ReadSP());
            WriteSP(ReadUSP());
        } else {
            WriteUSP(ReadSP());
            WriteSP(ReadSSP());
        }
        flagS = v;
    }
}

constexpr auto TestCondition(uint32_t status, uint32_t condition) -> bool {
    const auto n = (status & 0x08u) != 0u;
    const auto z = (status & 0x04u) != 0u;
    const auto v = (status & 0x02u) != 0u;
    const auto c = (status & 0x01u) != 0u;
    switch (condition) {
        case CONDITION_CODE_T: return true;
        case CONDITION_CODE_F: return false;
        case CONDITION_CODE_HI: return !(c || z);
        case CONDITION_CODE_LS: return (c || z);
        case CONDITION_CODE_CC: return !c;
        case CONDITION_CODE_CS: return c;
        case CONDITION_CODE_NE: return !z;
        case CONDITION_CODE_EQ: return z;
        case CONDITION_CODE_VC: return !v;
        case CONDITION_CODE_VS: return v;
        case CONDITION_CODE_PL: return !n;
        case CONDITION_CODE_MI: return n;
        case CONDITION_CODE_GE: return !(n ^ v);
        case CONDITION_CODE_LT: return (n ^ v);
        case CONDITION_CODE_GT: return !(z || (n ^ v));
        case CONDITION_CODE_LE: return (z || (n ^ v));
        default: return false;
    }
}

consteval auto GenerateConditionTable() -> std::array<uint16_t, 8> {
    std::array<uint16_t, 8> table{};
    for (auto condition = 0u; condition < 16u; condition += 2) {
        auto entry = 0u;
        for (auto status = 0u; status < 16u; ++status) {
            if (TestCondition(status, condition)) {
                entry += 1u << status;
            }
        }
        table[condition >> 1u] = entry;
    }
    return table;
}

constexpr auto CONDITION_LOOKUP_TABLE = GenerateConditionTable();

constexpr auto TestConditionWithLookup(uint32_t status, uint32_t condition) -> bool {
    const auto entry = CONDITION_LOOKUP_TABLE[condition >> 1u];
    return ((entry >> status) ^ condition) & 1u;
}

auto M68000::TestCondition(uint32_t condition) const -> bool {
    return TestConditionWithLookup(ReadCCR() & 0xFu, condition & 0xFu);
}

// Memory access

constexpr auto IsOddAddress(uint32_t address) -> bool {
    return address & 1u;
}

auto M68000::ReadByte(uint32_t address, uint32_t& result) -> bool {
    InternalCycle();
    InternalCycle();
    if (!GetMemory().ReadByte(address, result)) [[unlikely]] {
        RaiseBusErrorException(address);
        return false;
    }
    return true;
}

auto M68000::ReadWord(uint32_t address, uint32_t& result) -> bool {
    if (IsOddAddress(address)) [[unlikely]] {
        RaiseAddressErrorException(address);
        return false;
    }
    InternalCycle();
    InternalCycle();
    if (!GetMemory().ReadWord(address, result)) [[unlikely]] {
        RaiseBusErrorException(address);
        return false;
    }
    return true;
}

auto M68000::ReadLong(uint32_t address, uint32_t& result) -> bool {
    uint32_t high{}, low{};
    const auto success = ReadWord(address, high) &&
                         ReadWord(address + 2u, low);
    result = (high << 16u) + low;
    return success;
}

auto M68000::WriteByte(uint32_t address, uint32_t value) -> bool {
    InternalCycle();
    InternalCycle();
    if (!GetMemory().WriteByte(address, value)) [[unlikely]] {
        RaiseBusErrorException(address);
        return false;
    }
    return true;
}

auto M68000::WriteWord(uint32_t address, uint32_t value) -> bool {
    if (IsOddAddress(address)) [[unlikely]] {
        RaiseAddressErrorException(address);
        return false;
    }
    InternalCycle();
    InternalCycle();
    if (!GetMemory().WriteWord(address, value)) [[unlikely]] {
        RaiseBusErrorException(address);
        return false;
    }
    return true;
}

auto M68000::WriteLong(uint32_t address, uint32_t value) -> bool {
    return WriteWord(address, value >> 16u) &&
           WriteWord(address + 2u, value);
}

auto M68000::ReadWordNoException(uint32_t address, uint32_t& result) -> bool {
    if (IsOddAddress(address)) {
        return false;
    }
    InternalCycle();
    InternalCycle();
    return GetMemory().ReadWord(address, result);
}

auto M68000::ReadLongNoException(uint32_t address, uint32_t& result) -> bool {
    uint32_t high{}, low{};
    const auto success = ReadWordNoException(address, high) &&
                         ReadWordNoException(address + 2u, low);
    result = (high << 16u) + low;
    return success;
}

auto M68000::WriteWordNoException(uint32_t address, uint32_t value) -> bool {
    if (IsOddAddress(address)) {
        return false;
    }
    InternalCycle();
    InternalCycle();
    return GetMemory().WriteWord(address, value);
}

// Stack access

auto M68000::PushWord(uint32_t v) -> bool {
    const auto sp = ReadSP() - 2u;
    WriteSP(sp);
    return WriteWord(sp, v);
}

auto M68000::PushLong(uint32_t v) -> bool {
    return PushWord(v) &&
           PushWord(v >> 16u);
}

auto M68000::PopWord(uint32_t& v) -> bool {
    const auto sp = ReadSP();
    WriteSP(sp + 2u);
    return ReadWord(sp, v);
}

auto M68000::PopLong(uint32_t& v) -> bool {
    uint32_t hi{}, lo{};
    if (PopWord(hi) && PopWord(lo)) [[likely]] {
        v = (hi << 16u) + lo;
        return true;
    }
    return false;
}

auto M68000::PushWordNoException(uint32_t v) -> bool {
    const auto sp = ReadSP() - 2u;
    WriteSP(sp);
    return WriteWordNoException(sp, v);
}

auto M68000::PushLongNoException(uint32_t v) -> bool{
    return PushWordNoException(v) &&
           PushWordNoException(v >> 16u);
}

auto M68000::PushGroup0ExceptionStackFrame(
    uint32_t exceptionPc,
    uint32_t sr,
    uint32_t exceptionIrd,
    uint32_t address,
    uint32_t status) -> bool {
    return PushLongNoException(exceptionPc) &&
           PushWordNoException(sr) &&
           PushWordNoException(exceptionIrd) &&
           PushLongNoException(address) &&
           PushWordNoException(status);
}

auto M68000::PushGroup1And2ExceptionStackFrame(
    uint32_t exceptionPc,
    uint32_t sr) -> bool {
    return PushLong(exceptionPc) &&
           PushWord(sr);
}

// Prefetch

auto M68000::ExecutePrefetchCycle() -> bool {
    const auto currentPc = ReadPC();
    uint32_t ir;
    if (ReadWord(currentPc + 4u, ir)) [[unlikely]] {
        WriteIRC(ir);
        WritePC(currentPc + 2u);
        return true;
    }
    return false;
}

auto M68000::ExecuteFinalPrefetchCycle() -> bool {
    const auto ir = ReadIRC();
    if (ExecutePrefetchCycle()) [[unlikely]] {
        WriteIRD(ir);
        return true;
    }
    return false;
}

// Program flow change

auto M68000::Jump(uint32_t target) -> bool {
    WritePC(target);
    uint32_t value;
    if (!ReadWord(target, value)) [[unlikely]] {
        return false;
    }
    WriteIRD(value);
    if (!ReadWord(target + 2u, value)) [[unlikely]] {
        return false;
    }
    WriteIRC(value);
    return true;
}

auto M68000::JumpNoException(uint32_t target) -> bool {
    WritePC(target);
    uint32_t value;
    if (!ReadWordNoException(target, value)) [[unlikely]] {
        return false;
    }
    WriteIRD(value);
    if (!ReadWordNoException(target + 2u, value)) [[unlikely]] {
        return false;
    }
    WriteIRC(value);
    return true;
}

auto M68000::JumpSubroutine(uint32_t returnAddress, uint32_t target) -> bool {
    WritePC(target);
    uint32_t value;
    if (!ReadWord(target, value)) [[unlikely]] {
        return false;
    }
    WriteIRD(value);
    if (!PushLong(returnAddress)) [[unlikely]] {
        return false;
    }
    if (!ReadWord(target + 2u, value)) [[unlikely]] {
        return false;
    }
    WriteIRC(value);
    return true;
}

// Exception Handling

auto M68000::GetInterruptLevel() -> uint32_t {
    return GetInterrupts().GetInterruptLevel();
}

auto M68000::GetInterruptVector(uint32_t v) -> uint32_t {
    return GetInterrupts().GetInterruptVector(v & 0x7u);
}

auto M68000::EnterExceptionSupervisorMode() -> uint16_t {
    const auto sr = ReadSR();
    WriteTrace(false);
    WriteFlagT(false);
    WriteFlagS(true);
    return sr;
}

auto M68000::JumpToExceptionVector(uint32_t vector) -> bool {
    uint32_t target;
    if (!ReadLong(vector, target)) [[unlikely]] {
        return false;
    }
    InternalCycle();
    return Jump(target);
}

auto M68000::JumpToExceptionVectorNoException(uint32_t vector) -> bool {
    uint32_t target;
    if (!ReadLongNoException(vector, target)) [[unlikely]] {
        return false;
    }
    InternalCycle();
    return JumpNoException(target);
}

auto M68000::RaiseGroup0Exception(uint32_t vector, uint32_t address) -> void {
    const auto sr = EnterExceptionSupervisorMode();
    const auto exceptionPc = ReadPC();
    const auto exceptionIrd = ReadIRD();
    const uint32_t status{}; // TODO
    if (!PushGroup0ExceptionStackFrame(exceptionPc, sr, exceptionIrd, address, status)) {
        WriteHalted(true);
        return;
    }
    if (!JumpToExceptionVectorNoException(vector)) {
        WriteHalted(true);
        return;
    }
}

auto M68000::RaiseGroup1And2Exception(uint32_t vector) -> void {
    const auto sr = EnterExceptionSupervisorMode();
    const auto exceptionPc = ReadPC();
    if (!PushGroup1And2ExceptionStackFrame(exceptionPc, sr)) {
        return;
    }
    if (!JumpToExceptionVector(vector)) {
        return;
    }
}

auto M68000::RaiseBusErrorException(uint32_t address) -> void {
    RaiseGroup0Exception(VECTOR_BUS_ERROR, address);
}

auto M68000::RaiseAddressErrorException(uint32_t address) -> void {
    RaiseGroup0Exception(VECTOR_ADDRESS_ERROR, address);
}

auto M68000::RaiseIllegalInstructionException() -> void {
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    RaiseGroup1And2Exception(VECTOR_ILLEGAL_INSTRUCTION);
}

auto M68000::RaiseZeroDivideException() -> void {
    InternalCycle();
    InternalCycle();
    RaiseGroup1And2Exception(VECTOR_ZERO_DIVIDE);
}

auto M68000::RaiseChkException() -> void {
    // There's a 6 cycle disagreement between the UM and yacht.txt
    ElapseCycles(10u);
    RaiseGroup1And2Exception(VECTOR_CHK_INSTRUCTION);
}

auto M68000::RaiseTrapvException() -> void {
    RaiseGroup1And2Exception(VECTOR_TRAPV_INSTRUCTION);
}

auto M68000::RaisePrivilegeViolationException() -> void {
    ElapseCycles(4u);
    RaiseGroup1And2Exception(VECTOR_PRIVILEGE_VIOLATION);
}

auto M68000::RaiseTraceException() -> void {
    if (ReadHalted()) [[unlikely]] {
        return;
    }
    if (!ReadTrace()) {
        return;
    }
    InternalCycle();
    InternalCycle();
    const auto sr = EnterExceptionSupervisorMode();
    const auto exceptionPc = ReadPC();
    if (!PushGroup1And2ExceptionStackFrame(exceptionPc, sr)) {
        return;
    }
    if (!JumpToExceptionVector(VECTOR_TRACE)) {
        return;
    }
    WriteStopped(false);
}

auto M68000::RaiseLineEmulatorException(uint32_t vector) -> void {
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto sr = EnterExceptionSupervisorMode();
    const auto exceptionPc = ReadPC() - 2u;
    if (!PushGroup1And2ExceptionStackFrame(exceptionPc, sr)) {
        return;
    }
    if (!JumpToExceptionVector(vector)) {
        return;
    }
}

auto M68000::RaiseLineAEmulatorException() -> void {
    RaiseLineEmulatorException(VECTOR_LINE_1010_EMULATOR);
}

auto M68000::RaiseLineFEmulatorException() -> void {
    RaiseLineEmulatorException(VECTOR_LINE_1111_EMULATOR);
}

auto M68000::RaiseTrapException(uint32_t vector) -> void {
    InternalCycle();
    InternalCycle();
    WritePC(ReadPC() + 2u);
    RaiseGroup1And2Exception(VECTOR_TRAP_BASE + (vector << 2u));
}

auto M68000::RaiseInterruptException(uint32_t level) -> void {
    if (ReadHalted()) [[unlikely]] {
        return;
    }
    // Note: This isn't entirely correct, yacht states the cycles are interleaved with
    // pushing the stack frame
    ElapseCycles(14u);
    const auto sr = EnterExceptionSupervisorMode();
    const auto exceptionPc = ReadPC();
    const auto vector = GetInterruptVector(level);
    WriteInterruptPriorityMask(level);
    if (!PushGroup1And2ExceptionStackFrame(exceptionPc, sr)) [[unlikely]] {
        return;
    }
    if (!JumpToExceptionVector((vector & 0xFFu) << 2u)) [[unlikely]] {
        return;
    }
    WriteStopped(false);
}

auto M68000::RaiseInterruptException(uint32_t oldLevel, uint32_t newLevel) -> void {
    const auto mask = ReadInterruptPriorityMask();
    const auto nmi = oldLevel < 7u && newLevel == 7u;
    const auto irq = newLevel > mask;
    if (nmi || irq) {
        RaiseInterruptException(newLevel);
    }
}

auto M68000::RaiseResetException() -> void {
    EnterExceptionSupervisorMode();
    WriteInterruptPriorityMask(7u);
    uint32_t sp{};
    if (!ReadLong(VECTOR_RESET_STACK_POINTER, sp)) [[unlikely]] {
        return;
    }
    WriteSP(sp);
    if (JumpToExceptionVector(VECTOR_RESET_PROGRAM_COUNTER)) [[unlikely]] {
        return;
    }
    WriteHalted(false);
}

// Illegal instruction

auto M68000::ExecuteIllegal() -> void {
    RaiseIllegalInstructionException();
}

auto M68000::Reset() -> void {
    RaiseResetException();
}

auto M68000::Execute() -> void {
    const auto oldLevel = GetInterruptLevel();
    if (ReadStopped()) [[unlikely]] {
        InternalCycle();
        InternalCycle();
    } else if (ReadFlagT()) [[unlikely]] {
        WriteTrace(true);
        ExecuteInner();
        RaiseTraceException();
    } else [[likely]] {
        ExecuteInner();
    }
    const auto newLevel = GetInterruptLevel();
    RaiseInterruptException(oldLevel, newLevel);
}

auto M68000::ExecuteInner() -> void {
    const auto opcode = ReadIRD();
    switch (OpcodeLine(opcode)) {
        case 0x0u: return ExecuteLine0(opcode);
        case 0x1u: return ExecuteLine1(opcode);
        case 0x2u: return ExecuteLine2(opcode);
        case 0x3u: return ExecuteLine3(opcode);
        case 0x4u: return ExecuteLine4(opcode);
        case 0x5u: return ExecuteLine5(opcode);
        case 0x6u: return ExecuteLine6(opcode);
        case 0x7u: return ExecuteLine7(opcode);
        case 0x8u: return ExecuteLine8(opcode);
        case 0x9u: return ExecuteLine9(opcode);
        case 0xAu: return RaiseLineAEmulatorException();
        case 0xBu: return ExecuteLineB(opcode);
        case 0xCu: return ExecuteLineC(opcode);
        case 0xDu: return ExecuteLineD(opcode);
        case 0xEu: return ExecuteLineE(opcode);
        case 0xFu: return RaiseLineFEmulatorException();
            [[unlikely]] default: return ExecuteIllegal();
    }
}

#include <bitset>

#include "M68000/M68000.h"

#include "M68000/M68000_Opcode.h"
#include "M68000/M68000_Int.h"

// NOOP instruction
constexpr auto NOOP = 0x4E71u;

// Status register bits
constexpr auto FLAG_T = 0x8000u;
constexpr auto FLAG_S = 0x2000u;
constexpr auto FLAG_X = 0x0010u;
constexpr auto FLAG_N = 0x0008u;
constexpr auto FLAG_Z = 0x0004u;
constexpr auto FLAG_V = 0x0002u;
constexpr auto FLAG_C = 0x0001u;

// Condition codes

constexpr auto CONDITION_CODE_T = 0x0u;
constexpr auto CONDITION_CODE_F = 0x1u;
constexpr auto CONDITION_CODE_HI = 0x2u;
constexpr auto CONDITION_CODE_LS = 0x3u;
constexpr auto CONDITION_CODE_CC = 0x4u;
constexpr auto CONDITION_CODE_CS = 0x5u;
constexpr auto CONDITION_CODE_NE = 0x6u;
constexpr auto CONDITION_CODE_EQ = 0x7u;
constexpr auto CONDITION_CODE_VC = 0x8u;
constexpr auto CONDITION_CODE_VS = 0x9u;
constexpr auto CONDITION_CODE_PL = 0xAu;
constexpr auto CONDITION_CODE_MI = 0xBu;
constexpr auto CONDITION_CODE_GE = 0xCu;
constexpr auto CONDITION_CODE_LT = 0xDu;
constexpr auto CONDITION_CODE_GT = 0xEu;
constexpr auto CONDITION_CODE_LE = 0xFu;

// Exception vectors
constexpr auto VECTOR_RESET_STACK_POINTER = 0x000u;
constexpr auto VECTOR_RESET_PROGRAM_COUNTER = 0x004u;
constexpr auto VECTOR_BUS_ERROR = 0x008u;
constexpr auto VECTOR_ADDRESS_ERROR = 0x00C;
constexpr auto VECTOR_ILLEGAL_INSTRUCTION = 0x010u;
constexpr auto VECTOR_ZERO_DIVIDE = 0x014u;
constexpr auto VECTOR_CHK_INSTRUCTION = 0x018u;
constexpr auto VECTOR_TRAPV_INSTRUCTION = 0x01Cu;
constexpr auto VECTOR_PRIVILEGE_VIOLATION = 0x020u;
[[maybe_unused]] constexpr auto VECTOR_TRACE = 0x024u;
constexpr auto VECTOR_LINE_1010_EMULATOR = 0x028u;
constexpr auto VECTOR_LINE_1111_EMULATOR = 0x02Cu;

constexpr auto VECTOR_TRAP_BASE = 0x0080u;

namespace rbrown::m68000 {

M68000::M68000(Interrupts& i, Memory& m, Observer& o) :
    interrupts(i),
    memory(m),
    observer(o),
    data{},
    addr{},
    pc{},
    usp{},
    ssp{},
    irc{ NOOP },
    ird{ NOOP },
    interruptPriorityMask{ 7u },
    flagX{},
    flagN{},
    flagZ{ 1u },
    flagV{},
    flagC{},
    flagT{},
    flagS{ true },
    stopped{},
    halted{} {}

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

// Note when the code is calling ElapseCycles this generally indicates a lack
// of understanding about the nature of the cycles we want to elapse.
// Are they internal cycles? bus cycles? In the case of exceptions did we miss a bus cycle earlier in the process?
// etc
auto M68000::ElapseCycles(uint32_t cycles) -> void { GetObserver().Cycles(cycles); }

auto M68000::InternalCycle() -> void { ElapseCycles(2u); }

auto M68000::BusCycle() -> void { ElapseCycles(4u); }

auto M68000::ResetExternalDevices() -> void { GetObserver().Reset(); }

namespace {

// Interrupts

auto GetInterruptLevel(M68000& m68000) {
    return m68000.GetInterrupts().GetInterruptLevel();
}

auto GetInterruptVector(M68000& m68000, uint32_t v) {
    return m68000.GetInterrupts().GetInterruptVector(v & 0x7u);
}

// Memory access

// These need to be declared first to break a circular dependency
auto RaiseBusErrorException(M68000&, uint32_t) -> void;
auto RaiseAddressErrorException(M68000&, uint32_t) -> void;

auto ReadByte(M68000& m68000, uint32_t address, uint32_t& result) {
    m68000.BusCycle();
    if (m68000.GetMemory().ReadByte(address, result)) {
        return true;
    }
    RaiseBusErrorException(m68000, address);
    return false;
}

auto ReadWord(M68000& m68000, uint32_t address, uint32_t& result) {
    if (address & 1u) {
        RaiseAddressErrorException(m68000, address);
        return false;
    }
    m68000.BusCycle();
    if (m68000.GetMemory().ReadWord(address, result)) {
        return true;
    }
    RaiseBusErrorException(m68000, address);
    return false;
}

auto ReadWordNoException(M68000& m68000, uint32_t address, uint32_t& result) {
    if (address & 1u) {
        return false;
    }
    m68000.BusCycle();
    return m68000.GetMemory().ReadWord(address, result);
}

auto ReadLong(M68000& m68000, uint32_t address, uint32_t& result) {
    uint32_t high{}, low{};
    const auto success = ReadWord(m68000, address, high) &&
                         ReadWord(m68000, address + 2u, low);
    result = (high << 16u) + low;
    return success;
}

auto ReadLongNoException(M68000& m68000, uint32_t address, uint32_t& result) {
    uint32_t high{}, low{};
    const auto success = ReadWordNoException(m68000, address, high) &&
                         ReadWordNoException(m68000, address + 2u, low);
    result = (high << 16u) + low;
    return success;
}

auto WriteByte(M68000& m68000, uint32_t address, uint32_t value) {
    m68000.BusCycle();
    if (m68000.GetMemory().WriteByte(address, value)) {
        return true;
    }
    RaiseBusErrorException(m68000, address);
    return false;
}

auto WriteWord(M68000& m68000, uint32_t address, uint32_t value) {
    if (address & 1u) {
        RaiseAddressErrorException(m68000, address);
        return false;
    }
    m68000.BusCycle();
    if (m68000.GetMemory().WriteWord(address, value)) {
        return true;
    }
    RaiseBusErrorException(m68000, address);
    return false;
}

auto WriteWordNoException(M68000& m68000, uint32_t address, uint32_t value) {
    if (address & 1u) {
        return false;
    }
    m68000.BusCycle();
    return m68000.GetMemory().WriteWord(address, value);
}

auto WriteLong(M68000& m68000, uint32_t address, uint32_t value) {
    return WriteWord(m68000, address, value >> 16u) &&
           WriteWord(m68000, address + 2u, value);
}

// Stack access

auto PopWord(M68000& m68000, uint32_t& v) -> bool {
    const auto sp = m68000.ReadSP();
    m68000.WriteSP(sp + 2u);
    return ReadWord(m68000, sp, v);
}

auto PopLong(M68000& m68000, uint32_t& v) -> bool {
    uint32_t hi{}, lo{};
    if (PopWord(m68000, hi) && PopWord(m68000, lo)) {
        v = (hi << 16u) + lo;
        return true;
    }
    return false;
}

auto PushWord(M68000& m68000, uint32_t v) -> bool {
    // TODO don't know if the stack pointer is written back before or after writing to memory
    const auto sp = m68000.ReadSP() - 2u;
    m68000.WriteSP(sp);
    return WriteWord(m68000, sp, v);
}

auto PushWordNoException(M68000& m68000, uint32_t v) -> bool {
    // TODO don't know if the stack pointer is written back before or after writing to memory
    const auto sp = m68000.ReadSP() - 2u;
    m68000.WriteSP(sp);
    return WriteWordNoException(m68000, sp, v);
}

auto PushLong(M68000& m68000, uint32_t v) -> bool {
    return PushWord(m68000, v) &&
           PushWord(m68000, v >> 16u);
}

auto PushLongNoException(M68000& m68000, uint32_t v) {
    return PushWordNoException(m68000, v) &&
           PushWordNoException(m68000, v >> 16u);
}

auto PushGroup0ExceptionStackFrame(
    M68000& m68000,
    uint32_t pc,
    uint32_t sr,
    uint32_t ird,
    uint32_t address,
    uint32_t status) {
    return PushLongNoException(m68000, pc) &&
           PushWordNoException(m68000, sr) &&
           PushWordNoException(m68000, ird) &&
           PushLongNoException(m68000, address) &&
           PushWordNoException(m68000, status);
}

auto PushGroup1And2ExceptionStackFrame(M68000& m68000, uint32_t pc, uint32_t sr) {
    return PushLong(m68000, pc) &&
           PushWord(m68000, sr);
}

// Prefetch

auto ExecutePrefetchCycle(M68000& m68000) {
    const auto pc = m68000.ReadPC();
    uint32_t ir{};
    if (ReadWord(m68000, pc + 4u, ir)) {
        m68000.WriteIRC(ir);
        m68000.WritePC(pc + 2u);
        return true;
    }
    return false;
}

auto ExecuteFinalPrefetchCycle(M68000& m68000) {
    const auto ir = m68000.ReadIRC();
    if (ExecutePrefetchCycle(m68000)) {
        m68000.WriteIRD(ir);
        return true;
    }
    return false;
}

// Control flow change

auto JumpNoException(M68000& m68000, uint32_t target) {
    m68000.WritePC(target);
    uint32_t ird, irc;
    if (!ReadWordNoException(m68000, target, ird)) {
        return false;
    }
    m68000.WriteIRD(ird);
    if (!ReadWordNoException(m68000, target + 2u, irc)) {
        return false;
    }
    m68000.WriteIRC(irc);
    return true;
}

auto Jump(M68000& m68000, uint32_t target) {
    m68000.WritePC(target);
    uint32_t ird, irc;
    if (!ReadWord(m68000, target, ird)) {
        return false;
    }
    m68000.WriteIRD(ird);
    if (!ReadWord(m68000, target + 2u, irc)) {
        return false;
    }
    m68000.WriteIRC(irc);
    return true;
}

auto JumpSubroutine(M68000& m68000, uint32_t returnAddress, uint32_t target) {
    m68000.WritePC(target);
    uint32_t ird, irc;
    if (!ReadWord(m68000, target, ird)) {
        return false;
    }
    m68000.WriteIRD(ird);
    if (!PushLong(m68000, returnAddress)) {
        return false;
    }
    if (!ReadWord(m68000, target + 2u, irc)) {
        return false;
    }
    m68000.WriteIRC(irc);
    return true;
}

// Exception handling

auto EnterExceptionSupervisorMode(M68000& m68000) {
    const auto sr = m68000.ReadSR();
    m68000.WriteFlagT(false);
    m68000.WriteFlagS(true);
    return sr;
}

auto JumpToExceptionVector(M68000& m68000, uint32_t vector) {
    uint32_t pc{};
    if (!ReadLong(m68000, vector, pc)) {
        return false;
    }
    m68000.InternalCycle();
    return Jump(m68000, pc);
}

auto JumpToExceptionVectorNoException(M68000& m68000, uint32_t vector) {
    uint32_t pc{};
    if (!ReadLongNoException(m68000, vector, pc)) {
        return false;
    }
    m68000.InternalCycle();
    return JumpNoException(m68000, pc);
}


auto RaiseGroup0Exception(M68000& m68000, uint32_t vector, uint32_t address) {
    const auto sr = EnterExceptionSupervisorMode(m68000);
    const auto pc = m68000.ReadPC();
    const auto ird = m68000.ReadIRD();
    const uint32_t status{}; // TODO
    if (!PushGroup0ExceptionStackFrame(m68000, pc, sr, ird, address, status)) {
        m68000.WriteHalted(true);
        return;
    }
    if (!JumpToExceptionVectorNoException(m68000, vector)) {
        m68000.WriteHalted(true);
        return;
    }
}

auto RaiseGroup1And2Exception(M68000& m68000, uint32_t vector) {
    const auto sr = EnterExceptionSupervisorMode(m68000);
    const auto pc = m68000.ReadPC();
    if (!PushGroup1And2ExceptionStackFrame(m68000, pc, sr)) {
        return;
    }
    if (!JumpToExceptionVector(m68000, vector)) {
        return;
    }
}

auto RaiseBusErrorException(M68000& m68000, uint32_t address) -> void {
    RaiseGroup0Exception(m68000, VECTOR_BUS_ERROR, address);
}

auto RaiseAddressErrorException(M68000& m68000, uint32_t address) -> void {
    RaiseGroup0Exception(m68000, VECTOR_ADDRESS_ERROR, address);
}

auto RaiseIllegalInstructionException(M68000& m68000) {
    RaiseGroup1And2Exception(m68000, VECTOR_ILLEGAL_INSTRUCTION);
}

auto RaiseZeroDivideException(M68000& m68000) {
    m68000.ElapseCycles(4u);
    RaiseGroup1And2Exception(m68000, VECTOR_ZERO_DIVIDE);
}

auto RaiseChkException(M68000& m68000) {
    // Note: There's a 6 cycle disagreement between the UM and yacht.txt
    m68000.ElapseCycles(10u);
    RaiseGroup1And2Exception(m68000, VECTOR_CHK_INSTRUCTION);
}

auto RaiseTrapvException(M68000& m68000) {
    RaiseGroup1And2Exception(m68000, VECTOR_TRAPV_INSTRUCTION);
}

auto RaisePrivilegeViolationException(M68000& m68000) {
    m68000.ElapseCycles(4u);
    RaiseGroup1And2Exception(m68000, VECTOR_PRIVILEGE_VIOLATION);
}

auto RaiseLineEmulatorException(M68000& m68000, uint32_t vector) {
    const auto sr = EnterExceptionSupervisorMode(m68000);
    const auto pc = m68000.ReadPC() - 2u;
    if (!PushGroup1And2ExceptionStackFrame(m68000, pc, sr)) {
        return;
    }
    if (!JumpToExceptionVector(m68000, vector)) {
        return;
    }
}

auto RaiseLineAEmulatorException(M68000& m68000) {
    RaiseLineEmulatorException(m68000, VECTOR_LINE_1010_EMULATOR);
}

auto RaiseLineFEmulatorException(M68000& m68000) {
    RaiseLineEmulatorException(m68000, VECTOR_LINE_1111_EMULATOR);
}

auto RaiseTrapException(M68000& m68000, uint32_t vector) {
    m68000.ElapseCycles(4u);
    m68000.WritePC(m68000.ReadPC() + 2u);
    RaiseGroup1And2Exception(m68000, VECTOR_TRAP_BASE + (vector << 2u));
}

auto RaiseInterruptException(M68000& m68000, uint32_t level) {
    if (m68000.ReadHalted()) [[unlikely]] {
        return;
    }
    // Note: This isn't entirely correct, yacht states the cycles are interleaved with
    // pushing the stack frame
    m68000.ElapseCycles(14u);
    const auto sr = EnterExceptionSupervisorMode(m68000);
    const auto pc = m68000.ReadPC();
    const auto vector = GetInterruptVector(m68000, level);
    m68000.WriteInterruptPriorityMask(level);
    if (!PushGroup1And2ExceptionStackFrame(m68000, pc, sr)) {
        return;
    }
    if (!JumpToExceptionVector(m68000, (vector & 0xFFu) << 2u)) {
        return;
    }
    m68000.WriteStopped(false);
}

auto RaiseResetException(M68000& m68000) -> void {
    EnterExceptionSupervisorMode(m68000);
    m68000.WriteInterruptPriorityMask(7u);
    uint32_t sp{};
    if (!ReadLong(m68000, VECTOR_RESET_STACK_POINTER, sp)) {
        return;
    }
    m68000.WriteSP(sp);
    if (JumpToExceptionVector(m68000, VECTOR_RESET_PROGRAM_COUNTER)) {
        return;
    }
    m68000.WriteHalted(false);
}

auto CheckInterrupts(M68000& m68000, uint32_t oldLevel, uint32_t newLevel) {
    const auto mask = m68000.ReadInterruptPriorityMask();
    const auto nmi = oldLevel < 7u && newLevel == 7u;
    const auto irq = newLevel > mask;
    if (nmi || irq) {
        RaiseInterruptException(m68000, newLevel);
    }
}

// Condition code evaluation

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

auto TestCondition(M68000& m68000, uint32_t condition) -> bool {
    return TestConditionWithLookup(m68000.ReadCCR() & 0xFu, condition & 0xFu);
}

// Standard handler for an illegal instruction

auto ExecuteIllegal(M68000& m68000) {
    ExecuteFinalPrefetchCycle(m68000);
    RaiseIllegalInstructionException(m68000);
}

// Alu and address mode support tags

struct Byte {
};
struct Word {
};
struct Long {
};

// Alu support functions

template<typename T>
constexpr auto SignExtend(uint32_t v) {
    if constexpr(std::is_same_v<T, Byte>) {
        return SignExtend8(v);
    }
    if constexpr(std::is_same_v<T, Word>) {
        return SignExtend16(v);
    }
    return v;
}

template<typename T>
constexpr auto GetAluFlagShift() {
    if constexpr(std::is_same_v<T, Byte>) {
        return 24u;
    }
    if constexpr(std::is_same_v<T, Word>) {
        return 16u;
    }
    return 0u;
}

template<typename T>
auto WriteFlagX(M68000& m68000, uint32_t v) {
    m68000.WriteFlagX(v << GetAluFlagShift<T>());
}

template<typename T>
auto WriteFlagN(M68000& m68000, uint32_t v) {
    m68000.WriteFlagN(v << GetAluFlagShift<T>());
}

template<typename T>
auto WriteFlagZ(M68000& m68000, uint32_t v) {
    m68000.WriteFlagZ(v << GetAluFlagShift<T>());
}

template<typename T>
auto WriteFlagV(M68000& m68000, uint32_t v) {
    m68000.WriteFlagV(v << GetAluFlagShift<T>());
}

template<typename T>
auto WriteFlagC(M68000& m68000, uint32_t v) {
    m68000.WriteFlagC(v << GetAluFlagShift<T>());
}

template<typename T>
auto WriteFlagsLogical(M68000& m68000, uint32_t result) -> void {
    WriteFlagN<T>(m68000, result);
    WriteFlagZ<T>(m68000, result);
    WriteFlagV<T>(m68000, 0u);
    WriteFlagC<T>(m68000, 0u);
}

auto WriteFlagsDivisionOverflow(M68000& m68000) -> void {
    WriteFlagV<Word>(m68000, 0x8000u);
    WriteFlagC<Word>(m68000, 0x0000u);
}

template<typename T>
auto WriteFlagsArithmetic(M68000& m68000, uint32_t result, uint32_t overflow, uint32_t carry) -> void {
    WriteFlagX<T>(m68000, carry);
    WriteFlagN<T>(m68000, result);
    WriteFlagZ<T>(m68000, result);
    WriteFlagV<T>(m68000, overflow);
    WriteFlagC<T>(m68000, carry);
}

template<typename T>
auto WriteFlagsMultiprecision(M68000& m68000, uint32_t result, uint32_t overflow, uint32_t carry) -> void {
    WriteFlagX<T>(m68000, carry);
    WriteFlagN<T>(m68000, result);
    if (m68000.ReadFlagZ()) {
        WriteFlagZ<T>(m68000, result);
    }
    WriteFlagV<T>(m68000, overflow);
    WriteFlagC<T>(m68000, carry);
}

auto ReadFlagXBit(const M68000& m68000) {
    return m68000.ReadFlagX() ? 1u : 0u;
}

constexpr auto OverflowAdd(uint32_t src, uint32_t dst, uint32_t result) -> uint32_t {
    return ~(dst ^ src) & (dst ^ result);
}

constexpr auto OverflowSub(uint32_t src, uint32_t dst, uint32_t result) -> uint32_t {
    return (dst ^ src) & (dst ^ result);
}

constexpr auto Carry(uint32_t src, uint32_t dst, uint32_t result, uint32_t overflow) -> uint32_t {
    return (dst ^ src) ^ result ^ overflow;
}

constexpr auto CarryAdd(uint32_t src, uint32_t dst, uint32_t result) -> uint32_t {
    return Carry(src, dst, result, OverflowAdd(src, dst, result));
}

constexpr auto CarrySub(uint32_t src, uint32_t dst, uint32_t result) -> uint32_t {
    return Carry(src, dst, result, OverflowSub(src, dst, result));
}

// Alu operations

template<typename T>
struct Add {
    auto operator()(M68000& m68000, uint32_t src, uint32_t dst) {
        const auto result = dst + src;
        const auto overflow = OverflowAdd(src, dst, result);
        const auto carry = Carry(src, dst, result, overflow);
        WriteFlagsArithmetic<T>(m68000, result, overflow, carry);
        return result;
    }
};

template<typename T>
struct Sub {
    auto operator()(M68000& m68000, uint32_t src, uint32_t dst) {
        const auto result = dst - src;
        const auto overflow = OverflowSub(src, dst, result);
        const auto carry = Carry(src, dst, result, overflow);
        WriteFlagsArithmetic<T>(m68000, result, overflow, carry);
        return result;
    }
};

template<typename T>
struct Cmp {
    auto operator()(M68000& m68000, uint32_t src, uint32_t dst) {
        const auto result = dst - src;
        const auto overflow = OverflowSub(src, dst, result);
        const auto carry = Carry(src, dst, result, overflow);
        WriteFlagN<T>(m68000, result);
        WriteFlagZ<T>(m68000, result);
        WriteFlagV<T>(m68000, overflow);
        WriteFlagC<T>(m68000, carry);
        return 0u;
    }
};

template<typename T>
struct Or {
    auto operator()(M68000& m68000, uint32_t src, uint32_t dst) {
        const auto result = src | dst;
        WriteFlagsLogical<T>(m68000, result);
        return result;
    }
};

template<typename T>
struct And {
    auto operator()(M68000& m68000, uint32_t src, uint32_t dst) {
        const auto result = dst & src;
        WriteFlagsLogical<T>(m68000, result);
        return result;
    }
};

template<typename T>
struct Eor {
    auto operator()(M68000& m68000, uint32_t src, uint32_t dst) {
        const auto result = dst ^ src;
        WriteFlagsLogical<T>(m68000, result);
        return result;
    }
};

template<typename T>
struct Mulu {
    auto operator()(M68000& m68000, uint32_t src, uint32_t dst) {
        m68000.ElapseCycles(34u + 2u * PopCount16(src));
        const auto result = Truncate16(dst) * Truncate16(src);
        WriteFlagsLogical<T>(m68000, result);
        return result;
    }
};

template<typename T>
struct Muls {
    auto operator()(M68000& m68000, uint32_t src, uint32_t dst) {
        m68000.ElapseCycles(34u + 2u * PopCount16(src ^ (src << 1u)));
        const auto result = SignExtend16(dst) * SignExtend16(src);
        WriteFlagsLogical<T>(m68000, result);
        return result;
    }
};

// Multiprecision: ADDX, SUBX, ABCD, SBCD

template<typename T>
struct Addx {
    auto operator()(M68000& m68000, uint32_t src, uint32_t dst) {
        const auto result = dst + src + ReadFlagXBit(m68000);
        const auto overflow = OverflowAdd(src, dst, result);
        const auto carry = Carry(src, dst, result, overflow);
        WriteFlagsMultiprecision<T>(m68000, result, overflow, carry);
        return result;
    }
};

template<typename T>
struct Subx {
    auto operator()(M68000& m68000, uint32_t src, uint32_t dst) {
        const auto result = dst - src - ReadFlagXBit(m68000);
        const auto overflow = OverflowSub(src, dst, result);
        const auto carry = Carry(src, dst, result, overflow);
        WriteFlagsMultiprecision<T>(m68000, result, overflow, carry);
        return result;
    }
};

template<typename T>
struct Abcd {

    constexpr static auto CARRY_MASK = 0x88888888u;
    constexpr static auto ADJUSTMENT = 0x66666666u;

    static auto ComputeCorrection(uint32_t carry) {
        return (carry & CARRY_MASK) - ((carry & CARRY_MASK) >> 2u);
    }

    static auto ComputeCorrection(uint32_t sum, uint32_t carry) {
        return ComputeCorrection(carry | CarryAdd(sum, ADJUSTMENT, sum + ADJUSTMENT));
    }

    auto operator()(M68000& m68000, uint32_t src, uint32_t dst) {
        // Compute Binary Sum, Binary Carry
        const auto bs = dst + src + ReadFlagXBit(m68000);
        const auto bc = CarryAdd(src, dst, bs);
        // Add the Decimal Correction factor to the Binary Sum
        const auto dc = ComputeCorrection(bs, bc);
        const auto result = bs + dc;
        const auto overflow = OverflowAdd(bs, dc, result);
        const auto carry = Carry(bs, dc, overflow, result);
        WriteFlagsMultiprecision<T>(m68000, result, overflow, carry | bc);
        return result;
    }
};

template<typename T>
struct Sbcd {

    constexpr static auto CARRY_MASK = 0x88888888u;

    static auto ComputeCorrection(uint32_t carry) {
        return (carry & CARRY_MASK) - ((carry & CARRY_MASK) >> 2u);
    }

    auto operator()(M68000& m68000, uint32_t src, uint32_t dst) {
        // Compute Binary Difference, Binary Carry
        const auto bd = dst - src - ReadFlagXBit(m68000);
        const auto bc = CarrySub(src, dst, bd);
        // Subtract the Decimal Correction from the Binary Difference
        const auto dc = Sbcd::ComputeCorrection(bc);
        const auto result = bd - dc;
        const auto overflow = OverflowSub(dc, bd, result);
        const auto carry = Carry(dc, bd, result, overflow);
        WriteFlagsMultiprecision<T>(m68000, result, overflow, carry | bc);
        return result;
    }
};


// Alu address register operations: ADDA, SUBA

template<typename T>
struct Adda {
    auto operator()(M68000& m68000, uint32_t src, uint32_t dst) {
        return dst + SignExtend<T>(src);
    }
};

template<typename T>
struct Suba {
    auto operator()(M68000& m68000, uint32_t src, uint32_t dst) {
        return dst - SignExtend<T>(src);
    }
};

template<typename T>
struct Cmpa {
    auto operator()(M68000& m68000, uint32_t src, uint32_t dst) {
        const auto extended = SignExtend<T>(src);
        const auto result = dst - extended;
        const auto overflow = (dst ^ extended) & (dst ^ result);
        const auto carry = (dst ^ extended) ^ result ^ overflow;
        WriteFlagN<Long>(m68000, result);
        WriteFlagZ<Long>(m68000, result);
        WriteFlagV<Long>(m68000, overflow);
        WriteFlagC<Long>(m68000, carry);
        return 0u;
    }
};

// Bitwise operations: BTST, BCHG, BCLR and BSET

template<typename T>
constexpr auto GetBitForSize(uint32_t n) {
    if constexpr(std::is_same_v<T, Long>) {
        return n & 0x1Fu;
    }
    return n & 0x7u;
}

template<typename T>
struct Btst {
    auto operator()(M68000& m68000, uint32_t n, uint32_t dst) {
        const auto bit = GetBitForSize<T>(n);
        const auto mask = 1u << bit;
        const auto test = dst & mask;
        WriteFlagZ<T>(m68000, test);
        return 0u;
    }
};

template<typename T>
struct Bchg {
    auto operator()(M68000& m68000, uint32_t n, uint32_t dst) {
        const auto bit = GetBitForSize<T>(n);
        const auto mask = 1u << bit;
        const auto test = dst & mask;
        const auto result = dst ^ mask;
        WriteFlagZ<T>(m68000, test);
        return result;
    }
};

template<typename T>
struct Bclr {
    auto operator()(M68000& m68000, uint32_t n, uint32_t dst) {
        const auto bit = GetBitForSize<T>(n);
        const auto mask = 1u << bit;
        const auto test = dst & mask;
        const auto result = dst & ~mask;
        WriteFlagZ<T>(m68000, test);
        return result;
    }
};

template<typename T>
struct Bset {
    auto operator()(M68000& m68000, uint32_t n, uint32_t dst) {
        const auto bit = GetBitForSize<T>(n);
        const auto mask = 1u << bit;
        const auto test = dst & mask;
        const auto result = dst | mask;
        WriteFlagZ<T>(m68000, test);
        return result;
    }
};

// Shift rotate operations: ASR, LSR, ROXR, ROR, ASL, ASL, ROXL and ROL

template<typename T>
consteval auto GetMaxShift() {
    if constexpr(std::is_same_v<T, Byte>) {
        return 8u;
    }
    if constexpr(std::is_same_v<T, Word>) {
        return 16u;
    }
    return 32u;
}

template<typename T>
consteval auto GetShiftBitMask() {
    if constexpr(std::is_same_v<T, Byte>) {
        return 0xFFu;
    }
    if constexpr(std::is_same_v<T, Word>) {
        return 0xFFFFu;
    }
    return 0xFFFFFFFFu;
}

template<typename T>
consteval auto GetShiftMostSignificantBit() {
    if constexpr(std::is_same_v<T, Byte>) {
        return 0x80u;
    }
    if constexpr(std::is_same_v<T, Word>) {
        return 0x8000u;
    }
    return 0x80000000u;
}

template<typename T>
struct Asr {
    constexpr static auto MAX_SHIFT = GetMaxShift<T>() - 1u;
    constexpr static auto MASK = GetShiftBitMask<T>();
    constexpr static auto MSB = GetShiftMostSignificantBit<T>();

    static auto Shift(uint32_t shift, uint32_t v) {
        const auto s = (shift < MAX_SHIFT) ? shift : MAX_SHIFT;
        const auto logical = (v & MASK) >> s;
        const auto msb = MSB >> s;
        return (logical ^ msb) - msb;
    }

    static auto Carry(uint32_t shift, uint32_t v) {
        return shift ? Shift(shift - 1u, v) << MAX_SHIFT : 0u;
    }

    auto operator()(M68000& m68000, uint32_t shift, uint32_t v) {
        const auto result = Shift(shift, v);
        const auto carry = Carry(shift, v);
        if (shift) {
            WriteFlagX<T>(m68000, carry);
        }
        WriteFlagN<T>(m68000, result);
        WriteFlagZ<T>(m68000, result);
        WriteFlagV<T>(m68000, 0u);
        WriteFlagC<T>(m68000, carry);
        return result;
    }
};


template<typename T>
struct Lsr {
    constexpr static auto MAX_SHIFT = GetMaxShift<T>();
    constexpr static auto MASK = GetShiftBitMask<T>();

    static auto Shift(uint32_t shift, uint32_t v) {
        return (shift < MAX_SHIFT) ? (v & MASK) >> shift : 0u;
    }

    static auto Carry(uint32_t shift, uint32_t v) {
        return shift ? Shift(shift - 1, v) << (MAX_SHIFT - 1u) : 0u;
    }

    auto operator()(M68000& m68000, uint32_t shift, uint32_t v) {
        const auto result = Shift(shift, v);
        const auto carry = Carry(shift, v);
        if (shift) {
            WriteFlagX<T>(m68000, carry);
        }
        WriteFlagN<T>(m68000, result);
        WriteFlagZ<T>(m68000, result);
        WriteFlagV<T>(m68000, 0u);
        WriteFlagC<T>(m68000, carry);
        return result;
    }
};

template<typename T>
struct Roxr {
    constexpr static auto MAX_SHIFT = GetMaxShift<T>();
    constexpr static auto MASK = GetShiftBitMask<T>();

    static auto Rotate(uint32_t shift, uint32_t x, uint32_t v) {
        const auto s = shift % (MAX_SHIFT + 1u);
        if (s) {
            return ((v & MASK) >> 1u >> (s - 1u)) +
                   (x << (MAX_SHIFT - s)) +
                   (v << 1u << (MAX_SHIFT - s));
        }
        return v;
    }

    static auto Carry(uint32_t shift, uint32_t x, uint32_t v) {
        return (shift ? Rotate(shift - 1u, x, v) : x) << (MAX_SHIFT - 1u);
    }

    auto operator()(M68000& m68000, uint32_t shift, uint32_t v) {
        const auto x = m68000.ReadFlagX() ? 1u : 0u;
        const auto result = Rotate(shift, x, v);
        const auto carry = Carry(shift, x, v);
        if (shift) {
            WriteFlagX<T>(m68000, carry);
        }
        WriteFlagN<T>(m68000, result);
        WriteFlagZ<T>(m68000, result);
        WriteFlagV<T>(m68000, 0u);
        WriteFlagC<T>(m68000, carry);
        return result;
    }
};

template<typename T>
struct Ror {
    constexpr static auto MAX_SHIFT = GetMaxShift<T>();
    constexpr static auto MASK = GetShiftBitMask<T>();

    static auto Rotate(uint32_t shift, uint32_t v) {
        const auto s = shift & (MAX_SHIFT - 1u);
        if (s) {
            return ((v & MASK) >> s) + (v << (MAX_SHIFT - s));
        }
        return v;
    }

    static auto Carry(uint32_t shift, uint32_t v) {
        return shift ? Rotate(shift - 1u, v) << (MAX_SHIFT - 1u) : 0u;
    }

    auto operator()(M68000& m68000, uint32_t shift, uint32_t v) {
        const auto result = Rotate(shift, v);
        const auto carry = Carry(shift, v);
        WriteFlagN<T>(m68000, result);
        WriteFlagZ<T>(m68000, result);
        WriteFlagV<T>(m68000, 0u);
        WriteFlagC<T>(m68000, carry);
        return result;
    }
};

template<typename T>
struct Asl {
    constexpr static auto MAX_SHIFT = GetMaxShift<T>();
    constexpr static auto MASK = GetShiftBitMask<T>();
    constexpr static auto MSB = GetShiftMostSignificantBit<T>();

    static auto Shift(uint32_t shift, uint32_t v) {
        return (shift < MAX_SHIFT) ? v << shift : 0u;
    }

    static auto Carry(uint32_t shift, uint32_t v) {
        return shift ? Shift(shift - 1u, v) : 0u;
    }

    static auto Overflow(uint32_t shift, uint32_t v) {
        if (shift) {
            const auto s = (shift < MAX_SHIFT) ? shift : MAX_SHIFT;
            const auto changes = v ^ (v << 1u);
            const auto usedChanges = (changes & MASK) >> (MAX_SHIFT - s);
            return usedChanges ? MSB : 0u;
        }
        return 0u;
    }

    auto operator()(M68000& m68000, uint32_t shift, uint32_t v) {
        const auto result = Shift(shift, v);
        const auto carry = Carry(shift, v);
        const auto overflow = Overflow(shift, v);
        if (shift) {
            WriteFlagX<T>(m68000, carry);
        }
        WriteFlagN<T>(m68000, result);
        WriteFlagZ<T>(m68000, result);
        WriteFlagV<T>(m68000, overflow);
        WriteFlagC<T>(m68000, carry);
        return result;
    }
};

template<typename T>
struct Lsl {
    constexpr static auto MAX_SHIFT = GetMaxShift<T>();

    static auto Shift(uint32_t shift, uint32_t v) {
        return (shift < MAX_SHIFT) ? v << shift : 0u;
    }

    static auto Carry(uint32_t shift, uint32_t v) {
        return shift ? Shift(shift - 1, v) : 0u;
    }

    auto operator()(M68000& m68000, uint32_t shift, uint32_t v) {
        const auto result = Shift(shift, v);
        const auto carry = Carry(shift, v);
        if (shift) {
            WriteFlagX<T>(m68000, carry);
        }
        WriteFlagN<T>(m68000, result);
        WriteFlagZ<T>(m68000, result);
        WriteFlagV<T>(m68000, 0u);
        WriteFlagC<T>(m68000, carry);
        return result;
    }
};

template<typename T>
struct Roxl {
    constexpr static auto MAX_SHIFT = GetMaxShift<T>();
    constexpr static auto MASK = GetShiftBitMask<T>();

    static auto Rotate(uint32_t shift, uint32_t x, uint32_t v) {
        const auto s = shift % (MAX_SHIFT + 1u);
        if (s) {
            return (v << 1u << (s - 1u)) +
                   (x << (s - 1u)) +
                   ((v & MASK) >> 1u >> (MAX_SHIFT - s));
        }
        return v;
    }

    static auto Carry(uint32_t shift, uint32_t x, uint32_t v) {
        return shift ? Rotate(shift - 1u, x, v) : x << (MAX_SHIFT - 1u);
    }

    auto operator()(M68000& m68000, uint32_t shift, uint32_t v) {
        const auto x = m68000.ReadFlagX() ? 1u : 0u;
        const auto result = Rotate(shift, x, v);
        const auto carry = Carry(shift, x, v);
        if (shift) {
            WriteFlagX<T>(m68000, carry);
        }
        WriteFlagN<T>(m68000, result);
        WriteFlagZ<T>(m68000, result);
        WriteFlagV<T>(m68000, 0u);
        WriteFlagC<T>(m68000, carry);
        return result;
    }
};

template<typename T>
struct Rol {
    constexpr static auto MAX_SHIFT = GetMaxShift<T>();
    constexpr static auto MASK = GetShiftBitMask<T>();

    static auto Rotate(uint32_t shift, uint32_t v) {
        const auto s = shift & (MAX_SHIFT - 1u);
        if (s) {
            return (v << s) + ((v & MASK) >> (MAX_SHIFT - s));
        }
        return v;
    }

    static auto Carry(uint32_t shift, uint32_t v) {
        return shift ? Rotate(shift - 1u, v) : 0u;
    }

    auto operator()(M68000& m68000, uint32_t shift, uint32_t v) {
        const auto result = Rotate(shift, v);
        const auto carry = Carry(shift, v);
        WriteFlagN<T>(m68000, result);
        WriteFlagZ<T>(m68000, result);
        WriteFlagV<T>(m68000, 0u);
        WriteFlagC<T>(m68000, carry);
        return result;
    }
};

// Single operand: NEGX, CLR, NEG, NOT, NBCD, TST, MOVE FROM SR, SCC

template<typename T>
struct Negx {
    auto operator()(M68000& m68000, uint32_t dst) {
        const auto result = 0u - dst - ReadFlagXBit(m68000);
        const auto overflow = dst & result;
        const auto carry = dst ^ result ^ overflow;
        WriteFlagsMultiprecision<T>(m68000, result, overflow, carry);
        return result;
    }
};

template<typename T>
struct Clr {
    auto operator()(M68000& m68000, uint32_t) {
        const uint32_t result{};
        WriteFlagsLogical<T>(m68000, result);
        return result;
    }
};

template<typename T>
struct Neg {
    auto operator()(M68000& m68000, uint32_t dst) {
        const auto result = 0u - dst;
        const auto overflow = dst & result;
        const auto carry = dst ^ result ^ overflow;
        WriteFlagsArithmetic<T>(m68000, result, overflow, carry);
        return result;
    }
};

template<typename T>
struct Not {
    auto operator()(M68000& m68000, uint32_t dst) {
        const auto result = ~dst;
        WriteFlagsLogical<T>(m68000, result);
        return result;
    }
};

template<typename T>
struct Nbcd {
    constexpr static auto CARRY_MASK = 0x88888888u;

    static auto ComputeCorrection(uint32_t carry) {
        return (carry & CARRY_MASK) - ((carry & CARRY_MASK) >> 2u);
    }

    auto operator()(M68000& m68000, uint32_t dst) {
        // Compute Binary Difference (bd), Binary Carry (bc) and Decimal Correction (dc)
        const auto bd = 0u - dst - ReadFlagXBit(m68000);
        const auto bc = dst ^ bd ^ (dst & bd);
        const auto dc = ComputeCorrection(bc);
        // The result is formed by subtracting the Decimal Correction (dc)
        // from the Binary Difference (bd)
        const auto result = bd - dc;
        const auto overflow = OverflowSub(dc, bd, result);
        const auto carry = Carry(dc, bd, result, overflow);
        // Update flags (carry is or-ed with the binary carry)
        WriteFlagsMultiprecision<T>(m68000, result, overflow, carry | bc);
        return result;
    }
};

template<typename T>
struct Tst {
    auto operator()(M68000& m68000, uint32_t dst) {
        const auto result = dst;
        WriteFlagsLogical<T>(m68000, result);
        return result;
    }
};

template<typename T>
struct MoveFromSR {
    auto operator()(M68000& m68000, uint32_t) {
        return m68000.ReadSR();
    }
};

template<typename T>
struct TasD {
    // Similar work around to SccD
    auto operator()(M68000& m68000, uint32_t dst) {
        const uint32_t result = 0x80u | dst;
        WriteFlagsLogical<T>(m68000, dst);
        return result;
    }
};

template<typename T>
struct Tas {
    auto operator()(M68000& m68000, uint32_t dst) {
        const uint32_t result = 0x80u | dst;
        WriteFlagsLogical<T>(m68000, dst);
        m68000.InternalCycle();
        return result;
    }
};

// TODO: this is a workaround for different timings when addressing a data register
template<typename T>
struct SccD {
    constexpr static auto MASK = GetShiftBitMask<T>();

    auto operator()(M68000& m68000, uint32_t opcode, uint32_t) {
        if (TestCondition(m68000, OpcodeConditionCode(opcode))) {
            m68000.InternalCycle();
            return MASK;
        }
        return 0u;
    }
};

template<typename T>
struct Scc {
    constexpr static auto MASK = GetShiftBitMask<T>();

    auto operator()(M68000& m68000, uint32_t opcode, uint32_t) {
        if (TestCondition(m68000, OpcodeConditionCode(opcode))) {
            return MASK;
        }
        return 0u;
    }
};

// Quick instructions: ADDQ, SUBQ

template<typename T>
struct Addq {
    auto operator()(M68000& m68000, uint32_t opcode, uint32_t dst) {
        // TODO: potentially refactor this so both structs rely on a shared method
        return Add<T>()(m68000, OpcodeQuick(opcode), dst);
    }
};

template<typename T>
struct Subq {
    auto operator()(M68000& m68000, uint32_t opcode, uint32_t dst) {
        // TODO: potentially refactor this so both structs rely on a shared method
        return Sub<T>()(m68000, OpcodeQuick(opcode), dst);
    }
};

// Move instructions: MOVE, MOVEA

template<typename T>
struct Move {
    auto operator()(M68000& m68000, uint32_t dst) {
        const auto result = dst;
        WriteFlagsLogical<T>(m68000, result);
        return result;
    }
};

template<typename T>
struct Movea {
    auto operator()(M68000& m68000, uint32_t dst) {
        const auto result = SignExtend<T>(dst);
        return result;
    }
};

// Miscellaneous operations: ORI {SR|CCR}, ANDI {SR|CCR}, EORI {SR|CCR}

struct OrSR {
    auto operator()(uint32_t src, uint32_t dst) {
        return dst | src;
    }
};

struct AndSR {
    auto operator()(uint32_t src, uint32_t dst) {
        return dst & src;
    }
};

struct EorSR {
    auto operator()(uint32_t src, uint32_t dst) {
        return dst ^ src;
    }
};

// Effective address support functions

auto ComputeDisplacement(uint16_t displacement) {
    return SignExtend16(displacement);
}

auto ComputeIndexFromExtensionWord(M68000& m68000, uint32_t extension) {
    const auto re = ExtensionWordRegister(extension);
    const auto r = ExtensionWordAddress(extension) ?
                   m68000.ReadAddressRegisterLong(re) :
                   m68000.ReadDataRegisterLong(re);
    const auto index = ExtensionWordLong(extension) ? r : SignExtend16(r);
    const auto displacement = ExtensionWordDisplacement(extension);
    return index + SignExtend8(displacement);
}

auto ComputeShort(uint32_t word) {
    return SignExtend16(word);
}

// Branch instructions: BRA, BSR, Bcc, Dbcc

auto GetBranchDisplacementAndSize(const M68000& m68000, uint32_t opcode, uint32_t& displacement, uint32_t& size) {
    const auto byteDisplacement = OpcodeBranchDisplacement(opcode);
    if (byteDisplacement != 0u) {
        displacement = byteDisplacement;
        size = 2u;
        return;
    }
    const auto irc = m68000.ReadIRC();
    displacement = ComputeDisplacement(irc);
    size = 4u;
}

auto ExecuteBranchSubroutine(M68000& m68000, uint32_t opcode) {
    // Note: We follow the convention presented in yacht.txt
    m68000.InternalCycle();
    uint32_t displacement, size;
    GetBranchDisplacementAndSize(m68000, opcode, displacement, size);
    const auto pc = m68000.ReadPC();
    if (!PushLong(m68000, pc + size)) {
        return;
    }
    m68000.WritePC(pc + displacement - 2u);
    if (!ExecutePrefetchCycle(m68000)) {
        return;
    }
    ExecuteFinalPrefetchCycle(m68000);
}

auto ExecuteBranchTaken(M68000& m68000, uint32_t opcode) {
    // Note: We follow the convention presented in yacht.txt
    m68000.InternalCycle();
    uint32_t displacement, size;
    GetBranchDisplacementAndSize(m68000, opcode, displacement, size);
    const auto pc = m68000.ReadPC();
    m68000.WritePC(pc + displacement - 2u);
    if (!ExecutePrefetchCycle(m68000)) {
        return;
    }
    ExecuteFinalPrefetchCycle(m68000);
}


auto ExecuteBranchNotTaken(M68000& m68000, uint32_t opcode) {
    // Note: We follow the convention presented in yacht.txt
    m68000.InternalCycle();
    m68000.InternalCycle();
    const auto byteDisplacement = OpcodeBranchDisplacement(opcode);
    // Bcc.B
    if (byteDisplacement != 0u) {
        ExecuteFinalPrefetchCycle(m68000);
        return;
    }
    // Bcc.W
    if (!ExecutePrefetchCycle(m68000)) {
        return;
    }
    ExecuteFinalPrefetchCycle(m68000);
}

auto ExecuteBcc(M68000& m68000, uint32_t opcode) {
    const auto condition = OpcodeConditionCode(opcode);
    if (condition == CONDITION_CODE_F) {
        ExecuteBranchSubroutine(m68000, opcode);
        return;
    }
    if (TestCondition(m68000, condition)) {
        ExecuteBranchTaken(m68000, opcode);
        return;
    }
    ExecuteBranchNotTaken(m68000, opcode);
}

auto ExecuteDbccConditionTrue(M68000& m68000) {
    // Branch not taken: condition true
    // Note: We follow the convention presented in yacht.txt
    m68000.InternalCycle();
    m68000.InternalCycle();
    if (!ExecutePrefetchCycle(m68000)) {
        return;
    }
    ExecuteFinalPrefetchCycle(m68000);
}

auto ExecuteDbccCounterNotExpired(M68000& m68000) {
    // Branch taken: counter not expired
    // Note: We follow the convention presented in yacht.txt
    m68000.InternalCycle();
    const auto pc = m68000.ReadPC();
    const auto irc = m68000.ReadIRC();
    const auto displacement = ComputeDisplacement(irc);
    m68000.WritePC(pc + displacement - 2u);
    if (!ExecutePrefetchCycle(m68000)) {
        return;
    }
    ExecuteFinalPrefetchCycle(m68000);
}

auto ExecuteDbccCounterExpired(M68000& m68000) {
    // Branch not taken: counter expired
    // Note: We follow the convention presented in yacht.txt
    // TODO. There are two ways I can imagine the extra prefetch works.
    // 1. The MC68000 reads from the same address twice (implemented here)
    // 2. The MC68000 reads from the branch target and then has to fix up the program counter
    // and prefetch queue
    m68000.InternalCycle();
    if (!ExecutePrefetchCycle(m68000)) {
        return;
    }
    m68000.WritePC(m68000.ReadPC() - 2u);
    if (!ExecutePrefetchCycle(m68000)) {
        return;
    }
    ExecuteFinalPrefetchCycle(m68000);
}

auto ExecuteDbcc(M68000& m68000, uint32_t opcode) {
    if (TestCondition(m68000, OpcodeConditionCode(opcode))) {
        // Branch not taken: condition true
        ExecuteDbccConditionTrue(m68000);
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = m68000.ReadDataRegisterLong(ry);
    m68000.WriteDataRegisterWord(ry, y - 1u);
    if (y & 0xFFFFu) {
        // Branch taken: counter not expired
        ExecuteDbccCounterNotExpired(m68000);
        return;
    }
    // Branch not taken: counter expired
    ExecuteDbccCounterExpired(m68000);
}

// Address mode support functions

template<typename T>
constexpr auto AddressRegisterIncrement() -> uint32_t {
    if constexpr(std::is_same_v<T, Word>) {
        return 2u;
    }
    if constexpr(std::is_same_v<T, Long>) {
        return 4u;
    }
    return 0u;
}

template<typename T>
constexpr auto AddressRegisterIncrement(uint32_t r) -> uint32_t {
    if constexpr(std::is_same_v<T, Byte>) {
        return (r == 7u) ? 2u : 1u;
    }
    if constexpr(std::is_same_v<T, Word>) {
        return 2u;
    }
    if constexpr(std::is_same_v<T, Long>) {
        return 4u;
    }
    return 0u;
}

template<typename T>
constexpr auto ReadMemory(M68000& m68000, uint32_t address, uint32_t& result) {
    if constexpr(std::is_same_v<T, Byte>) {
        return ReadByte(m68000, address, result);
    } else if constexpr(std::is_same_v<T, Word>) {
        return ReadWord(m68000, address, result);
    } else if constexpr(std::is_same_v<T, Long>) {
        return ReadLong(m68000, address, result);
    }
    return false;
}

template<typename T>
constexpr auto WriteMemory(M68000& m68000, uint32_t address, uint32_t v) {
    if constexpr(std::is_same_v<T, Byte>) {
        return WriteByte(m68000, address, v);
    } else if constexpr(std::is_same_v<T, Word>) {
        return WriteWord(m68000, address, v);
    } else if constexpr(std::is_same_v<T, Long>) {
        return WriteLong(m68000, address, v);
    }
    return false;
}

template<typename T>
constexpr void WriteDataRegister(M68000& m68000, const uint32_t rx, const uint32_t result) {
    if constexpr(std::is_same_v<T, Byte>) {
        m68000.WriteDataRegisterByte(rx, result);
    } else if constexpr(std::is_same_v<T, Word>) {
        m68000.WriteDataRegisterWord(rx, result);
    } else if constexpr(std::is_same_v<T, Long>) {
        m68000.WriteDataRegisterLong(rx, result);
    }
}

// Effective address calculation

template<typename>
auto EffectiveAddressAddressIndirect(M68000& m68000, uint32_t ry, uint32_t& address) -> bool {
    const auto ay = m68000.ReadAddressRegisterLong(ry);
    address = ay;
    return true;
}

template<typename T>
auto EffectiveAddressAddressIncrement(M68000& m68000, uint32_t ry, uint32_t& address) -> bool {
    const auto ay = m68000.ReadAddressRegisterLong(ry);
    const auto size = AddressRegisterIncrement<T>(ry);
    address = ay;
    m68000.WriteAddressRegisterLong(ry, address + size);
    return true;
}

template<typename T>
auto EffectiveAddressAddressDecrement(M68000& m68000, uint32_t ry, uint32_t& address) -> bool {
    const auto ay = m68000.ReadAddressRegisterLong(ry);
    const auto size = AddressRegisterIncrement<T>(ry);
    address = ay - size;
    m68000.WriteAddressRegisterLong(ry, address);
    return true;
}

template<typename>
auto EffectiveAddressAddressDisplacement(M68000& m68000, uint32_t ry, uint32_t& address) -> bool {
    const auto irc = m68000.ReadIRC();
    if (!ExecutePrefetchCycle(m68000)) {
        return false;
    }
    const auto ay = m68000.ReadAddressRegisterLong(ry);
    const auto displacement = ComputeDisplacement(irc);
    address = ay + displacement;
    return true;
}

template<typename>
auto EffectiveAddressAddressIndex(M68000& m68000, uint32_t ry, uint32_t& address) -> bool {
    const auto irc = m68000.ReadIRC();
    m68000.InternalCycle();
    if (!ExecutePrefetchCycle(m68000)) {
        return false;
    }
    const auto ay = m68000.ReadAddressRegisterLong(ry);
    const auto index = ComputeIndexFromExtensionWord(m68000, irc);
    address = ay + index;
    return true;
}


template<typename>
auto EffectiveAddressShort(M68000& m68000, uint32_t& address) -> bool {
    const auto irc = m68000.ReadIRC();
    if (!ExecutePrefetchCycle(m68000)) {
        return false;
    }
    address = ComputeShort(irc);
    return true;
}

template<typename>
auto EffectiveAddressLong(M68000& m68000, uint32_t& address) -> bool {
    const auto hi = m68000.ReadIRC();
    if (!ExecutePrefetchCycle(m68000)) {
        return false;
    }
    const auto lo = m68000.ReadIRC();
    if (!ExecutePrefetchCycle(m68000)) {
        return false;
    }
    address = (hi << 16u) + lo;
    return true;
}

template<typename>
auto EffectiveAddressPCDisplacement(M68000& m68000, uint32_t& address) -> bool {
    const auto irc = m68000.ReadIRC();
    if (!ExecutePrefetchCycle(m68000)) {
        return false;
    }
    const auto pc = m68000.ReadPC();
    const auto displacement = ComputeDisplacement(irc);
    address = pc + displacement;
    return true;
}

template<typename>
auto EffectiveAddressPCIndex(M68000& m68000, uint32_t& address) -> bool {
    const auto irc = m68000.ReadIRC();
    m68000.InternalCycle();
    if (!ExecutePrefetchCycle(m68000)) {
        return false;
    }
    const auto pc = m68000.ReadPC();
    const auto index = ComputeIndexFromExtensionWord(m68000, irc);
    address = pc + index;
    return true;
}

// Reading from source
// TODO
// There's some overlap here with the effective address calculation
// but these methods existed first and until can either
// a) Test the cycle sequencing or b) comprehensively review with yacht.txt these remain

template<typename T>
auto ReadRegisterFromDataRegister(M68000& m68000, uint32_t ry, uint32_t& value) {
    const auto dy = m68000.ReadDataRegisterLong(ry);
    value = dy;
    return true;
}

template<typename T>
auto ReadRegisterFromAddressRegister(M68000& m68000, uint32_t ry, uint32_t& value) {
    const auto ay = m68000.ReadAddressRegisterLong(ry);
    value = ay;
    return true;
}


template<typename T>
auto ReadMemoryFromAddressIndirect(M68000& m68000, uint32_t ry, uint32_t& address, uint32_t& value) {
    const auto ay = m68000.ReadAddressRegisterLong(ry);
    address = ay;
    return ReadMemory<T>(m68000, address, value);
}

template<typename T>
auto ReadMemoryFromAddressIncrement(M68000& m68000, uint32_t ry, uint32_t& address, uint32_t& value) {
    const auto ay = m68000.ReadAddressRegisterLong(ry);
    const auto size = AddressRegisterIncrement<T>(ry);
    address = ay;
    if (!ReadMemory<T>(m68000, address, value)) {
        return false;
    }
    m68000.WriteAddressRegisterLong(ry, address + size);
    return true;
}

template<typename T>
auto ReadMemoryFromAddressDecrement(M68000& m68000, uint32_t ry, uint32_t& address, uint32_t& value) {
    const auto ay = m68000.ReadAddressRegisterLong(ry);
    const auto size = AddressRegisterIncrement<T>(ry);
    address = ay - size;
    m68000.InternalCycle();
    m68000.WriteAddressRegisterLong(ry, address);
    return ReadMemory<T>(m68000, address, value);
}

template<typename T>
auto ReadMemoryFromAddressDecrementWithoutInternalCycle(M68000& m68000, uint32_t ry, uint32_t& address, uint32_t& value) {
    // Note: as above but used for multiprecision instructions
    const auto ay = m68000.ReadAddressRegisterLong(ry);
    const auto size = AddressRegisterIncrement<T>(ry);
    address = ay - size;
    m68000.WriteAddressRegisterLong(ry, address);
    return ReadMemory<T>(m68000, address, value);
}

template<typename T>
auto ReadMemoryFromAddressDisplacement(M68000& m68000, uint32_t ry, uint32_t& address, uint32_t& value) {
    const auto irc = m68000.ReadIRC();
    if (!ExecutePrefetchCycle(m68000)) {
        return false;
    }
    const auto ay = m68000.ReadAddressRegisterLong(ry);
    const auto displacement = ComputeDisplacement(irc);
    address = ay + displacement;
    return ReadMemory<T>(m68000, address, value);
}

template<typename T>
auto ReadMemoryFromAddressIndex(M68000& m68000, uint32_t ry, uint32_t& address, uint32_t& value) {
    const auto irc = m68000.ReadIRC();
    m68000.InternalCycle();
    if (!ExecutePrefetchCycle(m68000)) {
        return false;
    }
    const auto ay = m68000.ReadAddressRegisterLong(ry);
    const auto index = ComputeIndexFromExtensionWord(m68000, irc);
    address = ay + index;
    return ReadMemory<T>(m68000, address, value);
}


template<typename T>
auto ReadMemoryFromShort(M68000& m68000, uint32_t& address, uint32_t& value) {
    const auto irc = m68000.ReadIRC();
    if (!ExecutePrefetchCycle(m68000)) {
        return false;
    }
    address = ComputeShort(irc);
    return ReadMemory<T>(m68000, address, value);
}

template<typename T>
auto ReadMemoryFromLong(M68000& m68000, uint32_t& address, uint32_t& value) {
    const auto hi = m68000.ReadIRC();
    if (!ExecutePrefetchCycle(m68000)) {
        return false;
    }
    const auto lo = m68000.ReadIRC();
    if (!ExecutePrefetchCycle(m68000)) {
        return false;
    }
    address = (hi << 16u) + lo;
    return ReadMemory<T>(m68000, address, value);
}

template<typename T>
auto ReadMemoryFromPCDisplacement(M68000& m68000, uint32_t& address, uint32_t& value) {
    const auto irc = m68000.ReadIRC();
    if (!ExecutePrefetchCycle(m68000)) {
        return false;
    }
    const auto pc = m68000.ReadPC();
    const auto displacement = ComputeDisplacement(irc);
    address = pc + displacement;
    return ReadMemory<T>(m68000, address, value);
}

template<typename T>
auto ReadMemoryFromPCIndex(M68000& m68000, uint32_t& address, uint32_t& value) {
    const auto irc = m68000.ReadIRC();
    m68000.InternalCycle();
    if (!ExecutePrefetchCycle(m68000)) {
        return false;
    }
    const auto pc = m68000.ReadPC();
    const auto index = ComputeIndexFromExtensionWord(m68000, irc);
    address = pc + index;
    return ReadMemory<T>(m68000, address, value);
}

template<typename T>
constexpr auto ReadImmediate(M68000& m68000, uint32_t& immediate) {
    const auto hi = m68000.ReadIRC();
    if (!ExecutePrefetchCycle(m68000)) {
        return false;
    }
    if constexpr(std::is_same_v<T, Byte> || std::is_same_v<T, Word>) {
        immediate = hi;
        return true;
    }
    const auto lo = m68000.ReadIRC();
    if (!ExecutePrefetchCycle(m68000)) {
        return false;
    }
    immediate = (hi << 16u) + lo;
    return true;
}

// Functors that allow the source reads to be templated

template<typename T>
struct SourceDataRegister {
    auto operator()(M68000& m68000, uint32_t ry, uint32_t&, uint32_t& y) {
        return ReadRegisterFromDataRegister<T>(m68000, ry, y);
    }
};

template<typename T>
struct SourceAddressRegister {
    auto operator()(M68000& m68000, uint32_t ry, uint32_t& address, uint32_t& y) {
        return ReadRegisterFromAddressRegister<T>(m68000, ry, y);
    }
};

template<typename T>
struct SourceAddressIndirect {
    template<typename... Args>
    auto operator()(Args&& ...args) { return ReadMemoryFromAddressIndirect<T>(std::forward<Args>(args)...); }
};

template<typename T>
struct SourceAddressIncrement {
    template<typename... Args>
    auto operator()(Args&& ...args) { return ReadMemoryFromAddressIncrement<T>(std::forward<Args>(args)...); }
};

template<typename T>
struct SourceAddressDecrement {
    template<typename... Args>
    auto operator()(Args&& ...args) { return ReadMemoryFromAddressDecrement<T>(std::forward<Args>(args)...); }
};

template<typename T>
struct SourceAddressDecrementWithoutInternalCycle {
    template<typename... Args>
    auto operator()(Args&& ...args) { return ReadMemoryFromAddressDecrementWithoutInternalCycle<T>(std::forward<Args>(args)...); }
};

template<typename T>
struct SourceAddressDisplacement {
    template<typename... Args>
    auto operator()(Args&& ...args) { return ReadMemoryFromAddressDisplacement<T>(std::forward<Args>(args)...); }
};

template<typename T>
struct SourceAddressIndex {
    template<typename... Args>
    auto operator()(Args&& ...args) { return ReadMemoryFromAddressIndex<T>(std::forward<Args>(args)...); }
};

template<typename T>
struct SourceShort {
    auto operator()(M68000& m68000, uint32_t, uint32_t& address, uint32_t& y) {
        return ReadMemoryFromShort<T>(m68000, address, y);
    }
};

template<typename T>
struct SourceLong {
    auto operator()(M68000& m68000, uint32_t, uint32_t& address, uint32_t& y) {
        return ReadMemoryFromLong<T>(m68000, address, y);
    }
};

template<typename T>
struct SourcePCDisplacement {
    auto operator()(M68000& m68000, uint32_t, uint32_t& address, uint32_t& y) {
        return ReadMemoryFromPCDisplacement<T>(m68000, address, y);
    }
};


template<typename T>
struct SourcePCIndex {
    auto operator()(M68000& m68000, uint32_t, uint32_t& address, uint32_t& y) {
        return ReadMemoryFromPCIndex<T>(m68000, address, y);
    }
};

template<typename T>
struct SourceImmediate {
    auto operator()(M68000& m68000, uint32_t, uint32_t&, uint32_t& y) {
        return ReadImmediate<T>(m68000, y);
    }
};

// Control-mode instructions

namespace {

auto ControlModeAddressIndirect(M68000& m68000, uint32_t opcode) -> uint32_t {
    const auto ry = OpcodeRegisterY(opcode);
    const auto ay = m68000.ReadAddressRegisterLong(ry);
    return ay;
}

auto ControlModeAddressDisplacement(M68000& m68000, uint32_t opcode) -> uint32_t {
    const auto ry = OpcodeRegisterY(opcode);
    const auto ay = m68000.ReadAddressRegisterLong(ry);
    const auto irc = m68000.ReadIRC();
    const auto displacement = ComputeDisplacement(irc);
    return ay + displacement;
}

auto ControlModeAddressIndex(M68000& m68000, uint32_t opcode) -> uint32_t {
    const auto ry = OpcodeRegisterY(opcode);
    const auto ay = m68000.ReadAddressRegisterLong(ry);
    const auto irc = m68000.ReadIRC();
    const auto index = ComputeIndexFromExtensionWord(m68000, irc);
    return ay + index;
}

auto ControlModeShort(M68000& m68000) -> uint32_t {
    const auto irc = m68000.ReadIRC();
    return ComputeShort(irc);
}

auto ControlModeLong(M68000& m68000, uint32_t& address) -> bool {
    const auto hi = m68000.ReadIRC();
    if (!ExecutePrefetchCycle(m68000)) {
        return false;
    }
    const auto lo = m68000.ReadIRC();
    address = (hi << 16u) + lo;
    return true;
}

auto ControlModePCDisplacement(M68000& m68000) -> uint32_t {
    const auto pc = m68000.ReadPC();
    const auto irc = m68000.ReadIRC();
    const auto displacement = ComputeDisplacement(irc);
    return pc + 2u + displacement;
}

auto ControlModePCIndex(M68000& m68000) -> uint32_t {
    const auto pc = m68000.ReadPC();
    const auto irc = m68000.ReadIRC();
    const auto index = ComputeIndexFromExtensionWord(m68000, irc);
    return pc + 2u + index;
}

// JMP

auto ExecuteJmpAddressIndirect(M68000& m68000, uint32_t opcode) -> void {
    Jump(m68000, ControlModeAddressIndirect(m68000, opcode));
}

auto ExecuteJmpAddressDisplacement(M68000& m68000, uint32_t opcode) -> void {
    const auto effectiveAddress = ControlModeAddressDisplacement(m68000, opcode);
    m68000.InternalCycle();
    Jump(m68000, effectiveAddress);
}

auto ExecuteJmpAddressIndex(M68000& m68000, uint32_t opcode) -> void {
    const auto effectiveAddress = ControlModeAddressIndex(m68000, opcode);
    m68000.ElapseCycles(6u);
    Jump(m68000, effectiveAddress);
}

auto ExecuteJmpShort(M68000& m68000) -> void {
    const auto effectiveAddress = ControlModeShort(m68000);
    m68000.InternalCycle();
    Jump(m68000, effectiveAddress);
}

auto ExecuteJmpLong(M68000& m68000) -> void {
    uint32_t effectiveAddress;
    if (!ControlModeLong(m68000, effectiveAddress)) {
        return;
    }
    Jump(m68000, effectiveAddress);
}

auto ExecuteJmpPCDisplacement(M68000& m68000) -> void {
    const auto effectiveAddress = ControlModePCDisplacement(m68000);
    m68000.InternalCycle();
    Jump(m68000, effectiveAddress);
}

auto ExecuteJmpPCIndex(M68000& m68000) -> void {
    const auto effectiveAddress = ControlModePCIndex(m68000);
    m68000.ElapseCycles(6u);
    Jump(m68000, effectiveAddress);
}

// JSR

auto ExecuteJsrAddressIndirect(M68000& m68000, uint32_t opcode) -> void {
    JumpSubroutine(m68000, m68000.ReadPC() + 2u, ControlModeAddressIndirect(m68000, opcode));
}

auto ExecuteJsrAddressDisplacement(M68000& m68000, uint32_t opcode) -> void {
    const auto effectiveAddress = ControlModeAddressDisplacement(m68000, opcode);
    m68000.InternalCycle();
    JumpSubroutine(m68000, m68000.ReadPC() + 4u, effectiveAddress);
}

auto ExecuteJsrAddressIndex(M68000& m68000, uint32_t opcode) -> void {
    const auto effectiveAddress = ControlModeAddressIndex(m68000, opcode);
    m68000.ElapseCycles(6u);
    JumpSubroutine(m68000, m68000.ReadPC() + 4u, effectiveAddress);
}

auto ExecuteJsrShort(M68000& m68000) -> void {
    const auto effectiveAddress = ControlModeShort(m68000);
    m68000.InternalCycle();
    JumpSubroutine(m68000, m68000.ReadPC() + 4u, effectiveAddress);
}

auto ExecuteJsrLong(M68000& m68000) -> void {
    uint32_t effectiveAddress;
    if (!ControlModeLong(m68000, effectiveAddress)) {
        return;
    }
    JumpSubroutine(m68000, m68000.ReadPC() + 4u, effectiveAddress);
}

auto ExecuteJsrPCDisplacement(M68000& m68000) -> void {
    const auto effectiveAddress = ControlModePCDisplacement(m68000);
    m68000.InternalCycle();
    JumpSubroutine(m68000, m68000.ReadPC() + 4u, effectiveAddress);
}

auto ExecuteJsrPCIndex(M68000& m68000) -> void {
    const auto effectiveAddress = ControlModePCIndex(m68000);
    m68000.ElapseCycles(6u);
    JumpSubroutine(m68000, m68000.ReadPC() + 4u, effectiveAddress);
}

// LEA

auto ExecuteLeaAddressIndirect(M68000& m68000, uint32_t opcode) -> void {
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto rx = OpcodeRegisterX(opcode);
    const auto effectiveAddress = ControlModeAddressIndirect(m68000, opcode);
    m68000.WriteAddressRegisterLong(rx, effectiveAddress);
}

auto ExecuteLeaAddressDisplacement(M68000& m68000, uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t effectiveAddress;
    if (!EffectiveAddressAddressDisplacement<Long>(m68000, ry, effectiveAddress)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto rx = OpcodeRegisterX(opcode);
    m68000.WriteAddressRegisterLong(rx, effectiveAddress);
}

auto ExecuteLeaAddressIndex(M68000& m68000, uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t effectiveAddress;
    if (!EffectiveAddressAddressIndex<Long>(m68000, ry, effectiveAddress)) {
        return;
    }
    m68000.InternalCycle();
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto rx = OpcodeRegisterX(opcode);
    m68000.WriteAddressRegisterLong(rx, effectiveAddress);
}

auto ExecuteLeaShort(M68000& m68000, uint32_t opcode) -> void {
    uint32_t effectiveAddress;
    if (!EffectiveAddressShort<Long>(m68000, effectiveAddress)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto rx = OpcodeRegisterX(opcode);
    m68000.WriteAddressRegisterLong(rx, effectiveAddress);
}

auto ExecuteLeaLong(M68000& m68000, uint32_t opcode) -> void {
    uint32_t effectiveAddress;
    if (!EffectiveAddressLong<Long>(m68000, effectiveAddress)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto rx = OpcodeRegisterX(opcode);
    m68000.WriteAddressRegisterLong(rx, effectiveAddress);
}

auto ExecuteLeaPCDisplacement(M68000& m68000, uint32_t opcode) -> void {
    uint32_t effectiveAddress;
    if (!EffectiveAddressPCDisplacement<Long>(m68000, effectiveAddress)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto rx = OpcodeRegisterX(opcode);
    m68000.WriteAddressRegisterLong(rx, effectiveAddress);
}

auto ExecuteLeaPCIndex(M68000& m68000, uint32_t opcode) -> void {
    uint32_t effectiveAddress;
    if (!EffectiveAddressPCIndex<Long>(m68000, effectiveAddress)) {
        return;
    }
    m68000.InternalCycle();
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto rx = OpcodeRegisterX(opcode);
    m68000.WriteAddressRegisterLong(rx, effectiveAddress);
}

// PEA

auto ExecutePeaAddressIndirect(M68000& m68000, uint32_t opcode) -> void {
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto effectiveAddress = ControlModeAddressIndirect(m68000, opcode);
    PushLong(m68000, effectiveAddress);
}

auto ExecutePeaAddressDisplacement(M68000& m68000, uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t effectiveAddress;
    if (!EffectiveAddressAddressDisplacement<Long>(m68000, ry, effectiveAddress)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    PushLong(m68000, effectiveAddress);
}

auto ExecutePeaAddressIndex(M68000& m68000, uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t effectiveAddress;
    if (!EffectiveAddressAddressIndex<Long>(m68000, ry, effectiveAddress)) {
        return;
    }
    m68000.InternalCycle();
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    PushLong(m68000, effectiveAddress);
}

auto ExecutePeaShort(M68000& m68000, uint32_t opcode) -> void {
    uint32_t effectiveAddress;
    if (!EffectiveAddressShort<Long>(m68000, effectiveAddress)) {
        return;
    }
    if (!PushLong(m68000, effectiveAddress)) {
        return;
    }
    ExecuteFinalPrefetchCycle(m68000);
}

auto ExecutePeaLong(M68000& m68000, uint32_t opcode) -> void {
    uint32_t effectiveAddress;
    if (!EffectiveAddressLong<Long>(m68000, effectiveAddress)) {
        return;
    }
    if (!PushLong(m68000, effectiveAddress)) {
        return;
    }
    ExecuteFinalPrefetchCycle(m68000);
}

auto ExecutePeaPCDisplacement(M68000& m68000, uint32_t opcode) -> void {
    uint32_t effectiveAddress;
    if (!EffectiveAddressPCDisplacement<Long>(m68000, effectiveAddress)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    PushLong(m68000, effectiveAddress);
}

auto ExecutePeaPCIndex(M68000& m68000, uint32_t opcode) -> void {
    uint32_t effectiveAddress;
    if (!EffectiveAddressPCIndex<Long>(m68000, effectiveAddress)) {
        return;
    }
    m68000.InternalCycle();
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    PushLong(m68000, effectiveAddress);
}

// Movem memory to register

template<typename T>
auto MoveMemoryToRegisters(M68000& m68000, uint32_t list, uint32_t& address) -> bool {
    const auto bitset = std::bitset<16>(list);
    uint32_t value;
    for (auto i = 0u; i < 16u; ++i) {
        if (bitset[i]) {
            if (!ReadMemory<T>(m68000, address, value)) {
                return false;
            }
            const auto extended = SignExtend<T>(value);
            if (i < 8u) {
                m68000.WriteDataRegisterLong(i, extended);
            } else {
                m68000.WriteAddressRegisterLong(i - 8u, extended);
            }
            address += AddressRegisterIncrement<T>();
        }
    }
    return ReadMemory<Word>(m68000, address, value);
}

template<typename T>
auto ExecuteMovemAddressIndirectToRegister(M68000& m68000, uint32_t opcode) -> void {
    const auto list = m68000.ReadIRC();
    if (!ExecutePrefetchCycle(m68000)) {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address;
    if (!EffectiveAddressAddressIndirect<Long>(m68000, ry, address)) {
        return;
    }
    if (!MoveMemoryToRegisters<T>(m68000, list, address)) {
        return;
    }
    ExecuteFinalPrefetchCycle(m68000);
}

template<typename T>
auto ExecuteMovemAddressIncrementToRegister(M68000& m68000, uint32_t opcode) -> void {
    const auto list = m68000.ReadIRC();
    if (!ExecutePrefetchCycle(m68000)) {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address;
    if (!EffectiveAddressAddressIndirect<Long>(m68000, ry, address)) {
        return;
    }
    if (!MoveMemoryToRegisters<T>(m68000, list, address)) {
        return;
    }
    m68000.WriteAddressRegisterLong(ry, address);
    ExecuteFinalPrefetchCycle(m68000);
}

template<typename T>
auto ExecuteMovemAddressDisplacementToRegister(M68000& m68000, uint32_t opcode) -> void {
    const auto list = m68000.ReadIRC();
    if (!ExecutePrefetchCycle(m68000)) {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address;
    if (!EffectiveAddressAddressDisplacement<Long>(m68000, ry, address)) {
        return;
    }
    if (!MoveMemoryToRegisters<T>(m68000, list, address)) {
        return;
    }
    ExecuteFinalPrefetchCycle(m68000);
}

template<typename T>
auto ExecuteMovemAddressIndexToRegister(M68000& m68000, uint32_t opcode) -> void {
    const auto list = m68000.ReadIRC();
    if (!ExecutePrefetchCycle(m68000)) {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address;
    if (!EffectiveAddressAddressIndex<Long>(m68000, ry, address)) {
        return;
    }
    if (!MoveMemoryToRegisters<T>(m68000, list, address)) {
        return;
    }
    ExecuteFinalPrefetchCycle(m68000);
}

template<typename T>
auto ExecuteMovemShortToRegister(M68000& m68000) -> void {
    const auto list = m68000.ReadIRC();
    if (!ExecutePrefetchCycle(m68000)) {
        return;
    }
    uint32_t address;
    if (!EffectiveAddressShort<Long>(m68000, address)) {
        return;
    }
    if (!MoveMemoryToRegisters<T>(m68000, list, address)) {
        return;
    }
    ExecuteFinalPrefetchCycle(m68000);
}

template<typename T>
auto ExecuteMovemLongToRegister(M68000& m68000) -> void {
    const auto list = m68000.ReadIRC();
    if (!ExecutePrefetchCycle(m68000)) {
        return;
    }
    uint32_t address;
    if (!EffectiveAddressLong<Long>(m68000, address)) {
        return;
    }
    if (!MoveMemoryToRegisters<T>(m68000, list, address)) {
        return;
    }
    ExecuteFinalPrefetchCycle(m68000);
}

template<typename T>
auto ExecuteMovemPCDisplacementToRegister(M68000& m68000) -> void {
    const auto list = m68000.ReadIRC();
    if (!ExecutePrefetchCycle(m68000)) {
        return;
    }
    uint32_t address;
    if (!EffectiveAddressPCDisplacement<Long>(m68000, address)) {
        return;
    }
    if (!MoveMemoryToRegisters<T>(m68000, list, address)) {
        return;
    }
    ExecuteFinalPrefetchCycle(m68000);
}

template<typename T>
auto ExecuteMovemPCIndexToRegister(M68000& m68000) -> void {
    const auto list = m68000.ReadIRC();
    if (!ExecutePrefetchCycle(m68000)) {
        return;
    }
    uint32_t address;
    if (!EffectiveAddressPCIndex<Long>(m68000, address)) {
        return;
    }
    if (!MoveMemoryToRegisters<T>(m68000, list, address)) {
        return;
    }
    ExecuteFinalPrefetchCycle(m68000);
}

// Movem register to memory

template<typename T>
auto MoveRegistersToMemory(M68000& m68000, uint32_t list, uint32_t address) -> bool {
    const auto bitset = std::bitset<16>(list);
    for (auto i = 0u; i < 16u; ++i) {
        if (bitset[i]) {
            const auto value = (i < 8) ?
                               m68000.ReadDataRegisterLong(i) :
                               m68000.ReadAddressRegisterLong(i - 8u);
            if (!WriteMemory<T>(m68000, address, value)) {
                return false;
            }
            address += AddressRegisterIncrement<T>();
        }
    }
    return true;
}

template<typename T>
auto MoveRegistersToMemoryDecrement(M68000& m68000, uint32_t list, uint32_t& address) -> bool {
    const auto bitset = std::bitset<16>(list);
    for (auto i = 0u; i < 16u; ++i) {
        if (bitset[i]) {
            address -= AddressRegisterIncrement<T>();
            const auto value = (i < 8) ?
                               m68000.ReadAddressRegisterLong(7u - i) :
                               m68000.ReadDataRegisterLong(15u - i);
            if (!WriteMemory<T>(m68000, address, value)) {
                return false;
            }
        }
    }
    return true;
}

template<typename T>
auto ExecuteMovemAddressIndirectToMemory(M68000& m68000, uint32_t opcode) -> void {
    const auto list = m68000.ReadIRC();
    if (!ExecutePrefetchCycle(m68000)) {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address;
    if (!EffectiveAddressAddressIndirect<Long>(m68000, ry, address)) {
        return;
    }
    if (!MoveRegistersToMemory<T>(m68000, list, address)) {
        return;
    }
    ExecuteFinalPrefetchCycle(m68000);
}

template<typename T>
auto ExecuteMovemAddressDecrementToMemory(M68000& m68000, uint32_t opcode) -> void {
    const auto list = m68000.ReadIRC();
    if (!ExecutePrefetchCycle(m68000)) {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address;
    if (!EffectiveAddressAddressIndirect<Long>(m68000, ry, address)) {
        return;
    }
    if (!MoveRegistersToMemoryDecrement<T>(m68000, list, address)) {
        return;
    }
    m68000.WriteAddressRegisterLong(ry, address);
    ExecuteFinalPrefetchCycle(m68000);
}

template<typename T>
auto ExecuteMovemAddressDisplacementToMemory(M68000& m68000, uint32_t opcode) -> void {
    const auto list = m68000.ReadIRC();
    if (!ExecutePrefetchCycle(m68000)) {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address;
    if (!EffectiveAddressAddressDisplacement<Long>(m68000, ry, address)) {
        return;
    }
    if (!MoveRegistersToMemory<T>(m68000, list, address)) {
        return;
    }
    ExecuteFinalPrefetchCycle(m68000);
}

template<typename T>
auto ExecuteMovemAddressIndexToMemory(M68000& m68000, uint32_t opcode) -> void {
    const auto list = m68000.ReadIRC();
    if (!ExecutePrefetchCycle(m68000)) {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address;
    if (!EffectiveAddressAddressIndex<Long>(m68000, ry, address)) {
        return;
    }
    if (!MoveRegistersToMemory<T>(m68000, list, address)) {
        return;
    }
    ExecuteFinalPrefetchCycle(m68000);
}

template<typename T>
auto ExecuteMovemShortToMemory(M68000& m68000) -> void {
    const auto list = m68000.ReadIRC();
    if (!ExecutePrefetchCycle(m68000)) {
        return;
    }
    uint32_t address;
    if (!EffectiveAddressShort<Long>(m68000, address)) {
        return;
    }
    if (!MoveRegistersToMemory<T>(m68000, list, address)) {
        return;
    }
    ExecuteFinalPrefetchCycle(m68000);
}

template<typename T>
auto ExecuteMovemLongToMemory(M68000& m68000) -> void {
    const auto list = m68000.ReadIRC();
    if (!ExecutePrefetchCycle(m68000)) {
        return;
    }
    uint32_t address;
    if (!EffectiveAddressLong<Long>(m68000, address)) {
        return;
    }
    if (!MoveRegistersToMemory<T>(m68000, list, address)) {
        return;
    }
    ExecuteFinalPrefetchCycle(m68000);
}

// MOVE USP

auto ExecuteMoveUspToUsp(M68000& m68000, uint32_t opcode) {
    if (!m68000.ReadFlagS()) {
        RaisePrivilegeViolationException(m68000);
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = m68000.ReadAddressRegisterLong(ry);
    m68000.WriteUSP(y);
}

auto ExecuteMoveUspToRegister(M68000& m68000, uint32_t opcode) {
    if (!m68000.ReadFlagS()) {
        RaisePrivilegeViolationException(m68000);
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    m68000.WriteAddressRegisterLong(ry, m68000.ReadUSP());
}

// NOP

auto ExecuteNop(M68000& m68000) -> void {
    ExecuteFinalPrefetchCycle(m68000);
}

// STOP

auto ExecuteStop(M68000& m68000) -> void {
    if (!m68000.ReadFlagS()) {
        RaisePrivilegeViolationException(m68000);
        return;
    }
    m68000.InternalCycle();
    m68000.InternalCycle();
    m68000.WriteSR(m68000.ReadIRC());
    m68000.WritePC(m68000.ReadPC() + 4u);
    m68000.WriteStopped(true);
}

// RTS

auto ExecuteRts(M68000& m68000) -> void {
    uint32_t target{};
    if (!PopLong(m68000, target)) {
        return;
    }
    Jump(m68000, target);
}

// RTR

auto ExecuteRtr(M68000& m68000) -> void {
    uint32_t ccr, target{};
    if (!PopWord(m68000, ccr)) {
        return;
    }
    if (!PopLong(m68000, target)) {
        return;
    }
    m68000.WriteCCR(ccr);
    Jump(m68000, target);
}

// RTE

auto ExecuteRte(M68000& m68000) -> void {
    if (!m68000.ReadFlagS()) {
        RaisePrivilegeViolationException(m68000);
        return;
    }
    uint32_t sr, target{};
    if (!PopWord(m68000, sr)) {
        return;
    }
    if (!PopLong(m68000, target)) {
        return;
    }
    m68000.WriteSR(sr);
    Jump(m68000, target);
}

// RESET

auto ExecuteReset(M68000& m68000) -> void {
    if (!m68000.ReadFlagS()) {
        RaisePrivilegeViolationException(m68000);
        return;
    }
    m68000.InternalCycle();
    m68000.InternalCycle();
    m68000.ResetExternalDevices();
    m68000.ElapseCycles(124u);
    ExecuteFinalPrefetchCycle(m68000);
}

// TRAP

auto ExecuteTrap(M68000& m68000, uint32_t opcode) -> void {
    RaiseTrapException(m68000, OpcodeTrapVector(opcode));
}


// TRAPV

auto ExecuteTrapv(M68000& m68000) -> void {
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    if (!m68000.ReadFlagV()) {
        return;
    }
    RaiseTrapvException(m68000);
}

// LINK

auto ExecuteLink(M68000& m68000, uint32_t opcode) -> void {
    const auto irc = m68000.ReadIRC();
    if (!ExecutePrefetchCycle(m68000)) {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = m68000.ReadAddressRegisterLong(ry);
    if (!PushLong(m68000, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto sp = m68000.ReadSP();
    m68000.WriteAddressRegisterLong(ry, sp);
    m68000.WriteSP(sp + ComputeDisplacement(irc));
}

// UNLK

auto ExecuteUnlk(M68000& m68000, uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    const auto sp = m68000.ReadAddressRegisterLong(ry);
    m68000.WriteSP(sp);
    uint32_t y{};
    if (!PopLong(m68000, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    m68000.WriteAddressRegisterLong(ry, y);
}

// EXT.{W|L} Dy

template<typename T>
auto Ext(uint32_t v) -> uint32_t {
    if constexpr(std::is_same_v<T, Word>) {
        return SignExtend8(v);
    }
    if constexpr(std::is_same_v<T, Long>) {
        return SignExtend16(v);
    }
    return v;
}

template<typename T>
auto ExecuteExtToDataRegister(M68000& m68000, uint32_t opcode) -> void {
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = m68000.ReadDataRegisterLong(ry);
    const auto result = Ext<T>(y);
    WriteFlagsLogical<T>(m68000, result);
    WriteDataRegister<T>(m68000, ry, result);
}

// EXG Dx, Dy
// EXG Ax, Ay
// EXF Dy, Ay

auto ExecuteExgDataRegisterWithDataRegister(M68000& m68000, uint32_t opcode) -> void {
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    m68000.InternalCycle();
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    auto x = m68000.ReadDataRegisterLong(rx);
    auto y = m68000.ReadDataRegisterLong(ry);
    std::swap(x, y);
    m68000.WriteDataRegisterLong(rx, x);
    m68000.WriteDataRegisterLong(ry, y);
}

auto ExecuteExgAddressRegisterWithAddressRegister(M68000& m68000, uint32_t opcode) -> void {
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    m68000.InternalCycle();
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    auto x = m68000.ReadAddressRegisterLong(rx);
    auto y = m68000.ReadAddressRegisterLong(ry);
    std::swap(x, y);
    m68000.WriteAddressRegisterLong(rx, x);
    m68000.WriteAddressRegisterLong(ry, y);
}

auto ExecuteExgDataRegisterWithAddressRegister(M68000& m68000, uint32_t opcode) -> void {
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    m68000.InternalCycle();
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    auto x = m68000.ReadDataRegisterLong(rx);
    auto y = m68000.ReadAddressRegisterLong(ry);
    std::swap(x, y);
    m68000.WriteDataRegisterLong(rx, x);
    m68000.WriteAddressRegisterLong(ry, y);
}

// SWAP Dy

auto ExecuteSwapToDataRegister(M68000& m68000, uint32_t opcode) -> void {
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = m68000.ReadDataRegisterLong(ry);
    const auto result = (y << 16u) + Truncate16(y >> 16u);
    WriteFlagsLogical<Long>(m68000, result);
    m68000.WriteDataRegisterLong(ry, result);
}

// MOVEQ #imm, Dx

auto ExecuteMoveqToDataRegister(M68000& m68000, uint32_t opcode) {
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto rx = OpcodeRegisterX(opcode);
    const auto result = OpcodeBranchDisplacement(opcode);
    WriteFlagsLogical<Long>(m68000, result);
    m68000.WriteDataRegisterLong(rx, result);
}

// MOVEP.{W|L} Dx, (d, Ay)

auto ExecuteMovepToAddressDisplacementWord(M68000& m68000, uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = m68000.ReadDataRegisterLong(rx);
    uint32_t effectiveAddress{};
    if (!EffectiveAddressAddressDisplacement<Long>(m68000, ry, effectiveAddress)) [[unlikely]] {
        return;
    }
    if (!WriteByte(m68000, effectiveAddress, x >> 8u)) [[unlikely]] {
        return;
    }
    if (!WriteByte(m68000, effectiveAddress + 2, x)) [[unlikely]] {
        return;
    }
    ExecuteFinalPrefetchCycle(m68000);
}

auto ExecuteMovepToAddressDisplacementLong(M68000& m68000, uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = m68000.ReadDataRegisterLong(rx);
    uint32_t effectiveAddress{};
    if (!EffectiveAddressAddressDisplacement<Long>(m68000, ry, effectiveAddress)) [[unlikely]] {
        return;
    }
    if (!WriteByte(m68000, effectiveAddress, x >> 24u)) [[unlikely]] {
        return;
    }
    if (!WriteByte(m68000, effectiveAddress + 2, x >> 16u)) [[unlikely]] {
        return;
    }
    if (!WriteByte(m68000, effectiveAddress + 4, x >> 8u)) [[unlikely]] {
        return;
    }
    if (!WriteByte(m68000, effectiveAddress + 6, x)) [[unlikely]] {
        return;
    }
    ExecuteFinalPrefetchCycle(m68000);
}

// MOVEP.{W|L} (d, Ay), Dx

auto ExecuteMovepToDataRegisterWord(M68000& m68000, uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t effectiveAddress{};
    if (!EffectiveAddressAddressDisplacement<Long>(m68000, ry, effectiveAddress)) [[unlikely]] {
        return;
    }
    uint32_t b1, b0;
    if (!ReadByte(m68000, effectiveAddress, b1)) [[unlikely]] {
        return;
    }
    if (!ReadByte(m68000, effectiveAddress + 2, b0)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) [[unlikely]] {
        return;
    }
    WriteDataRegister<Word>(m68000, rx,
                            ((b1 & 0xFFu) << 8u) +
                            (b0 & 0xFFu));
}

auto ExecuteMovepToDataRegisterLong(M68000& m68000, uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t effectiveAddress{};
    if (!EffectiveAddressAddressDisplacement<Long>(m68000, ry, effectiveAddress)) [[unlikely]] {
        return;
    }
    uint32_t b3, b2, b1, b0;
    if (!ReadByte(m68000, effectiveAddress, b3)) [[unlikely]] {
        return;
    }
    if (!ReadByte(m68000, effectiveAddress + 2, b2)) [[unlikely]] {
        return;
    }
    if (!ReadByte(m68000, effectiveAddress + 4, b1)) [[unlikely]] {
        return;
    }
    if (!ReadByte(m68000, effectiveAddress + 6, b0)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) [[unlikely]] {
        return;
    }
    WriteDataRegister<Long>(m68000, rx,
                            ((b3 & 0xFFu) << 24u) +
                            ((b2 & 0xFFu) << 16u) +
                            ((b1 & 0xFFu) << 8u) +
                            (b0 & 0xFFu));
}


}

// Address mode templates

namespace addressing::standard { // namespace addressing::standard
/*
 * Address modes for ALU operation with a data register as the destination
 *
 */

// {ADD|SUB|OR|AND|CMP}.B <ea>, Dx
// {ADD|SUB|OR|AND|CMP}.W <ea>, Dx
// {ADD|SUB|OR|AND|CMP}.L <ea>, Dx

template<template<typename> typename BinaryOp, template<typename> typename Source, typename T>
auto ExecuteBinaryOpSourceToDataRegister(M68000& m68000, uint32_t opcode) {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = m68000.ReadDataRegisterLong(rx);
    uint32_t address, y;
    if (!Source<T>()(m68000, ry, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = BinaryOp<T>()(m68000, y, x);
    if constexpr(std::is_same_v<BinaryOp<T>, Cmp<T>>) {
        if constexpr(std::is_same_v<T, Long>) {
            m68000.InternalCycle();
        }
        return;
    }
    if constexpr(std::is_same_v<T, Long>) {
        if constexpr(std::is_same_v<Source<T>, SourceDataRegister<T>> ||
                     std::is_same_v<Source<T>, SourceAddressRegister<T>> ||
                     std::is_same_v<Source<T>, SourceImmediate<T>>) {
            WriteDataRegister<T>(m68000, rx, result);
            m68000.InternalCycle();
            m68000.InternalCycle();
            return;
        }
        WriteDataRegister<T>(m68000, rx, result);
        m68000.InternalCycle();
        return;
    }
    WriteDataRegister<T>(m68000, rx, result);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpDataRegisterToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpSourceToDataRegister<BinaryOp, SourceDataRegister, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpAddressRegisterToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpSourceToDataRegister<BinaryOp, SourceAddressRegister, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpAddressIndirectToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpSourceToDataRegister<BinaryOp, SourceAddressIndirect, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpAddressIncrementToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpSourceToDataRegister<BinaryOp, SourceAddressIncrement, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpAddressDecrementToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpSourceToDataRegister<BinaryOp, SourceAddressDecrement, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpAddressDisplacementToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpSourceToDataRegister<BinaryOp, SourceAddressDisplacement, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpAddressIndexToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpSourceToDataRegister<BinaryOp, SourceAddressIndex, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpShortToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpSourceToDataRegister<BinaryOp, SourceShort, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpLongToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpSourceToDataRegister<BinaryOp, SourceLong, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpPCDisplacementToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpSourceToDataRegister<BinaryOp, SourcePCDisplacement, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpPCIndexToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpSourceToDataRegister<BinaryOp, SourcePCIndex, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpImmediateToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpSourceToDataRegister<BinaryOp, SourceImmediate, T>(m68000, opcode);
}

/*
 * Address modes for ALU operation with memory as the destination
 * 
 */

// {EOR}.B Dx, Dy
// {EOR}.W Dx, Dy
// Note: This is special case. Grouped here with the address modes that write to memory
// Since the operands are reversed in comparison to other register destination operations.

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpDataRegisterXToDataRegisterY(M68000& m68000, uint32_t opcode) {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = m68000.ReadDataRegisterLong(rx);
    const auto y = m68000.ReadDataRegisterLong(ry);
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    if constexpr(std::is_same_v<T, Long>) {
        m68000.InternalCycle();
        m68000.InternalCycle();
    }
    const auto result = BinaryOp<T>()(m68000, x, y);
    WriteDataRegister<T>(m68000, ry, result);
}

// {ADD|SUB|OR|AND|EOR}.B Dx, <ea>
// {ADD|SUB|OR|AND|EOR}.W Dx, <ea>
// {ADD|SUB|OR|AND|EOR}.L Dx, <ea>

template<template<typename> typename BinaryOp, template<typename> typename Source, typename T>
auto ExecuteBinaryOpDataRegisterToDestination(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = m68000.ReadDataRegisterLong(rx);
    uint32_t address, y;
    if (!Source<T>()(m68000, ry, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = BinaryOp<T>()(m68000, x, y);
    WriteMemory<T>(m68000, address, result);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpDataRegisterToAddressIndirect(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpDataRegisterToDestination<BinaryOp, SourceAddressIndirect, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpDataRegisterToAddressIncrement(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpDataRegisterToDestination<BinaryOp, SourceAddressIncrement, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpDataRegisterToAddressDecrement(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpDataRegisterToDestination<BinaryOp, SourceAddressDecrement, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpDataRegisterToAddressDisplacement(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpDataRegisterToDestination<BinaryOp, SourceAddressDisplacement, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpDataRegisterToAddressIndex(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpDataRegisterToDestination<BinaryOp, SourceAddressIndex, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpDataRegisterToShort(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpDataRegisterToDestination<BinaryOp, SourceShort, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpDataRegisterToLong(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpDataRegisterToDestination<BinaryOp, SourceLong, T>(m68000, opcode);
}

} // namespace addressing::standard

namespace addressing::multiply {

// {MULU|MULS}.W <ea>, Dx

template<template<typename> typename BinaryOp, template<typename> typename Source, typename T>
auto ExecuteMultiplyOpSourceToDataRegister(M68000& m68000, uint32_t opcode) {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = m68000.ReadDataRegisterLong(rx);
    uint32_t address, y;
    if (!Source<T>()(m68000, ry, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = BinaryOp<Long>()(m68000, y, x);
    WriteDataRegister<Long>(m68000, rx, result);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteMultiplyOpDataRegisterToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteMultiplyOpSourceToDataRegister<BinaryOp, SourceDataRegister, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteMultiplyOpAddressIndirectToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteMultiplyOpSourceToDataRegister<BinaryOp, SourceAddressIndirect, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteMultiplyOpAddressIncrementToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteMultiplyOpSourceToDataRegister<BinaryOp, SourceAddressIncrement, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteMultiplyOpAddressDecrementToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteMultiplyOpSourceToDataRegister<BinaryOp, SourceAddressDecrement, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteMultiplyOpAddressDisplacementToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteMultiplyOpSourceToDataRegister<BinaryOp, SourceAddressDisplacement, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteMultiplyOpAddressIndexToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteMultiplyOpSourceToDataRegister<BinaryOp, SourceAddressIndex, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteMultiplyOpShortToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteMultiplyOpSourceToDataRegister<BinaryOp, SourceShort, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteMultiplyOpLongToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteMultiplyOpSourceToDataRegister<BinaryOp, SourceLong, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteMultiplyOpPCDisplacementToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteMultiplyOpSourceToDataRegister<BinaryOp, SourcePCDisplacement, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteMultiplyOpPCIndexToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteMultiplyOpSourceToDataRegister<BinaryOp, SourcePCIndex, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteMultiplyOpImmediateToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteMultiplyOpSourceToDataRegister<BinaryOp, SourceImmediate, T>(m68000, opcode);
}


} // namespace addressing::multiply

namespace addressing::divide {

// DIVU.W <ea>, Dx

auto DivideUnsignedCycles(uint32_t dividend, uint32_t divisor, uint32_t quotient) -> uint32_t {
    // The zeroes in the quotient took 4 micro-cycles
    // The ones in the quotient took either 2 or 3 micro-cycles
    // We initially assume that the ones took 3 micro-cycles (one cycle less)
    // Then we do the division process and adjust for those that took 2 micro-cycles
    auto microCycles = 15u * 4u - std::popcount(quotient & ~1u);
    const auto alignedDivisor = divisor << 16u;
    for (auto i = 0u; i < 15u; ++i) {
        const auto previous = dividend;
        dividend <<= 1u;
        if (previous & 0x8000'0000u) {
            dividend -= alignedDivisor;
            microCycles -= 1u;
        } else if (dividend >= alignedDivisor) {
            dividend -= alignedDivisor;
        }
    }
    return 2 * microCycles;
}

template<template<typename> typename Source>
auto ExecuteDivideUnsignedOpSourceToDataRegister(M68000& m68000, uint32_t opcode) {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = m68000.ReadDataRegisterLong(rx);
    uint32_t address, y;
    if (!Source<Word>()(m68000, ry, address, y)) {
        return;
    }
    const auto dividend = x;
    const auto divisor = static_cast<uint16_t>(y);
    m68000.ElapseCycles(4u);
    if (divisor == 0u) {
        RaiseZeroDivideException(m68000);
        return;
    }
    const auto quotient = dividend / divisor;
    const auto remainder = dividend % divisor;
    m68000.ElapseCycles(2u);
    if (quotient >= 0x1'0000u) {
        WriteFlagsDivisionOverflow(m68000);
        ExecuteFinalPrefetchCycle(m68000);
        return;
    }
    m68000.ElapseCycles(DivideUnsignedCycles(dividend, divisor, quotient));
    m68000.ElapseCycles(6u);
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = (remainder << 16u) + quotient;
    WriteFlagsLogical<Word>(m68000, quotient);
    WriteDataRegister<Long>(m68000, rx, result);
}

auto ExecuteDivideUnsignedOpDataRegisterToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteDivideUnsignedOpSourceToDataRegister<SourceDataRegister>(m68000, opcode);
}

auto ExecuteDivideUnsignedOpAddressIndirectToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteDivideUnsignedOpSourceToDataRegister<SourceAddressIndirect>(m68000, opcode);
}

auto ExecuteDivideUnsignedOpAddressIncrementToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteDivideUnsignedOpSourceToDataRegister<SourceAddressIncrement>(m68000, opcode);
}

auto ExecuteDivideUnsignedOpAddressDecrementToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteDivideUnsignedOpSourceToDataRegister<SourceAddressDecrement>(m68000, opcode);
}

auto ExecuteDivideUnsignedOpAddressDisplacementToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteDivideUnsignedOpSourceToDataRegister<SourceAddressDisplacement>(m68000, opcode);
}

auto ExecuteDivideUnsignedOpAddressIndexToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteDivideUnsignedOpSourceToDataRegister<SourceAddressIndex>(m68000, opcode);
}

auto ExecuteDivideUnsignedOpShortToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteDivideUnsignedOpSourceToDataRegister<SourceShort>(m68000, opcode);
}

auto ExecuteDivideUnsignedOpLongToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteDivideUnsignedOpSourceToDataRegister<SourceLong>(m68000, opcode);
}

auto ExecuteDivideUnsignedOpPCDisplacementToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteDivideUnsignedOpSourceToDataRegister<SourcePCDisplacement>(m68000, opcode);
}

auto ExecuteDivideUnsignedOpPCIndexToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteDivideUnsignedOpSourceToDataRegister<SourcePCIndex>(m68000, opcode);
}

auto ExecuteDivideUnsignedOpImmediateToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteDivideUnsignedOpSourceToDataRegister<SourceImmediate>(m68000, opcode);
}

// DIVS.W <ea>, Dx

auto DivideSignedCycles(uint32_t quotient) -> uint32_t {
    // The zeroes in the quotient took 4 micro-cycles
    // The ones in the quotient took 3 micro-cycles
    return 2 * (15u * 4u - std::popcount(quotient & ~1u));
}

template<template<typename> typename Source>
auto ExecuteDivideSignedOpSourceToDataRegister(M68000& m68000, uint32_t opcode) {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = m68000.ReadDataRegisterLong(rx);
    uint32_t address, y;
    if (!Source<Word>()(m68000, ry, address, y)) {
        return;
    }
    const auto dividend = x;
    const auto divisor = static_cast<uint16_t>(y);
    m68000.ElapseCycles(4u);
    if (divisor == 0u) {
        RaiseZeroDivideException(m68000);
        return;
    }
    const bool signDividend = dividend & 0x8000'0000u;
    const bool signDivisor = divisor & 0x8000u;
    const auto absoluteDividend = signDividend ? -dividend : dividend;
    const auto absoluteDivisor = static_cast<uint16_t>(signDivisor ? -divisor : divisor);
    const auto absoluteQuotient = absoluteDividend / absoluteDivisor;
    const auto absoluteRemainder = absoluteDividend % absoluteDivisor;
    m68000.ElapseCycles(signDividend ? 10u : 8u);
    if (absoluteQuotient >= 0x1'0000u) {
        WriteFlagsDivisionOverflow(m68000);
        ExecuteFinalPrefetchCycle(m68000);
        return;
    }
    m68000.ElapseCycles(DivideSignedCycles(absoluteQuotient));
    m68000.ElapseCycles(10u);
    m68000.ElapseCycles(signDivisor ? 6u : signDividend ? 8u : 4u);
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto opposingSigns = signDividend ^ signDivisor;
    const auto quotient = static_cast<uint16_t>(opposingSigns ? -absoluteQuotient : absoluteQuotient);
    const auto remainder = static_cast<uint16_t>(signDividend ? -absoluteRemainder : absoluteRemainder);
    const auto positiveOverflow = !opposingSigns && (quotient & 0x8000u);
    const auto negativeOverflow = opposingSigns && (quotient > 0u && quotient < 0x8000u);
    if (positiveOverflow || negativeOverflow) {
        WriteFlagsDivisionOverflow(m68000);
        return;
    }
    const auto result = (remainder << 16u) + quotient;
    WriteFlagsLogical<Word>(m68000, quotient);
    WriteDataRegister<Long>(m68000, rx, result);
}

auto ExecuteDivideSignedOpDataRegisterToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteDivideSignedOpSourceToDataRegister<SourceDataRegister>(m68000, opcode);
}

auto ExecuteDivideSignedOpAddressIndirectToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteDivideSignedOpSourceToDataRegister<SourceAddressIndirect>(m68000, opcode);
}

auto ExecuteDivideSignedOpAddressIncrementToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteDivideSignedOpSourceToDataRegister<SourceAddressIncrement>(m68000, opcode);
}

auto ExecuteDivideSignedOpAddressDecrementToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteDivideSignedOpSourceToDataRegister<SourceAddressDecrement>(m68000, opcode);
}

auto ExecuteDivideSignedOpAddressDisplacementToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteDivideSignedOpSourceToDataRegister<SourceAddressDisplacement>(m68000, opcode);
}

auto ExecuteDivideSignedOpAddressIndexToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteDivideSignedOpSourceToDataRegister<SourceAddressIndex>(m68000, opcode);
}

auto ExecuteDivideSignedOpShortToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteDivideSignedOpSourceToDataRegister<SourceShort>(m68000, opcode);
}

auto ExecuteDivideSignedOpLongToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteDivideSignedOpSourceToDataRegister<SourceLong>(m68000, opcode);
}

auto ExecuteDivideSignedOpPCDisplacementToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteDivideSignedOpSourceToDataRegister<SourcePCDisplacement>(m68000, opcode);
}

auto ExecuteDivideSignedOpPCIndexToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteDivideSignedOpSourceToDataRegister<SourcePCIndex>(m68000, opcode);
}

auto ExecuteDivideSignedOpImmediateToDataRegister(M68000& m68000, uint32_t opcode) {
    ExecuteDivideSignedOpSourceToDataRegister<SourceImmediate>(m68000, opcode);
}


} // namespace addressing::divide

namespace addressing::address {
/*
 * Addressing modes for operations that target an address register
 */

// {ADDA|SUBA|CMPA}.W <ea>, Ax
// {ADDA|SUBA|CMPA}.L <ea>, Ax

template<template<typename> typename BinaryOp, template<typename> typename Source, typename T>
auto ExecuteBinaryOpSourceToAddressRegister(M68000& m68000, uint32_t opcode) {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = m68000.ReadAddressRegisterLong(rx);
    uint32_t address, y;
    if (!Source<T>()(m68000, ry, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = BinaryOp<T>()(m68000, y, x);
    if constexpr(std::is_same_v<BinaryOp<T>, Cmpa<T>>) {
        m68000.InternalCycle();
        return;
    }
    if constexpr(std::is_same_v<T, Word> ||
                 std::is_same_v<Source<T>, SourceDataRegister<T>> ||
                 std::is_same_v<Source<T>, SourceAddressRegister<T>> ||
                 std::is_same_v<Source<T>, SourceImmediate<T>>) {
        m68000.WriteAddressRegisterLong(rx, result);
        m68000.InternalCycle();
        m68000.InternalCycle();
        return;
    }
    m68000.WriteAddressRegisterLong(rx, result);
    m68000.InternalCycle();
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpDataRegisterToAddressRegister(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpSourceToAddressRegister<BinaryOp, SourceDataRegister, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpAddressRegisterToAddressRegister(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpSourceToAddressRegister<BinaryOp, SourceAddressRegister, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpAddressIndirectToAddressRegister(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpSourceToAddressRegister<BinaryOp, SourceAddressIndirect, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpAddressIncrementToAddressRegister(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpSourceToAddressRegister<BinaryOp, SourceAddressIncrement, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpAddressDecrementToAddressRegister(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpSourceToAddressRegister<BinaryOp, SourceAddressDecrement, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpAddressDisplacementToAddressRegister(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpSourceToAddressRegister<BinaryOp, SourceAddressDisplacement, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpAddressIndexToAddressRegister(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpSourceToAddressRegister<BinaryOp, SourceAddressIndex, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpShortToAddressRegister(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpSourceToAddressRegister<BinaryOp, SourceShort, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpLongToAddressRegister(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpSourceToAddressRegister<BinaryOp, SourceLong, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpPCDisplacementToAddressRegister(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpSourceToAddressRegister<BinaryOp, SourcePCDisplacement, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpPCIndexToAddressRegister(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpSourceToAddressRegister<BinaryOp, SourcePCIndex, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpImmediateToAddressRegister(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpSourceToAddressRegister<BinaryOp, SourceImmediate, T>(m68000, opcode);
}

} // namespace addressing::address

namespace addressing::immediate {

/*
 * Address modes for ALU operation with immediate source and memory as the destination
 * 
 */

// {ADDI|SUBI|ORI|ANDI|EORI|CMPI}.B #imm, Dy
// {ADDI|SUBI|ORI|ANDI|EORI|CMPI}.W #imm, Dy
// {ADDI|SUBI|ORI|ANDI|EORI|CMPI}.L #imm, Dy

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpImmediateToDataRegisterY(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document implies that all prefetch cycles are performed before the writes
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = m68000.ReadDataRegisterLong(ry);
    uint32_t x;
    if (!ReadImmediate<T>(m68000, x)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = BinaryOp<T>()(m68000, x, y);
    if constexpr(std::is_same_v<BinaryOp<T>, Cmp<T>>) {
        if constexpr(std::is_same_v<T, Long>) {
            m68000.InternalCycle();
        }
        return;
    }
    if constexpr(std::is_same_v<T, Long>) {
        m68000.InternalCycle();
        m68000.InternalCycle();
    }
    WriteDataRegister<T>(m68000, ry, result);
}

// {BTST|BCHG|BCLR|BSET}.L #imm, Dy

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBitwiseOpImmediateToDataRegisterY(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document implies that all prefetch cycles are performed before the writes
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = m68000.ReadDataRegisterLong(ry);
    uint32_t x;
    if (!ReadImmediate<Word>(m68000, x)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = BinaryOp<T>()(m68000, x, y);
    if constexpr(std::is_same_v<BinaryOp<T>, Btst<T>> ||
                 std::is_same_v<BinaryOp<T>, Bclr<T>>) {
        if constexpr(std::is_same_v<T, Long>) {
            m68000.InternalCycle();
        }
    }
    if constexpr(std::is_same_v<BinaryOp<T>, Btst<T>>) {
        return;
    }
    if constexpr(std::is_same_v<T, Long>) {
        m68000.InternalCycle();
        m68000.InternalCycle();
    }
    WriteDataRegister<T>(m68000, ry, result);
}

// {ADDI|SUBI|ORI|ANDI|EORI|CMPI}.B #imm, <ea>
// {ADDI|SUBI|ORI|ANDI|EORI|CMPI}.W #imm, <ea>
// {ADDI|SUBI|ORI|ANDI|EORI|CMPI}.L #imm, <ea>
// {BTST|BCHG|BCLR}.B #imm, <ea>

template<template<typename> typename BinaryOp, template<typename> typename Source, typename T>
auto ExecuteBinaryOpImmediateToDestination(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document implies that all prefetch cycles are performed before the writes
    uint32_t x;
    if (!ReadImmediate<T>(m68000, x)) {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!Source<T>()(m68000, ry, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = BinaryOp<T>()(m68000, x, y);
    if constexpr(std::is_same_v<BinaryOp<T>, Cmp<T>> ||
                 std::is_same_v<BinaryOp<T>, Btst<T>>) {
        return;
    }
    WriteMemory<T>(m68000, address, result);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpImmediateToAddressIndirect(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpImmediateToDestination<BinaryOp, SourceAddressIndirect, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpImmediateToAddressIncrement(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpImmediateToDestination<BinaryOp, SourceAddressIncrement, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpImmediateToAddressDecrement(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpImmediateToDestination<BinaryOp, SourceAddressDecrement, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpImmediateToAddressDisplacement(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpImmediateToDestination<BinaryOp, SourceAddressDisplacement, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpImmediateToAddressIndex(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpImmediateToDestination<BinaryOp, SourceAddressIndex, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpImmediateToShort(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpImmediateToDestination<BinaryOp, SourceShort, T>(m68000, opcode);
}

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpImmediateToLong(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpImmediateToDestination<BinaryOp, SourceLong, T>(m68000, opcode);
}

// BTST.B #imm, (d, PC)

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpImmediateToPCDisplacement(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpImmediateToDestination<BinaryOp, SourcePCDisplacement, T>(m68000, opcode);
}

// BTST.B #imm, (d, PC, Xn)

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpImmediateToPCIndex(M68000& m68000, uint32_t opcode) {
    ExecuteBinaryOpImmediateToDestination<BinaryOp, SourcePCIndex, T>(m68000, opcode);
}

// {ORI|ANDI|EORI}.B #imm, CCR

template<typename BinaryOp>
auto ExecuteBinaryOpImmediateToCCR(M68000& m68000) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    uint32_t x;
    if (!ReadImmediate<Byte>(m68000, x)) {
        return;
    }
    m68000.InternalCycle();
    m68000.InternalCycle();
    m68000.InternalCycle();
    m68000.InternalCycle();
    // Note: this is guesswork on my behalf
    // The logical to CCR ops perform 3 reads when only 2 would be necessary.
    // My guess is that the first read is repeated, but I would need to verify this in a test.
    m68000.WritePC(m68000.ReadPC() - 2u);
    if (!ExecutePrefetchCycle(m68000)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto y = m68000.ReadCCR();
    const auto result = BinaryOp()(x, y);
    m68000.WriteCCR(result);
}

// {ORI|ANDI|EORI}.B #imm, SR

template<typename BinaryOp>
auto ExecuteBinaryOpImmediateToSR(M68000& m68000) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    if (!m68000.ReadFlagS()) {
        RaisePrivilegeViolationException(m68000);
        return;
    }
    uint32_t x;
    if (!ReadImmediate<Word>(m68000, x)) {
        return;
    }
    m68000.InternalCycle();
    m68000.InternalCycle();
    m68000.InternalCycle();
    m68000.InternalCycle();
    // Note: this is guesswork on my behalf
    // The logical to SR ops perform 3 reads when only 2 would be necessary.
    // My guess is that the first read is repeated, but I would need to verify this in a test.
    m68000.WritePC(m68000.ReadPC() - 2u);
    if (!ExecutePrefetchCycle(m68000)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto y = m68000.ReadSR();
    const auto result = BinaryOp()(x, y);
    m68000.WriteSR(result);
}

/*
 * Address modes for ALU operation with memory as the destination
 *
 */

// {BTST|BCHG|BCLR|BSET}.L Dx, Dy

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpDataRegisterXToDataRegisterY(M68000& m68000, uint32_t opcode) {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = m68000.ReadDataRegisterLong(rx);
    const auto y = m68000.ReadDataRegisterLong(ry);
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = BinaryOp<T>()(m68000, x, y);
    if constexpr(std::is_same_v<BinaryOp<T>, Btst<T>>) {
        if constexpr(std::is_same_v<T, Long>) {
            m68000.InternalCycle();
        }
        return;
    }
    if constexpr(std::is_same_v<BinaryOp<T>, Bclr<T>>) {
        if constexpr(std::is_same_v<T, Long>) {
            m68000.InternalCycle();
        }
    }
    if constexpr(std::is_same_v<T, Long>) {
        m68000.InternalCycle();
        m68000.InternalCycle();
    }
    WriteDataRegister<T>(m68000, ry, result);
}

// {BTST|BCHG|BCLR|BSET}.B Dx, (Ay)

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpDataRegisterToAddressIndirect(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = m68000.ReadDataRegisterLong(rx);
    uint32_t address, y;
    if (!ReadMemoryFromAddressIndirect<T>(m68000, ry, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = BinaryOp<T>()(m68000, x, y);
    if constexpr(std::is_same_v<BinaryOp<T>, Btst<T>>) {
        return;
    }
    WriteMemory<T>(m68000, address, result);
}

// {BTST|BCHG|BCLR|BSET}.B Dx, (Ay)+

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpDataRegisterToAddressIncrement(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = m68000.ReadDataRegisterLong(rx);
    uint32_t address, y;
    if (!ReadMemoryFromAddressIncrement<T>(m68000, ry, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = BinaryOp<T>()(m68000, x, y);
    if constexpr(std::is_same_v<BinaryOp<T>, Btst<T>>) {
        return;
    }
    WriteMemory<T>(m68000, address, result);
}

// {BTST|BCHG|BCLR|BSET}.B Dx, -(Ay)

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpDataRegisterToAddressDecrement(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = m68000.ReadDataRegisterLong(rx);
    uint32_t address, y;
    if (!ReadMemoryFromAddressDecrement<T>(m68000, ry, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = BinaryOp<T>()(m68000, x, y);
    if constexpr(std::is_same_v<BinaryOp<T>, Btst<T>>) {
        return;
    }
    WriteMemory<T>(m68000, address, result);
}

// {BTST|BCHG|BCLR|BSET}.B Dx, (d, Ay)

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpDataRegisterToAddressDisplacement(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = m68000.ReadDataRegisterLong(rx);
    uint32_t address, y;
    if (!ReadMemoryFromAddressDisplacement<T>(m68000, ry, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = BinaryOp<T>()(m68000, x, y);
    if constexpr(std::is_same_v<BinaryOp<T>, Btst<T>>) {
        return;
    }
    WriteMemory<T>(m68000, address, result);
}

// {BTST|BCHG|BCLR|BSET}.B Dx, (d, Ay, Xn)

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpDataRegisterToAddressIndex(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = m68000.ReadDataRegisterLong(rx);
    uint32_t address, y;
    if (!ReadMemoryFromAddressIndex<T>(m68000, ry, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = BinaryOp<T>()(m68000, x, y);
    if constexpr(std::is_same_v<BinaryOp<T>, Btst<T>>) {
        return;
    }
    WriteMemory<T>(m68000, address, result);
}

// {BTST|BCHG|BCLR|BSET}.B Dx, (address).W

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpDataRegisterToShort(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    const auto rx = OpcodeRegisterX(opcode);
    const auto x = m68000.ReadDataRegisterLong(rx);
    uint32_t address, y;
    if (!ReadMemoryFromShort<T>(m68000, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = BinaryOp<T>()(m68000, x, y);
    if constexpr(std::is_same_v<BinaryOp<T>, Btst<T>>) {
        return;
    }
    WriteMemory<T>(m68000, address, result);
}

// {BTST|BCHG|BCLR|BSET}.B Dx, (address).L

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpDataRegisterToLong(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    const auto rx = OpcodeRegisterX(opcode);
    const auto x = m68000.ReadDataRegisterLong(rx);
    uint32_t address, y;
    if (!ReadMemoryFromLong<T>(m68000, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = BinaryOp<T>()(m68000, x, y);
    if constexpr(std::is_same_v<BinaryOp<T>, Btst<T>>) {
        return;
    }
    WriteMemory<T>(m68000, address, result);
}

// BTST.B Dx, (d, PC)

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpDataRegisterToPCDisplacement(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    const auto rx = OpcodeRegisterX(opcode);
    const auto x = m68000.ReadDataRegisterLong(rx);
    uint32_t address, y;
    if (!ReadMemoryFromPCDisplacement<T>(m68000, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = BinaryOp<T>()(m68000, x, y);
    if constexpr(std::is_same_v<BinaryOp<T>, Btst<T>>) {
        return;
    }
    WriteMemory<T>(m68000, address, result);
}

// BTST.B Dx, (d, PC, Xn)

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpDataRegisterToPCIndex(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    const auto rx = OpcodeRegisterX(opcode);
    const auto x = m68000.ReadDataRegisterLong(rx);
    uint32_t address, y;
    if (!ReadMemoryFromPCIndex<T>(m68000, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = BinaryOp<T>()(m68000, x, y);
    if constexpr(std::is_same_v<BinaryOp<T>, Btst<T>>) {
        return;
    }
    WriteMemory<T>(m68000, address, result);
}

// BTST.B Dx, #imm

template<template<typename> typename BinaryOp, typename T>
auto ExecuteBinaryOpDataRegisterToImmediate(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    const auto rx = OpcodeRegisterX(opcode);
    const auto x = m68000.ReadDataRegisterLong(rx);
    uint32_t y;
    if (!ReadImmediate<T>(m68000, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    BinaryOp<T>()(m68000, x, y);
}

} // namespace addressing::immediate

namespace addressing::shift_rotate {

// {ASR|LSR|ROXR|ROR}.W #imm, Dy
// {ASL|LSL|ROXL|ROL}.W #imm, Dy

template<template<typename> typename ShiftRotateOp, typename T>
auto ExecuteShiftRotateOpCountToDataRegister(M68000& m68000, uint32_t opcode) {
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = m68000.ReadDataRegisterLong(ry);
    const auto shift = OpcodeQuick(opcode);
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    if constexpr(std::is_same_v<T, Byte> || std::is_same_v<T, Word>) {
        m68000.ElapseCycles(2u + 2u * shift);
    } else {
        m68000.ElapseCycles(4u + 2u * shift);
    }
    const auto result = ShiftRotateOp<T>()(m68000, shift, y);
    WriteDataRegister<T>(m68000, ry, result);
}

// {ASR|LSR|ROXR|ROR}.W Dx, Dy
// {ASL|LSL|ROXL|ROL}.W Dx, Dy

template<template<typename> typename ShiftRotateOp, typename T>
auto ExecuteShiftRotateOpRegisterToDataRegister(M68000& m68000, uint32_t opcode) {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = m68000.ReadDataRegisterLong(rx);
    const auto y = m68000.ReadDataRegisterLong(ry);
    const auto shift = x & 0x3Fu;
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    if constexpr(std::is_same_v<T, Byte> || std::is_same_v<T, Word>) {
        m68000.ElapseCycles(2u + 2u * shift);
    } else {
        m68000.ElapseCycles(4u + 2u * shift);
    }
    const auto result = ShiftRotateOp<T>()(m68000, shift, y);
    WriteDataRegister<T>(m68000, ry, result);
}

// {ASR|LSR|ROXR|ROR}.W (Ay)
// {ASL|LSL|ROXL|ROL}.W (Ay)

template<template<typename> typename ShiftRotateOp>
auto ExecuteShiftRotateOpToAddressIndirect(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!ReadMemoryFromAddressIndirect<Word>(m68000, ry, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = ShiftRotateOp<Word>()(m68000, 1u, y);
    WriteMemory<Word>(m68000, address, result);
}

// {ASR|LSR|ROXR|ROR}.W (Ay)+
// {ASL|LSL|ROXL|ROL}.W (Ay)+

template<template<typename> typename ShiftRotateOp>
auto ExecuteShiftRotateOpToAddressIncrement(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!ReadMemoryFromAddressIncrement<Word>(m68000, ry, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = ShiftRotateOp<Word>()(m68000, 1u, y);
    WriteMemory<Word>(m68000, address, result);
}

// {ASR|LSR|ROXR|ROR}.W -(Ay)
// {ASL|LSL|ROXL|ROL}.W -(Ay)

template<template<typename> typename ShiftRotateOp>
auto ExecuteShiftRotateOpToAddressDecrement(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!ReadMemoryFromAddressDecrement<Word>(m68000, ry, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = ShiftRotateOp<Word>()(m68000, 1u, y);
    WriteMemory<Word>(m68000, address, result);
}

// {ASR|LSR|ROXR|ROR}.W (d, Ay)
// {ASL|LSL|ROXL|ROL}.W (d, Ay)

template<template<typename> typename ShiftRotateOp>
auto ExecuteShiftRotateOpToAddressDisplacement(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!ReadMemoryFromAddressDisplacement<Word>(m68000, ry, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = ShiftRotateOp<Word>()(m68000, 1u, y);
    WriteMemory<Word>(m68000, address, result);
}

// {ASR|LSR|ROXR|ROR}.W (d, Ay, Xn)
// {ASL|LSL|ROXL|ROL}.W (d, Ay, Xn)

template<template<typename> typename ShiftRotateOp>
auto ExecuteShiftRotateOpToAddressIndex(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!ReadMemoryFromAddressIndex<Word>(m68000, ry, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = ShiftRotateOp<Word>()(m68000, 1u, y);
    WriteMemory<Word>(m68000, address, result);
}

// {ASR|LSR|ROXR|ROR}.W (address).W
// {ASL|LSL|ROXL|ROL}.W (address).W

template<template<typename> typename ShiftRotateOp>
auto ExecuteShiftRotateOpToShort(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    uint32_t address, y;
    if (!ReadMemoryFromShort<Word>(m68000, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = ShiftRotateOp<Word>()(m68000, 1u, y);
    WriteMemory<Word>(m68000, address, result);
}

// {ASR|LSR|ROXR|ROR}.W (address).L
// {ASL|LSL|ROXL|ROL}.W (address).L

template<template<typename> typename ShiftRotateOp>
auto ExecuteShiftRotateOpToLong(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    uint32_t address, y;
    if (!ReadMemoryFromLong<Word>(m68000, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = ShiftRotateOp<Word>()(m68000, 1u, y);
    WriteMemory<Word>(m68000, address, result);
}


} // namespace addressing::shift_rotate

namespace addressing::single {

// {NEGX|CLR|NEG|NOT|TST}.{B|W|L} Dy
// NBCD.B Dy

template<template<typename> typename UnaryOp, typename T>
auto ExecuteUnaryOpToDataRegister(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = m68000.ReadDataRegisterLong(ry);
    const auto result = UnaryOp<T>()(m68000, y);
    if constexpr(std::is_same_v<UnaryOp<T>, Tst<T>>) {
        return;
    }
    if constexpr(
        std::is_same_v<UnaryOp<T>, Nbcd<Byte>> ||
        std::is_same_v<UnaryOp<T>, MoveFromSR<Word>>) {
        m68000.InternalCycle();
    }
    if constexpr(std::is_same_v<T, Long>) {
        m68000.InternalCycle();
    }
    WriteDataRegister<T>(m68000, ry, result);
}

// {NEGX|CLR|NEG|NOT|TST}.{B|W|L} (Ay)
// NBCD.B (Ay)

template<template<typename> typename UnaryOp, typename T>
auto ExecuteUnaryOpToAddressIndirect(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!ReadMemoryFromAddressIndirect<T>(m68000, ry, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = UnaryOp<T>()(m68000, y);
    if constexpr(std::is_same_v<UnaryOp<T>, Tst<T>>) {
        return;
    }
    WriteMemory<T>(m68000, address, result);
}

// {NEGX|CLR|NEG|NOT|TST}.{B|W|L} (Ay)+
// NBCD.B (Ay)+

template<template<typename> typename UnaryOp, typename T>
auto ExecuteUnaryOpToAddressIncrement(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!ReadMemoryFromAddressIncrement<T>(m68000, ry, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = UnaryOp<T>()(m68000, y);
    if constexpr(std::is_same_v<UnaryOp<T>, Tst<T>>) {
        return;
    }
    WriteMemory<T>(m68000, address, result);
}


// {NEGX|CLR|NEG|NOT|TST}.{B|W|L} -(Ay)
// NBCD.B -(Ay)

template<template<typename> typename UnaryOp, typename T>
auto ExecuteUnaryOpToAddressDecrement(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!ReadMemoryFromAddressDecrement<T>(m68000, ry, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = UnaryOp<T>()(m68000, y);
    if constexpr(std::is_same_v<UnaryOp<T>, Tst<T>>) {
        return;
    }
    WriteMemory<T>(m68000, address, result);
}

// {NEGX|CLR|NEG|NOT|TST}.{B|W|L} (d, Ay)
// NBCD.B (d, Ay)

template<template<typename> typename UnaryOp, typename T>
auto ExecuteUnaryOpToAddressDisplacement(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!ReadMemoryFromAddressDisplacement<T>(m68000, ry, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = UnaryOp<T>()(m68000, y);
    if constexpr(std::is_same_v<UnaryOp<T>, Tst<T>>) {
        return;
    }
    WriteMemory<T>(m68000, address, result);
}

// {NEGX|CLR|NEG|NOT|TST}.{B|W|L} (d, Ay, Xn)
// NBCD.B (d, Ay, Xn)

template<template<typename> typename UnaryOp, typename T>
auto ExecuteUnaryOpToAddressIndex(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!ReadMemoryFromAddressIndex<T>(m68000, ry, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = UnaryOp<T>()(m68000, y);
    if constexpr(std::is_same_v<UnaryOp<T>, Tst<T>>) {
        return;
    }
    WriteMemory<T>(m68000, address, result);
}

// {NEGX|CLR|NEG|NOT|TST}.{B|W|L} (address).W
// NBCD.B (address).W

template<template<typename> typename UnaryOp, typename T>
auto ExecuteUnaryOpToShort(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    uint32_t address, y;
    if (!ReadMemoryFromShort<T>(m68000, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = UnaryOp<T>()(m68000, y);
    if constexpr(std::is_same_v<UnaryOp<T>, Tst<T>>) {
        return;
    }
    WriteMemory<T>(m68000, address, result);
}

// {NEGX|CLR|NEG|NOT|TST}.{B|W|L} (address).L
// NBCD.B (address).L

template<template<typename> typename UnaryOp, typename T>
auto ExecuteUnaryOpToLong(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    uint32_t address, y;
    if (!ReadMemoryFromLong<T>(m68000, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = UnaryOp<T>()(m68000, y);
    if constexpr(std::is_same_v<UnaryOp<T>, Tst<T>>) {
        return;
    }
    WriteMemory<T>(m68000, address, result);
}

} // namespace addressing::single

namespace addressing::quick {

// {ADDQ|SUBQ}.{B|W|L} #imm, Dy
// Scc Dy

template<template<typename> typename BinaryOp, typename T>
auto ExecuteQuickOpToDataRegister(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    // Note: yacht.txt says that the additional internal cycles for
    // SCC: occur after the prefetch cycle
    // ADDQ.L: occur after the prefetch cycle
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = m68000.ReadDataRegisterLong(ry);
    const auto result = BinaryOp<T>()(m68000, opcode, y);
    WriteDataRegister<T>(m68000, ry, result);
    if constexpr(std::is_same_v<T, Long>) {
        m68000.InternalCycle();
        m68000.InternalCycle();
    }
}

// {ADDQ|SUBQ}.{B|W|L} #imm, Ay

template<template<typename> typename BinaryOp, typename T>
auto ExecuteQuickOpToAddressRegister(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto x = OpcodeQuick(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = m68000.ReadAddressRegisterLong(ry);
    const auto result = BinaryOp<T>()(m68000, x, y);
    m68000.WriteAddressRegisterLong(ry, result);
    m68000.InternalCycle();
    m68000.InternalCycle();
}

// {ADDQ|SUBQ}.{B|W|L} #imm, (Ay)
// Scc (Ay)

template<template<typename> typename BinaryOp, typename T>
auto ExecuteQuickOpToAddressIndirect(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!ReadMemoryFromAddressIndirect<T>(m68000, ry, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = BinaryOp<T>()(m68000, opcode, y);
    WriteMemory<T>(m68000, address, result);
}

// {ADDQ|SUBQ}.{B|W|L} #imm, (Ay)+
// Scc (Ay)+

template<template<typename> typename BinaryOp, typename T>
auto ExecuteQuickOpToAddressIncrement(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!ReadMemoryFromAddressIncrement<T>(m68000, ry, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = BinaryOp<T>()(m68000, opcode, y);
    WriteMemory<T>(m68000, address, result);
}

// {ADDQ|SUBQ}.{B|W|L} #imm, -(Ay)
// Scc -(Ay)

template<template<typename> typename BinaryOp, typename T>
auto ExecuteQuickOpToAddressDecrement(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!ReadMemoryFromAddressDecrement<T>(m68000, ry, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = BinaryOp<T>()(m68000, opcode, y);
    WriteMemory<T>(m68000, address, result);
}

// {ADDQ|SUBQ}.{B|W|L} #imm, (d, Ay)
// Scc (d, Ay)

template<template<typename> typename BinaryOp, typename T>
auto ExecuteQuickOpToAddressDisplacement(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!ReadMemoryFromAddressDisplacement<T>(m68000, ry, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = BinaryOp<T>()(m68000, opcode, y);
    WriteMemory<T>(m68000, address, result);
}

// {ADDQ|SUBQ}.{B|W|L} #imm, (d, Ay, Xn)
// Scc (d, Ay, Xn)

template<template<typename> typename BinaryOp, typename T>
auto ExecuteQuickOpToAddressIndex(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!ReadMemoryFromAddressIndex<T>(m68000, ry, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = BinaryOp<T>()(m68000, opcode, y);
    WriteMemory<T>(m68000, address, result);
}

// {ADDQ|SUBQ}.{B|W|L} #imm, (address).W
// Scc (address).W

template<template<typename> typename BinaryOp, typename T>
auto ExecuteQuickOpToShort(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    uint32_t address, y;
    if (!ReadMemoryFromShort<T>(m68000, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = BinaryOp<T>()(m68000, opcode, y);
    WriteMemory<T>(m68000, address, result);
}

// {ADDQ|SUBQ}.{B|W|L} #imm, (address).L
// Scc (address).L

template<template<typename> typename BinaryOp, typename T>
auto ExecuteQuickOpToLong(M68000& m68000, uint32_t opcode) {
    // Note: The prefetch document says that all prefetch cycles are performed before the writes
    uint32_t address, y;
    if (!ReadMemoryFromLong<T>(m68000, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = BinaryOp<T>()(m68000, opcode, y);
    WriteMemory<T>(m68000, address, result);
}


} // namespace addressing::quick

namespace addressing::move {
// Move specific functions

// MOVE.{B|W|L} <ea>, Dx
template<template<typename> typename Source, typename T>
auto ExecuteMoveOpToDataRegister(M68000& m68000, uint32_t opcode) {
    // Note: the prefetch cycles happen after the writes
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!Source<T>()(m68000, ry, address, y)) {
        return;
    }
    const auto result = Move<T>()(m68000, y);
    WriteDataRegister<T>(m68000, rx, result);
    ExecuteFinalPrefetchCycle(m68000);
}


// MOVE.{W|L} <ea>, Ax
template<template<typename> typename Source, typename T>
auto ExecuteMoveOpToAddressRegister(M68000& m68000, uint32_t opcode) {
    // Note: the prefetch cycles happen after the writes
    if constexpr(std::is_same_v<T, Byte>) {
        return ExecuteIllegal(m68000);
    }
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!Source<T>()(m68000, ry, address, y)) {
        return;
    }
    const auto result = Movea<T>()(m68000, y);
    m68000.WriteAddressRegisterLong(rx, result);
    ExecuteFinalPrefetchCycle(m68000);
}

// MOVE.{B|W|L} <ea>, (Ax)
template<template<typename> typename Source, typename T>
auto ExecuteMoveOpToAddressIndirect(M68000& m68000, uint32_t opcode) {
    // Note: the documentation says the writes happen before prefetch
    // Note: not sure at what point the flags are evaluated.
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!Source<T>()(m68000, ry, address, y)) {
        return;
    }
    if (!EffectiveAddressAddressIndirect<T>(m68000, rx, address)) {
        return;
    }
    const auto result = Move<T>()(m68000, y);
    if (!WriteMemory<T>(m68000, address, result)) {
        return;
    }
    ExecuteFinalPrefetchCycle(m68000);
}

// MOVE.{B|W|L} <ea>, (Ax)+
template<template<typename> typename Source, typename T>
auto ExecuteMoveOpToAddressIncrement(M68000& m68000, uint32_t opcode) {
    // Note: the documentation says the writes happen before prefetch
    // Note: not sure at what point the flags are evaluated.
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!Source<T>()(m68000, ry, address, y)) {
        return;
    }
    if (!EffectiveAddressAddressIncrement<T>(m68000, rx, address)) {
        return;
    }
    const auto result = Move<T>()(m68000, y);
    if (!WriteMemory<T>(m68000, address, result)) {
        return;
    }
    ExecuteFinalPrefetchCycle(m68000);
}


// MOVE.{B|W|L} <ea>, -(Ax)
template<template<typename> typename Source, typename T>
auto ExecuteMoveOpToAddressDecrement(M68000& m68000, uint32_t opcode) {
    // Note: the documentation says the prefetch happens before the writes
    // Note: not sure at what point the flags are evaluated.
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!Source<T>()(m68000, ry, address, y)) {
        return;
    }
    if (!EffectiveAddressAddressDecrement<T>(m68000, rx, address)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    const auto result = Move<T>()(m68000, y);
    WriteMemory<T>(m68000, address, result);
}

// MOVE.{B|W|L} <ea>, (d, Ax)
template<template<typename> typename Source, typename T>
auto ExecuteMoveOpToAddressDisplacement(M68000& m68000, uint32_t opcode) {
    // Note: the documentation says the writes happen before prefetch
    // Note: not sure at what point the flags are evaluated.
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!Source<T>()(m68000, ry, address, y)) {
        return;
    }
    if (!EffectiveAddressAddressDisplacement<T>(m68000, rx, address)) {
        return;
    }
    const auto result = Move<T>()(m68000, y);
    if (!WriteMemory<T>(m68000, address, result)) {
        return;
    }
    ExecuteFinalPrefetchCycle(m68000);
}

// MOVE.{B|W|L} <ea>, (d, Ax, Xn)
template<template<typename> typename Source, typename T>
auto ExecuteMoveOpToAddressIndex(M68000& m68000, uint32_t opcode) {
    // Note: prefetch documents says the writes happen before prefetch
    // Note: not sure at what point the flags are evaluated.
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!Source<T>()(m68000, ry, address, y)) {
        return;
    }
    if (!EffectiveAddressAddressIndex<T>(m68000, rx, address)) {
        return;
    }
    const auto result = Move<T>()(m68000, y);
    if (!WriteMemory<T>(m68000, address, result)) {
        return;
    }
    ExecuteFinalPrefetchCycle(m68000);
}

// MOVE.{B|W|L} <ea>, (address).W
template<template<typename> typename Source, typename T>
auto ExecuteMoveOpToShort(M68000& m68000, uint32_t opcode) {
    // Note: the documentation says the writes happen before prefetch
    // Note: not sure at what point the flags are evaluated.
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!Source<T>()(m68000, ry, address, y)) {
        return;
    }
    if (!EffectiveAddressShort<T>(m68000, address)) {
        return;
    }
    const auto result = Move<T>()(m68000, y);
    if (!WriteMemory<T>(m68000, address, result)) {
        return;
    }
    ExecuteFinalPrefetchCycle(m68000);
}


// MOVE.{B|W|L} {D|A}y, (address).L
template<template<typename> typename Source, typename T>
auto ExecuteMoveOpRegisterToLong(M68000& m68000, uint32_t opcode) {
    // Note: the documentation says the writes happen before prefetch
    // Note: not sure at what point the flags are evaluated.
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!Source<T>()(m68000, ry, address, y)) {
        return;
    }
    if (!EffectiveAddressLong<T>(m68000, address)) {
        return;
    }
    const auto result = Move<T>()(m68000, y);
    if (!WriteMemory<T>(m68000, address, result)) {
        return;
    }
    ExecuteFinalPrefetchCycle(m68000);
}


// MOVE.{B|W|L} <ea>, (address).L
template<template<typename> typename Source, typename T>
auto ExecuteMoveOpToLong(M68000& m68000, uint32_t opcode) {
    // Note: the instruction only performs one prefetch cycle
    // to copy the low order word of the address into irc
    // Then uses the new value of irc to form the address
    // The second usual prefetch cycle is deferred until after the write-cycles.
    // This is what the prefetch doc calls a class 2 instruction
    // (2 prefetches after the write-cycles).
    // Note: not sure at what point the flags are evaluated.
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!Source<T>()(m68000, ry, address, y)) {
        return;
    }
    const auto hi = m68000.ReadIRC();
    if (!ExecutePrefetchCycle(m68000)) {
        return;
    }
    const auto lo = m68000.ReadIRC();
    address = (hi << 16u) + lo;
    const auto result = Move<T>()(m68000, y);
    if (!WriteMemory<T>(m68000, address, result)) {
        return;
    }
    if (!ExecutePrefetchCycle(m68000)) {
        return;
    }
    ExecuteFinalPrefetchCycle(m68000);
}

} // namespace addressing::move

namespace addressing::multiprecision {

// ADDX.{B|W|L} Dy, Dx
// ABCD Dy, Dx
// SBCD Dy, Dx

template<template<typename> typename BinaryOp, typename T>
auto ExecuteMultiprecisionOpDataRegisterToDataRegister(M68000& m68000, uint32_t opcode) {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = m68000.ReadDataRegisterLong(rx);
    const auto y = m68000.ReadDataRegisterLong(ry);
    const auto result = BinaryOp<T>()(m68000, y, x);
    WriteDataRegister<T>(m68000, rx, result);
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    if constexpr(std::is_same_v<BinaryOp<T>, Abcd<T>> || std::is_same_v<BinaryOp<T>, Sbcd<T>>) {
        m68000.InternalCycle();
        return;
    }
    if constexpr(std::is_same_v<T, Long>) {
        m68000.InternalCycle();
        m68000.InternalCycle();
    }
}

// ADDX.{B|W|L} -(Ay), -(Ax)
// ABCD -(Ay), -(Ax)
// SBCD -(Ay), -(Ax)

template<template<typename> typename BinaryOp, typename T>
auto ExecuteMultiprecisionOpAddressDecrementToAddressDecrement(M68000& m68000, uint32_t opcode) {
    // Note: yacht.txt claims for longs that these instructions interleave write and prefetch operations
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y, x;
    if (!SourceAddressDecrement<T>()(m68000, ry, address, y)) {
        return;
    }
    if (!SourceAddressDecrementWithoutInternalCycle<T>()(m68000, rx, address, x)) {
        return;
    }
    const auto result = BinaryOp<T>()(m68000, y, x);
    if constexpr(std::is_same_v<T, Long>) {
        if (!WriteMemory<Word>(m68000, address + 2u, result)) {
            return;
        }
        if (!ExecuteFinalPrefetchCycle(m68000)) {
            return;
        }
        WriteMemory<Word>(m68000, address, result >> 16u);
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    WriteMemory<T>(m68000, address, result);
}

// CMPM.{B|W|L} (Ay)+, (Ax)+

template<template<typename> typename BinaryOp, typename T>
auto ExecuteMultiprecisionOpAddressIncrementToAddressIncrement(M68000& m68000, uint32_t opcode) {
    // Note: yacht.txt claims for longs that these instructions interleave write and prefetch operations
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y, x;
    if (!SourceAddressIncrement<T>()(m68000, ry, address, y)) {
        return;
    }
    if (!SourceAddressIncrement<T>()(m68000, rx, address, x)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    BinaryOp<T>()(m68000, y, x);
}

} // namespace addressing::multiprecision

namespace addressing::check {

template<template<typename> typename Source>
auto ExecuteChkToDataRegister(M68000& m68000, uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = Truncate16(m68000.ReadDataRegisterLong(rx));
    uint32_t address, y;
    if (!Source<Word>()(m68000, ry, address, y)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    if ((x & 0x8000u) || (y & 0x8000u) || (x > y)) {
        WriteFlagN<Word>(m68000, x);
        RaiseChkException(m68000);
        return;
    }
    m68000.InternalCycle();
    m68000.InternalCycle();
    m68000.InternalCycle();
}

} // namespace addressing::check

namespace addressing::ccr {

template<template<typename> typename Source>
auto ExecuteMoveOpSourceToCCR(M68000& m68000, uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!Source<Word>()(m68000, ry, address, y)) {
        return;
    }
    m68000.InternalCycle();
    m68000.InternalCycle();
    // Note: this is guesswork on my behalf
    // Yacht claims that there's an extra read cycle
    // This needs to be verified
    m68000.WritePC(m68000.ReadPC() - 2u);
    if (!ExecutePrefetchCycle(m68000)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    m68000.WriteCCR(y);
}

template<template<typename> typename Source>
auto ExecuteMoveOpSourceToSR(M68000& m68000, uint32_t opcode) -> void {
    if (!m68000.ReadFlagS()) {
        RaisePrivilegeViolationException(m68000);
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!Source<Word>()(m68000, ry, address, y)) {
        return;
    }
    m68000.InternalCycle();
    m68000.InternalCycle();
    // Note: this is guesswork on my behalf
    // Yacht claims that there's an extra read cycle
    // This needs to be verified
    m68000.WritePC(m68000.ReadPC() - 2u);
    if (!ExecutePrefetchCycle(m68000)) {
        return;
    }
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    m68000.WriteSR(y);
}

auto ExecuteMoveOpDataRegisterToCCR(M68000& m68000, uint32_t opcode) -> void {
    return ExecuteMoveOpSourceToCCR<SourceDataRegister>(m68000, opcode);
}

auto ExecuteMoveOpAddressIndirectToCCR(M68000& m68000, uint32_t opcode) -> void {
    return ExecuteMoveOpSourceToCCR<SourceAddressIndirect>(m68000, opcode);
}

auto ExecuteMoveOpAddressIncrementToCCR(M68000& m68000, uint32_t opcode) -> void {
    return ExecuteMoveOpSourceToCCR<SourceAddressIncrement>(m68000, opcode);
}

auto ExecuteMoveOpAddressDecrementToCCR(M68000& m68000, uint32_t opcode) -> void {
    return ExecuteMoveOpSourceToCCR<SourceAddressDecrement>(m68000, opcode);
}

auto ExecuteMoveOpAddressDisplacementToCCR(M68000& m68000, uint32_t opcode) -> void {
    return ExecuteMoveOpSourceToCCR<SourceAddressDisplacement>(m68000, opcode);
}

auto ExecuteMoveOpAddressIndexToCCR(M68000& m68000, uint32_t opcode) -> void {
    return ExecuteMoveOpSourceToCCR<SourceAddressIndex>(m68000, opcode);
}

auto ExecuteMoveOpShortToCCR(M68000& m68000, uint32_t opcode) -> void {
    return ExecuteMoveOpSourceToCCR<SourceShort>(m68000, opcode);
}

auto ExecuteMoveOpLongToCCR(M68000& m68000, uint32_t opcode) -> void {
    return ExecuteMoveOpSourceToCCR<SourceLong>(m68000, opcode);
}

auto ExecuteMoveOpPCDisplacementToCCR(M68000& m68000, uint32_t opcode) -> void {
    return ExecuteMoveOpSourceToCCR<SourcePCDisplacement>(m68000, opcode);
}

auto ExecuteMoveOpPCIndexToCCR(M68000& m68000, uint32_t opcode) -> void {
    return ExecuteMoveOpSourceToCCR<SourcePCIndex>(m68000, opcode);
}

auto ExecuteMoveOpImmediateToCCR(M68000& m68000, uint32_t opcode) -> void {
    return ExecuteMoveOpSourceToCCR<SourceImmediate>(m68000, opcode);
}

auto ExecuteMoveOpDataRegisterToSR(M68000& m68000, uint32_t opcode) -> void {
    return ExecuteMoveOpSourceToSR<SourceDataRegister>(m68000, opcode);
}

auto ExecuteMoveOpAddressIndirectToSR(M68000& m68000, uint32_t opcode) -> void {
    return ExecuteMoveOpSourceToSR<SourceAddressIndirect>(m68000, opcode);
}

auto ExecuteMoveOpAddressIncrementToSR(M68000& m68000, uint32_t opcode) -> void {
    return ExecuteMoveOpSourceToSR<SourceAddressIncrement>(m68000, opcode);
}

auto ExecuteMoveOpAddressDecrementToSR(M68000& m68000, uint32_t opcode) -> void {
    return ExecuteMoveOpSourceToSR<SourceAddressDecrement>(m68000, opcode);
}

auto ExecuteMoveOpAddressDisplacementToSR(M68000& m68000, uint32_t opcode) -> void {
    return ExecuteMoveOpSourceToSR<SourceAddressDisplacement>(m68000, opcode);
}

auto ExecuteMoveOpAddressIndexToSR(M68000& m68000, uint32_t opcode) -> void {
    return ExecuteMoveOpSourceToSR<SourceAddressIndex>(m68000, opcode);
}

auto ExecuteMoveOpShortToSR(M68000& m68000, uint32_t opcode) -> void {
    return ExecuteMoveOpSourceToSR<SourceShort>(m68000, opcode);
}

auto ExecuteMoveOpLongToSR(M68000& m68000, uint32_t opcode) -> void {
    return ExecuteMoveOpSourceToSR<SourceLong>(m68000, opcode);
}

auto ExecuteMoveOpPCDisplacementToSR(M68000& m68000, uint32_t opcode) -> void {
    return ExecuteMoveOpSourceToSR<SourcePCDisplacement>(m68000, opcode);
}

auto ExecuteMoveOpPCIndexToSR(M68000& m68000, uint32_t opcode) -> void {
    return ExecuteMoveOpSourceToSR<SourcePCIndex>(m68000, opcode);
}

auto ExecuteMoveOpImmediateToSR(M68000& m68000, uint32_t opcode) -> void {
    return ExecuteMoveOpSourceToSR<SourceImmediate>(m68000, opcode);
}


} // namespace addressing::ccr

/*
 * Dispatch
 *
 */

consteval auto SizeMode(auto size, auto mode) {
    return ((size & 7u) << 6u) + ((mode & 7u) << 3u);
}

consteval auto RegisterXY(auto x, auto y) {
    return ((x & 7u) << 9u) + (y & 0x7u);
}

auto ExecuteLine0(M68000& m68000, uint32_t opcode) {
    using namespace addressing::immediate;
    switch (opcode & SizeMode(7u, 7u)) {
        // {ORI|ANDI|SUBI|ADDI|EORI|CMPI}.B #imm, Dy
        // BTST.L #imm, Dy
        case SizeMode(0u, 0u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteBinaryOpImmediateToDataRegisterY<Or, Byte>(m68000, opcode);
                case 1u: return ExecuteBinaryOpImmediateToDataRegisterY<And, Byte>(m68000, opcode);
                case 2u: return ExecuteBinaryOpImmediateToDataRegisterY<Sub, Byte>(m68000, opcode);
                case 3u: return ExecuteBinaryOpImmediateToDataRegisterY<Add, Byte>(m68000, opcode);
                case 4u: return ExecuteBitwiseOpImmediateToDataRegisterY<Btst, Long>(m68000, opcode);
                case 5u: return ExecuteBinaryOpImmediateToDataRegisterY<Eor, Byte>(m68000, opcode);
                case 6u: return ExecuteBinaryOpImmediateToDataRegisterY<Cmp, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {ORI|ANDI|SUBI|ADDI|BTST|EORI|CMPI}.B #imm, (Ay)
        case SizeMode(0u, 2u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteBinaryOpImmediateToAddressIndirect<Or, Byte>(m68000, opcode);
                case 1u: return ExecuteBinaryOpImmediateToAddressIndirect<And, Byte>(m68000, opcode);
                case 2u: return ExecuteBinaryOpImmediateToAddressIndirect<Sub, Byte>(m68000, opcode);
                case 3u: return ExecuteBinaryOpImmediateToAddressIndirect<Add, Byte>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToAddressIndirect<Btst, Byte>(m68000, opcode);
                case 5u: return ExecuteBinaryOpImmediateToAddressIndirect<Eor, Byte>(m68000, opcode);
                case 6u: return ExecuteBinaryOpImmediateToAddressIndirect<Cmp, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {ORI|ANDI|SUBI|ADDI|BTST|EORI|CMPI}.B #imm, (Ay)+
        case SizeMode(0u, 3u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteBinaryOpImmediateToAddressIncrement<Or, Byte>(m68000, opcode);
                case 1u: return ExecuteBinaryOpImmediateToAddressIncrement<And, Byte>(m68000, opcode);
                case 2u: return ExecuteBinaryOpImmediateToAddressIncrement<Sub, Byte>(m68000, opcode);
                case 3u: return ExecuteBinaryOpImmediateToAddressIncrement<Add, Byte>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToAddressIncrement<Btst, Byte>(m68000, opcode);
                case 5u: return ExecuteBinaryOpImmediateToAddressIncrement<Eor, Byte>(m68000, opcode);
                case 6u: return ExecuteBinaryOpImmediateToAddressIncrement<Cmp, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {ORI|ANDI|SUBI|ADDI|BTST|EORI|CMPI}.B #imm, -(Ay)
        case SizeMode(0u, 4u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteBinaryOpImmediateToAddressDecrement<Or, Byte>(m68000, opcode);
                case 1u: return ExecuteBinaryOpImmediateToAddressDecrement<And, Byte>(m68000, opcode);
                case 2u: return ExecuteBinaryOpImmediateToAddressDecrement<Sub, Byte>(m68000, opcode);
                case 3u: return ExecuteBinaryOpImmediateToAddressDecrement<Add, Byte>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToAddressDecrement<Btst, Byte>(m68000, opcode);
                case 5u: return ExecuteBinaryOpImmediateToAddressDecrement<Eor, Byte>(m68000, opcode);
                case 6u: return ExecuteBinaryOpImmediateToAddressDecrement<Cmp, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {ORI|ANDI|SUBI|ADDI|BTST|EORI|CMPI}.B #imm, (d, Ay)
        case SizeMode(0u, 5u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteBinaryOpImmediateToAddressDisplacement<Or, Byte>(m68000, opcode);
                case 1u: return ExecuteBinaryOpImmediateToAddressDisplacement<And, Byte>(m68000, opcode);
                case 2u: return ExecuteBinaryOpImmediateToAddressDisplacement<Sub, Byte>(m68000, opcode);
                case 3u: return ExecuteBinaryOpImmediateToAddressDisplacement<Add, Byte>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToAddressDisplacement<Btst, Byte>(m68000, opcode);
                case 5u: return ExecuteBinaryOpImmediateToAddressDisplacement<Eor, Byte>(m68000, opcode);
                case 6u: return ExecuteBinaryOpImmediateToAddressDisplacement<Cmp, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {ORI|ANDI|SUBI|ADDI|BTST|EORI|CMPI}.B #imm, (d, Ay, Xn)
        case SizeMode(0u, 6u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteBinaryOpImmediateToAddressIndex<Or, Byte>(m68000, opcode);
                case 1u: return ExecuteBinaryOpImmediateToAddressIndex<And, Byte>(m68000, opcode);
                case 2u: return ExecuteBinaryOpImmediateToAddressIndex<Sub, Byte>(m68000, opcode);
                case 3u: return ExecuteBinaryOpImmediateToAddressIndex<Add, Byte>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToAddressIndex<Btst, Byte>(m68000, opcode);
                case 5u: return ExecuteBinaryOpImmediateToAddressIndex<Eor, Byte>(m68000, opcode);
                case 6u: return ExecuteBinaryOpImmediateToAddressIndex<Cmp, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {ORI|ANDI|SUBI|ADDI|BTST|EORI|CMPI}.B #imm, (address).{W|L}
            // BTST.B #imm, (d, PC)
            // BTST.B #imm, (d, PC, Xn)
        case SizeMode(0u, 7u):
            switch (opcode & RegisterXY(7u, 7u)) {
                // {ORI|ANDI|SUBI|ADDI|BTST|EORI|CMPI}.B #imm, (address).W
                case RegisterXY(0u, 0u): return ExecuteBinaryOpImmediateToShort<Or, Byte>(m68000, opcode);
                case RegisterXY(1u, 0u): return ExecuteBinaryOpImmediateToShort<And, Byte>(m68000, opcode);
                case RegisterXY(2u, 0u): return ExecuteBinaryOpImmediateToShort<Sub, Byte>(m68000, opcode);
                case RegisterXY(3u, 0u): return ExecuteBinaryOpImmediateToShort<Add, Byte>(m68000, opcode);
                case RegisterXY(4u, 0u): return ExecuteBinaryOpImmediateToShort<Btst, Byte>(m68000, opcode);
                case RegisterXY(5u, 0u): return ExecuteBinaryOpImmediateToShort<Eor, Byte>(m68000, opcode);
                case RegisterXY(6u, 0u): return ExecuteBinaryOpImmediateToShort<Cmp, Byte>(m68000, opcode);
                    // {ORI|ANDI|SUBI|ADDI|BTST|EORI|CMPI}.B #imm, (address).L
                case RegisterXY(0u, 1u): return ExecuteBinaryOpImmediateToLong<Or, Byte>(m68000, opcode);
                case RegisterXY(1u, 1u): return ExecuteBinaryOpImmediateToLong<And, Byte>(m68000, opcode);
                case RegisterXY(2u, 1u): return ExecuteBinaryOpImmediateToLong<Sub, Byte>(m68000, opcode);
                case RegisterXY(3u, 1u): return ExecuteBinaryOpImmediateToLong<Add, Byte>(m68000, opcode);
                case RegisterXY(4u, 1u): return ExecuteBinaryOpImmediateToLong<Btst, Byte>(m68000, opcode);
                case RegisterXY(5u, 1u): return ExecuteBinaryOpImmediateToLong<Eor, Byte>(m68000, opcode);
                case RegisterXY(6u, 1u): return ExecuteBinaryOpImmediateToLong<Cmp, Byte>(m68000, opcode);
                    // BTST.B #imm, (d, PC)
                case RegisterXY(4u, 2u): return ExecuteBinaryOpImmediateToPCDisplacement<Btst, Byte>(m68000, opcode);
                    // BTST.B #imm, (d, PC, Xn)
                case RegisterXY(4u, 3u): return ExecuteBinaryOpImmediateToPCIndex<Btst, Byte>(m68000, opcode);
                    // ORI.B #imm, CCR
                case RegisterXY(0u, 4u): return ExecuteBinaryOpImmediateToCCR<OrSR>(m68000);
                    // ANDI.B #imm, CCR
                case RegisterXY(1u, 4u): return ExecuteBinaryOpImmediateToCCR<AndSR>(m68000);
                    // EORI.B #imm, CCR
                case RegisterXY(5u, 4u): return ExecuteBinaryOpImmediateToCCR<EorSR>(m68000);
                    [[unlikely]] default : return ExecuteIllegal(m68000);
            }
            // {ORI|ANDI|SUBI|ADDI|EORI|CMPI}.W #imm, Dy
            // BCHG.L #imm, Dy
        case SizeMode(1u, 0u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteBinaryOpImmediateToDataRegisterY<Or, Word>(m68000, opcode);
                case 1u: return ExecuteBinaryOpImmediateToDataRegisterY<And, Word>(m68000, opcode);
                case 2u: return ExecuteBinaryOpImmediateToDataRegisterY<Sub, Word>(m68000, opcode);
                case 3u: return ExecuteBinaryOpImmediateToDataRegisterY<Add, Word>(m68000, opcode);
                case 4u: return ExecuteBitwiseOpImmediateToDataRegisterY<Bchg, Long>(m68000, opcode);
                case 5u: return ExecuteBinaryOpImmediateToDataRegisterY<Eor, Word>(m68000, opcode);
                case 6u: return ExecuteBinaryOpImmediateToDataRegisterY<Cmp, Word>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {ORI|ANDI|SUBI|ADDI|EORI|CMPI}.W #imm, (Ay)
            // BCHG.B #imm, (Ay)
        case SizeMode(1u, 2u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteBinaryOpImmediateToAddressIndirect<Or, Word>(m68000, opcode);
                case 1u: return ExecuteBinaryOpImmediateToAddressIndirect<And, Word>(m68000, opcode);
                case 2u: return ExecuteBinaryOpImmediateToAddressIndirect<Sub, Word>(m68000, opcode);
                case 3u: return ExecuteBinaryOpImmediateToAddressIndirect<Add, Word>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToAddressIndirect<Bchg, Byte>(m68000, opcode);
                case 5u: return ExecuteBinaryOpImmediateToAddressIndirect<Eor, Word>(m68000, opcode);
                case 6u: return ExecuteBinaryOpImmediateToAddressIndirect<Cmp, Word>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {ORI|ANDI|SUBI|ADDI|EORI|CMPI}.W #imm, (Ay)+
            // BCHG.B #imm, (Ay)+
        case SizeMode(1u, 3u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteBinaryOpImmediateToAddressIncrement<Or, Word>(m68000, opcode);
                case 1u: return ExecuteBinaryOpImmediateToAddressIncrement<And, Word>(m68000, opcode);
                case 2u: return ExecuteBinaryOpImmediateToAddressIncrement<Sub, Word>(m68000, opcode);
                case 3u: return ExecuteBinaryOpImmediateToAddressIncrement<Add, Word>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToAddressIncrement<Bchg, Byte>(m68000, opcode);
                case 5u: return ExecuteBinaryOpImmediateToAddressIncrement<Eor, Word>(m68000, opcode);
                case 6u: return ExecuteBinaryOpImmediateToAddressIncrement<Cmp, Word>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {ORI|ANDI|SUBI|ADDI|EORI|CMPI}.W #imm, -(Ay)
            // BCHG.B #imm, -(Ay)
        case SizeMode(1u, 4u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteBinaryOpImmediateToAddressDecrement<Or, Word>(m68000, opcode);
                case 1u: return ExecuteBinaryOpImmediateToAddressDecrement<And, Word>(m68000, opcode);
                case 2u: return ExecuteBinaryOpImmediateToAddressDecrement<Sub, Word>(m68000, opcode);
                case 3u: return ExecuteBinaryOpImmediateToAddressDecrement<Add, Word>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToAddressDecrement<Bchg, Byte>(m68000, opcode);
                case 5u: return ExecuteBinaryOpImmediateToAddressDecrement<Eor, Word>(m68000, opcode);
                case 6u: return ExecuteBinaryOpImmediateToAddressDecrement<Cmp, Word>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {ORI|ANDI|SUBI|ADDI|EORI|CMPI}.W #imm, (d, Ay)
            // BCHG.B #imm, (d, Ay)
        case SizeMode(1u, 5u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteBinaryOpImmediateToAddressDisplacement<Or, Word>(m68000, opcode);
                case 1u: return ExecuteBinaryOpImmediateToAddressDisplacement<And, Word>(m68000, opcode);
                case 2u: return ExecuteBinaryOpImmediateToAddressDisplacement<Sub, Word>(m68000, opcode);
                case 3u: return ExecuteBinaryOpImmediateToAddressDisplacement<Add, Word>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToAddressDisplacement<Bchg, Byte>(m68000, opcode);
                case 5u: return ExecuteBinaryOpImmediateToAddressDisplacement<Eor, Word>(m68000, opcode);
                case 6u: return ExecuteBinaryOpImmediateToAddressDisplacement<Cmp, Word>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {ORI|ANDI|SUBI|ADDI|EORI|CMPI}.W #imm, (d, Ay, Xn)
            // BCHG.B #imm, (d, Ay, Xn)
        case SizeMode(1u, 6u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteBinaryOpImmediateToAddressIndex<Or, Word>(m68000, opcode);
                case 1u: return ExecuteBinaryOpImmediateToAddressIndex<And, Word>(m68000, opcode);
                case 2u: return ExecuteBinaryOpImmediateToAddressIndex<Sub, Word>(m68000, opcode);
                case 3u: return ExecuteBinaryOpImmediateToAddressIndex<Add, Word>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToAddressIndex<Bchg, Byte>(m68000, opcode);
                case 5u: return ExecuteBinaryOpImmediateToAddressIndex<Eor, Word>(m68000, opcode);
                case 6u: return ExecuteBinaryOpImmediateToAddressIndex<Cmp, Word>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {ORI|ANDI|SUBI|ADDI|EORI|CMPI}.W #imm, (address).{W|L}
            // BCHG.B #imm, (address).{W|L}
        case SizeMode(1u, 7u):
            switch (opcode & RegisterXY(7u, 7u)) {
                // {ORI|ANDI|SUBI|ADDI|BTST|EORI|CMPI}.W #imm, (address).W
                case RegisterXY(0u, 0u): return ExecuteBinaryOpImmediateToShort<Or, Word>(m68000, opcode);
                case RegisterXY(1u, 0u): return ExecuteBinaryOpImmediateToShort<And, Word>(m68000, opcode);
                case RegisterXY(2u, 0u): return ExecuteBinaryOpImmediateToShort<Sub, Word>(m68000, opcode);
                case RegisterXY(3u, 0u): return ExecuteBinaryOpImmediateToShort<Add, Word>(m68000, opcode);
                case RegisterXY(4u, 0u): return ExecuteBinaryOpImmediateToShort<Bchg, Byte>(m68000, opcode);
                case RegisterXY(5u, 0u): return ExecuteBinaryOpImmediateToShort<Eor, Word>(m68000, opcode);
                case RegisterXY(6u, 0u): return ExecuteBinaryOpImmediateToShort<Cmp, Word>(m68000, opcode);
                    // {ORI|ANDI|SUBI|ADDI|BTST|EORI|CMPI}.W #imm, (address).L
                case RegisterXY(0u, 1u): return ExecuteBinaryOpImmediateToLong<Or, Word>(m68000, opcode);
                case RegisterXY(1u, 1u): return ExecuteBinaryOpImmediateToLong<And, Word>(m68000, opcode);
                case RegisterXY(2u, 1u): return ExecuteBinaryOpImmediateToLong<Sub, Word>(m68000, opcode);
                case RegisterXY(3u, 1u): return ExecuteBinaryOpImmediateToLong<Add, Word>(m68000, opcode);
                case RegisterXY(4u, 1u): return ExecuteBinaryOpImmediateToLong<Bchg, Byte>(m68000, opcode);
                case RegisterXY(5u, 1u): return ExecuteBinaryOpImmediateToLong<Eor, Word>(m68000, opcode);
                case RegisterXY(6u, 1u): return ExecuteBinaryOpImmediateToLong<Cmp, Word>(m68000, opcode);
                    // ORI.W #imm, SR
                case RegisterXY(0u, 4u): return ExecuteBinaryOpImmediateToSR<OrSR>(m68000);
                    // ANDI.W #imm, SR
                case RegisterXY(1u, 4u): return ExecuteBinaryOpImmediateToSR<AndSR>(m68000);
                    // EORI.W #imm, SR
                case RegisterXY(5u, 4u): return ExecuteBinaryOpImmediateToSR<EorSR>(m68000);
                    [[unlikely]] default : return ExecuteIllegal(m68000);
            }
            // {ORI|ANDI|SUBI|ADDI|EORI|CMPI}.L #imm, Dy
            // BCLR.L #imm, Dy
        case SizeMode(2u, 0u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteBinaryOpImmediateToDataRegisterY<Or, Long>(m68000, opcode);
                case 1u: return ExecuteBinaryOpImmediateToDataRegisterY<And, Long>(m68000, opcode);
                case 2u: return ExecuteBinaryOpImmediateToDataRegisterY<Sub, Long>(m68000, opcode);
                case 3u: return ExecuteBinaryOpImmediateToDataRegisterY<Add, Long>(m68000, opcode);
                case 4u: return ExecuteBitwiseOpImmediateToDataRegisterY<Bclr, Long>(m68000, opcode);
                case 5u: return ExecuteBinaryOpImmediateToDataRegisterY<Eor, Long>(m68000, opcode);
                case 6u: return ExecuteBinaryOpImmediateToDataRegisterY<Cmp, Long>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {ORI|ANDI|SUBI|ADDI|EORI|CMPI}.L #imm, (Ay)
            // BCLR.B #imm, (Ay)
        case SizeMode(2u, 2u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteBinaryOpImmediateToAddressIndirect<Or, Long>(m68000, opcode);
                case 1u: return ExecuteBinaryOpImmediateToAddressIndirect<And, Long>(m68000, opcode);
                case 2u: return ExecuteBinaryOpImmediateToAddressIndirect<Sub, Long>(m68000, opcode);
                case 3u: return ExecuteBinaryOpImmediateToAddressIndirect<Add, Long>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToAddressIndirect<Bclr, Byte>(m68000, opcode);
                case 5u: return ExecuteBinaryOpImmediateToAddressIndirect<Eor, Long>(m68000, opcode);
                case 6u: return ExecuteBinaryOpImmediateToAddressIndirect<Cmp, Long>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {ORI|ANDI|SUBI|ADDIEORI|CMPI}.L #imm, (Ay)+
            // BCLR.B #imm, (Ay)+
        case SizeMode(2u, 3u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteBinaryOpImmediateToAddressIncrement<Or, Long>(m68000, opcode);
                case 1u: return ExecuteBinaryOpImmediateToAddressIncrement<And, Long>(m68000, opcode);
                case 2u: return ExecuteBinaryOpImmediateToAddressIncrement<Sub, Long>(m68000, opcode);
                case 3u: return ExecuteBinaryOpImmediateToAddressIncrement<Add, Long>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToAddressIncrement<Bclr, Byte>(m68000, opcode);
                case 5u: return ExecuteBinaryOpImmediateToAddressIncrement<Eor, Long>(m68000, opcode);
                case 6u: return ExecuteBinaryOpImmediateToAddressIncrement<Cmp, Long>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {ORI|ANDI|SUBI|ADDI|EORI|CMPI}.L #imm, -(Ay)
            // BCLR.B #imm, -(Ay)
        case SizeMode(2u, 4u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteBinaryOpImmediateToAddressDecrement<Or, Long>(m68000, opcode);
                case 1u: return ExecuteBinaryOpImmediateToAddressDecrement<And, Long>(m68000, opcode);
                case 2u: return ExecuteBinaryOpImmediateToAddressDecrement<Sub, Long>(m68000, opcode);
                case 3u: return ExecuteBinaryOpImmediateToAddressDecrement<Add, Long>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToAddressDecrement<Bclr, Byte>(m68000, opcode);
                case 5u: return ExecuteBinaryOpImmediateToAddressDecrement<Eor, Long>(m68000, opcode);
                case 6u: return ExecuteBinaryOpImmediateToAddressDecrement<Cmp, Long>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {ORI|ANDI|SUBI|ADDI|EORI|CMPI}.L #imm, (d, Ay)
            // BCLR.B #imm, (d, Ay)
        case SizeMode(2u, 5u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteBinaryOpImmediateToAddressDisplacement<Or, Long>(m68000, opcode);
                case 1u: return ExecuteBinaryOpImmediateToAddressDisplacement<And, Long>(m68000, opcode);
                case 2u: return ExecuteBinaryOpImmediateToAddressDisplacement<Sub, Long>(m68000, opcode);
                case 3u: return ExecuteBinaryOpImmediateToAddressDisplacement<Add, Long>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToAddressDisplacement<Bclr, Byte>(m68000, opcode);
                case 5u: return ExecuteBinaryOpImmediateToAddressDisplacement<Eor, Long>(m68000, opcode);
                case 6u: return ExecuteBinaryOpImmediateToAddressDisplacement<Cmp, Long>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {ORI|ANDI|SUBI|ADDI|EORI|CMPI}.L #imm, (d, Ay, Xn)
            // BCLR.B #imm, (d, Ay, Xn)
        case SizeMode(2u, 6u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteBinaryOpImmediateToAddressIndex<Or, Long>(m68000, opcode);
                case 1u: return ExecuteBinaryOpImmediateToAddressIndex<And, Long>(m68000, opcode);
                case 2u: return ExecuteBinaryOpImmediateToAddressIndex<Sub, Long>(m68000, opcode);
                case 3u: return ExecuteBinaryOpImmediateToAddressIndex<Add, Long>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToAddressIndex<Bclr, Byte>(m68000, opcode);
                case 5u: return ExecuteBinaryOpImmediateToAddressIndex<Eor, Long>(m68000, opcode);
                case 6u: return ExecuteBinaryOpImmediateToAddressIndex<Cmp, Long>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {ORI|ANDI|SUBI|ADDI|EORI|CMPI}.L #imm, (address).{W|L}
            // BCLR.B #imm, (address).{W|L}
        case SizeMode(2u, 7u):
            switch (opcode & RegisterXY(7u, 7u)) {
                // {ORI|ANDI|SUBI|ADDI|BTST|EORI|CMPI}.L #imm, (address).L
                case RegisterXY(0u, 0u): return ExecuteBinaryOpImmediateToShort<Or, Long>(m68000, opcode);
                case RegisterXY(1u, 0u): return ExecuteBinaryOpImmediateToShort<And, Long>(m68000, opcode);
                case RegisterXY(2u, 0u): return ExecuteBinaryOpImmediateToShort<Sub, Long>(m68000, opcode);
                case RegisterXY(3u, 0u): return ExecuteBinaryOpImmediateToShort<Add, Long>(m68000, opcode);
                case RegisterXY(4u, 0u): return ExecuteBinaryOpImmediateToShort<Bclr, Byte>(m68000, opcode);
                case RegisterXY(5u, 0u): return ExecuteBinaryOpImmediateToShort<Eor, Long>(m68000, opcode);
                case RegisterXY(6u, 0u): return ExecuteBinaryOpImmediateToShort<Cmp, Long>(m68000, opcode);
                    // {ORI|ANDI|SUBI|ADDI|BTST|EORI|CMPI}.L #imm, (address).L
                case RegisterXY(0u, 1u): return ExecuteBinaryOpImmediateToLong<Or, Long>(m68000, opcode);
                case RegisterXY(1u, 1u): return ExecuteBinaryOpImmediateToLong<And, Long>(m68000, opcode);
                case RegisterXY(2u, 1u): return ExecuteBinaryOpImmediateToLong<Sub, Long>(m68000, opcode);
                case RegisterXY(3u, 1u): return ExecuteBinaryOpImmediateToLong<Add, Long>(m68000, opcode);
                case RegisterXY(4u, 1u): return ExecuteBinaryOpImmediateToLong<Bclr, Byte>(m68000, opcode);
                case RegisterXY(5u, 1u): return ExecuteBinaryOpImmediateToLong<Eor, Long>(m68000, opcode);
                case RegisterXY(6u, 1u): return ExecuteBinaryOpImmediateToLong<Cmp, Long>(m68000, opcode);
                    [[unlikely]] default : return ExecuteIllegal(m68000);
            }
            // BSET.L #imm, Dy
        case SizeMode(3u, 0u):
            switch (OpcodeRegisterX(opcode)) {
                case 4u: return ExecuteBitwiseOpImmediateToDataRegisterY<Bset, Long>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // BSET.B #imm, (Ay)
        case SizeMode(3u, 2u):
            switch (OpcodeRegisterX(opcode)) {
                case 4u: return ExecuteBinaryOpImmediateToAddressIndirect<Bset, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // BSET.B #imm, (Ay)+
        case SizeMode(3u, 3u):
            switch (OpcodeRegisterX(opcode)) {
                case 4u: return ExecuteBinaryOpImmediateToAddressIncrement<Bset, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // BSET.B #imm, -(Ay)
        case SizeMode(3u, 4u):
            switch (OpcodeRegisterX(opcode)) {
                case 4u: return ExecuteBinaryOpImmediateToAddressDecrement<Bset, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // BSET.B #imm, (d, Ay)
        case SizeMode(3u, 5u):
            switch (OpcodeRegisterX(opcode)) {
                case 4u: return ExecuteBinaryOpImmediateToAddressDisplacement<Bset, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // BSET.B #imm, (d, Ay, Xn)
        case SizeMode(3u, 6u):
            switch (OpcodeRegisterX(opcode)) {
                case 4u: return ExecuteBinaryOpImmediateToAddressIndex<Bset, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // BSET.B #imm, (address).{W|L}
        case SizeMode(3u, 7u):
            switch (opcode & RegisterXY(7u, 7u)) {
                // BSET.B #imm, (address).W
                case RegisterXY(4u, 0u): return ExecuteBinaryOpImmediateToShort<Bset, Byte>(m68000, opcode);
                    // BSET.B #imm, (address).L
                case RegisterXY(4u, 1u): return ExecuteBinaryOpImmediateToLong<Bset, Byte>(m68000, opcode);
                    [[unlikely]] default : return ExecuteIllegal(m68000);
            }
            // BTST.{B|L} Dx, <ea>, MOVEP.W (d, Ay), Dx
        case SizeMode(4u, 0u): return ExecuteBinaryOpDataRegisterXToDataRegisterY<Btst, Long>(m68000, opcode);
        case SizeMode(4u, 1u): return ExecuteMovepToDataRegisterWord(m68000, opcode);
        case SizeMode(4u, 2u): return ExecuteBinaryOpDataRegisterToAddressIndirect<Btst, Byte>(m68000, opcode);
        case SizeMode(4u, 3u): return ExecuteBinaryOpDataRegisterToAddressIncrement<Btst, Byte>(m68000, opcode);
        case SizeMode(4u, 4u): return ExecuteBinaryOpDataRegisterToAddressDecrement<Btst, Byte>(m68000, opcode);
        case SizeMode(4u, 5u): return ExecuteBinaryOpDataRegisterToAddressDisplacement<Btst, Byte>(m68000, opcode);
        case SizeMode(4u, 6u): return ExecuteBinaryOpDataRegisterToAddressIndex<Btst, Byte>(m68000, opcode);
        case SizeMode(4u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpDataRegisterToShort<Btst, Byte>(m68000, opcode);
                case 1u: return ExecuteBinaryOpDataRegisterToLong<Btst, Byte>(m68000, opcode);
                case 2u: return ExecuteBinaryOpDataRegisterToPCDisplacement<Btst, Byte>(m68000, opcode);
                case 3u: return ExecuteBinaryOpDataRegisterToPCIndex<Btst, Byte>(m68000, opcode);
                case 4u: return ExecuteBinaryOpDataRegisterToImmediate<Btst, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // BCHG.{B|L} Dx, <ea>, , MOVEP.L(d, Ay), Dx
        case SizeMode(5u, 0u): return ExecuteBinaryOpDataRegisterXToDataRegisterY<Bchg, Long>(m68000, opcode);
        case SizeMode(5u, 1u): return ExecuteMovepToDataRegisterLong(m68000, opcode);
        case SizeMode(5u, 2u): return ExecuteBinaryOpDataRegisterToAddressIndirect<Bchg, Byte>(m68000, opcode);
        case SizeMode(5u, 3u): return ExecuteBinaryOpDataRegisterToAddressIncrement<Bchg, Byte>(m68000, opcode);
        case SizeMode(5u, 4u): return ExecuteBinaryOpDataRegisterToAddressDecrement<Bchg, Byte>(m68000, opcode);
        case SizeMode(5u, 5u): return ExecuteBinaryOpDataRegisterToAddressDisplacement<Bchg, Byte>(m68000, opcode);
        case SizeMode(5u, 6u): return ExecuteBinaryOpDataRegisterToAddressIndex<Bchg, Byte>(m68000, opcode);
        case SizeMode(5u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpDataRegisterToShort<Bchg, Byte>(m68000, opcode);
                case 1u: return ExecuteBinaryOpDataRegisterToLong<Bchg, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // BCLR.{B|L} Dx, <ea>, MOVEP.W Dx, (d, Ay)
        case SizeMode(6u, 0u): return ExecuteBinaryOpDataRegisterXToDataRegisterY<Bclr, Long>(m68000, opcode);
        case SizeMode(6u, 1u): return ExecuteMovepToAddressDisplacementWord(m68000, opcode);
        case SizeMode(6u, 2u): return ExecuteBinaryOpDataRegisterToAddressIndirect<Bclr, Byte>(m68000, opcode);
        case SizeMode(6u, 3u): return ExecuteBinaryOpDataRegisterToAddressIncrement<Bclr, Byte>(m68000, opcode);
        case SizeMode(6u, 4u): return ExecuteBinaryOpDataRegisterToAddressDecrement<Bclr, Byte>(m68000, opcode);
        case SizeMode(6u, 5u): return ExecuteBinaryOpDataRegisterToAddressDisplacement<Bclr, Byte>(m68000, opcode);
        case SizeMode(6u, 6u): return ExecuteBinaryOpDataRegisterToAddressIndex<Bclr, Byte>(m68000, opcode);
        case SizeMode(6u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpDataRegisterToShort<Bclr, Byte>(m68000, opcode);
                case 1u: return ExecuteBinaryOpDataRegisterToLong<Bclr, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // BSET.{B|L} Dx, <ea>, MOVEP.L Dx, (d, Ay)
        case SizeMode(7u, 0u): return ExecuteBinaryOpDataRegisterXToDataRegisterY<Bset, Long>(m68000, opcode);
        case SizeMode(7u, 1u): return ExecuteMovepToAddressDisplacementLong(m68000, opcode);
        case SizeMode(7u, 2u): return ExecuteBinaryOpDataRegisterToAddressIndirect<Bset, Byte>(m68000, opcode);
        case SizeMode(7u, 3u): return ExecuteBinaryOpDataRegisterToAddressIncrement<Bset, Byte>(m68000, opcode);
        case SizeMode(7u, 4u): return ExecuteBinaryOpDataRegisterToAddressDecrement<Bset, Byte>(m68000, opcode);
        case SizeMode(7u, 5u): return ExecuteBinaryOpDataRegisterToAddressDisplacement<Bset, Byte>(m68000, opcode);
        case SizeMode(7u, 6u): return ExecuteBinaryOpDataRegisterToAddressIndex<Bset, Byte>(m68000, opcode);
        case SizeMode(7u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpDataRegisterToShort<Bset, Byte>(m68000, opcode);
                case 1u: return ExecuteBinaryOpDataRegisterToLong<Bset, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            [[unlikely]] default: return ExecuteIllegal(m68000);
    }
}

template<typename T>
auto ExecuteMove(M68000& m68000, uint32_t opcode) {
    using namespace addressing::move;
    switch (opcode & SizeMode(7u, 7u)) {
        // MOVE.{B|W|L} <ea>, Dx
        case SizeMode(0u, 0u): return ExecuteMoveOpToDataRegister<SourceDataRegister, T>(m68000, opcode);
        case SizeMode(0u, 1u):
            if constexpr(std::is_same_v<T, Byte>) {
                return ExecuteIllegal(m68000);
            }
            return ExecuteMoveOpToDataRegister<SourceAddressRegister, T>(m68000, opcode);
        case SizeMode(0u, 2u): return ExecuteMoveOpToDataRegister<SourceAddressIndirect, T>(m68000, opcode);
        case SizeMode(0u, 3u): return ExecuteMoveOpToDataRegister<SourceAddressIncrement, T>(m68000, opcode);
        case SizeMode(0u, 4u): return ExecuteMoveOpToDataRegister<SourceAddressDecrement, T>(m68000, opcode);
        case SizeMode(0u, 5u): return ExecuteMoveOpToDataRegister<SourceAddressDisplacement, T>(m68000, opcode);
        case SizeMode(0u, 6u): return ExecuteMoveOpToDataRegister<SourceAddressIndex, T>(m68000, opcode);
        case SizeMode(0u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteMoveOpToDataRegister<SourceShort, T>(m68000, opcode);
                case 1u: return ExecuteMoveOpToDataRegister<SourceLong, T>(m68000, opcode);
                case 2u: return ExecuteMoveOpToDataRegister<SourcePCDisplacement, T>(m68000, opcode);
                case 3u: return ExecuteMoveOpToDataRegister<SourcePCIndex, T>(m68000, opcode);
                case 4u: return ExecuteMoveOpToDataRegister<SourceImmediate, T>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // MOVEA.{W|L} <ea>, Ax
        case SizeMode(1u, 0u): return ExecuteMoveOpToAddressRegister<SourceDataRegister, T>(m68000, opcode);
        case SizeMode(1u, 1u): return ExecuteMoveOpToAddressRegister<SourceAddressRegister, T>(m68000, opcode);
        case SizeMode(1u, 2u): return ExecuteMoveOpToAddressRegister<SourceAddressIndirect, T>(m68000, opcode);
        case SizeMode(1u, 3u): return ExecuteMoveOpToAddressRegister<SourceAddressIncrement, T>(m68000, opcode);
        case SizeMode(1u, 4u): return ExecuteMoveOpToAddressRegister<SourceAddressDecrement, T>(m68000, opcode);
        case SizeMode(1u, 5u): return ExecuteMoveOpToAddressRegister<SourceAddressDisplacement, T>(m68000, opcode);
        case SizeMode(1u, 6u): return ExecuteMoveOpToAddressRegister<SourceAddressIndex, T>(m68000, opcode);
        case SizeMode(1u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteMoveOpToAddressRegister<SourceShort, T>(m68000, opcode);
                case 1u: return ExecuteMoveOpToAddressRegister<SourceLong, T>(m68000, opcode);
                case 2u: return ExecuteMoveOpToAddressRegister<SourcePCDisplacement, T>(m68000, opcode);
                case 3u: return ExecuteMoveOpToAddressRegister<SourcePCIndex, T>(m68000, opcode);
                case 4u: return ExecuteMoveOpToAddressRegister<SourceImmediate, T>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // MOVE.{B|W|L} <ea>, (Ax)
        case SizeMode(2u, 0u): return ExecuteMoveOpToAddressIndirect<SourceDataRegister, T>(m68000, opcode);
        case SizeMode(2u, 1u):
            if constexpr(std::is_same_v<T, Byte>) {
                return ExecuteIllegal(m68000);
            }
            return ExecuteMoveOpToAddressIndirect<SourceAddressRegister, T>(m68000, opcode);
        case SizeMode(2u, 2u): return ExecuteMoveOpToAddressIndirect<SourceAddressIndirect, T>(m68000, opcode);
        case SizeMode(2u, 3u): return ExecuteMoveOpToAddressIndirect<SourceAddressIncrement, T>(m68000, opcode);
        case SizeMode(2u, 4u): return ExecuteMoveOpToAddressIndirect<SourceAddressDecrement, T>(m68000, opcode);
        case SizeMode(2u, 5u): return ExecuteMoveOpToAddressIndirect<SourceAddressDisplacement, T>(m68000, opcode);
        case SizeMode(2u, 6u): return ExecuteMoveOpToAddressIndirect<SourceAddressIndex, T>(m68000, opcode);
        case SizeMode(2u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteMoveOpToAddressIndirect<SourceShort, T>(m68000, opcode);
                case 1u: return ExecuteMoveOpToAddressIndirect<SourceLong, T>(m68000, opcode);
                case 2u: return ExecuteMoveOpToAddressIndirect<SourcePCDisplacement, T>(m68000, opcode);
                case 3u: return ExecuteMoveOpToAddressIndirect<SourcePCIndex, T>(m68000, opcode);
                case 4u: return ExecuteMoveOpToAddressIndirect<SourceImmediate, T>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // MOVE.{B|W|L} <ea>, (Ax)+
        case SizeMode(3u, 0u): return ExecuteMoveOpToAddressIncrement<SourceDataRegister, T>(m68000, opcode);
        case SizeMode(3u, 1u):
            if constexpr(std::is_same_v<T, Byte>) {
                return ExecuteIllegal(m68000);
            }
            return ExecuteMoveOpToAddressIncrement<SourceAddressRegister, T>(m68000, opcode);
        case SizeMode(3u, 2u): return ExecuteMoveOpToAddressIncrement<SourceAddressIndirect, T>(m68000, opcode);
        case SizeMode(3u, 3u): return ExecuteMoveOpToAddressIncrement<SourceAddressIncrement, T>(m68000, opcode);
        case SizeMode(3u, 4u): return ExecuteMoveOpToAddressIncrement<SourceAddressDecrement, T>(m68000, opcode);
        case SizeMode(3u, 5u): return ExecuteMoveOpToAddressIncrement<SourceAddressDisplacement, T>(m68000, opcode);
        case SizeMode(3u, 6u): return ExecuteMoveOpToAddressIncrement<SourceAddressIndex, T>(m68000, opcode);
        case SizeMode(3u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteMoveOpToAddressIncrement<SourceShort, T>(m68000, opcode);
                case 1u: return ExecuteMoveOpToAddressIncrement<SourceLong, T>(m68000, opcode);
                case 2u: return ExecuteMoveOpToAddressIncrement<SourcePCDisplacement, T>(m68000, opcode);
                case 3u: return ExecuteMoveOpToAddressIncrement<SourcePCIndex, T>(m68000, opcode);
                case 4u: return ExecuteMoveOpToAddressIncrement<SourceImmediate, T>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // MOVE.{B|W|L} <ea>, -(Ax)
        case SizeMode(4u, 0u): return ExecuteMoveOpToAddressDecrement<SourceDataRegister, T>(m68000, opcode);
        case SizeMode(4u, 1u):
            if constexpr(std::is_same_v<T, Byte>) {
                return ExecuteIllegal(m68000);
            }
            return ExecuteMoveOpToAddressDecrement<SourceAddressRegister, T>(m68000, opcode);
        case SizeMode(4u, 2u): return ExecuteMoveOpToAddressDecrement<SourceAddressIndirect, T>(m68000, opcode);
        case SizeMode(4u, 3u): return ExecuteMoveOpToAddressDecrement<SourceAddressIncrement, T>(m68000, opcode);
        case SizeMode(4u, 4u): return ExecuteMoveOpToAddressDecrement<SourceAddressDecrement, T>(m68000, opcode);
        case SizeMode(4u, 5u): return ExecuteMoveOpToAddressDecrement<SourceAddressDisplacement, T>(m68000, opcode);
        case SizeMode(4u, 6u): return ExecuteMoveOpToAddressDecrement<SourceAddressIndex, T>(m68000, opcode);
        case SizeMode(4u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteMoveOpToAddressDecrement<SourceShort, T>(m68000, opcode);
                case 1u: return ExecuteMoveOpToAddressDecrement<SourceLong, T>(m68000, opcode);
                case 2u: return ExecuteMoveOpToAddressDecrement<SourcePCDisplacement, T>(m68000, opcode);
                case 3u: return ExecuteMoveOpToAddressDecrement<SourcePCIndex, T>(m68000, opcode);
                case 4u: return ExecuteMoveOpToAddressDecrement<SourceImmediate, T>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // MOVE.{B|W|L} <ea>, (d, Ax)
        case SizeMode(5u, 0u): return ExecuteMoveOpToAddressDisplacement<SourceDataRegister, T>(m68000, opcode);
        case SizeMode(5u, 1u):
            if constexpr(std::is_same_v<T, Byte>) {
                return ExecuteIllegal(m68000);
            }
            return ExecuteMoveOpToAddressDisplacement<SourceAddressRegister, T>(m68000, opcode);
        case SizeMode(5u, 2u): return ExecuteMoveOpToAddressDisplacement<SourceAddressIndirect, T>(m68000, opcode);
        case SizeMode(5u, 3u): return ExecuteMoveOpToAddressDisplacement<SourceAddressIncrement, T>(m68000, opcode);
        case SizeMode(5u, 4u): return ExecuteMoveOpToAddressDisplacement<SourceAddressDecrement, T>(m68000, opcode);
        case SizeMode(5u, 5u): return ExecuteMoveOpToAddressDisplacement<SourceAddressDisplacement, T>(m68000, opcode);
        case SizeMode(5u, 6u): return ExecuteMoveOpToAddressDisplacement<SourceAddressIndex, T>(m68000, opcode);
        case SizeMode(5u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteMoveOpToAddressDisplacement<SourceShort, T>(m68000, opcode);
                case 1u: return ExecuteMoveOpToAddressDisplacement<SourceLong, T>(m68000, opcode);
                case 2u: return ExecuteMoveOpToAddressDisplacement<SourcePCDisplacement, T>(m68000, opcode);
                case 3u: return ExecuteMoveOpToAddressDisplacement<SourcePCIndex, T>(m68000, opcode);
                case 4u: return ExecuteMoveOpToAddressDisplacement<SourceImmediate, T>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // MOVE.{B|W|L} <ea>, (d, Ax, Xn)
        case SizeMode(6u, 0u): return ExecuteMoveOpToAddressIndex<SourceDataRegister, T>(m68000, opcode);
        case SizeMode(6u, 1u):
            if constexpr(std::is_same_v<T, Byte>) {
                return ExecuteIllegal(m68000);
            }
            return ExecuteMoveOpToAddressIndex<SourceAddressRegister, T>(m68000, opcode);
        case SizeMode(6u, 2u): return ExecuteMoveOpToAddressIndex<SourceAddressIndirect, T>(m68000, opcode);
        case SizeMode(6u, 3u): return ExecuteMoveOpToAddressIndex<SourceAddressIncrement, T>(m68000, opcode);
        case SizeMode(6u, 4u): return ExecuteMoveOpToAddressIndex<SourceAddressDecrement, T>(m68000, opcode);
        case SizeMode(6u, 5u): return ExecuteMoveOpToAddressIndex<SourceAddressDisplacement, T>(m68000, opcode);
        case SizeMode(6u, 6u): return ExecuteMoveOpToAddressIndex<SourceAddressIndex, T>(m68000, opcode);
        case SizeMode(6u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteMoveOpToAddressIndex<SourceShort, T>(m68000, opcode);
                case 1u: return ExecuteMoveOpToAddressIndex<SourceLong, T>(m68000, opcode);
                case 2u: return ExecuteMoveOpToAddressIndex<SourcePCDisplacement, T>(m68000, opcode);
                case 3u: return ExecuteMoveOpToAddressIndex<SourcePCIndex, T>(m68000, opcode);
                case 4u: return ExecuteMoveOpToAddressIndex<SourceImmediate, T>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // MOVE.{B|W|L} Dy, (address).{W|L}
        case SizeMode(7u, 0u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteMoveOpToShort<SourceDataRegister, T>(m68000, opcode);
                case 1u: return ExecuteMoveOpRegisterToLong<SourceDataRegister, T>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // MOVE.{W|L} Ay, (address).{W|L}
        case SizeMode(7u, 1u):
            if constexpr(std::is_same_v<T, Byte>) {
                return ExecuteIllegal(m68000);
            }
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteMoveOpToShort<SourceAddressRegister, T>(m68000, opcode);
                case 1u: return ExecuteMoveOpRegisterToLong<SourceAddressRegister, T>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // MOVE.{B|W|L} (Ay), (address).{W|L}
        case SizeMode(7u, 2u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteMoveOpToShort<SourceAddressIndirect, T>(m68000, opcode);
                case 1u: return ExecuteMoveOpToLong<SourceAddressIndirect, T>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // MOVE.{B|W|L} (Ay)+, (address).{W|L}
        case SizeMode(7u, 3u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteMoveOpToShort<SourceAddressIncrement, T>(m68000, opcode);
                case 1u: return ExecuteMoveOpToLong<SourceAddressIncrement, T>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // MOVE.{B|W|L} -(Ay), (address).{W|L}
        case SizeMode(7u, 4u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteMoveOpToShort<SourceAddressDecrement, T>(m68000, opcode);
                case 1u: return ExecuteMoveOpToLong<SourceAddressDecrement, T>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // MOVE.{B|W|L} (d, Ay), (address).{W|L}
        case SizeMode(7u, 5u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteMoveOpToShort<SourceAddressDisplacement, T>(m68000, opcode);
                case 1u: return ExecuteMoveOpToLong<SourceAddressDisplacement, T>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // MOVE.{B|W|L} (d, Ay, Xn), (address).{W|L}
        case SizeMode(7u, 6u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteMoveOpToShort<SourceAddressIndex, T>(m68000, opcode);
                case 1u: return ExecuteMoveOpToLong<SourceAddressIndex, T>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // MOVE.{B|W|L} (address).{W|L}, (address).{W|L}
            // MOVE.{B|W|L} (d, PC), (address).{W|L}
            // MOVE.{B|W|L} (d, PC, Xn), (address).{W|L}
            // MOVE.{B|W|L} #imm, (address).{W|L}
        case SizeMode(7u, 7u):
            switch (opcode & RegisterXY(7u, 7u)) {
                case RegisterXY(0u, 0u): return ExecuteMoveOpToShort<SourceShort, T>(m68000, opcode);
                case RegisterXY(0u, 1u): return ExecuteMoveOpToShort<SourceLong, T>(m68000, opcode);
                case RegisterXY(0u, 2u): return ExecuteMoveOpToShort<SourcePCDisplacement, T>(m68000, opcode);
                case RegisterXY(0u, 3u): return ExecuteMoveOpToShort<SourcePCIndex, T>(m68000, opcode);
                case RegisterXY(0u, 4u): return ExecuteMoveOpToShort<SourceImmediate, T>(m68000, opcode);
                case RegisterXY(1u, 0u): return ExecuteMoveOpToLong<SourceShort, T>(m68000, opcode);
                case RegisterXY(1u, 1u): return ExecuteMoveOpToLong<SourceLong, T>(m68000, opcode);
                case RegisterXY(1u, 2u): return ExecuteMoveOpToLong<SourcePCDisplacement, T>(m68000, opcode);
                case RegisterXY(1u, 3u): return ExecuteMoveOpToLong<SourcePCIndex, T>(m68000, opcode);
                case RegisterXY(1u, 4u): return ExecuteMoveOpToLong<SourceImmediate, T>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            [[unlikely]] default: return ExecuteIllegal(m68000);
    }
}

auto ExecuteLine1(M68000& m68000, uint32_t opcode) {
    ExecuteMove<Byte>(m68000, opcode);
}

auto ExecuteLine2(M68000& m68000, uint32_t opcode) {
    ExecuteMove<Long>(m68000, opcode);
}

auto ExecuteLine3(M68000& m68000, uint32_t opcode) {
    ExecuteMove<Word>(m68000, opcode);
}

auto ExecuteLine4(M68000& m68000, uint32_t opcode) {
    using namespace addressing::single;
    using namespace addressing::check;
    using namespace addressing::ccr;
    switch (opcode & SizeMode(7u, 7u)) {
        // {NEGX|CLR|NEG|NOT|NBCD|TST}.B Dy
        case SizeMode(0u, 0u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteUnaryOpToDataRegister<Negx, Byte>(m68000, opcode);
                case 1u: return ExecuteUnaryOpToDataRegister<Clr, Byte>(m68000, opcode);
                case 2u: return ExecuteUnaryOpToDataRegister<Neg, Byte>(m68000, opcode);
                case 3u: return ExecuteUnaryOpToDataRegister<Not, Byte>(m68000, opcode);
                case 4u: return ExecuteUnaryOpToDataRegister<Nbcd, Byte>(m68000, opcode);
                case 5u: return ExecuteUnaryOpToDataRegister<Tst, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {NEGX|CLR|NEG|NOT|NBCD|TST}.B (Ay)
        case SizeMode(0u, 2u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteUnaryOpToAddressIndirect<Negx, Byte>(m68000, opcode);
                case 1u: return ExecuteUnaryOpToAddressIndirect<Clr, Byte>(m68000, opcode);
                case 2u: return ExecuteUnaryOpToAddressIndirect<Neg, Byte>(m68000, opcode);
                case 3u: return ExecuteUnaryOpToAddressIndirect<Not, Byte>(m68000, opcode);
                case 4u: return ExecuteUnaryOpToAddressIndirect<Nbcd, Byte>(m68000, opcode);
                case 5u: return ExecuteUnaryOpToAddressIndirect<Tst, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {NEGX|CLR|NEG|NOT|NBCD|TST}.B (Ay)+
        case SizeMode(0u, 3u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteUnaryOpToAddressIncrement<Negx, Byte>(m68000, opcode);
                case 1u: return ExecuteUnaryOpToAddressIncrement<Clr, Byte>(m68000, opcode);
                case 2u: return ExecuteUnaryOpToAddressIncrement<Neg, Byte>(m68000, opcode);
                case 3u: return ExecuteUnaryOpToAddressIncrement<Not, Byte>(m68000, opcode);
                case 4u: return ExecuteUnaryOpToAddressIncrement<Nbcd, Byte>(m68000, opcode);
                case 5u: return ExecuteUnaryOpToAddressIncrement<Tst, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {NEGX|CLR|NEG|NOT|NBCD|TST}.B -(Ay)
        case SizeMode(0u, 4u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteUnaryOpToAddressDecrement<Negx, Byte>(m68000, opcode);
                case 1u: return ExecuteUnaryOpToAddressDecrement<Clr, Byte>(m68000, opcode);
                case 2u: return ExecuteUnaryOpToAddressDecrement<Neg, Byte>(m68000, opcode);
                case 3u: return ExecuteUnaryOpToAddressDecrement<Not, Byte>(m68000, opcode);
                case 4u: return ExecuteUnaryOpToAddressDecrement<Nbcd, Byte>(m68000, opcode);
                case 5u: return ExecuteUnaryOpToAddressDecrement<Tst, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {NEGX|CLR|NEG|NOT|NBCD|TST}.B (d, Ay)
        case SizeMode(0u, 5u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteUnaryOpToAddressDisplacement<Negx, Byte>(m68000, opcode);
                case 1u: return ExecuteUnaryOpToAddressDisplacement<Clr, Byte>(m68000, opcode);
                case 2u: return ExecuteUnaryOpToAddressDisplacement<Neg, Byte>(m68000, opcode);
                case 3u: return ExecuteUnaryOpToAddressDisplacement<Not, Byte>(m68000, opcode);
                case 4u: return ExecuteUnaryOpToAddressDisplacement<Nbcd, Byte>(m68000, opcode);
                case 5u: return ExecuteUnaryOpToAddressDisplacement<Tst, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {NEGX|CLR|NEG|NOT|NBCD|TST}.B (d, Ay, Xn)
        case SizeMode(0u, 6u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteUnaryOpToAddressIndex<Negx, Byte>(m68000, opcode);
                case 1u: return ExecuteUnaryOpToAddressIndex<Clr, Byte>(m68000, opcode);
                case 2u: return ExecuteUnaryOpToAddressIndex<Neg, Byte>(m68000, opcode);
                case 3u: return ExecuteUnaryOpToAddressIndex<Not, Byte>(m68000, opcode);
                case 4u: return ExecuteUnaryOpToAddressIndex<Nbcd, Byte>(m68000, opcode);
                case 5u: return ExecuteUnaryOpToAddressIndex<Tst, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {NEGX|CLR|NEG|NOT|NBCD|TST}.B (address).{W|L}
        case SizeMode(0u, 7u):
            switch (opcode & RegisterXY(7u, 7u)) {
                case RegisterXY(0u, 0u): return ExecuteUnaryOpToShort<Negx, Byte>(m68000, opcode);
                case RegisterXY(1u, 0u): return ExecuteUnaryOpToShort<Clr, Byte>(m68000, opcode);
                case RegisterXY(2u, 0u): return ExecuteUnaryOpToShort<Neg, Byte>(m68000, opcode);
                case RegisterXY(3u, 0u): return ExecuteUnaryOpToShort<Not, Byte>(m68000, opcode);
                case RegisterXY(4u, 0u): return ExecuteUnaryOpToShort<Nbcd, Byte>(m68000, opcode);
                case RegisterXY(5u, 0u): return ExecuteUnaryOpToShort<Tst, Byte>(m68000, opcode);
                    //
                case RegisterXY(0u, 1u): return ExecuteUnaryOpToLong<Negx, Byte>(m68000, opcode);
                case RegisterXY(1u, 1u): return ExecuteUnaryOpToLong<Clr, Byte>(m68000, opcode);
                case RegisterXY(2u, 1u): return ExecuteUnaryOpToLong<Neg, Byte>(m68000, opcode);
                case RegisterXY(3u, 1u): return ExecuteUnaryOpToLong<Not, Byte>(m68000, opcode);
                case RegisterXY(4u, 1u): return ExecuteUnaryOpToLong<Nbcd, Byte>(m68000, opcode);
                case RegisterXY(5u, 1u): return ExecuteUnaryOpToLong<Tst, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {NEGX|CLR|NEG|NOT|SWAP|TST|TRAP}.W Dy
        case SizeMode(1u, 0u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteUnaryOpToDataRegister<Negx, Word>(m68000, opcode);
                case 1u: return ExecuteUnaryOpToDataRegister<Clr, Word>(m68000, opcode);
                case 2u: return ExecuteUnaryOpToDataRegister<Neg, Word>(m68000, opcode);
                case 3u: return ExecuteUnaryOpToDataRegister<Not, Word>(m68000, opcode);
                case 4u: return ExecuteSwapToDataRegister(m68000, opcode);
                case 5u: return ExecuteUnaryOpToDataRegister<Tst, Word>(m68000, opcode);
                case 7u: return ExecuteTrap(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // TRAP.W Ay
        case SizeMode(1u, 1u):
            switch (OpcodeRegisterX(opcode)) {
                case 7u: return ExecuteTrap(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {NEGX|CLR|NEG|NOT|PEA|TST|LINK}.W (Ay)
        case SizeMode(1u, 2u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteUnaryOpToAddressIndirect<Negx, Word>(m68000, opcode);
                case 1u: return ExecuteUnaryOpToAddressIndirect<Clr, Word>(m68000, opcode);
                case 2u: return ExecuteUnaryOpToAddressIndirect<Neg, Word>(m68000, opcode);
                case 3u: return ExecuteUnaryOpToAddressIndirect<Not, Word>(m68000, opcode);
                case 4u: return ExecutePeaAddressIndirect(m68000, opcode);
                case 5u: return ExecuteUnaryOpToAddressIndirect<Tst, Word>(m68000, opcode);
                case 7u: return ExecuteLink(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {NEGX|CLR|NEG|NOT|???|TST|UNLK}.W (Ay)+
        case SizeMode(1u, 3u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteUnaryOpToAddressIncrement<Negx, Word>(m68000, opcode);
                case 1u: return ExecuteUnaryOpToAddressIncrement<Clr, Word>(m68000, opcode);
                case 2u: return ExecuteUnaryOpToAddressIncrement<Neg, Word>(m68000, opcode);
                case 3u: return ExecuteUnaryOpToAddressIncrement<Not, Word>(m68000, opcode);
                case 5u: return ExecuteUnaryOpToAddressIncrement<Tst, Word>(m68000, opcode);
                case 7u: return ExecuteUnlk(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {NEGX|CLR|NEG|NOT|???|TST|MOVE USP}.W -(Ay)
        case SizeMode(1u, 4u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteUnaryOpToAddressDecrement<Negx, Word>(m68000, opcode);
                case 1u: return ExecuteUnaryOpToAddressDecrement<Clr, Word>(m68000, opcode);
                case 2u: return ExecuteUnaryOpToAddressDecrement<Neg, Word>(m68000, opcode);
                case 3u: return ExecuteUnaryOpToAddressDecrement<Not, Word>(m68000, opcode);
                case 5u: return ExecuteUnaryOpToAddressDecrement<Tst, Word>(m68000, opcode);
                case 7u: return ExecuteMoveUspToUsp(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {NEGX|CLR|NEG|NOT|PEA|TST|MOVE USP}.W (d, Ay)
        case SizeMode(1u, 5u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteUnaryOpToAddressDisplacement<Negx, Word>(m68000, opcode);
                case 1u: return ExecuteUnaryOpToAddressDisplacement<Clr, Word>(m68000, opcode);
                case 2u: return ExecuteUnaryOpToAddressDisplacement<Neg, Word>(m68000, opcode);
                case 3u: return ExecuteUnaryOpToAddressDisplacement<Not, Word>(m68000, opcode);
                case 4u: return ExecutePeaAddressDisplacement(m68000, opcode);
                case 5u: return ExecuteUnaryOpToAddressDisplacement<Tst, Word>(m68000, opcode);
                case 7u: return ExecuteMoveUspToRegister(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {NEGX|CLR|NEG|NOT|PEA|TST}.W (d, Ay, Xn)
        case SizeMode(1u, 6u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteUnaryOpToAddressIndex<Negx, Word>(m68000, opcode);
                case 1u: return ExecuteUnaryOpToAddressIndex<Clr, Word>(m68000, opcode);
                case 2u: return ExecuteUnaryOpToAddressIndex<Neg, Word>(m68000, opcode);
                case 3u: return ExecuteUnaryOpToAddressIndex<Not, Word>(m68000, opcode);
                case 4u: return ExecutePeaAddressIndex(m68000, opcode);
                case 5u: return ExecuteUnaryOpToAddressIndex<Tst, Word>(m68000, opcode);
                case 7u:
                    switch (OpcodeRegisterY(opcode)) {
                        case 0u: return ExecuteReset(m68000);
                        case 1u: return ExecuteNop(m68000);
                        case 2u: return ExecuteStop(m68000);
                        case 3u: return ExecuteRte(m68000);
                        case 5u: return ExecuteRts(m68000);
                        case 6u: return ExecuteTrapv(m68000);
                        case 7u: return ExecuteRtr(m68000);
                            [[unlikely]] default: return ExecuteIllegal(m68000);
                    }
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {NEGX|CLR|NEG|NOT|PEA|TST}.W (address).{W|L}
        case SizeMode(1u, 7u):
            switch (opcode & RegisterXY(7u, 7u)) {
                case RegisterXY(0u, 0u): return ExecuteUnaryOpToShort<Negx, Word>(m68000, opcode);
                case RegisterXY(1u, 0u): return ExecuteUnaryOpToShort<Clr, Word>(m68000, opcode);
                case RegisterXY(2u, 0u): return ExecuteUnaryOpToShort<Neg, Word>(m68000, opcode);
                case RegisterXY(3u, 0u): return ExecuteUnaryOpToShort<Not, Word>(m68000, opcode);
                case RegisterXY(4u, 0u): return ExecutePeaShort(m68000, opcode);
                case RegisterXY(5u, 0u): return ExecuteUnaryOpToShort<Tst, Word>(m68000, opcode);
                    //
                case RegisterXY(0u, 1u): return ExecuteUnaryOpToLong<Negx, Word>(m68000, opcode);
                case RegisterXY(1u, 1u): return ExecuteUnaryOpToLong<Clr, Word>(m68000, opcode);
                case RegisterXY(2u, 1u): return ExecuteUnaryOpToLong<Neg, Word>(m68000, opcode);
                case RegisterXY(3u, 1u): return ExecuteUnaryOpToLong<Not, Word>(m68000, opcode);
                case RegisterXY(4u, 1u): return ExecutePeaLong(m68000, opcode);
                case RegisterXY(5u, 1u): return ExecuteUnaryOpToLong<Tst, Word>(m68000, opcode);
                    //
                case RegisterXY(4u, 2u): return ExecutePeaPCDisplacement(m68000, opcode);
                    //
                case RegisterXY(4u, 3u): return ExecutePeaPCIndex(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {NEGX|CLR|NEG|NOT|EXT|TST}.L Dy
        case SizeMode(2u, 0u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteUnaryOpToDataRegister<Negx, Long>(m68000, opcode);
                case 1u: return ExecuteUnaryOpToDataRegister<Clr, Long>(m68000, opcode);
                case 2u: return ExecuteUnaryOpToDataRegister<Neg, Long>(m68000, opcode);
                case 4u: return ExecuteExtToDataRegister<Word>(m68000, opcode);
                case 3u: return ExecuteUnaryOpToDataRegister<Not, Long>(m68000, opcode);
                case 5u: return ExecuteUnaryOpToDataRegister<Tst, Long>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {NEGX|CLR|NEG|NOT|MOVEM|TST|JSR}.L (Ay)
        case SizeMode(2u, 2u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteUnaryOpToAddressIndirect<Negx, Long>(m68000, opcode);
                case 1u: return ExecuteUnaryOpToAddressIndirect<Clr, Long>(m68000, opcode);
                case 2u: return ExecuteUnaryOpToAddressIndirect<Neg, Long>(m68000, opcode);
                case 3u: return ExecuteUnaryOpToAddressIndirect<Not, Long>(m68000, opcode);
                case 4u: return ExecuteMovemAddressIndirectToMemory<Word>(m68000, opcode);
                case 5u: return ExecuteUnaryOpToAddressIndirect<Tst, Long>(m68000, opcode);
                case 6u: return ExecuteMovemAddressIndirectToRegister<Word>(m68000, opcode);
                case 7u: return ExecuteJsrAddressIndirect(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {NEGX|CLR|NEG|NOT|???|TST}.L (Ay)+
        case SizeMode(2u, 3u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteUnaryOpToAddressIncrement<Negx, Long>(m68000, opcode);
                case 1u: return ExecuteUnaryOpToAddressIncrement<Clr, Long>(m68000, opcode);
                case 2u: return ExecuteUnaryOpToAddressIncrement<Neg, Long>(m68000, opcode);
                case 3u: return ExecuteUnaryOpToAddressIncrement<Not, Long>(m68000, opcode);
                case 5u: return ExecuteUnaryOpToAddressIncrement<Tst, Long>(m68000, opcode);
                case 6u: return ExecuteMovemAddressIncrementToRegister<Word>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {NEGX|CLR|NEG|NOT|MOVEM|TST}.L -(Ay)
        case SizeMode(2u, 4u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteUnaryOpToAddressDecrement<Negx, Long>(m68000, opcode);
                case 1u: return ExecuteUnaryOpToAddressDecrement<Clr, Long>(m68000, opcode);
                case 2u: return ExecuteUnaryOpToAddressDecrement<Neg, Long>(m68000, opcode);
                case 3u: return ExecuteUnaryOpToAddressDecrement<Not, Long>(m68000, opcode);
                case 4u: return ExecuteMovemAddressDecrementToMemory<Word>(m68000, opcode);
                case 5u: return ExecuteUnaryOpToAddressDecrement<Tst, Long>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {NEGX|CLR|NEG|NOT|MOVEM|TST|JSR}.L (d, Ay)
        case SizeMode(2u, 5u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteUnaryOpToAddressDisplacement<Negx, Long>(m68000, opcode);
                case 1u: return ExecuteUnaryOpToAddressDisplacement<Clr, Long>(m68000, opcode);
                case 2u: return ExecuteUnaryOpToAddressDisplacement<Neg, Long>(m68000, opcode);
                case 3u: return ExecuteUnaryOpToAddressDisplacement<Not, Long>(m68000, opcode);
                case 4u: return ExecuteMovemAddressDisplacementToMemory<Word>(m68000, opcode);
                case 5u: return ExecuteUnaryOpToAddressDisplacement<Tst, Long>(m68000, opcode);
                case 6u: return ExecuteMovemAddressDisplacementToRegister<Word>(m68000, opcode);
                case 7u: return ExecuteJsrAddressDisplacement(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {NEGX|CLR|NEG|NOT|MOVEM|TST|JSR}.L (d, Ay, Xn)
        case SizeMode(2u, 6u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteUnaryOpToAddressIndex<Negx, Long>(m68000, opcode);
                case 1u: return ExecuteUnaryOpToAddressIndex<Clr, Long>(m68000, opcode);
                case 2u: return ExecuteUnaryOpToAddressIndex<Neg, Long>(m68000, opcode);
                case 3u: return ExecuteUnaryOpToAddressIndex<Not, Long>(m68000, opcode);
                case 4u: return ExecuteMovemAddressIndexToMemory<Word>(m68000, opcode);
                case 5u: return ExecuteUnaryOpToAddressIndex<Tst, Long>(m68000, opcode);
                case 6u: return ExecuteMovemAddressIndexToRegister<Word>(m68000, opcode);
                case 7u: return ExecuteJsrAddressIndex(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {NEGX|CLR|NEG|NOT|MOVEM|TST|JSR}.L (address).{W|L}
        case SizeMode(2u, 7u):
            switch (opcode & RegisterXY(7u, 7u)) {
                case RegisterXY(0u, 0u): return ExecuteUnaryOpToShort<Negx, Long>(m68000, opcode);
                case RegisterXY(1u, 0u): return ExecuteUnaryOpToShort<Clr, Long>(m68000, opcode);
                case RegisterXY(2u, 0u): return ExecuteUnaryOpToShort<Neg, Long>(m68000, opcode);
                case RegisterXY(3u, 0u): return ExecuteUnaryOpToShort<Not, Long>(m68000, opcode);
                case RegisterXY(4u, 0u): return ExecuteMovemShortToMemory<Word>(m68000);
                case RegisterXY(5u, 0u): return ExecuteUnaryOpToShort<Tst, Long>(m68000, opcode);
                case RegisterXY(6u, 0u): return ExecuteMovemShortToRegister<Word>(m68000);
                case RegisterXY(7u, 0u): return ExecuteJsrShort(m68000);
                    //
                case RegisterXY(0u, 1u): return ExecuteUnaryOpToLong<Negx, Long>(m68000, opcode);
                case RegisterXY(1u, 1u): return ExecuteUnaryOpToLong<Clr, Long>(m68000, opcode);
                case RegisterXY(2u, 1u): return ExecuteUnaryOpToLong<Neg, Long>(m68000, opcode);
                case RegisterXY(3u, 1u): return ExecuteUnaryOpToLong<Not, Long>(m68000, opcode);
                case RegisterXY(4u, 1u): return ExecuteMovemLongToMemory<Word>(m68000);
                case RegisterXY(5u, 1u): return ExecuteUnaryOpToLong<Tst, Long>(m68000, opcode);
                case RegisterXY(6u, 1u): return ExecuteMovemLongToRegister<Word>(m68000);
                case RegisterXY(7u, 1u): return ExecuteJsrLong(m68000);
                    //
                case RegisterXY(6u, 2u): return ExecuteMovemPCDisplacementToRegister<Word>(m68000);
                case RegisterXY(7u, 2u): return ExecuteJsrPCDisplacement(m68000);
                    //
                case RegisterXY(6u, 3u): return ExecuteMovemPCIndexToRegister<Word>(m68000);
                case RegisterXY(7u, 3u): return ExecuteJsrPCIndex(m68000);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {MOVE SR|MOVE CCR|EXT|TAS} Dy
        case SizeMode(3u, 0u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteUnaryOpToDataRegister<MoveFromSR, Word>(m68000, opcode);
                case 2u: return ExecuteMoveOpDataRegisterToCCR(m68000, opcode);
                case 3u: return ExecuteMoveOpDataRegisterToSR(m68000, opcode);
                case 4u: return ExecuteExtToDataRegister<Long>(m68000, opcode);
                case 5u: return ExecuteUnaryOpToDataRegister<TasD, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {MOVE SR|MOVE CCR|MOVEM|TAS|JMP} (Ay)
        case SizeMode(3u, 2u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteUnaryOpToAddressIndirect<MoveFromSR, Word>(m68000, opcode);
                case 2u: return ExecuteMoveOpAddressIndirectToCCR(m68000, opcode);
                case 3u: return ExecuteMoveOpAddressIndirectToSR(m68000, opcode);
                case 4u: return ExecuteMovemAddressIndirectToMemory<Long>(m68000, opcode);
                case 5u: return ExecuteUnaryOpToAddressIndirect<Tas, Byte>(m68000, opcode);
                case 6u: return ExecuteMovemAddressIndirectToRegister<Long>(m68000, opcode);
                case 7u: return ExecuteJmpAddressIndirect(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {MOVE SR|MOVE CCR|MOVEM|TAS} (Ay)+
        case SizeMode(3u, 3u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteUnaryOpToAddressIncrement<MoveFromSR, Word>(m68000, opcode);
                case 2u: return ExecuteMoveOpAddressIncrementToCCR(m68000, opcode);
                case 3u: return ExecuteMoveOpAddressIncrementToSR(m68000, opcode);
                case 5u: return ExecuteUnaryOpToAddressIncrement<Tas, Byte>(m68000, opcode);
                case 6u: return ExecuteMovemAddressIncrementToRegister<Long>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {MOVE SR|MOVE CCR|MOVEM|TAS} -(Ay)
        case SizeMode(3u, 4u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteUnaryOpToAddressDecrement<MoveFromSR, Word>(m68000, opcode);
                case 2u: return ExecuteMoveOpAddressDecrementToCCR(m68000, opcode);
                case 3u: return ExecuteMoveOpAddressDecrementToSR(m68000, opcode);
                case 4u: return ExecuteMovemAddressDecrementToMemory<Long>(m68000, opcode);
                case 5u: return ExecuteUnaryOpToAddressDecrement<Tas, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {MOVE SR|MOVE CCR|MOVEM|TAS|JMP} (d, Ay)
        case SizeMode(3u, 5u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteUnaryOpToAddressDisplacement<MoveFromSR, Word>(m68000, opcode);
                case 2u: return ExecuteMoveOpAddressDisplacementToCCR(m68000, opcode);
                case 3u: return ExecuteMoveOpAddressDisplacementToSR(m68000, opcode);
                case 4u: return ExecuteMovemAddressDisplacementToMemory<Long>(m68000, opcode);
                case 5u: return ExecuteUnaryOpToAddressDisplacement<Tas, Byte>(m68000, opcode);
                case 6u: return ExecuteMovemAddressDisplacementToRegister<Long>(m68000, opcode);
                case 7u: return ExecuteJmpAddressDisplacement(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {MOVE SR|MOVE CCR|MOVEM|TAS|JMP} (d, Ay, Xn)
        case SizeMode(3u, 6u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteUnaryOpToAddressIndex<MoveFromSR, Word>(m68000, opcode);
                case 2u: return ExecuteMoveOpAddressIndexToCCR(m68000, opcode);
                case 3u: return ExecuteMoveOpAddressIndexToSR(m68000, opcode);
                case 4u: return ExecuteMovemAddressIndexToMemory<Long>(m68000, opcode);
                case 5u: return ExecuteUnaryOpToAddressIndex<Tas, Byte>(m68000, opcode);
                case 6u: return ExecuteMovemAddressIndexToRegister<Long>(m68000, opcode);
                case 7u: return ExecuteJmpAddressIndex(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {MOVE SR|MOVE CCR|MOVEM|TAS|JMP} (address).{W|L}, (d, PC), (d, PC, Xn)
            // ILLEGAL
        case SizeMode(3u, 7u):
            switch (opcode & RegisterXY(7u, 7u)) {
                case RegisterXY(0u, 0u): return ExecuteUnaryOpToShort<MoveFromSR, Word>(m68000, opcode);
                case RegisterXY(2u, 0u): return ExecuteMoveOpShortToCCR(m68000, opcode);
                case RegisterXY(3u, 0u): return ExecuteMoveOpShortToSR(m68000, opcode);
                case RegisterXY(4u, 0u): return ExecuteMovemShortToMemory<Long>(m68000);
                case RegisterXY(5u, 0u): return ExecuteUnaryOpToShort<Tas, Byte>(m68000, opcode);
                case RegisterXY(6u, 0u): return ExecuteMovemShortToRegister<Long>(m68000);
                case RegisterXY(7u, 0u): return ExecuteJmpShort(m68000);
                    //
                case RegisterXY(0u, 1u): return ExecuteUnaryOpToLong<MoveFromSR, Word>(m68000, opcode);
                case RegisterXY(2u, 1u): return ExecuteMoveOpLongToCCR(m68000, opcode);
                case RegisterXY(3u, 1u): return ExecuteMoveOpLongToSR(m68000, opcode);
                case RegisterXY(4u, 1u): return ExecuteMovemLongToMemory<Long>(m68000);
                case RegisterXY(5u, 1u): return ExecuteUnaryOpToLong<Tas, Byte>(m68000, opcode);
                case RegisterXY(6u, 1u): return ExecuteMovemLongToRegister<Long>(m68000);
                case RegisterXY(7u, 1u): return ExecuteJmpLong(m68000);
                    //
                case RegisterXY(2u, 2u): return ExecuteMoveOpPCDisplacementToCCR(m68000, opcode);
                case RegisterXY(3u, 2u): return ExecuteMoveOpPCDisplacementToSR(m68000, opcode);
                case RegisterXY(6u, 2u): return ExecuteMovemPCDisplacementToRegister<Long>(m68000);
                case RegisterXY(7u, 2u): return ExecuteJmpPCDisplacement(m68000);
                    //
                case RegisterXY(2u, 3u): return ExecuteMoveOpPCIndexToCCR(m68000, opcode);
                case RegisterXY(3u, 3u): return ExecuteMoveOpPCIndexToSR(m68000, opcode);
                case RegisterXY(6u, 3u): return ExecuteMovemPCIndexToRegister<Long>(m68000);
                case RegisterXY(7u, 3u): return ExecuteJmpPCIndex(m68000);
                    //
                case RegisterXY(2u, 4u): return ExecuteMoveOpImmediateToCCR(m68000, opcode);
                case RegisterXY(3u, 4u): return ExecuteMoveOpImmediateToSR(m68000, opcode);
                case RegisterXY(5u, 4u): return ExecuteIllegal(m68000);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // CHK.W <ea>, Dx
        case SizeMode(6u, 0u): return ExecuteChkToDataRegister<SourceDataRegister>(m68000, opcode);
        case SizeMode(6u, 2u): return ExecuteChkToDataRegister<SourceAddressIndirect>(m68000, opcode);
        case SizeMode(6u, 3u): return ExecuteChkToDataRegister<SourceAddressIncrement>(m68000, opcode);
        case SizeMode(6u, 4u): return ExecuteChkToDataRegister<SourceAddressDecrement>(m68000, opcode);
        case SizeMode(6u, 5u): return ExecuteChkToDataRegister<SourceAddressDisplacement>(m68000, opcode);
        case SizeMode(6u, 6u): return ExecuteChkToDataRegister<SourceAddressIndex>(m68000, opcode);
        case SizeMode(6u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteChkToDataRegister<SourceShort>(m68000, opcode);
                case 1u: return ExecuteChkToDataRegister<SourceLong>(m68000, opcode);
                case 2u: return ExecuteChkToDataRegister<SourcePCDisplacement>(m68000, opcode);
                case 3u: return ExecuteChkToDataRegister<SourcePCIndex>(m68000, opcode);
                case 4u: return ExecuteChkToDataRegister<SourceImmediate>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // LEA <ea>, Ax
        case SizeMode(7u, 2u): return ExecuteLeaAddressIndirect(m68000, opcode);
        case SizeMode(7u, 5u): return ExecuteLeaAddressDisplacement(m68000, opcode);
        case SizeMode(7u, 6u): return ExecuteLeaAddressIndex(m68000, opcode);
        case SizeMode(7u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteLeaShort(m68000, opcode);
                case 1u: return ExecuteLeaLong(m68000, opcode);
                case 2u: return ExecuteLeaPCDisplacement(m68000, opcode);
                case 3u: return ExecuteLeaPCIndex(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            [[unlikely]] default: return ExecuteIllegal(m68000);
    }
}

auto ExecuteLine5(M68000& m68000, uint32_t opcode) {
    using namespace addressing::quick;
    switch (opcode & SizeMode(7u, 7u)) {
        // ADDQ.B #imm, <ea>
        case SizeMode(0u, 0u): return ExecuteQuickOpToDataRegister<Addq, Byte>(m68000, opcode);
        case SizeMode(0u, 2u): return ExecuteQuickOpToAddressIndirect<Addq, Byte>(m68000, opcode);
        case SizeMode(0u, 3u): return ExecuteQuickOpToAddressIncrement<Addq, Byte>(m68000, opcode);
        case SizeMode(0u, 4u): return ExecuteQuickOpToAddressDecrement<Addq, Byte>(m68000, opcode);
        case SizeMode(0u, 5u): return ExecuteQuickOpToAddressDisplacement<Addq, Byte>(m68000, opcode);
        case SizeMode(0u, 6u): return ExecuteQuickOpToAddressIndex<Addq, Byte>(m68000, opcode);
        case SizeMode(0u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteQuickOpToShort<Addq, Byte>(m68000, opcode);
                case 1u: return ExecuteQuickOpToLong<Addq, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // ADDQ.W #imm, <ea>
        case SizeMode(1u, 0u): return ExecuteQuickOpToDataRegister<Addq, Word>(m68000, opcode);
        case SizeMode(1u, 1u): return ExecuteQuickOpToAddressRegister<Adda, Word>(m68000, opcode);
        case SizeMode(1u, 2u): return ExecuteQuickOpToAddressIndirect<Addq, Word>(m68000, opcode);
        case SizeMode(1u, 3u): return ExecuteQuickOpToAddressIncrement<Addq, Word>(m68000, opcode);
        case SizeMode(1u, 4u): return ExecuteQuickOpToAddressDecrement<Addq, Word>(m68000, opcode);
        case SizeMode(1u, 5u): return ExecuteQuickOpToAddressDisplacement<Addq, Word>(m68000, opcode);
        case SizeMode(1u, 6u): return ExecuteQuickOpToAddressIndex<Addq, Word>(m68000, opcode);
        case SizeMode(1u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteQuickOpToShort<Addq, Word>(m68000, opcode);
                case 1u: return ExecuteQuickOpToLong<Addq, Word>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // ADDQ.L #imm, <ea>
        case SizeMode(2u, 0u): return ExecuteQuickOpToDataRegister<Addq, Long>(m68000, opcode);
        case SizeMode(2u, 1u): return ExecuteQuickOpToAddressRegister<Adda, Long>(m68000, opcode);
        case SizeMode(2u, 2u): return ExecuteQuickOpToAddressIndirect<Addq, Long>(m68000, opcode);
        case SizeMode(2u, 3u): return ExecuteQuickOpToAddressIncrement<Addq, Long>(m68000, opcode);
        case SizeMode(2u, 4u): return ExecuteQuickOpToAddressDecrement<Addq, Long>(m68000, opcode);
        case SizeMode(2u, 5u): return ExecuteQuickOpToAddressDisplacement<Addq, Long>(m68000, opcode);
        case SizeMode(2u, 6u): return ExecuteQuickOpToAddressIndex<Addq, Long>(m68000, opcode);
        case SizeMode(2u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteQuickOpToShort<Addq, Long>(m68000, opcode);
                case 1u: return ExecuteQuickOpToLong<Addq, Long>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // Scc <ea>
            // Dbcc
        case SizeMode(3u, 0u): return ExecuteQuickOpToDataRegister<SccD, Byte>(m68000, opcode);
        case SizeMode(3u, 1u): return ExecuteDbcc(m68000, opcode);
        case SizeMode(3u, 2u): return ExecuteQuickOpToAddressIndirect<Scc, Byte>(m68000, opcode);
        case SizeMode(3u, 3u): return ExecuteQuickOpToAddressIncrement<Scc, Byte>(m68000, opcode);
        case SizeMode(3u, 4u): return ExecuteQuickOpToAddressDecrement<Scc, Byte>(m68000, opcode);
        case SizeMode(3u, 5u): return ExecuteQuickOpToAddressDisplacement<Scc, Byte>(m68000, opcode);
        case SizeMode(3u, 6u): return ExecuteQuickOpToAddressIndex<Scc, Byte>(m68000, opcode);
        case SizeMode(3u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteQuickOpToShort<Scc, Byte>(m68000, opcode);
                case 1u: return ExecuteQuickOpToLong<Scc, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // SUBQ.B #imm, <ea>
        case SizeMode(4u, 0u): return ExecuteQuickOpToDataRegister<Subq, Byte>(m68000, opcode);
        case SizeMode(4u, 2u): return ExecuteQuickOpToAddressIndirect<Subq, Byte>(m68000, opcode);
        case SizeMode(4u, 3u): return ExecuteQuickOpToAddressIncrement<Subq, Byte>(m68000, opcode);
        case SizeMode(4u, 4u): return ExecuteQuickOpToAddressDecrement<Subq, Byte>(m68000, opcode);
        case SizeMode(4u, 5u): return ExecuteQuickOpToAddressDisplacement<Subq, Byte>(m68000, opcode);
        case SizeMode(4u, 6u): return ExecuteQuickOpToAddressIndex<Subq, Byte>(m68000, opcode);
        case SizeMode(4u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteQuickOpToShort<Subq, Byte>(m68000, opcode);
                case 1u: return ExecuteQuickOpToLong<Subq, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // SUBQ.W #imm, <ea>
        case SizeMode(5u, 0u): return ExecuteQuickOpToDataRegister<Subq, Word>(m68000, opcode);
        case SizeMode(5u, 1u): return ExecuteQuickOpToAddressRegister<Suba, Word>(m68000, opcode);
        case SizeMode(5u, 2u): return ExecuteQuickOpToAddressIndirect<Subq, Word>(m68000, opcode);
        case SizeMode(5u, 3u): return ExecuteQuickOpToAddressIncrement<Subq, Word>(m68000, opcode);
        case SizeMode(5u, 4u): return ExecuteQuickOpToAddressDecrement<Subq, Word>(m68000, opcode);
        case SizeMode(5u, 5u): return ExecuteQuickOpToAddressDisplacement<Subq, Word>(m68000, opcode);
        case SizeMode(5u, 6u): return ExecuteQuickOpToAddressIndex<Subq, Word>(m68000, opcode);
        case SizeMode(5u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteQuickOpToShort<Subq, Word>(m68000, opcode);
                case 1u: return ExecuteQuickOpToLong<Subq, Word>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // SUBQ.L #imm, <ea>
        case SizeMode(6u, 0u): return ExecuteQuickOpToDataRegister<Subq, Long>(m68000, opcode);
        case SizeMode(6u, 1u): return ExecuteQuickOpToAddressRegister<Suba, Long>(m68000, opcode);
        case SizeMode(6u, 2u): return ExecuteQuickOpToAddressIndirect<Subq, Long>(m68000, opcode);
        case SizeMode(6u, 3u): return ExecuteQuickOpToAddressIncrement<Subq, Long>(m68000, opcode);
        case SizeMode(6u, 4u): return ExecuteQuickOpToAddressDecrement<Subq, Long>(m68000, opcode);
        case SizeMode(6u, 5u): return ExecuteQuickOpToAddressDisplacement<Subq, Long>(m68000, opcode);
        case SizeMode(6u, 6u): return ExecuteQuickOpToAddressIndex<Subq, Long>(m68000, opcode);
        case SizeMode(6u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteQuickOpToShort<Subq, Long>(m68000, opcode);
                case 1u: return ExecuteQuickOpToLong<Subq, Long>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // Scc <ea>
            // Dbcc
        case SizeMode(7u, 0u): return ExecuteQuickOpToDataRegister<SccD, Byte>(m68000, opcode);
        case SizeMode(7u, 1u): return ExecuteDbcc(m68000, opcode);
        case SizeMode(7u, 2u): return ExecuteQuickOpToAddressIndirect<Scc, Byte>(m68000, opcode);
        case SizeMode(7u, 3u): return ExecuteQuickOpToAddressIncrement<Scc, Byte>(m68000, opcode);
        case SizeMode(7u, 4u): return ExecuteQuickOpToAddressDecrement<Scc, Byte>(m68000, opcode);
        case SizeMode(7u, 5u): return ExecuteQuickOpToAddressDisplacement<Scc, Byte>(m68000, opcode);
        case SizeMode(7u, 6u): return ExecuteQuickOpToAddressIndex<Scc, Byte>(m68000, opcode);
        case SizeMode(7u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteQuickOpToShort<Scc, Byte>(m68000, opcode);
                case 1u: return ExecuteQuickOpToLong<Scc, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            [[unlikely]] default: return ExecuteIllegal(m68000);
    }
}

auto ExecuteLine6(M68000& m68000, uint32_t opcode) {
    ExecuteBcc(m68000, opcode);
}

auto ExecuteLine7(M68000& m68000, uint32_t opcode) {
    if (opcode & 0x0100u) {
        ExecuteIllegal(m68000);
        return;
    }
    ExecuteMoveqToDataRegister(m68000, opcode);
}

auto ExecuteLine8(M68000& m68000, uint32_t opcode) {
    using namespace addressing::standard;
    using namespace addressing::divide;
    using namespace addressing::multiprecision;
    switch (opcode & SizeMode(7u, 7u)) {
        // OR.B <ea>, Dx
        case SizeMode(0u, 0u): return ExecuteBinaryOpDataRegisterToDataRegister<Or, Byte>(m68000, opcode);
        case SizeMode(0u, 2u): return ExecuteBinaryOpAddressIndirectToDataRegister<Or, Byte>(m68000, opcode);
        case SizeMode(0u, 3u): return ExecuteBinaryOpAddressIncrementToDataRegister<Or, Byte>(m68000, opcode);
        case SizeMode(0u, 4u): return ExecuteBinaryOpAddressDecrementToDataRegister<Or, Byte>(m68000, opcode);
        case SizeMode(0u, 5u): return ExecuteBinaryOpAddressDisplacementToDataRegister<Or, Byte>(m68000, opcode);
        case SizeMode(0u, 6u): return ExecuteBinaryOpAddressIndexToDataRegister<Or, Byte>(m68000, opcode);
        case SizeMode(0u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpShortToDataRegister<Or, Byte>(m68000, opcode);
                case 1u: return ExecuteBinaryOpLongToDataRegister<Or, Byte>(m68000, opcode);
                case 2u: return ExecuteBinaryOpPCDisplacementToDataRegister<Or, Byte>(m68000, opcode);
                case 3u: return ExecuteBinaryOpPCIndexToDataRegister<Or, Byte>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToDataRegister<Or, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // OR.W <ea>, Dx
        case SizeMode(1u, 0u): return ExecuteBinaryOpDataRegisterToDataRegister<Or, Word>(m68000, opcode);
        case SizeMode(1u, 2u): return ExecuteBinaryOpAddressIndirectToDataRegister<Or, Word>(m68000, opcode);
        case SizeMode(1u, 3u): return ExecuteBinaryOpAddressIncrementToDataRegister<Or, Word>(m68000, opcode);
        case SizeMode(1u, 4u): return ExecuteBinaryOpAddressDecrementToDataRegister<Or, Word>(m68000, opcode);
        case SizeMode(1u, 5u): return ExecuteBinaryOpAddressDisplacementToDataRegister<Or, Word>(m68000, opcode);
        case SizeMode(1u, 6u): return ExecuteBinaryOpAddressIndexToDataRegister<Or, Word>(m68000, opcode);
        case SizeMode(1u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpShortToDataRegister<Or, Word>(m68000, opcode);
                case 1u: return ExecuteBinaryOpLongToDataRegister<Or, Word>(m68000, opcode);
                case 2u: return ExecuteBinaryOpPCDisplacementToDataRegister<Or, Word>(m68000, opcode);
                case 3u: return ExecuteBinaryOpPCIndexToDataRegister<Or, Word>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToDataRegister<Or, Word>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // OR.L <ea>, Dx
        case SizeMode(2u, 0u): return ExecuteBinaryOpDataRegisterToDataRegister<Or, Long>(m68000, opcode);
        case SizeMode(2u, 2u): return ExecuteBinaryOpAddressIndirectToDataRegister<Or, Long>(m68000, opcode);
        case SizeMode(2u, 3u): return ExecuteBinaryOpAddressIncrementToDataRegister<Or, Long>(m68000, opcode);
        case SizeMode(2u, 4u): return ExecuteBinaryOpAddressDecrementToDataRegister<Or, Long>(m68000, opcode);
        case SizeMode(2u, 5u): return ExecuteBinaryOpAddressDisplacementToDataRegister<Or, Long>(m68000, opcode);
        case SizeMode(2u, 6u): return ExecuteBinaryOpAddressIndexToDataRegister<Or, Long>(m68000, opcode);
        case SizeMode(2u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpShortToDataRegister<Or, Long>(m68000, opcode);
                case 1u: return ExecuteBinaryOpLongToDataRegister<Or, Long>(m68000, opcode);
                case 2u: return ExecuteBinaryOpPCDisplacementToDataRegister<Or, Long>(m68000, opcode);
                case 3u: return ExecuteBinaryOpPCIndexToDataRegister<Or, Long>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToDataRegister<Or, Long>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // DIVU.W <ea>, Dx
        case SizeMode(3u, 0u): return ExecuteDivideUnsignedOpDataRegisterToDataRegister(m68000, opcode);
        case SizeMode(3u, 2u): return ExecuteDivideUnsignedOpAddressIndirectToDataRegister(m68000, opcode);
        case SizeMode(3u, 3u): return ExecuteDivideUnsignedOpAddressIncrementToDataRegister(m68000, opcode);
        case SizeMode(3u, 4u): return ExecuteDivideUnsignedOpAddressDecrementToDataRegister(m68000, opcode);
        case SizeMode(3u, 5u): return ExecuteDivideUnsignedOpAddressDisplacementToDataRegister(m68000, opcode);
        case SizeMode(3u, 6u): return ExecuteDivideUnsignedOpAddressIndexToDataRegister(m68000, opcode);
        case SizeMode(3u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteDivideUnsignedOpShortToDataRegister(m68000, opcode);
                case 1u: return ExecuteDivideUnsignedOpLongToDataRegister(m68000, opcode);
                case 2u: return ExecuteDivideUnsignedOpPCDisplacementToDataRegister(m68000, opcode);
                case 3u: return ExecuteDivideUnsignedOpPCIndexToDataRegister(m68000, opcode);
                case 4u: return ExecuteDivideUnsignedOpImmediateToDataRegister(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // SBCD.B Dy, Dx, SBCD -(Ay), -(Ax), OR.B Dx, <ea>
        case SizeMode(4u, 0u): return ExecuteMultiprecisionOpDataRegisterToDataRegister<Sbcd, Byte>(m68000, opcode);
        case SizeMode(4u, 1u): return ExecuteMultiprecisionOpAddressDecrementToAddressDecrement<Sbcd, Byte>(m68000, opcode);
        case SizeMode(4u, 2u): return ExecuteBinaryOpDataRegisterToAddressIndirect<Or, Byte>(m68000, opcode);
        case SizeMode(4u, 3u): return ExecuteBinaryOpDataRegisterToAddressIncrement<Or, Byte>(m68000, opcode);
        case SizeMode(4u, 4u): return ExecuteBinaryOpDataRegisterToAddressDecrement<Or, Byte>(m68000, opcode);
        case SizeMode(4u, 5u): return ExecuteBinaryOpDataRegisterToAddressDisplacement<Or, Byte>(m68000, opcode);
        case SizeMode(4u, 6u): return ExecuteBinaryOpDataRegisterToAddressIndex<Or, Byte>(m68000, opcode);
        case SizeMode(4u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpDataRegisterToShort<Or, Byte>(m68000, opcode);
                case 1u: return ExecuteBinaryOpDataRegisterToLong<Or, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // OR.W Dx, <ea>
        case SizeMode(5u, 2u): return ExecuteBinaryOpDataRegisterToAddressIndirect<Or, Word>(m68000, opcode);
        case SizeMode(5u, 3u): return ExecuteBinaryOpDataRegisterToAddressIncrement<Or, Word>(m68000, opcode);
        case SizeMode(5u, 4u): return ExecuteBinaryOpDataRegisterToAddressDecrement<Or, Word>(m68000, opcode);
        case SizeMode(5u, 5u): return ExecuteBinaryOpDataRegisterToAddressDisplacement<Or, Word>(m68000, opcode);
        case SizeMode(5u, 6u): return ExecuteBinaryOpDataRegisterToAddressIndex<Or, Word>(m68000, opcode);
        case SizeMode(5u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpDataRegisterToShort<Or, Word>(m68000, opcode);
                case 1u: return ExecuteBinaryOpDataRegisterToLong<Or, Word>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // OR.L Dx, <ea>
        case SizeMode(6u, 2u): return ExecuteBinaryOpDataRegisterToAddressIndirect<Or, Long>(m68000, opcode);
        case SizeMode(6u, 3u): return ExecuteBinaryOpDataRegisterToAddressIncrement<Or, Long>(m68000, opcode);
        case SizeMode(6u, 4u): return ExecuteBinaryOpDataRegisterToAddressDecrement<Or, Long>(m68000, opcode);
        case SizeMode(6u, 5u): return ExecuteBinaryOpDataRegisterToAddressDisplacement<Or, Long>(m68000, opcode);
        case SizeMode(6u, 6u): return ExecuteBinaryOpDataRegisterToAddressIndex<Or, Long>(m68000, opcode);
        case SizeMode(6u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpDataRegisterToShort<Or, Long>(m68000, opcode);
                case 1u: return ExecuteBinaryOpDataRegisterToLong<Or, Long>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // DIVS.W <ea>, Dx
        case SizeMode(7u, 0u): return ExecuteDivideSignedOpDataRegisterToDataRegister(m68000, opcode);
        case SizeMode(7u, 2u): return ExecuteDivideSignedOpAddressIndirectToDataRegister(m68000, opcode);
        case SizeMode(7u, 3u): return ExecuteDivideSignedOpAddressIncrementToDataRegister(m68000, opcode);
        case SizeMode(7u, 4u): return ExecuteDivideSignedOpAddressDecrementToDataRegister(m68000, opcode);
        case SizeMode(7u, 5u): return ExecuteDivideSignedOpAddressDisplacementToDataRegister(m68000, opcode);
        case SizeMode(7u, 6u): return ExecuteDivideSignedOpAddressIndexToDataRegister(m68000, opcode);
        case SizeMode(7u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteDivideSignedOpShortToDataRegister(m68000, opcode);
                case 1u: return ExecuteDivideSignedOpLongToDataRegister(m68000, opcode);
                case 2u: return ExecuteDivideSignedOpPCDisplacementToDataRegister(m68000, opcode);
                case 3u: return ExecuteDivideSignedOpPCIndexToDataRegister(m68000, opcode);
                case 4u: return ExecuteDivideSignedOpImmediateToDataRegister(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            [[unlikely]] default: return ExecuteIllegal(m68000);
    }
}

auto ExecuteLine9(M68000& m68000, uint32_t opcode) {
    using namespace addressing::standard;
    using namespace addressing::address;
    using namespace addressing::multiprecision;
    switch (opcode & SizeMode(7u, 7u)) {
        // SUB.B <ea>, Dx
        case SizeMode(0u, 0u): return ExecuteBinaryOpDataRegisterToDataRegister<Sub, Byte>(m68000, opcode);
        case SizeMode(0u, 2u): return ExecuteBinaryOpAddressIndirectToDataRegister<Sub, Byte>(m68000, opcode);
        case SizeMode(0u, 3u): return ExecuteBinaryOpAddressIncrementToDataRegister<Sub, Byte>(m68000, opcode);
        case SizeMode(0u, 4u): return ExecuteBinaryOpAddressDecrementToDataRegister<Sub, Byte>(m68000, opcode);
        case SizeMode(0u, 5u): return ExecuteBinaryOpAddressDisplacementToDataRegister<Sub, Byte>(m68000, opcode);
        case SizeMode(0u, 6u): return ExecuteBinaryOpAddressIndexToDataRegister<Sub, Byte>(m68000, opcode);
        case SizeMode(0u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpShortToDataRegister<Sub, Byte>(m68000, opcode);
                case 1u: return ExecuteBinaryOpLongToDataRegister<Sub, Byte>(m68000, opcode);
                case 2u: return ExecuteBinaryOpPCDisplacementToDataRegister<Sub, Byte>(m68000, opcode);
                case 3u: return ExecuteBinaryOpPCIndexToDataRegister<Sub, Byte>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToDataRegister<Sub, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // SUB.W <ea>, Dx
        case SizeMode(1u, 0u): return ExecuteBinaryOpDataRegisterToDataRegister<Sub, Word>(m68000, opcode);
        case SizeMode(1u, 1u): return ExecuteBinaryOpAddressRegisterToDataRegister<Sub, Word>(m68000, opcode);
        case SizeMode(1u, 2u): return ExecuteBinaryOpAddressIndirectToDataRegister<Sub, Word>(m68000, opcode);
        case SizeMode(1u, 3u): return ExecuteBinaryOpAddressIncrementToDataRegister<Sub, Word>(m68000, opcode);
        case SizeMode(1u, 4u): return ExecuteBinaryOpAddressDecrementToDataRegister<Sub, Word>(m68000, opcode);
        case SizeMode(1u, 5u): return ExecuteBinaryOpAddressDisplacementToDataRegister<Sub, Word>(m68000, opcode);
        case SizeMode(1u, 6u): return ExecuteBinaryOpAddressIndexToDataRegister<Sub, Word>(m68000, opcode);
        case SizeMode(1u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpShortToDataRegister<Sub, Word>(m68000, opcode);
                case 1u: return ExecuteBinaryOpLongToDataRegister<Sub, Word>(m68000, opcode);
                case 2u: return ExecuteBinaryOpPCDisplacementToDataRegister<Sub, Word>(m68000, opcode);
                case 3u: return ExecuteBinaryOpPCIndexToDataRegister<Sub, Word>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToDataRegister<Sub, Word>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // SUB.L <ea>, Dx
        case SizeMode(2u, 0u): return ExecuteBinaryOpDataRegisterToDataRegister<Sub, Long>(m68000, opcode);
        case SizeMode(2u, 1u): return ExecuteBinaryOpAddressRegisterToDataRegister<Sub, Long>(m68000, opcode);
        case SizeMode(2u, 2u): return ExecuteBinaryOpAddressIndirectToDataRegister<Sub, Long>(m68000, opcode);
        case SizeMode(2u, 3u): return ExecuteBinaryOpAddressIncrementToDataRegister<Sub, Long>(m68000, opcode);
        case SizeMode(2u, 4u): return ExecuteBinaryOpAddressDecrementToDataRegister<Sub, Long>(m68000, opcode);
        case SizeMode(2u, 5u): return ExecuteBinaryOpAddressDisplacementToDataRegister<Sub, Long>(m68000, opcode);
        case SizeMode(2u, 6u): return ExecuteBinaryOpAddressIndexToDataRegister<Sub, Long>(m68000, opcode);
        case SizeMode(2u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpShortToDataRegister<Sub, Long>(m68000, opcode);
                case 1u: return ExecuteBinaryOpLongToDataRegister<Sub, Long>(m68000, opcode);
                case 2u: return ExecuteBinaryOpPCDisplacementToDataRegister<Sub, Long>(m68000, opcode);
                case 3u: return ExecuteBinaryOpPCIndexToDataRegister<Sub, Long>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToDataRegister<Sub, Long>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // SUBA.W <ea>, Ax
        case SizeMode(3u, 0u): return ExecuteBinaryOpDataRegisterToAddressRegister<Suba, Word>(m68000, opcode);
        case SizeMode(3u, 1u): return ExecuteBinaryOpAddressRegisterToAddressRegister<Suba, Word>(m68000, opcode);
        case SizeMode(3u, 2u): return ExecuteBinaryOpAddressIndirectToAddressRegister<Suba, Word>(m68000, opcode);
        case SizeMode(3u, 3u): return ExecuteBinaryOpAddressIncrementToAddressRegister<Suba, Word>(m68000, opcode);
        case SizeMode(3u, 4u): return ExecuteBinaryOpAddressDecrementToAddressRegister<Suba, Word>(m68000, opcode);
        case SizeMode(3u, 5u): return ExecuteBinaryOpAddressDisplacementToAddressRegister<Suba, Word>(m68000, opcode);
        case SizeMode(3u, 6u): return ExecuteBinaryOpAddressIndexToAddressRegister<Suba, Word>(m68000, opcode);
        case SizeMode(3u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpShortToAddressRegister<Suba, Word>(m68000, opcode);
                case 1u: return ExecuteBinaryOpLongToAddressRegister<Suba, Word>(m68000, opcode);
                case 2u: return ExecuteBinaryOpPCDisplacementToAddressRegister<Suba, Word>(m68000, opcode);
                case 3u: return ExecuteBinaryOpPCIndexToAddressRegister<Suba, Word>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToAddressRegister<Suba, Word>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // SUBX.B Dy, Dx, SUBX.B -(Ay), -(Ax), SUB.B Dx, <ea>
        case SizeMode(4u, 0u): return ExecuteMultiprecisionOpDataRegisterToDataRegister<Subx, Byte>(m68000, opcode);
        case SizeMode(4u, 1u): return ExecuteMultiprecisionOpAddressDecrementToAddressDecrement<Subx, Byte>(m68000, opcode);
        case SizeMode(4u, 2u): return ExecuteBinaryOpDataRegisterToAddressIndirect<Sub, Byte>(m68000, opcode);
        case SizeMode(4u, 3u): return ExecuteBinaryOpDataRegisterToAddressIncrement<Sub, Byte>(m68000, opcode);
        case SizeMode(4u, 4u): return ExecuteBinaryOpDataRegisterToAddressDecrement<Sub, Byte>(m68000, opcode);
        case SizeMode(4u, 5u): return ExecuteBinaryOpDataRegisterToAddressDisplacement<Sub, Byte>(m68000, opcode);
        case SizeMode(4u, 6u): return ExecuteBinaryOpDataRegisterToAddressIndex<Sub, Byte>(m68000, opcode);
        case SizeMode(4u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpDataRegisterToShort<Sub, Byte>(m68000, opcode);
                case 1u: return ExecuteBinaryOpDataRegisterToLong<Sub, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // SUBX.W Dy, Dx, SUBX.W -(Ay), -(Ax), SUB.W Dx, <ea>
        case SizeMode(5u, 0u): return ExecuteMultiprecisionOpDataRegisterToDataRegister<Subx, Word>(m68000, opcode);
        case SizeMode(5u, 1u): return ExecuteMultiprecisionOpAddressDecrementToAddressDecrement<Subx, Word>(m68000, opcode);
        case SizeMode(5u, 2u): return ExecuteBinaryOpDataRegisterToAddressIndirect<Sub, Word>(m68000, opcode);
        case SizeMode(5u, 3u): return ExecuteBinaryOpDataRegisterToAddressIncrement<Sub, Word>(m68000, opcode);
        case SizeMode(5u, 4u): return ExecuteBinaryOpDataRegisterToAddressDecrement<Sub, Word>(m68000, opcode);
        case SizeMode(5u, 5u): return ExecuteBinaryOpDataRegisterToAddressDisplacement<Sub, Word>(m68000, opcode);
        case SizeMode(5u, 6u): return ExecuteBinaryOpDataRegisterToAddressIndex<Sub, Word>(m68000, opcode);
        case SizeMode(5u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpDataRegisterToShort<Sub, Word>(m68000, opcode);
                case 1u: return ExecuteBinaryOpDataRegisterToLong<Sub, Word>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // SUBX.L Dy, Dx, SUBX.L -(Ay), -(Ax), SUB.L Dx, <ea>
        case SizeMode(6u, 0u): return ExecuteMultiprecisionOpDataRegisterToDataRegister<Subx, Long>(m68000, opcode);
        case SizeMode(6u, 1u): return ExecuteMultiprecisionOpAddressDecrementToAddressDecrement<Subx, Long>(m68000, opcode);
        case SizeMode(6u, 2u): return ExecuteBinaryOpDataRegisterToAddressIndirect<Sub, Long>(m68000, opcode);
        case SizeMode(6u, 3u): return ExecuteBinaryOpDataRegisterToAddressIncrement<Sub, Long>(m68000, opcode);
        case SizeMode(6u, 4u): return ExecuteBinaryOpDataRegisterToAddressDecrement<Sub, Long>(m68000, opcode);
        case SizeMode(6u, 5u): return ExecuteBinaryOpDataRegisterToAddressDisplacement<Sub, Long>(m68000, opcode);
        case SizeMode(6u, 6u): return ExecuteBinaryOpDataRegisterToAddressIndex<Sub, Long>(m68000, opcode);
        case SizeMode(6u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpDataRegisterToShort<Sub, Long>(m68000, opcode);
                case 1u: return ExecuteBinaryOpDataRegisterToLong<Sub, Long>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // SUBA.L <ea>, Ax
        case SizeMode(7u, 0u): return ExecuteBinaryOpDataRegisterToAddressRegister<Suba, Long>(m68000, opcode);
        case SizeMode(7u, 1u): return ExecuteBinaryOpAddressRegisterToAddressRegister<Suba, Long>(m68000, opcode);
        case SizeMode(7u, 2u): return ExecuteBinaryOpAddressIndirectToAddressRegister<Suba, Long>(m68000, opcode);
        case SizeMode(7u, 3u): return ExecuteBinaryOpAddressIncrementToAddressRegister<Suba, Long>(m68000, opcode);
        case SizeMode(7u, 4u): return ExecuteBinaryOpAddressDecrementToAddressRegister<Suba, Long>(m68000, opcode);
        case SizeMode(7u, 5u): return ExecuteBinaryOpAddressDisplacementToAddressRegister<Suba, Long>(m68000, opcode);
        case SizeMode(7u, 6u): return ExecuteBinaryOpAddressIndexToAddressRegister<Suba, Long>(m68000, opcode);
        case SizeMode(7u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpShortToAddressRegister<Suba, Long>(m68000, opcode);
                case 1u: return ExecuteBinaryOpLongToAddressRegister<Suba, Long>(m68000, opcode);
                case 2u: return ExecuteBinaryOpPCDisplacementToAddressRegister<Suba, Long>(m68000, opcode);
                case 3u: return ExecuteBinaryOpPCIndexToAddressRegister<Suba, Long>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToAddressRegister<Suba, Long>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            [[unlikely]] default: return ExecuteIllegal(m68000);
    }
}

auto ExecuteLineA(M68000& m68000, uint32_t) {
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    RaiseLineAEmulatorException(m68000);
}

auto ExecuteLineB(M68000& m68000, uint32_t opcode) {
    using namespace addressing::standard;
    using namespace addressing::address;
    using namespace addressing::multiprecision;
    switch (opcode & SizeMode(7u, 7u)) {
        // CMP.B <ea>, Dx
        case SizeMode(0u, 0u): return ExecuteBinaryOpDataRegisterToDataRegister<Cmp, Byte>(m68000, opcode);
        case SizeMode(0u, 2u): return ExecuteBinaryOpAddressIndirectToDataRegister<Cmp, Byte>(m68000, opcode);
        case SizeMode(0u, 3u): return ExecuteBinaryOpAddressIncrementToDataRegister<Cmp, Byte>(m68000, opcode);
        case SizeMode(0u, 4u): return ExecuteBinaryOpAddressDecrementToDataRegister<Cmp, Byte>(m68000, opcode);
        case SizeMode(0u, 5u): return ExecuteBinaryOpAddressDisplacementToDataRegister<Cmp, Byte>(m68000, opcode);
        case SizeMode(0u, 6u): return ExecuteBinaryOpAddressIndexToDataRegister<Cmp, Byte>(m68000, opcode);
        case SizeMode(0u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpShortToDataRegister<Cmp, Byte>(m68000, opcode);
                case 1u: return ExecuteBinaryOpLongToDataRegister<Cmp, Byte>(m68000, opcode);
                case 2u: return ExecuteBinaryOpPCDisplacementToDataRegister<Cmp, Byte>(m68000, opcode);
                case 3u: return ExecuteBinaryOpPCIndexToDataRegister<Cmp, Byte>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToDataRegister<Cmp, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // CMP.W <ea>, Dx
        case SizeMode(1u, 0u): return ExecuteBinaryOpDataRegisterToDataRegister<Cmp, Word>(m68000, opcode);
        case SizeMode(1u, 1u): return ExecuteBinaryOpAddressRegisterToDataRegister<Cmp, Word>(m68000, opcode);
        case SizeMode(1u, 2u): return ExecuteBinaryOpAddressIndirectToDataRegister<Cmp, Word>(m68000, opcode);
        case SizeMode(1u, 3u): return ExecuteBinaryOpAddressIncrementToDataRegister<Cmp, Word>(m68000, opcode);
        case SizeMode(1u, 4u): return ExecuteBinaryOpAddressDecrementToDataRegister<Cmp, Word>(m68000, opcode);
        case SizeMode(1u, 5u): return ExecuteBinaryOpAddressDisplacementToDataRegister<Cmp, Word>(m68000, opcode);
        case SizeMode(1u, 6u): return ExecuteBinaryOpAddressIndexToDataRegister<Cmp, Word>(m68000, opcode);
        case SizeMode(1u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpShortToDataRegister<Cmp, Word>(m68000, opcode);
                case 1u: return ExecuteBinaryOpLongToDataRegister<Cmp, Word>(m68000, opcode);
                case 2u: return ExecuteBinaryOpPCDisplacementToDataRegister<Cmp, Word>(m68000, opcode);
                case 3u: return ExecuteBinaryOpPCIndexToDataRegister<Cmp, Word>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToDataRegister<Cmp, Word>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // CMP.W <ea>, Dx
        case SizeMode(2u, 0u): return ExecuteBinaryOpDataRegisterToDataRegister<Cmp, Long>(m68000, opcode);
        case SizeMode(2u, 1u): return ExecuteBinaryOpAddressRegisterToDataRegister<Cmp, Long>(m68000, opcode);
        case SizeMode(2u, 2u): return ExecuteBinaryOpAddressIndirectToDataRegister<Cmp, Long>(m68000, opcode);
        case SizeMode(2u, 3u): return ExecuteBinaryOpAddressIncrementToDataRegister<Cmp, Long>(m68000, opcode);
        case SizeMode(2u, 4u): return ExecuteBinaryOpAddressDecrementToDataRegister<Cmp, Long>(m68000, opcode);
        case SizeMode(2u, 5u): return ExecuteBinaryOpAddressDisplacementToDataRegister<Cmp, Long>(m68000, opcode);
        case SizeMode(2u, 6u): return ExecuteBinaryOpAddressIndexToDataRegister<Cmp, Long>(m68000, opcode);
        case SizeMode(2u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpShortToDataRegister<Cmp, Long>(m68000, opcode);
                case 1u: return ExecuteBinaryOpLongToDataRegister<Cmp, Long>(m68000, opcode);
                case 2u: return ExecuteBinaryOpPCDisplacementToDataRegister<Cmp, Long>(m68000, opcode);
                case 3u: return ExecuteBinaryOpPCIndexToDataRegister<Cmp, Long>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToDataRegister<Cmp, Long>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // CMPA.W <ea>, Ax
        case SizeMode(3u, 0u): return ExecuteBinaryOpDataRegisterToAddressRegister<Cmpa, Word>(m68000, opcode);
        case SizeMode(3u, 1u): return ExecuteBinaryOpAddressRegisterToAddressRegister<Cmpa, Word>(m68000, opcode);
        case SizeMode(3u, 2u): return ExecuteBinaryOpAddressIndirectToAddressRegister<Cmpa, Word>(m68000, opcode);
        case SizeMode(3u, 3u): return ExecuteBinaryOpAddressIncrementToAddressRegister<Cmpa, Word>(m68000, opcode);
        case SizeMode(3u, 4u): return ExecuteBinaryOpAddressDecrementToAddressRegister<Cmpa, Word>(m68000, opcode);
        case SizeMode(3u, 5u): return ExecuteBinaryOpAddressDisplacementToAddressRegister<Cmpa, Word>(m68000, opcode);
        case SizeMode(3u, 6u): return ExecuteBinaryOpAddressIndexToAddressRegister<Cmpa, Word>(m68000, opcode);
        case SizeMode(3u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpShortToAddressRegister<Cmpa, Word>(m68000, opcode);
                case 1u: return ExecuteBinaryOpLongToAddressRegister<Cmpa, Word>(m68000, opcode);
                case 2u: return ExecuteBinaryOpPCDisplacementToAddressRegister<Cmpa, Word>(m68000, opcode);
                case 3u: return ExecuteBinaryOpPCIndexToAddressRegister<Cmpa, Word>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToAddressRegister<Cmpa, Word>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // EOR.B Dx, <ea>, CMPM.B (Ay)+, (Ax)+
        case SizeMode(4u, 0u): return ExecuteBinaryOpDataRegisterXToDataRegisterY<Eor, Byte>(m68000, opcode);
        case SizeMode(4u, 1u): return ExecuteMultiprecisionOpAddressIncrementToAddressIncrement<Cmp, Byte>(m68000, opcode);
        case SizeMode(4u, 2u): return ExecuteBinaryOpDataRegisterToAddressIndirect<Eor, Byte>(m68000, opcode);
        case SizeMode(4u, 3u): return ExecuteBinaryOpDataRegisterToAddressIncrement<Eor, Byte>(m68000, opcode);
        case SizeMode(4u, 4u): return ExecuteBinaryOpDataRegisterToAddressDecrement<Eor, Byte>(m68000, opcode);
        case SizeMode(4u, 5u): return ExecuteBinaryOpDataRegisterToAddressDisplacement<Eor, Byte>(m68000, opcode);
        case SizeMode(4u, 6u): return ExecuteBinaryOpDataRegisterToAddressIndex<Eor, Byte>(m68000, opcode);
        case SizeMode(4u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpDataRegisterToShort<Eor, Byte>(m68000, opcode);
                case 1u: return ExecuteBinaryOpDataRegisterToLong<Eor, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // EOR.W Dx, <ea>, CMPM.W (Ay)+, (Ax)+
        case SizeMode(5u, 0u): return ExecuteBinaryOpDataRegisterXToDataRegisterY<Eor, Word>(m68000, opcode);
        case SizeMode(5u, 1u): return ExecuteMultiprecisionOpAddressIncrementToAddressIncrement<Cmp, Word>(m68000, opcode);
        case SizeMode(5u, 2u): return ExecuteBinaryOpDataRegisterToAddressIndirect<Eor, Word>(m68000, opcode);
        case SizeMode(5u, 3u): return ExecuteBinaryOpDataRegisterToAddressIncrement<Eor, Word>(m68000, opcode);
        case SizeMode(5u, 4u): return ExecuteBinaryOpDataRegisterToAddressDecrement<Eor, Word>(m68000, opcode);
        case SizeMode(5u, 5u): return ExecuteBinaryOpDataRegisterToAddressDisplacement<Eor, Word>(m68000, opcode);
        case SizeMode(5u, 6u): return ExecuteBinaryOpDataRegisterToAddressIndex<Eor, Word>(m68000, opcode);
        case SizeMode(5u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpDataRegisterToShort<Eor, Word>(m68000, opcode);
                case 1u: return ExecuteBinaryOpDataRegisterToLong<Eor, Word>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // EOR.L Dx, <ea>, CMPM.L (Ay)+, (Ax)+
        case SizeMode(6u, 0u): return ExecuteBinaryOpDataRegisterXToDataRegisterY<Eor, Long>(m68000, opcode);
        case SizeMode(6u, 1u): return ExecuteMultiprecisionOpAddressIncrementToAddressIncrement<Cmp, Long>(m68000, opcode);
        case SizeMode(6u, 2u): return ExecuteBinaryOpDataRegisterToAddressIndirect<Eor, Long>(m68000, opcode);
        case SizeMode(6u, 3u): return ExecuteBinaryOpDataRegisterToAddressIncrement<Eor, Long>(m68000, opcode);
        case SizeMode(6u, 4u): return ExecuteBinaryOpDataRegisterToAddressDecrement<Eor, Long>(m68000, opcode);
        case SizeMode(6u, 5u): return ExecuteBinaryOpDataRegisterToAddressDisplacement<Eor, Long>(m68000, opcode);
        case SizeMode(6u, 6u): return ExecuteBinaryOpDataRegisterToAddressIndex<Eor, Long>(m68000, opcode);
        case SizeMode(6u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpDataRegisterToShort<Eor, Long>(m68000, opcode);
                case 1u: return ExecuteBinaryOpDataRegisterToLong<Eor, Long>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // CMPA.L <ea>, Ax
        case SizeMode(7u, 0u): return ExecuteBinaryOpDataRegisterToAddressRegister<Cmpa, Long>(m68000, opcode);
        case SizeMode(7u, 1u): return ExecuteBinaryOpAddressRegisterToAddressRegister<Cmpa, Long>(m68000, opcode);
        case SizeMode(7u, 2u): return ExecuteBinaryOpAddressIndirectToAddressRegister<Cmpa, Long>(m68000, opcode);
        case SizeMode(7u, 3u): return ExecuteBinaryOpAddressIncrementToAddressRegister<Cmpa, Long>(m68000, opcode);
        case SizeMode(7u, 4u): return ExecuteBinaryOpAddressDecrementToAddressRegister<Cmpa, Long>(m68000, opcode);
        case SizeMode(7u, 5u): return ExecuteBinaryOpAddressDisplacementToAddressRegister<Cmpa, Long>(m68000, opcode);
        case SizeMode(7u, 6u): return ExecuteBinaryOpAddressIndexToAddressRegister<Cmpa, Long>(m68000, opcode);
        case SizeMode(7u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpShortToAddressRegister<Cmpa, Long>(m68000, opcode);
                case 1u: return ExecuteBinaryOpLongToAddressRegister<Cmpa, Long>(m68000, opcode);
                case 2u: return ExecuteBinaryOpPCDisplacementToAddressRegister<Cmpa, Long>(m68000, opcode);
                case 3u: return ExecuteBinaryOpPCIndexToAddressRegister<Cmpa, Long>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToAddressRegister<Cmpa, Long>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            [[unlikely]] default: return ExecuteIllegal(m68000);
    }
}

auto ExecuteLineC(M68000& m68000, uint32_t opcode) {
    using namespace addressing::standard;
    using namespace addressing::multiply;
    using namespace addressing::multiprecision;
    switch (opcode & SizeMode(7u, 7u)) {
        // AND.B <ea>, Dx
        case SizeMode(0u, 0u): return ExecuteBinaryOpDataRegisterToDataRegister<And, Byte>(m68000, opcode);
        case SizeMode(0u, 2u): return ExecuteBinaryOpAddressIndirectToDataRegister<And, Byte>(m68000, opcode);
        case SizeMode(0u, 3u): return ExecuteBinaryOpAddressIncrementToDataRegister<And, Byte>(m68000, opcode);
        case SizeMode(0u, 4u): return ExecuteBinaryOpAddressDecrementToDataRegister<And, Byte>(m68000, opcode);
        case SizeMode(0u, 5u): return ExecuteBinaryOpAddressDisplacementToDataRegister<And, Byte>(m68000, opcode);
        case SizeMode(0u, 6u): return ExecuteBinaryOpAddressIndexToDataRegister<And, Byte>(m68000, opcode);
        case SizeMode(0u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpShortToDataRegister<And, Byte>(m68000, opcode);
                case 1u: return ExecuteBinaryOpLongToDataRegister<And, Byte>(m68000, opcode);
                case 2u: return ExecuteBinaryOpPCDisplacementToDataRegister<And, Byte>(m68000, opcode);
                case 3u: return ExecuteBinaryOpPCIndexToDataRegister<And, Byte>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToDataRegister<And, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // AND.W <ea>, Dx
        case SizeMode(1u, 0u): return ExecuteBinaryOpDataRegisterToDataRegister<And, Word>(m68000, opcode);
        case SizeMode(1u, 2u): return ExecuteBinaryOpAddressIndirectToDataRegister<And, Word>(m68000, opcode);
        case SizeMode(1u, 3u): return ExecuteBinaryOpAddressIncrementToDataRegister<And, Word>(m68000, opcode);
        case SizeMode(1u, 4u): return ExecuteBinaryOpAddressDecrementToDataRegister<And, Word>(m68000, opcode);
        case SizeMode(1u, 5u): return ExecuteBinaryOpAddressDisplacementToDataRegister<And, Word>(m68000, opcode);
        case SizeMode(1u, 6u): return ExecuteBinaryOpAddressIndexToDataRegister<And, Word>(m68000, opcode);
        case SizeMode(1u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpShortToDataRegister<And, Word>(m68000, opcode);
                case 1u: return ExecuteBinaryOpLongToDataRegister<And, Word>(m68000, opcode);
                case 2u: return ExecuteBinaryOpPCDisplacementToDataRegister<And, Word>(m68000, opcode);
                case 3u: return ExecuteBinaryOpPCIndexToDataRegister<And, Word>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToDataRegister<And, Word>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // AND.L <ea>, Dx
        case SizeMode(2u, 0u): return ExecuteBinaryOpDataRegisterToDataRegister<And, Long>(m68000, opcode);
        case SizeMode(2u, 2u): return ExecuteBinaryOpAddressIndirectToDataRegister<And, Long>(m68000, opcode);
        case SizeMode(2u, 3u): return ExecuteBinaryOpAddressIncrementToDataRegister<And, Long>(m68000, opcode);
        case SizeMode(2u, 4u): return ExecuteBinaryOpAddressDecrementToDataRegister<And, Long>(m68000, opcode);
        case SizeMode(2u, 5u): return ExecuteBinaryOpAddressDisplacementToDataRegister<And, Long>(m68000, opcode);
        case SizeMode(2u, 6u): return ExecuteBinaryOpAddressIndexToDataRegister<And, Long>(m68000, opcode);
        case SizeMode(2u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpShortToDataRegister<And, Long>(m68000, opcode);
                case 1u: return ExecuteBinaryOpLongToDataRegister<And, Long>(m68000, opcode);
                case 2u: return ExecuteBinaryOpPCDisplacementToDataRegister<And, Long>(m68000, opcode);
                case 3u: return ExecuteBinaryOpPCIndexToDataRegister<And, Long>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToDataRegister<And, Long>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // MULU.W <ea>, Dx
        case SizeMode(3u, 0u): return ExecuteMultiplyOpDataRegisterToDataRegister<Mulu, Word>(m68000, opcode);
        case SizeMode(3u, 2u): return ExecuteMultiplyOpAddressIndirectToDataRegister<Mulu, Word>(m68000, opcode);
        case SizeMode(3u, 3u): return ExecuteMultiplyOpAddressIncrementToDataRegister<Mulu, Word>(m68000, opcode);
        case SizeMode(3u, 4u): return ExecuteMultiplyOpAddressDecrementToDataRegister<Mulu, Word>(m68000, opcode);
        case SizeMode(3u, 5u): return ExecuteMultiplyOpAddressDisplacementToDataRegister<Mulu, Word>(m68000, opcode);
        case SizeMode(3u, 6u): return ExecuteMultiplyOpAddressIndexToDataRegister<Mulu, Word>(m68000, opcode);
        case SizeMode(3u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteMultiplyOpShortToDataRegister<Mulu, Word>(m68000, opcode);
                case 1u: return ExecuteMultiplyOpLongToDataRegister<Mulu, Word>(m68000, opcode);
                case 2u: return ExecuteMultiplyOpPCDisplacementToDataRegister<Mulu, Word>(m68000, opcode);
                case 3u: return ExecuteMultiplyOpPCIndexToDataRegister<Mulu, Word>(m68000, opcode);
                case 4u: return ExecuteMultiplyOpImmediateToDataRegister<Mulu, Word>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // ABCD Dy, Dx, ABCD -(Ay), -(Ax), AND.B Dx, <ea>
        case SizeMode(4u, 0u): return ExecuteMultiprecisionOpDataRegisterToDataRegister<Abcd, Byte>(m68000, opcode);
        case SizeMode(4u, 1u): return ExecuteMultiprecisionOpAddressDecrementToAddressDecrement<Abcd, Byte>(m68000, opcode);
        case SizeMode(4u, 2u): return ExecuteBinaryOpDataRegisterToAddressIndirect<And, Byte>(m68000, opcode);
        case SizeMode(4u, 3u): return ExecuteBinaryOpDataRegisterToAddressIncrement<And, Byte>(m68000, opcode);
        case SizeMode(4u, 4u): return ExecuteBinaryOpDataRegisterToAddressDecrement<And, Byte>(m68000, opcode);
        case SizeMode(4u, 5u): return ExecuteBinaryOpDataRegisterToAddressDisplacement<And, Byte>(m68000, opcode);
        case SizeMode(4u, 6u): return ExecuteBinaryOpDataRegisterToAddressIndex<And, Byte>(m68000, opcode);
        case SizeMode(4u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpDataRegisterToShort<And, Byte>(m68000, opcode);
                case 1u: return ExecuteBinaryOpDataRegisterToLong<And, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // AND.W Dx, <ea>
        case SizeMode(5u, 0u): return ExecuteExgDataRegisterWithDataRegister(m68000, opcode);
        case SizeMode(5u, 1u): return ExecuteExgAddressRegisterWithAddressRegister(m68000, opcode);
        case SizeMode(5u, 2u): return ExecuteBinaryOpDataRegisterToAddressIndirect<And, Word>(m68000, opcode);
        case SizeMode(5u, 3u): return ExecuteBinaryOpDataRegisterToAddressIncrement<And, Word>(m68000, opcode);
        case SizeMode(5u, 4u): return ExecuteBinaryOpDataRegisterToAddressDecrement<And, Word>(m68000, opcode);
        case SizeMode(5u, 5u): return ExecuteBinaryOpDataRegisterToAddressDisplacement<And, Word>(m68000, opcode);
        case SizeMode(5u, 6u): return ExecuteBinaryOpDataRegisterToAddressIndex<And, Word>(m68000, opcode);
        case SizeMode(5u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpDataRegisterToShort<And, Word>(m68000, opcode);
                case 1u: return ExecuteBinaryOpDataRegisterToLong<And, Word>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // AND.L Dx, <ea>
        case SizeMode(6u, 1u): return ExecuteExgDataRegisterWithAddressRegister(m68000, opcode);
        case SizeMode(6u, 2u): return ExecuteBinaryOpDataRegisterToAddressIndirect<And, Long>(m68000, opcode);
        case SizeMode(6u, 3u): return ExecuteBinaryOpDataRegisterToAddressIncrement<And, Long>(m68000, opcode);
        case SizeMode(6u, 4u): return ExecuteBinaryOpDataRegisterToAddressDecrement<And, Long>(m68000, opcode);
        case SizeMode(6u, 5u): return ExecuteBinaryOpDataRegisterToAddressDisplacement<And, Long>(m68000, opcode);
        case SizeMode(6u, 6u): return ExecuteBinaryOpDataRegisterToAddressIndex<And, Long>(m68000, opcode);
        case SizeMode(6u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpDataRegisterToShort<And, Long>(m68000, opcode);
                case 1u: return ExecuteBinaryOpDataRegisterToLong<And, Long>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // MULS.W <ea>, Dx
        case SizeMode(7u, 0u): return ExecuteMultiplyOpDataRegisterToDataRegister<Muls, Word>(m68000, opcode);
        case SizeMode(7u, 2u): return ExecuteMultiplyOpAddressIndirectToDataRegister<Muls, Word>(m68000, opcode);
        case SizeMode(7u, 3u): return ExecuteMultiplyOpAddressIncrementToDataRegister<Muls, Word>(m68000, opcode);
        case SizeMode(7u, 4u): return ExecuteMultiplyOpAddressDecrementToDataRegister<Muls, Word>(m68000, opcode);
        case SizeMode(7u, 5u): return ExecuteMultiplyOpAddressDisplacementToDataRegister<Muls, Word>(m68000, opcode);
        case SizeMode(7u, 6u): return ExecuteMultiplyOpAddressIndexToDataRegister<Muls, Word>(m68000, opcode);
        case SizeMode(7u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteMultiplyOpShortToDataRegister<Muls, Word>(m68000, opcode);
                case 1u: return ExecuteMultiplyOpLongToDataRegister<Muls, Word>(m68000, opcode);
                case 2u: return ExecuteMultiplyOpPCDisplacementToDataRegister<Muls, Word>(m68000, opcode);
                case 3u: return ExecuteMultiplyOpPCIndexToDataRegister<Muls, Word>(m68000, opcode);
                case 4u: return ExecuteMultiplyOpImmediateToDataRegister<Muls, Word>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            [[unlikely]] default: return ExecuteIllegal(m68000);
    }
}

auto ExecuteLineD(M68000& m68000, uint32_t opcode) {
    using namespace addressing::standard;
    using namespace addressing::address;
    using namespace addressing::multiprecision;
    switch (opcode & SizeMode(7u, 7u)) {
        // ADD.B <ea>, Dx
        case SizeMode(0u, 0u): return ExecuteBinaryOpDataRegisterToDataRegister<Add, Byte>(m68000, opcode);
        case SizeMode(0u, 2u): return ExecuteBinaryOpAddressIndirectToDataRegister<Add, Byte>(m68000, opcode);
        case SizeMode(0u, 3u): return ExecuteBinaryOpAddressIncrementToDataRegister<Add, Byte>(m68000, opcode);
        case SizeMode(0u, 4u): return ExecuteBinaryOpAddressDecrementToDataRegister<Add, Byte>(m68000, opcode);
        case SizeMode(0u, 5u): return ExecuteBinaryOpAddressDisplacementToDataRegister<Add, Byte>(m68000, opcode);
        case SizeMode(0u, 6u): return ExecuteBinaryOpAddressIndexToDataRegister<Add, Byte>(m68000, opcode);
        case SizeMode(0u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpShortToDataRegister<Add, Byte>(m68000, opcode);
                case 1u: return ExecuteBinaryOpLongToDataRegister<Add, Byte>(m68000, opcode);
                case 2u: return ExecuteBinaryOpPCDisplacementToDataRegister<Add, Byte>(m68000, opcode);
                case 3u: return ExecuteBinaryOpPCIndexToDataRegister<Add, Byte>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToDataRegister<Add, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // ADD.W <ea>, Dx
        case SizeMode(1u, 0u): return ExecuteBinaryOpDataRegisterToDataRegister<Add, Word>(m68000, opcode);
        case SizeMode(1u, 1u): return ExecuteBinaryOpAddressRegisterToDataRegister<Add, Word>(m68000, opcode);
        case SizeMode(1u, 2u): return ExecuteBinaryOpAddressIndirectToDataRegister<Add, Word>(m68000, opcode);
        case SizeMode(1u, 3u): return ExecuteBinaryOpAddressIncrementToDataRegister<Add, Word>(m68000, opcode);
        case SizeMode(1u, 4u): return ExecuteBinaryOpAddressDecrementToDataRegister<Add, Word>(m68000, opcode);
        case SizeMode(1u, 5u): return ExecuteBinaryOpAddressDisplacementToDataRegister<Add, Word>(m68000, opcode);
        case SizeMode(1u, 6u): return ExecuteBinaryOpAddressIndexToDataRegister<Add, Word>(m68000, opcode);
        case SizeMode(1u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpShortToDataRegister<Add, Word>(m68000, opcode);
                case 1u: return ExecuteBinaryOpLongToDataRegister<Add, Word>(m68000, opcode);
                case 2u: return ExecuteBinaryOpPCDisplacementToDataRegister<Add, Word>(m68000, opcode);
                case 3u: return ExecuteBinaryOpPCIndexToDataRegister<Add, Word>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToDataRegister<Add, Word>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // ADD.L <ea>, Dx
        case SizeMode(2u, 0u): return ExecuteBinaryOpDataRegisterToDataRegister<Add, Long>(m68000, opcode);
        case SizeMode(2u, 1u): return ExecuteBinaryOpAddressRegisterToDataRegister<Add, Long>(m68000, opcode);
        case SizeMode(2u, 2u): return ExecuteBinaryOpAddressIndirectToDataRegister<Add, Long>(m68000, opcode);
        case SizeMode(2u, 3u): return ExecuteBinaryOpAddressIncrementToDataRegister<Add, Long>(m68000, opcode);
        case SizeMode(2u, 4u): return ExecuteBinaryOpAddressDecrementToDataRegister<Add, Long>(m68000, opcode);
        case SizeMode(2u, 5u): return ExecuteBinaryOpAddressDisplacementToDataRegister<Add, Long>(m68000, opcode);
        case SizeMode(2u, 6u): return ExecuteBinaryOpAddressIndexToDataRegister<Add, Long>(m68000, opcode);
        case SizeMode(2u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpShortToDataRegister<Add, Long>(m68000, opcode);
                case 1u: return ExecuteBinaryOpLongToDataRegister<Add, Long>(m68000, opcode);
                case 2u: return ExecuteBinaryOpPCDisplacementToDataRegister<Add, Long>(m68000, opcode);
                case 3u: return ExecuteBinaryOpPCIndexToDataRegister<Add, Long>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToDataRegister<Add, Long>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // ADDA.W <ea>, Ax
        case SizeMode(3u, 0u): return ExecuteBinaryOpDataRegisterToAddressRegister<Adda, Word>(m68000, opcode);
        case SizeMode(3u, 1u): return ExecuteBinaryOpAddressRegisterToAddressRegister<Adda, Word>(m68000, opcode);
        case SizeMode(3u, 2u): return ExecuteBinaryOpAddressIndirectToAddressRegister<Adda, Word>(m68000, opcode);
        case SizeMode(3u, 3u): return ExecuteBinaryOpAddressIncrementToAddressRegister<Adda, Word>(m68000, opcode);
        case SizeMode(3u, 4u): return ExecuteBinaryOpAddressDecrementToAddressRegister<Adda, Word>(m68000, opcode);
        case SizeMode(3u, 5u): return ExecuteBinaryOpAddressDisplacementToAddressRegister<Adda, Word>(m68000, opcode);
        case SizeMode(3u, 6u): return ExecuteBinaryOpAddressIndexToAddressRegister<Adda, Word>(m68000, opcode);
        case SizeMode(3u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpShortToAddressRegister<Adda, Word>(m68000, opcode);
                case 1u: return ExecuteBinaryOpLongToAddressRegister<Adda, Word>(m68000, opcode);
                case 2u: return ExecuteBinaryOpPCDisplacementToAddressRegister<Adda, Word>(m68000, opcode);
                case 3u: return ExecuteBinaryOpPCIndexToAddressRegister<Adda, Word>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToAddressRegister<Adda, Word>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // ADDX.B Dy, Dx, ADDX.B -(Ay), -(Ax), ADD.B Dx, <ea>
        case SizeMode(4u, 0u): return ExecuteMultiprecisionOpDataRegisterToDataRegister<Addx, Byte>(m68000, opcode);
        case SizeMode(4u, 1u): return ExecuteMultiprecisionOpAddressDecrementToAddressDecrement<Addx, Byte>(m68000, opcode);
        case SizeMode(4u, 2u): return ExecuteBinaryOpDataRegisterToAddressIndirect<Add, Byte>(m68000, opcode);
        case SizeMode(4u, 3u): return ExecuteBinaryOpDataRegisterToAddressIncrement<Add, Byte>(m68000, opcode);
        case SizeMode(4u, 4u): return ExecuteBinaryOpDataRegisterToAddressDecrement<Add, Byte>(m68000, opcode);
        case SizeMode(4u, 5u): return ExecuteBinaryOpDataRegisterToAddressDisplacement<Add, Byte>(m68000, opcode);
        case SizeMode(4u, 6u): return ExecuteBinaryOpDataRegisterToAddressIndex<Add, Byte>(m68000, opcode);
        case SizeMode(4u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpDataRegisterToShort<Add, Byte>(m68000, opcode);
                case 1u: return ExecuteBinaryOpDataRegisterToLong<Add, Byte>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // ADDX.W Dy, Dx, ADDX.W -(Ay), -(Ax), ADD.W Dx, <ea>
        case SizeMode(5u, 0u): return ExecuteMultiprecisionOpDataRegisterToDataRegister<Addx, Word>(m68000, opcode);
        case SizeMode(5u, 1u): return ExecuteMultiprecisionOpAddressDecrementToAddressDecrement<Addx, Word>(m68000, opcode);
        case SizeMode(5u, 2u): return ExecuteBinaryOpDataRegisterToAddressIndirect<Add, Word>(m68000, opcode);
        case SizeMode(5u, 3u): return ExecuteBinaryOpDataRegisterToAddressIncrement<Add, Word>(m68000, opcode);
        case SizeMode(5u, 4u): return ExecuteBinaryOpDataRegisterToAddressDecrement<Add, Word>(m68000, opcode);
        case SizeMode(5u, 5u): return ExecuteBinaryOpDataRegisterToAddressDisplacement<Add, Word>(m68000, opcode);
        case SizeMode(5u, 6u): return ExecuteBinaryOpDataRegisterToAddressIndex<Add, Word>(m68000, opcode);
        case SizeMode(5u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpDataRegisterToShort<Add, Word>(m68000, opcode);
                case 1u: return ExecuteBinaryOpDataRegisterToLong<Add, Word>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // ADDX.L Dy, Dx, ADDX.L -(Ay), -(Ax), ADD.L Dx, <ea>
        case SizeMode(6u, 0u): return ExecuteMultiprecisionOpDataRegisterToDataRegister<Addx, Long>(m68000, opcode);
        case SizeMode(6u, 1u): return ExecuteMultiprecisionOpAddressDecrementToAddressDecrement<Addx, Long>(m68000, opcode);
        case SizeMode(6u, 2u): return ExecuteBinaryOpDataRegisterToAddressIndirect<Add, Long>(m68000, opcode);
        case SizeMode(6u, 3u): return ExecuteBinaryOpDataRegisterToAddressIncrement<Add, Long>(m68000, opcode);
        case SizeMode(6u, 4u): return ExecuteBinaryOpDataRegisterToAddressDecrement<Add, Long>(m68000, opcode);
        case SizeMode(6u, 5u): return ExecuteBinaryOpDataRegisterToAddressDisplacement<Add, Long>(m68000, opcode);
        case SizeMode(6u, 6u): return ExecuteBinaryOpDataRegisterToAddressIndex<Add, Long>(m68000, opcode);
        case SizeMode(6u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpDataRegisterToShort<Add, Long>(m68000, opcode);
                case 1u: return ExecuteBinaryOpDataRegisterToLong<Add, Long>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // ADDA.L <ea>, Ax
        case SizeMode(7u, 0u): return ExecuteBinaryOpDataRegisterToAddressRegister<Adda, Long>(m68000, opcode);
        case SizeMode(7u, 1u): return ExecuteBinaryOpAddressRegisterToAddressRegister<Adda, Long>(m68000, opcode);
        case SizeMode(7u, 2u): return ExecuteBinaryOpAddressIndirectToAddressRegister<Adda, Long>(m68000, opcode);
        case SizeMode(7u, 3u): return ExecuteBinaryOpAddressIncrementToAddressRegister<Adda, Long>(m68000, opcode);
        case SizeMode(7u, 4u): return ExecuteBinaryOpAddressDecrementToAddressRegister<Adda, Long>(m68000, opcode);
        case SizeMode(7u, 5u): return ExecuteBinaryOpAddressDisplacementToAddressRegister<Adda, Long>(m68000, opcode);
        case SizeMode(7u, 6u): return ExecuteBinaryOpAddressIndexToAddressRegister<Adda, Long>(m68000, opcode);
        case SizeMode(7u, 7u):
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBinaryOpShortToAddressRegister<Adda, Long>(m68000, opcode);
                case 1u: return ExecuteBinaryOpLongToAddressRegister<Adda, Long>(m68000, opcode);
                case 2u: return ExecuteBinaryOpPCDisplacementToAddressRegister<Adda, Long>(m68000, opcode);
                case 3u: return ExecuteBinaryOpPCIndexToAddressRegister<Adda, Long>(m68000, opcode);
                case 4u: return ExecuteBinaryOpImmediateToAddressRegister<Adda, Long>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // Illegal
            [[unlikely]] default: return ExecuteIllegal(m68000);
    }
}

auto ExecuteLineE(M68000& m68000, uint32_t opcode) {
    using namespace addressing::shift_rotate;
    switch (opcode & SizeMode(7u, 7u)) {
        // {ASR|LSR|ROXR|ROR}.B #data, Dy
        case SizeMode(0u, 0u): return ExecuteShiftRotateOpCountToDataRegister<Asr, Byte>(m68000, opcode);
        case SizeMode(0u, 1u): return ExecuteShiftRotateOpCountToDataRegister<Lsr, Byte>(m68000, opcode);
        case SizeMode(0u, 2u): return ExecuteShiftRotateOpCountToDataRegister<Roxr, Byte>(m68000, opcode);
        case SizeMode(0u, 3u): return ExecuteShiftRotateOpCountToDataRegister<Ror, Byte>(m68000, opcode);
            // {ASR|LSR|ROXR|ROR}.B Dx, Dy
        case SizeMode(0u, 4u): return ExecuteShiftRotateOpRegisterToDataRegister<Asr, Byte>(m68000, opcode);
        case SizeMode(0u, 5u): return ExecuteShiftRotateOpRegisterToDataRegister<Lsr, Byte>(m68000, opcode);
        case SizeMode(0u, 6u): return ExecuteShiftRotateOpRegisterToDataRegister<Roxr, Byte>(m68000, opcode);
        case SizeMode(0u, 7u): return ExecuteShiftRotateOpRegisterToDataRegister<Ror, Byte>(m68000, opcode);
            // {ASR|LSR|ROXR|ROR}.W #data, Dy
        case SizeMode(1u, 0u): return ExecuteShiftRotateOpCountToDataRegister<Asr, Word>(m68000, opcode);
        case SizeMode(1u, 1u): return ExecuteShiftRotateOpCountToDataRegister<Lsr, Word>(m68000, opcode);
        case SizeMode(1u, 2u): return ExecuteShiftRotateOpCountToDataRegister<Roxr, Word>(m68000, opcode);
        case SizeMode(1u, 3u): return ExecuteShiftRotateOpCountToDataRegister<Ror, Word>(m68000, opcode);
            // {ASR|LSR|ROXR|ROR}.W Dx, Dy
        case SizeMode(1u, 4u): return ExecuteShiftRotateOpRegisterToDataRegister<Asr, Word>(m68000, opcode);
        case SizeMode(1u, 5u): return ExecuteShiftRotateOpRegisterToDataRegister<Lsr, Word>(m68000, opcode);
        case SizeMode(1u, 6u): return ExecuteShiftRotateOpRegisterToDataRegister<Roxr, Word>(m68000, opcode);
        case SizeMode(1u, 7u): return ExecuteShiftRotateOpRegisterToDataRegister<Ror, Word>(m68000, opcode);
            // {ASR|LSR|ROXR|ROR}.L #data, Dy
        case SizeMode(2u, 0u): return ExecuteShiftRotateOpCountToDataRegister<Asr, Long>(m68000, opcode);
        case SizeMode(2u, 1u): return ExecuteShiftRotateOpCountToDataRegister<Lsr, Long>(m68000, opcode);
        case SizeMode(2u, 2u): return ExecuteShiftRotateOpCountToDataRegister<Roxr, Long>(m68000, opcode);
        case SizeMode(2u, 3u): return ExecuteShiftRotateOpCountToDataRegister<Ror, Long>(m68000, opcode);
            // {ASR|LSR|ROXR|ROR}.L Dx, Dy
        case SizeMode(2u, 4u): return ExecuteShiftRotateOpRegisterToDataRegister<Asr, Long>(m68000, opcode);
        case SizeMode(2u, 5u): return ExecuteShiftRotateOpRegisterToDataRegister<Lsr, Long>(m68000, opcode);
        case SizeMode(2u, 6u): return ExecuteShiftRotateOpRegisterToDataRegister<Roxr, Long>(m68000, opcode);
        case SizeMode(2u, 7u): return ExecuteShiftRotateOpRegisterToDataRegister<Ror, Long>(m68000, opcode);
            // {ASR|LSR|ROXR|ROR}.W (Ay)
        case SizeMode(3u, 2u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteShiftRotateOpToAddressIndirect<Asr>(m68000, opcode);
                case 1u: return ExecuteShiftRotateOpToAddressIndirect<Lsr>(m68000, opcode);
                case 2u: return ExecuteShiftRotateOpToAddressIndirect<Roxr>(m68000, opcode);
                case 3u: return ExecuteShiftRotateOpToAddressIndirect<Ror>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {ASR|LSR|ROXR|ROR}.W (Ay)+
        case SizeMode(3u, 3u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteShiftRotateOpToAddressIncrement<Asr>(m68000, opcode);
                case 1u: return ExecuteShiftRotateOpToAddressIncrement<Lsr>(m68000, opcode);
                case 2u: return ExecuteShiftRotateOpToAddressIncrement<Roxr>(m68000, opcode);
                case 3u: return ExecuteShiftRotateOpToAddressIncrement<Ror>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {ASR|LSR|ROXR|ROR}.W -(Ay)
        case SizeMode(3u, 4u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteShiftRotateOpToAddressDecrement<Asr>(m68000, opcode);
                case 1u: return ExecuteShiftRotateOpToAddressDecrement<Lsr>(m68000, opcode);
                case 2u: return ExecuteShiftRotateOpToAddressDecrement<Roxr>(m68000, opcode);
                case 3u: return ExecuteShiftRotateOpToAddressDecrement<Ror>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {ASR|LSR|ROXR|ROR}.W (d, Ay)
        case SizeMode(3u, 5u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteShiftRotateOpToAddressDisplacement<Asr>(m68000, opcode);
                case 1u: return ExecuteShiftRotateOpToAddressDisplacement<Lsr>(m68000, opcode);
                case 2u: return ExecuteShiftRotateOpToAddressDisplacement<Roxr>(m68000, opcode);
                case 3u: return ExecuteShiftRotateOpToAddressDisplacement<Ror>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {ASR|LSR|ROXR|ROR}.W (d, Ay, Xn)
        case SizeMode(3u, 6u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteShiftRotateOpToAddressIndex<Asr>(m68000, opcode);
                case 1u: return ExecuteShiftRotateOpToAddressIndex<Lsr>(m68000, opcode);
                case 2u: return ExecuteShiftRotateOpToAddressIndex<Roxr>(m68000, opcode);
                case 3u: return ExecuteShiftRotateOpToAddressIndex<Ror>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {ASR|LSR|ROXR|ROR}.W (address).{W|L}
        case SizeMode(3u, 7u):
            switch (opcode & RegisterXY(7u, 7u)) {
                case RegisterXY(0u, 0u): return ExecuteShiftRotateOpToShort<Asr>(m68000, opcode);
                case RegisterXY(1u, 0u): return ExecuteShiftRotateOpToShort<Lsr>(m68000, opcode);
                case RegisterXY(2u, 0u): return ExecuteShiftRotateOpToShort<Roxr>(m68000, opcode);
                case RegisterXY(3u, 0u): return ExecuteShiftRotateOpToShort<Ror>(m68000, opcode);
                case RegisterXY(0u, 1u): return ExecuteShiftRotateOpToLong<Asr>(m68000, opcode);
                case RegisterXY(1u, 1u): return ExecuteShiftRotateOpToLong<Lsr>(m68000, opcode);
                case RegisterXY(2u, 1u): return ExecuteShiftRotateOpToLong<Roxr>(m68000, opcode);
                case RegisterXY(3u, 1u): return ExecuteShiftRotateOpToLong<Ror>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {ASL|LSL|ROXL|ROL}.B #data, Dy
        case SizeMode(4u, 0u): return ExecuteShiftRotateOpCountToDataRegister<Asl, Byte>(m68000, opcode);
        case SizeMode(4u, 1u): return ExecuteShiftRotateOpCountToDataRegister<Lsl, Byte>(m68000, opcode);
        case SizeMode(4u, 2u): return ExecuteShiftRotateOpCountToDataRegister<Roxl, Byte>(m68000, opcode);
        case SizeMode(4u, 3u): return ExecuteShiftRotateOpCountToDataRegister<Rol, Byte>(m68000, opcode);
            // {ASL|LSL|ROXL|ROL}.B Dx, Dy
        case SizeMode(4u, 4u): return ExecuteShiftRotateOpRegisterToDataRegister<Asl, Byte>(m68000, opcode);
        case SizeMode(4u, 5u): return ExecuteShiftRotateOpRegisterToDataRegister<Lsl, Byte>(m68000, opcode);
        case SizeMode(4u, 6u): return ExecuteShiftRotateOpRegisterToDataRegister<Roxl, Byte>(m68000, opcode);
        case SizeMode(4u, 7u): return ExecuteShiftRotateOpRegisterToDataRegister<Rol, Byte>(m68000, opcode);
            // {ASL|LSL|ROXL|ROL}.W #data, Dy
        case SizeMode(5u, 0u): return ExecuteShiftRotateOpCountToDataRegister<Asl, Word>(m68000, opcode);
        case SizeMode(5u, 1u): return ExecuteShiftRotateOpCountToDataRegister<Lsl, Word>(m68000, opcode);
        case SizeMode(5u, 2u): return ExecuteShiftRotateOpCountToDataRegister<Roxl, Word>(m68000, opcode);
        case SizeMode(5u, 3u): return ExecuteShiftRotateOpCountToDataRegister<Rol, Word>(m68000, opcode);
            // {ASL|LSL|ROXL|ROL}.W Dx, Dy
        case SizeMode(5u, 4u): return ExecuteShiftRotateOpRegisterToDataRegister<Asl, Word>(m68000, opcode);
        case SizeMode(5u, 5u): return ExecuteShiftRotateOpRegisterToDataRegister<Lsl, Word>(m68000, opcode);
        case SizeMode(5u, 6u): return ExecuteShiftRotateOpRegisterToDataRegister<Roxl, Word>(m68000, opcode);
        case SizeMode(5u, 7u): return ExecuteShiftRotateOpRegisterToDataRegister<Rol, Word>(m68000, opcode);
            // {ASL|LSL|ROXL|ROL}.L #data, Dy
        case SizeMode(6u, 0u): return ExecuteShiftRotateOpCountToDataRegister<Asl, Long>(m68000, opcode);
        case SizeMode(6u, 1u): return ExecuteShiftRotateOpCountToDataRegister<Lsl, Long>(m68000, opcode);
        case SizeMode(6u, 2u): return ExecuteShiftRotateOpCountToDataRegister<Roxl, Long>(m68000, opcode);
        case SizeMode(6u, 3u): return ExecuteShiftRotateOpCountToDataRegister<Rol, Long>(m68000, opcode);
            // {ASL|LSL|ROXL|ROL}.L Dx, Dy
        case SizeMode(6u, 4u): return ExecuteShiftRotateOpRegisterToDataRegister<Asl, Long>(m68000, opcode);
        case SizeMode(6u, 5u): return ExecuteShiftRotateOpRegisterToDataRegister<Lsl, Long>(m68000, opcode);
        case SizeMode(6u, 6u): return ExecuteShiftRotateOpRegisterToDataRegister<Roxl, Long>(m68000, opcode);
        case SizeMode(6u, 7u): return ExecuteShiftRotateOpRegisterToDataRegister<Rol, Long>(m68000, opcode);
            // {ASL|LSL|ROXL|ROL}.W (Ay)
        case SizeMode(7, 2u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteShiftRotateOpToAddressIndirect<Asl>(m68000, opcode);
                case 1u: return ExecuteShiftRotateOpToAddressIndirect<Lsl>(m68000, opcode);
                case 2u: return ExecuteShiftRotateOpToAddressIndirect<Roxl>(m68000, opcode);
                case 3u: return ExecuteShiftRotateOpToAddressIndirect<Rol>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {ASL|LSL|ROXL|ROL}.W (Ay)+
        case SizeMode(7, 3u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteShiftRotateOpToAddressIncrement<Asl>(m68000, opcode);
                case 1u: return ExecuteShiftRotateOpToAddressIncrement<Lsl>(m68000, opcode);
                case 2u: return ExecuteShiftRotateOpToAddressIncrement<Roxl>(m68000, opcode);
                case 3u: return ExecuteShiftRotateOpToAddressIncrement<Rol>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {ASL|LSL|ROXL|ROL}.W -(Ay)
        case SizeMode(7, 4u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteShiftRotateOpToAddressDecrement<Asl>(m68000, opcode);
                case 1u: return ExecuteShiftRotateOpToAddressDecrement<Lsl>(m68000, opcode);
                case 2u: return ExecuteShiftRotateOpToAddressDecrement<Roxl>(m68000, opcode);
                case 3u: return ExecuteShiftRotateOpToAddressDecrement<Rol>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {ASL|LSL|ROXL|ROL}.W (d, Ay)
        case SizeMode(7, 5u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteShiftRotateOpToAddressDisplacement<Asl>(m68000, opcode);
                case 1u: return ExecuteShiftRotateOpToAddressDisplacement<Lsl>(m68000, opcode);
                case 2u: return ExecuteShiftRotateOpToAddressDisplacement<Roxl>(m68000, opcode);
                case 3u: return ExecuteShiftRotateOpToAddressDisplacement<Rol>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {ASL|LSL|ROXL|ROL}.W (d, Ay, Xn)
        case SizeMode(7, 6u):
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteShiftRotateOpToAddressIndex<Asl>(m68000, opcode);
                case 1u: return ExecuteShiftRotateOpToAddressIndex<Lsl>(m68000, opcode);
                case 2u: return ExecuteShiftRotateOpToAddressIndex<Roxl>(m68000, opcode);
                case 3u: return ExecuteShiftRotateOpToAddressIndex<Rol>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            // {ASL|LSL|ROXL|ROL}.W (address).{W|L}
        case SizeMode(7, 7u):
            switch (opcode & RegisterXY(7u, 7u)) {
                case RegisterXY(0u, 0u): return ExecuteShiftRotateOpToShort<Asl>(m68000, opcode);
                case RegisterXY(1u, 0u): return ExecuteShiftRotateOpToShort<Lsl>(m68000, opcode);
                case RegisterXY(2u, 0u): return ExecuteShiftRotateOpToShort<Roxl>(m68000, opcode);
                case RegisterXY(3u, 0u): return ExecuteShiftRotateOpToShort<Rol>(m68000, opcode);
                case RegisterXY(0u, 1u): return ExecuteShiftRotateOpToLong<Asl>(m68000, opcode);
                case RegisterXY(1u, 1u): return ExecuteShiftRotateOpToLong<Lsl>(m68000, opcode);
                case RegisterXY(2u, 1u): return ExecuteShiftRotateOpToLong<Roxl>(m68000, opcode);
                case RegisterXY(3u, 1u): return ExecuteShiftRotateOpToLong<Rol>(m68000, opcode);
                    [[unlikely]] default: return ExecuteIllegal(m68000);
            }
            [[unlikely]] default: return ExecuteIllegal(m68000);
    }
}

auto ExecuteLineF(M68000& m68000, uint32_t) {
    if (!ExecuteFinalPrefetchCycle(m68000)) {
        return;
    }
    RaiseLineFEmulatorException(m68000);
}

auto ExecuteInner(M68000& m68000) {
    const auto opcode = m68000.ReadIRD();
    switch (OpcodeLine(opcode)) {
        case 0x0u: return ExecuteLine0(m68000, opcode);
        case 0x1u: return ExecuteLine1(m68000, opcode);
        case 0x2u: return ExecuteLine2(m68000, opcode);
        case 0x3u: return ExecuteLine3(m68000, opcode);
        case 0x4u: return ExecuteLine4(m68000, opcode);
        case 0x5u: return ExecuteLine5(m68000, opcode);
        case 0x6u: return ExecuteLine6(m68000, opcode);
        case 0x7u: return ExecuteLine7(m68000, opcode);
        case 0x8u: return ExecuteLine8(m68000, opcode);
        case 0x9u: return ExecuteLine9(m68000, opcode);
        case 0xAu: return ExecuteLineA(m68000, opcode);
        case 0xBu: return ExecuteLineB(m68000, opcode);
        case 0xCu: return ExecuteLineC(m68000, opcode);
        case 0xDu: return ExecuteLineD(m68000, opcode);
        case 0xEu: return ExecuteLineE(m68000, opcode);
        case 0xFu: return ExecuteLineF(m68000, opcode);
            [[unlikely]] default: return ExecuteIllegal(m68000);
    }
}

auto Execute(M68000& m68000) {
    const auto oldLevel = GetInterruptLevel(m68000);
    if (m68000.ReadStopped()) [[unlikely]] {
        m68000.InternalCycle();
        m68000.InternalCycle();
    } else {
        ExecuteInner(m68000);
    }
    const auto newLevel = GetInterruptLevel(m68000);
    CheckInterrupts(m68000, oldLevel, newLevel);
}

}

auto M68000::Execute() -> void {
    ::rbrown::m68000::Execute(*this);
}

auto M68000::Reset() -> void {
    RaiseResetException(*this);
}

}
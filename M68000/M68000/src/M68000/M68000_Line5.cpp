#include "M68000/M68000.h"
#include "M68000/M68000_Opcode.h"
#include "M68000/M68000_EffectiveAddress.h"
#include "M68000/M68000_Operations.h"

using namespace rbrown::m68000;

auto M68000::ExecuteLine5(uint32_t opcode) -> void {
    switch (OpcodeModeX(opcode)) {
        case 0u: return ExecuteAddq<Byte>(opcode);
        case 1u: return ExecuteAddq<Word>(opcode);
        case 2u: return ExecuteAddq<Long>(opcode);
        case 3u: return ExecuteScc(opcode);
        case 4u: return ExecuteSubq<Byte>(opcode);
        case 5u: return ExecuteSubq<Word>(opcode);
        case 6u: return ExecuteSubq<Long>(opcode);
        case 7u: return ExecuteScc(opcode);
        default:return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteAddq(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteAddqDataRegister<T>(opcode);
        case 1u:
            if constexpr(std::is_same_v<T, Byte>) {
                return ExecuteIllegal();
            } else {
                return ExecuteAddqAddressRegister<T>(opcode);
            }
        case 2u: return ExecuteAddqEffectiveAddress<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteAddqEffectiveAddress<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteAddqEffectiveAddress<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteAddqEffectiveAddress<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteAddqEffectiveAddress<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteAddqEffectiveAddress<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteAddqEffectiveAddress<&M68000::ReadFromLong<T>, T>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteSubq(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteSubqDataRegister<T>(opcode);
        case 1u:
            if constexpr(std::is_same_v<T, Byte>) {
                return ExecuteIllegal();
            } else {
                return ExecuteSubqAddressRegister<T>(opcode);
            }
        case 2u: return ExecuteSubqEffectiveAddress<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteSubqEffectiveAddress<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteSubqEffectiveAddress<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteSubqEffectiveAddress<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteSubqEffectiveAddress<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteSubqEffectiveAddress<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteSubqEffectiveAddress<&M68000::ReadFromLong<T>, T>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteScc(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteSccDataRegister(opcode);
        case 1u: return ExecuteDbcc(opcode);
        case 2u: return ExecuteSccEffectiveAddress<&M68000::ReadFromAddressIndirect<Byte>>(opcode);
        case 3u: return ExecuteSccEffectiveAddress<&M68000::ReadFromAddressIncrement<Byte>>(opcode);
        case 4u: return ExecuteSccEffectiveAddress<&M68000::ReadFromAddressDecrement<Byte>>(opcode);
        case 5u: return ExecuteSccEffectiveAddress<&M68000::ReadFromAddressDisplacement<Byte>>(opcode);
        case 6u: return ExecuteSccEffectiveAddress<&M68000::ReadFromAddressIndex<Byte>>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteSccEffectiveAddress<&M68000::ReadFromShort<Byte>>(opcode);
                case 1u: return ExecuteSccEffectiveAddress<&M68000::ReadFromLong<Byte>>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

// ADDQ.{B|W|L} #imm, Dy

template<typename T>
auto M68000::ExecuteAddqDataRegister(uint32_t opcode) -> void {
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = ReadDataRegisterLong(ry);
    const auto result = Add<T>(OpcodeQuick(opcode), y);
    WriteDataRegister<T>(ry, result);
    if constexpr(std::is_same_v<T, Long>) {
        InternalCycle();
        InternalCycle();
    }
}

// ADDQ.{B|W|L} #imm, Ay

template<typename T>
auto M68000::ExecuteAddqAddressRegister(uint32_t opcode) -> void {
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = ReadAddressRegisterLong(ry);
    const auto result = Adda<T>(OpcodeQuick(opcode), y);
    WriteAddressRegisterLong(ry, result);
    InternalCycle();
    InternalCycle();
}

// ADDQ.{B|W|L} #imm, <ea>

template<auto Source, typename T>
auto M68000::ExecuteAddqEffectiveAddress(uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Add<T>(OpcodeQuick(opcode), y);
    WriteMemory<T>(address, result);
}

// SUBQ.{B|W|L} #imm, Dy

template<typename T>
auto M68000::ExecuteSubqDataRegister(uint32_t opcode) -> void {
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = ReadDataRegisterLong(ry);
    const auto result = Sub<T>(OpcodeQuick(opcode), y);
    WriteDataRegister<T>(ry, result);
    if constexpr(std::is_same_v<T, Long>) {
        InternalCycle();
        InternalCycle();
    }
}

// SUBQ.{B|W|L} #imm, Ay

template<typename T>
auto M68000::ExecuteSubqAddressRegister(uint32_t opcode) -> void {
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = ReadAddressRegisterLong(ry);
    const auto result = Suba<T>(OpcodeQuick(opcode), y);
    WriteAddressRegisterLong(ry, result);
    InternalCycle();
    InternalCycle();
}

// SUBQ.{B|W|L} #imm, <ea>

template<auto Source, typename T>
auto M68000::ExecuteSubqEffectiveAddress(uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Sub<T>(OpcodeQuick(opcode), y);
    WriteMemory<T>(address, result);
}

// SCC Dy

auto M68000::ExecuteSccDataRegister(uint32_t opcode) -> void {
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = ReadDataRegisterLong(ry);
    const auto result = Scc(OpcodeConditionCode(opcode), y);
    WriteDataRegister<Byte>(ry, result);
    if (result) {
        InternalCycle();
    }
}

// SCC <ea>

template<auto Source>
auto M68000::ExecuteSccEffectiveAddress(uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Scc(OpcodeConditionCode(opcode), y);
    WriteMemory<Byte>(address, result);
}

// DBCC Dy, *+offset

auto M68000::ExecuteDbcc(uint32_t opcode) -> void {
    if (TestCondition(OpcodeConditionCode(opcode))) {
        // Branch not taken: condition true
        ExecuteDbccConditionTrue();
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = ReadDataRegisterLong(ry);
    WriteDataRegisterWord(ry, y - 1u);
    if (y & 0xFFFFu) {
        // Branch taken: counter not expired
        ExecuteDbccCounterNotExpired();
        return;
    }
    // Branch not taken: counter expired
    ExecuteDbccCounterExpired();
}

auto M68000::ExecuteDbccConditionTrue() -> void {
    // Branch not taken: condition true
    InternalCycle();
    InternalCycle();
    if (!ExecutePrefetchCycle()) [[unlikely]] {
        return;
    }
    ExecuteFinalPrefetchCycle();
}

auto M68000::ExecuteDbccCounterNotExpired() -> void {
    // Branch taken: counter not expired
    InternalCycle();
    const auto baseAddress = ReadPC();
    const auto displacementWord = ReadIRC();
    const auto displacement = SignExtend16(displacementWord);
    WritePC(baseAddress + displacement - 2u);
    if (!ExecutePrefetchCycle()) [[unlikely]] {
        return;
    }
    ExecuteFinalPrefetchCycle();
}

auto M68000::ExecuteDbccCounterExpired() -> void {
    // Branch not taken: counter expired
    // TODO. There are two ways I can imagine the extra prefetch works.
    // 1. The MC68000 reads from the same address twice (implemented here)
    // 2. The MC68000 reads from the branch target and then has to fix up the program counter
    // and prefetch queue
    InternalCycle();
    if (!ExecutePrefetchCycle()) [[unlikely]] {
        return;
    }
    WritePC(ReadPC() - 2u);
    if (!ExecutePrefetchCycle()) [[unlikely]] {
        return;
    }
    ExecuteFinalPrefetchCycle();
}
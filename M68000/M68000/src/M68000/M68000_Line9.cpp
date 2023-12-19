#include "M68000/M68000.h"
#include "M68000/M68000_Opcode.h"
#include "M68000/M68000_EffectiveAddress.h"
#include "M68000/M68000_Operations.h"

using namespace rbrown::m68000;

auto M68000::ExecuteLine9(uint32_t opcode) -> void {
    switch (OpcodeModeX(opcode)) {
        case 0u: return ExecuteSubDataRegister<Byte>(opcode);
        case 1u: return ExecuteSubDataRegister<Word>(opcode);
        case 2u: return ExecuteSubDataRegister<Long>(opcode);
        case 3u: return ExecuteSubAddressRegister<Word>(opcode);
        case 4u: return ExecuteSubEffectiveAddress<Byte>(opcode);
        case 5u: return ExecuteSubEffectiveAddress<Word>(opcode);
        case 6u: return ExecuteSubEffectiveAddress<Long>(opcode);
        case 7u: return ExecuteSubAddressRegister<Long>(opcode);
        [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteSubDataRegister(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteSubDataRegister_RegisterImmediate<&M68000::ReadFromDataRegister<T>, T>(opcode);
        case 1u: if constexpr(std::is_same_v<T, Byte>) {
            return ExecuteIllegal();
        } else {
            return ExecuteSubDataRegister_RegisterImmediate<&M68000::ReadFromAddressRegister<T>, T>(opcode);
        }
        case 2u: return ExecuteSubDataRegister<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteSubDataRegister<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteSubDataRegister<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteSubDataRegister<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteSubDataRegister<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteSubDataRegister<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteSubDataRegister<&M68000::ReadFromLong<T>, T>(opcode);
                case 2u: return ExecuteSubDataRegister<&M68000::ReadFromPCDisplacement<T>, T>(opcode);
                case 3u: return ExecuteSubDataRegister<&M68000::ReadFromPCIndex<T>, T>(opcode);
                case 4u: return ExecuteSubDataRegister_RegisterImmediate<&M68000::ReadFromImmediate<T>, T>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteSubAddressRegister(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteSubAddressRegister_RegisterImmediate<&M68000::ReadFromDataRegister<T>, T>(opcode);
        case 1u: return ExecuteSubAddressRegister_RegisterImmediate<&M68000::ReadFromAddressRegister<T>, T>(opcode);
        case 2u: return ExecuteSubAddressRegister<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteSubAddressRegister<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteSubAddressRegister<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteSubAddressRegister<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteSubAddressRegister<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteSubAddressRegister<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteSubAddressRegister<&M68000::ReadFromLong<T>, T>(opcode);
                case 2u: return ExecuteSubAddressRegister<&M68000::ReadFromPCDisplacement<T>, T>(opcode);
                case 3u: return ExecuteSubAddressRegister<&M68000::ReadFromPCIndex<T>, T>(opcode);
                case 4u: return ExecuteSubAddressRegister_RegisterImmediate<&M68000::ReadFromImmediate<T>, T>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteSubEffectiveAddress(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteSubxDataRegister<T>(opcode);
        case 1u: return ExecuteSubxAddressDecrement<T>(opcode);
        case 2u: return ExecuteSubEffectiveAddress<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteSubEffectiveAddress<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteSubEffectiveAddress<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteSubEffectiveAddress<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteSubEffectiveAddress<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteSubEffectiveAddress<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteSubEffectiveAddress<&M68000::ReadFromLong<T>, T>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

// SUB.{B|W|L} <ea>, Dx

template<auto Source, typename T>
auto M68000::ExecuteSubDataRegister_RegisterImmediate(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadDataRegisterLong(rx);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Sub<T>(y, x);
    WriteDataRegister<T>(rx, result);
    if constexpr(std::is_same_v<T, Long>) {
        InternalCycle();
        InternalCycle();
    }
}

// SUB.{B|W|L} <ea>, Dx

template<auto Source, typename T>
auto M68000::ExecuteSubDataRegister(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadDataRegisterLong(rx);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Sub<T>(y, x);
    WriteDataRegister<T>(rx, result);
    if constexpr(std::is_same_v<T, Long>) {
        InternalCycle();
    }
}

// SUBA.{W|L} <ea>, Ax

template<auto Source, typename T>
auto M68000::ExecuteSubAddressRegister_RegisterImmediate(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadAddressRegisterLong(rx);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Suba<T>(y, x);
    WriteAddressRegisterLong(rx, result);
    InternalCycle();
    InternalCycle();
}

template<auto Source, typename T>
auto M68000::ExecuteSubAddressRegister(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadAddressRegisterLong(rx);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Suba<T>(y, x);
    WriteAddressRegisterLong(rx, result);
    if constexpr(std::is_same_v<T, Word>) {
        InternalCycle();
    }
    InternalCycle();
}

// SUB.{B|W|L} Dx, <ea>

template<auto Source, typename T>
auto M68000::ExecuteSubEffectiveAddress(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadDataRegisterLong(rx);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Sub<T>(x, y);
    WriteMemory<T>(address, result);
}

// SUBX.{B|W|L} Dy, Dx

template<typename T>
auto M68000::ExecuteSubxDataRegister(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadDataRegisterLong(rx);
    const auto y = ReadDataRegisterLong(ry);
    const auto result = Subx<T>(y, x);
    WriteDataRegister<T>(rx, result);
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    if constexpr(std::is_same_v<T, Long>) {
        InternalCycle();
        InternalCycle();
    }
}

// SUBX.{B|W|L} -(Ay), -(Ax)

template<typename T>
auto M68000::ExecuteSubxAddressDecrement(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y, x;
    if (!ReadFromAddressDecrement<T>(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ReadFromAddressDecrementWithoutInternalCycle<T>(rx, address, x)) [[unlikely]] {
        return;
    }
    const auto result = Subx<T>(y, x);
    if constexpr(std::is_same_v<T, Long>) {
        if (!WriteMemory<Word>(address + 2u, result)) [[unlikely]] {
            return;
        }
        if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
            return;
        }
        WriteMemory<Word>(address, result >> 16u);
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    WriteMemory<T>(address, result);
}

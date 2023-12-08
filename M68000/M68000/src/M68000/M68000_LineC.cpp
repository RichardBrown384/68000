#include "M68000/M68000.h"
#include "M68000/M68000_Opcode.h"
#include "M68000/M68000_EffectiveAddress.h"
#include "M68000/M68000_Operations.h"

using namespace rbrown::m68000;

auto M68000::ExecuteLineC(uint32_t opcode) -> void {
    switch (OpcodeModeX(opcode)) {
        case 0u: return ExecuteAndDataRegister<Byte>(opcode);
        case 1u: return ExecuteAndDataRegister<Word>(opcode);
        case 2u: return ExecuteAndDataRegister<Long>(opcode);
        case 3u: return ExecuteMuluDataRegister(opcode);
        case 4u: return ExecuteAndEffectiveAddress<Byte>(opcode);
        case 5u: return ExecuteAndEffectiveAddress<Word>(opcode);
        case 6u: return ExecuteAndEffectiveAddress<Long>(opcode);
        case 7u: return ExecuteMulsDataRegister(opcode);
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteAndDataRegister(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteAndDataRegister_RegisterImmediate<&M68000::ReadFromDataRegister<T>, T>(opcode);
        case 2u: return ExecuteAndDataRegister<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteAndDataRegister<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteAndDataRegister<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteAndDataRegister<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteAndDataRegister<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteAndDataRegister<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteAndDataRegister<&M68000::ReadFromLong<T>, T>(opcode);
                case 2u: return ExecuteAndDataRegister<&M68000::ReadFromPCDisplacement<T>, T>(opcode);
                case 3u: return ExecuteAndDataRegister<&M68000::ReadFromPCIndex<T>, T>(opcode);
                case 4u: return ExecuteAndDataRegister_RegisterImmediate<&M68000::ReadFromImmediate<T>, T>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteMuluDataRegister(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteMuluDataRegister<&M68000::ReadFromDataRegister<Word>>(opcode);
        case 2u: return ExecuteMuluDataRegister<&M68000::ReadFromAddressIndirect<Word>>(opcode);
        case 3u: return ExecuteMuluDataRegister<&M68000::ReadFromAddressIncrement<Word>>(opcode);
        case 4u: return ExecuteMuluDataRegister<&M68000::ReadFromAddressDecrement<Word>>(opcode);
        case 5u: return ExecuteMuluDataRegister<&M68000::ReadFromAddressDisplacement<Word>>(opcode);
        case 6u: return ExecuteMuluDataRegister<&M68000::ReadFromAddressIndex<Word>>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteMuluDataRegister<&M68000::ReadFromShort<Word>>(opcode);
                case 1u: return ExecuteMuluDataRegister<&M68000::ReadFromLong<Word>>(opcode);
                case 2u: return ExecuteMuluDataRegister<&M68000::ReadFromPCDisplacement<Word>>(opcode);
                case 3u: return ExecuteMuluDataRegister<&M68000::ReadFromPCIndex<Word>>(opcode);
                case 4u: return ExecuteMuluDataRegister<&M68000::ReadFromImmediate<Word>>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteAndEffectiveAddress(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u:
            if constexpr(std::is_same_v<T, Byte>) {
                return ExecuteAbcdDataRegister(opcode);
            } else if constexpr(std::is_same_v<T, Word>) {
                return ExecuteExgDataRegisterDataRegister(opcode);
            } else {
                return ExecuteIllegal();
            }
        case 1u:
            if constexpr(std::is_same_v<T, Byte>) {
                return ExecuteAbcdAddressDecrement(opcode);
            } else if constexpr(std::is_same_v<T, Word>) {
                return ExecuteExgAddressRegisterAddressRegister(opcode);
            } else if constexpr(std::is_same_v<T, Long>) {
                return ExecuteExgDataRegisterAddressRegister(opcode);
            } else {
                return ExecuteIllegal();
            }
        case 2u: return ExecuteAndEffectiveAddress<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteAndEffectiveAddress<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteAndEffectiveAddress<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteAndEffectiveAddress<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteAndEffectiveAddress<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteAndEffectiveAddress<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteAndEffectiveAddress<&M68000::ReadFromLong<T>, T>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteMulsDataRegister(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteMulsDataRegister<&M68000::ReadFromDataRegister<Word>>(opcode);
        case 2u: return ExecuteMulsDataRegister<&M68000::ReadFromAddressIndirect<Word>>(opcode);
        case 3u: return ExecuteMulsDataRegister<&M68000::ReadFromAddressIncrement<Word>>(opcode);
        case 4u: return ExecuteMulsDataRegister<&M68000::ReadFromAddressDecrement<Word>>(opcode);
        case 5u: return ExecuteMulsDataRegister<&M68000::ReadFromAddressDisplacement<Word>>(opcode);
        case 6u: return ExecuteMulsDataRegister<&M68000::ReadFromAddressIndex<Word>>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteMulsDataRegister<&M68000::ReadFromShort<Word>>(opcode);
                case 1u: return ExecuteMulsDataRegister<&M68000::ReadFromLong<Word>>(opcode);
                case 2u: return ExecuteMulsDataRegister<&M68000::ReadFromPCDisplacement<Word>>(opcode);
                case 3u: return ExecuteMulsDataRegister<&M68000::ReadFromPCIndex<Word>>(opcode);
                case 4u: return ExecuteMulsDataRegister<&M68000::ReadFromImmediate<Word>>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

// AND.{B|W|L} <ea>, Dx

template<auto Source, typename T>
auto M68000::ExecuteAndDataRegister_RegisterImmediate(uint32_t opcode) -> void {
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
    const auto result = And<T>(y, x);
    WriteDataRegister<T>(rx, result);
    if constexpr(std::is_same_v<T, Long>) {
        InternalCycle();
        InternalCycle();
    }
}

// AND.{B|W|L} <ea>, Dx

template<auto Source, typename T>
auto M68000::ExecuteAndDataRegister(uint32_t opcode) -> void {
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
    const auto result = And<T>(y, x);
    WriteDataRegister<T>(rx, result);
    if constexpr(std::is_same_v<T, Long>) {
        InternalCycle();
    }
}

// AND.{B|W|L} Dx, <ea>

template<auto Source, typename T>
auto M68000::ExecuteAndEffectiveAddress(uint32_t opcode) -> void {
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
    const auto result = And<T>(x, y);
    WriteMemory<T>(address, result);
}

// ABCD.B Dy, Dx

auto M68000::ExecuteAbcdDataRegister(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadDataRegisterLong(rx);
    const auto y = ReadDataRegisterLong(ry);
    const auto result = Abcd<Byte>(y, x);
    WriteDataRegister<Byte>(rx, result);
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    InternalCycle();
}

// ABCD.B -(Ay), -(Ax)

auto M68000::ExecuteAbcdAddressDecrement(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y, x;
    if (!ReadFromAddressDecrement<Byte>(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ReadFromAddressDecrementWithoutInternalCycle<Byte>(rx, address, x)) [[unlikely]] {
        return;
    }
    const auto result = Abcd<Byte>(y, x);
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    WriteMemory<Byte>(address, result);
}

// EXG Dx, Dy

auto M68000::ExecuteExgDataRegisterDataRegister(uint32_t opcode) -> void {
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    InternalCycle();
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadDataRegisterLong(rx);
    const auto y = ReadDataRegisterLong(ry);
    WriteDataRegisterLong(rx, y);
    WriteDataRegisterLong(ry, x);
}


// EXG Ax, Ay

auto M68000::ExecuteExgAddressRegisterAddressRegister(uint32_t opcode) -> void {
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    InternalCycle();
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadAddressRegisterLong(rx);
    const auto y = ReadAddressRegisterLong(ry);
    WriteAddressRegisterLong(rx, y);
    WriteAddressRegisterLong(ry, x);
}

// EXG Dx, Ay

auto M68000::ExecuteExgDataRegisterAddressRegister(uint32_t opcode) -> void {
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    InternalCycle();
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadDataRegisterLong(rx);
    const auto y = ReadAddressRegisterLong(ry);
    WriteDataRegisterLong(rx, y);
    WriteAddressRegisterLong(ry, x);
}

// MULU.W <ea>, Dx

template<auto Source>
auto M68000::ExecuteMuluDataRegister(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadDataRegisterLong(rx);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]]{
        return;
    }
    const auto result = Mulu<Long>(y, x);
    WriteDataRegister<Long>(rx, result);
}

// MULS.W <ea>, Dx

template<auto Source>
auto M68000::ExecuteMulsDataRegister(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadDataRegisterLong(rx);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]]{
        return;
    }
    const auto result = Muls<Long>(y, x);
    WriteDataRegister<Long>(rx, result);
}



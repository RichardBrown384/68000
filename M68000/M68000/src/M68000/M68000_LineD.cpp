#include "M68000/M68000.h"
#include "M68000/M68000_Opcode.h"
#include "M68000/M68000_EffectiveAddress.h"
#include "M68000/M68000_Operations.h"

using namespace rbrown::m68000;

auto M68000::ExecuteLineD(uint32_t opcode) -> void {
    switch (OpcodeModeX(opcode)) {
        case 0u: return ExecuteAddDataRegister<Byte>(opcode);
        case 1u: return ExecuteAddDataRegister<Word>(opcode);
        case 2u: return ExecuteAddDataRegister<Long>(opcode);
        case 3u: return ExecuteAddAddressRegister<Word>(opcode);
        case 4u: return ExecuteAddEffectiveAddress<Byte>(opcode);
        case 5u: return ExecuteAddEffectiveAddress<Word>(opcode);
        case 6u: return ExecuteAddEffectiveAddress<Long>(opcode);
        case 7u: return ExecuteAddAddressRegister<Long>(opcode);
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteAddDataRegister(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteAddDataRegister_RegisterImmediate<&M68000::ReadFromDataRegister<T>, T>(opcode);
        case 1u: if constexpr(std::is_same_v<T, Byte>) {
                return ExecuteIllegal();
            } else {
                return ExecuteAddDataRegister_RegisterImmediate<&M68000::ReadFromAddressRegister<T>, T>(opcode);
            }
        case 2u: return ExecuteAddDataRegister<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteAddDataRegister<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteAddDataRegister<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteAddDataRegister<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteAddDataRegister<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteAddDataRegister<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteAddDataRegister<&M68000::ReadFromLong<T>, T>(opcode);
                case 2u: return ExecuteAddDataRegister<&M68000::ReadFromPCDisplacement<T>, T>(opcode);
                case 3u: return ExecuteAddDataRegister<&M68000::ReadFromPCIndex<T>, T>(opcode);
                case 4u: return ExecuteAddDataRegister_RegisterImmediate<&M68000::ReadFromImmediate<T>, T>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteAddAddressRegister(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteAddAddressRegister_RegisterImmediate<&M68000::ReadFromDataRegister<T>, T > (opcode);
        case 1u: return ExecuteAddAddressRegister_RegisterImmediate<&M68000::ReadFromAddressRegister<T>, T > (opcode);
        case 2u: return ExecuteAddAddressRegister<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteAddAddressRegister<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteAddAddressRegister<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteAddAddressRegister<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteAddAddressRegister<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteAddAddressRegister<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteAddAddressRegister<&M68000::ReadFromLong<T>, T>(opcode);
                case 2u: return ExecuteAddAddressRegister<&M68000::ReadFromPCDisplacement<T>, T>(opcode);
                case 3u: return ExecuteAddAddressRegister<&M68000::ReadFromPCIndex<T>, T>(opcode);
                case 4u: return ExecuteAddAddressRegister_RegisterImmediate<&M68000::ReadFromImmediate<T>, T > (opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteAddEffectiveAddress(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteAddxDataRegister<T>(opcode);
        case 1u: return ExecuteAddxAddressDecrement<T>(opcode);
        case 2u: return ExecuteAddEffectiveAddress<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteAddEffectiveAddress<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteAddEffectiveAddress<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteAddEffectiveAddress<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteAddEffectiveAddress<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteAddEffectiveAddress<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteAddEffectiveAddress<&M68000::ReadFromLong<T>, T>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

// ADD.{B|W|L} <ea>, Dx

template<auto Source, typename T>
auto M68000::ExecuteAddDataRegister_RegisterImmediate(uint32_t opcode) -> void {
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
    const auto result = Add<T>(y, x);
    WriteDataRegister<T>(rx, result);
    if constexpr(std::is_same_v<T, Long>) {
        InternalCycle();
        InternalCycle();
    }
}

// ADD.{B|W|L} <ea>, Dx

template<auto Source, typename T>
auto M68000::ExecuteAddDataRegister(uint32_t opcode) -> void {
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
    const auto result = Add<T>(y, x);
    WriteDataRegister<T>(rx, result);
    if constexpr(std::is_same_v<T, Long>) {
        InternalCycle();
    }
}

// ADDA.{W|L} <ea>, Ax

template<auto Source, typename T>
auto M68000::ExecuteAddAddressRegister_RegisterImmediate(uint32_t opcode) -> void {
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
    const auto result = Adda<T>(y, x);
    WriteAddressRegisterLong(rx, result);
    InternalCycle();
    InternalCycle();
}

template<auto Source, typename T>
auto M68000::ExecuteAddAddressRegister(uint32_t opcode) -> void {
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
    const auto result = Adda<T>(y, x);
    WriteAddressRegisterLong(rx, result);
    if constexpr(std::is_same_v<T, Word>) {
        InternalCycle();
    }
    InternalCycle();
}

// ADD.{B|W|L} Dx, <ea>

template<auto Source, typename T>
auto M68000::ExecuteAddEffectiveAddress(uint32_t opcode) -> void {
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
    const auto result = Add<T>(x, y);
    WriteMemory<T>(address, result);
}

// ADDX.{B|W|L} Dy, Dx

template<typename T>
auto M68000::ExecuteAddxDataRegister(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadDataRegisterLong(rx);
    const auto y = ReadDataRegisterLong(ry);
    const auto result = Addx<T>(y, x);
    WriteDataRegister<T>(rx, result);
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    if constexpr(std::is_same_v<T, Long>) {
        InternalCycle();
        InternalCycle();
    }
}

// ADDX.{B|W|L} -(Ay), -(Ax)

template<typename T>
auto M68000::ExecuteAddxAddressDecrement(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y, x;
    if (!ReadFromAddressDecrement<T>(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ReadFromAddressDecrementWithoutInternalCycle<T>(rx, address, x)) [[unlikely]] {
        return;
    }
    const auto result = Addx<T>(y, x);
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

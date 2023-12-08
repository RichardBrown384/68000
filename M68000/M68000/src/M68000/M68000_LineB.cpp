#include "M68000/M68000.h"
#include "M68000/M68000_Opcode.h"
#include "M68000/M68000_EffectiveAddress.h"
#include "M68000/M68000_Operations.h"

using namespace rbrown::m68000;

auto M68000::ExecuteLineB(uint32_t opcode) -> void {
    switch (OpcodeModeX(opcode)) {
        case 0u: return ExecuteCmpDataRegister<Byte>(opcode);
        case 1u: return ExecuteCmpDataRegister<Word>(opcode);
        case 2u: return ExecuteCmpDataRegister<Long>(opcode);
        case 3u: return ExecuteCmpAddressRegister<Word>(opcode);
        case 4u: return ExecuteEorEffectiveAddress<Byte>(opcode);
        case 5u: return ExecuteEorEffectiveAddress<Word>(opcode);
        case 6u: return ExecuteEorEffectiveAddress<Long>(opcode);
        case 7u: return ExecuteCmpAddressRegister<Long>(opcode);
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteCmpDataRegister(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteCmpDataRegister<&M68000::ReadFromDataRegister<T>, T>(opcode);
        case 1u: if constexpr(std::is_same_v<T, Byte>) {
                return ExecuteIllegal();
            } else {
                return ExecuteCmpDataRegister<&M68000::ReadFromAddressRegister<T>, T>(opcode);
            }
        case 2u: return ExecuteCmpDataRegister<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteCmpDataRegister<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteCmpDataRegister<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteCmpDataRegister<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteCmpDataRegister<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteCmpDataRegister<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteCmpDataRegister<&M68000::ReadFromLong<T>, T>(opcode);
                case 2u: return ExecuteCmpDataRegister<&M68000::ReadFromPCDisplacement<T>, T>(opcode);
                case 3u: return ExecuteCmpDataRegister<&M68000::ReadFromPCIndex<T>, T>(opcode);
                case 4u: return ExecuteCmpDataRegister<&M68000::ReadFromImmediate<T>, T>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteCmpAddressRegister(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteCmpAddressRegister<&M68000::ReadFromDataRegister<T>, T > (opcode);
        case 1u: return ExecuteCmpAddressRegister<&M68000::ReadFromAddressRegister<T>, T > (opcode);
        case 2u: return ExecuteCmpAddressRegister<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteCmpAddressRegister<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteCmpAddressRegister<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteCmpAddressRegister<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteCmpAddressRegister<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteCmpAddressRegister<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteCmpAddressRegister<&M68000::ReadFromLong<T>, T>(opcode);
                case 2u: return ExecuteCmpAddressRegister<&M68000::ReadFromPCDisplacement<T>, T>(opcode);
                case 3u: return ExecuteCmpAddressRegister<&M68000::ReadFromPCIndex<T>, T>(opcode);
                case 4u: return ExecuteCmpAddressRegister<&M68000::ReadFromImmediate<T>, T > (opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteEorEffectiveAddress(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteEorDataRegister<T>(opcode);
        case 1u: return ExecuteCmpAddressIncrement<T>(opcode);
        case 2u: return ExecuteEorEffectiveAddress<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteEorEffectiveAddress<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteEorEffectiveAddress<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteEorEffectiveAddress<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteEorEffectiveAddress<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteEorEffectiveAddress<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteEorEffectiveAddress<&M68000::ReadFromLong<T>, T>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

// CMP.{B|W|L} <ea>, Dx

template<auto Source, typename T>
auto M68000::ExecuteCmpDataRegister(uint32_t opcode) -> void {
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
    Cmp<T>(y, x);
    if constexpr(std::is_same_v<T, Long>) {
        InternalCycle();
    }
}

// CMPA.{W|L} <ea>, Ax

template<auto Source, typename T>
auto M68000::ExecuteCmpAddressRegister(uint32_t opcode) -> void {
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
    Cmpa<T>(y, x);
    InternalCycle();
}

// CMPM.{B|W|L} (Ay)+, (Ax)+

template<typename T>
auto M68000::ExecuteCmpAddressIncrement(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y, x;
    if (!ReadFromAddressIncrement<T>(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ReadFromAddressIncrement<T>(rx, address, x)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    Cmp<T>(y, x);
}


// EOR.{B|W|L} Dx, Dy

template<typename T>
auto M68000::ExecuteEorDataRegister(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadDataRegisterLong(rx);
    const auto y = ReadDataRegisterLong(ry);
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Eor<T>(x, y);
    WriteDataRegister<T>(ry, result);
    if constexpr(std::is_same_v<T, Long>) {
        InternalCycle();
        InternalCycle();
    }
}

// EOR.{B|W|L} Dx, <ea>

template<auto Source, typename T>
auto M68000::ExecuteEorEffectiveAddress(uint32_t opcode) -> void {
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
    const auto result = Eor<T>(x, y);
    WriteMemory<T>(address, result);
}

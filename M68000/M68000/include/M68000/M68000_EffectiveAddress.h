#pragma once

#include "M68000/M68000.h"
#include "M68000/M68000_Sizes.h"

namespace rbrown::m68000 {

// Register access functions

template<typename T>
auto M68000::WriteDataRegister(uint32_t rx, uint32_t result) -> void {
    if constexpr(std::is_same_v<T, Byte>) {
        WriteDataRegisterByte(rx, result);
    } else if constexpr(std::is_same_v<T, Word>) {
        WriteDataRegisterWord(rx, result);
    } else if constexpr(std::is_same_v<T, Long>) {
        WriteDataRegisterLong(rx, result);
    }
}

// Memory access functions

template<typename T>
auto M68000::ReadMemory(uint32_t address, uint32_t& value) -> bool {
    if constexpr(std::is_same_v<T, Byte>) {
        return ReadByte(address, value);
    } else if constexpr(std::is_same_v<T, Word>) {
        return ReadWord(address, value);
    } else if constexpr(std::is_same_v<T, Long>) {
        return ReadLong(address, value);
    } else {
        return false;
    }
}

template<typename T>
auto M68000::WriteMemory(uint32_t address, uint32_t value) -> bool {
    if constexpr(std::is_same_v<T, Byte>) {
        return WriteByte(address, value);
    } else if constexpr(std::is_same_v<T, Word>) {
        return WriteWord(address, value);
    } else if constexpr(std::is_same_v<T, Long>) {
        return WriteLong(address, value);
    } else {
        return false;
    }
}

// Effective address calculation

template<typename T>
auto M68000::EffectiveAddressAddressIncrement(uint32_t ry, uint32_t& address) -> bool {
    const auto ay = ReadAddressRegisterLong(ry);
    const auto size = T::AddressIncrement(ry);
    address = ay;
    WriteAddressRegisterLong(ry, address + size);
    return true;
}

template<typename T>
auto M68000::EffectiveAddressAddressDecrement(uint32_t ry, uint32_t& address) -> bool {
    InternalCycle();
    const auto ay = ReadAddressRegisterLong(ry);
    const auto size = T::AddressIncrement(ry);
    address = ay - size;
    WriteAddressRegisterLong(ry, address);
    return true;
}

template<typename T>
auto M68000::EffectiveAddressAddressDecrementWithoutInternalCycle(uint32_t ry, uint32_t& address) -> bool {
    const auto ay = ReadAddressRegisterLong(ry);
    const auto size = T::AddressIncrement(ry);
    address = ay - size;
    WriteAddressRegisterLong(ry, address);
    return true;
}

// Read operations

template<typename>
auto M68000::ReadFromDataRegister(uint32_t ry, [[maybe_unused]] uint32_t& address, uint32_t& value) -> bool {
    value = ReadDataRegisterLong(ry);
    return true;
}

template<typename>
auto M68000::ReadFromAddressRegister(uint32_t ry, [[maybe_unused]] uint32_t& address, uint32_t& value) -> bool {
    value = ReadAddressRegisterLong(ry);
    return true;
}

template<typename T>
auto M68000::ReadFromAddressIndirect(uint32_t ry, uint32_t& address, uint32_t& value) -> bool {
    if (EffectiveAddressAddressIndirect(ry, address)) [[likely]] {
        return ReadMemory<T>(address, value);
    }
    return false;
}

template<typename T>
auto M68000::ReadFromAddressIncrement(uint32_t ry, uint32_t& address, uint32_t& value) -> bool {
    if (EffectiveAddressAddressIncrement<T>(ry, address)) [[likely]] {
        return ReadMemory<T>(address, value);
    }
    return false;
}

template<typename T>
auto M68000::ReadFromAddressDecrement(uint32_t ry, uint32_t& address, uint32_t& value) -> bool {
    if (EffectiveAddressAddressDecrement<T>(ry, address)) [[likely]] {
        return ReadMemory<T>(address, value);
    }
    return false;
}

template<typename T>
auto M68000::ReadFromAddressDecrementWithoutInternalCycle(uint32_t ry, uint32_t& address, uint32_t& value) -> bool {
    // Note: as above but used for multiprecision instructions
    if (EffectiveAddressAddressDecrementWithoutInternalCycle<T>(ry, address)) [[likely]] {
        return ReadMemory<T>(address, value);
    }
    return false;
}

template<typename T>
auto M68000::ReadFromAddressDisplacement(uint32_t ry, uint32_t& address, uint32_t& value) -> bool {
    if (EffectiveAddressAddressDisplacement(ry, address)) [[likely]] {
        return ReadMemory<T>(address, value);
    }
    return false;
}

template<typename T>
auto M68000::ReadFromAddressIndex(uint32_t ry, uint32_t& address, uint32_t& value) -> bool {
    if (EffectiveAddressAddressIndex(ry, address)) [[likely]] {
        return ReadMemory<T>(address, value);
    }
    return false;
}

template<typename T>
auto M68000::ReadFromShort(uint32_t ry, uint32_t& address, uint32_t& value) -> bool {
    if (EffectiveAddressShort(ry, address)) [[likely]] {
        return ReadMemory<T>(address, value);
    }
    return false;
}

template<typename T>
auto M68000::ReadFromLong(uint32_t ry, uint32_t& address, uint32_t& value) -> bool {
    if (EffectiveAddressLong(ry, address)) [[likely]] {
        return ReadMemory<T>(address, value);
    }
    return false;
}

template<typename T>
auto M68000::ReadFromPCDisplacement(uint32_t ry, uint32_t& address, uint32_t& value) -> bool {
    if (EffectiveAddressPCDisplacement(ry, address)) {
        return ReadMemory<T>(address, value);
    }
    return false;
}

template<typename T>
auto M68000::ReadFromPCIndex(uint32_t ry, uint32_t& address, uint32_t& value) -> bool {
    if (EffectiveAddressPCIndex(ry, address)) {
        return ReadMemory<T>(address, value);
    }
    return false;
}

template<typename T>
auto M68000::ReadFromImmediate([[maybe_unused]] uint32_t ry, uint32_t& address, uint32_t& value) -> bool {
    const auto hi = ReadIRC();
    if (!ExecutePrefetchCycle()) [[unlikely]] {
        return false;
    }
    if constexpr(std::is_same_v<T, Byte> || std::is_same_v<T, Word>) {
        value = hi;
        return true;
    }
    const auto lo = ReadIRC();
    if (!ExecutePrefetchCycle()) [[unlikely]] {
        return false;
    }
    value = (hi << 16u) + lo;
    return true;
}


}
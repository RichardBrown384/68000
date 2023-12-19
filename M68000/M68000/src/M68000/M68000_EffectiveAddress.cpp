#include "M68000/M68000.h"
#include "M68000/M68000_Opcode.h"
#include "M68000/M68000_Int.h"

using namespace rbrown::m68000;

auto M68000::ComputeIndexFromExtensionWord(uint32_t extension) const -> uint32_t {
    const auto re = ExtensionWordRegister(extension);
    const auto r = ExtensionWordAddress(extension) ?
                   ReadAddressRegisterLong(re) :
                   ReadDataRegisterLong(re);
    const auto index = ExtensionWordLong(extension) ? r : SignExtend16(r);
    const auto displacement = ExtensionWordDisplacement(extension);
    return index + SignExtend8(displacement);
}

auto M68000::EffectiveAddressAddressIndirect(uint32_t ry, uint32_t& address) const -> bool {
    address = ReadAddressRegisterLong(ry);
    return true;
}

auto M68000::EffectiveAddressAddressDisplacement(uint32_t ry, uint32_t& address) -> bool {
    const auto displacementWord = ReadIRC();
    if (!ExecutePrefetchCycle()) [[unlikely]] {
        return false;
    }
    const auto baseAddress = ReadAddressRegisterLong(ry);
    const auto displacement = SignExtend16(displacementWord);
    address = baseAddress + displacement;
    return true;
}

auto M68000::EffectiveAddressAddressIndex(uint32_t ry, uint32_t& address) -> bool {
    InternalCycle();
    const auto extensionWord = ReadIRC();
    if (!ExecutePrefetchCycle()) [[unlikely]] {
        return false;
    }
    const auto baseAddress = ReadAddressRegisterLong(ry);
    const auto index = ComputeIndexFromExtensionWord(extensionWord);
    address = baseAddress + index;
    return true;
}

auto M68000::EffectiveAddressAddressIndexControl(uint32_t ry, uint32_t& address) -> bool {
    InternalCycle();
    const auto extensionWord = ReadIRC();
    if (!ExecutePrefetchCycle()) [[unlikely]] {
        return false;
    }
    InternalCycle();
    const auto baseAddress = ReadAddressRegisterLong(ry);
    const auto index = ComputeIndexFromExtensionWord(extensionWord);
    address = baseAddress + index;
    return true;
}

auto M68000::EffectiveAddressShort([[maybe_unused]] uint32_t ry, uint32_t& address) -> bool {
    const auto shortWord = ReadIRC();
    if (!ExecutePrefetchCycle()) [[unlikely]] {
        return false;
    }
    address = SignExtend16(shortWord);
    return true;
}

auto M68000::EffectiveAddressLong([[maybe_unused]] uint32_t ry, uint32_t& address) -> bool {
    const auto hi = ReadIRC();
    if (!ExecutePrefetchCycle()) [[unlikely]] {
        return false;
    }
    const auto lo = ReadIRC();
    if (!ExecutePrefetchCycle()) [[unlikely]] {
        return false;
    }
    address = (hi << 16u) + lo;
    return true;
}

auto M68000::EffectiveAddressPCDisplacement([[maybe_unused]] uint32_t ry, uint32_t& address) -> bool {
    const auto displacementWord = ReadIRC();
    if (!ExecutePrefetchCycle()) [[unlikely]] {
        return false;
    }
    const auto baseAddress = ReadPC();
    const auto displacement = SignExtend16(displacementWord);
    address = baseAddress + displacement;
    return true;
}

auto M68000::EffectiveAddressPCIndex([[maybe_unused]] uint32_t ry, uint32_t& address) -> bool {
    InternalCycle();
    const auto extensionWord = ReadIRC();
    if (!ExecutePrefetchCycle()) [[unlikely]] {
        return false;
    }
    const auto baseAddress = ReadPC();
    const auto index = ComputeIndexFromExtensionWord(extensionWord);
    address = baseAddress + index;
    return true;
}

auto M68000::EffectiveAddressPCIndexControl([[maybe_unused]] uint32_t ry, uint32_t& address) -> bool {
    InternalCycle();
    const auto extensionWord = ReadIRC();
    if (!ExecutePrefetchCycle()) [[unlikely]] {
        return false;
    }
    InternalCycle();
    const auto baseAddress = ReadPC();
    const auto index = ComputeIndexFromExtensionWord(extensionWord);
    address = baseAddress + index;
    return true;
}

auto M68000::ControlAddressIndirect(uint32_t ry, uint32_t& target) const -> bool {
    target = ReadAddressRegisterLong(ry);
    return true;
}

auto M68000::ControlAddressDisplacement(uint32_t ry, uint32_t& target) -> bool {
    InternalCycle();
    const auto baseAddress = ReadAddressRegisterLong(ry);
    const auto displacementWord = ReadIRC();
    target = baseAddress + SignExtend16(displacementWord);
    return true;
}

auto M68000::ControlAddressIndex(uint32_t ry, uint32_t& target) -> bool {
    InternalCycle();
    InternalCycle();
    InternalCycle();
    const auto baseAddress = ReadAddressRegisterLong(ry);
    const auto indexWord = ReadIRC();
    target = baseAddress + ComputeIndexFromExtensionWord(indexWord);
    return true;
}

auto M68000::ControlShort(uint32_t, uint32_t& target) -> bool {
    InternalCycle();
    const auto shortWord = ReadIRC();
    target = SignExtend16(shortWord);
    return true;
}

auto M68000::ControlLong(uint32_t, uint32_t& target) -> bool {
    const auto hi = ReadIRC();
    if (!ExecutePrefetchCycle()) [[unlikely]] {
        return false;
    }
    const auto lo = ReadIRC();
    target = (hi << 16u) + lo;
    return true;
}

auto M68000::ControlPCDisplacement(uint32_t, uint32_t& target) -> bool {
    InternalCycle();
    const auto baseAddress = ReadPC();
    const auto displacementWord = ReadIRC();
    target = baseAddress + 2u + SignExtend16(displacementWord);
    return true;
}

auto M68000::ControlPCIndex(uint32_t, uint32_t& target) -> bool {
    InternalCycle();
    InternalCycle();
    InternalCycle();
    const auto baseAddress = ReadPC();
    const auto indexWord = ReadIRC();
    target = baseAddress + 2u + ComputeIndexFromExtensionWord(indexWord);
    return true;
}
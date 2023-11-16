#include <vector>

#include "Mocks.h"

namespace {
auto MaskAddress(auto address) {
    return address & 0x00FFFFFFu;
}
}

bool MemoryMock::ReadByte(uint32_t address, uint32_t& result) {
    address = MaskAddress(address);
    result = memory.contains(address) ? memory.at(address) : 0u;
    return true;
}

bool MemoryMock::ReadWord(uint32_t address, uint32_t& result) {
    uint32_t hi, lo;
    if (ReadByte(address, hi) && ReadByte(address + 1u, lo)) {
        result = (hi << 8u) + lo;
        return true;
    }
    return false;
}

bool MemoryMock::WriteByte(uint32_t address, uint32_t value) {
    memory[MaskAddress(address)] = (uint8_t)(value);
    return true;
}

bool MemoryMock::WriteWord(uint32_t address, uint32_t value) {
    return WriteByte(address, value >> 8u) &&
           WriteByte(address + 1u, value);
}

bool MemoryMock::WriteWords(uint32_t address, const std::vector<uint16_t>& words) {
    for (const auto& w : words) {
        if (!WriteWord(address, w)) {
            return false;
        }
        address += 2u;
    }
    return true;
}
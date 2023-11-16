#pragma once

#include "M68000/M68000.h"

#include <unordered_map>

class InterruptsMock : public rbrown::m68000::Interrupts {
public:
    InterruptsMock() : calls(0), initialLevel(0), subsequentLevel(0), vector(24u) {}

    virtual ~InterruptsMock() = default;

    uint32_t GetInterruptLevel() final {
        if (calls) {
            return subsequentLevel;
        }
        calls = 1u;
        return initialLevel;
    }

    uint32_t GetInterruptVector(uint32_t) final { return vector; }

    void SetInitialLevel(uint32_t v) { initialLevel = v; }

    void SetSubsequentLevel(uint32_t v) { subsequentLevel = v; }

    void SetInterruptVector(uint32_t v) { vector = v; }

private:
    uint32_t calls;
    uint32_t initialLevel;
    uint32_t subsequentLevel;
    uint32_t vector;
};

class MemoryMock : public rbrown::m68000::Memory {
public:
    MemoryMock() : memory() {}

    bool ReadByte(uint32_t address, uint32_t& result) final {
        address &= 0xFF'FFFFu;
        result = memory.contains(address) ? memory.at(address) : 0u;
        return true;
    }

    bool ReadWord(uint32_t address, uint32_t& result) final {
        uint32_t hi, lo;
        if (ReadByte(address, hi) && ReadByte(address + 1u, lo)) {
            result = (hi << 8u) + lo;
            return true;
        }
        return false;
    }

    bool WriteByte(uint32_t address, uint32_t value) final {
        address &= 0xFF'FFFFu;
        memory[address] = static_cast<uint8_t>(value);
        return true;
    }

    bool WriteWord(uint32_t address, uint32_t value) final {
        return WriteByte(address, value >> 8u) &&
               WriteByte(address + 1u, value);
    }

private:
    std::unordered_map <uint32_t, uint8_t> memory;
};

class ObserverMock : public rbrown::m68000::Observer {
public:
    ObserverMock() : m_cycles(0) {}

    virtual ~ObserverMock() {}

    inline uint32_t GetCycles() const { return m_cycles; }

    inline void Cycles(uint32_t cycles) final { m_cycles += cycles; }

    inline void Reset() final {}

private:
    uint32_t m_cycles;
};

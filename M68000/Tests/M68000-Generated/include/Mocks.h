#pragma once

#include <unordered_map>

#include "M68000/M68000.h"

class InterruptsMock : public rbrown::m68000::Interrupts {
public:
    InterruptsMock() : calls(0), initialLevel(0), subsequentLevel(0), vector(24u) {}
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

class MemoryMock final: public rbrown::m68000::Memory {
public:
    MemoryMock() : memory() {}

    bool ReadByte(uint32_t, uint32_t&) final;
    bool ReadWord(uint32_t, uint32_t&) final;

    bool WriteByte(uint32_t, uint32_t) final;
    bool WriteWord(uint32_t, uint32_t) final;

    bool WriteWords(uint32_t, const std::vector<uint16_t>&);

private:
    std::unordered_map<uint32_t, uint8_t> memory;
};

class ObserverMock final: public rbrown::m68000::Observer {
public:
    ObserverMock() : m_cycles(0) {}
    [[nodiscard]] uint32_t GetCycles() const { return m_cycles; }
    void Cycles(uint32_t cycles) final { m_cycles += cycles; }
    void Reset() final {}
private:
    uint32_t m_cycles;
};
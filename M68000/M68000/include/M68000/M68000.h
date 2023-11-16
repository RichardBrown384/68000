#pragma once

#include <cstdint>
#include <array>

namespace rbrown::m68000 {

class Interrupts {
public:
    virtual ~Interrupts() = default;
    virtual uint32_t GetInterruptLevel() = 0;
    virtual uint32_t GetInterruptVector(uint32_t) = 0;
};

class Memory {
public:
    virtual ~Memory() = default;

    virtual bool ReadByte(uint32_t, uint32_t&) = 0;
    virtual bool ReadWord(uint32_t, uint32_t&) = 0;

    virtual bool WriteByte(uint32_t, uint32_t) = 0;
    virtual bool WriteWord(uint32_t, uint32_t) = 0;
};

class Observer {
public:
    virtual ~Observer() = default;

    virtual void Cycles(uint32_t) = 0;

    virtual void Reset() = 0;
};

class M68000 {
public:
    M68000(Interrupts&, Memory&, Observer& observer);

    [[nodiscard]] auto ReadDataRegisterLong(uint32_t r) const { return data[r]; }
    [[nodiscard]] auto ReadAddressRegisterLong(uint32_t r) const { return addr[r]; }

    [[nodiscard]] auto ReadSP() const { return ReadAddressRegisterLong(7u); }
    [[nodiscard]] auto ReadPC() const { return pc; }
    [[nodiscard]] auto ReadUSP() const { return usp; }
    [[nodiscard]] auto ReadSSP() const { return ssp; }
    [[nodiscard]] auto ReadIRC() const { return irc; }
    [[nodiscard]] auto ReadIRD() const { return ird; }

    [[nodiscard]] auto ReadSR() const -> uint16_t;
    [[nodiscard]] auto ReadCCR() const -> uint16_t;

    [[nodiscard]] auto ReadFlagT() const { return flagT; }
    [[nodiscard]] auto ReadFlagS() const { return flagS; }

    [[nodiscard]] auto ReadInterruptPriorityMask() const { return interruptPriorityMask; }

    [[nodiscard]] auto ReadFlagX() const { return (flagX & 0x80000000u) != 0u; }
    [[nodiscard]] auto ReadFlagN() const { return (flagN & 0x80000000u) != 0u; }
    [[nodiscard]] auto ReadFlagZ() const { return flagZ == 0u; }
    [[nodiscard]] auto ReadFlagV() const { return (flagV & 0x80000000u) != 0u; }
    [[nodiscard]] auto ReadFlagC() const { return (flagC & 0x80000000u) != 0u; }

    [[nodiscard]] auto ReadStopped() const { return stopped; }
    [[nodiscard]] auto ReadHalted() const { return halted; }

    auto WriteDataRegisterByte(uint32_t r, uint32_t v) { data[r] = (data[r] & ~0xFFu) + (v & 0xFFu); }
    auto WriteDataRegisterWord(uint32_t r, uint32_t v) { data[r] = (data[r] & ~0xFFFFu) + (v & 0xFFFFu); }
    auto WriteDataRegisterLong(uint32_t r, uint32_t v) { data[r] = v; }

    auto WriteAddressRegisterLong(uint32_t r, uint32_t v) { addr[r] = v; };

    auto WriteSP(uint32_t v) { WriteAddressRegisterLong(7u, v); }
    auto WritePC(uint32_t v) { pc = v; }
    auto WriteUSP(uint32_t v) { usp = v; }
    auto WriteSSP(uint32_t v) { ssp = v; }
    auto WriteIRC(uint16_t v) { irc = v; }
    auto WriteIRD(uint16_t v) { ird = v; }

    auto WriteSR(uint16_t v) -> void;
    auto WriteCCR(uint16_t v) -> void;

    auto WriteFlagT(bool v) { flagT = v; }
    auto WriteFlagS(bool v) -> void;

    auto WriteInterruptPriorityMask(uint32_t v) { interruptPriorityMask = v & 7u; }

    auto WriteFlagX(uint32_t v) { flagX = v; };
    auto WriteFlagN(uint32_t v) { flagN = v; };
    auto WriteFlagZ(uint32_t v) { flagZ = v; };
    auto WriteFlagV(uint32_t v) { flagV = v; };
    auto WriteFlagC(uint32_t v) { flagC = v; };

    auto WriteStopped(bool v) { stopped = v; }
    auto WriteHalted(bool v) { stopped = v; halted = v; }

    auto ElapseCycles(uint32_t) -> void;
    auto InternalCycle() -> void;
    auto BusCycle() -> void;
    auto ResetExternalDevices() -> void;

    auto Execute() -> void;
    auto Reset() -> void;

    auto& GetInterrupts() { return interrupts; }
    auto& GetMemory() { return memory; }
    auto& GetObserver() { return observer; }

private:
    Interrupts& interrupts;
    Memory& memory;
    Observer& observer;

    std::array<uint32_t, 8> data;
    std::array<uint32_t, 8> addr;

    uint32_t pc;
    uint32_t usp;
    uint32_t ssp;
    uint16_t irc;
    uint16_t ird;

    uint32_t interruptPriorityMask;

    uint32_t flagX;
    uint32_t flagN;
    uint32_t flagZ;
    uint32_t flagV;
    uint32_t flagC;

    bool flagT;
    bool flagS;

    bool stopped;
    bool halted;
};

}
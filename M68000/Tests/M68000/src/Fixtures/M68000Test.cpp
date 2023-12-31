#include "M68000/Fixtures/M68000Test.h"
#include "M68000/Mocks/M68000Mocks.h"

#include "M68000/M68000.h"
#include "M68000/M68000_Constants.h"
#include "M68000/Assembler.h"

#include <regex>
#include <cstdlib>
#include <utility>

using namespace rbrown::m68000;

namespace {

auto MatchStatusRegister(const char* condition, uint32_t& v) -> bool {
    static const std::regex STATUS_REGISTER(R"(^SR is ([TS]+|0),([0-7]),([XNZVC]+|0)$)");
    std::cmatch match;
    if (std::regex_match(condition, match, STATUS_REGISTER)) {
        const std::string& ts = match.str(1);
        const std::string& mask = match.str(2);
        const std::string& xnzvc = match.str(3);
        uint32_t sr{};
        for (const auto& c: ts) {
            if (c == 'T') sr |= FLAG_T;
            if (c == 'S') sr |= FLAG_S;
        }
        sr |= std::stoul(mask, nullptr, 10) << 8u;
        for (const auto& c: xnzvc) {
            if (c == 'X') sr |= FLAG_X;
            if (c == 'N') sr |= FLAG_N;
            if (c == 'Z') sr |= FLAG_Z;
            if (c == 'V') sr |= FLAG_V;
            if (c == 'C') sr |= FLAG_C;
        }
        v = sr;
        return true;
    }
    return false;
}

auto MatchProgramCounter(const char* condition, uint32_t& v) -> bool {
    static const std::regex PC(R"(^PC is 0x([0-9A-F]+)$)");
    std::cmatch match;
    if (std::regex_match(condition, match, PC)) {
        v = std::stoul(match.str(1), nullptr, 16);
        return true;
    }
    return false;
}

auto MatchCycles(const char* condition, uint32_t& v) -> bool {
    static const std::regex CYCLES(R"(^CYCLES is ([1-9][0-9]*)$)");
    std::cmatch match;
    if (std::regex_match(condition, match, CYCLES)) {
        v = std::stoul(match.str(1), nullptr, 10);
        return true;
    }
    return false;
}

auto MatchDataRegister(const char* condition, uint32_t& r, uint32_t& v) -> bool {
    static const std::regex DATA_REGISTER(R"(^D([0-7]) is 0x([0-9A-F]+)$)");
    std::cmatch match;
    if (std::regex_match(condition, match, DATA_REGISTER)) {
        r = std::stoul(match.str(1), nullptr, 10);
        v = std::stoul(match.str(2), nullptr, 16);
        return true;
    }
    return false;
}

auto MatchAddressRegister(const char* condition, uint32_t& r, uint32_t& v) -> bool {
    static const std::regex ADDRESS_REGISTER(R"(^A([0-7]) is 0x([0-9A-F]+)$)");
    std::cmatch match;
    if (std::regex_match(condition, match, ADDRESS_REGISTER)) {
        r = std::stoul(match.str(1), nullptr, 10);
        v = std::stoul(match.str(2), nullptr, 16);
        return true;
    }
    return false;
}

auto MatchUserStackPointer(const char* condition, uint32_t& v) -> bool {
    static const std::regex USP(R"(^USP is 0x([0-9A-F]+)$)");
    std::cmatch match;
    if (std::regex_match(condition, match, USP)) {
        v = std::stoul(match.str(1), nullptr, 16);
        return true;
    }
    return false;
}

auto MatchSupervisorStackPointer(const char* condition, uint32_t& v) -> bool {
    static const std::regex SSP(R"(^SSP is 0x([0-9A-F]+)$)");
    std::cmatch match;
    if (std::regex_match(condition, match, SSP)) {
        v = std::stoul(match.str(1), nullptr, 16);
        return true;
    }
    return false;
}

auto MatchStopped(const char* condition, uint32_t& v) -> bool {
    static const std::regex STOPPED(R"(^STOPPED is (0|1)$)");
    std::cmatch match;
    if (std::regex_match(condition, match, STOPPED)) {
        v = std::stoul(match.str(1), nullptr, 10);
        return true;
    }
    return false;
}

auto MatchInterrupts(const char* condition, uint32_t& oldLevel, uint32_t& newLevel, uint32_t& vector) -> bool {
    static const std::regex INTERRUPTS(R"(INT is ([0-7]),([0-7]),([0-7]+))");
    std::cmatch match;
    if (std::regex_match(condition, match, INTERRUPTS)) {
        oldLevel = std::stoul(match.str(1), nullptr, 10);
        newLevel = std::stoul(match.str(2), nullptr, 10);
        vector = std::stoul(match.str(3), nullptr, 10);
        return true;
    }
    return false;
}

auto MatchMemoryByte(const char* condition, uint32_t& address, uint32_t& v) -> bool {
    static const std::regex MEMORY_BYTE(R"(^\(0x([0-9A-F]+)\)\.B is 0x([0-9A-F]+)$)");
    std::cmatch match;
    if (std::regex_match(condition, match, MEMORY_BYTE)) {
        address = std::stoul(match.str(1), nullptr, 16);
        v = std::stoul(match.str(2), nullptr, 16);
        return true;
    }
    return false;
}

auto MatchMemoryWord(const char* condition, uint32_t& address, uint32_t& v) -> bool {
    static const std::regex MEMORY_WORD(R"(^\(0x([0-9A-F]+)\)\.W is 0x([0-9A-F]+)$)");
    std::cmatch match;
    if (std::regex_match(condition, match, MEMORY_WORD)) {
        address = std::stoul(match.str(1), nullptr, 16);
        v = std::stoul(match.str(2), nullptr, 16);
        return true;
    }
    return false;
}

auto MatchMemoryLong(const char* condition, uint32_t& address, uint32_t& v) -> bool {
    static const std::regex MEMORY_LONG(R"(^\(0x([0-9A-F]+)\)\.L is 0x([0-9A-F]+)$)");
    std::cmatch match;
    if (std::regex_match(condition, match, MEMORY_LONG)) {
        address = std::stoul(match.str(1), nullptr, 16);
        v = std::stoul(match.str(2), nullptr, 16);
        return true;
    }
    return false;
}

}

struct M68000Test::M68000TestImpl {
    M68000TestImpl() :
        interrupts{}, memory{}, observer{}, m68000{ interrupts, memory, observer } {}

    InterruptsMock interrupts;
    MemoryMock memory;
    ObserverMock observer;
    M68000 m68000;
};

M68000Test::M68000Test() :
    impl(std::make_unique<M68000Test::M68000TestImpl>()) {}

M68000Test::~M68000Test() = default;

void M68000Test::Given(const std::initializer_list<const char*>& conditions) {
    if (HasFatalFailure()) {
        return;
    }
    uint32_t r, address, v;
    uint32_t oldLevel, newLevel, vector;
    const auto size = conditions.size();
    const auto& data = std::data(conditions);
    ASSERT_TRUE(conditions.size() >= 2);
    ASSERT_TRUE(MatchStatusRegister(data[0u], v));
    ASSERT_TRUE(MatchProgramCounter(data[1u], address));
    impl->m68000.WriteSR(v);
    impl->m68000.WritePC(address);
    auto index = 2u;
    while (index < size && MatchDataRegister(data[index], r, v)) {
        impl->m68000.WriteDataRegisterLong(r, v);
        ++index;
    }
    while (index < size && MatchAddressRegister(data[index], r, v)) {
        impl->m68000.WriteAddressRegisterLong(r, v);
        ++index;
    }
    if (index < size && MatchUserStackPointer(data[index], v)) {
        impl->m68000.WriteUSP(v);
        ++index;
    }
    if (index < size && MatchSupervisorStackPointer(data[index], v)) {
        impl->m68000.WriteSSP(v);
        ++index;
    }
    if (index < size && MatchStopped(data[index], v)) {
        impl->m68000.WriteStopped(v);
        ++index;
    }
    if (index < size && MatchInterrupts(data[index], oldLevel, newLevel, vector)) {
        impl->interrupts.SetInitialLevel(oldLevel);
        impl->interrupts.SetSubsequentLevel(newLevel);
        impl->interrupts.SetInterruptVector(vector);
        ++index;
    }
    while (index < size) {
        const auto condition = data[index];
        if (MatchMemoryByte(condition, address, v)) {
            ASSERT_TRUE(impl->memory.WriteByte(address, v));
            ++index;
        } else if (MatchMemoryWord(condition, address, v)) {
            ASSERT_TRUE(impl->memory.WriteWord(address, v));
            ++index;
        } else if (MatchMemoryLong(condition, address, v)) {
            ASSERT_TRUE(impl->memory.WriteWord(address, v >> 16u));
            ASSERT_TRUE(impl->memory.WriteWord(address + 2u, v));
            ++index;
        } else {
            FAIL() << condition;
        }
    }
}

void M68000Test::When(const std::initializer_list<const char*>& assembly) {
    if (HasFatalFailure()) {
        return;
    }

    std::vector<uint32_t> words;
    for (const auto& line: assembly) {
        Instruction instruction;
        ASSERT_TRUE(Assemble(line, instruction)) << line;
        const auto& data = instruction.GetWords();
        words.insert(words.cend(), data.begin(), data.end());
    }

    Apply(impl->m68000.ReadPC(), words);

    for (size_t i = 0; i < assembly.size(); ++i) {
        impl->m68000.Execute();
    }
}

void M68000Test::When(const std::initializer_list<uint32_t>& words) {
    if (HasFatalFailure()) {
        return;
    }

    Apply(impl->m68000.ReadPC(), words);

    impl->m68000.Execute();
}

void M68000Test::Apply(uint32_t address, const std::vector<uint32_t>& words) {
    for (const auto& w: words) {
        ASSERT_TRUE(impl->memory.WriteWord(address, w));
        address += 2u;
    }

    if (!words.empty()) {
        impl->m68000.WriteIRD(data(words)[0]);
    }

    if (words.size() >= 2) {
        impl->m68000.WriteIRC(data(words)[1]);
    }
}

void M68000Test::Then(const std::initializer_list<const char*>& conditions) {
    if (HasFatalFailure()) {
        return;
    }
    uint32_t r, address, expected;
    const auto size = conditions.size();
    const auto& data = std::data(conditions);
    ASSERT_TRUE(conditions.size() >= 3u);
    {
        ASSERT_TRUE(MatchStatusRegister(data[0u], expected));
        const auto actual = impl->m68000.ReadSR();
        EXPECT_EQ(expected, actual) << data[0u];
    }
    {
        ASSERT_TRUE(MatchProgramCounter(data[1u], expected));
        const auto actual = impl->m68000.ReadPC();
        EXPECT_EQ(expected, actual) << data[1u];
    }
    {
        ASSERT_TRUE(MatchCycles(data[2u], expected));
        const auto actual = impl->observer.GetCycles();
        EXPECT_EQ(expected, actual) << data[2u];
    }
    auto index = 3u;
    while (index < size && MatchDataRegister(data[index], r, expected)) {
        const auto actual = impl->m68000.ReadDataRegisterLong(r);
        EXPECT_EQ(expected, actual) << data[index];
        ++index;
    }
    while (index < size && MatchAddressRegister(data[index], r, expected)) {
        const auto actual = impl->m68000.ReadAddressRegisterLong(r);
        EXPECT_EQ(expected, actual) << data[index];
        ++index;
    }
    if (index < size && MatchUserStackPointer(data[index], expected)) {
        const auto actual = impl->m68000.ReadUSP();
        EXPECT_EQ(expected, actual) << data[index];
        ++index;
    }
    if (index < size && MatchSupervisorStackPointer(data[index], expected)) {
        const auto actual = impl->m68000.ReadSSP();
        EXPECT_EQ(expected, actual) << data[index];
        ++index;
    }
    if (index < size && MatchStopped(data[index], expected)) {
        const auto actual = impl->m68000.ReadStopped();
        EXPECT_EQ(expected, actual) << data[index];
        ++index;
    }
    while (index < size) {
        const auto condition = data[index];
        if (MatchMemoryByte(condition, address, expected)) {
            uint32_t actual;
            ASSERT_TRUE(impl->memory.ReadByte(address, actual));
            EXPECT_EQ(expected, actual) << condition;
            ++index;
        } else if (MatchMemoryWord(condition, address, expected)) {
            uint32_t actual;
            ASSERT_TRUE(impl->memory.ReadWord(address, actual));
            EXPECT_EQ(expected, actual) << condition;
            ++index;
        } else if (MatchMemoryLong(condition, address, expected)) {
            uint32_t hi, lo;
            ASSERT_TRUE(impl->memory.ReadWord(address, hi));
            ASSERT_TRUE(impl->memory.ReadWord(address + 2u, lo));
            const auto actual = (hi << 16u) + lo;
            EXPECT_EQ(expected, actual) << condition;
            ++index;
        } else {
            FAIL() << condition;
        }
    }
}

void M68000Test::Then(uint32_t expected) {
    const auto actual = impl->observer.GetCycles();
    EXPECT_EQ(expected, actual) << "CYCLES is " << expected;
}
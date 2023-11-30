#include <cstdint>
#include <charconv>

#include "TestFixture.h"
#include "TestData.h"

#include "M68000/Assembler.h"
#include "M68000/M68000_Constants.h"

using namespace rbrown::m68000;

namespace {

constexpr auto TRAILER_WORD_ONE = 0xBBBBu;
constexpr auto TRAILER_WORD_TWO = 0xCCCCu;

constexpr auto FromChars(const std::string& s) -> uint32_t {
    uint32_t r;
    std::from_chars(s.data(), s.data() + s.size(), r);
    return r;
}

auto MapToUint16(const StatusRegister& s) {
    uint16_t sr{};
    if (s.t) sr |= FLAG_T;
    if (s.s) sr |= FLAG_S;
    sr |= (s.interrupt_mask & 7u) << 8u;
    if (s.x) sr |= FLAG_X;
    if (s.n) sr |= FLAG_N;
    if (s.z) sr |= FLAG_Z;
    if (s.v) sr |= FLAG_V;
    if (s.c) sr |= FLAG_C;
    return sr;
}

auto Assemble(const std::vector<std::string>& assembly) -> std::vector<uint16_t> {
    std::vector<uint16_t> words {};
    for (const auto& line: assembly) {
        Instruction instruction;
        EXPECT_TRUE(Assemble(line, instruction)) << line;
        const auto& data = instruction.GetWords();
        words.insert(words.cend(), data.begin(), data.end());
    }
    words.push_back(TRAILER_WORD_ONE);
    words.push_back(TRAILER_WORD_TWO);
    return words;
}

}

TestFixture::TestFixture() :
    interrupts(),
    memory(),
    observer(),
    m68000(interrupts, memory, observer) {}

void TestFixture::Given(const struct Given& given) {
    m68000.WriteSR(MapToUint16(given.status_register));
    m68000.WritePC(given.pc);
    for (const auto& [r, value] : given.d) {
        m68000.WriteDataRegisterLong(FromChars(r), value);
    }
    for (const auto& [r, value] : given.a) {
        m68000.WriteAddressRegisterLong(FromChars(r), value);
    }
    for (const auto& [address, value] : given.memory) {
        ASSERT_TRUE(memory.WriteByte(FromChars(address), value));
    }
    m68000.WriteUSP(given.usp);
    m68000.WriteSSP(given.ssp);
    m68000.WriteStopped(given.stopped);
}

void TestFixture::When(
    const std::vector<std::string>& when,
    uint32_t givenPc,
    uint32_t thenPc) {

    const std::vector<uint16_t> code = Assemble(when);
    const std::vector<uint16_t> codeTrailer = Assemble({});

    ASSERT_TRUE(memory.WriteWords(givenPc, code));
    ASSERT_TRUE(memory.WriteWords(thenPc, codeTrailer));

    m68000.WriteIRD(code[0]);
    m68000.WriteIRC(code[1]);

    for (size_t i = 0; i < when.size(); ++i) {
        m68000.Execute();
    }
}

void TestFixture::Then(const struct Then& then) {
    EXPECT_EQ(MapToUint16(then.status_register), m68000.ReadSR());
    EXPECT_EQ(then.pc, m68000.ReadPC());
    EXPECT_EQ(then.cycles, observer.GetCycles());
    if (!then.stopped) {
        EXPECT_EQ(TRAILER_WORD_ONE, m68000.ReadIRD());
        EXPECT_EQ(TRAILER_WORD_TWO, m68000.ReadIRC());
    }
    for (const auto& [r, expected] : then.d) {
        const auto actual = m68000.ReadDataRegisterLong(FromChars(r));
        EXPECT_EQ(expected, actual);
    }
    for (const auto& [r, expected] : then.a) {
        const auto actual = m68000.ReadAddressRegisterLong(FromChars(r));
        EXPECT_EQ(expected, actual);
    }
    for (const auto& [address, expected] : then.memory) {
        uint32_t actual;
        ASSERT_TRUE(memory.ReadByte(FromChars(address), actual));
        EXPECT_EQ(expected, actual);
    }
    EXPECT_EQ(then.usp, m68000.ReadUSP());
    EXPECT_EQ(then.ssp, m68000.ReadSSP());
    EXPECT_EQ(then.stopped, m68000.ReadStopped());
}
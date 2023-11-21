#include "M68000/Disassembler.h"
#include "M68000/DisassemblerImpl.h"
#include "M68000/M68000_Opcode.h"
#include "M68000/M68000_Int.h"

#include <fmt/core.h>
#include <fmt/ranges.h>
#include <vector>

using namespace rbrown::m68000;

auto Disassembler::ReadNextByte() -> uint16_t {
    return Truncate8(stream.ReadWord());
}

auto Disassembler::ReadNextWord() -> uint16_t {
    return stream.ReadWord();
}

auto Disassembler::ReadNextLong() -> uint32_t {
    const auto hi = stream.ReadWord();
    const auto lo = stream.ReadWord();
    return (hi << 16u) + lo;
}

auto Disassembler::Dn(uint32_t n) -> std::string {
    return fmt::format("D{}", n);
}

auto Disassembler::An(uint32_t n) -> std::string {
    return fmt::format("A{}", n);
}

auto Disassembler::AnIndirect(uint32_t n) -> std::string {
    return fmt::format("(A{})", n);
}

auto Disassembler::AnIncrement(uint32_t n) -> std::string {
    return fmt::format("(A{})+", n);
}

auto Disassembler::AnDecrement(uint32_t n) -> std::string {
    return fmt::format("-(A{})", n);
}

auto Disassembler::AnDisplacement(uint32_t n) -> std::string {
    const auto displacement = ReadNextWord();
    return fmt::format("({}, A{})", displacement, n);
}

auto Disassembler::AnIndex(uint32_t n) -> std::string {
    const auto extension = ReadNextWord();
    const auto index = ExtensionWordDisplacement(extension);
    const auto type = ExtensionWordAddress(extension) ? 'A' : 'D';
    const auto m = ExtensionWordRegister(extension);
    const auto size = ExtensionWordLong(extension) ? 'L' : 'W';
    return fmt::format("({}, A{}, {}{}.{})", index, n, type, m, size);
}

auto Disassembler::Short() -> std::string {
    return fmt::format("({}).W", ReadNextWord());
}

auto Disassembler::Long() -> std::string {
    return fmt::format("({}).L", ReadNextLong());
}

auto Disassembler::PCDisplacement() -> std::string {
    const auto displacement = ReadNextWord();
    return fmt::format("({}, PC)", displacement);
}

auto Disassembler::PCIndex() -> std::string {
    const auto extension = ReadNextWord();
    const auto index = ExtensionWordDisplacement(extension);
    const auto type = ExtensionWordAddress(extension) ? 'A' : 'D';
    const auto m = ExtensionWordRegister(extension);
    const auto size = ExtensionWordLong(extension) ? 'L' : 'W';
    return fmt::format("({}, PC, {}{}.{})", index, type, m, size);
}

auto Disassembler::ImmediateByte() -> std::string { return fmt::format("#{}", ReadNextByte()); }

auto Disassembler::ImmediateWord() -> std::string { return fmt::format("#{}", ReadNextWord()); }

auto Disassembler::ImmediateLong() -> std::string { return fmt::format("#{}", ReadNextLong()); }

auto Disassembler::Quick(uint32_t v) -> std::string { return fmt::format("#{}", v);}

auto Disassembler::QuickByte(uint32_t v) -> std::string { return fmt::format("#{:-}", static_cast<int8_t>(v)); }

auto Disassembler::TrapVector(uint32_t opcode) -> std::string {
    return fmt::format("#0x{:X}", OpcodeTrapVector(opcode));
}

auto Disassembler::RegisterList(uint32_t list) -> std::string {
    std::vector<std::string> segments;
    RegisterList(list, 'D', segments);
    RegisterList(list >> 8u, 'A', segments);
    return fmt::format("{}", fmt::join(segments, "/"));
}

auto Disassembler::RegisterList(
    uint32_t list,
    char symbol,
    std::vector<std::string>& segments) -> void {
    auto count = 0u;
    for (auto i = 0u; i < 8u; ++i) {
        if (list & (1u << i)) {
            ++count;
        } else if (count == 1u) {
            segments.push_back(fmt::format("{}{}", symbol, i - 1u));
            count = 0u;
        } else if (count) {
            segments.push_back(fmt::format("{}{}-{}{}", symbol, i - count, symbol, i - 1u));
            count = 0u;
        }
    }
    if (count == 1u) {
        segments.push_back(fmt::format("{}{}", symbol, 7u));
    } else if (count) {
        segments.push_back(fmt::format("{}{}-{}{}", symbol, 7 - count, symbol, 7 - 1u));
    }
}

auto Disassembler::BinaryInstruction(const std::string& mnemonic,
                                     const std::string& s,
                                     const std::string& d) -> std::string {
    return fmt::format("{} {}, {}", mnemonic, s, d);
}

auto Disassembler::SingleInstruction(const std::string& mnemonic,
                                     const std::string& d) -> std::string {
    return fmt::format("{} {}", mnemonic, d);
}

auto Disassembler::BranchInstruction(const std::string& cc,
                                     const std::string& size,
                                     uint16_t displacement) -> std::string {
    const auto signedDisplacement = static_cast<int16_t>(displacement);
    return fmt::format("B{}.{} *{:+}", cc, size, 2 + signedDisplacement);
}

auto Disassembler::SetConditionInstruction(const std::string& cc,
                                           const std::string& d) -> std::string {
    return fmt::format("S{} {}", cc, d);
}

auto Disassembler::DecrementBranchInstruction(const std::string& cc,
                                              const std::string& d,
                                              uint16_t displacement) -> std::string {
    const auto signedDisplacement = static_cast<int16_t>(displacement);
    return fmt::format("DB{} {}, *{:+}", cc, d, 2 + signedDisplacement);
}

auto Disassembler::Disassemble() -> std::string {
    const auto opcode = ReadNextWord();
    switch (OpcodeLine(opcode)) {
        case 0x0u: return Line0(opcode);
        case 0x1u: return Line1(opcode);
        case 0x2u: return Line2(opcode);
        case 0x3u: return Line3(opcode);
        case 0x4u: return Line4(opcode);
        case 0x5u: return Line5(opcode);
        case 0x6u: return Line6(opcode);
        case 0x7u: return Line7(opcode);
        case 0x8u: return Line8(opcode);
        case 0x9u: return Line9(opcode);
        case 0xAu: return LineA(opcode);
        case 0xBu: return LineB(opcode);
        case 0xCu: return LineC(opcode);
        case 0xDu: return LineD(opcode);
        case 0xEu: return LineE(opcode);
        case 0xFu: return LineF(opcode);
            [[unlikely]] default: return {};
    }
}

auto Disassembler::LineA(uint32_t) -> std::string { return {}; }

auto Disassembler::LineF(uint32_t) -> std::string { return {}; }

namespace rbrown::m68000 {

std::string Disassemble(InstructionStream& stream) {
    Disassembler disassembler{ stream };
    return disassembler.Disassemble();
}


}
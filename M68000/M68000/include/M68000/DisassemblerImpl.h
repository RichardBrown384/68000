#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace rbrown::m68000 {

class InstructionStream;

constexpr static auto STATUS_REGISTER = "SR";
constexpr static auto CONDITION_CODE_REGISTER = "CCR";

struct Disassembler {
    auto Disassemble() -> std::string;

    auto Line0(uint32_t) -> std::string;
    auto Line0Size0(uint32_t) -> std::string;
    auto Line0Size0Rx0(const std::string&, uint32_t) -> std::string;
    auto Line0Size0Rx2(const std::string&, uint32_t) -> std::string;
    auto Line0Size0Rx4(uint32_t) -> std::string;
    auto Line0Size1(uint32_t) -> std::string;
    auto Line0Size1Rx0(const std::string&, uint32_t) -> std::string;
    auto Line0Size1Rx2(const std::string&, uint32_t) -> std::string;
    auto Line0Size1Rx4(uint32_t) -> std::string;
    auto Line0Size2(uint32_t) -> std::string;
    auto Line0Size2Rx0(const std::string&, uint32_t) -> std::string;
    auto Line0Size2Rx4(uint32_t) -> std::string;
    auto Line0Size3(uint32_t) -> std::string;
    auto Line0Size3Rx4(uint32_t) -> std::string;
    auto Line0Size4(uint32_t) -> std::string;
    auto Line0Size5(uint32_t) -> std::string;
    auto Line0Size6(uint32_t) -> std::string;
    auto Line0Size7(uint32_t) -> std::string;

    auto Line1(uint32_t) -> std::string;
    auto Line1(const std::string&, uint32_t) -> std::string;

    auto Line2(uint32_t) -> std::string;
    auto Line2(const std::string&, uint32_t) -> std::string;

    auto Line3(uint32_t) -> std::string;
    auto Line3(const std::string&, uint32_t) -> std::string;

    auto Line4(uint32_t) -> std::string;
    auto Line4Size0(uint32_t) -> std::string;
    auto Line4Size0(const std::string&, uint32_t) -> std::string;
    auto Line4Size1(uint32_t) -> std::string;
    auto Line4Size1Rx4(uint32_t) -> std::string;
    auto Line4Size1Rx7(uint32_t) -> std::string;
    auto Line4Size2(uint32_t) -> std::string;
    auto Line4Size2Rx4(uint32_t) -> std::string;
    auto Line4Size2Rx6(uint32_t) -> std::string;
    auto Line4Size2Rx7(const std::string&, uint32_t) -> std::string;
    auto Line4Size3(uint32_t) -> std::string;
    auto Line4Size3Rx0(uint32_t) -> std::string;
    auto Line4Size3Rx2(const std::string&, uint32_t) -> std::string;
    auto Line4Size3Rx4(uint32_t) -> std::string;
    auto Line4Size3Rx5(uint32_t) -> std::string;
    auto Line4Size3Rx6(uint32_t) -> std::string;
    auto Line4Size6(uint32_t) -> std::string;
    auto Line4Size7(uint32_t) -> std::string;

    auto Line5(uint32_t) -> std::string;
    auto Line5Size0(const std::string&, uint32_t) -> std::string;
    auto Line5Size1(const std::string&, uint32_t) -> std::string;
    auto Line5Size3(uint32_t) -> std::string;

    auto Line6(uint32_t) -> std::string;

    static auto Line7(uint32_t) -> std::string;

    auto Line8(uint32_t) -> std::string;
    auto Line8Size0(const std::string&, uint32_t) -> std::string;
    auto Line8Size1(const std::string&, uint32_t) -> std::string;
    auto Line8Size2(const std::string&, uint32_t) -> std::string;
    auto Line8Size4(uint32_t) -> std::string;
    auto Line8Size5(const std::string&, uint32_t) -> std::string;

    auto Line9(uint32_t) -> std::string;
    auto Line9Size1(const std::string&, uint32_t) -> std::string;
    auto Line9Size2(const std::string&, uint32_t) -> std::string;
    auto Line9Size3(const std::string&, uint32_t) -> std::string;
    auto Line9Size4(uint32_t) -> std::string;
    auto Line9Size5(uint32_t) -> std::string;
    auto Line9Size6(uint32_t) -> std::string;
    auto Line9Size7(const std::string&, uint32_t) -> std::string;

    static auto LineA(uint32_t) -> std::string;

    auto LineB(uint32_t) -> std::string;
    auto LineBSize4(uint32_t) -> std::string;
    auto LineBSize5(uint32_t) -> std::string;
    auto LineBSize6(uint32_t) -> std::string;

    auto LineC(uint32_t) -> std::string;
    auto LineCSize4(uint32_t) -> std::string;
    auto LineCSize5(uint32_t) -> std::string;
    auto LineCSize6(uint32_t) -> std::string;

    auto LineD(uint32_t) -> std::string;
    auto LineDSize4(uint32_t) -> std::string;
    auto LineDSize5(uint32_t) -> std::string;
    auto LineDSize6(uint32_t) -> std::string;

    auto LineE(uint32_t) -> std::string;
    static auto LineESize0(uint32_t) -> std::string;
    static auto LineESize1(uint32_t) -> std::string;
    static auto LineESize2(uint32_t) -> std::string;
    auto LineESize3(uint32_t) -> std::string;
    auto LineESize3(const std::string&, uint32_t) -> std::string;
    static auto LineESize4(uint32_t) -> std::string;
    static auto LineESize5(uint32_t) -> std::string;
    static auto LineESize6(uint32_t) -> std::string;
    auto LineESize7(uint32_t) -> std::string;

    static auto LineF(uint32_t) -> std::string;

    static auto Dn(uint32_t) -> std::string;
    static auto An(uint32_t) -> std::string;
    static auto AnIndirect(uint32_t) -> std::string;
    static auto AnIncrement(uint32_t) -> std::string;
    static auto AnDecrement(uint32_t) -> std::string;
    auto AnDisplacement(uint32_t) -> std::string;
    auto AnIndex(uint32_t) -> std::string;
    auto Short() -> std::string;
    auto Long() -> std::string;
    auto PCDisplacement() -> std::string;
    auto PCIndex() -> std::string;
    auto ImmediateByte() -> std::string;
    auto ImmediateWord() -> std::string;
    auto ImmediateLong() -> std::string;
    static auto Quick(uint32_t) -> std::string;
    static auto QuickByte(uint32_t) -> std::string;
    static auto TrapVector(uint32_t) -> std::string;
    static auto RegisterList(uint32_t) -> std::string;
    static auto RegisterList(uint32_t, char, std::vector<std::string>&) -> void;

    static auto BinaryInstruction(const std::string&, const std::string&, const std::string&) -> std::string;
    static auto SingleInstruction(const std::string&, const std::string&) -> std::string;
    static auto BranchInstruction(const std::string&, const std::string&, uint16_t displacement) -> std::string;
    static auto SetConditionInstruction(const std::string&, const std::string&) -> std::string;
    static auto DecrementBranchInstruction(const std::string&, const std::string&, uint16_t) -> std::string;

    auto ReadNextByte() -> uint16_t;
    auto ReadNextWord() -> uint16_t;
    auto ReadNextLong() -> uint32_t;

    InstructionStream& stream;
};

}



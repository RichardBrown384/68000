#include "M68000/M68000.h"
#include "M68000/M68000_Opcode.h"
#include "M68000/M68000_EffectiveAddress.h"
#include "M68000/M68000_Operations.h"

using namespace rbrown::m68000;

auto M68000::ExecuteLineE(uint32_t opcode) -> void {
    switch (OpcodeModeX(opcode)) {
        case 0u: return ExecuteShiftRotateRightDataRegister<Byte>(opcode);
        case 1u: return ExecuteShiftRotateRightDataRegister<Word>(opcode);
        case 2u: return ExecuteShiftRotateRightDataRegister<Long>(opcode);
        case 3u: return ExecuteShiftRotateRightEffectiveAddress(opcode);
        case 4u: return ExecuteShiftRotateLeftDataRegister<Byte>(opcode);
        case 5u: return ExecuteShiftRotateLeftDataRegister<Word>(opcode);
        case 6u: return ExecuteShiftRotateLeftDataRegister<Long>(opcode);
        case 7u: return ExecuteShiftRotateLeftEffectiveAddress(opcode);
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteShiftRotateRightDataRegister(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteShiftRotateCountDataRegister<&M68000::Asr<T>, T>(opcode);
        case 1u: return ExecuteShiftRotateCountDataRegister<&M68000::Lsr<T>, T>(opcode);
        case 2u: return ExecuteShiftRotateCountDataRegister<&M68000::Roxr<T>, T>(opcode);
        case 3u: return ExecuteShiftRotateCountDataRegister<&M68000::Ror<T>, T>(opcode);
        case 4u: return ExecuteShiftRotateRegisterDataRegister<&M68000::Asr<T>, T>(opcode);
        case 5u: return ExecuteShiftRotateRegisterDataRegister<&M68000::Lsr<T>, T>(opcode);
        case 6u: return ExecuteShiftRotateRegisterDataRegister<&M68000::Roxr<T>, T>(opcode);
        case 7u: return ExecuteShiftRotateRegisterDataRegister<&M68000::Ror<T>, T>(opcode);
        [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteShiftRotateRightEffectiveAddress(uint32_t opcode) -> void {
    switch (OpcodeRegisterX(opcode)) {
        case 0u: return ExecuteShiftRotateEffectiveAddress<&M68000::Asr<Word>>(opcode);
        case 1u: return ExecuteShiftRotateEffectiveAddress<&M68000::Lsr<Word>>(opcode);
        case 2u: return ExecuteShiftRotateEffectiveAddress<&M68000::Roxr<Word>>(opcode);
        case 3u: return ExecuteShiftRotateEffectiveAddress<&M68000::Ror<Word>>(opcode);
        [[unlikely]] default: return ExecuteIllegal();
    }
}

template<auto ShiftRotate>
auto M68000::ExecuteShiftRotateEffectiveAddress(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 2u: return ExecuteShiftRotateEffectiveAddress<ShiftRotate, &M68000::ReadFromAddressIndirect<Word>>(opcode);
        case 3u: return ExecuteShiftRotateEffectiveAddress<ShiftRotate, &M68000::ReadFromAddressIncrement<Word>>(opcode);
        case 4u: return ExecuteShiftRotateEffectiveAddress<ShiftRotate, &M68000::ReadFromAddressDecrement<Word>>(opcode);
        case 5u: return ExecuteShiftRotateEffectiveAddress<ShiftRotate, &M68000::ReadFromAddressDisplacement<Word>>(opcode);
        case 6u: return ExecuteShiftRotateEffectiveAddress<ShiftRotate, &M68000::ReadFromAddressIndex<Word>>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteShiftRotateEffectiveAddress<ShiftRotate, &M68000::ReadFromShort<Word>>(opcode);
                case 1u: return ExecuteShiftRotateEffectiveAddress<ShiftRotate, &M68000::ReadFromLong<Word>>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteShiftRotateLeftDataRegister(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteShiftRotateCountDataRegister<&M68000::Asl<T>, T>(opcode);
        case 1u: return ExecuteShiftRotateCountDataRegister<&M68000::Lsl<T>, T>(opcode);
        case 2u: return ExecuteShiftRotateCountDataRegister<&M68000::Roxl<T>, T>(opcode);
        case 3u: return ExecuteShiftRotateCountDataRegister<&M68000::Rol<T>, T>(opcode);
        case 4u: return ExecuteShiftRotateRegisterDataRegister<&M68000::Asl<T>, T>(opcode);
        case 5u: return ExecuteShiftRotateRegisterDataRegister<&M68000::Lsl<T>, T>(opcode);
        case 6u: return ExecuteShiftRotateRegisterDataRegister<&M68000::Roxl<T>, T>(opcode);
        case 7u: return ExecuteShiftRotateRegisterDataRegister<&M68000::Rol<T>, T>(opcode);
        [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteShiftRotateLeftEffectiveAddress(uint32_t opcode) -> void {
    switch (OpcodeRegisterX(opcode)) {
        case 0u: return ExecuteShiftRotateEffectiveAddress<&M68000::Asl<Word>>(opcode);
        case 1u: return ExecuteShiftRotateEffectiveAddress<&M68000::Lsl<Word>>(opcode);
        case 2u: return ExecuteShiftRotateEffectiveAddress<&M68000::Roxl<Word>>(opcode);
        case 3u: return ExecuteShiftRotateEffectiveAddress<&M68000::Rol<Word>>(opcode);
            [[unlikely]] default: return ExecuteIllegal();
    }
}

// OP.{B|W|L} #imm, Dy

template<auto ShiftRotate, typename T>
auto M68000::ExecuteShiftRotateCountDataRegister(uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = ReadDataRegisterLong(ry);
    const auto shift = OpcodeQuick(opcode);
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    if constexpr(std::is_same_v<T, Byte> || std::is_same_v<T, Word>) {
        ElapseCycles(2u + 2u * shift);
    } else {
        ElapseCycles(4u + 2u * shift);
    }
    const auto result = (this->*ShiftRotate)(shift, y);
    WriteDataRegister<T>(ry, result);
}

// OP.{B|W|L} Dx, Dy

template<auto ShiftRotate, typename T>
auto M68000::ExecuteShiftRotateRegisterDataRegister(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadDataRegisterLong(rx);
    const auto y = ReadDataRegisterLong(ry);
    const auto shift = x & 0x3Fu;
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    if constexpr(std::is_same_v<T, Byte> || std::is_same_v<T, Word>) {
        ElapseCycles(2u + 2u * shift);
    } else {
        ElapseCycles(4u + 2u * shift);
    }
    const auto result = (this->*ShiftRotate)(shift, y);
    WriteDataRegister<T>(ry, result);
}

// OP.{B|W|L} <ea>

template<auto ShiftRotate, auto Source>
auto M68000::ExecuteShiftRotateEffectiveAddress(uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = (this->*ShiftRotate)(1u, y);
    WriteMemory<Word>(address, result);
}
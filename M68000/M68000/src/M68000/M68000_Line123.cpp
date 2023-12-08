#include "M68000/M68000.h"
#include "M68000/M68000_Opcode.h"
#include "M68000/M68000_EffectiveAddress.h"
#include "M68000/M68000_Operations.h"

using namespace rbrown::m68000;

auto M68000::ExecuteLine1(uint32_t opcode) -> void {
    ExecuteMove<Byte>(opcode);
}

auto M68000::ExecuteLine2(uint32_t opcode) -> void {
    ExecuteMove<Long>(opcode);
}

auto M68000::ExecuteLine3(uint32_t opcode) -> void {
    ExecuteMove<Word>(opcode);
}

template<typename T>
auto M68000::ExecuteMove(uint32_t opcode) -> void {
    switch (OpcodeModeX(opcode)) {
        case 0u: return ExecuteMoveDataRegister<T>(opcode);
        case 1u: return ExecuteMoveAddressRegister<T>(opcode);
        case 2u: return ExecuteMoveAddressIndirect<T>(opcode);
        case 3u: return ExecuteMoveAddressIncrement<T>(opcode);
        case 4u: return ExecuteMoveAddressDecrement<T>(opcode);
        case 5u: return ExecuteMoveAddressDisplacement<T>(opcode);
        case 6u: return ExecuteMoveAddressIndex<T>(opcode);
        case 7u:
            switch (OpcodeRegisterX(opcode)) {
                case 0u: return ExecuteMoveShort<T>(opcode);
                case 1u: return ExecuteMoveLong<T>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteMoveDataRegister(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteMoveDataRegister<&M68000::ReadFromDataRegister<T>, T>(opcode);
        case 1u:
            if constexpr(std::is_same_v<T, Byte>) {
                return ExecuteIllegal();
            }
            return ExecuteMoveDataRegister<&M68000::ReadFromAddressRegister<T>, T>(opcode);
        case 2u: return ExecuteMoveDataRegister<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteMoveDataRegister<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteMoveDataRegister<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteMoveDataRegister<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteMoveDataRegister<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteMoveDataRegister<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteMoveDataRegister<&M68000::ReadFromLong<T>, T>(opcode);
                case 2u: return ExecuteMoveDataRegister<&M68000::ReadFromPCDisplacement<T>, T>(opcode);
                case 3u: return ExecuteMoveDataRegister<&M68000::ReadFromPCIndex<T>, T>(opcode);
                case 4u: return ExecuteMoveDataRegister<&M68000::ReadFromImmediate<T>, T>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteMoveAddressRegister(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteMoveAddressRegister<&M68000::ReadFromDataRegister<T>, T>(opcode);
        case 1u: return ExecuteMoveAddressRegister<&M68000::ReadFromAddressRegister<T>, T>(opcode);
        case 2u: return ExecuteMoveAddressRegister<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteMoveAddressRegister<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteMoveAddressRegister<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteMoveAddressRegister<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteMoveAddressRegister<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteMoveAddressRegister<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteMoveAddressRegister<&M68000::ReadFromLong<T>, T>(opcode);
                case 2u: return ExecuteMoveAddressRegister<&M68000::ReadFromPCDisplacement<T>, T>(opcode);
                case 3u: return ExecuteMoveAddressRegister<&M68000::ReadFromPCIndex<T>, T>(opcode);
                case 4u: return ExecuteMoveAddressRegister<&M68000::ReadFromImmediate<T>, T>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteMoveAddressIndirect(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteMoveAddressIndirect<&M68000::ReadFromDataRegister<T>, T>(opcode);
        case 1u:
            if constexpr(std::is_same_v<T, Byte>) {
                return ExecuteIllegal();
            }
            return ExecuteMoveAddressIndirect<&M68000::ReadFromAddressRegister<T>, T>(opcode);
        case 2u: return ExecuteMoveAddressIndirect<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteMoveAddressIndirect<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteMoveAddressIndirect<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteMoveAddressIndirect<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteMoveAddressIndirect<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteMoveAddressIndirect<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteMoveAddressIndirect<&M68000::ReadFromLong<T>, T>(opcode);
                case 2u: return ExecuteMoveAddressIndirect<&M68000::ReadFromPCDisplacement<T>, T>(opcode);
                case 3u: return ExecuteMoveAddressIndirect<&M68000::ReadFromPCIndex<T>, T>(opcode);
                case 4u: return ExecuteMoveAddressIndirect<&M68000::ReadFromImmediate<T>, T>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteMoveAddressIncrement(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteMoveAddressIncrement<&M68000::ReadFromDataRegister<T>, T>(opcode);
        case 1u:
            if constexpr(std::is_same_v<T, Byte>) {
                return ExecuteIllegal();
            }
            return ExecuteMoveAddressIncrement<&M68000::ReadFromAddressRegister<T>, T>(opcode);
        case 2u: return ExecuteMoveAddressIncrement<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteMoveAddressIncrement<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteMoveAddressIncrement<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteMoveAddressIncrement<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteMoveAddressIncrement<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteMoveAddressIncrement<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteMoveAddressIncrement<&M68000::ReadFromLong<T>, T>(opcode);
                case 2u: return ExecuteMoveAddressIncrement<&M68000::ReadFromPCDisplacement<T>, T>(opcode);
                case 3u: return ExecuteMoveAddressIncrement<&M68000::ReadFromPCIndex<T>, T>(opcode);
                case 4u: return ExecuteMoveAddressIncrement<&M68000::ReadFromImmediate<T>, T>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteMoveAddressDecrement(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteMoveAddressDecrement<&M68000::ReadFromDataRegister<T>, T>(opcode);
        case 1u:
            if constexpr(std::is_same_v<T, Byte>) {
                return ExecuteIllegal();
            }
            return ExecuteMoveAddressDecrement<&M68000::ReadFromAddressRegister<T>, T>(opcode);
        case 2u: return ExecuteMoveAddressDecrement<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteMoveAddressDecrement<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteMoveAddressDecrement<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteMoveAddressDecrement<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteMoveAddressDecrement<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteMoveAddressDecrement<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteMoveAddressDecrement<&M68000::ReadFromLong<T>, T>(opcode);
                case 2u: return ExecuteMoveAddressDecrement<&M68000::ReadFromPCDisplacement<T>, T>(opcode);
                case 3u: return ExecuteMoveAddressDecrement<&M68000::ReadFromPCIndex<T>, T>(opcode);
                case 4u: return ExecuteMoveAddressDecrement<&M68000::ReadFromImmediate<T>, T>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteMoveAddressDisplacement(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteMoveAddressDisplacement<&M68000::ReadFromDataRegister<T>, T>(opcode);
        case 1u:
            if constexpr(std::is_same_v<T, Byte>) {
                return ExecuteIllegal();
            }
            return ExecuteMoveAddressDisplacement<&M68000::ReadFromAddressRegister<T>, T>(opcode);
        case 2u: return ExecuteMoveAddressDisplacement<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteMoveAddressDisplacement<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteMoveAddressDisplacement<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteMoveAddressDisplacement<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteMoveAddressDisplacement<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteMoveAddressDisplacement<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteMoveAddressDisplacement<&M68000::ReadFromLong<T>, T>(opcode);
                case 2u: return ExecuteMoveAddressDisplacement<&M68000::ReadFromPCDisplacement<T>, T>(opcode);
                case 3u: return ExecuteMoveAddressDisplacement<&M68000::ReadFromPCIndex<T>, T>(opcode);
                case 4u: return ExecuteMoveAddressDisplacement<&M68000::ReadFromImmediate<T>, T>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteMoveAddressIndex(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteMoveAddressIndex<&M68000::ReadFromDataRegister<T>, T>(opcode);
        case 1u:
            if constexpr(std::is_same_v<T, Byte>) {
                return ExecuteIllegal();
            }
            return ExecuteMoveAddressIndex<&M68000::ReadFromAddressRegister<T>, T>(opcode);
        case 2u: return ExecuteMoveAddressIndex<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteMoveAddressIndex<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteMoveAddressIndex<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteMoveAddressIndex<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteMoveAddressIndex<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteMoveAddressIndex<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteMoveAddressIndex<&M68000::ReadFromLong<T>, T>(opcode);
                case 2u: return ExecuteMoveAddressIndex<&M68000::ReadFromPCDisplacement<T>, T>(opcode);
                case 3u: return ExecuteMoveAddressIndex<&M68000::ReadFromPCIndex<T>, T>(opcode);
                case 4u: return ExecuteMoveAddressIndex<&M68000::ReadFromImmediate<T>, T>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteMoveShort(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteMoveShort<&M68000::ReadFromDataRegister<T>, T>(opcode);
        case 1u:
            if constexpr(std::is_same_v<T, Byte>) {
                return ExecuteIllegal();
            }
            return ExecuteMoveShort<&M68000::ReadFromAddressRegister<T>, T>(opcode);
        case 2u: return ExecuteMoveShort<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteMoveShort<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteMoveShort<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteMoveShort<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteMoveShort<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteMoveShort<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteMoveShort<&M68000::ReadFromLong<T>, T>(opcode);
                case 2u: return ExecuteMoveShort<&M68000::ReadFromPCDisplacement<T>, T>(opcode);
                case 3u: return ExecuteMoveShort<&M68000::ReadFromPCIndex<T>, T>(opcode);
                case 4u: return ExecuteMoveShort<&M68000::ReadFromImmediate<T>, T>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteMoveLong(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteMoveLong_Register<&M68000::ReadFromDataRegister<T>, T>(opcode);
        case 1u:
            if constexpr(std::is_same_v<T, Byte>) {
                return ExecuteIllegal();
            }
            return ExecuteMoveLong_Register<&M68000::ReadFromAddressRegister<T>, T>(opcode);
        case 2u: return ExecuteMoveLong<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteMoveLong<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteMoveLong<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteMoveLong<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteMoveLong<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteMoveLong<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteMoveLong<&M68000::ReadFromLong<T>, T>(opcode);
                case 2u: return ExecuteMoveLong<&M68000::ReadFromPCDisplacement<T>, T>(opcode);
                case 3u: return ExecuteMoveLong<&M68000::ReadFromPCIndex<T>, T>(opcode);
                case 4u: return ExecuteMoveLong<&M68000::ReadFromImmediate<T>, T>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

// MOVE.{B|W|L} <ea>, Dx

template<auto Source, typename T>
auto M68000::ExecuteMoveDataRegister(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    const auto result = Move<T>(y);
    WriteDataRegister<T>(rx, result);
    ExecuteFinalPrefetchCycle();
}

// MOVE.{W|L} <ea>, Ax

template<auto Source, typename T>
auto M68000::ExecuteMoveAddressRegister(uint32_t opcode) -> void {
    if constexpr(std::is_same_v<T, Byte>) {
        return ExecuteIllegal();
    }
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    const auto result = Movea<T>(y);
    WriteAddressRegisterLong(rx, result);
    ExecuteFinalPrefetchCycle();
}

// MOVE.{B|W|L} <ea>, (Ax)

template<auto Source, typename T>
auto M68000::ExecuteMoveAddressIndirect(uint32_t opcode) -> void {
    // The prefetch cycles happen after the writes
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!EffectiveAddressAddressIndirect(rx, address)) [[unlikely]] {
        return;
    }
    const auto result = Move<T>(y);
    if (!WriteMemory<T>(address, result)) [[unlikely]] {
        return;
    }
    ExecuteFinalPrefetchCycle();
}

// MOVE.{B|W|L} <ea>, (Ax)+

template<auto Source, typename T>
auto M68000::ExecuteMoveAddressIncrement(uint32_t opcode) -> void {
    // The prefetch cycles happen after the writes
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!EffectiveAddressAddressIncrement<T>(rx, address)) [[unlikely]] {
        return;
    }
    const auto result = Move<T>(y);
    if (!WriteMemory<T>(address, result)) [[unlikely]] {
        return;
    }
    ExecuteFinalPrefetchCycle();
}

// MOVE.{B|W|L} <ea>, -(Ax)

template<auto Source, typename T>
auto M68000::ExecuteMoveAddressDecrement(uint32_t opcode) -> void {
    // The prefetch cycles happen before the writes
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!EffectiveAddressAddressDecrementWithoutInternalCycle<T>(rx, address)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Move<T>(y);
    WriteMemory<T>(address, result);
}

// MOVE.{B|W|L} <ea>, (d, Ax)

template<auto Source, typename T>
auto M68000::ExecuteMoveAddressDisplacement(uint32_t opcode) -> void{
    // The prefetch cycles happen after the writes
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!EffectiveAddressAddressDisplacement(rx, address)) [[unlikely]] {
        return;
    }
    const auto result = Move<T>(y);
    if (!WriteMemory<T>(address, result)) [[unlikely]] {
        return;
    }
    ExecuteFinalPrefetchCycle();
}

// MOVE.{B|W|L} <ea>, (d, Ax, Xn)

template<auto Source, typename T>
auto M68000::ExecuteMoveAddressIndex(uint32_t opcode) -> void {
    // The prefetch cycles happen after the writes
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!EffectiveAddressAddressIndex(rx, address)) [[unlikely]] {
        return;
    }
    const auto result = Move<T>(y);
    if (!WriteMemory<T>(address, result)) [[unlikely]] {
        return;
    }
    ExecuteFinalPrefetchCycle();
}

// MOVE.{B|W|L} <ea>, ().W

template<auto Source, typename T>
auto M68000::ExecuteMoveShort(uint32_t opcode) -> void {
    // The prefetch cycles happen after the writes
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!EffectiveAddressShort(rx, address)) [[unlikely]] {
        return;
    }
    const auto result = Move<T>(y);
    if (!WriteMemory<T>(address, result)) [[unlikely]] {
        return;
    }
    ExecuteFinalPrefetchCycle();
}

// MOVE.{B|W|L} {D|A}y, ().W

template<auto Source, typename T>
auto M68000::ExecuteMoveLong_Register(uint32_t opcode) -> void {
    // The prefetch cycles happen after the writes
    const auto rx = OpcodeRegisterY(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!EffectiveAddressLong(rx, address)) [[unlikely]] {
        return;
    }
    const auto result = Move<T>(y);
    if (!WriteMemory<T>(address, result)) [[unlikely]] {
        return;
    }
    ExecuteFinalPrefetchCycle();
}

template<auto Source, typename T>
auto M68000::ExecuteMoveLong(uint32_t opcode) -> void {
    // The instruction only performs one prefetch cycle
    // to copy the low order word of the address into irc
    // Then uses the new value of irc to form the address
    // The second usual prefetch cycle is deferred until after the write-cycles.
    // This is what the prefetch doc calls a class 2 instruction
    // (2 prefetches after the write-cycles).
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    const auto hi = ReadIRC();
    if (!ExecutePrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto lo = ReadIRC();
    address = (hi << 16u) + lo;
    const auto result = Move<T>(y);
    if (!WriteMemory<T>(address, result)) [[unlikely]] {
        return;
    }
    if (!ExecutePrefetchCycle()) [[unlikely]] {
        return;
    }
    ExecuteFinalPrefetchCycle();
}
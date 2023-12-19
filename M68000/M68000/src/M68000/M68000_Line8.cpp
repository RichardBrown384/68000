#include "M68000/M68000.h"
#include "M68000/M68000_Opcode.h"
#include "M68000/M68000_EffectiveAddress.h"
#include "M68000/M68000_Operations.h"

using namespace rbrown::m68000;

auto M68000::ExecuteLine8(uint32_t opcode) -> void {
    switch (OpcodeModeX(opcode)) {
        case 0u: return ExecuteOrDataRegister<Byte>(opcode);
        case 1u: return ExecuteOrDataRegister<Word>(opcode);
        case 2u: return ExecuteOrDataRegister<Long>(opcode);
        case 3u: return ExecuteDivuDataRegister(opcode);
        case 4u: return ExecuteOrEffectiveAddress<Byte>(opcode);
        case 5u: return ExecuteOrEffectiveAddress<Word>(opcode);
        case 6u: return ExecuteOrEffectiveAddress<Long>(opcode);
        case 7u: return ExecuteDivsDataRegister(opcode);
        [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteOrDataRegister(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteOrDataRegister_RegisterImmediate<&M68000::ReadFromDataRegister<T>, T>(opcode);
        case 2u: return ExecuteOrDataRegister<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteOrDataRegister<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteOrDataRegister<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteOrDataRegister<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteOrDataRegister<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteOrDataRegister<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteOrDataRegister<&M68000::ReadFromLong<T>, T>(opcode);
                case 2u: return ExecuteOrDataRegister<&M68000::ReadFromPCDisplacement<T>, T>(opcode);
                case 3u: return ExecuteOrDataRegister<&M68000::ReadFromPCIndex<T>, T>(opcode);
                case 4u: return ExecuteOrDataRegister_RegisterImmediate<&M68000::ReadFromImmediate<T>, T>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteDivuDataRegister(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteDivuDataRegister<&M68000::ReadFromDataRegister<Word>>(opcode);
        case 2u: return ExecuteDivuDataRegister<&M68000::ReadFromAddressIndirect<Word>>(opcode);
        case 3u: return ExecuteDivuDataRegister<&M68000::ReadFromAddressIncrement<Word>>(opcode);
        case 4u: return ExecuteDivuDataRegister<&M68000::ReadFromAddressDecrement<Word>>(opcode);
        case 5u: return ExecuteDivuDataRegister<&M68000::ReadFromAddressDisplacement<Word>>(opcode);
        case 6u: return ExecuteDivuDataRegister<&M68000::ReadFromAddressIndex<Word>>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteDivuDataRegister<&M68000::ReadFromShort<Word>>(opcode);
                case 1u: return ExecuteDivuDataRegister<&M68000::ReadFromLong<Word>>(opcode);
                case 2u: return ExecuteDivuDataRegister<&M68000::ReadFromPCDisplacement<Word>>(opcode);
                case 3u: return ExecuteDivuDataRegister<&M68000::ReadFromPCIndex<Word>>(opcode);
                case 4u: return ExecuteDivuDataRegister<&M68000::ReadFromImmediate<Word>>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteOrEffectiveAddress(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u:
            if constexpr(std::is_same_v<T, Byte>) {
                return ExecuteSbcdDataRegister(opcode);
            } else {
                return ExecuteIllegal();
            }
        case 1u:
            if constexpr(std::is_same_v<T, Byte>) {
                return ExecuteSbcdAddressDecrement(opcode);
            } else {
                return ExecuteIllegal();
            }
        case 2u: return ExecuteOrEffectiveAddress<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteOrEffectiveAddress<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteOrEffectiveAddress<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteOrEffectiveAddress<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteOrEffectiveAddress<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteOrEffectiveAddress<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteOrEffectiveAddress<&M68000::ReadFromLong<T>, T>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteDivsDataRegister(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteDivsDataRegister<&M68000::ReadFromDataRegister<Word>>(opcode);
        case 2u: return ExecuteDivsDataRegister<&M68000::ReadFromAddressIndirect<Word>>(opcode);
        case 3u: return ExecuteDivsDataRegister<&M68000::ReadFromAddressIncrement<Word>>(opcode);
        case 4u: return ExecuteDivsDataRegister<&M68000::ReadFromAddressDecrement<Word>>(opcode);
        case 5u: return ExecuteDivsDataRegister<&M68000::ReadFromAddressDisplacement<Word>>(opcode);
        case 6u: return ExecuteDivsDataRegister<&M68000::ReadFromAddressIndex<Word>>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteDivsDataRegister<&M68000::ReadFromShort<Word>>(opcode);
                case 1u: return ExecuteDivsDataRegister<&M68000::ReadFromLong<Word>>(opcode);
                case 2u: return ExecuteDivsDataRegister<&M68000::ReadFromPCDisplacement<Word>>(opcode);
                case 3u: return ExecuteDivsDataRegister<&M68000::ReadFromPCIndex<Word>>(opcode);
                case 4u: return ExecuteDivsDataRegister<&M68000::ReadFromImmediate<Word>>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

// OR.{B|W|L} <ea>, Dx

template<auto Source, typename T>
auto M68000::ExecuteOrDataRegister_RegisterImmediate(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadDataRegisterLong(rx);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Or<T>(y, x);
    WriteDataRegister<T>(rx, result);
    if constexpr(std::is_same_v<T, Long>) {
        InternalCycle();
        InternalCycle();
    }
}

// OR.{B|W|L} <ea>, Dx

template<auto Source, typename T>
auto M68000::ExecuteOrDataRegister(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadDataRegisterLong(rx);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Or<T>(y, x);
    WriteDataRegister<T>(rx, result);
    if constexpr(std::is_same_v<T, Long>) {
        InternalCycle();
    }
}

// SBCD.B Dy, Dx

auto M68000::ExecuteSbcdDataRegister(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadDataRegisterLong(rx);
    const auto y = ReadDataRegisterLong(ry);
    const auto result = Sbcd<Byte>(y, x);
    WriteDataRegister<Byte>(rx, result);
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    InternalCycle();
}

// SBCD.B -(Ay), -(Ax)

auto M68000::ExecuteSbcdAddressDecrement(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y, x;
    if (!ReadFromAddressDecrement<Byte>(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ReadFromAddressDecrementWithoutInternalCycle<Byte>(rx, address, x)) [[unlikely]] {
        return;
    }
    const auto result = Sbcd<Byte>(y, x);
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    WriteMemory<Byte>(address, result);
}

// DIVU.W <ea>, Dx

constexpr auto DivuCycles(uint32_t dividend, uint32_t divisor, uint32_t quotient) -> uint32_t {
    // The zeroes in the quotient took 4 micro-cycles
    // The ones in the quotient took either 2 or 3 micro-cycles
    // We initially assume that the ones took 3 micro-cycles (one cycle less than the zeroes)
    // Then we do the division process and adjust for those that took 2 micro-cycles
    auto microCycles = 15u * 4u - PopCount16(quotient & ~1u);
    const auto alignedDivisor = divisor << 16u;
    for (auto i = 0u; i < 15u; ++i) {
        const auto previous = dividend;
        dividend <<= 1u;
        if (previous & 0x8000'0000u) {
            dividend -= alignedDivisor;
            microCycles -= 1u;
        } else if (dividend >= alignedDivisor) {
            dividend -= alignedDivisor;
        }
    }
    return 2 * microCycles;
}

template<auto Source>
auto M68000::ExecuteDivuDataRegister(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadDataRegisterLong(rx);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    const auto dividend = x;
    const auto divisor = static_cast<uint16_t>(y);
    InternalCycle();
    InternalCycle();
    if (divisor == 0u) {
        RaiseZeroDivideException();
        return;
    }
    const auto quotient = dividend / divisor;
    const auto remainder = dividend % divisor;
    InternalCycle();
    if (quotient >= 0x1'0000u) {
        WriteFlagsDivisionOverflow<Word>();
        ExecuteFinalPrefetchCycle();
        return;
    }
    ElapseCycles(DivuCycles(dividend, divisor, quotient));
    InternalCycle();
    InternalCycle();
    InternalCycle();
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = (remainder << 16u) + quotient;
    WriteFlagsLogical<Word>(quotient);
    WriteDataRegister<Long>(rx, result);
}

// OR.{B|W|L} Dx, <ea>

template<auto Source, typename T>
auto M68000::ExecuteOrEffectiveAddress(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadDataRegisterLong(rx);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Or<T>(x, y);
    WriteMemory<T>(address, result);
}

// DIVS.W <ea>, Dx

constexpr auto DivsCycles(uint32_t quotient) -> uint32_t {
    // The zeroes in the quotient took 4 micro-cycles
    // The ones in the quotient took 3 micro-cycles
    return 2 * (15u * 4u - PopCount16(quotient & ~1u));
}

template<auto Source>
auto M68000::ExecuteDivsDataRegister(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadDataRegisterLong(rx);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    const auto dividend = x;
    const auto divisor = static_cast<uint16_t>(y);
    InternalCycle();
    InternalCycle();
    if (divisor == 0u) {
        RaiseZeroDivideException();
        return;
    }
    const bool signDividend = dividend & 0x8000'0000u;
    const bool signDivisor = divisor & 0x8000u;
    const auto absoluteDividend = signDividend ? -dividend : dividend;
    const auto absoluteDivisor = static_cast<uint16_t>(signDivisor ? -divisor : divisor);
    const auto absoluteQuotient = absoluteDividend / absoluteDivisor;
    const auto absoluteRemainder = absoluteDividend % absoluteDivisor;
    ElapseCycles(signDividend ? 10u : 8u);
    if (absoluteQuotient >= 0x1'0000u) {
        WriteFlagsDivisionOverflow<Word>();
        ExecuteFinalPrefetchCycle();
        return;
    }
    ElapseCycles(DivsCycles(absoluteQuotient));
    ElapseCycles(10u);
    ElapseCycles(signDivisor ? 6u : signDividend ? 8u : 4u);
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto opposingSigns = signDividend ^ signDivisor;
    const auto quotient = static_cast<uint16_t>(opposingSigns ? -absoluteQuotient : absoluteQuotient);
    const auto remainder = static_cast<uint16_t>(signDividend ? -absoluteRemainder : absoluteRemainder);
    const auto positiveOverflow = !opposingSigns && (quotient & 0x8000u);
    const auto negativeOverflow = opposingSigns && (quotient > 0u && quotient < 0x8000u);
    if (positiveOverflow || negativeOverflow) {
        WriteFlagsDivisionOverflow<Word>();
        return;
    }
    const auto result = (remainder << 16u) + quotient;
    WriteFlagsLogical<Word>(quotient);
    WriteDataRegister<Long>(rx, result);
}
#pragma once

#include "M68000/M68000.h"
#include "M68000/M68000_Int.h"
#include "M68000/M68000_Sizes.h"

namespace rbrown::m68000 {

// Alu support functions

template<typename T>
auto M68000::WriteFlagX(uint32_t v) -> void {
    WriteFlagX(v << T::FLAG_SHIFT);
}

template<typename T>
auto M68000::WriteFlagN(uint32_t v) -> void {
    WriteFlagN(v << T::FLAG_SHIFT);
}

template<typename T>
auto M68000::WriteFlagZ(uint32_t v) -> void {
    WriteFlagZ(v << T::FLAG_SHIFT);
}

template<typename T>
auto M68000::WriteFlagV(uint32_t v) -> void {
    WriteFlagV(v << T::FLAG_SHIFT);
}

template<typename T>
auto M68000::WriteFlagC(uint32_t v) -> void {
    WriteFlagC(v << T::FLAG_SHIFT);
}

template<typename T>
auto M68000::WriteFlagsArithmetic(uint32_t result, uint32_t overflow, uint32_t carry) -> void {
    WriteFlagX<T>(carry);
    WriteFlagN<T>(result);
    WriteFlagZ<T>(result);
    WriteFlagV<T>(overflow);
    WriteFlagC<T>(carry);
}

template<typename T>
auto M68000::WriteFlagsCompare(uint32_t result, uint32_t overflow, uint32_t carry) -> void {
    WriteFlagN<T>(result);
    WriteFlagZ<T>(result);
    WriteFlagV<T>(overflow);
    WriteFlagC<T>(carry);
}

template<typename T>
auto M68000::WriteFlagsLogical(uint32_t result) -> void {
    WriteFlagN<T>(result);
    WriteFlagZ<T>(result);
    WriteFlagV<T>(0u);
    WriteFlagC<T>(0u);
}

template<typename T>
auto M68000::WriteFlagsMultiprecision(uint32_t result, uint32_t overflow, uint32_t carry) -> void {
    WriteFlagX<T>(carry);
    WriteFlagN<T>(result);
    if (ReadFlagZ()) {
        WriteFlagZ<T>(result);
    }
    WriteFlagV<T>(overflow);
    WriteFlagC<T>(carry);
}

template<typename T>
auto M68000::WriteFlagsDivisionOverflow() -> void {
    WriteFlagV<T>(T::MSB);
    WriteFlagC<T>(0u);
}

template<typename T>
auto M68000::WriteFlagsShiftRotate(uint32_t shift, uint32_t result, uint32_t overflow, uint32_t carry) -> void {
    if (shift) {
        WriteFlagX<T>(carry);
    }
    WriteFlagN<T>(result);
    WriteFlagZ<T>(result);
    WriteFlagV<T>(overflow);
    WriteFlagC<T>(carry);
}

template<typename T>
auto M68000::WriteFlagsRotate(uint32_t result, uint32_t carry) -> void {
    WriteFlagN<T>(result);
    WriteFlagZ<T>(result);
    WriteFlagV<T>(0u);
    WriteFlagC<T>(carry);
}

constexpr auto OverflowAdd(uint32_t src, uint32_t dst, uint32_t result) -> uint32_t {
    return ~(dst ^ src) & (dst ^ result);
}

constexpr auto OverflowSub(uint32_t src, uint32_t dst, uint32_t result) -> uint32_t {
    return (dst ^ src) & (dst ^ result);
}

constexpr auto Carry(uint32_t src, uint32_t dst, uint32_t result, uint32_t overflow) -> uint32_t {
    return (dst ^ src) ^ result ^ overflow;
}

constexpr auto CarryAdd(uint32_t src, uint32_t dst, uint32_t result) -> uint32_t {
    return Carry(src, dst, result, OverflowAdd(src, dst, result));
}

constexpr auto CarrySub(uint32_t src, uint32_t dst, uint32_t result) -> uint32_t {
    return Carry(src, dst, result, OverflowSub(src, dst, result));
}

constexpr auto BcdCorrection(uint32_t carry) -> uint32_t {
    constexpr auto mask = 0x88888888u;
    return (carry & mask) - ((carry & mask) >> 2u);
}

constexpr auto BcdCorrectionAdd(uint32_t sum, uint32_t carry) -> uint32_t {
    constexpr auto correction = 0x66666666u;
    return BcdCorrection(carry | CarryAdd(sum, correction, sum + correction));
}

template<typename T>
auto M68000::Add(uint32_t src, uint32_t dst) -> uint32_t {
    const auto result = dst + src;
    const auto overflow = OverflowAdd(src, dst, result);
    const auto carry = Carry(src, dst, result, overflow);
    WriteFlagsArithmetic<T>(result, overflow, carry);
    return result;
}

template<typename T>
auto M68000::Sub(uint32_t src, uint32_t dst) -> uint32_t {
    const auto result =  dst - src;
    const auto overflow = OverflowSub(src, dst, result);
    const auto carry = Carry(src, dst, result, overflow);
    WriteFlagsArithmetic<T>(result, overflow, carry);
    return result;
}

template<typename T>
auto M68000::Cmp(uint32_t src, uint32_t dst) -> void {
    const auto result = dst - src;
    const auto overflow = OverflowSub(src, dst, result);
    const auto carry = Carry(src, dst, result, overflow);
    WriteFlagsCompare<T>(result, overflow, carry);
}

template<typename T>
auto M68000::Or(uint32_t src, uint32_t dst) -> uint32_t {
    const auto result = src | dst;
    WriteFlagsLogical<T>(result);
    return result;
}

template<typename T>
auto M68000::And(uint32_t src, uint32_t dst) -> uint32_t {
    const auto result = dst & src;
    WriteFlagsLogical<T>(result);
    return result;
}

template<typename T>
auto M68000::Eor(uint32_t src, uint32_t dst) -> uint32_t {
    const auto result = dst ^ src;
    WriteFlagsLogical<T>(result);
    return result;
}

template<typename T>
auto M68000::Mulu(uint32_t src, uint32_t dst) -> uint32_t {
    ElapseCycles(34u + 2u * PopCount16(src));
    const auto result = Truncate16(dst) * Truncate16(src);
    WriteFlagsLogical<T>(result);
    return result;
}

template<typename T>
auto M68000::Muls(uint32_t src, uint32_t dst) -> uint32_t {
    ElapseCycles(34u + 2u * PopCount16(src ^ (src << 1u)));
    const auto result = SignExtend16(dst) * SignExtend16(src);
    WriteFlagsLogical<T>(result);
    return result;
}

template<typename T>
auto M68000::Adda(uint32_t src, uint32_t dst) -> uint32_t {
    return dst + T::SignExtend(src);
}

template<typename T>
auto M68000::Suba(uint32_t src, uint32_t dst) -> uint32_t {
    return dst - T::SignExtend(src);
}

template<typename T>
auto M68000::Cmpa(uint32_t src, uint32_t dst) -> void {
    const auto extended = T::SignExtend(src);
    const auto result = dst - extended;
    const auto overflow = OverflowSub(extended, dst, result);
    const auto carry = Carry(extended, dst, result, overflow);
    WriteFlagsCompare<Long>(result, overflow, carry);
}

template<typename T>
auto M68000::Addx(uint32_t src, uint32_t dst) -> uint32_t {
    const auto result = dst + src + ReadFlagX();
    const auto overflow = OverflowAdd(src, dst, result);
    const auto carry = Carry(src, dst, result, overflow);
    WriteFlagsMultiprecision<T>(result, overflow, carry);
    return result;
}

template<typename T>
auto M68000::Subx(uint32_t src, uint32_t dst) -> uint32_t {
    const auto result = dst - src - ReadFlagX();
    const auto overflow = OverflowSub(src, dst, result);
    const auto carry = Carry(src, dst, result, overflow);
    WriteFlagsMultiprecision<T>(result, overflow, carry);
    return result;
}

template<typename T>
auto M68000::Abcd(uint32_t src, uint32_t dst) -> uint32_t {
    // Compute Binary Sum, Binary Carry
    const auto bs = dst + src + ReadFlagX();
    const auto bc = CarryAdd(src, dst, bs);
    // Add the Decimal Correction factor to the Binary Sum
    const auto dc = BcdCorrectionAdd(bs, bc);
    const auto result = bs + dc;
    const auto overflow = OverflowAdd(bs, dc, result);
    const auto carry = Carry(bs, dc, overflow, result);
    WriteFlagsMultiprecision<T>(result, overflow, carry | bc);
    return result;
}

template<typename T>
auto M68000::Sbcd(uint32_t src, uint32_t dst) -> uint32_t {
    // Compute Binary Difference, Binary Carry
    const auto bd = dst - src - ReadFlagX();
    const auto bc = CarrySub(src, dst, bd);
    // Subtract the Decimal Correction from the Binary Difference
    const auto dc = BcdCorrection(bc);
    const auto result = bd - dc;
    const auto overflow = OverflowSub(dc, bd, result);
    const auto carry = Carry(dc, bd, result, overflow);
    WriteFlagsMultiprecision<T>(result, overflow, carry | bc);
    return result;
}

template<typename T>
auto M68000::Btst(uint32_t n, uint32_t dst) -> void {
    const auto bit = n & (T::BITS - 1u);
    const auto mask = 1u << bit;
    const auto test = dst & mask;
    WriteFlagZ<T>(test);
}

template<typename T>
auto M68000::Bchg(uint32_t n, uint32_t dst) -> uint32_t {
    const auto bit = n & (T::BITS - 1u);
    const auto mask = 1u << bit;
    const auto test = dst & mask;
    const auto result = dst ^ mask;
    WriteFlagZ<T>(test);
    return result;
}

template<typename T>
auto M68000::Bclr(uint32_t n, uint32_t dst) -> uint32_t {
    const auto bit = n & (T::BITS - 1u);
    const auto mask = 1u << bit;
    const auto test = dst & mask;
    const auto result = dst & ~mask;
    WriteFlagZ<T>(test);
    return result;
}

template<typename T>
auto M68000::Bset(uint32_t n, uint32_t dst) -> uint32_t {
    const auto bit = n & (T::BITS - 1u);
    const auto mask = 1u << bit;
    const auto test = dst & mask;
    const auto result = dst | mask;
    WriteFlagZ<T>(test);
    return result;
}

template<typename T>
auto M68000::Move(uint32_t dst) -> uint32_t {
    const auto result = dst;
    WriteFlagsLogical<T>(result);
    return result;
}

template<typename T>
auto M68000::Movea(uint32_t dst) -> uint32_t {
    return T::SignExtend(dst);
}

template<typename T>
auto M68000::Negx(uint32_t dst) -> uint32_t {
    const auto result = 0u - dst - ReadFlagX();
    const auto overflow = dst & result;
    const auto carry = dst ^ result ^ overflow;
    WriteFlagsMultiprecision<T>(result, overflow, carry);
    return result;
}

template<typename T>
auto M68000::Clr(uint32_t) -> uint32_t {
    WriteFlagsLogical<T>(0u);
    return 0u;
}

template<typename T>
auto M68000::Neg(uint32_t dst) -> uint32_t {
    const auto result = 0u - dst;
    const auto overflow = dst & result;
    const auto carry = dst ^ result ^ overflow;
    WriteFlagsArithmetic<T>(result, overflow, carry);
    return result;
}

template<typename T>
auto M68000::Not(uint32_t dst) -> uint32_t {
    const auto result = ~dst;
    WriteFlagsLogical<T>(result);
    return result;
}

template<typename T>
auto M68000::Nbcd(uint32_t dst) -> uint32_t {
    // Compute Binary Difference (bd), Binary Carry (bc) and Decimal Correction (dc)
    const auto bd = 0u - dst - ReadFlagX();
    const auto bc = dst ^ bd ^ (dst & bd);
    const auto dc = BcdCorrection(bc);
    // The result is formed by subtracting the Decimal Correction (dc)
    // from the Binary Difference (bd)
    const auto result = bd - dc;
    const auto overflow = OverflowSub(dc, bd, result);
    const auto carry = Carry(dc, bd, result, overflow);
    // Update flags (carry is or-ed with the binary carry)
    WriteFlagsMultiprecision<T>(result, overflow, carry | bc);
    return result;
}

template<typename T>
auto M68000::Tst(uint32_t dst) -> void {
    WriteFlagsLogical<T>(dst);
}

template<typename T>
auto M68000::Ext(uint32_t dst) -> uint32_t {
    if constexpr(std::is_same_v<T, Word>) {
        const auto result = SignExtend8(dst);
        WriteFlagsLogical<T>(result);
        return result;
    }
    if constexpr(std::is_same_v<T, Long>) {
        const auto result = SignExtend16(dst);
        WriteFlagsLogical<T>(result);
        return result;
    }
    return dst;
}

template<typename T>
auto M68000::Asr(uint32_t shift, uint32_t v) -> uint32_t {
    const auto result = AsrShift<T>(shift, v);
    const auto carry = AsrCarry<T>(shift, v);
    WriteFlagsShiftRotate<T>(shift, result, 0u, carry);
    return result;
}

template<typename T>
auto M68000::AsrShift(uint32_t shift, uint32_t v) -> uint32_t {
    const auto s = (shift < T::BITS - 1u) ? shift : T::BITS - 1u;
    const auto logical = (v & T::MASK) >> s;
    const auto msb = T::MSB >> s;
    return (logical ^ msb) - msb;
}

template<typename T>
auto M68000::AsrCarry(uint32_t shift, uint32_t v) -> uint32_t {
    return shift ? AsrShift<T>(shift - 1u, v) << (T::BITS - 1u) : 0u;
}

template<typename T>
auto M68000::Lsr(uint32_t shift, uint32_t v) -> uint32_t {
    const auto result = LsrShift<T>(shift, v);
    const auto carry = LsrCarry<T>(shift, v);
    WriteFlagsShiftRotate<T>(shift, result, 0u, carry);
    return result;
}

template<typename T>
auto M68000::LsrShift(uint32_t shift, uint32_t v) -> uint32_t {
    return (shift < T::BITS) ? (v & T::MASK) >> shift : 0u;
}

template<typename T>
auto M68000::LsrCarry(uint32_t shift, uint32_t v) -> uint32_t {
    return shift ? LsrShift<T>(shift - 1, v) << (T::BITS - 1u) : 0u;
}

template<typename T>
auto M68000::Roxr(uint32_t shift, uint32_t v) -> uint32_t {
    const auto x = ReadFlagX();
    const auto result = RoxrRotate<T>(shift, x, v);
    const auto carry = RoxrCarry<T>(shift, x, v);
    WriteFlagsShiftRotate<T>(shift, result, 0u, carry);
    return result;
}

template<typename T>
auto M68000::RoxrRotate(uint32_t shift, uint32_t x, uint32_t v) -> uint32_t {
    const auto s = shift % (T::BITS + 1u);
    if (s) {
        return ((v & T::MASK) >> 1u >> (s - 1u)) +
               (x << (T::BITS - s)) +
               (v << 1u << (T::BITS - s));
    }
    return v;
}

template<typename T>
auto M68000::RoxrCarry(uint32_t shift, uint32_t x, uint32_t v) -> uint32_t {
    return (shift ? RoxrRotate<T>(shift - 1u, x, v) : x) << (T::BITS - 1u);
}

template<typename T>
auto M68000::Ror(uint32_t shift, uint32_t v) -> uint32_t {
    const auto result = RorRotate<T>(shift, v);
    const auto carry = RorCarry<T>(shift, v);
    WriteFlagsRotate<T>(result, carry);
    return result;
}

template<typename T>
auto M68000::RorRotate(uint32_t shift, uint32_t v) -> uint32_t {
    const auto s = shift & (T::BITS - 1u);
    if (s) {
        return ((v & T::MASK) >> s) + (v << (T::BITS - s));
    }
    return v;
}

template<typename T>
auto M68000::RorCarry(uint32_t shift, uint32_t v) -> uint32_t {
    return shift ? RorRotate<T>(shift - 1u, v) << (T::BITS - 1u) : 0u;
}

template<typename T>
auto M68000::Asl(uint32_t shift, uint32_t v) -> uint32_t {
    const auto result = AslShift<T>(shift, v);
    const auto overflow = AslOverflow<T>(shift, v);
    const auto carry = AslCarry<T>(shift, v);
    WriteFlagsShiftRotate<T>(shift, result, overflow, carry);
    return result;
}

template<typename T>
auto M68000::AslShift(uint32_t shift, uint32_t v) -> uint32_t {
    return (shift < T::BITS) ? v << shift : 0u;
}

template<typename T>
auto M68000::AslOverflow(uint32_t shift, uint32_t v) -> uint32_t {
    if (shift) {
        const auto s = (shift < T::BITS) ? shift : T::BITS;
        const auto changes = v ^ (v << 1u);
        const auto usedChanges = (changes & T::MASK) >> (T::BITS - s);
        return usedChanges ? T::MSB : 0u;
    }
    return 0u;
}

template<typename T>
auto M68000::AslCarry(uint32_t shift, uint32_t v) -> uint32_t {
    return shift ? AslShift<T>(shift - 1u, v) : 0u;
}

template<typename T>
auto M68000::Lsl(uint32_t shift, uint32_t v) -> uint32_t {
    const auto result = LslShift<T>(shift, v);
    const auto carry = LslCarry<T>(shift, v);
    WriteFlagsShiftRotate<T>(shift, result, 0u, carry);
    return result;
}

template<typename T>
auto M68000::LslShift(uint32_t shift, uint32_t v) -> uint32_t {
    return (shift < T::BITS) ? v << shift : 0u;
}

template<typename T>
auto M68000::LslCarry(uint32_t shift, uint32_t v) -> uint32_t {
    return shift ? LslShift<T>(shift - 1, v) : 0u;
}

template<typename T>
auto M68000::RoxlRotate(uint32_t shift, uint32_t x, uint32_t v) -> uint32_t {
    const auto s = shift % (T::BITS + 1u);
    if (s) {
        return (v << 1u << (s - 1u)) +
               (x << (s - 1u)) +
               ((v & T::MASK) >> 1u >> (T::BITS - s));
    }
    return v;
}

template<typename T>
auto M68000::Roxl(uint32_t shift, uint32_t v) -> uint32_t {
    const auto x = ReadFlagX();
    const auto result = RoxlRotate<T>(shift, x, v);
    const auto carry = RoxlCarry<T>(shift, x, v);
    WriteFlagsShiftRotate<T>(shift, result, 0u, carry);
    return result;
}

template<typename T>
auto M68000::RoxlCarry(uint32_t shift, uint32_t x, uint32_t v) -> uint32_t {
    return shift ? RoxlRotate<T>(shift - 1u, x, v) : x << (T::BITS - 1u);
}

template<typename T>
auto M68000::Rol(uint32_t shift, uint32_t v) -> uint32_t {
    const auto result = RolRotate<T>(shift, v);
    const auto carry = RolCarry<T>(shift, v);
    WriteFlagsRotate<T>(result, carry);
    return result;
}

template<typename T>
auto M68000::RolRotate(uint32_t shift, uint32_t v) -> uint32_t {
    const auto s = shift & (T::BITS - 1u);
    if (s) {
        return (v << s) + ((v & T::MASK) >> (T::BITS - s));
    }
    return v;
}

template<typename T>
auto M68000::RolCarry(uint32_t shift, uint32_t v) -> uint32_t {
    return shift ? RolRotate<T>(shift - 1u, v) : 0u;
}

}
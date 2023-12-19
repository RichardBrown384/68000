#include "M68000/M68000.h"
#include "M68000/M68000_Operations.h"

using namespace rbrown::m68000;

auto M68000::Swap(uint32_t dst) -> uint32_t {
    const auto result = (dst << 16u) + Truncate16(dst >> 16u);
    WriteFlagsLogical<Long>(result);
    return result;
}

auto M68000::Tas(uint32_t dst) -> uint32_t {
    const auto truncated = Truncate8(dst);
    WriteFlagsLogical<Byte>(truncated);
    return 0x80u | truncated;
}

auto M68000::Scc(uint32_t condition, uint32_t) const -> uint32_t {
    return TestCondition(condition) ? 0xFFu : 0u;
}

auto M68000::Moveq(uint32_t dst) -> uint32_t {
    const auto result = SignExtend8(dst);
    WriteFlagsLogical<Long>(result);
    return result;
}
#pragma once

#include <cstdint>
#include <bit>

namespace rbrown::m68000 {

constexpr auto SignExtend8(uint32_t v) {
    return ((v & 0xFFu) ^ 0x80u) - 0x80u;
}

constexpr auto SignExtend16(uint32_t v) {
    return ((v & 0xFFFFu) ^ 0x8000u) - 0x8000u;
}

constexpr auto Truncate8(auto v) { return v & 0xFFu; }

constexpr auto Truncate16(auto v) { return v & 0xFFFFu; }

constexpr auto Reverse16(auto v) {
    v = ((v & 0xFF00u) >> 8u) + ((v & 0x00FFu) << 8u);
    v = ((v & 0xF0F0u) >> 4u) + ((v & 0x0F0Fu) << 4u);
    v = ((v & 0xCCCCu) >> 2u) + ((v & 0x3333u) << 2u);
    v = ((v & 0xAAAAu) >> 1u) + ((v & 0x5555u) << 1u);
    return v;
}

constexpr auto PopCount16(auto v) { return std::popcount(v & 0xFFFFu); }

}
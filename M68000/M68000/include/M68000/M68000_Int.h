#pragma once

#include <cstdint>
#include <bit>

namespace rbrown::m68000 {

constexpr auto Truncate8(auto v) { return v & 0xFFu; }

constexpr auto Truncate16(auto v) { return v & 0xFFFFu; }

constexpr auto SignExtend8(uint32_t v) {
    return (Truncate8(v) ^ 0x80u) - 0x80u;
}

constexpr auto SignExtend16(uint32_t v) {
    return (Truncate16(v) ^ 0x8000u) - 0x8000u;
}

constexpr auto Reverse16(auto v) {
    v = ((v & 0xFF00u) >> 8u) + ((v & 0x00FFu) << 8u);
    v = ((v & 0xF0F0u) >> 4u) + ((v & 0x0F0Fu) << 4u);
    v = ((v & 0xCCCCu) >> 2u) + ((v & 0x3333u) << 2u);
    v = ((v & 0xAAAAu) >> 1u) + ((v & 0x5555u) << 1u);
    return v;
}

constexpr auto Pack16(uint32_t b0, uint32_t b1) {
    return (Truncate8(b1) << 8u) + Truncate8(b0);
}

constexpr auto Pack32(uint32_t b0, uint32_t b1, uint32_t b2, uint32_t b3) {
    return (Truncate8(b3) << 24u) +
           (Truncate8(b2) << 16u) +
           (Truncate8(b1) << 8u) +
           Truncate8(b0);
}

constexpr auto PopCount16(auto v) { return std::popcount(v & 0xFFFFu); }

}
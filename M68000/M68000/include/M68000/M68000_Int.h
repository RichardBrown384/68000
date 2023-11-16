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

constexpr auto Truncate16(auto v) { return v & 0xFFFFu; }

constexpr auto PopCount16(auto v) { return std::popcount(v & 0xFFFFu); }

}
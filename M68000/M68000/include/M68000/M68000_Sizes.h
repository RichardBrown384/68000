#pragma once

#include "M68000/M68000_Int.h"

namespace rbrown::m68000 {

struct Byte {
    static constexpr auto BITS = 8u;
    static constexpr auto MASK = 0xFFu;
    static constexpr auto MSB = 0x80u;
    static constexpr auto FLAG_SHIFT = 32u - BITS;

    static constexpr auto AddressIncrement(uint32_t r) -> uint32_t {
        return (r == 7u) ? 2u : 1u;
    }

    static constexpr auto SignExtend(uint32_t v) -> uint32_t {
        return SignExtend8(v);
    }
};

struct Word {
    static constexpr auto BITS = 16u;
    static constexpr auto MASK = 0xFFFFu;
    static constexpr auto MSB = 0x8000u;
    static constexpr auto FLAG_SHIFT = 32u - BITS;
    static constexpr auto ADDRESS_INCREMENT = 2u;

    static constexpr auto AddressIncrement(uint32_t) -> uint32_t {
        return ADDRESS_INCREMENT;
    }

    static constexpr auto SignExtend(uint32_t v) -> uint32_t {
        return SignExtend16(v);
    }
};

struct Long {
    static constexpr auto BITS = 32u;
    static constexpr auto MASK = 0xFFFF'FFFFu;
    static constexpr auto MSB = 0x8000'0000u;
    static constexpr auto FLAG_SHIFT = 32u - BITS;
    static constexpr auto ADDRESS_INCREMENT = 4u;

    static constexpr auto AddressIncrement(uint32_t) -> uint32_t {
        return ADDRESS_INCREMENT;
    }

    static constexpr auto SignExtend(uint32_t v) -> uint32_t {
        return v;
    }
};

}
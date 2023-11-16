#include "M68000/Fixtures/M68000Test.h"

constexpr auto Encode(uint32_t op, uint32_t rx, uint32_t mx, uint32_t my, uint32_t ry) {
    return (op << 12u) + (rx << 9u) + (mx << 6u) + (my << 3u) + (ry);
}

constexpr auto VALUES = {

    Encode(0x0u, 0u, 0u, 1u, 4u), // ORI.B #imm, A4
    Encode(0x0u, 0u, 0u, 7u, 2u), // ORI.B #imm, <>
    Encode(0x0u, 0u, 0u, 7u, 3u), // ORI.B #imm, <>
    Encode(0x0u, 0u, 0u, 7u, 5u), // ORI.B #imm, <>
    Encode(0x0u, 0u, 0u, 7u, 6u), // ORI.B #imm, <>
    Encode(0x0u, 0u, 0u, 7u, 7u), // ORI.B #imm, <>

    Encode(0x0u, 0u, 1u, 1u, 4u), // ORI.W #imm, A4
    Encode(0x0u, 0u, 1u, 7u, 2u), // ORI.W #imm, <>
    Encode(0x0u, 0u, 1u, 7u, 3u), // ORI.W #imm, <>
    Encode(0x0u, 0u, 1u, 7u, 5u), // ORI.W #imm, <>
    Encode(0x0u, 0u, 1u, 7u, 6u), // ORI.W #imm, <>
    Encode(0x0u, 0u, 1u, 7u, 7u), // ORI.W #imm, <>

    Encode(0x0u, 0u, 2u, 1u, 4u), // ORI.L #imm, A4
    Encode(0x0u, 0u, 2u, 7u, 2u), // ORI.L #imm, <>
    Encode(0x0u, 0u, 2u, 7u, 3u), // ORI.L #imm, <>
    Encode(0x0u, 0u, 2u, 7u, 4u), // ORI.L #imm, <>
    Encode(0x0u, 0u, 2u, 7u, 5u), // ORI.L #imm, <>
    Encode(0x0u, 0u, 2u, 7u, 6u), // ORI.L #imm, <>
    Encode(0x0u, 0u, 2u, 7u, 7u), // ORI.L #imm, <>

    Encode(0x0u, 0u, 3u, 0u, 4u), // Undef #imm, D4
    Encode(0x0u, 0u, 3u, 1u, 4u), // Undef #imm, A4
    Encode(0x0u, 0u, 3u, 2u, 4u), // Undef #imm, (A4)
    Encode(0x0u, 0u, 3u, 3u, 4u), // Undef #imm, (A4)+
    Encode(0x0u, 0u, 3u, 4u, 4u), // Undef #imm, -(A4)
    Encode(0x0u, 0u, 3u, 5u, 4u), // Undef #imm, (d16, A4)
    Encode(0x0u, 0u, 3u, 5u, 4u), // Undef #imm, (d8, A4, Xn)
    Encode(0x0u, 0u, 3u, 7u, 0u), // Undef #imm, (XXX).W
    Encode(0x0u, 0u, 3u, 7u, 1u), // Undef #imm, (XXX).L
    Encode(0x0u, 0u, 3u, 7u, 2u), // Undef #imm, (d16, PC)
    Encode(0x0u, 0u, 3u, 7u, 3u), // Undef #imm, (d8, PC, Xn)
    Encode(0x0u, 0u, 3u, 7u, 4u), // Undef #imm, #imm
    Encode(0x0u, 0u, 3u, 7u, 5u), // Undef #imm, <>
    Encode(0x0u, 0u, 3u, 7u, 6u), // Undef #imm, <>
    Encode(0x0u, 0u, 3u, 7u, 7u), // Undef #imm, <>

    Encode(0x0u, 0u, 4u, 7u, 5u), // BTST D0, <>
    Encode(0x0u, 0u, 4u, 7u, 6u), // BTST D0, <>
    Encode(0x0u, 0u, 4u, 7u, 7u), // BTST D0, <>

    Encode(0x0u, 0u, 5u, 7u, 2u), // BCHG D0, <>
    Encode(0x0u, 0u, 5u, 7u, 3u), // BCHG D0, <>
    Encode(0x0u, 0u, 5u, 7u, 4u), // BCHG D0, <>
    Encode(0x0u, 0u, 5u, 7u, 5u), // BCHG D0, <>
    Encode(0x0u, 0u, 5u, 7u, 6u), // BCHG D0, <>
    Encode(0x0u, 0u, 5u, 7u, 7u), // BCHG D0, <>

    Encode(0x0u, 0u, 6u, 7u, 2u), // BCLR D0, <>
    Encode(0x0u, 0u, 6u, 7u, 3u), // BCLR D0, <>
    Encode(0x0u, 0u, 6u, 7u, 4u), // BCLR D0, <>
    Encode(0x0u, 0u, 6u, 7u, 5u), // BCLR D0, <>
    Encode(0x0u, 0u, 6u, 7u, 6u), // BCLR D0, <>
    Encode(0x0u, 0u, 6u, 7u, 7u), // BCLR D0, <>

    Encode(0x0u, 0u, 7u, 7u, 2u), // BSET D0, <>
    Encode(0x0u, 0u, 7u, 7u, 3u), // BSET D0, <>
    Encode(0x0u, 0u, 7u, 7u, 4u), // BSET D0, <>
    Encode(0x0u, 0u, 7u, 7u, 5u), // BSET D0, <>
    Encode(0x0u, 0u, 7u, 7u, 6u), // BSET D0, <>
    Encode(0x0u, 0u, 7u, 7u, 7u), // BSET D0, <>

    Encode(0x0u, 1u, 0u, 1u, 4u), // ANDI.B #imm, A4
    Encode(0x0u, 1u, 0u, 7u, 2u), // ANDI.B #imm, <>
    Encode(0x0u, 1u, 0u, 7u, 3u), // ANDI.B #imm, <>
    Encode(0x0u, 1u, 0u, 7u, 5u), // ANDI.B #imm, <>
    Encode(0x0u, 1u, 0u, 7u, 6u), // ANDI.B #imm, <>
    Encode(0x0u, 1u, 0u, 7u, 7u), // ANDI.B #imm, <>

    Encode(0x0u, 1u, 1u, 1u, 4u), // ANDI.W #imm, A4
    Encode(0x0u, 1u, 1u, 7u, 2u), // ANDI.W #imm, <>
    Encode(0x0u, 1u, 1u, 7u, 3u), // ANDI.W #imm, <>
    Encode(0x0u, 1u, 1u, 7u, 5u), // ANDI.W #imm, <>
    Encode(0x0u, 1u, 1u, 7u, 6u), // ANDI.W #imm, <>
    Encode(0x0u, 1u, 1u, 7u, 7u), // ANDI.W #imm, <>

    Encode(0x0u, 1u, 2u, 1u, 4u), // ANDI.L #imm, A4
    Encode(0x0u, 1u, 2u, 7u, 2u), // ANDI.L #imm, <>
    Encode(0x0u, 1u, 2u, 7u, 3u), // ANDI.L #imm, <>
    Encode(0x0u, 1u, 2u, 7u, 4u), // ANDI.L #imm, <>
    Encode(0x0u, 1u, 2u, 7u, 5u), // ANDI.L #imm, <>
    Encode(0x0u, 1u, 2u, 7u, 6u), // ANDI.L #imm, <>
    Encode(0x0u, 1u, 2u, 7u, 7u), // ANDI.L #imm, <>

    Encode(0x0u, 1u, 3u, 0u, 4u), // Undef #imm, D4
    Encode(0x0u, 1u, 3u, 1u, 4u), // Undef #imm, A4
    Encode(0x0u, 1u, 3u, 2u, 4u), // Undef #imm, (A4)
    Encode(0x0u, 1u, 3u, 3u, 4u), // Undef #imm, (A4)+
    Encode(0x0u, 1u, 3u, 4u, 4u), // Undef #imm, -(A4)
    Encode(0x0u, 1u, 3u, 5u, 4u), // Undef #imm, (d16, A4)
    Encode(0x0u, 1u, 3u, 5u, 4u), // Undef #imm, (d8, A4, Xn)
    Encode(0x0u, 1u, 3u, 7u, 0u), // Undef #imm, (XXX).W
    Encode(0x0u, 1u, 3u, 7u, 1u), // Undef #imm, (XXX).L
    Encode(0x0u, 1u, 3u, 7u, 2u), // Undef #imm, (d16, PC)
    Encode(0x0u, 1u, 3u, 7u, 3u), // Undef #imm, (d8, PC, Xn)
    Encode(0x0u, 1u, 3u, 7u, 4u), // Undef #imm, #imm
    Encode(0x0u, 1u, 3u, 7u, 5u), // Undef #imm, <>
    Encode(0x0u, 1u, 3u, 7u, 6u), // Undef #imm, <>
    Encode(0x0u, 1u, 3u, 7u, 7u), // Undef #imm, <>

    Encode(0x0u, 2u, 0u, 1u, 4u), // SUBI.B #imm, A4
    Encode(0x0u, 2u, 0u, 7u, 2u), // SUBI.B #imm, <>
    Encode(0x0u, 2u, 0u, 7u, 3u), // SUBI.B #imm, <>
    Encode(0x0u, 2u, 0u, 7u, 4u), // SUBI.B #imm, <>
    Encode(0x0u, 2u, 0u, 7u, 5u), // SUBI.B #imm, <>
    Encode(0x0u, 2u, 0u, 7u, 6u), // SUBI.B #imm, <>
    Encode(0x0u, 2u, 0u, 7u, 7u), // SUBI.B #imm, <>

    Encode(0x0u, 2u, 1u, 1u, 4u), // SUBI.W #imm, A4
    Encode(0x0u, 2u, 1u, 7u, 2u), // SUBI.W #imm, <>
    Encode(0x0u, 2u, 1u, 7u, 3u), // SUBI.W #imm, <>
    Encode(0x0u, 2u, 1u, 7u, 4u), // SUBI.W #imm, <>
    Encode(0x0u, 2u, 1u, 7u, 5u), // SUBI.W #imm, <>
    Encode(0x0u, 2u, 1u, 7u, 6u), // SUBI.W #imm, <>
    Encode(0x0u, 2u, 1u, 7u, 7u), // SUBI.W #imm, <>

    Encode(0x0u, 2u, 2u, 1u, 4u), // SUBI.L #imm, A4
    Encode(0x0u, 2u, 2u, 7u, 2u), // SUBI.L #imm, <>
    Encode(0x0u, 2u, 2u, 7u, 3u), // SUBI.L #imm, <>
    Encode(0x0u, 2u, 2u, 7u, 4u), // SUBI.L #imm, <>
    Encode(0x0u, 2u, 2u, 7u, 5u), // SUBI.L #imm, <>
    Encode(0x0u, 2u, 2u, 7u, 6u), // SUBI.L #imm, <>
    Encode(0x0u, 2u, 2u, 7u, 7u), // SUBI.L #imm, <>

    Encode(0x0u, 2u, 3u, 0u, 4u), // Undef #imm, D4
    Encode(0x0u, 2u, 3u, 1u, 4u), // Undef #imm, A4
    Encode(0x0u, 2u, 3u, 2u, 4u), // Undef #imm, (A4)
    Encode(0x0u, 2u, 3u, 3u, 4u), // Undef #imm, (A4)+
    Encode(0x0u, 2u, 3u, 4u, 4u), // Undef #imm, -(A4)
    Encode(0x0u, 2u, 3u, 5u, 4u), // Undef #imm, (d16, A4)
    Encode(0x0u, 2u, 3u, 5u, 4u), // Undef #imm, (d8, A4, Xn)
    Encode(0x0u, 2u, 3u, 7u, 0u), // Undef #imm, (XXX).W
    Encode(0x0u, 2u, 3u, 7u, 1u), // Undef #imm, (XXX).L
    Encode(0x0u, 2u, 3u, 7u, 2u), // Undef #imm, (d16, PC)
    Encode(0x0u, 2u, 3u, 7u, 3u), // Undef #imm, (d8, PC, Xn)
    Encode(0x0u, 2u, 3u, 7u, 4u), // Undef #imm, #imm
    Encode(0x0u, 2u, 3u, 7u, 5u), // Undef #imm, <>
    Encode(0x0u, 2u, 3u, 7u, 6u), // Undef #imm, <>
    Encode(0x0u, 2u, 3u, 7u, 7u), // Undef #imm, <>

    Encode(0x0u, 3u, 0u, 1u, 4u), // ADDI.B #imm, A4
    Encode(0x0u, 3u, 0u, 7u, 2u), // ADDI.B #imm, <>
    Encode(0x0u, 3u, 0u, 7u, 3u), // ADDI.B #imm, <>
    Encode(0x0u, 3u, 0u, 7u, 4u), // ADDI.B #imm, <>
    Encode(0x0u, 3u, 0u, 7u, 5u), // ADDI.B #imm, <>
    Encode(0x0u, 3u, 0u, 7u, 6u), // ADDI.B #imm, <>
    Encode(0x0u, 3u, 0u, 7u, 7u), // ADDI.B #imm, <>

    Encode(0x0u, 3u, 1u, 1u, 4u), // ADDI.W #imm, A4
    Encode(0x0u, 3u, 1u, 7u, 2u), // ADDI.W #imm, <>
    Encode(0x0u, 3u, 1u, 7u, 3u), // ADDI.W #imm, <>
    Encode(0x0u, 3u, 1u, 7u, 4u), // ADDI.W #imm, <>
    Encode(0x0u, 3u, 1u, 7u, 5u), // ADDI.W #imm, <>
    Encode(0x0u, 3u, 1u, 7u, 6u), // ADDI.W #imm, <>
    Encode(0x0u, 3u, 1u, 7u, 7u), // ADDI.W #imm, <>

    Encode(0x0u, 3u, 2u, 1u, 4u), // ADDI.L #imm, A4
    Encode(0x0u, 3u, 2u, 7u, 2u), // ADDI.L #imm, <>
    Encode(0x0u, 3u, 2u, 7u, 3u), // ADDI.L #imm, <>
    Encode(0x0u, 3u, 2u, 7u, 4u), // ADDI.L #imm, <>
    Encode(0x0u, 3u, 2u, 7u, 5u), // ADDI.L #imm, <>
    Encode(0x0u, 3u, 2u, 7u, 6u), // ADDI.L #imm, <>
    Encode(0x0u, 3u, 2u, 7u, 7u), // ADDI.L #imm, <>

    Encode(0x0u, 3u, 3u, 0u, 4u), // Undef #imm, D4
    Encode(0x0u, 3u, 3u, 1u, 4u), // Undef #imm, A4
    Encode(0x0u, 3u, 3u, 2u, 4u), // Undef #imm, (A4)
    Encode(0x0u, 3u, 3u, 3u, 4u), // Undef #imm, (A4)+
    Encode(0x0u, 3u, 3u, 4u, 4u), // Undef #imm, -(A4)
    Encode(0x0u, 3u, 3u, 5u, 4u), // Undef #imm, (d16, A4)
    Encode(0x0u, 3u, 3u, 5u, 4u), // Undef #imm, (d8, A4, Xn)
    Encode(0x0u, 3u, 3u, 7u, 0u), // Undef #imm, (XXX).W
    Encode(0x0u, 3u, 3u, 7u, 1u), // Undef #imm, (XXX).L
    Encode(0x0u, 3u, 3u, 7u, 2u), // Undef #imm, (d16, PC)
    Encode(0x0u, 3u, 3u, 7u, 3u), // Undef #imm, (d8, PC, Xn)
    Encode(0x0u, 3u, 3u, 7u, 4u), // Undef #imm, #imm
    Encode(0x0u, 3u, 3u, 7u, 5u), // Undef #imm, <>
    Encode(0x0u, 3u, 3u, 7u, 6u), // Undef #imm, <>
    Encode(0x0u, 3u, 3u, 7u, 7u), // Undef #imm, <>

    Encode(0x0u, 4u, 0u, 1u, 4u), // BTST #imm, A4
    Encode(0x0u, 4u, 0u, 7u, 4u), // BTST #imm, <>
    Encode(0x0u, 4u, 0u, 7u, 5u), // BTST #imm, <>
    Encode(0x0u, 4u, 0u, 7u, 6u), // BTST #imm, <>
    Encode(0x0u, 4u, 0u, 7u, 7u), // BTST #imm, <>

    Encode(0x0u, 4u, 1u, 1u, 4u), // BCHG #imm, A4
    Encode(0x0u, 4u, 1u, 7u, 2u), // BCHG #imm, <>
    Encode(0x0u, 4u, 1u, 7u, 3u), // BCHG #imm, <>
    Encode(0x0u, 4u, 1u, 7u, 4u), // BCHG #imm, <>
    Encode(0x0u, 4u, 1u, 7u, 5u), // BCHG #imm, <>
    Encode(0x0u, 4u, 1u, 7u, 6u), // BCHG #imm, <>
    Encode(0x0u, 4u, 1u, 7u, 7u), // BCHG #imm, <>

    Encode(0x0u, 4u, 2u, 1u, 4u), // BCLR #imm, A4
    Encode(0x0u, 4u, 2u, 7u, 2u), // BCLR #imm, <>
    Encode(0x0u, 4u, 2u, 7u, 3u), // BCLR #imm, <>
    Encode(0x0u, 4u, 2u, 7u, 4u), // BCLR #imm, <>
    Encode(0x0u, 4u, 2u, 7u, 5u), // BCLR #imm, <>
    Encode(0x0u, 4u, 2u, 7u, 6u), // BCLR #imm, <>
    Encode(0x0u, 4u, 2u, 7u, 7u), // BCLR #imm, <>

    Encode(0x0u, 4u, 3u, 1u, 4u), // BSET #imm, A4
    Encode(0x0u, 4u, 3u, 7u, 2u), // BSET #imm, <>
    Encode(0x0u, 4u, 3u, 7u, 3u), // BSET #imm, <>
    Encode(0x0u, 4u, 3u, 7u, 4u), // BSET #imm, <>
    Encode(0x0u, 4u, 3u, 7u, 5u), // BSET #imm, <>
    Encode(0x0u, 4u, 3u, 7u, 6u), // BSET #imm, <>
    Encode(0x0u, 4u, 3u, 7u, 7u), // BSET #imm, <>

    Encode(0x0u, 5u, 0u, 1u, 4u), // EORI.B #imm, A4
    Encode(0x0u, 5u, 0u, 7u, 2u), // EORI.B #imm, <>
    Encode(0x0u, 5u, 0u, 7u, 3u), // EORI.B #imm, <>
    Encode(0x0u, 5u, 0u, 7u, 5u), // EORI.B #imm, <>
    Encode(0x0u, 5u, 0u, 7u, 6u), // EORI.B #imm, <>
    Encode(0x0u, 5u, 0u, 7u, 7u), // EORI.B #imm, <>

    Encode(0x0u, 5u, 1u, 1u, 4u), // EORI.W #imm, A4
    Encode(0x0u, 5u, 1u, 7u, 2u), // EORI.W #imm, <>
    Encode(0x0u, 5u, 1u, 7u, 3u), // EORI.W #imm, <>
    Encode(0x0u, 5u, 1u, 7u, 5u), // EORI.W #imm, <>
    Encode(0x0u, 5u, 1u, 7u, 6u), // EORI.W #imm, <>
    Encode(0x0u, 5u, 1u, 7u, 7u), // EORI.W #imm, <>

    Encode(0x0u, 5u, 2u, 1u, 4u), // EORI.L #imm, A4
    Encode(0x0u, 5u, 2u, 7u, 2u), // EORI.L #imm, <>
    Encode(0x0u, 5u, 2u, 7u, 3u), // EORI.L #imm, <>
    Encode(0x0u, 5u, 2u, 7u, 4u), // EORI.L #imm, <>
    Encode(0x0u, 5u, 2u, 7u, 5u), // EORI.L #imm, <>
    Encode(0x0u, 5u, 2u, 7u, 6u), // EORI.L #imm, <>
    Encode(0x0u, 5u, 2u, 7u, 7u), // EORI.L #imm, <>

    Encode(0x0u, 5u, 3u, 0u, 4u), // Undef #imm, D4
    Encode(0x0u, 5u, 3u, 1u, 4u), // Undef #imm, A4
    Encode(0x0u, 5u, 3u, 2u, 4u), // Undef #imm, (A4)
    Encode(0x0u, 5u, 3u, 3u, 4u), // Undef #imm, (A4)+
    Encode(0x0u, 5u, 3u, 4u, 4u), // Undef #imm, -(A4)
    Encode(0x0u, 5u, 3u, 5u, 4u), // Undef #imm, (d16, A4)
    Encode(0x0u, 5u, 3u, 5u, 4u), // Undef #imm, (d8, A4, Xn)
    Encode(0x0u, 5u, 3u, 7u, 0u), // Undef #imm, (XXX).W
    Encode(0x0u, 5u, 3u, 7u, 1u), // Undef #imm, (XXX).L
    Encode(0x0u, 5u, 3u, 7u, 2u), // Undef #imm, (d16, PC)
    Encode(0x0u, 5u, 3u, 7u, 3u), // Undef #imm, (d8, PC, Xn)
    Encode(0x0u, 5u, 3u, 7u, 4u), // Undef #imm, #imm
    Encode(0x0u, 5u, 3u, 7u, 5u), // Undef #imm, <>
    Encode(0x0u, 5u, 3u, 7u, 6u), // Undef #imm, <>
    Encode(0x0u, 5u, 3u, 7u, 7u), // Undef #imm, <>

    Encode(0x0u, 6u, 0u, 1u, 4u), // CMPI.B #imm, A4
    Encode(0x0u, 6u, 0u, 7u, 2u), // CMPI.B #imm, <>
    Encode(0x0u, 6u, 0u, 7u, 3u), // CMPI.B #imm, <>
    Encode(0x0u, 6u, 0u, 7u, 4u), // CMPI.B #imm, <>
    Encode(0x0u, 6u, 0u, 7u, 5u), // CMPI.B #imm, <>
    Encode(0x0u, 6u, 0u, 7u, 6u), // CMPI.B #imm, <>
    Encode(0x0u, 6u, 0u, 7u, 7u), // CMPI.B #imm, <>

    Encode(0x0u, 6u, 1u, 1u, 4u), // CMPI.W #imm, A4
    Encode(0x0u, 6u, 1u, 7u, 2u), // CMPI.W #imm, <>
    Encode(0x0u, 6u, 1u, 7u, 3u), // CMPI.W #imm, <>
    Encode(0x0u, 6u, 1u, 7u, 4u), // CMPI.W #imm, <>
    Encode(0x0u, 6u, 1u, 7u, 5u), // CMPI.W #imm, <>
    Encode(0x0u, 6u, 1u, 7u, 6u), // CMPI.W #imm, <>
    Encode(0x0u, 6u, 1u, 7u, 7u), // CMPI.W #imm, <>

    Encode(0x0u, 6u, 2u, 1u, 4u), // CMPI.L #imm, A4
    Encode(0x0u, 6u, 2u, 7u, 2u), // CMPI.L #imm, <>
    Encode(0x0u, 6u, 2u, 7u, 3u), // CMPI.L #imm, <>
    Encode(0x0u, 6u, 2u, 7u, 4u), // CMPI.L #imm, <>
    Encode(0x0u, 6u, 2u, 7u, 5u), // CMPI.L #imm, <>
    Encode(0x0u, 6u, 2u, 7u, 6u), // CMPI.L #imm, <>
    Encode(0x0u, 6u, 2u, 7u, 7u), // CMPI.L #imm, <>

    Encode(0x0u, 6u, 3u, 0u, 4u), // Undef #imm, D4
    Encode(0x0u, 6u, 3u, 1u, 4u), // Undef #imm, A4
    Encode(0x0u, 6u, 3u, 2u, 4u), // Undef #imm, (A4)
    Encode(0x0u, 6u, 3u, 3u, 4u), // Undef #imm, (A4)+
    Encode(0x0u, 6u, 3u, 4u, 4u), // Undef #imm, -(A4)
    Encode(0x0u, 6u, 3u, 5u, 4u), // Undef #imm, (d16, A4)
    Encode(0x0u, 6u, 3u, 5u, 4u), // Undef #imm, (d8, A4, Xn)
    Encode(0x0u, 6u, 3u, 7u, 0u), // Undef #imm, (XXX).W
    Encode(0x0u, 6u, 3u, 7u, 1u), // Undef #imm, (XXX).L
    Encode(0x0u, 6u, 3u, 7u, 2u), // Undef #imm, (d16, PC)
    Encode(0x0u, 6u, 3u, 7u, 3u), // Undef #imm, (d8, PC, Xn)
    Encode(0x0u, 6u, 3u, 7u, 4u), // Undef #imm, #imm
    Encode(0x0u, 6u, 3u, 7u, 5u), // Undef #imm, <>
    Encode(0x0u, 6u, 3u, 7u, 6u), // Undef #imm, <>
    Encode(0x0u, 6u, 3u, 7u, 7u), // Undef #imm, <>

    Encode(0x0u, 7u, 0u, 0u, 4u), // Undef #imm, D4
    Encode(0x0u, 7u, 0u, 1u, 4u), // Undef #imm, A4
    Encode(0x0u, 7u, 0u, 2u, 4u), // Undef #imm, (A4)
    Encode(0x0u, 7u, 0u, 3u, 4u), // Undef #imm, (A4)+
    Encode(0x0u, 7u, 0u, 4u, 4u), // Undef #imm, -(A4)
    Encode(0x0u, 7u, 0u, 5u, 4u), // Undef #imm, (d16, A4)
    Encode(0x0u, 7u, 0u, 5u, 4u), // Undef #imm, (d8, A4, Xn)
    Encode(0x0u, 7u, 0u, 7u, 0u), // Undef #imm, (XXX).W
    Encode(0x0u, 7u, 0u, 7u, 1u), // Undef #imm, (XXX).L
    Encode(0x0u, 7u, 0u, 7u, 2u), // Undef #imm, (d16, PC)
    Encode(0x0u, 7u, 0u, 7u, 3u), // Undef #imm, (d8, PC, Xn)
    Encode(0x0u, 7u, 0u, 7u, 4u), // Undef #imm, #imm
    Encode(0x0u, 7u, 0u, 7u, 5u), // Undef #imm, <>
    Encode(0x0u, 7u, 0u, 7u, 6u), // Undef #imm, <>
    Encode(0x0u, 7u, 0u, 7u, 7u), // Undef #imm, <>

    Encode(0x0u, 7u, 2u, 0u, 4u), // Undef #imm, D4
    Encode(0x0u, 7u, 2u, 1u, 4u), // Undef #imm, A4
    Encode(0x0u, 7u, 2u, 2u, 4u), // Undef #imm, (A4)
    Encode(0x0u, 7u, 2u, 3u, 4u), // Undef #imm, (A4)+
    Encode(0x0u, 7u, 2u, 4u, 4u), // Undef #imm, -(A4)
    Encode(0x0u, 7u, 2u, 5u, 4u), // Undef #imm, (d16, A4)
    Encode(0x0u, 7u, 2u, 5u, 4u), // Undef #imm, (d8, A4, Xn)
    Encode(0x0u, 7u, 2u, 7u, 0u), // Undef #imm, (XXX).W
    Encode(0x0u, 7u, 2u, 7u, 1u), // Undef #imm, (XXX).L
    Encode(0x0u, 7u, 2u, 7u, 2u), // Undef #imm, (d16, PC)
    Encode(0x0u, 7u, 2u, 7u, 3u), // Undef #imm, (d8, PC, Xn)
    Encode(0x0u, 7u, 2u, 7u, 4u), // Undef #imm, #imm
    Encode(0x0u, 7u, 2u, 7u, 5u), // Undef #imm, <>
    Encode(0x0u, 7u, 2u, 7u, 6u), // Undef #imm, <>
    Encode(0x0u, 7u, 2u, 7u, 7u), // Undef #imm, <>

    Encode(0x0u, 7u, 3u, 0u, 4u), // Undef #imm, D4
    Encode(0x0u, 7u, 3u, 1u, 4u), // Undef #imm, A4
    Encode(0x0u, 7u, 3u, 2u, 4u), // Undef #imm, (A4)
    Encode(0x0u, 7u, 3u, 3u, 4u), // Undef #imm, (A4)+
    Encode(0x0u, 7u, 3u, 4u, 4u), // Undef #imm, -(A4)
    Encode(0x0u, 7u, 3u, 5u, 4u), // Undef #imm, (d16, A4)
    Encode(0x0u, 7u, 3u, 5u, 4u), // Undef #imm, (d8, A4, Xn)
    Encode(0x0u, 7u, 3u, 7u, 0u), // Undef #imm, (XXX).W
    Encode(0x0u, 7u, 3u, 7u, 1u), // Undef #imm, (XXX).L
    Encode(0x0u, 7u, 3u, 7u, 2u), // Undef #imm, (d16, PC)
    Encode(0x0u, 7u, 3u, 7u, 3u), // Undef #imm, (d8, PC, Xn)
    Encode(0x0u, 7u, 3u, 7u, 4u), // Undef #imm, #imm
    Encode(0x0u, 7u, 3u, 7u, 5u), // Undef #imm, <>
    Encode(0x0u, 7u, 3u, 7u, 6u), // Undef #imm, <>
    Encode(0x0u, 7u, 3u, 7u, 7u), // Undef #imm, <>

    Encode(0x0u, 7u, 3u, 0u, 4u), // Undef #imm, D4
    Encode(0x0u, 7u, 3u, 1u, 4u), // Undef #imm, A4
    Encode(0x0u, 7u, 3u, 2u, 4u), // Undef #imm, (A4)
    Encode(0x0u, 7u, 3u, 3u, 4u), // Undef #imm, (A4)+
    Encode(0x0u, 7u, 3u, 4u, 4u), // Undef #imm, -(A4)
    Encode(0x0u, 7u, 3u, 5u, 4u), // Undef #imm, (d16, A4)
    Encode(0x0u, 7u, 3u, 5u, 4u), // Undef #imm, (d8, A4, Xn)
    Encode(0x0u, 7u, 3u, 7u, 0u), // Undef #imm, (XXX).W
    Encode(0x0u, 7u, 3u, 7u, 1u), // Undef #imm, (XXX).L
    Encode(0x0u, 7u, 3u, 7u, 2u), // Undef #imm, (d16, PC)
    Encode(0x0u, 7u, 3u, 7u, 3u), // Undef #imm, (d8, PC, Xn)
    Encode(0x0u, 7u, 3u, 7u, 4u), // Undef #imm, #imm
    Encode(0x0u, 7u, 3u, 7u, 5u), // Undef #imm, <>
    Encode(0x0u, 7u, 3u, 7u, 6u), // Undef #imm, <>
    Encode(0x0u, 7u, 3u, 7u, 7u), // Undef #imm, <>


};

class Line0IllegalInstructionTest: public M68000Test, public ::testing::WithParamInterface<uint32_t> {};

TEST_P(Line0IllegalInstructionTest, IllegalInstructionPattern) {
    const auto illegal = GetParam();
    Given({
        "SR is 0,0,XC",
        "A7 is 0x00FF0000",
        "SSP is 0x01000000",
        "(0x10).L is 0x00ADBCBC",
        "(0x00FFFFFA).W is 0xCDCD",
        "(0x00FFFFFC).L is 0xCDCDCDCD",
    });
    When({
        illegal
    });
    Then({
        "SR is S,0,XC",
        "A7 is 0x00FFFFFA",
        "USP is 0x00FF0000",
        "PC is 0x00ADBCBC",
        "(0x10).L is 0x00ADBCBC",
        "(0x00FFFFFA).W is 0x0011",
        "(0x00FFFFFC).L is 0x00001002",
        "CYCLES is 34"
    });
}

INSTANTIATE_TEST_SUITE_P(
   IllegalLine0InstructionPatterns,
   Line0IllegalInstructionTest,
   ::testing::ValuesIn(VALUES)
);

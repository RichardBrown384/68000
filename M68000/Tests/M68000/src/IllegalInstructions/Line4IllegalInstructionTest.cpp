#include "M68000/Fixtures/M68000Test.h"

constexpr auto Encode(uint32_t op, uint32_t rx, uint32_t mx, uint32_t my, uint32_t ry) {
    return (op << 12u) + (rx << 9u) + (mx << 6u) + (my << 3u) + (ry);
}

constexpr auto VALUES = {

    Encode(0x4u, 0u, 0u, 1u, 4u), // NEXG.B A4
    Encode(0x4u, 0u, 0u, 7u, 2u), // NEXG.B <>
    Encode(0x4u, 0u, 0u, 7u, 3u), // NEXG.B <>
    Encode(0x4u, 0u, 0u, 7u, 4u), // NEXG.B <>
    Encode(0x4u, 0u, 0u, 7u, 5u), // NEXG.B <>
    Encode(0x4u, 0u, 0u, 7u, 6u), // NEXG.B <>
    Encode(0x4u, 0u, 0u, 7u, 7u), // NEXG.B <>

    Encode(0x4u, 0u, 1u, 1u, 4u), // NEXG.W A4
    Encode(0x4u, 0u, 1u, 7u, 2u), // NEXG.W <>
    Encode(0x4u, 0u, 1u, 7u, 3u), // NEXG.W <>
    Encode(0x4u, 0u, 1u, 7u, 4u), // NEXG.W <>
    Encode(0x4u, 0u, 1u, 7u, 5u), // NEXG.W <>
    Encode(0x4u, 0u, 1u, 7u, 6u), // NEXG.W <>
    Encode(0x4u, 0u, 1u, 7u, 7u), // NEXG.W <>

    Encode(0x4u, 0u, 2u, 1u, 4u), // NEXG.L A4
    Encode(0x4u, 0u, 2u, 7u, 2u), // NEXG.L <>
    Encode(0x4u, 0u, 2u, 7u, 3u), // NEXG.L <>
    Encode(0x4u, 0u, 2u, 7u, 4u), // NEXG.L <>
    Encode(0x4u, 0u, 2u, 7u, 5u), // NEXG.L <>
    Encode(0x4u, 0u, 2u, 7u, 6u), // NEXG.L <>
    Encode(0x4u, 0u, 2u, 7u, 7u), // NEXG.L <>

    Encode(0x4u, 0u, 3u, 1u, 4u), // MOVE SR, A4
    Encode(0x4u, 0u, 3u, 7u, 2u), // MOVE SR, <>
    Encode(0x4u, 0u, 3u, 7u, 3u), // MOVE SR, <>
    Encode(0x4u, 0u, 3u, 7u, 4u), // MOVE SR, <>
    Encode(0x4u, 0u, 3u, 7u, 5u), // MOVE SR, <>
    Encode(0x4u, 0u, 3u, 7u, 6u), // MOVE SR, <>
    Encode(0x4u, 0u, 3u, 7u, 7u), // MOVE SR, <>

    Encode(0x4u, 0u, 4u, 0u, 4u), // Undef D4
    Encode(0x4u, 0u, 4u, 1u, 4u), // Undef A4
    Encode(0x4u, 0u, 4u, 2u, 4u), // Undef (A4)
    Encode(0x4u, 0u, 4u, 3u, 4u), // Undef (A4)+
    Encode(0x4u, 0u, 4u, 4u, 4u), // Undef -(A4)
    Encode(0x4u, 0u, 4u, 5u, 4u), // Undef (d16, A4)
    Encode(0x4u, 0u, 4u, 5u, 4u), // Undef (d8, A4, Xn)
    Encode(0x4u, 0u, 4u, 7u, 0u), // Undef (XXX).W
    Encode(0x4u, 0u, 4u, 7u, 1u), // Undef (XXX).L
    Encode(0x4u, 0u, 4u, 7u, 2u), // Undef (d16, PC)
    Encode(0x4u, 0u, 4u, 7u, 3u), // Undef (d8, PC, Xn)
    Encode(0x4u, 0u, 4u, 7u, 4u), // Undef #imm
    Encode(0x4u, 0u, 4u, 7u, 5u), // Undef <>
    Encode(0x4u, 0u, 4u, 7u, 6u), // Undef <>
    Encode(0x4u, 0u, 4u, 7u, 7u), // Undef <>

    Encode(0x4u, 0u, 5u, 0u, 4u), // Undef D4
    Encode(0x4u, 0u, 5u, 1u, 4u), // Undef A4
    Encode(0x4u, 0u, 5u, 2u, 4u), // Undef (A4)
    Encode(0x4u, 0u, 5u, 3u, 4u), // Undef (A4)+
    Encode(0x4u, 0u, 5u, 4u, 4u), // Undef -(A4)
    Encode(0x4u, 0u, 5u, 5u, 4u), // Undef (d16, A4)
    Encode(0x4u, 0u, 5u, 5u, 4u), // Undef (d8, A4, Xn)
    Encode(0x4u, 0u, 5u, 7u, 0u), // Undef (XXX).W
    Encode(0x4u, 0u, 5u, 7u, 1u), // Undef (XXX).L
    Encode(0x4u, 0u, 5u, 7u, 2u), // Undef (d16, PC)
    Encode(0x4u, 0u, 5u, 7u, 3u), // Undef (d8, PC, Xn)
    Encode(0x4u, 0u, 5u, 7u, 4u), // Undef #imm
    Encode(0x4u, 0u, 5u, 7u, 5u), // Undef <>
    Encode(0x4u, 0u, 5u, 7u, 6u), // Undef <>
    Encode(0x4u, 0u, 5u, 7u, 7u), // Undef <>

    Encode(0x4u, 0u, 6u, 1u, 4u), // CHK.W A4, D0
    Encode(0x4u, 0u, 6u, 7u, 5u), // CHK.W <>, D0
    Encode(0x4u, 0u, 6u, 7u, 6u), // CHK.W <>, D0
    Encode(0x4u, 0u, 6u, 7u, 7u), // CHK.W <>, D0

    Encode(0x4u, 0u, 7u, 0u, 4u), // LEA D4, A0
    Encode(0x4u, 0u, 7u, 1u, 4u), // LEA A4, A0
    Encode(0x4u, 0u, 7u, 3u, 4u), // LEA (A4)+, A0
    Encode(0x4u, 0u, 7u, 4u, 4u), // LEA -A4, A0
    Encode(0x4u, 0u, 7u, 7u, 4u), // LEA #imm, A0
    Encode(0x4u, 0u, 7u, 7u, 5u), // LEA <>, A0
    Encode(0x4u, 0u, 7u, 7u, 6u), // LEA <>, A0
    Encode(0x4u, 0u, 7u, 7u, 7u), // LEA <>, A0


    Encode(0x4u, 1u, 0u, 1u, 4u), // CLR.B A4
    Encode(0x4u, 1u, 0u, 7u, 2u), // CLR.B <>
    Encode(0x4u, 1u, 0u, 7u, 3u), // CLR.B <>
    Encode(0x4u, 1u, 0u, 7u, 4u), // CLR.B <>
    Encode(0x4u, 1u, 0u, 7u, 5u), // CLR.B <>
    Encode(0x4u, 1u, 0u, 7u, 6u), // CLR.B <>
    Encode(0x4u, 1u, 0u, 7u, 7u), // CLR.B <>

    Encode(0x4u, 1u, 1u, 1u, 4u), // CLR.W A4
    Encode(0x4u, 1u, 1u, 7u, 2u), // CLR.W <>
    Encode(0x4u, 1u, 1u, 7u, 3u), // CLR.W <>
    Encode(0x4u, 1u, 1u, 7u, 4u), // CLR.W <>
    Encode(0x4u, 1u, 1u, 7u, 5u), // CLR.W <>
    Encode(0x4u, 1u, 1u, 7u, 6u), // CLR.W <>
    Encode(0x4u, 1u, 1u, 7u, 7u), // CLR.W <>

    Encode(0x4u, 1u, 2u, 1u, 4u), // CLR.L A4
    Encode(0x4u, 1u, 2u, 7u, 2u), // CLR.L <>
    Encode(0x4u, 1u, 2u, 7u, 3u), // CLR.L <>
    Encode(0x4u, 1u, 2u, 7u, 4u), // CLR.L <>
    Encode(0x4u, 1u, 2u, 7u, 5u), // CLR.L <>
    Encode(0x4u, 1u, 2u, 7u, 6u), // CLR.L <>
    Encode(0x4u, 1u, 2u, 7u, 7u), // CLR.L <>

    Encode(0x4u, 1u, 3u, 0u, 4u), // Undef D4
    Encode(0x4u, 1u, 3u, 1u, 4u), // Undef A4
    Encode(0x4u, 1u, 3u, 2u, 4u), // Undef (A4)
    Encode(0x4u, 1u, 3u, 3u, 4u), // Undef (A4)+
    Encode(0x4u, 1u, 3u, 4u, 4u), // Undef -(A4)
    Encode(0x4u, 1u, 3u, 5u, 4u), // Undef (d16, A4)
    Encode(0x4u, 1u, 3u, 5u, 4u), // Undef (d8, A4, Xn)
    Encode(0x4u, 1u, 3u, 7u, 0u), // Undef (XXX).W
    Encode(0x4u, 1u, 3u, 7u, 1u), // Undef (XXX).L
    Encode(0x4u, 1u, 3u, 7u, 2u), // Undef (d16, PC)
    Encode(0x4u, 1u, 3u, 7u, 3u), // Undef (d8, PC, Xn)
    Encode(0x4u, 1u, 3u, 7u, 4u), // Undef #imm
    Encode(0x4u, 1u, 3u, 7u, 5u), // Undef <>
    Encode(0x4u, 1u, 3u, 7u, 6u), // Undef <>
    Encode(0x4u, 1u, 3u, 7u, 7u), // Undef <>

    Encode(0x4u, 1u, 4u, 0u, 4u), // Undef D4
    Encode(0x4u, 1u, 4u, 1u, 4u), // Undef A4
    Encode(0x4u, 1u, 4u, 2u, 4u), // Undef (A4)
    Encode(0x4u, 1u, 4u, 3u, 4u), // Undef (A4)+
    Encode(0x4u, 1u, 4u, 4u, 4u), // Undef -(A4)
    Encode(0x4u, 1u, 4u, 5u, 4u), // Undef (d16, A4)
    Encode(0x4u, 1u, 4u, 5u, 4u), // Undef (d8, A4, Xn)
    Encode(0x4u, 1u, 4u, 7u, 0u), // Undef (XXX).W
    Encode(0x4u, 1u, 4u, 7u, 1u), // Undef (XXX).L
    Encode(0x4u, 1u, 4u, 7u, 2u), // Undef (d16, PC)
    Encode(0x4u, 1u, 4u, 7u, 3u), // Undef (d8, PC, Xn)
    Encode(0x4u, 1u, 4u, 7u, 4u), // Undef #imm
    Encode(0x4u, 1u, 4u, 7u, 5u), // Undef <>
    Encode(0x4u, 1u, 4u, 7u, 6u), // Undef <>
    Encode(0x4u, 1u, 4u, 7u, 7u), // Undef <>

    Encode(0x4u, 1u, 5u, 0u, 4u), // Undef D4
    Encode(0x4u, 1u, 5u, 1u, 4u), // Undef A4
    Encode(0x4u, 1u, 5u, 2u, 4u), // Undef (A4)
    Encode(0x4u, 1u, 5u, 3u, 4u), // Undef (A4)+
    Encode(0x4u, 1u, 5u, 4u, 4u), // Undef -(A4)
    Encode(0x4u, 1u, 5u, 5u, 4u), // Undef (d16, A4)
    Encode(0x4u, 1u, 5u, 5u, 4u), // Undef (d8, A4, Xn)
    Encode(0x4u, 1u, 5u, 7u, 0u), // Undef (XXX).W
    Encode(0x4u, 1u, 5u, 7u, 1u), // Undef (XXX).L
    Encode(0x4u, 1u, 5u, 7u, 2u), // Undef (d16, PC)
    Encode(0x4u, 1u, 5u, 7u, 3u), // Undef (d8, PC, Xn)
    Encode(0x4u, 1u, 5u, 7u, 4u), // Undef #imm
    Encode(0x4u, 1u, 5u, 7u, 5u), // Undef <>
    Encode(0x4u, 1u, 5u, 7u, 6u), // Undef <>
    Encode(0x4u, 1u, 5u, 7u, 7u), // Undef <>


    Encode(0x4u, 2u, 0u, 1u, 4u), // NEG.B A4
    Encode(0x4u, 2u, 0u, 7u, 2u), // NEG.B <>
    Encode(0x4u, 2u, 0u, 7u, 3u), // NEG.B <>
    Encode(0x4u, 2u, 0u, 7u, 4u), // NEG.B <>
    Encode(0x4u, 2u, 0u, 7u, 5u), // NEG.B <>
    Encode(0x4u, 2u, 0u, 7u, 6u), // NEG.B <>
    Encode(0x4u, 2u, 0u, 7u, 7u), // NEG.B <>

    Encode(0x4u, 2u, 1u, 1u, 4u), // NEG.W A4
    Encode(0x4u, 2u, 1u, 7u, 2u), // NEG.W <>
    Encode(0x4u, 2u, 1u, 7u, 3u), // NEG.W <>
    Encode(0x4u, 2u, 1u, 7u, 4u), // NEG.W <>
    Encode(0x4u, 2u, 1u, 7u, 5u), // NEG.W <>
    Encode(0x4u, 2u, 1u, 7u, 6u), // NEG.W <>
    Encode(0x4u, 2u, 1u, 7u, 7u), // NEG.W <>

    Encode(0x4u, 2u, 2u, 1u, 4u), // NEG.L A4
    Encode(0x4u, 2u, 2u, 7u, 2u), // NEG.L <>
    Encode(0x4u, 2u, 2u, 7u, 3u), // NEG.L <>
    Encode(0x4u, 2u, 2u, 7u, 4u), // NEG.L <>
    Encode(0x4u, 2u, 2u, 7u, 5u), // NEG.L <>
    Encode(0x4u, 2u, 2u, 7u, 6u), // NEG.L <>
    Encode(0x4u, 2u, 2u, 7u, 7u), // NEG.L <>

    Encode(0x4u, 2u, 3u, 1u, 4u), // MOVE A4, CCR
    Encode(0x4u, 2u, 3u, 7u, 5u), // MOVE <>, CCR
    Encode(0x4u, 2u, 3u, 7u, 6u), // MOVE <>, CCR
    Encode(0x4u, 2u, 3u, 7u, 7u), // MOVE <>, CCR

    Encode(0x4u, 2u, 4u, 0u, 4u), // Undef D4
    Encode(0x4u, 2u, 4u, 1u, 4u), // Undef A4
    Encode(0x4u, 2u, 4u, 2u, 4u), // Undef (A4)
    Encode(0x4u, 2u, 4u, 3u, 4u), // Undef (A4)+
    Encode(0x4u, 2u, 4u, 4u, 4u), // Undef -(A4)
    Encode(0x4u, 2u, 4u, 5u, 4u), // Undef (d16, A4)
    Encode(0x4u, 2u, 4u, 5u, 4u), // Undef (d8, A4, Xn)
    Encode(0x4u, 2u, 4u, 7u, 0u), // Undef (XXX).W
    Encode(0x4u, 2u, 4u, 7u, 1u), // Undef (XXX).L
    Encode(0x4u, 2u, 4u, 7u, 2u), // Undef (d16, PC)
    Encode(0x4u, 2u, 4u, 7u, 3u), // Undef (d8, PC, Xn)
    Encode(0x4u, 2u, 4u, 7u, 4u), // Undef #imm
    Encode(0x4u, 2u, 4u, 7u, 5u), // Undef <>
    Encode(0x4u, 2u, 4u, 7u, 6u), // Undef <>
    Encode(0x4u, 2u, 4u, 7u, 7u), // Undef <>

    Encode(0x4u, 2u, 5u, 0u, 4u), // Undef D4
    Encode(0x4u, 2u, 5u, 1u, 4u), // Undef A4
    Encode(0x4u, 2u, 5u, 2u, 4u), // Undef (A4)
    Encode(0x4u, 2u, 5u, 3u, 4u), // Undef (A4)+
    Encode(0x4u, 2u, 5u, 4u, 4u), // Undef -(A4)
    Encode(0x4u, 2u, 5u, 5u, 4u), // Undef (d16, A4)
    Encode(0x4u, 2u, 5u, 5u, 4u), // Undef (d8, A4, Xn)
    Encode(0x4u, 2u, 5u, 7u, 0u), // Undef (XXX).W
    Encode(0x4u, 2u, 5u, 7u, 1u), // Undef (XXX).L
    Encode(0x4u, 2u, 5u, 7u, 2u), // Undef (d16, PC)
    Encode(0x4u, 2u, 5u, 7u, 3u), // Undef (d8, PC, Xn)
    Encode(0x4u, 2u, 5u, 7u, 4u), // Undef #imm
    Encode(0x4u, 2u, 5u, 7u, 5u), // Undef <>
    Encode(0x4u, 2u, 5u, 7u, 6u), // Undef <>
    Encode(0x4u, 2u, 5u, 7u, 7u), // Undef <>


    Encode(0x4u, 3u, 0u, 1u, 4u), // NOT.B A4
    Encode(0x4u, 3u, 0u, 7u, 2u), // NOT.B <>
    Encode(0x4u, 3u, 0u, 7u, 3u), // NOT.B <>
    Encode(0x4u, 3u, 0u, 7u, 4u), // NOT.B <>
    Encode(0x4u, 3u, 0u, 7u, 5u), // NOT.B <>
    Encode(0x4u, 3u, 0u, 7u, 6u), // NOT.B <>
    Encode(0x4u, 3u, 0u, 7u, 7u), // NOT.B <>

    Encode(0x4u, 3u, 1u, 1u, 4u), // NOT.W A4
    Encode(0x4u, 3u, 1u, 7u, 2u), // NOT.W <>
    Encode(0x4u, 3u, 1u, 7u, 3u), // NOT.W <>
    Encode(0x4u, 3u, 1u, 7u, 4u), // NOT.W <>
    Encode(0x4u, 3u, 1u, 7u, 5u), // NOT.W <>
    Encode(0x4u, 3u, 1u, 7u, 6u), // NOT.W <>
    Encode(0x4u, 3u, 1u, 7u, 7u), // NOT.W <>

    Encode(0x4u, 3u, 2u, 1u, 4u), // NOT.L A4
    Encode(0x4u, 3u, 2u, 7u, 2u), // NOT.L <>
    Encode(0x4u, 3u, 2u, 7u, 3u), // NOT.L <>
    Encode(0x4u, 3u, 2u, 7u, 4u), // NOT.L <>
    Encode(0x4u, 3u, 2u, 7u, 5u), // NOT.L <>
    Encode(0x4u, 3u, 2u, 7u, 6u), // NOT.L <>
    Encode(0x4u, 3u, 2u, 7u, 7u), // NOT.L <>

    Encode(0x4u, 3u, 3u, 1u, 4u), // MOVE A4, SR
    Encode(0x4u, 3u, 3u, 7u, 5u), // MOVE <>, SR
    Encode(0x4u, 3u, 3u, 7u, 6u), // MOVE <>, SR
    Encode(0x4u, 3u, 3u, 7u, 7u), // MOVE <>, SR

    Encode(0x4u, 3u, 4u, 0u, 4u), // Undef D4
    Encode(0x4u, 3u, 4u, 1u, 4u), // Undef A4
    Encode(0x4u, 3u, 4u, 2u, 4u), // Undef (A4)
    Encode(0x4u, 3u, 4u, 3u, 4u), // Undef (A4)+
    Encode(0x4u, 3u, 4u, 4u, 4u), // Undef -(A4)
    Encode(0x4u, 3u, 4u, 5u, 4u), // Undef (d16, A4)
    Encode(0x4u, 3u, 4u, 5u, 4u), // Undef (d8, A4, Xn)
    Encode(0x4u, 3u, 4u, 7u, 0u), // Undef (XXX).W
    Encode(0x4u, 3u, 4u, 7u, 1u), // Undef (XXX).L
    Encode(0x4u, 3u, 4u, 7u, 2u), // Undef (d16, PC)
    Encode(0x4u, 3u, 4u, 7u, 3u), // Undef (d8, PC, Xn)
    Encode(0x4u, 3u, 4u, 7u, 4u), // Undef #imm
    Encode(0x4u, 3u, 4u, 7u, 5u), // Undef <>
    Encode(0x4u, 3u, 4u, 7u, 6u), // Undef <>
    Encode(0x4u, 3u, 4u, 7u, 7u), // Undef <>

    Encode(0x4u, 3u, 5u, 0u, 4u), // Undef D4
    Encode(0x4u, 3u, 5u, 1u, 4u), // Undef A4
    Encode(0x4u, 3u, 5u, 2u, 4u), // Undef (A4)
    Encode(0x4u, 3u, 5u, 3u, 4u), // Undef (A4)+
    Encode(0x4u, 3u, 5u, 4u, 4u), // Undef -(A4)
    Encode(0x4u, 3u, 5u, 5u, 4u), // Undef (d16, A4)
    Encode(0x4u, 3u, 5u, 5u, 4u), // Undef (d8, A4, Xn)
    Encode(0x4u, 3u, 5u, 7u, 0u), // Undef (XXX).W
    Encode(0x4u, 3u, 5u, 7u, 1u), // Undef (XXX).L
    Encode(0x4u, 3u, 5u, 7u, 2u), // Undef (d16, PC)
    Encode(0x4u, 3u, 5u, 7u, 3u), // Undef (d8, PC, Xn)
    Encode(0x4u, 3u, 5u, 7u, 4u), // Undef #imm
    Encode(0x4u, 3u, 5u, 7u, 5u), // Undef <>
    Encode(0x4u, 3u, 5u, 7u, 6u), // Undef <>
    Encode(0x4u, 3u, 5u, 7u, 7u), // Undef <>

    Encode(0x4u, 4u, 0u, 1u, 4u), // NBCD A4
    Encode(0x4u, 4u, 0u, 7u, 2u), // NBCD <>
    Encode(0x4u, 4u, 0u, 7u, 3u), // NBCD <>
    Encode(0x4u, 4u, 0u, 7u, 4u), // NBCD <>
    Encode(0x4u, 4u, 0u, 7u, 5u), // NBCD <>
    Encode(0x4u, 4u, 0u, 7u, 6u), // NBCD <>
    Encode(0x4u, 4u, 0u, 7u, 7u), // NBCD <>

    Encode(0x4u, 4u, 1u, 1u, 4u), // PEA A4
    Encode(0x4u, 4u, 1u, 3u, 4u), // PEA (A4)+
    Encode(0x4u, 4u, 1u, 4u, 4u), // PEA -(A4)
    Encode(0x4u, 4u, 1u, 7u, 4u), // PEA <>
    Encode(0x4u, 4u, 1u, 7u, 5u), // PEA <>
    Encode(0x4u, 4u, 1u, 7u, 6u), // PEA <>
    Encode(0x4u, 4u, 1u, 7u, 7u), // PEA <>

    Encode(0x4u, 4u, 2u, 1u, 4u), // MOVEM.W [], A4
    Encode(0x4u, 4u, 2u, 3u, 4u), // MOVEM.W [], (A4)+
    Encode(0x4u, 4u, 2u, 7u, 2u), // MOVEM.W [], <>
    Encode(0x4u, 4u, 2u, 7u, 3u), // MOVEM.W [], <>
    Encode(0x4u, 4u, 2u, 7u, 4u), // MOVEM.W [], <>
    Encode(0x4u, 4u, 2u, 7u, 5u), // MOVEM.W [], <>
    Encode(0x4u, 4u, 2u, 7u, 6u), // MOVEM.W [], <>
    Encode(0x4u, 4u, 2u, 7u, 7u), // MOVEM.W [], <>

    Encode(0x4u, 4u, 3u, 1u, 4u), // MOVEM.L [], A4
    Encode(0x4u, 4u, 3u, 3u, 4u), // MOVEM.L [], (A4)+
    Encode(0x4u, 4u, 3u, 7u, 2u), // MOVEM.L [], <>
    Encode(0x4u, 4u, 3u, 7u, 3u), // MOVEM.L [], <>
    Encode(0x4u, 4u, 3u, 7u, 4u), // MOVEM.L [], <>
    Encode(0x4u, 4u, 3u, 7u, 5u), // MOVEM.L [], <>
    Encode(0x4u, 4u, 3u, 7u, 6u), // MOVEM.L [], <>
    Encode(0x4u, 4u, 3u, 7u, 7u), // MOVEM.L [], <>

    Encode(0x4u, 4u, 4u, 0u, 4u), // Undef D4
    Encode(0x4u, 4u, 4u, 1u, 4u), // Undef A4
    Encode(0x4u, 4u, 4u, 2u, 4u), // Undef (A4)
    Encode(0x4u, 4u, 4u, 3u, 4u), // Undef (A4)+
    Encode(0x4u, 4u, 4u, 4u, 4u), // Undef -(A4)
    Encode(0x4u, 4u, 4u, 5u, 4u), // Undef (d16, A4)
    Encode(0x4u, 4u, 4u, 5u, 4u), // Undef (d8, A4, Xn)
    Encode(0x4u, 4u, 4u, 7u, 0u), // Undef (XXX).W
    Encode(0x4u, 4u, 4u, 7u, 1u), // Undef (XXX).L
    Encode(0x4u, 4u, 4u, 7u, 2u), // Undef (d16, PC)
    Encode(0x4u, 4u, 4u, 7u, 3u), // Undef (d8, PC, Xn)
    Encode(0x4u, 4u, 4u, 7u, 4u), // Undef #imm
    Encode(0x4u, 4u, 4u, 7u, 5u), // Undef <>
    Encode(0x4u, 4u, 4u, 7u, 6u), // Undef <>
    Encode(0x4u, 4u, 4u, 7u, 7u), // Undef <>

    Encode(0x4u, 4u, 5u, 0u, 4u), // Undef D4
    Encode(0x4u, 4u, 5u, 1u, 4u), // Undef A4
    Encode(0x4u, 4u, 5u, 2u, 4u), // Undef (A4)
    Encode(0x4u, 4u, 5u, 3u, 4u), // Undef (A4)+
    Encode(0x4u, 4u, 5u, 4u, 4u), // Undef -(A4)
    Encode(0x4u, 4u, 5u, 5u, 4u), // Undef (d16, A4)
    Encode(0x4u, 4u, 5u, 5u, 4u), // Undef (d8, A4, Xn)
    Encode(0x4u, 4u, 5u, 7u, 0u), // Undef (XXX).W
    Encode(0x4u, 4u, 5u, 7u, 1u), // Undef (XXX).L
    Encode(0x4u, 4u, 5u, 7u, 2u), // Undef (d16, PC)
    Encode(0x4u, 4u, 5u, 7u, 3u), // Undef (d8, PC, Xn)
    Encode(0x4u, 4u, 5u, 7u, 4u), // Undef #imm
    Encode(0x4u, 4u, 5u, 7u, 5u), // Undef <>
    Encode(0x4u, 4u, 5u, 7u, 6u), // Undef <>
    Encode(0x4u, 4u, 5u, 7u, 7u), // Undef <>


    Encode(0x4u, 5u, 0u, 1u, 4u), // TST.B A4
    Encode(0x4u, 5u, 0u, 7u, 2u), // TST.B <>
    Encode(0x4u, 5u, 0u, 7u, 3u), // TST.B <>
    Encode(0x4u, 5u, 0u, 7u, 4u), // TST.B <>
    Encode(0x4u, 5u, 0u, 7u, 5u), // TST.B <>
    Encode(0x4u, 5u, 0u, 7u, 6u), // TST.B <>
    Encode(0x4u, 5u, 0u, 7u, 7u), // TST.B <>

    Encode(0x4u, 5u, 1u, 1u, 4u), // TST.W A4
    Encode(0x4u, 5u, 1u, 7u, 2u), // TST.W <>
    Encode(0x4u, 5u, 1u, 7u, 3u), // TST.W <>
    Encode(0x4u, 5u, 1u, 7u, 4u), // TST.W <>
    Encode(0x4u, 5u, 1u, 7u, 5u), // TST.W <>
    Encode(0x4u, 5u, 1u, 7u, 6u), // TST.W <>
    Encode(0x4u, 5u, 1u, 7u, 7u), // TST.W <>

    Encode(0x4u, 5u, 2u, 1u, 4u), // TST.L A4
    Encode(0x4u, 5u, 2u, 7u, 2u), // TST.L <>
    Encode(0x4u, 5u, 2u, 7u, 3u), // TST.L <>
    Encode(0x4u, 5u, 2u, 7u, 4u), // TST.L <>
    Encode(0x4u, 5u, 2u, 7u, 5u), // TST.L <>
    Encode(0x4u, 5u, 2u, 7u, 6u), // TST.L <>
    Encode(0x4u, 5u, 2u, 7u, 7u), // TST.L <>

    Encode(0x4u, 5u, 3u, 1u, 4u), // TAS A4
    Encode(0x4u, 5u, 3u, 7u, 2u), // TAS <>
    Encode(0x4u, 5u, 3u, 7u, 3u), // TAS <>
    Encode(0x4u, 5u, 3u, 7u, 4u), // TAS <>
    Encode(0x4u, 5u, 3u, 7u, 5u), // TAS <>
    Encode(0x4u, 5u, 3u, 7u, 6u), // TAS <>
    Encode(0x4u, 5u, 3u, 7u, 7u), // TAS <>

    Encode(0x4u, 5u, 4u, 0u, 4u), // Undef D4
    Encode(0x4u, 5u, 4u, 1u, 4u), // Undef A4
    Encode(0x4u, 5u, 4u, 2u, 4u), // Undef (A4)
    Encode(0x4u, 5u, 4u, 3u, 4u), // Undef (A4)+
    Encode(0x4u, 5u, 4u, 4u, 4u), // Undef -(A4)
    Encode(0x4u, 5u, 4u, 5u, 4u), // Undef (d16, A4)
    Encode(0x4u, 5u, 4u, 5u, 4u), // Undef (d8, A4, Xn)
    Encode(0x4u, 5u, 4u, 7u, 0u), // Undef (XXX).W
    Encode(0x4u, 5u, 4u, 7u, 1u), // Undef (XXX).L
    Encode(0x4u, 5u, 4u, 7u, 2u), // Undef (d16, PC)
    Encode(0x4u, 5u, 4u, 7u, 3u), // Undef (d8, PC, Xn)
    Encode(0x4u, 5u, 4u, 7u, 4u), // Undef #imm
    Encode(0x4u, 5u, 4u, 7u, 5u), // Undef <>
    Encode(0x4u, 5u, 4u, 7u, 6u), // Undef <>
    Encode(0x4u, 5u, 4u, 7u, 7u), // Undef <>

    Encode(0x4u, 5u, 5u, 0u, 4u), // Undef D4
    Encode(0x4u, 5u, 5u, 1u, 4u), // Undef A4
    Encode(0x4u, 5u, 5u, 2u, 4u), // Undef (A4)
    Encode(0x4u, 5u, 5u, 3u, 4u), // Undef (A4)+
    Encode(0x4u, 5u, 5u, 4u, 4u), // Undef -(A4)
    Encode(0x4u, 5u, 5u, 5u, 4u), // Undef (d16, A4)
    Encode(0x4u, 5u, 5u, 5u, 4u), // Undef (d8, A4, Xn)
    Encode(0x4u, 5u, 5u, 7u, 0u), // Undef (XXX).W
    Encode(0x4u, 5u, 5u, 7u, 1u), // Undef (XXX).L
    Encode(0x4u, 5u, 5u, 7u, 2u), // Undef (d16, PC)
    Encode(0x4u, 5u, 5u, 7u, 3u), // Undef (d8, PC, Xn)
    Encode(0x4u, 5u, 5u, 7u, 4u), // Undef #imm
    Encode(0x4u, 5u, 5u, 7u, 5u), // Undef <>
    Encode(0x4u, 5u, 5u, 7u, 6u), // Undef <>
    Encode(0x4u, 5u, 5u, 7u, 7u), // Undef <>


    Encode(0x4u, 6u, 0u, 0u, 4u), // Undef D4
    Encode(0x4u, 6u, 0u, 1u, 4u), // Undef A4
    Encode(0x4u, 6u, 0u, 2u, 4u), // Undef (A4)
    Encode(0x4u, 6u, 0u, 3u, 4u), // Undef (A4)+
    Encode(0x4u, 6u, 0u, 4u, 4u), // Undef -(A4)
    Encode(0x4u, 6u, 0u, 5u, 4u), // Undef (d16, A4)
    Encode(0x4u, 6u, 0u, 5u, 4u), // Undef (d8, A4, Xn)
    Encode(0x4u, 6u, 0u, 7u, 0u), // Undef (XXX).W
    Encode(0x4u, 6u, 0u, 7u, 1u), // Undef (XXX).L
    Encode(0x4u, 6u, 0u, 7u, 2u), // Undef (d16, PC)
    Encode(0x4u, 6u, 0u, 7u, 3u), // Undef (d8, PC, Xn)
    Encode(0x4u, 6u, 0u, 7u, 4u), // Undef #imm
    Encode(0x4u, 6u, 0u, 7u, 5u), // Undef <>
    Encode(0x4u, 6u, 0u, 7u, 6u), // Undef <>
    Encode(0x4u, 6u, 0u, 7u, 7u), // Undef <>

    Encode(0x4u, 6u, 1u, 0u, 4u), // Undef D4
    Encode(0x4u, 6u, 1u, 1u, 4u), // Undef A4
    Encode(0x4u, 6u, 1u, 2u, 4u), // Undef (A4)
    Encode(0x4u, 6u, 1u, 3u, 4u), // Undef (A4)+
    Encode(0x4u, 6u, 1u, 4u, 4u), // Undef -(A4)
    Encode(0x4u, 6u, 1u, 5u, 4u), // Undef (d16, A4)
    Encode(0x4u, 6u, 1u, 5u, 4u), // Undef (d8, A4, Xn)
    Encode(0x4u, 6u, 1u, 7u, 0u), // Undef (XXX).W
    Encode(0x4u, 6u, 1u, 7u, 1u), // Undef (XXX).L
    Encode(0x4u, 6u, 1u, 7u, 2u), // Undef (d16, PC)
    Encode(0x4u, 6u, 1u, 7u, 3u), // Undef (d8, PC, Xn)
    Encode(0x4u, 6u, 1u, 7u, 4u), // Undef #imm
    Encode(0x4u, 6u, 1u, 7u, 5u), // Undef <>
    Encode(0x4u, 6u, 1u, 7u, 6u), // Undef <>
    Encode(0x4u, 6u, 1u, 7u, 7u), // Undef <>

    Encode(0x4u, 6u, 2u, 0u, 4u), // MOVEM.W D4, []
    Encode(0x4u, 6u, 2u, 1u, 4u), // MOVEM.W A4, []
    Encode(0x4u, 6u, 2u, 4u, 4u), // MOVEM.W -(A4), []
    Encode(0x4u, 6u, 2u, 7u, 4u), // MOVEM.W #imm, []
    Encode(0x4u, 6u, 2u, 7u, 5u), // MOVEM.W <>, []
    Encode(0x4u, 6u, 2u, 7u, 6u), // MOVEM.W <>, []
    Encode(0x4u, 6u, 2u, 7u, 7u), // MOVEM.W <>, []

    Encode(0x4u, 6u, 3u, 0u, 4u), // MOVEM.L D4, []
    Encode(0x4u, 6u, 3u, 1u, 4u), // MOVEM.L A4, []
    Encode(0x4u, 6u, 3u, 4u, 4u), // MOVEM.L -(A4), []
    Encode(0x4u, 6u, 3u, 7u, 4u), // MOVEM.L #imm, []
    Encode(0x4u, 6u, 3u, 7u, 5u), // MOVEM.L <>, []
    Encode(0x4u, 6u, 3u, 7u, 6u), // MOVEM.L <>, []
    Encode(0x4u, 6u, 3u, 7u, 7u), // MOVEM.L <>, []

    Encode(0x4u, 6u, 4u, 0u, 4u), // Undef D4
    Encode(0x4u, 6u, 4u, 1u, 4u), // Undef A4
    Encode(0x4u, 6u, 4u, 2u, 4u), // Undef (A4)
    Encode(0x4u, 6u, 4u, 3u, 4u), // Undef (A4)+
    Encode(0x4u, 6u, 4u, 4u, 4u), // Undef -(A4)
    Encode(0x4u, 6u, 4u, 5u, 4u), // Undef (d16, A4)
    Encode(0x4u, 6u, 4u, 5u, 4u), // Undef (d8, A4, Xn)
    Encode(0x4u, 6u, 4u, 7u, 0u), // Undef (XXX).W
    Encode(0x4u, 6u, 4u, 7u, 1u), // Undef (XXX).L
    Encode(0x4u, 6u, 4u, 7u, 2u), // Undef (d16, PC)
    Encode(0x4u, 6u, 4u, 7u, 3u), // Undef (d8, PC, Xn)
    Encode(0x4u, 6u, 4u, 7u, 4u), // Undef #imm
    Encode(0x4u, 6u, 4u, 7u, 5u), // Undef <>
    Encode(0x4u, 6u, 4u, 7u, 6u), // Undef <>
    Encode(0x4u, 6u, 4u, 7u, 7u), // Undef <>

    Encode(0x4u, 6u, 5u, 0u, 4u), // Undef D4
    Encode(0x4u, 6u, 5u, 1u, 4u), // Undef A4
    Encode(0x4u, 6u, 5u, 2u, 4u), // Undef (A4)
    Encode(0x4u, 6u, 5u, 3u, 4u), // Undef (A4)+
    Encode(0x4u, 6u, 5u, 4u, 4u), // Undef -(A4)
    Encode(0x4u, 6u, 5u, 5u, 4u), // Undef (d16, A4)
    Encode(0x4u, 6u, 5u, 5u, 4u), // Undef (d8, A4, Xn)
    Encode(0x4u, 6u, 5u, 7u, 0u), // Undef (XXX).W
    Encode(0x4u, 6u, 5u, 7u, 1u), // Undef (XXX).L
    Encode(0x4u, 6u, 5u, 7u, 2u), // Undef (d16, PC)
    Encode(0x4u, 6u, 5u, 7u, 3u), // Undef (d8, PC, Xn)
    Encode(0x4u, 6u, 5u, 7u, 4u), // Undef #imm
    Encode(0x4u, 6u, 5u, 7u, 5u), // Undef <>
    Encode(0x4u, 6u, 5u, 7u, 6u), // Undef <>
    Encode(0x4u, 6u, 5u, 7u, 7u), // Undef <>


    Encode(0x4u, 7u, 0u, 0u, 4u), // Undef D4
    Encode(0x4u, 7u, 0u, 1u, 4u), // Undef A4
    Encode(0x4u, 7u, 0u, 2u, 4u), // Undef (A4)
    Encode(0x4u, 7u, 0u, 3u, 4u), // Undef (A4)+
    Encode(0x4u, 7u, 0u, 4u, 4u), // Undef -(A4)
    Encode(0x4u, 7u, 0u, 5u, 4u), // Undef (d16, A4)
    Encode(0x4u, 7u, 0u, 5u, 4u), // Undef (d8, A4, Xn)
    Encode(0x4u, 7u, 0u, 7u, 0u), // Undef (XXX).W
    Encode(0x4u, 7u, 0u, 7u, 1u), // Undef (XXX).L
    Encode(0x4u, 7u, 0u, 7u, 2u), // Undef (d16, PC)
    Encode(0x4u, 7u, 0u, 7u, 3u), // Undef (d8, PC, Xn)
    Encode(0x4u, 7u, 0u, 7u, 4u), // Undef #imm
    Encode(0x4u, 7u, 0u, 7u, 5u), // Undef <>
    Encode(0x4u, 7u, 0u, 7u, 6u), // Undef <>
    Encode(0x4u, 7u, 0u, 7u, 7u), // Undef <>

    Encode(0x4u, 7u, 1u, 7u, 0u), // Undef <>

    Encode(0x4u, 7u, 2u, 0u, 4u), // JSR D4
    Encode(0x4u, 7u, 2u, 1u, 4u), // JSR A4
    Encode(0x4u, 7u, 2u, 3u, 4u), // JSR (A4)+
    Encode(0x4u, 7u, 2u, 4u, 4u), // JSR -(A4)
    Encode(0x4u, 7u, 2u, 7u, 4u), // JSR #imm
    Encode(0x4u, 7u, 2u, 7u, 5u), // JSR <>
    Encode(0x4u, 7u, 2u, 7u, 6u), // JSR <>
    Encode(0x4u, 7u, 2u, 7u, 7u), // JSR <>

    Encode(0x4u, 7u, 3u, 0u, 4u), // JMP D4
    Encode(0x4u, 7u, 3u, 1u, 4u), // JMP A4
    Encode(0x4u, 7u, 3u, 3u, 4u), // JMP (A4)+
    Encode(0x4u, 7u, 3u, 4u, 4u), // JMP -(A4)
    Encode(0x4u, 7u, 3u, 7u, 4u), // JMP #imm
    Encode(0x4u, 7u, 3u, 7u, 5u), // JMP <>
    Encode(0x4u, 7u, 3u, 7u, 6u), // JMP <>
    Encode(0x4u, 7u, 3u, 7u, 7u), // JMP <>

    Encode(0x4u, 7u, 4u, 0u, 4u), // Undef D4
    Encode(0x4u, 7u, 4u, 1u, 4u), // Undef A4
    Encode(0x4u, 7u, 4u, 2u, 4u), // Undef (A4)
    Encode(0x4u, 7u, 4u, 3u, 4u), // Undef (A4)+
    Encode(0x4u, 7u, 4u, 4u, 4u), // Undef -(A4)
    Encode(0x4u, 7u, 4u, 5u, 4u), // Undef (d16, A4)
    Encode(0x4u, 7u, 4u, 5u, 4u), // Undef (d8, A4, Xn)
    Encode(0x4u, 7u, 4u, 7u, 0u), // Undef (XXX).W
    Encode(0x4u, 7u, 4u, 7u, 1u), // Undef (XXX).L
    Encode(0x4u, 7u, 4u, 7u, 2u), // Undef (d16, PC)
    Encode(0x4u, 7u, 4u, 7u, 3u), // Undef (d8, PC, Xn)
    Encode(0x4u, 7u, 4u, 7u, 4u), // Undef #imm
    Encode(0x4u, 7u, 4u, 7u, 5u), // Undef <>
    Encode(0x4u, 7u, 4u, 7u, 6u), // Undef <>
    Encode(0x4u, 7u, 4u, 7u, 7u), // Undef <>

    Encode(0x4u, 7u, 5u, 0u, 4u), // Undef D4
    Encode(0x4u, 7u, 5u, 1u, 4u), // Undef A4
    Encode(0x4u, 7u, 5u, 2u, 4u), // Undef (A4)
    Encode(0x4u, 7u, 5u, 3u, 4u), // Undef (A4)+
    Encode(0x4u, 7u, 5u, 4u, 4u), // Undef -(A4)
    Encode(0x4u, 7u, 5u, 5u, 4u), // Undef (d16, A4)
    Encode(0x4u, 7u, 5u, 5u, 4u), // Undef (d8, A4, Xn)
    Encode(0x4u, 7u, 5u, 7u, 0u), // Undef (XXX).W
    Encode(0x4u, 7u, 5u, 7u, 1u), // Undef (XXX).L
    Encode(0x4u, 7u, 5u, 7u, 2u), // Undef (d16, PC)
    Encode(0x4u, 7u, 5u, 7u, 3u), // Undef (d8, PC, Xn)
    Encode(0x4u, 7u, 5u, 7u, 4u), // Undef #imm
    Encode(0x4u, 7u, 5u, 7u, 5u), // Undef <>
    Encode(0x4u, 7u, 5u, 7u, 6u), // Undef <>
    Encode(0x4u, 7u, 5u, 7u, 7u), // Undef <>
};

class Line4IllegalInstructionTest: public M68000Test, public ::testing::WithParamInterface<uint32_t> {};

TEST_P(Line4IllegalInstructionTest, IllegalInstructionPattern) {
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
   IllegalLine4InstructionPatterns,
   Line4IllegalInstructionTest,
   ::testing::ValuesIn(VALUES)
);

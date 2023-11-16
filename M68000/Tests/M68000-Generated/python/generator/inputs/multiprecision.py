"""
This module contains inputs for the multiprecision instructions.
"""

from ..types.instruction_inputs import \
    BinaryInputs
from ..types.sized_instruction_inputs import \
    ByteInstructionInputs, \
    WordInstructionInputs, \
    LongInstructionInputs
from ..types.status_register import StatusRegister

ADDX_BYTE_INPUTS = ByteInstructionInputs(inputs=[
    # Check the operation looks like addx
    BinaryInputs(src=0x05, dst=0x02),
    BinaryInputs(status_register=StatusRegister(x=True), src=0x05, dst=0x02),
    BinaryInputs(src=0x16, dst=0x78),
    BinaryInputs(status_register=StatusRegister(x=True), src=0x16, dst=0x78),
    # Check that only the lower 8 bits are impacted
    BinaryInputs(src=0xFF, dst=0xEEBB_AA02),
    # Check the x flag behaviour
    BinaryInputs(status_register=StatusRegister(x=False), src=0xFF, dst=0x05),
    BinaryInputs(status_register=StatusRegister(x=True), src=0xFF, dst=0x01),
    # Check the n flag behaviour
    BinaryInputs(src=0x80, dst=0x42),
    BinaryInputs(src=0x00, dst=0xFF),
    BinaryInputs(status_register=StatusRegister(x=True), src=0x01, dst=0x7E),
    # Check the z flag behaviour
    # (Cleared if the result is nonzero; unchanged otherwise).
    BinaryInputs(status_register=StatusRegister(z=True), src=0x00, dst=0x00),
    BinaryInputs(status_register=StatusRegister(z=True), src=0x00, dst=0x01),
    BinaryInputs(src=0x00, dst=0x00),
    BinaryInputs(src=0x00, dst=0x01),
    # Check the v flag behaviour
    BinaryInputs(src=0x81, dst=0x80),
    BinaryInputs(src=0x7F, dst=0x01),
    # Check the carry flag behaviour
    BinaryInputs(status_register=StatusRegister(c=False), src=0xFB, dst=0x05),
    BinaryInputs(status_register=StatusRegister(c=True), src=0x10, dst=0x00),
])

ADDX_WORD_INPUTS = WordInstructionInputs(inputs=[
    # Check the operation looks like addx
    BinaryInputs(src=0x0500, dst=0x0200),
    BinaryInputs(status_register=StatusRegister(x=True), src=0x0500, dst=0x0200),
    BinaryInputs(src=0x1632, dst=0x7855),
    BinaryInputs(status_register=StatusRegister(x=True), src=0x1632, dst=0x7855),
    # Check that only the lower 16 bits are impacted
    BinaryInputs(src=0xFFFF, dst=0xEEBB_AA02),
    # Check the x flag behaviour
    BinaryInputs(status_register=StatusRegister(x=False), src=0xEFFF, dst=0x0005),
    BinaryInputs(status_register=StatusRegister(x=True), src=0xEFFF, dst=0x0001),
    # Check the n flag behaviour
    BinaryInputs(src=0x8000, dst=0x4200),
    BinaryInputs(src=0x0000, dst=0xFFFF),
    BinaryInputs(status_register=StatusRegister(x=True), src=0x0001, dst=0x7FFE),
    # Check the z flag behaviour
    # (Cleared if the result is nonzero; unchanged otherwise).
    BinaryInputs(status_register=StatusRegister(z=True), src=0x0000, dst=0x0000),
    BinaryInputs(status_register=StatusRegister(z=True), src=0x0000, dst=0x0001),
    BinaryInputs(src=0x0000, dst=0x0000),
    BinaryInputs(src=0x0000, dst=0x0001),
    # Check the v flag behaviour
    BinaryInputs(src=0x8100, dst=0x8000),
    BinaryInputs(src=0x7FFF, dst=0x0001),
    # Check the carry flag behaviour
    BinaryInputs(status_register=StatusRegister(c=False), src=0xFFFB, dst=0x0005),
    BinaryInputs(status_register=StatusRegister(c=True), src=0x1000, dst=0x0000),
])

ADDX_LONG_INPUTS = LongInstructionInputs(inputs=[
    # Check the operation looks like addx
    BinaryInputs(src=0x0500_1234, dst=0x0200_5678),
    BinaryInputs(status_register=StatusRegister(x=True), src=0x0500_1234, dst=0x0200_5678),
    BinaryInputs(src=0x1111_1632, dst=0x2222_7855),
    BinaryInputs(status_register=StatusRegister(x=True), src=0x1111_1632, dst=0x2222_7855),
    # Check that all 32 bits are impacted
    BinaryInputs(src=0xFFFF_5555, dst=0xEEBB_AA02),
    # Check the x flag behaviour
    BinaryInputs(status_register=StatusRegister(x=False), src=0xEFFF_FFFF, dst=0x0000_0005),
    BinaryInputs(status_register=StatusRegister(x=True), src=0xEFFF_FFFF, dst=0x0000_0001),
    # Check the n flag behaviour
    BinaryInputs(src=0x8000_0000, dst=0x4200_0000),
    BinaryInputs(src=0x0000_0000, dst=0xFFFF_FFFF),
    BinaryInputs(status_register=StatusRegister(x=True), src=0x0000_0001, dst=0x7FFF_FFFE),
    # Check the z flag behaviour
    # (Cleared if the result is nonzero; unchanged otherwise).
    BinaryInputs(status_register=StatusRegister(z=True), src=0x0000_0000, dst=0x0000_0000),
    BinaryInputs(status_register=StatusRegister(z=True), src=0x0000_0000, dst=0x0000_0001),
    BinaryInputs(src=0x0000_0000, dst=0x0000_0000),
    BinaryInputs(src=0x0000_0000, dst=0x0000_0001),
    # Check the v flag behaviour
    BinaryInputs(src=0x8100_0000, dst=0x8000_0000),
    BinaryInputs(src=0x7FFF_FFFF, dst=0x0000_0001),
    # Check the carry flag behaviour
    BinaryInputs(status_register=StatusRegister(c=False), src=0xFFFF_FFFB, dst=0x0000_0005),
    BinaryInputs(status_register=StatusRegister(c=True), src=0x1000_0000, dst=0x0000_0000),
])

SUBX_BYTE_INPUTS = ByteInstructionInputs(inputs=[
    BinaryInputs(src=0x35, dst=0x12),  # check operation is something like subtraction
    # check x flag influences result
    BinaryInputs(status_register=StatusRegister(x=True), src=0x35, dst=0x12),
    BinaryInputs(src=0x6656_5A01, dst=0x6565_A5FE),  # check byte operation on register
    BinaryInputs(src=0xC0, dst=0x04),  # check negative flag
    BinaryInputs(status_register=StatusRegister(x=True), src=0xC0, dst=0x04),
    BinaryInputs(src=0x00, dst=0x00),  # check trivial zero flag
    BinaryInputs(status_register=StatusRegister(x=True), src=0x00, dst=0x01),
    # Check the z flag behaviour
    # (Cleared if the result is nonzero; unchanged otherwise).
    BinaryInputs(status_register=StatusRegister(z=True), src=0x00, dst=0x00),
    BinaryInputs(status_register=StatusRegister(z=True), src=0x00, dst=0x01),
    BinaryInputs(src=0x00, dst=0x00),
    BinaryInputs(src=0x00, dst=0x01),
    BinaryInputs(src=0xFF, dst=0x7F),  # check overflow from positive minuend
    BinaryInputs(status_register=StatusRegister(x=True), src=0xFE, dst=0x7F),
    BinaryInputs(src=0x01, dst=0x80),  # check overflow from negative minuend
    BinaryInputs(status_register=StatusRegister(x=True), src=0x00, dst=0x80),
    BinaryInputs(src=0xF0, dst=0x10),  # check carry flag
    BinaryInputs(status_register=StatusRegister(x=True), src=0xEF, dst=0x10),
])

SUBX_WORD_INPUTS = WordInstructionInputs(inputs=[
    # check operation is something like subtraction
    BinaryInputs(src=0x3322, dst=0x5511),
    # check x flag influences result
    BinaryInputs(status_register=StatusRegister(x=True), src=0x3322, dst=0x5511),
    BinaryInputs(src=0xABAC_AB88, dst=0xCDCD_DEDA),  # check word operation on register
    BinaryInputs(src=0xD000, dst=0x0004),  # check negative flag
    BinaryInputs(status_register=StatusRegister(x=True), src=0xD000, dst=0x0003),
    # Check the z flag behaviour
    # (Cleared if the result is nonzero; unchanged otherwise).
    BinaryInputs(status_register=StatusRegister(z=True), src=0x0000, dst=0x0000),
    BinaryInputs(status_register=StatusRegister(z=True), src=0x0000, dst=0x0001),
    BinaryInputs(src=0x0000, dst=0x0000),
    BinaryInputs(src=0x0000, dst=0x0001),
    BinaryInputs(src=0xFF00, dst=0x7F00),  # check overflow from positive minuend
    BinaryInputs(status_register=StatusRegister(x=True), src=0xFEFF, dst=0x7F00),
    BinaryInputs(src=0x0001, dst=0x8000),  # check overflow from negative minuend
    BinaryInputs(status_register=StatusRegister(x=True), src=0x0000, dst=0x8000),
    BinaryInputs(src=0xF000, dst=0x1000),  # check carry flag
    BinaryInputs(
        status_register=StatusRegister(x=True),
        src=0xEFFF,
        dst=0x1000),
])

SUBX_LONG_INPUTS = LongInstructionInputs(inputs=[
    # check operation is something like subtraction
    BinaryInputs(src=0x5B5B_5B01, dst=0xB5AB_A5FE),
    # check x flag influences result
    BinaryInputs(
        status_register=StatusRegister(x=True),
        src=0x5B5B_5B01,
        dst=0xB5AB_A5FE
    ),
    BinaryInputs(src=0xD000_0000, dst=0x0003_0000),  # check negative flag
    BinaryInputs(status_register=StatusRegister(x=True), src=0xD000_0000, dst=0x0003_0000),
    BinaryInputs(src=0x0000_0000, dst=0x0000_0000),  # check trivial zero flag
    BinaryInputs(status_register=StatusRegister(x=True), src=0x0000_0000, dst=0x0000_0001),
    # Check the z flag behaviour
    # (Cleared if the result is nonzero; unchanged otherwise).
    BinaryInputs(status_register=StatusRegister(z=True), src=0x0000_0000, dst=0x0000_0000),
    BinaryInputs(status_register=StatusRegister(z=True), src=0x0000_0000, dst=0x0000_0001),
    BinaryInputs(src=0x0000_0000, dst=0x0000_0000),
    BinaryInputs(src=0x0000_0000, dst=0x0000_0001),
    # check overflow from positive minuend
    BinaryInputs(src=0xFF00_FF00, dst=0x7F00_DD00),
    BinaryInputs(
        status_register=StatusRegister(x=True),
        src=0XFF00_FEFF,
        dst=0x7F00_DD00
    ),
    # check overflow from negative minuend
    BinaryInputs(src=0x0001_0001, dst=0x8000_0000),
    BinaryInputs(
        status_register=StatusRegister(x=True),
        src=0x0001_0000,
        dst=0x8000_0000
    ),
    BinaryInputs(src=0xF000_0000, dst=0x1000_0000),  # check carry flag
    BinaryInputs(
        status_register=StatusRegister(x=True),
        src=0xF000_0000,
        dst=0x1000_0001),
])

ABCD_BYTE_INPUTS = ByteInstructionInputs(inputs=[
    # Check the operation looks like abcd
    BinaryInputs(src=0x11, dst=0x02),
    BinaryInputs(status_register=StatusRegister(x=True), src=0x11, dst=0x02),
    BinaryInputs(src=0x19, dst=0x72),
    BinaryInputs(status_register=StatusRegister(x=True), src=0x19, dst=0x72),
    BinaryInputs(src=0x22, dst=0x19),
    BinaryInputs(status_register=StatusRegister(x=True), src=0x22, dst=0x19),
    BinaryInputs(src=0x62, dst=0x19),
    BinaryInputs(status_register=StatusRegister(x=True), src=0x62, dst=0x19),
    BinaryInputs(src=0x01, dst=0x19),
    BinaryInputs(status_register=StatusRegister(x=True), src=0x01, dst=0x19),
    # Check that only the lower 8 bits are impacted
    BinaryInputs(src=0xFF, dst=0xEEBB_AA02),
    # Check the x flag behaviour
    BinaryInputs(status_register=StatusRegister(x=False), src=0xFF, dst=0x05),
    BinaryInputs(status_register=StatusRegister(x=True), src=0xFF, dst=0x01),
    # Check the n flag behaviour
    BinaryInputs(src=0x80, dst=0x42),
    BinaryInputs(src=0x00, dst=0xFF),
    BinaryInputs(status_register=StatusRegister(x=True), src=0x01, dst=0x7E),
    # Check the z flag behaviour
    # (Cleared if the result is nonzero; unchanged otherwise).
    BinaryInputs(status_register=StatusRegister(z=True), src=0x01, dst=0x99),
    BinaryInputs(status_register=StatusRegister(z=True), src=0x01, dst=0x98),
    BinaryInputs(src=0x01, dst=0x99),
    BinaryInputs(src=0x01, dst=0x98),
    # Check the carry flag behaviour
    BinaryInputs(status_register=StatusRegister(c=False), src=0x94, dst=0x05),
    BinaryInputs(status_register=StatusRegister(c=True), src=0x10, dst=0x00),
])

SBCD_BYTE_INPUTS = ByteInstructionInputs(inputs=[
    # Check the operation looks like abcd
    BinaryInputs(src=0x11, dst=0x02),
    BinaryInputs(status_register=StatusRegister(x=True), src=0x11, dst=0x02),
    BinaryInputs(src=0x19, dst=0x72),
    BinaryInputs(status_register=StatusRegister(x=True), src=0x19, dst=0x72),
    BinaryInputs(src=0x22, dst=0x19),
    BinaryInputs(status_register=StatusRegister(x=True), src=0x22, dst=0x19),
    BinaryInputs(src=0x62, dst=0x19),
    BinaryInputs(status_register=StatusRegister(x=True), src=0x62, dst=0x19),
    BinaryInputs(src=0x01, dst=0x19),
    BinaryInputs(status_register=StatusRegister(x=True), src=0x01, dst=0x19),
    BinaryInputs(src=0x17, dst=0x36),
    BinaryInputs(status_register=StatusRegister(x=True), src=0x17, dst=0x36),
    # Check that only the lower 8 bits are impacted
    BinaryInputs(src=0xFF, dst=0xEEBB_AA02),
    # Check the x flag behaviour
    BinaryInputs(status_register=StatusRegister(x=False), src=0xFF, dst=0x05),
    BinaryInputs(status_register=StatusRegister(x=True), src=0xFF, dst=0x01),
    # Check the n flag behaviour
    BinaryInputs(src=0x02, dst=0x89),
    BinaryInputs(src=0x02, dst=0x79),
    BinaryInputs(status_register=StatusRegister(x=True), src=0x00, dst=0x80),
    # Check the v flag behaviour
    BinaryInputs(src=0x29, dst=0x81),
    # Check the z flag behaviour
    # (Cleared if the result is nonzero; unchanged otherwise).
    BinaryInputs(status_register=StatusRegister(z=True), src=0x01, dst=0x01),
    BinaryInputs(status_register=StatusRegister(z=True), src=0x01, dst=0x02),
    BinaryInputs(src=0x01, dst=0x01),
    BinaryInputs(src=0x01, dst=0x02),
    # Check the carry flag behaviour
    BinaryInputs(status_register=StatusRegister(c=False), src=0x94, dst=0x05),
    BinaryInputs(status_register=StatusRegister(c=True), src=0x10, dst=0x20),
])

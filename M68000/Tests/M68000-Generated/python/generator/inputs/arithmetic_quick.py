"""
This module contains inputs for the quick instructions.
"""

from ..types.instruction_inputs import \
    BinaryInputs

from ..types.sized_instruction_inputs import \
    ByteInstructionInputs, \
    WordInstructionInputs, \
    LongInstructionInputs
from ..types.status_register import StatusRegister

ADDQ_BYTE_INPUTS = ByteInstructionInputs(inputs=[
    # Check the operation looks like addition
    BinaryInputs(src=0x1, dst=0x05),
    BinaryInputs(src=0x2, dst=0xF0),
    # Check byte operation on a register
    BinaryInputs(src=0x8, dst=0x1621_0FFC),
    # Check the x flag doesn't influence the result
    BinaryInputs(status_register=StatusRegister(x=True), src=0x8, dst=0x02),
    # Check the x flag
    BinaryInputs(status_register=StatusRegister(x=False), src=0x1, dst=0xFF),
    BinaryInputs(status_register=StatusRegister(x=True), src=0x6, dst=0x80),
    # Check the n flag
    BinaryInputs(status_register=StatusRegister(n=False), src=0x3, dst=0x7F),
    BinaryInputs(status_register=StatusRegister(n=True), src=0x2, dst=0x01),
    # Check the z flag
    BinaryInputs(status_register=StatusRegister(z=False), src=0x1, dst=0xFF),
    BinaryInputs(status_register=StatusRegister(z=True), src=0x2, dst=0x01),
    # Check the v flag
    BinaryInputs(status_register=StatusRegister(v=False), src=0x1, dst=0x7F),
    BinaryInputs(status_register=StatusRegister(v=True), src=0x6, dst=0x01),
    # Check the c flag
    BinaryInputs(status_register=StatusRegister(c=False), src=0x1, dst=0xFF),
    BinaryInputs(status_register=StatusRegister(c=True), src=0x6, dst=0x80),
])

ADDQ_WORD_INPUTS = WordInstructionInputs(inputs=[
    # Check the operation looks like addition
    BinaryInputs(src=0x1, dst=0x03FF),
    BinaryInputs(src=0x2, dst=0x8201),
    # Check word operation on a register
    BinaryInputs(src=0x8, dst=0x1620_FFFC),
    # Check the x flag doesn't influence the result
    BinaryInputs(status_register=StatusRegister(x=True), src=0x1, dst=0x03FF),
    # Check the x flag
    BinaryInputs(status_register=StatusRegister(x=False), src=0x1, dst=0xFFFF),
    BinaryInputs(status_register=StatusRegister(x=True), src=0x6, dst=0x8000),
    # Check the n flag
    BinaryInputs(status_register=StatusRegister(n=False), src=0x3, dst=0x7FFF),
    BinaryInputs(status_register=StatusRegister(n=True), src=0x2, dst=0x0001),
    # Check the z flag
    BinaryInputs(status_register=StatusRegister(z=False), src=0x2, dst=0xFFFE),
    BinaryInputs(status_register=StatusRegister(z=True), src=0x2, dst=0x0001),
    # Check the v flag
    BinaryInputs(status_register=StatusRegister(v=False), src=0x2, dst=0x7FFE),
    BinaryInputs(status_register=StatusRegister(v=True), src=0x4, dst=0x0001),
    # Check the c flag
    BinaryInputs(status_register=StatusRegister(c=False), src=0x1, dst=0xFFFF),
    BinaryInputs(status_register=StatusRegister(c=True), src=0x6, dst=0x8000),
])

ADDQ_LONG_INPUTS = LongInstructionInputs(inputs=[
    # Check the operation looks like addition
    BinaryInputs(src=0x1, dst=0x03FF_FFFF),
    BinaryInputs(src=0x2, dst=0x8201_FFFF),
    # Check long operation on a register
    BinaryInputs(src=0x8, dst=0x1220_FFFC),
    # Check the x flag doesn't influence the result
    BinaryInputs(status_register=StatusRegister(x=True), src=0x2, dst=0xABAB_010F),
    # Check the x flag
    BinaryInputs(status_register=StatusRegister(x=False), src=0x1, dst=0xFFFF_FFFF),
    BinaryInputs(status_register=StatusRegister(x=True), src=0x6, dst=0x8000_00000),
    # Check the n flag
    BinaryInputs(status_register=StatusRegister(n=False), src=0x3, dst=0x7FFF_FFFF),
    BinaryInputs(status_register=StatusRegister(n=True), src=0x2, dst=0x0000_0001),
    # Check the z flag
    BinaryInputs(status_register=StatusRegister(z=False), src=0x2, dst=0xFFFF_FFFE),
    BinaryInputs(status_register=StatusRegister(z=True), src=0x2, dst=0x0000_0001),
    # Check the v flag
    BinaryInputs(status_register=StatusRegister(v=False), src=0x2, dst=0x7FFF_FFFE),
    BinaryInputs(status_register=StatusRegister(v=True), src=0x4, dst=0x0000_0001),
    # Check the c flag
    BinaryInputs(status_register=StatusRegister(c=False), src=0x1, dst=0xFFFF_FFFF),
    BinaryInputs(status_register=StatusRegister(c=True), src=0x6, dst=0x8000_00000),
])

SUBQ_BYTE_INPUTS = ByteInstructionInputs(inputs=[
    # Check the operation looks like subtraction
    BinaryInputs(src=0x1, dst=0x05),
    BinaryInputs(src=0x2, dst=0xF0),
    # Check byte operation on a register
    BinaryInputs(src=0x8, dst=0x1621_0F00),
    # Check the x flag doesn't influence the result
    BinaryInputs(status_register=StatusRegister(x=True), src=0x8, dst=0x30),
    # Check the x flag
    BinaryInputs(status_register=StatusRegister(x=False), src=0x1, dst=0x00),
    BinaryInputs(status_register=StatusRegister(x=True), src=0x6, dst=0x07),
    # Check the n flag
    BinaryInputs(status_register=StatusRegister(n=False), src=0x1, dst=0x00),
    BinaryInputs(status_register=StatusRegister(n=True), src=0x2, dst=0x03),
    # Check the z flag
    BinaryInputs(status_register=StatusRegister(z=False), src=0x1, dst=0x01),
    BinaryInputs(status_register=StatusRegister(z=True), src=0x2, dst=0x03),
    # Check the v flag
    BinaryInputs(status_register=StatusRegister(v=False), src=0x1, dst=0x80),
    BinaryInputs(status_register=StatusRegister(v=True), src=0x6, dst=0x20),
    # Check the c flag
    BinaryInputs(status_register=StatusRegister(c=False), src=0x1, dst=0x00),
    BinaryInputs(status_register=StatusRegister(c=True), src=0x6, dst=0x07),
])

SUBQ_WORD_INPUTS = WordInstructionInputs(inputs=[
    # Check the operation looks like subtraction
    BinaryInputs(src=0x1, dst=0x03FF),
    BinaryInputs(src=0x2, dst=0xF0F0),
    # Check byte operation on a register
    BinaryInputs(src=0x8, dst=0x1620_0000),
    # Check the x flag doesn't influence the result
    BinaryInputs(status_register=StatusRegister(x=True), src=0x8, dst=0x3000),
    # Check the x flag
    BinaryInputs(status_register=StatusRegister(x=False), src=0x1, dst=0x0000),
    BinaryInputs(status_register=StatusRegister(x=True), src=0x6, dst=0x0700),
    # Check the n flag
    BinaryInputs(status_register=StatusRegister(n=False), src=0x1, dst=0x0000),
    BinaryInputs(status_register=StatusRegister(n=True), src=0x2, dst=0x0310),
    # Check the z flag
    BinaryInputs(status_register=StatusRegister(z=False), src=0x1, dst=0x0001),
    BinaryInputs(status_register=StatusRegister(z=True), src=0x2, dst=0x0310),
    # Check the v flag
    BinaryInputs(status_register=StatusRegister(v=False), src=0x1, dst=0x8000),
    BinaryInputs(status_register=StatusRegister(v=True), src=0x6, dst=0x2000),
    # Check the c flag
    BinaryInputs(status_register=StatusRegister(c=False), src=0x1, dst=0x0000),
    BinaryInputs(status_register=StatusRegister(c=True), src=0x6, dst=0x0700),
])

SUBQ_LONG_INPUTS = LongInstructionInputs(inputs=[
    # Check the operation looks like subtraction
    BinaryInputs(src=0x1, dst=0x03FF_FFFF),
    BinaryInputs(src=0x2, dst=0xF0F0_F0F0),
    # Check byte operation on a register
    BinaryInputs(src=0x8, dst=0x1620_0000),
    # Check the x flag doesn't influence the result
    BinaryInputs(status_register=StatusRegister(x=True), src=0x8, dst=0x3000_3000),
    # Check the x flag
    BinaryInputs(status_register=StatusRegister(x=False), src=0x1, dst=0x0000_0000),
    BinaryInputs(status_register=StatusRegister(x=True), src=0x6, dst=0x0700_0600),
    # Check the n flag
    BinaryInputs(status_register=StatusRegister(n=False), src=0x1, dst=0x0000_0000),
    BinaryInputs(status_register=StatusRegister(n=True), src=0x2, dst=0x0310_0130),
    # Check the z flag
    BinaryInputs(status_register=StatusRegister(z=False), src=0x1, dst=0x0000_0001),
    BinaryInputs(status_register=StatusRegister(z=True), src=0x2, dst=0x0310_3200),
    # Check the v flag
    BinaryInputs(status_register=StatusRegister(v=False), src=0x1, dst=0x8000_0000),
    BinaryInputs(status_register=StatusRegister(v=True), src=0x6, dst=0x2000_2000),
    # Check the c flag
    BinaryInputs(status_register=StatusRegister(c=False), src=0x1, dst=0x0000_0000),
    BinaryInputs(status_register=StatusRegister(c=True), src=0x6, dst=0x0700_9810),
])

MOVEQ_LONG_INPUTS = LongInstructionInputs(inputs=[
    # Test zero flag
    BinaryInputs(src=0x00, dst=0xA5A5_A5A5),
    # Test negative flag
    BinaryInputs(src=0x80, dst=0x0220_0330),
    BinaryInputs(src=0x7F, dst=0x0220_0330),
    # Test overflow and carry flags are cleared
    BinaryInputs(
        status_register=StatusRegister(c=True, v=True),
        src=0x01,
        dst=0x0110_0220
    )
])

"""
This module contains inputs for the bitwise instructions.
"""

from ..types.instruction_inputs import \
    BinaryInputs

from ..types.sized_instruction_inputs import \
    ByteInstructionInputs,\
    LongInstructionInputs

from ..types.status_register import StatusRegister

BITWISE_BYTE_INPUTS = ByteInstructionInputs(inputs=[
    # Check the operation looks like a bitwise operation and the zero flag gets set appropriately
    BinaryInputs(src=0, dst=0xF0), BinaryInputs(src=4, dst=0xF0),
    BinaryInputs(src=4, dst=0x0F),  # Check the outcome when the zero flag is previously set
    BinaryInputs(status_register=StatusRegister(z=True), src=0, dst=0xF0),
    BinaryInputs(status_register=StatusRegister(z=True), src=4, dst=0xF0),
    # Check modulo 8 on the shift parameter
    BinaryInputs(src=0xFF0F_FFF8, dst=0xF0), BinaryInputs(src=0xF0FF_FFFC, dst=0xF0),
    # Check the other condition codes aren't affected regardless of the result
    BinaryInputs(status_register=StatusRegister(x=True, n=True, v=True, c=True), src=0, dst=0xF0),
    BinaryInputs(status_register=StatusRegister(x=True, n=True, v=True, c=True), src=4, dst=0xF0)
])

BITWISE_LONG_INPUTS = LongInstructionInputs(inputs=[
    # Check the operation looks like a bitwise operation and the zero flag gets set appropriately
    BinaryInputs(src=0, dst=0xFF00_FF00), BinaryInputs(src=8, dst=0xFF00_FF00),
    BinaryInputs(src=16, dst=0xFF00_FF00), BinaryInputs(src=24, dst=0xFF00_FF00),
    BinaryInputs(src=0, dst=0x00FF_00FF), BinaryInputs(src=8, dst=0x00FF_00FF),
    BinaryInputs(src=16, dst=0x00FF_00FF), BinaryInputs(src=24, dst=0x00FF_00FF),
    # Check the outcome when the zero flag is previously set
    BinaryInputs(status_register=StatusRegister(z=True), src=0, dst=0xFF00_FF00),
    BinaryInputs(status_register=StatusRegister(z=True), src=8, dst=0xFF00_FF00),
    BinaryInputs(status_register=StatusRegister(z=True), src=16, dst=0xFF00_FF00),
    BinaryInputs(status_register=StatusRegister(z=True), src=24, dst=0xFF00_FF00),
    # Check modulo 32 on the shift parameter
    BinaryInputs(src=0xFF0F_FFE0, dst=0xFF00_FF00), BinaryInputs(src=0xF0FF_FFE8, dst=0xFF00_FF00),
    # Check the other condition codes aren't affected regardless of the result
    BinaryInputs(
        status_register=StatusRegister(x=True, n=True, v=True, c=True),
        src=0,
        dst=0xFF00_FF00),
    BinaryInputs(
        status_register=StatusRegister(x=True, n=True, v=True, c=True),
        src=8,
        dst=0xFF00_FF00)
])

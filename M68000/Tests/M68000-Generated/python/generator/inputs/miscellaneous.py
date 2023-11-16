"""
This module contains inputs for the miscellaneous instructions.
"""
import itertools

from ..status_register_data import \
    ALL_CONDITION_CODE_REGISTERS, \
    REDUCED_CONDITION_CODE_REGISTERS, \
    ALL_STATUS_REGISTERS, \
    REDUCED_STATUS_REGISTERS, \
    SUPERVISOR_STATUS_REGISTERS, \
    STACK_POINTERS, \
    USER_STACK_POINTERS
from ..types.instruction_inputs import \
    BinaryInputs, \
    SingleInputs, \
    StatusRegisterInputs
from ..types.sized_instruction_inputs import \
    ByteInstructionInputs, \
    WordInstructionInputs, \
    LongInstructionInputs
from ..types.status_register import StatusRegister

LOGICAL_OPERATION_CONDITION_CODE_REGISTER_INPUTS = ByteInstructionInputs(inputs=[
    BinaryInputs(src=src, dst=dst, status_register=status)
    for src, dst, status in itertools.product(
        [0xFF, 0xAA, 0x55, 0x00],
        [0x00],
        ALL_CONDITION_CODE_REGISTERS)
])

LOGICAL_TO_STATUS_REGISTER_INPUTS = WordInstructionInputs(inputs=[
    StatusRegisterInputs(src=src, ssp=usp, usp=ssp, status_register=status)
    for src, ssp, usp, status in itertools.product(
        [0xFFFF, 0xAAAA, 0x5555, 0x0000],
        USER_STACK_POINTERS,
        STACK_POINTERS,
        SUPERVISOR_STATUS_REGISTERS
    )
])

MOVE_TO_CONDITION_CODE_STATUS_REGISTER_INPUTS = WordInstructionInputs(inputs=[
    BinaryInputs(src=src, dst=dst, status_register=status)
    for src, dst, status in itertools.product(
        [0xFFAA, 0xFFCC, 0x00AA, 0x00BB],
        [0x00],
        REDUCED_CONDITION_CODE_REGISTERS
    )
])

MOVE_TO_STATUS_REGISTER_WORD_INPUTS = WordInstructionInputs(inputs=[
    StatusRegisterInputs(src=src, ssp=usp, usp=ssp, status_register=status)
    for src, ssp, usp, status in itertools.product(
        [0xFFFF, 0xAAAA, 0x5555, 0x0000],
        USER_STACK_POINTERS,
        STACK_POINTERS,
        REDUCED_STATUS_REGISTERS
    )
])

MOVE_FROM_STATUS_REGISTER_INPUTS = WordInstructionInputs(inputs=[
    BinaryInputs(src=0x0000, dst=0xAAAA_5555, status_register=status)
    for status in ALL_STATUS_REGISTERS
])

EXT_WORD_INPUTS = WordInstructionInputs(inputs=[
    SingleInputs(dst=dst, status_register=status)
    for dst, status in itertools.product([
        0x0080, 0x007F, 0x0000, 0x1181
    ], ALL_STATUS_REGISTERS)
])

EXT_LONG_INPUTS = LongInstructionInputs(inputs=[
    SingleInputs(dst=dst, status_register=status)
    for dst, status in itertools.product([
        0x0000_8000, 0x0000_7F00, 0x0000_0000, 0x0011_8100
    ], ALL_STATUS_REGISTERS)
])

SWAP_INPUTS = LongInstructionInputs(inputs=[
    SingleInputs(dst=dst, status_register=status)
    for dst, status in itertools.product([
        0x98AB_CDEF, 0x0000_CDEF, 0xDDDD_7777, 0x0000_0000
    ], ALL_STATUS_REGISTERS)
])

CHK_INPUTS = WordInstructionInputs(inputs=[
    BinaryInputs(src=src, dst=dst, status_register=status)
    for src, dst, status in itertools.product(
        [0x7000, 0x7002, 0x4001],
        [0x4000, 0x1000, 0x0000],
        [StatusRegister(n=True), StatusRegister(n=False)]
    )
])

STOP_INPUTS = WordInstructionInputs(inputs=[
    StatusRegisterInputs(src=src, ssp=usp, usp=ssp, status_register=status, stopped=True)
    for src, ssp, usp, status in itertools.product(
        [0xFFFF, 0xAAAA, 0x5555, 0x0000, 0x2001, 0x0001],
        USER_STACK_POINTERS,
        STACK_POINTERS,
        SUPERVISOR_STATUS_REGISTERS
    )
])

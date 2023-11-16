"""
This module contains functions to produce status register outputs
for common types of operation
"""
from ..types.instruction_inputs import InstructionInputs
from ..types.size import SizeCharacteristics
from ..types.status_register import StatusRegister


def sign_extend(size_characteristics: SizeCharacteristics, value: int) -> int:
    mask, msb_mask = size_characteristics.mask, \
                     size_characteristics.most_significant_bit_mask
    masked_value = value & mask
    return (masked_value ^ msb_mask) - msb_mask


def produce_arithmetic_status_register(
        size_characteristics: SizeCharacteristics,
        result: int,
        overflow: int,
        carry: int) -> StatusRegister:
    mask, msb_mask = size_characteristics.mask, \
                     size_characteristics.most_significant_bit_mask
    return StatusRegister(
        x=(carry & msb_mask) != 0,
        n=(result & msb_mask) != 0,
        z=(result & mask) == 0,
        v=(overflow & msb_mask) != 0,
        c=(carry & msb_mask) != 0,
    )


def produce_compare_status_register(
        size_characteristics: SizeCharacteristics,
        inputs: InstructionInputs,
        result: int,
        overflow: int,
        carry: int) -> StatusRegister:
    mask, msb_mask = size_characteristics.mask, \
                     size_characteristics.most_significant_bit_mask
    return StatusRegister(
        x=inputs.status_register.x,
        n=(result & msb_mask) != 0,
        z=(result & mask) == 0,
        v=(overflow & msb_mask) != 0,
        c=(carry & msb_mask) != 0,
    )


def produce_logic_status_register(
        size_characteristics: SizeCharacteristics,
        inputs: InstructionInputs,
        result: int) -> StatusRegister:
    mask, msb_mask = size_characteristics.mask, \
                     size_characteristics.most_significant_bit_mask
    return StatusRegister(
        x=inputs.status_register.x,
        n=(result & msb_mask) != 0,
        z=(result & mask) == 0,
        v=False,
        c=False
    )


def produce_multiprecision_status_register(
        size_characteristics: SizeCharacteristics,
        inputs: InstructionInputs,
        result: int,
        overflow: int,
        carry: int) -> StatusRegister:
    mask, msb_mask = size_characteristics.mask, \
                     size_characteristics.most_significant_bit_mask
    return StatusRegister(
        x=(carry & msb_mask) != 0,
        n=(result & msb_mask) != 0,
        z=inputs.status_register.z and (result & mask) == 0,
        v=(overflow & msb_mask) != 0,
        c=(carry & msb_mask) != 0,
    )


def produce_bit_status_register(
        inputs: InstructionInputs,
        test: int) -> StatusRegister:
    return StatusRegister(
        x=inputs.status_register.x,
        n=inputs.status_register.n,
        z=(test == 0),
        v=inputs.status_register.v,
        c=inputs.status_register.c
    )


def produce_divide_overflow_status_register(inputs: InstructionInputs) -> StatusRegister:
    return StatusRegister(
        x=inputs.status_register.x,
        n=inputs.status_register.n,
        z=inputs.status_register.z,
        v=True,
        c=False
    )

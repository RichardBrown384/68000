"""
This module contains functions that produce multiprecision
outputs from the given inputs for the specified size.
"""

from .preserve import \
    preserve_supervisor_state_and_upper_input_bits
from .shared import \
    produce_multiprecision_status_register
from ..types.instruction_inputs import \
    BinaryInputs
from ..types.instruction_outputs import InstructionOutputs
from ..types.size import \
    SizeCharacteristics


def __overflow_add(src: int, dst: int, result: int) -> int:
    return ~(dst ^ src) & (dst ^ result)


def __overflow_sub(src: int, dst: int, result: int) -> int:
    return (dst ^ src) & (dst ^ result)


def __carry(src: int, dst: int, result: int, overflow: int) -> int:
    return (dst ^ src) ^ result ^ overflow


def __carry_add(src: int, dst: int) -> int:
    return __carry(src, dst, dst + src, __overflow_add(src, dst, dst + src))


def __decimal_correction(carry: int) -> int:
    return (carry & 0x8888_8888) - ((carry & 0x8888_8888) >> 2)


def __addx(src: int, dst: int, x_bit: int) -> [int, int, int]:
    result = dst + src + x_bit
    overflow = __overflow_add(src, dst, result)
    carry = __carry(src, dst, result, overflow)
    return result, overflow, carry


def __subx(src: int, dst: int, x_bit: int) -> [int, int, int]:
    result = dst - src - x_bit
    overflow = __overflow_sub(src, dst, result)
    carry = __carry(src, dst, result, overflow)
    return result, overflow, carry


def __abcd(src: int, dst: int, x_bit: int) -> [int, int, int]:
    # Compute Binary Sum, Binary Carry
    binary_result = dst + src + x_bit
    binary_overflow = __overflow_add(src, dst, binary_result)
    binary_carry = __carry(src, dst, binary_result, binary_overflow)
    # Add the Decimal Correction factor to the Binary Sum
    decimal_correction = __decimal_correction(
        binary_carry |
        __carry_add(binary_result, 0x6666_6666)
    )
    result = binary_result + decimal_correction
    overflow = __overflow_add(binary_result, decimal_correction, result)
    carry = __carry(binary_result, decimal_correction, overflow, result) | binary_carry
    return result, overflow, carry


def __sbcd(src: int, dst: int, x_bit: int) -> [int, int, int]:
    # Compute Binary Difference, Binary Carry
    binary_difference = dst - src - x_bit
    binary_overflow = __overflow_sub(src, dst, binary_difference)
    binary_carry = __carry(src, dst, binary_difference, binary_overflow)
    # Subtract the Decimal Correction from the Binary Difference
    decimal_correction = __decimal_correction(binary_carry)
    result = binary_difference - decimal_correction
    overflow = __overflow_sub(decimal_correction, binary_difference, result)
    carry = __carry(decimal_correction, binary_difference, result, overflow) | binary_carry
    return result, overflow, carry


@preserve_supervisor_state_and_upper_input_bits
def produce_addx_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: BinaryInputs) -> InstructionOutputs:
    """Produces ADDX outputs for the given size."""
    x_bit = 1 if inputs.status_register.x else 0
    result, overflow, carry = __addx(inputs.src, inputs.dst, x_bit)
    return InstructionOutputs(
        dst=result,
        status_register=produce_multiprecision_status_register(
            size_characteristics, inputs, result, overflow, carry
        )
    )


@preserve_supervisor_state_and_upper_input_bits
def produce_subx_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: BinaryInputs) -> InstructionOutputs:
    """Produces SUBX outputs for the given size."""
    x_bit = 1 if inputs.status_register.x else 0
    result, overflow, carry = __subx(inputs.src, inputs.dst, x_bit)
    return InstructionOutputs(
        dst=result,
        status_register=produce_multiprecision_status_register(
            size_characteristics, inputs, result, overflow, carry
        )
    )


@preserve_supervisor_state_and_upper_input_bits
def produce_abcd_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: BinaryInputs) -> InstructionOutputs:
    """Produces ABCD outputs for the given size."""
    x_bit = 1 if inputs.status_register.x else 0
    result, overflow, carry = __abcd(inputs.src, inputs.dst, x_bit)
    return InstructionOutputs(
        dst=result,
        status_register=produce_multiprecision_status_register(
            size_characteristics, inputs, result, overflow, carry
        )
    )


@preserve_supervisor_state_and_upper_input_bits
def produce_sbcd_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: BinaryInputs) -> InstructionOutputs:
    """Produces SBCD outputs for the given size."""
    x_bit = 1 if inputs.status_register.x else 0
    result, overflow, carry = __sbcd(inputs.src, inputs.dst, x_bit)
    return InstructionOutputs(
        dst=result,
        status_register=produce_multiprecision_status_register(
            size_characteristics, inputs, result, overflow, carry
        )
    )

"""
This module contains functions that produce single operation outputs
from the given inputs for the specified size.
"""

from .preserve import \
    preserve_supervisor_state_and_upper_input_bits
from .shared import \
    produce_arithmetic_status_register, \
    produce_logic_status_register, \
    produce_multiprecision_status_register

from ..types.instruction_inputs import \
    SingleInputs, ConditionalInputs
from ..types.instruction_outputs import InstructionOutputs

from ..types.size import \
    SizeCharacteristics


def __negx(dst: int, x_bit: int):
    result = 0 - dst - x_bit
    overflow = dst & result
    carry = dst ^ result ^ overflow
    return result, overflow, carry


def __neg(dst: int):
    return __negx(dst, 0)


def __not(dst: int):
    return ~dst


def __nbcd(dst: int, x_bit: int):
    # Compute Binary Difference, Binary Carry, and Decimal Correction
    binary_difference = 0 - dst - x_bit
    binary_carry = dst ^ binary_difference ^ (dst & binary_difference)
    decimal_correction = (binary_carry & 0x8888_8888) - ((binary_carry & 0x8888_8888) >> 2)
    # The result is formed by subtracting the Decimal Correction (dc)
    # from the Binary Difference (bd)
    result = binary_difference - decimal_correction
    overflow = (binary_difference ^ decimal_correction) & (binary_difference ^ result)
    carry = (binary_difference ^ decimal_correction) ^ result ^ overflow
    # Final carry is or-ed with the binary carry
    return result, overflow, carry | binary_carry


def __scc(size_characteristics: SizeCharacteristics,
          inputs: ConditionalInputs) -> int:
    """Produces SCC outputs for the given size."""
    return size_characteristics.mask if inputs.test else 0


def __tas(dst: int) -> int:
    return dst | 0x80


@preserve_supervisor_state_and_upper_input_bits
def produce_negx_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: SingleInputs) -> InstructionOutputs:
    """Produces NEGX outputs for the given size."""
    x_bit = 1 if inputs.status_register.x else 0
    result, overflow, carry = __negx(inputs.dst, x_bit)
    return InstructionOutputs(
        dst=result,
        status_register=produce_multiprecision_status_register(
            size_characteristics, inputs, result, overflow, carry
        )
    )


@preserve_supervisor_state_and_upper_input_bits
def produce_clr_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: SingleInputs) -> InstructionOutputs:
    """Produces CLR outputs for the given size."""
    result = 0
    return InstructionOutputs(
        dst=result,
        status_register=produce_logic_status_register(
            size_characteristics, inputs, result
        )
    )


@preserve_supervisor_state_and_upper_input_bits
def produce_neg_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: SingleInputs) -> InstructionOutputs:
    """Produces NEG outputs for the given size."""
    result, overflow, carry = __neg(inputs.dst)
    return InstructionOutputs(
        dst=result,
        status_register=produce_arithmetic_status_register(
            size_characteristics, result, overflow, carry
        )
    )


@preserve_supervisor_state_and_upper_input_bits
def produce_not_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: SingleInputs) -> InstructionOutputs:
    """Produces NOT outputs for the given size."""
    result = __not(inputs.dst)
    return InstructionOutputs(
        dst=result,
        status_register=produce_logic_status_register(
            size_characteristics, inputs, result
        )
    )


@preserve_supervisor_state_and_upper_input_bits
def produce_nbcd_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: SingleInputs) -> InstructionOutputs:
    """Produces NBCD outputs for the given size."""
    x_bit = 1 if inputs.status_register.x else 0
    result, overflow, carry = __nbcd(inputs.dst, x_bit)
    return InstructionOutputs(
        dst=result,
        status_register=produce_multiprecision_status_register(
            size_characteristics, inputs, result, overflow, carry
        )
    )


@preserve_supervisor_state_and_upper_input_bits
def produce_tas_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: SingleInputs) -> InstructionOutputs:
    """Produces TAS outputs for the given size."""
    result = __tas(inputs.dst)
    return InstructionOutputs(
        dst=result,
        status_register=produce_logic_status_register(
            size_characteristics, inputs, inputs.dst
        )
    )


@preserve_supervisor_state_and_upper_input_bits
def produce_tst_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: SingleInputs) -> InstructionOutputs:
    """Produces TST outputs for the given size."""
    result = inputs.dst
    return InstructionOutputs(
        dst=result,
        status_register=produce_logic_status_register(
            size_characteristics, inputs, result
        )
    )


@preserve_supervisor_state_and_upper_input_bits
def produce_scc_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: ConditionalInputs) -> InstructionOutputs:
    """Produces SCC outputs for the given size."""
    return InstructionOutputs(
        dst=__scc(size_characteristics, inputs),
        status_register=inputs.status_register
    )

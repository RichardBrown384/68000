"""
This module contains functions that produce bitwise outputs
from the given inputs for the specified size.
"""

from .preserve import \
    preserve_supervisor_state_and_upper_input_bits
from .shared import produce_bit_status_register

from ..types.instruction_inputs import \
    BinaryInputs
from ..types.instruction_outputs import InstructionOutputs

from ..types.size import \
    SizeCharacteristics


@preserve_supervisor_state_and_upper_input_bits
def produce_bchg_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: BinaryInputs) -> InstructionOutputs:
    """Produces BCHG outputs for a given size."""
    bit = inputs.src % size_characteristics.bits
    mask = 1 << bit
    test = inputs.dst & mask
    result = inputs.dst ^ mask
    return InstructionOutputs(
        dst=result,
        status_register=produce_bit_status_register(inputs, test)
    )


@preserve_supervisor_state_and_upper_input_bits
def produce_bclr_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: BinaryInputs) -> InstructionOutputs:
    """Produces BCLR outputs for a given size."""
    bit = inputs.src % size_characteristics.bits
    mask = 1 << bit
    test = inputs.dst & mask
    result = inputs.dst & ~mask
    return InstructionOutputs(
        dst=result,
        status_register=produce_bit_status_register(inputs, test)
    )


@preserve_supervisor_state_and_upper_input_bits
def produce_bset_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: BinaryInputs) -> InstructionOutputs:
    """Produces BSET outputs for a given size."""
    bit = inputs.src % size_characteristics.bits
    mask = 1 << bit
    test = inputs.dst & mask
    result = inputs.dst | mask
    return InstructionOutputs(
        dst=result,
        status_register=produce_bit_status_register(inputs, test)
    )


@preserve_supervisor_state_and_upper_input_bits
def produce_btst_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: BinaryInputs) -> InstructionOutputs:
    """Produces TSTS outputs for a given size."""
    bit = inputs.src % size_characteristics.bits
    mask = 1 << bit
    test = inputs.dst & mask
    return InstructionOutputs(
        dst=inputs.dst,
        status_register=produce_bit_status_register(inputs, test)
    )

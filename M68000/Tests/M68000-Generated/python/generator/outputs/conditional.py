"""
This module contains functions that produce branch outputs
from the given inputs for the specified size.
"""
from .preserve import \
    preserve_supervisor_state_and_upper_input_bits, \
    preserve_supervisor_state
from ..types.instruction_inputs import ConditionalInputs
from ..types.instruction_outputs import InstructionOutputs
from ..types.size import SizeCharacteristics


@preserve_supervisor_state
def produce_bcc_outputs(
        _size_characteristics: SizeCharacteristics,
        inputs: ConditionalInputs) -> InstructionOutputs:
    """Produces BCC outputs for a given size."""
    return InstructionOutputs(
        dst=inputs.dst,
        status_register=inputs.status_register
    )


@preserve_supervisor_state_and_upper_input_bits
def produce_dbcc_outputs(
        _size_characteristics: SizeCharacteristics,
        inputs: ConditionalInputs) -> InstructionOutputs:
    """Produces DBCC outputs for a given size."""
    return InstructionOutputs(
        dst=inputs.dst if inputs.test else inputs.dst - 1,
        status_register=inputs.status_register
    )

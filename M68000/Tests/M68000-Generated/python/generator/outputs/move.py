"""
This module contains functions that produce move outputs
from the given inputs for the specified size.
"""

from .preserve import \
    preserve_supervisor_state_and_upper_input_bits, \
    preserve_supervisor_state
from .shared import produce_logic_status_register, sign_extend
from ..types.instruction_inputs import BinaryInputs
from ..types.instruction_outputs import InstructionOutputs
from ..types.size import SizeCharacteristics


@preserve_supervisor_state_and_upper_input_bits
def produce_move_outputs(size_characteristics: SizeCharacteristics,
                         inputs: BinaryInputs) -> InstructionOutputs:
    """Produces MOVE outputs for a given size."""
    result = inputs.src
    return InstructionOutputs(
        dst=result,
        status_register=produce_logic_status_register(
            size_characteristics, inputs, result
        )
    )


@preserve_supervisor_state
def produce_movea_outputs(size_characteristics: SizeCharacteristics,
                          inputs: BinaryInputs) -> InstructionOutputs:
    """Produces MOVEA outputs for a given size."""
    result = sign_extend(size_characteristics, inputs.src)
    return InstructionOutputs(
        dst=result,
        status_register=inputs.status_register
    )

"""
This module contains a decorator that can be applied to an output producer to perform
common adjustments on the supplied output. Namely, restore the supervisor portion of the
status register and adjust the result for the instruction size.
"""

import functools

from ..types.instruction_inputs import \
    InstructionInputs
from ..types.instruction_outputs import InstructionOutputs
from ..types.sized_instruction_test_file import InstructionOutputsProducer

from ..types.size import \
    SizeCharacteristics

from ..types.status_register import StatusRegister


def __merge_status_registers(
        from_input: StatusRegister,
        from_output: StatusRegister) -> StatusRegister:
    """
    Combines two status registers by taking the supervisor values from the input status register
    and the condition code register from the output status register

    :param from_input: The original status register for the binary operation
    :param from_output: The output status register with a valid condition code portion
    :return: the combined status register
    """
    return StatusRegister.combine(from_input, from_output)


def __merge_dst(mask: int, from_input: int, from_output: int) -> int:
    """
    Bitwise merges from_input and from_output according to the specified mask

    :param mask: The bits in then we wish to preserve
    :param from_input: The input value of the operation
    :param from_output: The output value of the operation
    :return: The merged result
    """
    return (~mask & from_input) + (mask & from_output)


def preserve_supervisor_state_and_upper_input_bits(
        func: InstructionOutputsProducer) -> InstructionOutputsProducer:
    """
    Takes the outputs from an operation and partially merges them with the input values.

    Usually when we perform an ALU operation we want to preserve the supervisor portion
    of the status register and the upper bits of the original input.
    (Because byte operations only operate on the lower 8-bits of a register and so forth)

    :param func: The instruction outputs producer to decorate
    :return: wrapper that merges the inputs and outputs
    """

    @functools.wraps(func)
    def wrapper(
            size_characteristics: SizeCharacteristics,
            inputs: InstructionInputs) -> InstructionOutputs:
        outputs = func(size_characteristics, inputs)
        return InstructionOutputs(
            dst=__merge_dst(size_characteristics.mask, inputs.dst, outputs.dst),
            status_register=__merge_status_registers(
                inputs.status_register,
                outputs.status_register
            )
        )

    return wrapper


def preserve_supervisor_state(func: InstructionOutputsProducer) -> InstructionOutputsProducer:
    """
    Takes the output status register and merges it with the input status register preserving
    the supervisor portion.

    :param func: The instruction outputs producer to decorate
    :return: wrapper that merges the inputs and outputs
    """

    @functools.wraps(func)
    def wrapper(
            size_characteristics: SizeCharacteristics,
            inputs: InstructionInputs) -> InstructionOutputs:
        outputs = func(size_characteristics, inputs)
        return InstructionOutputs(
            dst=outputs.dst,
            status_register=__merge_status_registers(
                inputs.status_register,
                outputs.status_register
            )
        )

    return wrapper

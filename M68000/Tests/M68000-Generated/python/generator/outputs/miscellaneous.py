"""
This module contains functions that produce miscellaneous outputs
from the given inputs for the specified size.
"""
from .preserve import preserve_supervisor_state_and_upper_input_bits, preserve_supervisor_state
from .shared import produce_logic_status_register
from ..types.address_modes.util.sign_extend import \
    sign_extend_word, \
    sign_extend_byte
from ..types.instruction_inputs import InstructionInputs
from ..types.instruction_outputs import InstructionOutputs
from ..types.size import SizeCharacteristics
from ..types.status_register import StatusRegister


def __and(src: int, status_register: StatusRegister) -> int:
    return src & status_register.as_int()


def __eor(src: int, status_register: StatusRegister) -> int:
    return src ^ status_register.as_int()


def __or(src: int, status_register: StatusRegister) -> int:
    return src | status_register.as_int()


def __swap(dst: int) -> int:
    return (dst << 16) + ((dst >> 16) & 0xFFFF)


def produce_andi_status_register_outputs(
        _size_characteristics: SizeCharacteristics,
        inputs: InstructionInputs) -> InstructionOutputs:
    """Produces ANDI status outputs."""
    result = __and(inputs.src, inputs.status_register)
    return InstructionOutputs(
        dst=result,
        status_register=StatusRegister.from_int(result))


def produce_eori_status_register_outputs(
        _size_characteristics: SizeCharacteristics,
        inputs: InstructionInputs) -> InstructionOutputs:
    """Produces EORI status outputs."""
    result = __eor(inputs.src, inputs.status_register)
    return InstructionOutputs(
        dst=result,
        status_register=StatusRegister.from_int(result))


def produce_ori_status_register_outputs(
        _size_characteristics: SizeCharacteristics,
        inputs: InstructionInputs) -> InstructionOutputs:
    """Produces OR status outputs."""
    result = __or(inputs.src, inputs.status_register)
    return InstructionOutputs(
        dst=result,
        status_register=StatusRegister.from_int(result))


@preserve_supervisor_state
def produce_andi_condition_code_register_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: InstructionInputs) -> InstructionOutputs:
    """Produces ANDI condition code register outputs."""
    return produce_andi_status_register_outputs(size_characteristics, inputs)


@preserve_supervisor_state
def produce_eori_condition_code_register_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: InstructionInputs) -> InstructionOutputs:
    """Produces EORI condition code register outputs."""
    return produce_eori_status_register_outputs(size_characteristics, inputs)


@preserve_supervisor_state
def produce_ori_condition_code_register_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: InstructionInputs) -> InstructionOutputs:
    """Produces ORI condition code register outputs."""
    return produce_ori_status_register_outputs(size_characteristics, inputs)


def produce_move_to_status_register_outputs(
        _size_characteristics: SizeCharacteristics,
        inputs: InstructionInputs) -> InstructionOutputs:
    """Produces MOVE to status register outputs."""
    return InstructionOutputs(
        dst=inputs.dst,
        status_register=StatusRegister.from_int(inputs.src))


@preserve_supervisor_state
def produce_move_to_condition_code_register_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: InstructionInputs) -> InstructionOutputs:
    """Produces MOVE to condition code register outputs."""
    return produce_move_to_status_register_outputs(size_characteristics, inputs)


@preserve_supervisor_state_and_upper_input_bits
def produce_move_from_status_register_outputs(
        _size_characteristics: SizeCharacteristics,
        inputs: InstructionInputs) -> InstructionOutputs:
    """Produces MOVE FROM SR outputs."""
    result = inputs.status_register.as_int()
    return InstructionOutputs(
        dst=result,
        status_register=inputs.status_register
    )


@preserve_supervisor_state_and_upper_input_bits
def produce_ext_word_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: InstructionInputs) -> InstructionOutputs:
    """Produces EXT.W outputs."""
    result = sign_extend_byte(inputs.dst)
    return InstructionOutputs(
        dst=result,
        status_register=produce_logic_status_register(
            size_characteristics, inputs, result)
    )


@preserve_supervisor_state_and_upper_input_bits
def produce_ext_long_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: InstructionInputs) -> InstructionOutputs:
    """Produces EXT.L outputs."""
    result = sign_extend_word(inputs.dst)
    return InstructionOutputs(
        dst=result,
        status_register=produce_logic_status_register(
            size_characteristics, inputs, result)
    )


@preserve_supervisor_state_and_upper_input_bits
def produce_swap_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: InstructionInputs) -> InstructionOutputs:
    """Produces SWAP outputs."""
    result = __swap(inputs.dst)
    return InstructionOutputs(
        dst=result,
        status_register=produce_logic_status_register(
            size_characteristics, inputs, result)
    )


@preserve_supervisor_state_and_upper_input_bits
def produce_chk_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: InstructionInputs) -> InstructionOutputs:
    """Produces CHK.W outputs."""
    return InstructionOutputs(
        dst=inputs.dst,
        status_register=inputs.status_register
    )

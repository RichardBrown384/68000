"""
This module contains functions that produce arithmetic and
logical outputs from the given inputs for the specified size.
"""

from .preserve import \
    preserve_supervisor_state_and_upper_input_bits, \
    preserve_supervisor_state
from .shared import \
    produce_arithmetic_status_register, \
    produce_logic_status_register, \
    produce_compare_status_register, \
    produce_divide_overflow_status_register
from .shared import sign_extend
from ..types.address_modes.util.sign_extend import \
    sign_extend_word, sign_extend_byte
from ..types.instruction_inputs import \
    BinaryInputs
from ..types.instruction_outputs import InstructionOutputs
from ..types.size import \
    SizeCharacteristics
from ..types.sized_instruction_inputs import \
    LONG_CHARACTERISTICS


def __add(src: int, dst: int) -> [int, int, int]:
    result = dst + src
    overflow = ~(dst ^ src) & (dst ^ result)
    carry = (dst ^ src) ^ result ^ overflow
    return result, overflow, carry


def __adda(size_characteristics: SizeCharacteristics, src: int, dst: int) -> int:
    return dst + sign_extend(size_characteristics, src)


def __sub(src: int, dst: int) -> [int, int, int]:
    result = dst - src
    overflow = (dst ^ src) & (dst ^ result)
    carry = (dst ^ src) ^ result ^ overflow
    return result, overflow, carry


def __suba(size_characteristics: SizeCharacteristics, src: int, dst: int) -> [int, int, int]:
    return __sub(sign_extend(size_characteristics, src), dst)


def __and(src: int, dst: int) -> int:
    return dst & src


def __eor(src: int, dst: int) -> int:
    return dst ^ src


def __or(src: int, dst: int) -> int:
    return dst | src


def __mulu(src: int, dst: int) -> int:
    return (dst & 0xFFFF) * (src & 0xFFFF)


def __muls(src: int, dst: int) -> int:
    return sign_extend_word(dst) * sign_extend_word(src)


@preserve_supervisor_state_and_upper_input_bits
def produce_add_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: BinaryInputs) -> InstructionOutputs:
    result, overflow, carry = __add(inputs.src, inputs.dst)
    return InstructionOutputs(
        dst=result,
        status_register=produce_arithmetic_status_register(
            size_characteristics, result, overflow, carry
        )
    )


@preserve_supervisor_state
def produce_adda_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: BinaryInputs) -> InstructionOutputs:
    result = __adda(size_characteristics, inputs.src, inputs.dst)
    return InstructionOutputs(
        dst=result,
        status_register=inputs.status_register
    )


@preserve_supervisor_state_and_upper_input_bits
def produce_sub_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: BinaryInputs) -> InstructionOutputs:
    result, overflow, carry = __sub(inputs.src, inputs.dst)
    return InstructionOutputs(
        dst=result,
        status_register=produce_arithmetic_status_register(
            size_characteristics, result, overflow, carry
        )
    )


@preserve_supervisor_state
def produce_suba_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: BinaryInputs) -> InstructionOutputs:
    result, *_ = __suba(size_characteristics, inputs.src, inputs.dst)
    return InstructionOutputs(
        dst=result,
        status_register=inputs.status_register
    )


@preserve_supervisor_state_and_upper_input_bits
def produce_cmp_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: BinaryInputs) -> InstructionOutputs:
    result, overflow, carry = __sub(inputs.src, inputs.dst)
    return InstructionOutputs(
        dst=inputs.dst,
        status_register=produce_compare_status_register(
            size_characteristics, inputs, result, overflow, carry
        )
    )


@preserve_supervisor_state
def produce_cmpa_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: BinaryInputs) -> InstructionOutputs:
    result, overflow, carry = __suba(size_characteristics, inputs.src, inputs.dst)
    return InstructionOutputs(
        dst=inputs.dst,
        status_register=produce_compare_status_register(
            LONG_CHARACTERISTICS, inputs, result, overflow, carry
        )
    )


@preserve_supervisor_state_and_upper_input_bits
def produce_and_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: BinaryInputs) -> InstructionOutputs:
    result = __and(inputs.src, inputs.dst)
    return InstructionOutputs(
        dst=result,
        status_register=produce_logic_status_register(
            size_characteristics, inputs, result
        )
    )


@preserve_supervisor_state_and_upper_input_bits
def produce_eor_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: BinaryInputs) -> InstructionOutputs:
    result = __eor(inputs.src, inputs.dst)
    return InstructionOutputs(
        dst=result,
        status_register=produce_logic_status_register(
            size_characteristics, inputs, result
        )
    )


@preserve_supervisor_state_and_upper_input_bits
def produce_or_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: BinaryInputs) -> InstructionOutputs:
    result = __or(inputs.src, inputs.dst)
    return InstructionOutputs(
        dst=result,
        status_register=produce_logic_status_register(
            size_characteristics, inputs, result
        )
    )


@preserve_supervisor_state
def produce_mulu_outputs(
        _size_characteristics: SizeCharacteristics,
        inputs: BinaryInputs) -> InstructionOutputs:
    result = __mulu(inputs.src, inputs.dst)
    return InstructionOutputs(
        dst=result,
        status_register=produce_logic_status_register(
            LONG_CHARACTERISTICS, inputs, result
        )
    )


@preserve_supervisor_state
def produce_muls_outputs(
        _size_characteristics: SizeCharacteristics,
        inputs: BinaryInputs) -> InstructionOutputs:
    result = __muls(inputs.src, inputs.dst)
    return InstructionOutputs(
        dst=result,
        status_register=produce_logic_status_register(
            LONG_CHARACTERISTICS, inputs, result
        )
    )


@preserve_supervisor_state
def produce_divu_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: BinaryInputs) -> InstructionOutputs:
    dividend = inputs.dst
    divisor = inputs.src & 0xFFFF
    assert divisor != 0
    quotient = dividend // divisor
    remainder = dividend % divisor

    if quotient >= 0x1_00_00:
        return InstructionOutputs(
            dst=dividend,
            status_register=produce_divide_overflow_status_register(inputs))

    result = (remainder << 16) + quotient
    return InstructionOutputs(
        dst=result,
        status_register=produce_logic_status_register(size_characteristics, inputs, result))


@preserve_supervisor_state
def produce_divs_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: BinaryInputs) -> InstructionOutputs:
    def is_negative_word(word):
        return word & 0x8000 != 0

    def is_negative_long(long):
        return long & 0x8000_0000 != 0

    def negate_word(word):
        return -word & 0xFFFF

    def negate_long(long):
        return -long & 0xFFFF_FFFF

    def abs_long(long):
        return negate_long(long) if is_negative_long(long) else long

    def abs_word(word):
        return negate_word(word) if is_negative_word(word) else word

    def is_less_than_or_equal_to_zero(word):
        return word == 0 or is_negative_word(word)

    signed_dividend = inputs.dst
    signed_divisor = inputs.src & 0xFFFF
    assert signed_divisor != 0

    absolute_dividend = abs_long(signed_dividend)
    absolute_divisor = abs_word(signed_divisor)

    absolute_quotient = absolute_dividend // absolute_divisor
    absolute_remainder = absolute_dividend % absolute_divisor

    if absolute_quotient >= 0x1_00_00:
        return InstructionOutputs(
            dst=signed_dividend,
            status_register=produce_divide_overflow_status_register(inputs))

    opposing_signs = is_negative_long(signed_dividend) ^ is_negative_word(signed_divisor)

    quotient = negate_word(absolute_quotient) if \
        opposing_signs \
        else absolute_quotient
    remainder = negate_word(absolute_remainder) \
        if is_negative_long(signed_dividend) \
        else absolute_remainder

    if not opposing_signs and is_negative_word(quotient) or \
            opposing_signs and not is_less_than_or_equal_to_zero(quotient):
        return InstructionOutputs(
            dst=signed_dividend,
            status_register=produce_divide_overflow_status_register(inputs))

    result = (remainder << 16) + quotient
    return InstructionOutputs(
        dst=result,
        status_register=produce_logic_status_register(size_characteristics, inputs, result))


@preserve_supervisor_state_and_upper_input_bits
def produce_moveq_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: BinaryInputs) -> InstructionOutputs:
    result = sign_extend_byte(inputs.src)
    return InstructionOutputs(
        dst=result,
        status_register=produce_logic_status_register(
            size_characteristics, inputs, result
        )
    )

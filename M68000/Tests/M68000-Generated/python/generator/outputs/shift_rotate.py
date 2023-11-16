"""
This module contains functions that produce shift and
rotate outputs from the given inputs for the specified size.
"""

from .preserve import \
    preserve_supervisor_state_and_upper_input_bits
from .shared import sign_extend

from ..types.instruction_inputs import \
    BinaryInputs
from ..types.instruction_outputs import InstructionOutputs

from ..types.size import SizeCharacteristics

from ..types.status_register import StatusRegister


def __clamp(value: int, maximum: int) -> int:
    return value if value < maximum else maximum


def __asr(size_characteristics: SizeCharacteristics,
          shift: int,
          value: int) -> [int, int]:
    max_shift = size_characteristics.bits - 1

    sign_extended = sign_extend(size_characteristics, value)

    result_shift = __clamp(shift, max_shift)
    carry_shift = __clamp(shift - 1, max_shift)

    result = sign_extended >> result_shift
    carry = sign_extended >> carry_shift if shift else 0
    return result, carry


def __lsr(size_characteristics: SizeCharacteristics,
          shift: int,
          value: int) -> [int, int]:
    max_shift = size_characteristics.bits
    mask = size_characteristics.mask

    masked_value = value & mask

    result_shift = __clamp(shift, max_shift)
    carry_shift = __clamp(shift - 1, max_shift)

    result = masked_value >> result_shift
    carry = masked_value >> carry_shift if shift else 0
    return result, carry


def __rotate_extended_right(
        size_characteristics: SizeCharacteristics,
        shift: int,
        x_bit: int,
        value: int) -> int:
    max_shift = size_characteristics.bits
    mask = size_characteristics.mask

    rotate_shift = shift % (max_shift + 1)
    if rotate_shift:
        extended = (x_bit << max_shift) + (value & mask)
        rotated = (extended >> rotate_shift) + \
                  (extended << (max_shift + 1 - rotate_shift))
        return rotated

    return value


def __roxr(size_characteristics: SizeCharacteristics,
           shift: int,
           x_bit: int,
           value: int) -> [int, int]:
    result = __rotate_extended_right(
        size_characteristics,
        shift,
        x_bit,
        value
    )
    carry = __rotate_extended_right(
        size_characteristics,
        shift - 1,
        x_bit,
        value
    ) if shift else x_bit

    return result, carry


def __rotate_right(size_characteristics: SizeCharacteristics,
                   shift: int,
                   value: int) -> int:
    max_shift = size_characteristics.bits
    mask = size_characteristics.mask

    masked_value = value & mask
    rotate_shift = shift % max_shift

    if rotate_shift:
        return (masked_value >> rotate_shift) + \
               (masked_value << (max_shift - rotate_shift))

    return value


def __ror(size_characteristics: SizeCharacteristics,
          shift: int,
          value: int) -> [int, int]:
    result = __rotate_right(size_characteristics, shift, value)
    carry = __rotate_right(
        size_characteristics,
        shift - 1,
        value
    ) if shift else 0

    return result, carry


def __asl_overflow(size_characteristics: SizeCharacteristics,
                   shift: int,
                   value: int) -> int:
    max_shift = size_characteristics.bits
    mask = size_characteristics.mask

    if shift:
        overflow_shift = __clamp(shift, max_shift)
        changes = value ^ (value << 1)
        used_changes = (changes & mask) >> (max_shift - overflow_shift)
        return 1 if used_changes else 0
    return 0


def __asl(size_characteristics: SizeCharacteristics,
          shift: int,
          value: int) -> [int, int, int]:
    result = value << shift
    overflow = __asl_overflow(size_characteristics, shift, value)
    carry = value << shift - 1 if shift else 0
    return result, overflow, carry


def __lsl(shift: int,
          value: int) -> [int, int]:
    result = value << shift
    carry = value << shift - 1 if shift else 0
    return result, carry


def __rotate_extended_left(
        size_characteristics: SizeCharacteristics,
        shift: int,
        x_bit: int,
        value: int) -> int:
    max_shift = size_characteristics.bits
    mask = size_characteristics.mask

    rotate_shift = shift % (max_shift + 1)
    if rotate_shift:
        extended = (x_bit << max_shift) + (value & mask)
        rotated = (extended << rotate_shift) + \
                  (extended >> (max_shift + 1 - rotate_shift))
        return rotated

    return value


def __roxl(size_characteristics: SizeCharacteristics,
           shift: int,
           x_bit: int,
           value: int) -> [int, int]:
    max_shift = size_characteristics.bits
    result = __rotate_extended_left(
        size_characteristics,
        shift,
        x_bit,
        value
    )
    carry = __rotate_extended_left(
        size_characteristics,
        shift - 1,
        x_bit,
        value
    ) if shift else x_bit << (max_shift - 1)

    return result, carry


def __rotate_left(size_characteristics: SizeCharacteristics,
                  shift: int,
                  value: int) -> int:
    max_shift = size_characteristics.bits
    mask = size_characteristics.mask

    masked_value = value & mask
    rotate_shift = shift % max_shift

    if rotate_shift:
        return (masked_value << rotate_shift) + \
               (masked_value >> (max_shift - rotate_shift))

    return value


def __rol(size_characteristics: SizeCharacteristics,
          shift: int,
          value: int) -> [int, int]:
    result = __rotate_left(size_characteristics, shift, value)
    carry = __rotate_left(
        size_characteristics,
        shift - 1,
        value
    ) if shift else 0

    return result, carry


@preserve_supervisor_state_and_upper_input_bits
def produce_asr_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: BinaryInputs) -> InstructionOutputs:
    # Reduce the shift modulo 64 for register shifts, the other types
    # produce shifts in the range 1 to 8 so this should be safe
    shift = inputs.src & 0x3F
    result, carry = __asr(size_characteristics, shift, inputs.dst)

    mask = size_characteristics.mask
    msb = size_characteristics.most_significant_bit_mask

    return InstructionOutputs(
        dst=result,
        status_register=StatusRegister(
            x=(carry & 0x01) != 0 if shift else inputs.status_register.x,
            n=(result & msb) != 0,
            z=(result & mask) == 0,
            v=False,
            c=(carry & 0x01) != 0
        )
    )


@preserve_supervisor_state_and_upper_input_bits
def produce_lsr_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: BinaryInputs) -> InstructionOutputs:
    # Reduce the shift modulo 64 for register shifts, the other types
    # produce shifts in the range 1 to 8 so this should be safe
    shift = inputs.src & 0x3F
    result, carry = __lsr(size_characteristics, shift, inputs.dst)

    mask = size_characteristics.mask
    msb = size_characteristics.most_significant_bit_mask

    return InstructionOutputs(
        dst=result,
        status_register=StatusRegister(
            x=(carry & 0x01) != 0 if shift else inputs.status_register.x,
            n=(result & msb) != 0,
            z=(result & mask) == 0,
            v=False,
            c=(carry & 0x01) != 0
        )
    )


@preserve_supervisor_state_and_upper_input_bits
def produce_roxr_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: BinaryInputs) -> InstructionOutputs:
    # Reduce the shift modulo 64 for register shifts, the other types
    # produce shifts in the range 1 to 8 so this should be safe
    shift = inputs.src & 0x3F
    x_bit = 1 if inputs.status_register.x else 0

    result, carry = __roxr(size_characteristics, shift, x_bit, inputs.dst)

    mask = size_characteristics.mask
    msb = size_characteristics.most_significant_bit_mask

    return InstructionOutputs(
        dst=result,
        status_register=StatusRegister(
            x=(carry & 0x01) != 0,
            n=(result & msb) != 0,
            z=(result & mask) == 0,
            v=False,
            c=(carry & 0x01) != 0
        )
    )


@preserve_supervisor_state_and_upper_input_bits
def produce_ror_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: BinaryInputs) -> InstructionOutputs:
    # Reduce the shift modulo 64 for register shifts, the other types
    # produce shifts in the range 1 to 8 so this should be safe
    shift = inputs.src & 0x3F
    result, carry = __ror(size_characteristics, shift, inputs.dst)

    mask = size_characteristics.mask
    msb = size_characteristics.most_significant_bit_mask

    return InstructionOutputs(
        dst=result,
        status_register=StatusRegister(
            x=inputs.status_register.x,
            n=(result & msb) != 0,
            z=(result & mask) == 0,
            v=False,
            c=(carry & 0x01) != 0
        )
    )


@preserve_supervisor_state_and_upper_input_bits
def produce_asl_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: BinaryInputs) -> InstructionOutputs:
    # Reduce the shift modulo 64 for register shifts, the other types
    # produce shifts in the range 1 to 8 so this should be safe
    shift = inputs.src & 0x3F
    result, overflow, carry = __asl(size_characteristics, shift, inputs.dst)

    mask = size_characteristics.mask
    msb = size_characteristics.most_significant_bit_mask

    return InstructionOutputs(
        dst=result,
        status_register=StatusRegister(
            x=(carry & msb) != 0 if shift else inputs.status_register.x,
            n=(result & msb) != 0,
            z=(result & mask) == 0,
            v=(overflow & 0x1) != 0,
            c=(carry & msb) != 0
        )
    )


@preserve_supervisor_state_and_upper_input_bits
def produce_lsl_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: BinaryInputs) -> InstructionOutputs:
    # Reduce the shift modulo 64 for register shifts, the other types
    # produce shifts in the range 1 to 8 so this should be safe
    shift = inputs.src & 0x3F
    result, carry = __lsl(shift, inputs.dst)

    mask = size_characteristics.mask
    msb = size_characteristics.most_significant_bit_mask

    return InstructionOutputs(
        dst=result,
        status_register=StatusRegister(
            x=(carry & msb) != 0 if shift else inputs.status_register.x,
            n=(result & msb) != 0,
            z=(result & mask) == 0,
            v=False,
            c=(carry & msb) != 0
        )
    )


@preserve_supervisor_state_and_upper_input_bits
def produce_roxl_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: BinaryInputs) -> InstructionOutputs:
    # Reduce the shift modulo 64 for register shifts, the other types
    # produce shifts in the range 1 to 8 so this should be safe
    shift = inputs.src & 0x3F
    x_bit = 1 if inputs.status_register.x else 0

    result, carry = __roxl(size_characteristics, shift, x_bit, inputs.dst)

    mask = size_characteristics.mask
    msb = size_characteristics.most_significant_bit_mask

    return InstructionOutputs(
        dst=result,
        status_register=StatusRegister(
            x=(carry & msb) != 0,
            n=(result & msb) != 0,
            z=(result & mask) == 0,
            v=False,
            c=(carry & msb) != 0
        )
    )


@preserve_supervisor_state_and_upper_input_bits
def produce_rol_outputs(
        size_characteristics: SizeCharacteristics,
        inputs: BinaryInputs) -> InstructionOutputs:
    # Reduce the shift modulo 64 for register shifts, the other types
    # produce shifts in the range 1 to 8 so this should be safe
    shift = inputs.src & 0x3F
    result, carry = __rol(size_characteristics, shift, inputs.dst)

    mask = size_characteristics.mask
    msb = size_characteristics.most_significant_bit_mask

    return InstructionOutputs(
        dst=result,
        status_register=StatusRegister(
            x=inputs.status_register.x,
            n=(result & msb) != 0,
            z=(result & mask) == 0,
            v=False,
            c=(carry & msb) != 0
        )
    )

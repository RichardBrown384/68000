"""
This module contains test file descriptions for the standard
arithmetic instructions.
"""

from typing import List

from ..address_mode_data.arithmetic import \
    BINARY_DATA_REGISTER_TO_DATA_REGISTER, \
    BINARY_ADDRESS_REGISTER_TO_DATA_REGISTER, \
    BINARY_MEMORY_TO_DATA_REGISTER, \
    BINARY_IMMEDIATE_TO_DATA_REGISTER, \
    BINARY_DATA_REGISTER_TO_MEMORY, \
    BINARY_DATA_REGISTER_TO_ADDRESS_REGISTER, \
    BINARY_ADDRESS_REGISTER_TO_ADDRESS_REGISTER, \
    BINARY_IMMEDIATE_TO_ADDRESS_REGISTER, \
    BINARY_MEMORY_TO_ADDRESS_REGISTER
from ..inputs.arithmetic import \
    ADD_BYTE_INPUTS, ADD_WORD_INPUTS, ADD_LONG_INPUTS, \
    SUB_BYTE_INPUTS, SUB_WORD_INPUTS, SUB_LONG_INPUTS, \
    CMP_BYTE_INPUTS, CMP_WORD_INPUTS, CMP_LONG_INPUTS, \
    AND_BYTE_INPUTS, AND_WORD_INPUTS, AND_LONG_INPUTS, \
    OR_BYTE_INPUTS, OR_WORD_INPUTS, OR_LONG_INPUTS, \
    EOR_BYTE_INPUTS, EOR_WORD_INPUTS, EOR_LONG_INPUTS, \
    MULU_WORD_INPUTS, \
    DIVU_WORD_INPUTS
from ..outputs.arithmetic import \
    produce_add_outputs, \
    produce_adda_outputs, \
    produce_sub_outputs, \
    produce_suba_outputs, \
    produce_cmp_outputs, \
    produce_cmpa_outputs, \
    produce_and_outputs, \
    produce_or_outputs, \
    produce_eor_outputs, \
    produce_mulu_outputs, \
    produce_muls_outputs, \
    produce_divu_outputs, \
    produce_divs_outputs
from ..types.cycles import \
    takes_n_cycles, \
    takes_n_cycles_plus_destination, \
    takes_n_cycles_plus_source
from ..types.sized_instruction_test_file import SizedInstructionTestFile, ModesAndCycles


def __logic_modes_and_cycles(
        memory_to_register: int = 0,
        register_to_register: int = 0,
        register_to_memory: int = 0) -> List[ModesAndCycles]:
    return [
        ModesAndCycles(address_modes=[
            BINARY_DATA_REGISTER_TO_DATA_REGISTER,
        ], cycles=takes_n_cycles(register_to_register)),
        ModesAndCycles(address_modes=[
            BINARY_IMMEDIATE_TO_DATA_REGISTER
        ], cycles=takes_n_cycles_plus_source(register_to_register)),
        ModesAndCycles(address_modes=[
            BINARY_MEMORY_TO_DATA_REGISTER,
        ], cycles=takes_n_cycles_plus_source(memory_to_register)),
        ModesAndCycles(address_modes=[
            BINARY_DATA_REGISTER_TO_MEMORY,
        ], cycles=takes_n_cycles_plus_destination(register_to_memory)),
    ]


def __arithmetic_modes_and_cycles(
        memory_to_register: int = 0,
        register_to_register: int = 0,
        register_to_memory: int = 0) -> List[ModesAndCycles]:
    return [
        ModesAndCycles(address_modes=[
            BINARY_DATA_REGISTER_TO_DATA_REGISTER,
            BINARY_ADDRESS_REGISTER_TO_DATA_REGISTER
        ], cycles=takes_n_cycles(register_to_register)),
        ModesAndCycles(address_modes=[
            BINARY_IMMEDIATE_TO_DATA_REGISTER
        ], cycles=takes_n_cycles_plus_source(register_to_register)),
        ModesAndCycles(address_modes=[
            BINARY_MEMORY_TO_DATA_REGISTER,
        ], cycles=takes_n_cycles_plus_source(memory_to_register)),
        ModesAndCycles(address_modes=[
            BINARY_DATA_REGISTER_TO_MEMORY,
        ], cycles=takes_n_cycles_plus_destination(register_to_memory)),
    ]


def __address_arithmetic_modes_and_cycles(
        memory_to_register: int = 0,
        register_to_register: int = 0) -> List[ModesAndCycles]:
    return [
        ModesAndCycles(address_modes=[
            BINARY_DATA_REGISTER_TO_ADDRESS_REGISTER,
            BINARY_ADDRESS_REGISTER_TO_ADDRESS_REGISTER
        ], cycles=takes_n_cycles(register_to_register)),
        ModesAndCycles(address_modes=[
            BINARY_IMMEDIATE_TO_ADDRESS_REGISTER
        ], cycles=takes_n_cycles_plus_source(register_to_register)),
        ModesAndCycles(address_modes=[
            BINARY_MEMORY_TO_ADDRESS_REGISTER,
        ], cycles=takes_n_cycles_plus_source(memory_to_register))
    ]


def __cmp_modes_and_cycles(
        memory_to_register: int = 0,
        register_to_register: int = 0) -> List[ModesAndCycles]:
    return [
        ModesAndCycles(address_modes=[
            BINARY_DATA_REGISTER_TO_DATA_REGISTER,
        ], cycles=takes_n_cycles(register_to_register)),
        ModesAndCycles(address_modes=[
            BINARY_MEMORY_TO_DATA_REGISTER,
            BINARY_IMMEDIATE_TO_DATA_REGISTER,
        ], cycles=takes_n_cycles_plus_source(memory_to_register))
    ]


def __eor_modes_and_cycles(
        register_to_register: int = 0,
        register_to_memory: int = 0) -> List[ModesAndCycles]:
    return [
        ModesAndCycles(address_modes=[
            BINARY_DATA_REGISTER_TO_DATA_REGISTER
        ], cycles=takes_n_cycles(register_to_register)),
        ModesAndCycles(address_modes=[
            BINARY_DATA_REGISTER_TO_MEMORY,
        ], cycles=takes_n_cycles_plus_destination(register_to_memory)),
    ]


def bit_count_word(word):
    return (word & 0xFFFF).bit_count()


def __mulu_cycles(source, _destination, inputs):
    return source + 38 + 2 * bit_count_word(inputs.src)


def __muls_cycles(source, _destination, inputs):
    return source + 38 + 2 * bit_count_word(inputs.src ^ (inputs.src << 1))


def __divu_cycles(source, _destination, inputs) -> int:
    cycles = source + 2 * 2  # DVUR1 + DVUM2
    dividend = inputs.dst
    divisor = inputs.src & 0xFFFF
    if divisor == 0:
        # Divide by zero exception
        return cycles + 32
    cycles += 1 * 2  # DVUM3
    if dividend // divisor >= 0x1_00_00:
        # Overflow
        cycles += 2 * 2  # DVUM4 + DVUMA
        return cycles
    aligned_divisor = divisor << 16
    for _ in range(15):
        cycles += 2 * 2  # DVUM5/6 + DVUM7/8
        previous = dividend
        dividend <<= 1
        if previous & 0x8000_0000:
            dividend -= aligned_divisor
        elif dividend >= aligned_divisor:
            dividend -= aligned_divisor
            cycles += 1 * 2  # DVUMB
        else:
            cycles += 2 * 2  # DVUMB + DVUME
    # DVUM5/6 + DVUM7/8 + DVUM9/C + DVUMD/F + DVUM0
    return cycles + 2 * 5


def __divs_cycles(source, _destination, inputs) -> int:
    cycles = source + 2 * 2  # DVS01, DVS03
    dividend = inputs.dst
    divisor = inputs.src & 0xFFFF
    if divisor == 0:
        # Divide by zero exception
        return cycles + 32
    sign_bit_dividend = dividend & 0x8000_0000 != 0
    sign_bit_divisor = divisor & 0x8000 != 0
    if sign_bit_dividend:
        cycles += 5 * 2  # DVS04/5, DVS06, DVS10, DVS11, DVS08
    else:
        cycles += 4 * 2  # DVS04/5, DVS06, DVS07, DVS08,
    abs_dividend = -dividend & 0xFFFF_FFFF if sign_bit_dividend else dividend
    abs_divisor = -divisor & 0xFFFF if sign_bit_divisor else divisor
    if abs_dividend // abs_divisor >= 0x1_00_00:
        cycles += 2 * 2  # DVUMZ, DVUMA
        return cycles
    aligned_divisor = abs_divisor << 16
    for _ in range(15):
        cycles += 3 * 2  # DVS09/A DVS0C, DVS0D
        abs_dividend <<= 1
        if abs_dividend >= aligned_divisor:
            abs_dividend -= aligned_divisor
        else:
            cycles += 2  # DVS0F
    cycles += 5 * 2  # DVS09/A, DVS0C, DVS0E, DVS12/13, DVS14
    if sign_bit_divisor:
        # DVS15, DVS1D, DVS1F, DVS20
        # DVS15, DVS1D, DVS1E, DVS1C
        # DVS15, DVS1D, DVS1E, DVUM4
        cycles += 4 * 2
    elif sign_bit_dividend:
        # DVS15, DVS16, DVS1A, DVS1B, DVS1C
        # DVS15, DVS16, DVS1A, DVS1B, DVUM4
        cycles += 5 * 2
    else:
        # DVS15, DVS16, DVS17
        cycles += 3 * 2
    # LEAA2 or DVUMA
    return cycles + 1 * 2


ADD_BYTE = SizedInstructionTestFile(
    instruction='ADD.B',
    name='add_byte',
    inputs=ADD_BYTE_INPUTS,
    outputs_producer=produce_add_outputs,
    modes=__logic_modes_and_cycles(
        memory_to_register=4,
        register_to_register=4,
        register_to_memory=8)
)

ADD_WORD = SizedInstructionTestFile(
    instruction='ADD.W',
    name='add_word',
    inputs=ADD_WORD_INPUTS,
    outputs_producer=produce_add_outputs,
    modes=__arithmetic_modes_and_cycles(
        memory_to_register=4,
        register_to_register=4,
        register_to_memory=8)
)

ADD_LONG = SizedInstructionTestFile(
    instruction='ADD.L',
    name='add_long',
    inputs=ADD_LONG_INPUTS,
    outputs_producer=produce_add_outputs,
    modes=__arithmetic_modes_and_cycles(
        memory_to_register=6,
        register_to_register=8,
        register_to_memory=12)
)

ADDA_WORD = SizedInstructionTestFile(
    instruction='ADDA.W',
    name='adda_word',
    inputs=ADD_WORD_INPUTS,
    outputs_producer=produce_adda_outputs,
    modes=__address_arithmetic_modes_and_cycles(
        memory_to_register=8,
        register_to_register=8)
)

ADDA_LONG = SizedInstructionTestFile(
    instruction='ADDA.L',
    name='adda_long',
    inputs=ADD_LONG_INPUTS,
    outputs_producer=produce_adda_outputs,
    modes=__address_arithmetic_modes_and_cycles(
        memory_to_register=6,
        register_to_register=8)
)

SUB_BYTE = SizedInstructionTestFile(
    instruction='SUB.B',
    name='sub_byte',
    inputs=SUB_BYTE_INPUTS,
    outputs_producer=produce_sub_outputs,
    modes=__logic_modes_and_cycles(
        memory_to_register=4,
        register_to_register=4,
        register_to_memory=8)
)

SUB_WORD = SizedInstructionTestFile(
    instruction='SUB.W',
    name='sub_word',
    inputs=SUB_WORD_INPUTS,
    outputs_producer=produce_sub_outputs,
    modes=__arithmetic_modes_and_cycles(
        memory_to_register=4,
        register_to_register=4,
        register_to_memory=8)
)

SUB_LONG = SizedInstructionTestFile(
    instruction='SUB.L',
    name='sub_long',
    inputs=SUB_LONG_INPUTS,
    outputs_producer=produce_sub_outputs,
    modes=__arithmetic_modes_and_cycles(
        memory_to_register=6,
        register_to_register=8,
        register_to_memory=12)
)

SUBA_WORD = SizedInstructionTestFile(
    instruction='SUBA.W',
    name='suba_word',
    inputs=SUB_WORD_INPUTS,
    outputs_producer=produce_suba_outputs,
    modes=__address_arithmetic_modes_and_cycles(
        memory_to_register=8,
        register_to_register=8)
)

SUBA_LONG = SizedInstructionTestFile(
    instruction='SUBA.L',
    name='suba_long',
    inputs=SUB_LONG_INPUTS,
    outputs_producer=produce_suba_outputs,
    modes=__address_arithmetic_modes_and_cycles(
        memory_to_register=6,
        register_to_register=8)
)

CMP_BYTE = SizedInstructionTestFile(
    instruction='CMP.B',
    name='cmp_byte',
    inputs=CMP_BYTE_INPUTS,
    outputs_producer=produce_cmp_outputs,
    modes=__cmp_modes_and_cycles(
        memory_to_register=4,
        register_to_register=4)
)

CMP_WORD = SizedInstructionTestFile(
    instruction='CMP.W',
    name='cmp_word',
    inputs=CMP_WORD_INPUTS,
    outputs_producer=produce_cmp_outputs,
    modes=__cmp_modes_and_cycles(
        memory_to_register=4,
        register_to_register=4)

)

CMP_LONG = SizedInstructionTestFile(
    instruction='CMP.L',
    name='cmp_long',
    inputs=CMP_LONG_INPUTS,
    outputs_producer=produce_cmp_outputs,
    modes=__cmp_modes_and_cycles(
        memory_to_register=6,
        register_to_register=6)
)

CMPA_WORD = SizedInstructionTestFile(
    instruction='CMPA.W',
    name='cmpa_word',
    inputs=CMP_WORD_INPUTS,
    outputs_producer=produce_cmpa_outputs,
    modes=__address_arithmetic_modes_and_cycles(
        memory_to_register=6,
        register_to_register=6)

)

CMPA_LONG = SizedInstructionTestFile(
    instruction='CMPA.L',
    name='cmpa_long',
    inputs=CMP_LONG_INPUTS,
    outputs_producer=produce_cmpa_outputs,
    modes=__address_arithmetic_modes_and_cycles(
        memory_to_register=6,
        register_to_register=6)
)

AND_BYTE = SizedInstructionTestFile(
    instruction='AND.B',
    name='and_byte',
    inputs=AND_BYTE_INPUTS,
    outputs_producer=produce_and_outputs,
    modes=__logic_modes_and_cycles(
        memory_to_register=4,
        register_to_register=4,
        register_to_memory=8)
)

AND_WORD = SizedInstructionTestFile(
    instruction='AND.W',
    name='and_word',
    inputs=AND_WORD_INPUTS,
    outputs_producer=produce_and_outputs,
    modes=__logic_modes_and_cycles(
        memory_to_register=4,
        register_to_register=4,
        register_to_memory=8)
)

AND_LONG = SizedInstructionTestFile(
    instruction='AND.L',
    name='and_long',
    inputs=AND_LONG_INPUTS,
    outputs_producer=produce_and_outputs,
    modes=__logic_modes_and_cycles(
        memory_to_register=6,
        register_to_register=8,
        register_to_memory=12)
)

OR_BYTE = SizedInstructionTestFile(
    instruction='OR.B',
    name='or_byte',
    inputs=OR_BYTE_INPUTS,
    outputs_producer=produce_or_outputs,
    modes=__logic_modes_and_cycles(
        memory_to_register=4,
        register_to_register=4,
        register_to_memory=8)
)

OR_WORD = SizedInstructionTestFile(
    instruction='OR.W',
    name='or_word',
    inputs=OR_WORD_INPUTS,
    outputs_producer=produce_or_outputs,
    modes=__logic_modes_and_cycles(
        memory_to_register=4,
        register_to_register=4,
        register_to_memory=8)
)

OR_LONG = SizedInstructionTestFile(
    instruction='OR.L',
    name='or_long',
    inputs=OR_LONG_INPUTS,
    outputs_producer=produce_or_outputs,
    modes=__logic_modes_and_cycles(
        memory_to_register=6,
        register_to_register=8,
        register_to_memory=12)
)

EOR_BYTE = SizedInstructionTestFile(
    instruction='EOR.B',
    name='eor_byte',
    inputs=EOR_BYTE_INPUTS,
    outputs_producer=produce_eor_outputs,
    modes=__eor_modes_and_cycles(
        register_to_register=4,
        register_to_memory=8)
)

EOR_WORD = SizedInstructionTestFile(
    instruction='EOR.W',
    name='eor_word',
    inputs=EOR_WORD_INPUTS,
    outputs_producer=produce_eor_outputs,
    modes=__eor_modes_and_cycles(
        register_to_register=4,
        register_to_memory=8)
)

EOR_LONG = SizedInstructionTestFile(
    instruction='EOR.L',
    name='eor_long',
    inputs=EOR_LONG_INPUTS,
    outputs_producer=produce_eor_outputs,
    modes=__eor_modes_and_cycles(
        register_to_register=8,
        register_to_memory=12)
)

MULU_WORD = SizedInstructionTestFile(
    instruction='MULU',
    name='mulu_word',
    inputs=MULU_WORD_INPUTS,
    outputs_producer=produce_mulu_outputs,
    modes=[
        ModesAndCycles(address_modes=[
            BINARY_DATA_REGISTER_TO_DATA_REGISTER,
            BINARY_IMMEDIATE_TO_DATA_REGISTER,
            BINARY_MEMORY_TO_DATA_REGISTER
        ], cycles=__mulu_cycles)
    ]
)

MULS_WORD = SizedInstructionTestFile(
    instruction='MULS',
    name='muls_word',
    inputs=MULU_WORD_INPUTS,
    outputs_producer=produce_muls_outputs,
    modes=[
        ModesAndCycles(address_modes=[
            BINARY_DATA_REGISTER_TO_DATA_REGISTER,
            BINARY_IMMEDIATE_TO_DATA_REGISTER,
            BINARY_MEMORY_TO_DATA_REGISTER
        ], cycles=__muls_cycles)
    ]
)

DIVU_WORD = SizedInstructionTestFile(
    instruction='DIVU',
    name='divu_word',
    inputs=DIVU_WORD_INPUTS,
    outputs_producer=produce_divu_outputs,
    modes=[
        ModesAndCycles(address_modes=[
            BINARY_DATA_REGISTER_TO_DATA_REGISTER,
            BINARY_IMMEDIATE_TO_DATA_REGISTER,
            BINARY_MEMORY_TO_DATA_REGISTER
        ], cycles=__divu_cycles)
    ]
)

DIVS_WORD = SizedInstructionTestFile(
    instruction='DIVS',
    name='divs_word',
    inputs=DIVU_WORD_INPUTS,
    outputs_producer=produce_divs_outputs,
    modes=[
        ModesAndCycles(address_modes=[
            BINARY_DATA_REGISTER_TO_DATA_REGISTER,
            BINARY_IMMEDIATE_TO_DATA_REGISTER,
            BINARY_MEMORY_TO_DATA_REGISTER
        ], cycles=__divs_cycles)
    ]
)

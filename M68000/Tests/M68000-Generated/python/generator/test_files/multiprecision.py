"""
This module contains test file descriptions for the multiprecision instructions.
"""

from typing import List

from ..address_mode_data.arithmetic import \
    BINARY_DATA_REGISTER_TO_DATA_REGISTER
from ..address_mode_data.multiprecision import \
    MULTIPRECISION_MEMORY_TO_MEMORY_DECREMENT, \
    MULTIPRECISION_MEMORY_TO_MEMORY_INCREMENT
from ..inputs.arithmetic import \
    CMP_BYTE_INPUTS, \
    CMP_WORD_INPUTS, \
    CMP_LONG_INPUTS
from ..inputs.multiprecision import \
    ADDX_BYTE_INPUTS, ADDX_WORD_INPUTS, ADDX_LONG_INPUTS, \
    SUBX_BYTE_INPUTS, SUBX_WORD_INPUTS, SUBX_LONG_INPUTS, \
    ABCD_BYTE_INPUTS, SBCD_BYTE_INPUTS
from ..outputs.arithmetic import \
    produce_cmp_outputs
from ..outputs.multiprecision import \
    produce_addx_outputs, \
    produce_subx_outputs, \
    produce_abcd_outputs, \
    produce_sbcd_outputs
from ..types.cycles import takes_n_cycles
from ..types.sized_instruction_test_file import \
    SizedInstructionTestFile, \
    ModesAndCycles


def __multiprecision_modes_and_cycles(
        register_to_register: int = 0,
        memory_to_memory: int = 0) -> List[ModesAndCycles]:
    return [
        ModesAndCycles(address_modes=[
            BINARY_DATA_REGISTER_TO_DATA_REGISTER,
        ], cycles=takes_n_cycles(register_to_register)),
        ModesAndCycles(address_modes=[
            MULTIPRECISION_MEMORY_TO_MEMORY_DECREMENT
        ], cycles=takes_n_cycles(memory_to_memory)),
    ]


def __multiprecision_compare_modes_and_cycles(
        memory_to_memory: int = 0) -> List[ModesAndCycles]:
    return [
        ModesAndCycles(address_modes=[
            MULTIPRECISION_MEMORY_TO_MEMORY_INCREMENT
        ], cycles=takes_n_cycles(memory_to_memory)),
    ]


ADDX_BYTE = SizedInstructionTestFile(
    instruction='ADDX.B',
    name='addx_byte',
    inputs=ADDX_BYTE_INPUTS,
    outputs_producer=produce_addx_outputs,
    modes=__multiprecision_modes_and_cycles(
        register_to_register=4,
        memory_to_memory=18)
)

ADDX_WORD = SizedInstructionTestFile(
    instruction='ADDX.W',
    name='addx_word',
    inputs=ADDX_WORD_INPUTS,
    outputs_producer=produce_addx_outputs,
    modes=__multiprecision_modes_and_cycles(
        register_to_register=4,
        memory_to_memory=18)
)

ADDX_LONG = SizedInstructionTestFile(
    instruction='ADDX.L',
    name='addx_long',
    inputs=ADDX_LONG_INPUTS,
    outputs_producer=produce_addx_outputs,
    modes=__multiprecision_modes_and_cycles(
        register_to_register=8,
        memory_to_memory=30)
)

SUBX_BYTE = SizedInstructionTestFile(
    instruction='SUBX.B',
    name='subx_byte',
    inputs=SUBX_BYTE_INPUTS,
    outputs_producer=produce_subx_outputs,
    modes=__multiprecision_modes_and_cycles(
        register_to_register=4,
        memory_to_memory=18)
)

SUBX_WORD = SizedInstructionTestFile(
    instruction='SUBX.W',
    name='subx_word',
    inputs=SUBX_WORD_INPUTS,
    outputs_producer=produce_subx_outputs,
    modes=__multiprecision_modes_and_cycles(
        register_to_register=4,
        memory_to_memory=18)
)

SUBX_LONG = SizedInstructionTestFile(
    instruction='SUBX.L',
    name='subx_long',
    inputs=SUBX_LONG_INPUTS,
    outputs_producer=produce_subx_outputs,
    modes=__multiprecision_modes_and_cycles(
        register_to_register=8,
        memory_to_memory=30)
)

CMPM_BYTE = SizedInstructionTestFile(
    instruction='CMPM.B',
    name='cmpm_byte',
    inputs=CMP_BYTE_INPUTS,
    outputs_producer=produce_cmp_outputs,
    modes=__multiprecision_compare_modes_and_cycles(
        memory_to_memory=12)
)

CMPM_WORD = SizedInstructionTestFile(
    instruction='CMPM.W',
    name='cmpm_word',
    inputs=CMP_WORD_INPUTS,
    outputs_producer=produce_cmp_outputs,
    modes=__multiprecision_compare_modes_and_cycles(
        memory_to_memory=12)
)

CMPM_LONG = SizedInstructionTestFile(
    instruction='CMPM.L',
    name='cmpm_long',
    inputs=CMP_LONG_INPUTS,
    outputs_producer=produce_cmp_outputs,
    modes=__multiprecision_compare_modes_and_cycles(
        memory_to_memory=20)
)

ABCD_BYTE = SizedInstructionTestFile(
    instruction='ABCD',
    name='abcd_byte',
    inputs=ABCD_BYTE_INPUTS,
    outputs_producer=produce_abcd_outputs,
    modes=__multiprecision_modes_and_cycles(
        register_to_register=6,
        memory_to_memory=18)
)

SBCD_BYTE = SizedInstructionTestFile(
    instruction='SBCD',
    name='sbcd_byte',
    inputs=SBCD_BYTE_INPUTS,
    outputs_producer=produce_sbcd_outputs,
    modes=__multiprecision_modes_and_cycles(
        register_to_register=6,
        memory_to_memory=18)
)

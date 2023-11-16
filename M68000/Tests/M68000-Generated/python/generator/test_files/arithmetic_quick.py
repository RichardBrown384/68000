"""
This module contains test file descriptions for the quick instructions.
"""

from typing import List

from ..address_mode_data.arithmetic_quick import \
    QUICK_TO_DATA_REGISTER, \
    QUICK_TO_ADDRESS_REGISTER, \
    QUICK_TO_MEMORY
from ..inputs.arithmetic_quick import \
    ADDQ_BYTE_INPUTS, ADDQ_WORD_INPUTS, ADDQ_LONG_INPUTS, \
    SUBQ_BYTE_INPUTS, SUBQ_WORD_INPUTS, SUBQ_LONG_INPUTS, \
    MOVEQ_LONG_INPUTS
from ..outputs.arithmetic import \
    produce_add_outputs, produce_sub_outputs, \
    produce_adda_outputs, produce_suba_outputs, \
    produce_moveq_outputs
from ..types.cycles import takes_n_cycles, \
    takes_n_cycles_plus_destination
from ..types.sized_instruction_test_file import SizedInstructionTestFile, ModesAndCycles


def __byte_modes_and_cycles(
        immediate_to_register: int = 0,
        immediate_to_memory: int = 0) -> List[ModesAndCycles]:
    return [
        ModesAndCycles(
            address_modes=[QUICK_TO_DATA_REGISTER],
            cycles=takes_n_cycles(immediate_to_register)),
        ModesAndCycles(
            address_modes=[QUICK_TO_MEMORY],
            cycles=takes_n_cycles_plus_destination(immediate_to_memory))
    ]


def __word_modes_and_cycles(
        immediate_to_data: int = 0,
        immediate_to_memory: int = 0) -> List[ModesAndCycles]:
    return [
        ModesAndCycles(
            address_modes=[QUICK_TO_DATA_REGISTER],
            cycles=takes_n_cycles(immediate_to_data)),
        ModesAndCycles(
            address_modes=[QUICK_TO_MEMORY],
            cycles=takes_n_cycles_plus_destination(immediate_to_memory))
    ]


def __long_modes_and_cycles(
        immediate_to_data: int = 0) -> List[ModesAndCycles]:
    return [
        ModesAndCycles(
            address_modes=[QUICK_TO_DATA_REGISTER],
            cycles=takes_n_cycles(immediate_to_data))
    ]


def __address_register_modes_and_cycles(
        immediate_to_register: int = 0) -> List[ModesAndCycles]:
    return [
        ModesAndCycles(
            address_modes=[QUICK_TO_ADDRESS_REGISTER],
            cycles=takes_n_cycles(immediate_to_register)),
    ]


ADDQ_BYTE = SizedInstructionTestFile(
    instruction='ADDQ.B',
    name='addq_byte',
    inputs=ADDQ_BYTE_INPUTS,
    outputs_producer=produce_add_outputs,
    modes=__byte_modes_and_cycles(
        immediate_to_register=4,
        immediate_to_memory=8)
)

ADDQ_WORD = SizedInstructionTestFile(
    instruction='ADDQ.W',
    name='addq_word',
    inputs=ADDQ_WORD_INPUTS,
    outputs_producer=produce_add_outputs,
    modes=__word_modes_and_cycles(
        immediate_to_data=4,
        immediate_to_memory=8)
)

ADDQ_LONG = SizedInstructionTestFile(
    instruction='ADDQ.L',
    name='addq_long',
    inputs=ADDQ_LONG_INPUTS,
    outputs_producer=produce_add_outputs,
    modes=__word_modes_and_cycles(
        immediate_to_data=8,
        immediate_to_memory=12)
)

SUBQ_BYTE = SizedInstructionTestFile(
    instruction='SUBQ.B',
    name='subq_byte',
    inputs=SUBQ_BYTE_INPUTS,
    outputs_producer=produce_sub_outputs,
    modes=__byte_modes_and_cycles(immediate_to_register=4,
                                  immediate_to_memory=8)
)

SUBQ_WORD = SizedInstructionTestFile(
    instruction='SUBQ.W',
    name='subq_word',
    inputs=SUBQ_WORD_INPUTS,
    outputs_producer=produce_sub_outputs,
    modes=__word_modes_and_cycles(
        immediate_to_data=4,
        immediate_to_memory=8)
)

SUBQ_LONG = SizedInstructionTestFile(
    instruction='SUBQ.L',
    name='subq_long',
    inputs=SUBQ_LONG_INPUTS,
    outputs_producer=produce_sub_outputs,
    modes=__word_modes_and_cycles(
        immediate_to_data=8,
        immediate_to_memory=12)
)

ADDAQ_WORD = SizedInstructionTestFile(
    instruction='ADDQ.W',
    name='addqa_word',
    inputs=ADDQ_WORD_INPUTS,
    outputs_producer=produce_adda_outputs,
    modes=__address_register_modes_and_cycles(immediate_to_register=8)
)

ADDQA_LONG = SizedInstructionTestFile(
    instruction='ADDQ.L',
    name='addqa_long',
    inputs=ADDQ_LONG_INPUTS,
    outputs_producer=produce_adda_outputs,
    modes=__address_register_modes_and_cycles(immediate_to_register=8)
)

SUBQA_WORD = SizedInstructionTestFile(
    instruction='SUBQ.W',
    name='subqa_word',
    inputs=SUBQ_WORD_INPUTS,
    outputs_producer=produce_suba_outputs,
    modes=__address_register_modes_and_cycles(immediate_to_register=8)
)

SUBQA_LONG = SizedInstructionTestFile(
    instruction='SUBQ.L',
    name='subqa_long',
    inputs=SUBQ_LONG_INPUTS,
    outputs_producer=produce_suba_outputs,
    modes=__address_register_modes_and_cycles(immediate_to_register=8)
)

MOVEQ_LONG = SizedInstructionTestFile(
    instruction='MOVEQ',
    name='moveq_long',
    inputs=MOVEQ_LONG_INPUTS,
    outputs_producer=produce_moveq_outputs,
    modes=__long_modes_and_cycles(immediate_to_data=4)
)

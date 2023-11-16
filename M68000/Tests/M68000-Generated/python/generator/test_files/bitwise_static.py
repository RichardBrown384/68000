"""
This module contains test file descriptions for the static bitwise instructions.
"""

from typing import List

from ..inputs.bitwise import \
    BITWISE_BYTE_INPUTS, BITWISE_LONG_INPUTS
from ..address_mode_data.bitwise_static import \
    BITWISE_STATIC_TO_DATA_REGISTER, \
    BITWISE_STATIC_TO_MEMORY
from ..outputs.bitwise import \
    produce_bchg_outputs, produce_bclr_outputs, \
    produce_bset_outputs, produce_btst_outputs
from ..types.cycles import \
    takes_n_cycles_plus_destination, \
    takes_n_cycles
from ..types.sized_instruction_test_file import SizedInstructionTestFile, ModesAndCycles


def __byte_modes_and_cycles(immediate_to_memory: int = 0) -> List[ModesAndCycles]:
    return [ModesAndCycles(
        address_modes=[
            BITWISE_STATIC_TO_MEMORY
        ],
        cycles=takes_n_cycles_plus_destination(immediate_to_memory)
    )]


def __long_modes_and_cycles(immediate_to_register: int = 0) -> List[ModesAndCycles]:
    return [ModesAndCycles(
        address_modes=[
            BITWISE_STATIC_TO_DATA_REGISTER
        ],
        cycles=takes_n_cycles(immediate_to_register)
    )]


BCHG_STATIC_BYTE = SizedInstructionTestFile(
    instruction='BCHG.B',
    name='bchg_static_byte',
    inputs=BITWISE_BYTE_INPUTS,
    outputs_producer=produce_bchg_outputs,
    modes=__byte_modes_and_cycles(immediate_to_memory=12)
)

BCHG_STATIC_LONG = SizedInstructionTestFile(
    instruction='BCHG.L',
    name='bchg_static_long',
    inputs=BITWISE_LONG_INPUTS,
    outputs_producer=produce_bchg_outputs,
    modes=__long_modes_and_cycles(immediate_to_register=12)
)

BCLR_STATIC_BYTE = SizedInstructionTestFile(
    instruction='BCLR.B',
    name='bclr_static_byte',
    inputs=BITWISE_BYTE_INPUTS,
    outputs_producer=produce_bclr_outputs,
    modes=__byte_modes_and_cycles(immediate_to_memory=12)
)

BCLR_STATIC_LONG = SizedInstructionTestFile(
    instruction='BCLR.L',
    name='bclr_static_long',
    inputs=BITWISE_LONG_INPUTS,
    outputs_producer=produce_bclr_outputs,
    modes=__long_modes_and_cycles(immediate_to_register=14)
)

BSET_STATIC_BYTE = SizedInstructionTestFile(
    instruction='BSET.B',
    name='bset_static_byte',
    inputs=BITWISE_BYTE_INPUTS,
    outputs_producer=produce_bset_outputs,
    modes=__byte_modes_and_cycles(immediate_to_memory=12)
)

BSET_STATIC_LONG = SizedInstructionTestFile(
    instruction='BSET.L',
    name='bset_static_long',
    inputs=BITWISE_LONG_INPUTS,
    outputs_producer=produce_bset_outputs,
    modes=__long_modes_and_cycles(immediate_to_register=12)
)

BTST_STATIC_BYTE = SizedInstructionTestFile(
    instruction='BTST.B',
    name='btst_static_byte',
    inputs=BITWISE_BYTE_INPUTS,
    outputs_producer=produce_btst_outputs,
    modes=__byte_modes_and_cycles(immediate_to_memory=8)
)

BTST_STATIC_LONG = SizedInstructionTestFile(
    instruction='BTST.L',
    name='btst_static_long',
    inputs=BITWISE_LONG_INPUTS,
    outputs_producer=produce_btst_outputs,
    modes=__long_modes_and_cycles(immediate_to_register=10)
)

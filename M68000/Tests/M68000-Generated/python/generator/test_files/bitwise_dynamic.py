"""
This module contains test file descriptions for the dynamic bitwise instructions.
"""

from typing import List

from ..inputs.bitwise import \
    BITWISE_BYTE_INPUTS, BITWISE_LONG_INPUTS
from ..address_mode_data.arithmetic import \
    BINARY_DATA_REGISTER_TO_MEMORY, \
    BINARY_DATA_REGISTER_TO_DATA_REGISTER
from ..address_mode_data.bitwise_dynamic \
    import BITWISE_DYNAMIC_TO_MEMORY
from ..outputs.bitwise import \
    produce_bchg_outputs, produce_bclr_outputs,\
    produce_bset_outputs, produce_btst_outputs
from ..types.cycles import \
    takes_n_cycles_plus_destination, \
    takes_n_cycles
from ..types.sized_instruction_test_file import \
    SizedInstructionTestFile, ModesAndCycles


def __byte_modes_and_cycles(register_to_memory: int = 0) -> List[ModesAndCycles]:
    return [ModesAndCycles(
        address_modes=[
            BINARY_DATA_REGISTER_TO_MEMORY
        ],
        cycles=takes_n_cycles_plus_destination(register_to_memory)
    )]


def __long_modes_and_cycles(register_to_register: int = 0) -> List[ModesAndCycles]:
    return [ModesAndCycles(
        address_modes=[
            BINARY_DATA_REGISTER_TO_DATA_REGISTER
        ],
        cycles=takes_n_cycles(register_to_register)
    )]


BCHG_DYNAMIC_BYTE = SizedInstructionTestFile(
    instruction='BCHG.B',
    name='bchg_dynamic_byte',
    inputs=BITWISE_BYTE_INPUTS,
    outputs_producer=produce_bchg_outputs,
    modes=__byte_modes_and_cycles(register_to_memory=8)
)

BCHG_DYNAMIC_LONG = SizedInstructionTestFile(
    instruction='BCHG.L',
    name='bchg_dynamic_long',
    inputs=BITWISE_LONG_INPUTS,
    outputs_producer=produce_bchg_outputs,
    modes=__long_modes_and_cycles(register_to_register=8)
)

BCLR_DYNAMIC_BYTE = SizedInstructionTestFile(
    instruction='BCLR.B',
    name='bclr_dynamic_byte',
    inputs=BITWISE_BYTE_INPUTS,
    outputs_producer=produce_bclr_outputs,
    modes=__byte_modes_and_cycles(register_to_memory=8)
)

BCLR_DYNAMIC_LONG = SizedInstructionTestFile(
    instruction='BCLR.L',
    name='bclr_dynamic_long',
    inputs=BITWISE_LONG_INPUTS,
    outputs_producer=produce_bclr_outputs,
    modes=__long_modes_and_cycles(register_to_register=10)
)

BSET_DYNAMIC_BYTE = SizedInstructionTestFile(
    instruction='BSET.B',
    name='bset_dynamic_byte',
    inputs=BITWISE_BYTE_INPUTS,
    outputs_producer=produce_bset_outputs,
    modes=__byte_modes_and_cycles(register_to_memory=8)
)

BSET_DYNAMIC_LONG = SizedInstructionTestFile(
    instruction='BSET.L',
    inputs=BITWISE_LONG_INPUTS,
    name='bset_dynamic_long',
    outputs_producer=produce_bset_outputs,
    modes=__long_modes_and_cycles(register_to_register=8)
)

BTST_DYNAMIC_BYTE = SizedInstructionTestFile(
    instruction='BTST.B',
    name='btst_dynamic_byte',
    inputs=BITWISE_BYTE_INPUTS,
    outputs_producer=produce_btst_outputs,
    modes=[ModesAndCycles(
        address_modes=[
            BINARY_DATA_REGISTER_TO_MEMORY,
            BITWISE_DYNAMIC_TO_MEMORY
        ],
        cycles=takes_n_cycles_plus_destination(4)
    )]
)

BTST_DYNAMIC_LONG = SizedInstructionTestFile(
    instruction='BTST.L',
    name='btst_dynamic_long',
    inputs=BITWISE_LONG_INPUTS,
    outputs_producer=produce_btst_outputs,
    modes=__long_modes_and_cycles(register_to_register=6)
)

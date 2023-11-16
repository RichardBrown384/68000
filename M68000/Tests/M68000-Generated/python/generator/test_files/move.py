from typing import List

from ..address_mode_data.arithmetic import \
    BINARY_DATA_REGISTER_TO_DATA_REGISTER, \
    BINARY_IMMEDIATE_TO_DATA_REGISTER, \
    BINARY_MEMORY_TO_DATA_REGISTER, \
    BINARY_DATA_REGISTER_TO_ADDRESS_REGISTER, \
    BINARY_IMMEDIATE_TO_ADDRESS_REGISTER, \
    BINARY_MEMORY_TO_ADDRESS_REGISTER
from ..address_mode_data.move import \
    MOVE_DATA_REGISTER_TO_MEMORY_EXCLUDING_DECREMENT, \
    MOVE_DATA_REGISTER_TO_MEMORY_DECREMENT
from ..inputs.move import \
    MOVE_BYTE_INPUTS, \
    MOVE_WORD_INPUTS,\
    MOVE_LONG_INPUTS
from ..outputs.move import \
    produce_move_outputs, \
    produce_movea_outputs
from ..types.cycles import \
    takes_n_cycles, \
    takes_n_cycles_plus_destination, \
    takes_n_cycles_plus_source
from ..types.sized_instruction_test_file import \
    SizedInstructionTestFile, \
    ModesAndCycles


def __move_modes_and_cycles(
        register_to_register: int = 0,
        memory_to_register: int = 0,
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
            MOVE_DATA_REGISTER_TO_MEMORY_EXCLUDING_DECREMENT,
        ], cycles=takes_n_cycles_plus_destination(register_to_memory)),
        ModesAndCycles(address_modes=[
            MOVE_DATA_REGISTER_TO_MEMORY_DECREMENT,
        ], cycles=takes_n_cycles_plus_destination(register_to_memory - 2)),
    ]


def __movea_modes_and_cycles(
        register_to_register: int = 0,
        memory_to_register: int = 0) -> List[ModesAndCycles]:
    return [
        ModesAndCycles(address_modes=[
            BINARY_DATA_REGISTER_TO_ADDRESS_REGISTER,
        ], cycles=takes_n_cycles(register_to_register)),
        ModesAndCycles(address_modes=[
            BINARY_IMMEDIATE_TO_ADDRESS_REGISTER
        ], cycles=takes_n_cycles_plus_source(register_to_register)),
        ModesAndCycles(address_modes=[
            BINARY_MEMORY_TO_ADDRESS_REGISTER,
        ], cycles=takes_n_cycles_plus_source(memory_to_register))
    ]


MOVE_BYTE = SizedInstructionTestFile(
    instruction='MOVE.B',
    name='move_byte',
    inputs=MOVE_BYTE_INPUTS,
    outputs_producer=produce_move_outputs,
    modes=__move_modes_and_cycles(
        register_to_register=4,
        memory_to_register=4,
        register_to_memory=4)
)

MOVE_WORD = SizedInstructionTestFile(
    instruction='MOVE.W',
    name='move_word',
    inputs=MOVE_WORD_INPUTS,
    outputs_producer=produce_move_outputs,
    modes=__move_modes_and_cycles(
        register_to_register=4,
        memory_to_register=4,
        register_to_memory=4)
)

MOVE_LONG = SizedInstructionTestFile(
    instruction='MOVE.L',
    name='move_long',
    inputs=MOVE_LONG_INPUTS,
    outputs_producer=produce_move_outputs,
    modes=__move_modes_and_cycles(
        register_to_register=4,
        memory_to_register=4,
        register_to_memory=4)
)

MOVEA_WORD = SizedInstructionTestFile(
    instruction='MOVEA.W',
    name='movea_word',
    inputs=MOVE_WORD_INPUTS,
    outputs_producer=produce_movea_outputs,
    modes=__movea_modes_and_cycles(
        register_to_register=4,
        memory_to_register=4)
)

MOVEL_WORD = SizedInstructionTestFile(
    instruction='MOVEA.L',
    name='movea_long',
    inputs=MOVE_LONG_INPUTS,
    outputs_producer=produce_movea_outputs,
    modes=__movea_modes_and_cycles(
        register_to_register=4,
        memory_to_register=4)
)

"""
This module contains functions to create modes and cycles objects
for the shift rotate instruction test files.
"""

from typing import List

from ..address_mode_data.shift_rotate import \
    SHIFT_ROTATE_COUNT_TO_DATA_REGISTER, \
    SHIFT_ROTATE_DATA_REGISTER_TO_DATA_REGISTER
from ..address_mode_data.single_operand import SINGLE_TO_MEMORY
from ..types.cycles import takes_n_cycles_plus_destination

from ..types.sized_instruction_test_file import ModesAndCycles


def shift_rotate_count_modes_and_cycles(
        immediate_to_register: int = 0) -> List[ModesAndCycles]:
    return [
        ModesAndCycles(address_modes=[
            SHIFT_ROTATE_COUNT_TO_DATA_REGISTER
        ], cycles=lambda _source, _destination, inputs:
            immediate_to_register + 2 * inputs.src)
    ]


def shift_rotate_register_modes_and_cycles(
        register_to_register: int = 0) -> List[ModesAndCycles]:
    return [
        ModesAndCycles(address_modes=[
            SHIFT_ROTATE_DATA_REGISTER_TO_DATA_REGISTER
        ], cycles=lambda _source, _destination, inputs:
            register_to_register + 2 * (inputs.src & 0x3F))
    ]


def shift_rotate_memory_modes_and_cycles(
        memory_to_memory: int = 0) -> List[ModesAndCycles]:
    return [
        ModesAndCycles(address_modes=[
            SINGLE_TO_MEMORY
        ], cycles=takes_n_cycles_plus_destination(memory_to_memory))
    ]

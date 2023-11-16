"""
This module contains the address mode data specific to move instructions.
"""

from .shared import \
    produce_address_mode_products, \
    destination_index_data_register_is_not_source_data_register
from .shared_mode_data import \
    PCS, \
    DATA_REGISTERS, \
    DATA_REGISTERS_REDUCED, \
    ADDRESS_INDIRECTS, \
    ADDRESS_INCREMENTS, \
    ADDRESS_DECREMENTS, \
    STACK_DECREMENTS, \
    STACK_INCREMENTS, \
    ADDRESS_DISPLACEMENTS, \
    ADDRESS_INDEXES, \
    SHORTS, \
    LONGS

MOVE_DATA_REGISTER_TO_MEMORY_EXCLUDING_DECREMENT = [
    *produce_address_mode_products(PCS, DATA_REGISTERS, ADDRESS_INDIRECTS),
    *produce_address_mode_products(PCS, DATA_REGISTERS, ADDRESS_INCREMENTS),
    *produce_address_mode_products(PCS, DATA_REGISTERS, STACK_INCREMENTS),
    *produce_address_mode_products(PCS, DATA_REGISTERS, ADDRESS_DISPLACEMENTS),
    *produce_address_mode_products(
        PCS, DATA_REGISTERS_REDUCED, ADDRESS_INDEXES,
        predicate=destination_index_data_register_is_not_source_data_register
    ),
    *produce_address_mode_products(PCS, DATA_REGISTERS, SHORTS),
    *produce_address_mode_products(PCS, DATA_REGISTERS, LONGS)
]

MOVE_DATA_REGISTER_TO_MEMORY_DECREMENT = [
    *produce_address_mode_products(PCS, DATA_REGISTERS, ADDRESS_DECREMENTS),
    *produce_address_mode_products(PCS, DATA_REGISTERS, STACK_DECREMENTS),
]

"""
This module contains the address mode data for the arithmetic binary operation instructions.
"""

from .shared import produce_address_mode_products, \
    source_index_data_register_is_not_destination_data_register, \
    destination_index_data_register_is_not_source_data_register, \
    source_index_address_register_is_not_destination_address_register, \
    produce_address_mode_products_excluding_same, \
    source_or_index_register_is_not_destination_address_register
from .shared_mode_data import \
    PCS, \
    DATA_REGISTERS, \
    DATA_REGISTERS_REDUCED, \
    ADDRESS_REGISTERS, \
    ADDRESS_INDIRECTS, \
    ADDRESS_INCREMENTS, \
    STACK_INCREMENTS, \
    ADDRESS_DECREMENTS, \
    STACK_DECREMENTS, \
    ADDRESS_DISPLACEMENTS, \
    ADDRESS_INDEXES, \
    SHORTS, \
    LONGS, \
    PC_DISPLACEMENTS, \
    PC_INDEXES, \
    IMMEDIATES

BINARY_DATA_REGISTER_TO_DATA_REGISTER = \
    produce_address_mode_products_excluding_same(PCS, DATA_REGISTERS, DATA_REGISTERS)

BINARY_ADDRESS_REGISTER_TO_DATA_REGISTER = \
    produce_address_mode_products(PCS, ADDRESS_REGISTERS, DATA_REGISTERS)

BINARY_MEMORY_TO_DATA_REGISTER = [
    *produce_address_mode_products(PCS, ADDRESS_INDIRECTS, DATA_REGISTERS),
    *produce_address_mode_products(PCS, ADDRESS_INCREMENTS, DATA_REGISTERS),
    *produce_address_mode_products(PCS, STACK_INCREMENTS, DATA_REGISTERS),
    *produce_address_mode_products(PCS, ADDRESS_DECREMENTS, DATA_REGISTERS),
    *produce_address_mode_products(PCS, STACK_DECREMENTS, DATA_REGISTERS),
    *produce_address_mode_products(PCS, ADDRESS_DISPLACEMENTS, DATA_REGISTERS),
    *produce_address_mode_products(
        PCS, ADDRESS_INDEXES, DATA_REGISTERS_REDUCED,
        predicate=source_index_data_register_is_not_destination_data_register
    ),
    *produce_address_mode_products(PCS, SHORTS, DATA_REGISTERS),
    *produce_address_mode_products(PCS, LONGS, DATA_REGISTERS),
    *produce_address_mode_products(PCS, PC_DISPLACEMENTS, DATA_REGISTERS),
    *produce_address_mode_products(
        PCS, PC_INDEXES, DATA_REGISTERS,
        predicate=source_index_data_register_is_not_destination_data_register
    ),
]

BINARY_IMMEDIATE_TO_DATA_REGISTER = \
    produce_address_mode_products(PCS, IMMEDIATES, DATA_REGISTERS)

BINARY_DATA_REGISTER_TO_MEMORY = [
    *produce_address_mode_products(PCS, DATA_REGISTERS, ADDRESS_INDIRECTS),
    *produce_address_mode_products(PCS, DATA_REGISTERS, ADDRESS_INCREMENTS),
    *produce_address_mode_products(PCS, DATA_REGISTERS, STACK_INCREMENTS),
    *produce_address_mode_products(PCS, DATA_REGISTERS, ADDRESS_DECREMENTS),
    *produce_address_mode_products(PCS, DATA_REGISTERS, STACK_DECREMENTS),
    *produce_address_mode_products(PCS, DATA_REGISTERS, ADDRESS_DISPLACEMENTS),
    *produce_address_mode_products(
        PCS, DATA_REGISTERS_REDUCED, ADDRESS_INDEXES,
        predicate=destination_index_data_register_is_not_source_data_register
    ),
    *produce_address_mode_products(PCS, DATA_REGISTERS, SHORTS),
    *produce_address_mode_products(PCS, DATA_REGISTERS, LONGS)
]

BINARY_DATA_REGISTER_TO_ADDRESS_REGISTER = \
    produce_address_mode_products(
        PCS, DATA_REGISTERS, ADDRESS_REGISTERS
    )

BINARY_ADDRESS_REGISTER_TO_ADDRESS_REGISTER = \
    produce_address_mode_products_excluding_same(PCS, ADDRESS_REGISTERS, ADDRESS_REGISTERS)

BINARY_MEMORY_TO_ADDRESS_REGISTER = [
    *produce_address_mode_products_excluding_same(PCS, ADDRESS_INDIRECTS, ADDRESS_REGISTERS, ),
    *produce_address_mode_products_excluding_same(PCS, ADDRESS_INCREMENTS, ADDRESS_REGISTERS),
    *produce_address_mode_products_excluding_same(PCS, STACK_INCREMENTS, ADDRESS_REGISTERS),
    *produce_address_mode_products_excluding_same(PCS, ADDRESS_DECREMENTS, ADDRESS_REGISTERS),
    *produce_address_mode_products_excluding_same(PCS, STACK_DECREMENTS, ADDRESS_REGISTERS),
    *produce_address_mode_products_excluding_same(PCS, ADDRESS_DISPLACEMENTS, ADDRESS_REGISTERS),
    *produce_address_mode_products(
        PCS, ADDRESS_INDEXES, ADDRESS_REGISTERS,
        predicate=source_or_index_register_is_not_destination_address_register
    ),
    *produce_address_mode_products(PCS, SHORTS, ADDRESS_REGISTERS),
    *produce_address_mode_products(PCS, LONGS, ADDRESS_REGISTERS),
    *produce_address_mode_products(PCS, PC_DISPLACEMENTS, ADDRESS_REGISTERS),
    *produce_address_mode_products(
        PCS, PC_INDEXES, ADDRESS_REGISTERS,
        predicate=source_index_address_register_is_not_destination_address_register
    ),
]

BINARY_IMMEDIATE_TO_ADDRESS_REGISTER = \
    produce_address_mode_products(PCS, IMMEDIATES, ADDRESS_REGISTERS)

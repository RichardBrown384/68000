"""
This module contains the address mode data for the bitwise dynamic instructions.
"""

from .shared_mode_data import \
    PCS, \
    DATA_REGISTERS, \
    PC_DISPLACEMENTS, \
    PC_INDEXES, \
    IMMEDIATES

from .shared import produce_address_mode_products, \
    destination_index_data_register_is_not_source_data_register

BITWISE_DYNAMIC_TO_MEMORY = [
    *produce_address_mode_products(PCS, DATA_REGISTERS, PC_DISPLACEMENTS),
    *produce_address_mode_products(
        PCS, DATA_REGISTERS, PC_INDEXES,
        predicate=destination_index_data_register_is_not_source_data_register
    ),
    *produce_address_mode_products(PCS, DATA_REGISTERS, IMMEDIATES)
]

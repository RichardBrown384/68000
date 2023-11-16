"""
This module contains the address mode data for the single-operand instructions.
"""


from .shared_mode_data import \
    PCS, \
    DATA_REGISTERS, \
    ADDRESS_INDIRECTS, \
    ADDRESS_INCREMENTS, \
    STACK_INCREMENTS, \
    ADDRESS_DECREMENTS, \
    STACK_DECREMENTS, \
    ADDRESS_DISPLACEMENTS, \
    ADDRESS_INDEXES, \
    SHORTS, \
    LONGS, \
    NULLS

from .shared import produce_address_mode_products

SINGLE_TO_DATA_REGISTER = produce_address_mode_products(PCS, NULLS, DATA_REGISTERS)

SINGLE_TO_MEMORY = [
    *produce_address_mode_products(PCS, NULLS, ADDRESS_INDIRECTS),
    *produce_address_mode_products(PCS, NULLS, ADDRESS_INCREMENTS),
    *produce_address_mode_products(PCS, NULLS, STACK_INCREMENTS),
    *produce_address_mode_products(PCS, NULLS, ADDRESS_DECREMENTS),
    *produce_address_mode_products(PCS, NULLS, STACK_DECREMENTS),
    *produce_address_mode_products(PCS, NULLS, ADDRESS_DISPLACEMENTS),
    *produce_address_mode_products(PCS, NULLS, ADDRESS_INDEXES),
    *produce_address_mode_products(PCS, NULLS, SHORTS),
    *produce_address_mode_products(PCS, NULLS, LONGS)
]

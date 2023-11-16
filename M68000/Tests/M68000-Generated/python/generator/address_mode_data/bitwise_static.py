"""
This module contains the address mode data for the bitwise static instructions.
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
    BITWISE_IMMEDIATES

from .shared import produce_address_mode_products

BITWISE_STATIC_TO_DATA_REGISTER = \
    produce_address_mode_products(PCS, BITWISE_IMMEDIATES, DATA_REGISTERS)

BITWISE_STATIC_TO_MEMORY = [
    *produce_address_mode_products(PCS, BITWISE_IMMEDIATES, ADDRESS_INDIRECTS),
    *produce_address_mode_products(PCS, BITWISE_IMMEDIATES, ADDRESS_INCREMENTS),
    *produce_address_mode_products(PCS, BITWISE_IMMEDIATES, STACK_INCREMENTS),
    *produce_address_mode_products(PCS, BITWISE_IMMEDIATES, ADDRESS_DECREMENTS),
    *produce_address_mode_products(PCS, BITWISE_IMMEDIATES, STACK_DECREMENTS),
    *produce_address_mode_products(PCS, BITWISE_IMMEDIATES, ADDRESS_DISPLACEMENTS),
    *produce_address_mode_products(PCS, BITWISE_IMMEDIATES, ADDRESS_INDEXES),
    *produce_address_mode_products(PCS, BITWISE_IMMEDIATES, SHORTS),
    *produce_address_mode_products(PCS, BITWISE_IMMEDIATES, LONGS),
]

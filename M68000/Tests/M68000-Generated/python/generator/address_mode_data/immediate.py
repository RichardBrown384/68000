"""
This module contains the address mode data for the immediate instructions.
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
    IMMEDIATES

from .shared import produce_address_mode_products

IMMEDIATE_TO_DATA_REGISTER = \
    produce_address_mode_products(PCS, IMMEDIATES, DATA_REGISTERS)

IMMEDIATE_TO_MEMORY = [
    *produce_address_mode_products(PCS, IMMEDIATES, ADDRESS_INDIRECTS),
    *produce_address_mode_products(PCS, IMMEDIATES, ADDRESS_INCREMENTS),
    *produce_address_mode_products(PCS, IMMEDIATES, STACK_INCREMENTS),
    *produce_address_mode_products(PCS, IMMEDIATES, ADDRESS_DECREMENTS),
    *produce_address_mode_products(PCS, IMMEDIATES, STACK_DECREMENTS),
    *produce_address_mode_products(PCS, IMMEDIATES, ADDRESS_DISPLACEMENTS),
    *produce_address_mode_products(PCS, IMMEDIATES, ADDRESS_INDEXES),
    *produce_address_mode_products(PCS, IMMEDIATES, SHORTS),
    *produce_address_mode_products(PCS, IMMEDIATES, LONGS),
]

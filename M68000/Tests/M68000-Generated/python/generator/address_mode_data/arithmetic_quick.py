"""
This module contains the address mode data for the quick instructions.
"""

from .shared_mode_data import \
    PCS, \
    DATA_REGISTERS, \
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
    QUICK_IMMEDIATES

from .shared import produce_address_mode_products

QUICK_TO_DATA_REGISTER = \
    produce_address_mode_products(PCS, QUICK_IMMEDIATES, DATA_REGISTERS)

QUICK_TO_ADDRESS_REGISTER = \
    produce_address_mode_products(PCS, QUICK_IMMEDIATES, ADDRESS_REGISTERS)

QUICK_TO_MEMORY = [
    *produce_address_mode_products(PCS, QUICK_IMMEDIATES, ADDRESS_INDIRECTS),
    *produce_address_mode_products(PCS, QUICK_IMMEDIATES, ADDRESS_INCREMENTS),
    *produce_address_mode_products(PCS, QUICK_IMMEDIATES, STACK_INCREMENTS),
    *produce_address_mode_products(PCS, QUICK_IMMEDIATES, ADDRESS_DECREMENTS),
    *produce_address_mode_products(PCS, QUICK_IMMEDIATES, STACK_DECREMENTS),
    *produce_address_mode_products(PCS, QUICK_IMMEDIATES, ADDRESS_DISPLACEMENTS),
    *produce_address_mode_products(PCS, QUICK_IMMEDIATES, ADDRESS_INDEXES),
    *produce_address_mode_products(PCS, QUICK_IMMEDIATES, SHORTS),
    *produce_address_mode_products(PCS, QUICK_IMMEDIATES, LONGS)
]

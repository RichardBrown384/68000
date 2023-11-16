"""
This module contains the address mode data for the multiprecision instructions.
"""

from .shared import \
    produce_address_mode_products_excluding_same
from .shared_mode_data import \
    PCS, \
    ADDRESS_DECREMENTS, \
    ADDRESS_DECREMENTS_ALTERNATE, \
    STACK_DECREMENTS, \
    ADDRESS_INCREMENTS, \
    ADDRESS_INCREMENTS_ALTERNATE, \
    STACK_INCREMENTS

MULTIPRECISION_MEMORY_TO_MEMORY_DECREMENT = [
    *produce_address_mode_products_excluding_same(
        PCS, ADDRESS_DECREMENTS, ADDRESS_DECREMENTS_ALTERNATE),
    *produce_address_mode_products_excluding_same(
        PCS, STACK_DECREMENTS, ADDRESS_DECREMENTS_ALTERNATE),
    *produce_address_mode_products_excluding_same(
        PCS, ADDRESS_DECREMENTS_ALTERNATE, STACK_DECREMENTS)
]

MULTIPRECISION_MEMORY_TO_MEMORY_INCREMENT = [
    *produce_address_mode_products_excluding_same(
        PCS, ADDRESS_INCREMENTS, ADDRESS_INCREMENTS_ALTERNATE),
    *produce_address_mode_products_excluding_same(
        PCS, STACK_INCREMENTS, ADDRESS_INCREMENTS_ALTERNATE),
    *produce_address_mode_products_excluding_same(
        PCS, ADDRESS_INCREMENTS_ALTERNATE, STACK_INCREMENTS)
]

"""
This module contains the address mode data for the shift rotate instructions.
"""

from .shared import produce_address_mode_products, \
    produce_address_mode_products_excluding_same
from .shared_mode_data import \
    PCS, \
    DATA_REGISTERS, \
    QUICK_IMMEDIATES

SHIFT_ROTATE_COUNT_TO_DATA_REGISTER = \
    produce_address_mode_products(PCS, QUICK_IMMEDIATES, DATA_REGISTERS)

SHIFT_ROTATE_DATA_REGISTER_TO_DATA_REGISTER = \
    produce_address_mode_products_excluding_same(PCS, DATA_REGISTERS, DATA_REGISTERS)

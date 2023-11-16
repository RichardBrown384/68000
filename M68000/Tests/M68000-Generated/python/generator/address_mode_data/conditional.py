"""
This module contains the address mode data for the conditional instructions.
"""
from .shared import produce_address_mode_products
from .shared_mode_data import \
    PCS, \
    NULLS, \
    WORD_DECREMENT_AND_BRANCHES, \
    BYTE_BRANCHES,\
    WORD_BRANCHES, \
    BYTE_SUBROUTINE_BRANCHES, \
    WORD_SUBROUTINE_BRANCHES

CONDITIONAL_WORD_DECREMENT_AND_BRANCH = produce_address_mode_products(
    PCS, NULLS, WORD_DECREMENT_AND_BRANCHES
)

CONDITIONAL_BYTE_BRANCH = produce_address_mode_products(
    PCS, NULLS, BYTE_BRANCHES
)

CONDITIONAL_WORD_BRANCH = produce_address_mode_products(
    PCS, NULLS, WORD_BRANCHES
)

CONDITIONAL_BYTE_SUBROUTINE_BRANCH = produce_address_mode_products(
    PCS, NULLS, BYTE_SUBROUTINE_BRANCHES
)

CONDITIONAL_WORD_SUBROUTINE_BRANCH = produce_address_mode_products(
    PCS, NULLS, WORD_SUBROUTINE_BRANCHES
)

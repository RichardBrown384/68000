from .shared import produce_address_mode_products
from .shared_mode_data import \
    PCS, \
    CONDITION_CODE_REGISTERS, \
    STATUS_REGISTERS, \
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
    PC_DISPLACEMENTS, \
    PC_INDEXES, \
    IMMEDIATES, \
    NULLS

# Dn, CCR
# <ea>, CCR
# #imm, CCR

MISCELLANEOUS_DATA_REGISTER_TO_CONDITION_CODE_REGISTER = [
    *produce_address_mode_products(PCS, DATA_REGISTERS, CONDITION_CODE_REGISTERS),
]

MISCELLANEOUS_MEMORY_TO_CONDITION_CODE_REGISTER = [
    *produce_address_mode_products(PCS, ADDRESS_INDIRECTS, CONDITION_CODE_REGISTERS),
    *produce_address_mode_products(PCS, ADDRESS_INCREMENTS, CONDITION_CODE_REGISTERS),
    *produce_address_mode_products(PCS, STACK_INCREMENTS, CONDITION_CODE_REGISTERS),
    *produce_address_mode_products(PCS, ADDRESS_DECREMENTS, CONDITION_CODE_REGISTERS),
    *produce_address_mode_products(PCS, STACK_DECREMENTS, CONDITION_CODE_REGISTERS),
    *produce_address_mode_products(PCS, ADDRESS_DISPLACEMENTS, CONDITION_CODE_REGISTERS),
    *produce_address_mode_products(PCS, ADDRESS_INDEXES, CONDITION_CODE_REGISTERS),
    *produce_address_mode_products(PCS, SHORTS, CONDITION_CODE_REGISTERS),
    *produce_address_mode_products(PCS, LONGS, CONDITION_CODE_REGISTERS),
    *produce_address_mode_products(PCS, PC_DISPLACEMENTS, CONDITION_CODE_REGISTERS),
    *produce_address_mode_products(PCS, PC_INDEXES, CONDITION_CODE_REGISTERS)
]

MISCELLANEOUS_IMMEDIATE_TO_CONDITION_CODE_REGISTER = [
    *produce_address_mode_products(PCS, IMMEDIATES, CONDITION_CODE_REGISTERS)
]

# Dn, SR
# <ea>, SR
# #imm, SR

MISCELLANEOUS_DATA_REGISTER_TO_STATUS_REGISTER = [
    *produce_address_mode_products(PCS, DATA_REGISTERS, STATUS_REGISTERS),
]

MISCELLANEOUS_MEMORY_TO_STATUS_REGISTER = [
    *produce_address_mode_products(PCS, ADDRESS_INDIRECTS, STATUS_REGISTERS),
    *produce_address_mode_products(PCS, ADDRESS_INCREMENTS, STATUS_REGISTERS),
    *produce_address_mode_products(PCS, STACK_INCREMENTS, STATUS_REGISTERS),
    *produce_address_mode_products(PCS, ADDRESS_DECREMENTS, STATUS_REGISTERS),
    *produce_address_mode_products(PCS, STACK_DECREMENTS, STATUS_REGISTERS),
    *produce_address_mode_products(PCS, ADDRESS_DISPLACEMENTS, STATUS_REGISTERS),
    *produce_address_mode_products(PCS, ADDRESS_INDEXES, STATUS_REGISTERS),
    *produce_address_mode_products(PCS, SHORTS, STATUS_REGISTERS),
    *produce_address_mode_products(PCS, LONGS, STATUS_REGISTERS),
    *produce_address_mode_products(PCS, PC_DISPLACEMENTS, STATUS_REGISTERS),
    *produce_address_mode_products(PCS, PC_INDEXES, STATUS_REGISTERS)
]

MISCELLANEOUS_IMMEDIATE_TO_STATUS_REGISTER = [
    *produce_address_mode_products(PCS, IMMEDIATES, STATUS_REGISTERS)
]

# SR, Dn
# SR, <ea>

MISCELLANEOUS_STATUS_REGISTER_TO_DATA_REGISTER = \
    produce_address_mode_products(PCS, STATUS_REGISTERS, DATA_REGISTERS)

MISCELLANEOUS_STATUS_REGISTER_TO_MEMORY = [
    *produce_address_mode_products(PCS, STATUS_REGISTERS, ADDRESS_INDIRECTS),
    *produce_address_mode_products(PCS, STATUS_REGISTERS, ADDRESS_INCREMENTS),
    *produce_address_mode_products(PCS, STATUS_REGISTERS, STACK_INCREMENTS),
    *produce_address_mode_products(PCS, STATUS_REGISTERS, ADDRESS_DECREMENTS),
    *produce_address_mode_products(PCS, STATUS_REGISTERS, STACK_DECREMENTS),
    *produce_address_mode_products(PCS, STATUS_REGISTERS, ADDRESS_DISPLACEMENTS),
    *produce_address_mode_products(PCS, STATUS_REGISTERS, ADDRESS_INDEXES),
    *produce_address_mode_products(PCS, STATUS_REGISTERS, SHORTS),
    *produce_address_mode_products(PCS, STATUS_REGISTERS, LONGS)
]

# STOP #imm
MISCELLANEOUS_IMMEDIATE_TO_NULL = [
    *produce_address_mode_products(PCS, IMMEDIATES, NULLS)
]
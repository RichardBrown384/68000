"""
This module contains a list of all possible condition code register states.
"""

import itertools

from ..types.status_register import StatusRegister

__CONDITION_FLAG_VALUES = [False, True]
__INTERRUPT_MASKS = [0, 6]


ALL_CONDITION_CODE_REGISTERS = [
    StatusRegister(x=extend,
                   n=negative, z=zero,
                   v=overflow, c=carry)
    for extend, negative, zero, overflow, carry in itertools.product(
        __CONDITION_FLAG_VALUES,
        __CONDITION_FLAG_VALUES, __CONDITION_FLAG_VALUES,
        __CONDITION_FLAG_VALUES, __CONDITION_FLAG_VALUES)
]

REDUCED_CONDITION_CODE_REGISTERS = [
    StatusRegister(x=extend,
                   n=negative,
                   v=overflow)
    for extend, negative, overflow in itertools.product(
        __CONDITION_FLAG_VALUES,
        __CONDITION_FLAG_VALUES,
        __CONDITION_FLAG_VALUES)
]

ALL_STATUS_REGISTERS = [
    StatusRegister(s=supervisor,
                   interrupt_mask=interrupt_mask,
                   x=extended,
                   n=negative, z=zero,
                   v=overflow, c=carry)
    for supervisor, interrupt_mask, extended, negative, zero, overflow, carry in itertools.product(
        __CONDITION_FLAG_VALUES,
        __INTERRUPT_MASKS,
        __CONDITION_FLAG_VALUES,
        __CONDITION_FLAG_VALUES, __CONDITION_FLAG_VALUES,
        __CONDITION_FLAG_VALUES, __CONDITION_FLAG_VALUES
    )
]

SUPERVISOR_STATUS_REGISTERS = [
    StatusRegister(s=supervisor,
                   interrupt_mask=interrupt_mask,
                   x=extended,
                   n=negative, z=zero,
                   v=overflow, c=carry)
    for supervisor, interrupt_mask, extended, negative, zero, overflow, carry in itertools.product(
        [True],
        __INTERRUPT_MASKS,
        __CONDITION_FLAG_VALUES,
        __CONDITION_FLAG_VALUES, __CONDITION_FLAG_VALUES,
        __CONDITION_FLAG_VALUES, __CONDITION_FLAG_VALUES
    )
]

REDUCED_STATUS_REGISTERS = [
    StatusRegister(s=supervisor,
                   v=overflow)
    for supervisor, overflow in itertools.product(
        [True],
        __CONDITION_FLAG_VALUES,
    )
]

STACK_POINTERS = [0x00FF_FFFC, 0x0000_100C]
USER_STACK_POINTERS = [0x0003_0000, 0x0004_0000]

"""
This module contains functions that validate the address mode input parameters.
"""


def check_is_even(value: int) -> bool:
    """Returns true if the value is even."""
    return value % 2 == 0


def check_register_number(number: int) -> bool:
    """Returns true if the register number is between 0 and 7."""
    return 0 <= number < 8


def check_increment_register_number(number: int) -> bool:
    """Returns true if the register number is between 0 and 6."""
    return 0 <= number < 7


def check_register_value(value: int) -> bool:
    """Returns true if the unsigned value fits in 32-bits."""
    return 0 <= value < 0xFFFF_FFFF


def check_displacement_word(value: int) -> bool:
    """Returns true if the signed values fits in 16-bits."""
    return -32768 <= value < 32768


def check_displacement_byte(value):
    """Returns true if the signed values fits in 8-bits."""
    return -128 <= value < 128


def check_short(value):
    """Returns true if the signed values fits in 16-bits."""
    return 0 <= value < 0xFFFF


def check_long(value):
    """Returns true if the signed values fits in 32-bits."""
    return 0 <= value < 0xFFFF_FFFF

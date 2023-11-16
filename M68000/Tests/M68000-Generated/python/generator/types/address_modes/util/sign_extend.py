"""
This module defines functions to sign extend values
"""


def sign_extend_byte(value: int) -> int:
    """Given an integer, truncates it to 8-bits and sign extends it."""
    return ((value & 0xFF) ^ 0x80) - 0x80


def sign_extend_word(value: int) -> int:
    """Given an integer, truncates it to 16-bits and sign extends it."""
    return ((value & 0xFFFF) ^ 0x8000) - 0x8000

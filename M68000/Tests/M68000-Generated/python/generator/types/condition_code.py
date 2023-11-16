"""
This module contains an enumeration of the M68000's condition codes
"""

from enum import Enum


class ConditionCode(Enum):
    """Enumerates all the possible M68000 condition codes."""
    T = 0x0
    F = 0x1
    HI = 0x2
    LS = 0x3
    CC = 0x4
    CS = 0x5
    NE = 0x6
    EQ = 0x7
    VC = 0x8
    VS = 0x9
    PL = 0xA
    MI = 0xB
    GE = 0xC
    LT = 0xD
    GT = 0xE
    LE = 0xF

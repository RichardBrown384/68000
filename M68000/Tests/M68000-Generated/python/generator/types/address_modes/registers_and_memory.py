"""
This module contains a dataclass that encapsulates what values an address mode
requires and where (be it data registers, address registers or memory).
"""

import dataclasses
from typing import Dict


@dataclasses.dataclass(kw_only=True)
# pylint: disable=invalid-name
class RegistersAndMemory:
    """Represents the state an address mode requires."""
    d: Dict[int, int] = dataclasses.field(default_factory=dict)
    a: Dict[int, int] = dataclasses.field(default_factory=dict)
    memory: Dict[int, int] = dataclasses.field(default_factory=dict)

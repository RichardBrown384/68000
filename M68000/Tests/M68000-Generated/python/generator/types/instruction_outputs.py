"""
This module contains dataclasses that represent M68000 instruction outputs
"""

import dataclasses

from .status_register import StatusRegister


@dataclasses.dataclass(kw_only=True)
class InstructionOutputs:
    """Outputs of single or binary operation."""
    dst: int
    status_register: StatusRegister

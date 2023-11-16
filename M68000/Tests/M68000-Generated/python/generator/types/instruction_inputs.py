"""
This module contains dataclasses that represent M68000 instruction inputs.
"""

import dataclasses

from .condition_code import ConditionCode
from .status_register import StatusRegister

_USER_STACK_POINTER = 0x0010_0000
_SUPERVISOR_STACK_POINTER = 0x00FF_FF_FF


@dataclasses.dataclass(kw_only=True)
class SingleInputs:
    """Inputs for a single operand instruction."""
    dst: int
    status_register: StatusRegister = \
        dataclasses.field(default_factory=StatusRegister)
    src: int = dataclasses.field(init=False)
    ssp: int = dataclasses.field(init=False)
    usp: int = dataclasses.field(init=False)
    stopped: bool = dataclasses.field(init=False)

    def __post_init__(self):
        """Initialises the src, ssp and usp fields"""
        self.src = 0
        self.usp = _USER_STACK_POINTER
        self.ssp = _SUPERVISOR_STACK_POINTER
        self.stopped = False


@dataclasses.dataclass(kw_only=True)
class BinaryInputs:
    """Inputs for a binary operation instruction."""
    src: int
    dst: int
    status_register: StatusRegister = \
        dataclasses.field(default_factory=StatusRegister)
    ssp: int = dataclasses.field(init=False)
    usp: int = dataclasses.field(init=False)
    stopped: bool = dataclasses.field(init=False)

    def __post_init__(self):
        """Initialises the ssp and usp fields"""
        self.usp = _USER_STACK_POINTER
        self.ssp = _SUPERVISOR_STACK_POINTER
        self.stopped = False


@dataclasses.dataclass(kw_only=True)
class ConditionalInputs:
    """Specialised inputs for the conditional instructions."""
    condition_code: ConditionCode
    dst: int = 0
    status_register: StatusRegister = \
        dataclasses.field(default_factory=StatusRegister)
    src: int = dataclasses.field(init=False)
    test: bool = dataclasses.field(init=False)
    ssp: int = dataclasses.field(init=False)
    usp: int = dataclasses.field(init=False)
    stopped: bool = dataclasses.field(init=False)

    def __post_init__(self):
        """Initialises src, usp and ssp and evaluates the condition code test."""
        self.src = 0
        self.test = self.status_register.test(self.condition_code)
        self.usp = _USER_STACK_POINTER
        self.ssp = _SUPERVISOR_STACK_POINTER
        self.stopped = False


@dataclasses.dataclass(kw_only=True)
class StatusRegisterInputs:
    src: int
    ssp: int
    usp: int
    status_register: StatusRegister = \
        dataclasses.field(default_factory=StatusRegister)
    stopped: bool = False
    dst: int = dataclasses.field(init=False)

    def __post_init__(self):
        """Set dst to zero."""
        self.dst = 0


InstructionInputs = SingleInputs | BinaryInputs | ConditionalInputs | StatusRegisterInputs

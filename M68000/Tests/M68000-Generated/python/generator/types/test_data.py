"""
This module contains the data structures that represent a test case.
"""

import dataclasses
from typing import Dict, List

from .status_register import StatusRegister

Registers = Dict[int, int]
Memory = Dict[int, int]


# pylint: disable=invalid-name
@dataclasses.dataclass(kw_only=True)
class GivenConditions:
    status_register: StatusRegister
    pc: int
    d: Registers = dataclasses.field(default_factory=dict)
    a: Registers = dataclasses.field(default_factory=dict)
    memory: Memory = dataclasses.field(default_factory=dict)
    usp: int = 0
    ssp: int = 0
    stopped: bool = False


# pylint: disable=invalid-name
@dataclasses.dataclass(kw_only=True)
class ThenConditions:
    status_register: StatusRegister
    pc: int
    cycles: int
    d: Registers = dataclasses.field(default_factory=dict)
    a: Registers = dataclasses.field(default_factory=dict)
    memory: Memory = dataclasses.field(default_factory=dict)
    usp: int = 0
    ssp: int = 0
    stopped: bool = False


@dataclasses.dataclass(kw_only=True)
class TestData:
    given: GivenConditions
    when: List[str]
    then: ThenConditions

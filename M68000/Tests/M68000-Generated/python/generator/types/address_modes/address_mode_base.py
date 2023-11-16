"""
This module defines the abstract base class for all the address modes
"""

import abc

from .conditional_branch import ConditionalBranch
from .registers_and_memory import RegistersAndMemory
from ..instruction_inputs import InstructionInputs
from ..size import SizeAdapter


class AddressModeBase(metaclass=abc.ABCMeta):
    """Address Mode Base Class."""

    @abc.abstractmethod
    def assembly(self, size_adapter: SizeAdapter, data: int) -> str:
        """Given a size adapter and input value returns the assembly for this address mode."""
        raise NotImplementedError('users must define assembly to use this base class')

    @abc.abstractmethod
    def produce_inputs(self,
                       size_adapter: SizeAdapter,
                       program_counter: int,
                       data: int) -> RegistersAndMemory:
        """Given a size adapter, input value and program counter returns the mode inputs."""
        raise NotImplementedError('users must define produce_inputs to use this base class')

    @abc.abstractmethod
    def produce_outputs(self,
                        size_adapter: SizeAdapter,
                        program_counter: int,
                        data: int) -> RegistersAndMemory:
        """Given a size adapter, input value and program counter returns the mode outputs."""
        raise NotImplementedError('users must define produce_outputs to use this base class')

    @abc.abstractmethod
    def extension_words(self, size_adapter: SizeAdapter) -> int:
        """Given a size adapter returns the number of extension words this mode has."""
        raise NotImplementedError('users must define extension_words to use this base class')

    @abc.abstractmethod
    def conditional_branch(self, inputs: InstructionInputs) -> ConditionalBranch:
        """Given instruction inputs determines if the address mode branches."""
        raise NotImplementedError('users must define branch to use this base class')

    @abc.abstractmethod
    def cycles(self, size_adapter: SizeAdapter, inputs: InstructionInputs) -> int:
        """Given a size adapter returns the number of cycles this address mode takes."""
        raise NotImplementedError('users must define cycles to use this base class')

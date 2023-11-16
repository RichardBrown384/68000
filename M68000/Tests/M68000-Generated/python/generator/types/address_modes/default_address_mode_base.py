import abc

from .address_mode_base import AddressModeBase
from .registers_and_memory import RegistersAndMemory
from .conditional_branch import ConditionalBranch
from ..instruction_inputs import InstructionInputs
from ..size import SizeAdapter

_EMPTY_REGISTERS_AND_MEMORY = RegistersAndMemory()
_DEFAULT_BRANCH = ConditionalBranch()


class DefaultAddressModeBase(AddressModeBase, metaclass=abc.ABCMeta):
    """Address Mode Base with common defaults."""

    def produce_inputs(self,
                       size_adapter: SizeAdapter,
                       program_counter: int,
                       data: int) -> RegistersAndMemory:
        return _EMPTY_REGISTERS_AND_MEMORY

    def produce_outputs(self,
                        size_adapter: SizeAdapter,
                        program_counter: int,
                        data: int) -> RegistersAndMemory:
        return _EMPTY_REGISTERS_AND_MEMORY

    def extension_words(self, size_adapter: SizeAdapter) -> int:
        return 0

    def conditional_branch(self, inputs: InstructionInputs) -> ConditionalBranch:
        return _DEFAULT_BRANCH

    def cycles(self, size_adapter: SizeAdapter, inputs: InstructionInputs) -> int:
        return 0

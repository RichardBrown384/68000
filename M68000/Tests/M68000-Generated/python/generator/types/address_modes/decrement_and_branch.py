"""
This module defines the decrement and branch address mode
"""
import dataclasses

from .conditional_branch import ConditionalBranch
from .default_address_mode_base import DefaultAddressModeBase
from .registers_and_memory import RegistersAndMemory
from .util.checks import check_displacement_word
from ..instruction_inputs import InstructionInputs
from ..size import SizeAdapter

_CYCLES_CONDITION_FALSE_COUNTER_EXPIRED = 14
_CYCLES_CONDITION_FALSE_COUNTER_NOT_EXPIRED = 10
_CYCLES_CONDITION_TRUE = 12


@dataclasses.dataclass(kw_only=True)
class DecrementAndBranch(DefaultAddressModeBase):
    """The class for decrement and branch."""
    number: int
    displacement: int

    def __post_init__(self):
        assert check_displacement_word(self.displacement)
        self.__assembly = f'D{self.number}, *{self.displacement:+}'

    def assembly(self, size_adapter: SizeAdapter, data: int) -> str:
        return self.__assembly

    def produce_inputs(self,
                       size_adapter: SizeAdapter,
                       program_counter: int,
                       data: int) -> RegistersAndMemory:
        return RegistersAndMemory(d={self.number: data})

    def produce_outputs(self,
                        size_adapter: SizeAdapter,
                        program_counter: int,
                        data: int) -> RegistersAndMemory:
        return RegistersAndMemory(d={self.number: data})

    def extension_words(self, size_adapter: SizeAdapter) -> int:
        return 1

    def conditional_branch(self, inputs: InstructionInputs) -> ConditionalBranch:
        return ConditionalBranch(
            branch=not inputs.test and inputs.dst & 0xFFFF,
            displacement=self.displacement - 2)

    def cycles(self, size_adapter: SizeAdapter, inputs: InstructionInputs) -> int:
        if inputs.test:
            return _CYCLES_CONDITION_TRUE
        if inputs.dst & 0xFFFF:
            return _CYCLES_CONDITION_FALSE_COUNTER_NOT_EXPIRED
        return _CYCLES_CONDITION_FALSE_COUNTER_EXPIRED

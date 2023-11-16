"""
This module defines the branch subroutine byte address mode
"""
import dataclasses

from .conditional_branch import ConditionalBranch
from .default_address_mode_base import DefaultAddressModeBase
from .registers_and_memory import RegistersAndMemory
from .util.checks import check_is_even, check_register_value, check_displacement_byte
from ..instruction_inputs import InstructionInputs
from ..size import SizeAdapter
from ..sized_instruction_inputs import LONG_ADAPTER

_CYCLES_CONDITION_FALSE = 18
_CYCLES_CONDITION_TRUE = 18


@dataclasses.dataclass(kw_only=True)
class BranchSubroutineByte(DefaultAddressModeBase):
    """The class for branch subroutine byte."""
    value: int
    displacement: int
    number: int = dataclasses.field(init=False)

    def __post_init__(self):
        assert check_is_even(self.value) and \
               check_register_value(self.value) and \
               check_displacement_byte(self.displacement)
        self.__assembly = f'*{self.displacement:+}'
        self.number = 7

    def assembly(self, size_adapter: SizeAdapter, data: int) -> str:
        return self.__assembly

    def _effective_address(self):
        return self.value - 4

    def _create_address_inputs(self):
        return {self.number: self.value}

    def _create_address_outputs(self):
        return {self.number: self.value - 4}

    def _create_memory(self, size_adapter: SizeAdapter, data: int):
        return size_adapter.create_memory(self._effective_address(), data)

    def produce_inputs(self,
                       size_adapter: SizeAdapter,
                       program_counter: int,
                       data: int) -> RegistersAndMemory:
        return RegistersAndMemory(
            a=self._create_address_inputs(),
            memory=self._create_memory(LONG_ADAPTER, data))

    def produce_outputs(self,
                        size_adapter: SizeAdapter,
                        program_counter: int,
                        data: int) -> RegistersAndMemory:
        return RegistersAndMemory(
            a=self._create_address_outputs(),
            memory=self._create_memory(LONG_ADAPTER, program_counter + 2))

    def conditional_branch(self, inputs: InstructionInputs) -> ConditionalBranch:
        return ConditionalBranch(
            branch=inputs.test,
            displacement=self.displacement - 2)

    def cycles(self, size_adapter: SizeAdapter, inputs: InstructionInputs) -> int:
        return _CYCLES_CONDITION_TRUE if inputs.test else _CYCLES_CONDITION_FALSE

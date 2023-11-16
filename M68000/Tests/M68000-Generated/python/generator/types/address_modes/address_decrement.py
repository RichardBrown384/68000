"""
This module defines the address decrement mode
"""

import dataclasses

from .default_address_mode_base import DefaultAddressModeBase
from .registers_and_memory import RegistersAndMemory
from .util.checks import \
    check_increment_register_number, \
    check_register_value
from ..instruction_inputs import InstructionInputs
from ..size import SizeAdapter


@dataclasses.dataclass(kw_only=True)
class AddressDecrement(DefaultAddressModeBase):
    """This class defines the Address Decrement mode."""
    number: int
    value: int

    def __post_init__(self):
        assert check_increment_register_number(self.number) and \
               check_register_value(self.value)
        self.__assembly = f'-(A{self.number})'

    def assembly(self, size_adapter: SizeAdapter, data: int) -> str:
        return self.__assembly

    def _effective_address(self, size_adapter: SizeAdapter):
        increment = size_adapter.address_register_increment(self.number)
        return self.value - increment

    def _create_address_inputs(self):
        return {self.number: self.value}

    def _create_address_outputs(self, size_adapter: SizeAdapter):
        return {self.number: self._effective_address(size_adapter)}

    def _create_memory(self, size_adapter: SizeAdapter, data: int):
        return size_adapter.create_memory(self._effective_address(size_adapter), data)

    def produce_inputs(self,
                       size_adapter: SizeAdapter,
                       program_counter: int,
                       data: int) -> RegistersAndMemory:
        return RegistersAndMemory(
            a=self._create_address_inputs(),
            memory=self._create_memory(size_adapter, data))

    def produce_outputs(self,
                        size_adapter: SizeAdapter,
                        program_counter: int,
                        data: int) -> RegistersAndMemory:
        return RegistersAndMemory(
            a=self._create_address_outputs(size_adapter),
            memory=self._create_memory(size_adapter, data))

    def cycles(self, size_adapter: SizeAdapter, inputs: InstructionInputs) -> int:
        return 2 + 4 * size_adapter.operand_words

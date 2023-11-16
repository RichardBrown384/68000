"""
This module defines the program counter displacement mode
"""

import dataclasses

from .default_address_mode_base import DefaultAddressModeBase
from .registers_and_memory import RegistersAndMemory
from .util.checks import check_displacement_word
from ..instruction_inputs import InstructionInputs
from ...types.size import SizeAdapter


@dataclasses.dataclass(kw_only=True)
class PcDisplacement(DefaultAddressModeBase):
    """This class defines the Program Counter Displacement mode."""
    displacement: int

    def __post_init__(self):
        assert check_displacement_word(self.displacement)
        self.__assembly = f'({self.displacement}, PC)'

    def assembly(self, size_adapter: SizeAdapter, data: int) -> str:
        return self.__assembly

    def _effective_address(self, program_counter: int):
        return self.displacement + program_counter + 2

    def _create_memory(self, size_adapter: SizeAdapter, data: int, program_counter: int):
        effective_address = self._effective_address(program_counter)
        return size_adapter.create_memory(effective_address, data)

    def produce_inputs(self,
                       size_adapter: SizeAdapter,
                       program_counter: int,
                       data: int) -> RegistersAndMemory:
        return RegistersAndMemory(memory=self._create_memory(size_adapter, data, program_counter))

    def produce_outputs(self,
                        size_adapter: SizeAdapter,
                        program_counter: int,
                        data: int) -> RegistersAndMemory:
        return RegistersAndMemory(memory=self._create_memory(size_adapter, data, program_counter))

    def extension_words(self, size_adapter: SizeAdapter) -> int:
        return 1

    def cycles(self, size_adapter: SizeAdapter, inputs: InstructionInputs) -> int:
        return 4 * (1 + size_adapter.operand_words)

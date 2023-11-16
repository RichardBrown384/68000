import dataclasses

from .default_address_mode_base import DefaultAddressModeBase
from .index_register import IndexRegister
from .registers_and_memory import RegistersAndMemory
from .util.checks import check_displacement_byte
from ..instruction_inputs import InstructionInputs
from ...types.size import SizeAdapter


@dataclasses.dataclass(kw_only=True)
class PcIndex(DefaultAddressModeBase):
    displacement: int
    index: IndexRegister

    def __post_init__(self):
        assert check_displacement_byte(self.displacement)
        self.__index_inputs = self.index.produce_inputs()
        self.__assembly = f'({self.displacement}, PC, {self.index.assembly()})'

    def assembly(self, size_adapter: SizeAdapter, data: int) -> str:
        return self.__assembly

    def _effective_address(self, program_counter: int):
        return self.displacement + (program_counter + 2) + self.index.index_value()

    def _create_memory(self, size_adapter: SizeAdapter, data: int, program_counter: int):
        effective_address = self._effective_address(program_counter)
        return size_adapter.create_memory(effective_address, data)

    def produce_inputs(self,
                       size_adapter: SizeAdapter,
                       program_counter: int,
                       data: int) -> RegistersAndMemory:
        return RegistersAndMemory(
            a=self.__index_inputs.a,
            d=self.__index_inputs.d,
            memory=self._create_memory(size_adapter, data, program_counter))

    def produce_outputs(self,
                        size_adapter: SizeAdapter,
                        program_counter: int,
                        data: int) -> RegistersAndMemory:
        return RegistersAndMemory(
            a=self.__index_inputs.a,
            d=self.__index_inputs.d,
            memory=self._create_memory(size_adapter, data, program_counter))

    def extension_words(self, size_adapter: SizeAdapter) -> int:
        return 1

    def cycles(self, size_adapter: SizeAdapter, inputs: InstructionInputs) -> int:
        return 2 + 4 * (1 + size_adapter.operand_words)

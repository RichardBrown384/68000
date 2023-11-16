import dataclasses

from .default_address_mode_base import DefaultAddressModeBase
from .index_register import IndexRegister
from .registers_and_memory import RegistersAndMemory
from .util.checks import check_register_number, \
    check_register_value, check_displacement_byte
from ..instruction_inputs import InstructionInputs
from ...types.size import SizeAdapter


@dataclasses.dataclass(kw_only=True)
class AddressIndex(DefaultAddressModeBase):
    number: int
    value: int
    displacement: int
    index: IndexRegister

    def __post_init__(self):
        assert check_register_number(self.number) and \
               check_register_value(self.value) and \
               check_displacement_byte(self.displacement)
        self.__effective_address = \
            self.displacement + \
            self.value + \
            self.index.index_value()
        self.__index_inputs = self.index.produce_inputs()
        self.__index_a = self.__index_inputs.a | {self.number: self.value}
        self.__assembly = f'({self.displacement}, A{self.number}, {self.index.assembly()})'

    def assembly(self, size_adapter: SizeAdapter, data: int) -> str:
        return self.__assembly

    def _effective_address(self):
        return self.__effective_address

    def _create_memory(self, size_adapter, data):
        return size_adapter.create_memory(self._effective_address(), data)

    def produce_inputs(self,
                       size_adapter: SizeAdapter,
                       program_counter: int,
                       data: int) -> RegistersAndMemory:
        return RegistersAndMemory(
            a=self.__index_a,
            d=self.__index_inputs.d,
            memory=self._create_memory(size_adapter, data))

    def produce_outputs(self,
                        size_adapter: SizeAdapter,
                        program_counter: int,
                        data: int) -> RegistersAndMemory:
        return RegistersAndMemory(
            a=self.__index_a,
            d=self.__index_inputs.d,
            memory=self._create_memory(size_adapter, data))

    def extension_words(self, size_adapter: SizeAdapter) -> int:
        return 1

    def cycles(self, size_adapter: SizeAdapter, inputs: InstructionInputs) -> int:
        return 2 + 4 * (1 + size_adapter.operand_words)

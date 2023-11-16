import dataclasses

from .default_address_mode_base import DefaultAddressModeBase
from .registers_and_memory import RegistersAndMemory
from .util.checks import check_short
from .util.sign_extend import sign_extend_word
from ..instruction_inputs import InstructionInputs
from ...types.size import SizeAdapter


@dataclasses.dataclass(kw_only=True)
class Short(DefaultAddressModeBase):
    value: int

    def __post_init__(self):
        assert check_short(self.value)
        self.__assembly = f'({self.value}).W'

    def assembly(self, size_adapter: SizeAdapter, data: int) -> str:
        return self.__assembly

    def _effective_address(self):
        return sign_extend_word(self.value)

    def _create_memory(self, size_adapter: SizeAdapter, data: int):
        return size_adapter.create_memory(self._effective_address(), data)

    def produce_inputs(self,
                       size_adapter: SizeAdapter,
                       program_counter: int,
                       data: int) -> RegistersAndMemory:
        return RegistersAndMemory(memory=self._create_memory(size_adapter, data))

    def produce_outputs(self,
                        size_adapter: SizeAdapter,
                        program_counter: int,
                        data: int) -> RegistersAndMemory:
        return RegistersAndMemory(memory=self._create_memory(size_adapter, data))

    def extension_words(self, size_adapter: SizeAdapter) -> int:
        return 1

    def cycles(self, size_adapter: SizeAdapter, inputs: InstructionInputs) -> int:
        return 4 * (1 + size_adapter.operand_words)

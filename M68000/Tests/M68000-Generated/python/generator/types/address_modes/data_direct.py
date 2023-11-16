import dataclasses

from .default_address_mode_base import DefaultAddressModeBase
from .registers_and_memory import RegistersAndMemory
from .util.checks import check_register_number
from ...types.size import SizeAdapter


@dataclasses.dataclass(kw_only=True)
class DataRegister(DefaultAddressModeBase):
    number: int

    def __post_init__(self):
        assert check_register_number(self.number)
        self.__assembly = f'D{self.number}'

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

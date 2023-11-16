import dataclasses
from enum import Enum

from .registers_and_memory import RegistersAndMemory
from .util.checks import check_register_number, \
    check_register_value
from .util.sign_extend import sign_extend_word


class IndexRegisterType(Enum):
    DATA_REGISTER = 0
    ADDRESS_REGISTER = 1


class IndexRegisterSize(Enum):
    WORD = 0
    LONG = 1


@dataclasses.dataclass(kw_only=True)
class IndexRegister:
    type: IndexRegisterType
    size: IndexRegisterSize
    number: int
    value: int

    def __post_init__(self):
        assert check_register_number(self.number) and \
               check_register_value(self.value)
        data = self.type == IndexRegisterType.DATA_REGISTER
        word = self.size == IndexRegisterSize.WORD
        letter = 'D' if data else 'A'
        size = 'W' if word else 'L'
        self.__assembly = f'{letter}{self.number}.{size}'
        self.__index_value = sign_extend_word(self.value) if word else self.value
        data = {self.number: self.__index_value} if data else {}
        address = {self.number: self.__index_value} if not data else {}
        self.__inputs = RegistersAndMemory(d=data, a=address)

    def assembly(self) -> str:
        return self.__assembly

    def index_value(self) -> int:
        return self.__index_value

    def produce_inputs(self) -> RegistersAndMemory:
        return self.__inputs

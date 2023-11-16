import dataclasses
from enum import Enum
from typing import Callable


class Size(Enum):
    BYTE = 0
    WORD = 1
    LONG = 2


@dataclasses.dataclass(kw_only=True)
class SizeCharacteristics:
    size: Size
    bits: int
    mask: int
    most_significant_bit_mask: int


@dataclasses.dataclass(kw_only=True)
class SizeAdapter:
    create_memory: Callable[[int, int], dict]
    address_register_increment: Callable[[int], int]
    immediate_operand_mask: int
    operand_words: int

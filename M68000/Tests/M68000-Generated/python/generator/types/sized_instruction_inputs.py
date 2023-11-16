import dataclasses
from typing import ClassVar, List

from .instruction_inputs import InstructionInputs
from .memory import \
    create_memory_byte, \
    create_memory_word, \
    create_memory_long
from .size import Size, SizeAdapter, SizeCharacteristics

BYTE_ADAPTER = SizeAdapter(
    create_memory=create_memory_byte,
    address_register_increment=lambda number: 2 if number == 7 else 1,
    immediate_operand_mask=0xFF,
    operand_words=1
)

WORD_ADAPTER = SizeAdapter(
    create_memory=create_memory_word,
    address_register_increment=lambda _: 2,
    immediate_operand_mask=0xFFFF,
    operand_words=1
)

LONG_ADAPTER = SizeAdapter(
    create_memory=create_memory_long,
    address_register_increment=lambda _: 4,
    immediate_operand_mask=0xFFFF_FFFF,
    operand_words=2
)

BYTE_CHARACTERISTICS = SizeCharacteristics(
    size=Size.BYTE,
    bits=8,
    mask=0xFF,
    most_significant_bit_mask=0x80
)

WORD_CHARACTERISTICS = SizeCharacteristics(
    size=Size.WORD,
    bits=16,
    mask=0xFFFF,
    most_significant_bit_mask=0x8000
)

LONG_CHARACTERISTICS = SizeCharacteristics(
    size=Size.LONG,
    bits=32,
    mask=0xFFFF_FFFF,
    most_significant_bit_mask=0x8000_0000
)


@dataclasses.dataclass(kw_only=True)
class ByteInstructionInputs:
    """The inputs for a byte sized operation."""
    adapter: ClassVar[SizeAdapter] = BYTE_ADAPTER
    characteristics: ClassVar[SizeCharacteristics] = BYTE_CHARACTERISTICS
    inputs: List[InstructionInputs]


@dataclasses.dataclass(kw_only=True)
class WordInstructionInputs:
    """The inputs for a word sized operation."""
    adapter: ClassVar[SizeAdapter] = WORD_ADAPTER
    characteristics: ClassVar[SizeCharacteristics] = WORD_CHARACTERISTICS
    inputs: List[InstructionInputs]


@dataclasses.dataclass(kw_only=True)
class LongInstructionInputs:
    """The inputs for a long sized operation."""
    adapter: ClassVar[SizeAdapter] = LONG_ADAPTER
    characteristics: ClassVar[SizeCharacteristics] = LONG_CHARACTERISTICS
    inputs: List[InstructionInputs]


SizedInstructionInputs = ByteInstructionInputs | \
                         WordInstructionInputs | \
                         LongInstructionInputs

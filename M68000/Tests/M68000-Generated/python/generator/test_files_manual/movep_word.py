import itertools
from typing import Dict

from .shared import PROGRAM_COUNTERS
from ..types.manual_test_file import ManualTestFile
from ..types.memory import create_memory_words, create_memory_byte
from ..types.status_register import StatusRegister
from ..types.test_data import \
    TestData, \
    GivenConditions, \
    ThenConditions


def __movep_word_register_result(address: int, memory: Dict[int, int]) -> int:
    return (memory[address] << 8) + memory[address + 2]


def __movep_word_memory_result(address: int, word1: int) -> int:
    return create_memory_byte(address, word1 >> 8) | \
           create_memory_byte(address + 2, word1)


def __movep_word_register(
        pc: int,
        displacement: int,
        y: int,
        base_address: int,
        word1: int,
        word2: int,
        x: int) -> TestData:
    effective_address = base_address + displacement
    memory = create_memory_words(
        effective_address & ~1,
        word1,
        word2
    )
    result = __movep_word_register_result(effective_address, memory)
    return TestData(
        given=GivenConditions(
            status_register=StatusRegister(),
            pc=pc,
            d={x: 0xFFFF_FFFF},
            a={y: base_address},
            memory=memory
        ),
        when=[f'MOVEP.W ({displacement}, A{y}), D{x}'],
        then=ThenConditions(
            status_register=StatusRegister(),
            pc=pc + 4,
            cycles=16,
            d={x: 0xFFFF_0000 + result},
            a={y: base_address},
            memory=memory
        ),
    )


def __movep_word_memory(
        pc: int,
        displacement: int,
        y: int,
        base_address: int,
        word1: int,
        x: int) -> TestData:
    effective_address = base_address + displacement
    memory = create_memory_words(
        effective_address & ~1,
        0xFFFF,
        0xFFFF
    )
    result = __movep_word_memory_result(effective_address, word1)
    return TestData(
        given=GivenConditions(
            status_register=StatusRegister(),
            pc=pc,
            d={x: 0xFFFF_0000 + word1},
            a={y: base_address},
            memory=memory
        ),
        when=[f'MOVEP.W D{x}, ({displacement}, A{y})'],
        then=ThenConditions(
            status_register=StatusRegister(),
            pc=pc + 4,
            cycles=16,
            d={x: 0xFFFF_0000 + word1},
            a={y: base_address},
            memory=memory | result
        ),
    )


def __movep_word_register_tests():
    return [
        __movep_word_register(pc, displacement, y, base_address, word1, word2, x)
        for pc, displacement, y, base_address, word1, word2, x in itertools.product(
            PROGRAM_COUNTERS,
            [0x0000, 0x1000, 0x0001, 0x1001],
            [1, 7],
            [0x4000, 0x5000],
            [0xAABB, 0xCCDD],
            [0x9988, 0xEE77],
            [0, 3]
        )]


def __movep_word_memory_tests():
    return [
        __movep_word_memory(pc, displacement, y, base_address, word1, x)
        for pc, displacement, y, base_address, word1, x in itertools.product(
            PROGRAM_COUNTERS,
            [0x0000, 0x1000, 0x0001, 0x1001],
            [1, 7],
            [0x4000, 0x5000],
            [0xAABB, 0xCCDD],
            [0, 3]
        )]


MOVEP_WORD = ManualTestFile(
    name='movep_word',
    d=[
        *__movep_word_register_tests(),
        *__movep_word_memory_tests()
    ]
)

import itertools
from typing import Dict

from .shared import PROGRAM_COUNTERS
from ..types.manual_test_file import ManualTestFile
from ..types.memory import create_memory_words, create_memory_byte, create_memory_longs
from ..types.status_register import StatusRegister
from ..types.test_data import \
    TestData, \
    GivenConditions, \
    ThenConditions


def __movep_long_register_result(address: int, memory: Dict[int, int]) -> int:
    return (memory[address] << 24) + \
           (memory[address + 2] << 16) + \
           (memory[address + 4] << 8) + \
           memory[address + 6]


def __movep_long_memory_result(address: int, long1: int) -> int:
    return create_memory_byte(address, long1 >> 24) | \
           create_memory_byte(address + 2, long1 >> 16) | \
           create_memory_byte(address + 4, long1 >> 8) | \
           create_memory_byte(address + 6, long1)


def __movep_long_register(
        pc: int,
        displacement: int,
        y: int,
        base_address: int,
        long1: int,
        long2: int,
        x: int) -> TestData:
    effective_address = base_address + displacement
    memory = create_memory_longs(
        effective_address & ~1,
        long1,
        long2,
    )
    result = __movep_long_register_result(effective_address, memory)
    return TestData(
        given=GivenConditions(
            status_register=StatusRegister(),
            pc=pc,
            d={x: 0xFFFF_FFFF},
            a={y: base_address},
            memory=memory
        ),
        when=[f'MOVEP.L ({displacement}, A{y}), D{x}'],
        then=ThenConditions(
            status_register=StatusRegister(),
            pc=pc + 4,
            cycles=24,
            d={x: result},
            a={y: base_address},
            memory=memory
        ),
    )


def __movep_long_memory(
        pc: int,
        displacement: int,
        y: int,
        base_address: int,
        long1: int,
        x: int) -> TestData:
    effective_address = base_address + displacement
    memory = create_memory_longs(
        effective_address & ~1,
        0xFFFF_FFFF,
        0xFFFF_FFFF
    )
    result = __movep_long_memory_result(effective_address, long1)
    return TestData(
        given=GivenConditions(
            status_register=StatusRegister(),
            pc=pc,
            d={x: long1},
            a={y: base_address},
            memory=memory
        ),
        when=[f'MOVEP.L D{x}, ({displacement}, A{y})'],
        then=ThenConditions(
            status_register=StatusRegister(),
            pc=pc + 4,
            cycles=24,
            d={x: long1},
            a={y: base_address},
            memory=memory | result
        ),
    )


def __movep_long_register_tests():
    return [
        __movep_long_register(pc, displacement, y, base_address, long1, long2, x)
        for pc, displacement, y, base_address, long1, long2, x in itertools.product(
            PROGRAM_COUNTERS,
            [0x0000, 0x1000, 0x0001, 0x1001],
            [1, 7],
            [0x4000, 0x5000],
            [0xAABB_2233, 0xCCDD_6611],
            [0x9988_4455, 0xEE77_A5A5],
            [0, 3]
        )]


def __movep_long_memory_tests():
    return [
        __movep_long_memory(pc, displacement, y, base_address, long1, x)
        for pc, displacement, y, base_address, long1, x in itertools.product(
            PROGRAM_COUNTERS,
            [0x0000, 0x1000, 0x0001, 0x1001],
            [1, 7],
            [0x4000, 0x5000],
            [0xAABB_2233, 0xCCDD_6111],
            [0, 3]
        )]


MOVEP_LONG = ManualTestFile(
    name='movep_long',
    d=[
        *__movep_long_register_tests(),
        *__movep_long_memory_tests()
    ]
)

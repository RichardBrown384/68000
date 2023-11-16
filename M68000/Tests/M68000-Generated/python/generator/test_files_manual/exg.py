import itertools
from typing import List, Callable

from .shared import PROGRAM_COUNTERS
from ..types.manual_test_file import ManualTestFile
from ..types.status_register import StatusRegister
from ..types.test_data import \
    TestData, \
    GivenConditions, \
    ThenConditions

__GIVEN_DATA_REGISTERS = {
    0: 0x1111_2222,
    1: 0x2222_2222,
    2: 0x3333_4444,
    3: 0x4444_4444,
    4: 0x5555_6666,
    5: 0x6666_6666,
    6: 0x7777_8888,
    7: 0x8888_8888
}
__GIVEN_ADDRESS_REGISTERS = {
    0: 0xAAAA_AAAA,
    1: 0x9999_AAAA,
    2: 0xCCCC_CCCC,
    3: 0xBBBB_CCCC,
    4: 0xEEEE_EEEE,
    5: 0xDDDD_EEEE,
    6: 0x0000_0000,
    7: 0xFFFF_0000
}
__REGISTER_NUMBERS = [r for r in range(8)]


def __exg_dx_dy(pc: int, x: int, y: int) -> TestData:
    return TestData(
        given=GivenConditions(
            status_register=StatusRegister(),
            pc=pc,
            d=__GIVEN_DATA_REGISTERS,
            a=__GIVEN_ADDRESS_REGISTERS,
        ),
        when=[f'EXG D{x}, D{y}'],
        then=ThenConditions(
            status_register=StatusRegister(),
            pc=pc + 2,
            cycles=6,
            d=__GIVEN_DATA_REGISTERS | {
                x: __GIVEN_DATA_REGISTERS[y],
                y: __GIVEN_DATA_REGISTERS[x]
            },
            a=__GIVEN_ADDRESS_REGISTERS,
        ),
    )


def __exg_ax_ay(pc: int, x: int, y: int) -> TestData:
    return TestData(
        given=GivenConditions(
            status_register=StatusRegister(),
            pc=pc,
            d=__GIVEN_DATA_REGISTERS,
            a=__GIVEN_ADDRESS_REGISTERS,
        ),
        when=[f'EXG A{x}, A{y}'],
        then=ThenConditions(
            status_register=StatusRegister(),
            pc=pc + 2,
            cycles=6,
            d=__GIVEN_DATA_REGISTERS,
            a=__GIVEN_ADDRESS_REGISTERS | {
                x: __GIVEN_ADDRESS_REGISTERS[y],
                y: __GIVEN_ADDRESS_REGISTERS[x]
            }
        ),
    )


def __exg_dx_ay(pc: int, x: int, y: int) -> TestData:
    return TestData(
        given=GivenConditions(
            status_register=StatusRegister(),
            pc=pc,
            d=__GIVEN_DATA_REGISTERS,
            a=__GIVEN_ADDRESS_REGISTERS,
        ),
        when=[f'EXG D{x}, A{y}'],
        then=ThenConditions(
            status_register=StatusRegister(),
            pc=pc + 2,
            cycles=6,
            d=__GIVEN_DATA_REGISTERS | {
                x: __GIVEN_ADDRESS_REGISTERS[y],
            },
            a=__GIVEN_ADDRESS_REGISTERS | {
                y: __GIVEN_DATA_REGISTERS[x]
            },
        ),
    )


def __exg_test_cases(test_data_producer: Callable[[int, int, int], TestData]) -> List[TestData]:
    return [
        test_data_producer(pc, x, y)
        for pc, x, y, in itertools.product(
            PROGRAM_COUNTERS,
            __REGISTER_NUMBERS,
            __REGISTER_NUMBERS
        )
    ]


EXG = ManualTestFile(
    name='exg',
    d=[
        *__exg_test_cases(__exg_dx_dy),
        *__exg_test_cases(__exg_ax_ay),
        *__exg_test_cases(__exg_dx_ay),
    ]
)

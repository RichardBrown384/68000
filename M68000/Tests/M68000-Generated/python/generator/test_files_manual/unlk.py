import itertools

from .shared import PROGRAM_COUNTERS
from ..status_register_data import STACK_POINTERS
from ..types.manual_test_file import ManualTestFile
from ..types.memory import create_memory_long
from ..types.status_register import StatusRegister
from ..types.test_data import \
    TestData, \
    GivenConditions, \
    ThenConditions

__ADDRESS_REGISTERS = [1, 2, 5, 7]
__ADDRESS_VALUES = [0xCAFE_CAFE, 0xDEED_DEED]


def __unlk(pc: int, sp: int, n: int, value: int) -> TestData:
    return TestData(
        given=GivenConditions(
            status_register=StatusRegister(),
            pc=pc,
            a={
                7: 0x00DC_DCD0,
                n: sp - 4
            },
            memory=create_memory_long(sp - 4, value)
        ),
        when=[f'UNLK A{n}'],
        then=ThenConditions(
            status_register=StatusRegister(),
            pc=pc + 2,
            cycles=12,
            a={
                7: sp,
                n: value
            },
            memory=create_memory_long(sp - 4, value)
        ),
    )


UNLK = ManualTestFile(
    name='unlk',
    d=[
        __unlk(pc, sp, n, value)
        for pc, sp, n, value in itertools.product(
            PROGRAM_COUNTERS,
            STACK_POINTERS,
            __ADDRESS_REGISTERS,
            __ADDRESS_VALUES)
    ]
)

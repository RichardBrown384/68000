import itertools

from .shared import \
    PROGRAM_COUNTERS
from ..status_register_data import USER_STACK_POINTERS
from ..types.manual_test_file import ManualTestFile
from ..types.status_register import StatusRegister
from ..types.test_data import \
    TestData, \
    GivenConditions, \
    ThenConditions

__ADDRESS_REGISTERS = [1, 2, 5, 7]
__ADDRESS_VALUES = [0xCAFE_CAFE, 0xDEED_DEED]


def __to_usp(pc: int, usp: int, n: int, value: int) -> TestData:
    return TestData(
        given=GivenConditions(
            status_register=StatusRegister(),
            pc=pc,
            a={n: value},
            usp=usp
        ),
        when=[f'MOVE.L A{n}, USP'],
        then=ThenConditions(
            status_register=StatusRegister(),
            pc=pc + 2,
            cycles=4,
            a={n: value},
            usp=value
        ),
    )


def __from_usp(pc: int, usp: int, n: int, value: int) -> TestData:
    return TestData(
        given=GivenConditions(
            status_register=StatusRegister(),
            pc=pc,
            a={n: value},
            usp=usp
        ),
        when=[f'MOVE.L USP, A{n}'],
        then=ThenConditions(
            status_register=StatusRegister(),
            pc=pc + 2,
            cycles=4,
            a={n: usp},
            usp=usp
        ),
    )


MOVE_TO_USP = ManualTestFile(
    name='move_to_usp',
    d=[
        __to_usp(pc, usp, n, value)
        for pc, usp, n, value, in itertools.product(
            PROGRAM_COUNTERS,
            USER_STACK_POINTERS,
            __ADDRESS_REGISTERS,
            __ADDRESS_VALUES)
    ]
)

MOVE_FROM_USP = ManualTestFile(
    name='move_from_usp',
    d=[
        __from_usp(pc, usp, n, value)
        for pc, usp, n, value in itertools.product(
            PROGRAM_COUNTERS,
            USER_STACK_POINTERS,
            __ADDRESS_REGISTERS,
            __ADDRESS_VALUES)
    ]
)

import itertools

from .shared import \
    PROGRAM_COUNTERS, \
    RETURN_TARGETS
from ..status_register_data import STACK_POINTERS
from ..types.manual_test_file import ManualTestFile
from ..types.memory import create_memory_long
from ..types.status_register import StatusRegister
from ..types.test_data import \
    TestData, \
    GivenConditions, \
    ThenConditions


def __rts(pc: int, sp: int, target: int) -> TestData:
    return TestData(
        given=GivenConditions(
            status_register=StatusRegister(),
            pc=pc,
            a={7: sp},
            memory=create_memory_long(sp, target)),
        when=['RTS'],
        then=ThenConditions(
            status_register=StatusRegister(),
            pc=target,
            cycles=16,
            a={7: sp + 4},
            memory=create_memory_long(sp, target)),
    )


RTS = ManualTestFile(
    name='rts',
    d=[
        __rts(pc, sp, target)
        for pc, sp, target in itertools.product(
            PROGRAM_COUNTERS,
            STACK_POINTERS,
            RETURN_TARGETS
        )
    ]
)

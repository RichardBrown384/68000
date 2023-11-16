import itertools

from .shared import \
    PROGRAM_COUNTERS, \
    RETURN_TARGETS
from ..status_register_data import STACK_POINTERS
from ..types.manual_test_file import ManualTestFile
from ..types.memory import create_stack_frame
from ..types.status_register import StatusRegister
from ..types.test_data import \
    TestData, \
    GivenConditions, \
    ThenConditions

__GIVEN_STATUS_REGISTERS = [
    StatusRegister(s=True, v=True),
    StatusRegister(s=False, c=True)
]

__THEN_STATUS_REGISTERS = [
    StatusRegister(x=True, c=True),
    StatusRegister(s=False, n=True),
    StatusRegister(z=True, v=True)
]


def __rtr(
        pc: int,
        sp: int,
        given_status: StatusRegister,
        then_status: StatusRegister,
        target: int) -> TestData:
    return TestData(
        given=GivenConditions(
            status_register=given_status,
            pc=pc,
            a={7: sp},
            memory=create_stack_frame(
                sp, then_status.as_int(), target)),
        when=['RTR'],
        then=ThenConditions(
            status_register=StatusRegister.combine(given_status, then_status),
            pc=target,
            cycles=20,
            a={7: sp + 6},
            memory=create_stack_frame(
                sp, then_status.as_int(), target)),
    )


RTR = ManualTestFile(
    name='rtr',
    d=[
        __rtr(pc, sp, given_status, then_status, target)
        for pc, sp, given_status, then_status, target in itertools.product(
            PROGRAM_COUNTERS,
            STACK_POINTERS,
            __GIVEN_STATUS_REGISTERS,
            __THEN_STATUS_REGISTERS,
            RETURN_TARGETS
        )
    ]
)

import itertools

from .shared import \
    PROGRAM_COUNTERS, \
    RETURN_TARGETS
from ..status_register_data import STACK_POINTERS, USER_STACK_POINTERS
from ..types.manual_test_file import ManualTestFile
from ..types.memory import create_stack_frame
from ..types.status_register import StatusRegister
from ..types.test_data import \
    TestData, \
    GivenConditions, \
    ThenConditions

__GIVEN_STATUS_REGISTERS = [
    StatusRegister(s=True, v=True),
    StatusRegister(s=True, x=True, c=True),
]

__THEN_STATUS_REGISTERS = [
    StatusRegister(x=True, c=True),
    StatusRegister(s=False, n=True),
    StatusRegister(z=True, v=True)
]


# Note: this test exposes an implementation detail in the current cpu implementation
# The values held in SP while the cpu is in supervisor will be stale

def __rte(
        pc: int,
        sp: int,
        usp: int,
        given_status: StatusRegister,
        then_status: StatusRegister,
        target: int) -> TestData:
    return TestData(
        given=GivenConditions(
            status_register=given_status,
            pc=pc,
            a={7: sp},
            memory=create_stack_frame(
                sp, then_status.as_int(), target),
            usp=usp,
            ssp=sp),
        when=['RTE'],
        then=ThenConditions(
            status_register=then_status,
            pc=target,
            cycles=20,
            a={7: sp + 6 if then_status.s else usp},
            usp=usp,
            ssp=sp + 6 if not then_status.s else sp,
            memory=create_stack_frame(
                sp, then_status.as_int(), target)),
    )


RTE = ManualTestFile(
    name='rte',
    d=[
        __rte(pc, sp, usp, given_status, then_status, target)
        for pc, sp, usp, given_status, then_status, target in itertools.product(
            PROGRAM_COUNTERS,
            STACK_POINTERS,
            USER_STACK_POINTERS,
            __GIVEN_STATUS_REGISTERS,
            __THEN_STATUS_REGISTERS,
            RETURN_TARGETS
        )
    ]
)

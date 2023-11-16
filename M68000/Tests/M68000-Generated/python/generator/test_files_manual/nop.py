import itertools

from .shared import PROGRAM_COUNTERS
from ..types.manual_test_file import ManualTestFile
from ..types.status_register import StatusRegister
from ..types.test_data import \
    TestData, \
    GivenConditions, \
    ThenConditions

__SUPERVISORS = [True, False]


def __nop(pc: int, s: bool) -> TestData:
    return TestData(
        given=GivenConditions(
            status_register=StatusRegister(s=s),
            pc=pc
        ),
        when=['NOP'],
        then=ThenConditions(
            status_register=StatusRegister(s=s),
            pc=pc + 2,
            cycles=4,
        ),
    )


NOP = ManualTestFile(
    name='nop',
    d=[
        __nop(pc, s)
        for pc, s in itertools.product(
            PROGRAM_COUNTERS,
            __SUPERVISORS
        )
    ]
)

import itertools

from .shared import PROGRAM_COUNTERS
from ..types.manual_test_file import ManualTestFile
from ..types.status_register import StatusRegister
from ..types.test_data import \
    TestData, \
    GivenConditions, \
    ThenConditions

__GIVEN_STATUS_REGISTER = StatusRegister(
    x=True, n=True, z=True, c=True
)


def __trapv(pc: int) -> TestData:
    return TestData(
        given=GivenConditions(
            status_register=__GIVEN_STATUS_REGISTER,
            pc=pc
        ),
        when=['TRAPV'],
        then=ThenConditions(
            status_register=__GIVEN_STATUS_REGISTER,
            pc=pc + 2,
            cycles=4,
        ),
    )


TRAPV = ManualTestFile(
    name='trapv',
    d=[
        __trapv(pc)
        for pc, in itertools.product(
            PROGRAM_COUNTERS
        )
    ]
)

from .shared import PROGRAM_COUNTERS
from ..types.manual_test_file import ManualTestFile
from ..types.status_register import StatusRegister
from ..types.test_data import \
    TestData, \
    GivenConditions, \
    ThenConditions


def __reset(pc: int) -> TestData:
    return TestData(
        given=GivenConditions(
            status_register=StatusRegister(),
            pc=pc
        ),
        when=['RESET'],
        then=ThenConditions(
            status_register=StatusRegister(),
            pc=pc + 2,
            cycles=132,
        ),
    )


RESET = ManualTestFile(
    name='reset',
    d=[
        __reset(pc)
        for pc in PROGRAM_COUNTERS
    ]
)

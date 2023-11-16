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
__DISPLACEMENTS = [0x100, -0x100, -0x4000]


def __link(pc: int, sp: int, n: int, value: int, displacement: int) -> TestData:
    return TestData(
        given=GivenConditions(
            status_register=StatusRegister(),
            pc=pc,
            a={
                n: value,
                7: sp
            },
            memory=create_memory_long(sp - 4, 0xDCDC_DCDC)
        ),
        when=[f'LINK A{n}, #{displacement}'],
        then=ThenConditions(
            status_register=StatusRegister(),
            pc=pc + 4,
            cycles=16,
            a={
                n: sp - 4,
                7: sp - 4 + displacement
            },
            memory=create_memory_long(sp - 4, sp if n == 7 else value)
        ),
    )


LINK = ManualTestFile(
    name='link',
    d=[
        __link(pc, sp, n, value, displacement)
        for pc, sp, n, value, displacement in itertools.product(
            PROGRAM_COUNTERS,
            STACK_POINTERS,
            __ADDRESS_REGISTERS,
            __ADDRESS_VALUES,
            __DISPLACEMENTS)
    ]
)

from ..types.manual_test_file import ManualTestFile
from ..types.status_register import StatusRegister
from ..types.test_data import \
    TestData, \
    GivenConditions, \
    ThenConditions

__JMP_ADDRESS_INDIRECT = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        a={1: 0xDCDC_DCDC}),
    when=['JMP (A1)'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0xDCDC_DCDC,
        cycles=8,
        a={1: 0xDCDC_DCDC}),
)

__JMP_ADDRESS_DISPLACEMENT = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        a={1: 0xDCDC_DC00}),
    when=['JMP (0xDC, A1)'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0xDCDC_DCDC,
        cycles=10,
        a={1: 0xDCDC_DC00}),
)

__JMP_ADDRESS_INDEX = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        a={1: 0xDCDC_DC00, 2: 0x0000_00D0}),
    when=['JMP (0xA, A1, A2.L)'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0xDCDC_DCDA,
        cycles=14,
        a={1: 0xDCDC_DC00, 2: 0x0000_00D0}),
)

__JMP_ADDRESS_SHORT = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000),
    when=['JMP (0xDCDC).W'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0xFFFF_DCDC,
        cycles=10),
)

__JMP_ADDRESS_LONG = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000),
    when=['JMP (0xBBCCBBCC).L'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0xBBCC_BBCC,
        cycles=12),
)

__JMP_PC_DISPLACEMENT = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000),
    when=['JMP (0x200, PC)'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x0000_1202,
        cycles=10),
)

__JMP_PC_INDEX = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        a={2: 0x0000_0300}),
    when=['JMP (0x60, PC, A2.L)'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x0000_1362,
        cycles=14,
        a={2: 0x0000_0300}),
)

JMP = ManualTestFile(
    name='jmp',
    d=[
        __JMP_ADDRESS_INDIRECT,
        __JMP_ADDRESS_DISPLACEMENT,
        __JMP_ADDRESS_INDEX,
        __JMP_ADDRESS_SHORT,
        __JMP_ADDRESS_LONG,
        __JMP_PC_DISPLACEMENT,
        __JMP_PC_INDEX,
    ]
)

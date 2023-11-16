from ..types.manual_test_file import ManualTestFile
from ..types.status_register import StatusRegister
from ..types.test_data import \
    TestData, \
    GivenConditions, \
    ThenConditions

__LEA_ADDRESS_INDIRECT = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        a={1: 0xCAFE_CAFE, 5: 0xDCDC_DCDC}),
    when=['LEA (A1), A5'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x1002,
        cycles=4,
        a={1: 0xCAFE_CAFE, 5: 0xCAFE_CAFE}),
)

__LEA_ADDRESS_DISPLACEMENT = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        a={1: 0xCAFE_CA00, 5: 0xDCDC_DCDC}),
    when=['LEA (0xE8, A1), A5'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x1004,
        cycles=8,
        a={1: 0xCAFE_CA00, 5: 0xCAFE_CAE8}),
)

__LEA_ADDRESS_INDEX = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        a={1: 0xCAFE_CA00, 2: 0x0000_00D0, 5: 0xCDCD_CDCD}),
    when=['LEA (0xA, A1, A2.L), A5'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x1004,
        cycles=12,
        a={1: 0xCAFE_CA00, 2: 0x0000_00D0, 5: 0xCAFE_CADA}),
)

__LEA_ADDRESS_SHORT = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        a={5: 0xBABA_BABA}),
    when=['LEA (0xDCDC).W, A5'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x1004,
        cycles=8,
        a={5: 0xFFFF_DCDC}),
)

__LEA_ADDRESS_LONG = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        a={5: 0xBABA_BABA}),
    when=['LEA (0xBBCCBBCC).L, A5'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x1006,
        cycles=12,
        a={5: 0xBBCCBBCC}),
)

__LEA_PC_DISPLACEMENT = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        a={5: 0xCAFE_CAFE}),
    when=['LEA (0x200, PC), A5'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x1004,
        cycles=8,
        a={5: 0x0000_1202}),
)

__LEA_PC_INDEX = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        a={2: 0x0000_0300, 5: 0xCAFE_CAFE}),
    when=['LEA (0x60, PC, A2.L), A5'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x1004,
        cycles=12,
        a={2: 0x0000_0300, 5: 0x0000_1362}),
)

LEA = ManualTestFile(
    name='lea',
    d=[
        __LEA_ADDRESS_INDIRECT,
        __LEA_ADDRESS_DISPLACEMENT,
        __LEA_ADDRESS_INDEX,
        __LEA_ADDRESS_SHORT,
        __LEA_ADDRESS_LONG,
        __LEA_PC_DISPLACEMENT,
        __LEA_PC_INDEX,
    ]
)

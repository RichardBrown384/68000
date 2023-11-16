from ..types.manual_test_file import ManualTestFile
from ..types.memory import create_memory_long
from ..types.status_register import StatusRegister
from ..types.test_data import \
    TestData, \
    GivenConditions, \
    ThenConditions

__JSR_ADDRESS_INDIRECT = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        a={1: 0xDCDC_DCDC, 7: 0x0100_0000},
        memory=create_memory_long(0x00FF_FFFC, 0xCAFE_CAFE)),
    when=['JSR (A1)'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0xDCDC_DCDC,
        cycles=16,
        a={1: 0xDCDC_DCDC, 7: 0x00FF_FFFC},
        memory=create_memory_long(0x00FF_FFFC, 0x0000_1002)),
)

__JSR_ADDRESS_DISPLACEMENT = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        a={1: 0xDCDC_DC00, 7: 0x0100_0000},
        memory=create_memory_long(0x00FF_FFFC, 0xCAFE_CAFE)),
    when=['JSR (0xDC, A1)'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0xDCDC_DCDC,
        cycles=18,
        a={1: 0xDCDC_DC00, 7: 0x00FF_FFFC},
        memory=create_memory_long(0x00FF_FFFC, 0x0000_1004)),
)

__JSR_ADDRESS_INDEX = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        a={1: 0xDCDC_DC00, 2: 0x0000_00D0, 7: 0x0100_0000},
        memory=create_memory_long(0x00FF_FFFC, 0xCAFE_CAFE)),
    when=['JSR (0xA, A1, A2.L)'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0xDCDC_DCDA,
        cycles=22,
        a={1: 0xDCDC_DC00, 2: 0x0000_00D0, 7: 0x00FF_FFFC},
        memory=create_memory_long(0x00FF_FFFC, 0x0000_1004)),
)

__JSR_ADDRESS_SHORT = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        a={7: 0x0100_0000},
        memory=create_memory_long(0x00FF_FFFC, 0xCAFE_CAFE)),
    when=['JSR (0xDCDC).W'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0xFFFF_DCDC,
        cycles=18,
        a={7: 0x00FF_FFFC},
        memory=create_memory_long(0x00FF_FFFC, 0x0000_1004)),
)

__JSR_ADDRESS_LONG = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        a={7: 0x0100_0000},
        memory=create_memory_long(0x00FF_FFFC, 0xCAFE_CAFE)),
    when=['JSR (0xBBCCBBCC).L'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0xBBCC_BBCC,
        cycles=20,
        a={7: 0x00FF_FFFC},
        memory=create_memory_long(0x00FF_FFFC, 0x0000_1006)),
)

__JSR_PC_DISPLACEMENT = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        a={7: 0x0100_0000},
        memory=create_memory_long(0x00FF_FFFC, 0xCAFE_CAFE)),
    when=['JSR (0x200, PC)'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x0000_1202,
        cycles=18,
        a={7: 0x00FF_FFFC},
        memory=create_memory_long(0x00FF_FFFC, 0x0000_1004)),
)

__JSR_PC_INDEX = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        a={2: 0x0000_0300, 7: 0x0100_0000},
        memory=create_memory_long(0x00FF_FFFC, 0xCAFE_CAFE)),
    when=['JSR (0x60, PC, A2.L)'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x0000_1362,
        cycles=22,
        a={2: 0x0000_0300, 7: 0x00FF_FFFC},
        memory=create_memory_long(0x00FF_FFFC, 0x0000_1004)),
)

JSR = ManualTestFile(
    name='jsr',
    d=[
        __JSR_ADDRESS_INDIRECT,
        __JSR_ADDRESS_DISPLACEMENT,
        __JSR_ADDRESS_INDEX,
        __JSR_ADDRESS_SHORT,
        __JSR_ADDRESS_LONG,
        __JSR_PC_DISPLACEMENT,
        __JSR_PC_INDEX,
    ]
)

from ..types.manual_test_file import ManualTestFile
from ..types.memory import create_memory_long
from ..types.status_register import StatusRegister
from ..types.test_data import \
    TestData, \
    GivenConditions, \
    ThenConditions

__PEA_ADDRESS_INDIRECT = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        a={1: 0xDCDC_DCDC, 7: 0x0100_0000},
        memory=create_memory_long(0x00FF_FFFC, 0xCAFE_CAFE)),
    when=['PEA (A1)'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x1002,
        cycles=12,
        a={1: 0xDCDC_DCDC, 7: 0x00FF_FFFC},
        memory=create_memory_long(0x00FF_FFFC, 0xDCDC_DCDC)),
)

__PEA_ADDRESS_DISPLACEMENT = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        a={1: 0xDCDC_DC00, 7: 0x0100_0000},
        memory=create_memory_long(0x00FF_FFFC, 0xCAFE_CAFE)),
    when=['PEA (0xDC, A1)'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x1004,
        cycles=16,
        a={1: 0xDCDC_DC00, 7: 0x00FF_FFFC},
        memory=create_memory_long(0x00FF_FFFC, 0xDCDC_DCDC)),
)

__PEA_ADDRESS_INDEX = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        a={1: 0xDCDC_DC00, 2: 0x0000_00D0, 7: 0x0100_0000},
        memory=create_memory_long(0x00FF_FFFC, 0xCAFE_CAFE)),
    when=['PEA (0xA, A1, A2.L)'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x1004,
        cycles=20,
        a={1: 0xDCDC_DC00, 2: 0x0000_00D0, 7: 0x00FF_FFFC},
        memory=create_memory_long(0x00FF_FFFC, 0xDCDC_DCDA)),
)

__PEA_ADDRESS_SHORT = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        a={7: 0x0100_0000},
        memory=create_memory_long(0x00FF_FFFC, 0xCAFE_CAFE)),
    when=['PEA (0xDCDC).W'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x1004,
        cycles=16,
        a={7: 0x00FF_FFFC},
        memory=create_memory_long(0x00FF_FFFC, 0xFFFF_DCDC)),
)

__PEA_ADDRESS_LONG = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        a={7: 0x0100_0000},
        memory=create_memory_long(0x00FF_FFFC, 0xCAFE_CAFE)),
    when=['PEA (0xBBCCBBCC).L'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x1006,
        cycles=20,
        a={7: 0x00FF_FFFC},
        memory=create_memory_long(0x00FF_FFFC, 0xBBCC_BBCC)),
)

__PEA_PC_DISPLACEMENT = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        a={7: 0x0100_0000},
        memory=create_memory_long(0x00FF_FFFC, 0xCAFE_CAFE)),
    when=['PEA (0x200, PC)'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x1004,
        cycles=16,
        a={7: 0x00FF_FFFC},
        memory=create_memory_long(0x00FF_FFFC, 0x0000_1202)),
)

__PEA_PC_INDEX = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        a={2: 0x0000_0300, 7: 0x0100_0000},
        memory=create_memory_long(0x00FF_FFFC, 0xCAFE_CAFE)),
    when=['PEA (0x60, PC, A2.L)'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x1004,
        cycles=20,
        a={2: 0x0000_0300, 7: 0x00FF_FFFC},
        memory=create_memory_long(0x00FF_FFFC, 0x0000_1362)),
)

PEA = ManualTestFile(
    name='pea',
    d=[
        __PEA_ADDRESS_INDIRECT,
        __PEA_ADDRESS_DISPLACEMENT,
        __PEA_ADDRESS_INDEX,
        __PEA_ADDRESS_SHORT,
        __PEA_ADDRESS_LONG,
        __PEA_PC_DISPLACEMENT,
        __PEA_PC_INDEX,
    ]
)

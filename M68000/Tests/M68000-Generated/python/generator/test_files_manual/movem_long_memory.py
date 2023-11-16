from ..types.manual_test_file import ManualTestFile
from ..types.memory import create_memory_longs
from ..types.status_register import StatusRegister
from ..types.test_data import \
    TestData, \
    GivenConditions, \
    ThenConditions

__REGISTER_SIZE = 4
__BASE_ADDRESS = 0x0000_2000
__INDEX_ADDRESS = 0x0000_01FE

__GIVEN_DATA_REGISTERS = {
    1: 0xAADD_CCBB,
    2: 0xE0E0_E0E0
}

__GIVEN_ADDRESS_REGISTERS = {
    4: __BASE_ADDRESS,
    5: 0x1010_1010,
    6: __INDEX_ADDRESS
}


def create_given_memory(address):
    return create_memory_longs(
        address,
        0xFFFF_FFFF,
        0xFFFF_FFFF,
        0xFFFF_FFFF,
        0xFFFF_FFFF)


def create_then_memory(address):
    return create_memory_longs(
        address,
        __GIVEN_DATA_REGISTERS[1],
        __GIVEN_DATA_REGISTERS[2],
        __GIVEN_ADDRESS_REGISTERS[4],
        __GIVEN_ADDRESS_REGISTERS[5])


__MOVEM_ADDRESS_INDIRECT = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        d=__GIVEN_DATA_REGISTERS,
        a=__GIVEN_ADDRESS_REGISTERS,
        memory=create_given_memory(__BASE_ADDRESS)),
    when=['MOVEM.L D1-D2/A4-A5, (A4)'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x1004,
        cycles=40,
        d=__GIVEN_DATA_REGISTERS,
        a=__GIVEN_ADDRESS_REGISTERS,
        memory=create_then_memory(__BASE_ADDRESS)),
)

__MOVEM_ADDRESS_DECREMENT = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        d=__GIVEN_DATA_REGISTERS,
        a=__GIVEN_ADDRESS_REGISTERS,
        memory=create_given_memory(__BASE_ADDRESS)),
    when=['MOVEM.L D1-D2/A4-A5, -(A4)'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x1004,
        cycles=40,
        d=__GIVEN_DATA_REGISTERS,
        a=__GIVEN_ADDRESS_REGISTERS | {4: __BASE_ADDRESS - 4 * __REGISTER_SIZE},
        memory=create_then_memory(__BASE_ADDRESS - 4 * __REGISTER_SIZE)),
)

__MOVEM_ADDRESS_DISPLACEMENT = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        d=__GIVEN_DATA_REGISTERS,
        a=__GIVEN_ADDRESS_REGISTERS,
        memory=create_given_memory(__BASE_ADDRESS + 0xDC)),
    when=['MOVEM.L D1-D2/A4-A5, (0xDC, A4)'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x1006,
        cycles=44,
        d=__GIVEN_DATA_REGISTERS,
        a=__GIVEN_ADDRESS_REGISTERS,
        memory=create_then_memory(__BASE_ADDRESS + 0xDC)),
)

__MOVEM_ADDRESS_INDEX = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        d=__GIVEN_DATA_REGISTERS,
        a=__GIVEN_ADDRESS_REGISTERS,
        memory=create_given_memory(__BASE_ADDRESS + __INDEX_ADDRESS + 0x02)),
    when=['MOVEM.L D1-D2/A4-A5, (0x02, A4, A6.L)'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x1006,
        cycles=46,
        d=__GIVEN_DATA_REGISTERS,
        a=__GIVEN_ADDRESS_REGISTERS,
        memory=create_then_memory(__BASE_ADDRESS + __INDEX_ADDRESS + 0x02)),
)

__MOVEM_ADDRESS_SHORT = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        d=__GIVEN_DATA_REGISTERS,
        a=__GIVEN_ADDRESS_REGISTERS,
        memory=create_given_memory(0xFFFF_DCDC)),
    when=['MOVEM.L D1-D2/A4-A5, (0xDCDC).W'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x1006,
        cycles=44,
        d=__GIVEN_DATA_REGISTERS,
        a=__GIVEN_ADDRESS_REGISTERS,
        memory=create_then_memory(0xFFFF_DCDC)),
)

__MOVEM_ADDRESS_LONG = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        d=__GIVEN_DATA_REGISTERS,
        a=__GIVEN_ADDRESS_REGISTERS,
        memory=create_given_memory(0xBBCC_BBCC)),
    when=['MOVEM.L D1-D2/A4-A5, (0xBBCCBBCC).L'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x1008,
        cycles=48,
        d=__GIVEN_DATA_REGISTERS,
        a=__GIVEN_ADDRESS_REGISTERS,
        memory=create_then_memory(0xBBCC_BBCC)),
)

MOVEM_LONG_MEMORY = ManualTestFile(
    name='movem_long_memory',
    d=[
        __MOVEM_ADDRESS_INDIRECT,
        __MOVEM_ADDRESS_DECREMENT,
        __MOVEM_ADDRESS_DISPLACEMENT,
        __MOVEM_ADDRESS_INDEX,
        __MOVEM_ADDRESS_SHORT,
        __MOVEM_ADDRESS_LONG,
    ]
)

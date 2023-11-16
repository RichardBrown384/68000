from ..types.address_modes.util.sign_extend import sign_extend_word
from ..types.manual_test_file import ManualTestFile
from ..types.memory import create_memory_words
from ..types.status_register import StatusRegister
from ..types.test_data import \
    TestData, \
    GivenConditions, \
    ThenConditions

__REGISTER_SIZE = 2
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

__THEN_VALUE_1 = 0xDEED
__THEN_VALUE_2 = 0x7EEF
__THEN_VALUE_3 = 0x8080
__THEN_VALUE_4 = 0x7091

__THEN_DATA_REGISTERS = {
    1: sign_extend_word(__THEN_VALUE_1),
    2: sign_extend_word(__THEN_VALUE_2)
}

__THEN_ADDRESS_REGISTERS = {
    4: sign_extend_word(__THEN_VALUE_3),
    5: sign_extend_word(__THEN_VALUE_4)
}


def create_memory(address):
    return create_memory_words(
        address,
        __THEN_VALUE_1, __THEN_VALUE_2,
        __THEN_VALUE_3, __THEN_VALUE_4)


__MOVEM_ADDRESS_INDIRECT = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        d=__GIVEN_DATA_REGISTERS,
        a=__GIVEN_ADDRESS_REGISTERS,
        memory=create_memory(__BASE_ADDRESS)),
    when=['MOVEM.W (A4), D1-D2/A4-A5'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x1004,
        cycles=28,
        d=__THEN_DATA_REGISTERS,
        a=__THEN_ADDRESS_REGISTERS,
        memory=create_memory(__BASE_ADDRESS)),
)

__MOVEM_ADDRESS_INCREMENT = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        d=__GIVEN_DATA_REGISTERS,
        a=__GIVEN_ADDRESS_REGISTERS,
        memory=create_memory(__BASE_ADDRESS)),
    when=['MOVEM.W (A4)+, D1-D2/A4-A5'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x1004,
        cycles=28,
        d=__THEN_DATA_REGISTERS,
        a=__THEN_ADDRESS_REGISTERS | {4: __BASE_ADDRESS + 4 * __REGISTER_SIZE},
        memory=create_memory(__BASE_ADDRESS)),
)

__MOVEM_ADDRESS_DISPLACEMENT = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        d=__GIVEN_DATA_REGISTERS,
        a=__GIVEN_ADDRESS_REGISTERS,
        memory=create_memory(__BASE_ADDRESS + 0xDC)),
    when=['MOVEM.W (0xDC, A4), D1-D2/A4-A5'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x1006,
        cycles=32,
        d=__THEN_DATA_REGISTERS,
        a=__THEN_ADDRESS_REGISTERS,
        memory=create_memory(__BASE_ADDRESS + 0xDC)),
)

__MOVEM_ADDRESS_INDEX = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        d=__GIVEN_DATA_REGISTERS,
        a=__GIVEN_ADDRESS_REGISTERS,
        memory=create_memory(__BASE_ADDRESS + __INDEX_ADDRESS + 0x02)),
    when=['MOVEM.W (0x02, A4, A6.L), D1-D2/A4-A5'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x1006,
        cycles=34,
        d=__THEN_DATA_REGISTERS,
        a=__THEN_ADDRESS_REGISTERS,
        memory=create_memory(__BASE_ADDRESS + __INDEX_ADDRESS + 0x02)),
)

__MOVEM_ADDRESS_SHORT = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        d=__GIVEN_DATA_REGISTERS,
        a=__GIVEN_ADDRESS_REGISTERS,
        memory=create_memory(0xFFFF_DCDC)),
    when=['MOVEM.W (0xDCDC).W, D1-D2/A4-A5'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x1006,
        cycles=32,
        d=__THEN_DATA_REGISTERS,
        a=__THEN_ADDRESS_REGISTERS,
        memory=create_memory(0xFFFF_DCDC)),
)

__MOVEM_ADDRESS_LONG = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        d=__GIVEN_DATA_REGISTERS,
        a=__GIVEN_ADDRESS_REGISTERS,
        memory=create_memory(0xBBCC_BBCC)),
    when=['MOVEM.W (0xBBCCBBCC).L, D1-D2/A4-A5'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x1008,
        cycles=36,
        d=__THEN_DATA_REGISTERS,
        a=__THEN_ADDRESS_REGISTERS,
        memory=create_memory(0xBBCC_BBCC)),
)

__MOVEM_PC_DISPLACEMENT = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        d=__GIVEN_DATA_REGISTERS,
        a=__GIVEN_ADDRESS_REGISTERS,
        memory=create_memory(0x1204)),
    when=['MOVEM.W (0x200, PC), D1-D2/A4-A5'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x1006,
        cycles=32,
        d=__THEN_DATA_REGISTERS,
        a=__THEN_ADDRESS_REGISTERS,
        memory=create_memory(0x1204)),
)

__MOVEM_PC_INDEX = TestData(
    given=GivenConditions(
        status_register=StatusRegister(),
        pc=0x1000,
        d=__GIVEN_DATA_REGISTERS,
        a=__GIVEN_ADDRESS_REGISTERS,
        memory=create_memory(0x1004 + __INDEX_ADDRESS + 0x02)),
    when=['MOVEM.W (0x02, PC, A6.L), D1-D2/A4-A5'],
    then=ThenConditions(
        status_register=StatusRegister(),
        pc=0x1006,
        cycles=34,
        d=__THEN_DATA_REGISTERS,
        a=__THEN_ADDRESS_REGISTERS,
        memory=create_memory(0x1004 + __INDEX_ADDRESS + 0x02)),
)

MOVEM_WORD_REGISTER = ManualTestFile(
    name='movem_word_register',
    d=[
        __MOVEM_ADDRESS_INDIRECT,
        __MOVEM_ADDRESS_INCREMENT,
        __MOVEM_ADDRESS_DISPLACEMENT,
        __MOVEM_ADDRESS_INDEX,
        __MOVEM_ADDRESS_SHORT,
        __MOVEM_ADDRESS_LONG,
        __MOVEM_PC_DISPLACEMENT,
        __MOVEM_PC_INDEX,
    ]
)
